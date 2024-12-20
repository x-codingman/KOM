import os
import json
import re




# def parse_function_declaration(declaration):
#     pattern = r'(\w+)\s+(\w+)\s*\((.*?)\)'
#     match = re.match(pattern, declaration.strip().replace('\n', ' '))
#     if not match:
#         return None

#     return_type = match.group(1)
#     function_name = match.group(2)
#     args = match.group(3)

#     args_split = [arg.strip() for arg in args.split(',')]
#     arg_types = []
#     arg_names = []

#     for arg in args_split:
#         split_arg = re.split(r'\s+', arg.strip())
        
#         # Checking if const is present
#         if 'const' in split_arg:
#             type_part = ' '.join(split_arg[:-1]) # everything except the last part which is the argument name
#         else:
#             type_part = split_arg[0] if len(split_arg) == 2 else ' '.join(split_arg[:-1])
        
#         arg_names.append(split_arg[-1])
#         arg_types.append(type_part)

#     control_flags = ["true"] * len(arg_names)  # Creating a list of 'true' values equal to the number of arguments

#     return {
#         "name": function_name,
#         "arg_nums": len(arg_names),
#         "arguments": ", ".join(arg_names),
#         "type": ", ".join(arg_types),
#         "control_flags": ", ".join(control_flags)
#     }



# with open("funcs.txt", "r") as f:
#     content = f.read()

# declarations = re.findall(r'(\w+\s+\w+\s*\(.*?\))', content, re.DOTALL)
# parsed_functions = [parse_function_declaration(decl) for decl in declarations]

# # Writing the parsed information to a JSON file
# with open('funcs_info_v2.json', 'w') as json_file:
#     json.dump(parsed_functions, json_file, indent=4)

# exit()


with open('funcs_info_v2.json', 'r') as f:
    funcs = json.load(f)

for func in funcs:
    arg_names = func["arguments"].split(',')
    arg_types = func["type"].split(',')
    control_flags = func["control_flags"].split(',')
    declarations = []
    klee_calls = []
    conditions = []
    for arg_name, arg_type, control_flag in zip(arg_names, arg_types, control_flags):
        declarations.append(f'{arg_type.strip()} {arg_name.strip()};\n')
        if control_flag.strip() == "restricted":
            conditions.append( f'if ({arg_name.strip()} < ATTACK_CAPABILITY_REGION_START || {arg_name.strip()} > ATTACK_CAPABILITY_REGION_END) {{ return 0; }}\n')
            klee_calls.append(f'klee_make_symbolic_controllable(&{arg_name.strip()}, sizeof({arg_name.strip()}), "{arg_name.strip()}", true);\n')
        else:    
            klee_calls.append(f'klee_make_symbolic_controllable(&{arg_name.strip()}, sizeof({arg_name.strip()}), "{arg_name.strip()}", {control_flag.strip()});\n')
    declaration_code = ''.join(declarations)
    klee_call_code = ''.join(klee_calls)
    condition_code = ''.join(conditions)
    function_call = f'{func["name"]}({func["arguments"]});\n'
    # Rest of the script
    func_name = func['name']
    file_path = f"test_files/{func_name}.c"
    print(f"Generating file {file_path}...")

    with open(file_path, 'w') as file:
        file.write('#include "klee_help.h"\n')
        file.write('#include <FreeRTOS.h>\n')
        file.write('#include <task.h>\n')
        file.write('#include <queue.h>\n')
        file.write('#include <klee/klee.h>\n')
        file.write('#include <list.h>\n')
        file.write('#define STACK_SIZE 200\n')
        file.write('#define MPU_ENABLE_ADDRESS_START 0xefff2000\n')
        file.write('#define MPU_ENABLE_ADDRESS_END 0xefff4000\n')
        file.write('#define ATTACK_CAPABILITY_REGION_START 0x80000000\n')
        file.write('#define ATTACK_CAPABILITY_REGION_END 0x8fffffff\n')
        file.write('void vTaskFunction1( void *pvParameters );\n')
        file.write('int main()\n')
        file.write('{\n')
        file.write('xTaskCreate(vTaskFunction1, "Task1", STACK_SIZE, NULL, 1, NULL);\n')
        file.write(declaration_code)
        file.write(klee_call_code)
        file.write(condition_code)
        file.write(function_call)
        file.write('return 0;\n')
        file.write('}\n')
        file.write('void vTaskFunction1( void *pvParameters )\n')
        file.write('{\n')
        file.write('assert(0);\n')
        file.write('}\n')
        file.close()

    print(f"File {file_path} generated.")