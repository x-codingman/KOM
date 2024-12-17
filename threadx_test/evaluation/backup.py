import os
import re

output_dir = "evaluation_files"
if not os.path.exists(output_dir):
    os.makedirs(output_dir)

import re

def extract_params(param_str):
    params = []
    param_str_parts = [part.strip() for part in param_str.split(",")]

    is_function_pointer = False
    func_ptr_decl = ""

    for segment in param_str_parts:
        if '(' in segment and ')' not in segment:  # If it's the beginning of a function pointer
            is_function_pointer = True
            func_ptr_decl = segment
        elif is_function_pointer and ')' in segment:  # If it's the end of a function pointer
            func_ptr_decl += ", " + segment
            params.append((func_ptr_decl, 'fp'))
            is_function_pointer = False
            func_ptr_decl = ""
        elif is_function_pointer:  # If it's a part of a function pointer
            func_ptr_decl += ", " + segment
        else:
            type_name, var_name = re.match(r'(\w+(?:\s*\*\s*\*?)?)\s*(\w+)', segment).groups()
            param_type = type_name.strip()
            param_name = var_name.strip()
            params.append((param_type, param_name))

    return params

def generate_c_file(func_name, params):
    content = '''#include "tx_api.h"
#include "klee/klee.h"
#include "klee_help.h"\n\n'''

    content += 'int main()\n{\n'

    call_params = []
    for param_type, param_name in params:
        if '(' in param_type:  # If it's a function pointer
            content += f"    {param_type};\n"
            call_params.append(param_name)
        else:
            content += f"    {param_type} {param_name};\n"
            content += f'    klee_make_symbolic_controllable(&{param_name}, sizeof({param_name}), "{param_name}", true);\n'
            call_params.append(param_name)

    func_call = "{}({});".format(func_name, ', '.join(call_params))
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
        
        c_content = generate_c_file("_txe_" + func_name, params)
        with open(os.path.join(output_dir, f"_txe_{func_name}.c"), 'w') as f:
            f.write(c_content)