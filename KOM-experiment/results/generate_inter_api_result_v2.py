import os
import json
import pandas as pd

def count_keys_in_json(file_path):
    """ 读取JSON文件并计算其中的键的数量。"""
    with open(file_path, 'r') as file:
        data = json.load(file)
        return len(data)

def count_no_constraint(file_path):
    with open(file_path, 'r') as file:
        count = 0
        datas = json.load(file)
        for key, value in datas.items():
            if key.startswith("writable location"):
                if value.get("constraints")==[]:
                    count+=1
        return count

def max_keys_json_in_directory(directory):
    """ 返回给定目录中键数量最多的JSON文件的键的数量。"""
    max_keys = 0
    max_no_constraint = 0
    for filename in os.listdir(directory):
        if filename.endswith('.json'):
            file_path = os.path.join(directory, filename)
            keys_count = count_keys_in_json(file_path)
            no_constraint_count = count_no_constraint(file_path)
            if keys_count > max_keys:
                max_keys = keys_count
            if no_constraint_count > max_no_constraint:
                max_no_constraint = no_constraint_count
    return max_keys, max_no_constraint

def generate_report(base_directory):
    """ 生成报告并保存为xlsx文件。"""
    result = get_api_combination_result()
    report = []
    function_count=0
    for folder in os.listdir(base_directory):
        function_count = function_count+1
        folder_path = os.path.join(base_directory, folder)
        if os.path.isdir(folder_path):
            max_keys, max_no_constraint = max_keys_json_in_directory(folder_path)
            if max_keys == 0:
                max_keys =2
            if result.get(folder) is None:
                result[folder] = 0
            type_name = folder.split("_")[0].upper()
            
            report.append([folder,type_name, result[folder],max_keys-2, max_no_constraint])
    print("Num of funcs:" + str(function_count))
           
    # 转换为DataFrame并保存为Excel文件
    
    df = pd.DataFrame(report, columns=['API Name', "Type","Count combinations",'Writable Location Count',"No Constraint Count"])
    df.to_excel('system_call_pairs_report.xlsx', index=False)


def get_api_combination_result():
    filename = 'output.xlsx'  # 替换为你的文件名
    df = pd.read_excel(filename, index_col=0, engine='openpyxl')

    # 初始化一个空的字典来存储结果
    result = {}
    num = 0

    # 遍历每一行
    for function in df.index:
        # 过滤出不包含 "create" 的行
        filtered_df = df.loc[function][~df.loc[function].index.str.contains('create')]
        count_ok = filtered_df.value_counts().get('✓', 0)
        result[function] = count_ok - 1
        if count_ok >= 1:
            num = num + 1
    print(num)
    return result

# 将下面的路径替换为你的基础目录路径
base_directory = '/home/klee/threadx/symbolic_execution/test-info-output'
generate_report(base_directory)
