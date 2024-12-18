import os
import re

output_dir = "evaluation_files"
if not os.path.exists(output_dir):
    os.makedirs(output_dir)

def extract_params(param_str):
    params = []
    param_str = param_str.strip()
    if param_str.upper() == "VOID":  # Special handling for VOID type
        return params

    param_str_parts = [part.strip() for part in param_str.split(",")]

    buffer = ""

    for segment in param_str_parts:
        if not buffer:
            buffer = segment
        else:
            buffer += ", " + segment

        open_brackets = buffer.count('(')
        close_brackets = buffer.count(')')
        
        if open_brackets == close_brackets:  # when we have a complete parameter
            segment = buffer
            buffer = ""

            if "(" in segment and ")" in segment and "(*" in segment:  # Function pointer
                func_ptr_decl = segment
                match = re.search(r'\(\*(\w+)\)', func_ptr_decl)
                if match:
                    func_ptr_name = match.group(1)
                    params.append((func_ptr_decl, func_ptr_name))
            else:
                type_name, var_name = re.match(r'(\w+(?:\s*\*\s*\*?)?)\s*(\w+)', segment).groups()
                param_type = type_name.strip()
                param_name = "KLEE_TX_"+var_name.strip()
                params.append((param_type, param_name))

    return params




def generate_c_file(func_name, params):
    content = '''#include "tx_api.h"
#include "klee/klee.h"
#include "klee_help.h"\n\n'''


    content += 'extern TX_THREAD *    _tx_thread_current_ptr;\n\n'
    #content += '_tx_thread_current_ptr -> tx_thread_module_instance_ptr->txm_module_instance_property_flags |= TXM_MODULE_MEMORY_PROTECTION;\n\n'
    content += 'UCHAR                   pool_start[9120];\n\n'
    content += 'int main()\n{\n'
    content += '    klee_make_symbolic_controllable(&_tx_thread_current_ptr, sizeof(_tx_thread_current_ptr), "_tx_thread_current_ptr", false);\n'
    content += '    _txm_module_kernel_call_dispatcher=_txm_module_manager_kernel_dispatch;\n'
    call_params = []
    for param_type, param_name in params:
        if '(' in param_type:  # If it's a function pointer
            content += f"    {param_type};\n"
            call_params.append(param_name)
            content += f'    klee_make_symbolic_controllable(&{param_name}, sizeof({param_name}), "{param_name}", true);\n'
        else:
            if(param_name != 'pool_start'):
                content += f"    {param_type} {param_name};\n"
                content += f'    klee_make_symbolic_controllable(&{param_name}, sizeof({param_name}), "{param_name}", true);\n'
            call_params.append(param_name)

    func_call = "{}({});".format("m_txe_"+func_name, ', '.join(call_params))
    content += f'    {func_call}\n'
    content += '}\n'
    return content

with open('funcs.txt', 'r') as f:
    content = f.read().splitlines()

for line in content:
    match = re.match(r'(.+)\s+_txe_(\w+)\((.*)\);', line)
    if match:
        return_type, func_name, param_str = match.groups()
        params = extract_params(param_str)
        
        c_content = generate_c_file(func_name, params)
        with open(os.path.join(output_dir, f"{func_name}.c"), 'w') as f:
            f.write(c_content)
