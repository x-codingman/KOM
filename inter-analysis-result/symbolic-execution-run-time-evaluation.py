import os
import pandas as pd



def time_tranform(time_str):

    # Split the time string into its components
    hours, minutes, seconds = [int(i) for i in time_str.split(":")]

    # Calculate total seconds
    total_seconds = hours * 3600 + minutes * 60 + seconds
    return total_seconds

def extract_info(directory):
    # 创建一个空的DataFrame来存储结果
    df = pd.DataFrame(columns=['System Call', 'Elapsed', 'Explored Paths', 'Avg. Constructs Per Query', 
                               'Total Queries', 'Valid Queries', 'Invalid Queries', 'Query Cex',
                               'Total Instructions', 'Completed Paths', 'Partially Completed Paths', 
                               'Generated Tests'])

    # 遍历目录下的每个子文件夹
    for folder in os.listdir(directory):
        folder_path = os.path.join(directory, folder)
        if os.path.isdir(folder_path):
            info_file = os.path.join(folder_path, "info")
            
            # 检查info文件是否存在
            if os.path.isfile(info_file):
                with open(info_file, 'r') as file:
                    content = file.read()

                    # 提取信息
                    try:
                        elapsed = content.split('Elapsed: ')[1].split('\n')[0]
                        explored_paths = content.split('explored paths = ')[1].split('\n')[0]
                        avg_constructs = content.split('avg. constructs per query = ')[1].split('\n')[0]
                        total_queries = content.split('total queries = ')[1].split('\n')[0]
                        valid_queries = content.split('valid queries = ')[1].split('\n')[0]
                        invalid_queries = content.split('invalid queries = ')[1].split('\n')[0]
                        query_cex = content.split('query cex = ')[1].split('\n')[0]
                        total_instructions = content.split('total instructions = ')[1].split('\n')[0]
                        completed_paths = content.split('completed paths = ')[1].split('\n')[0]
                        partially_completed_paths = content.split('partially completed paths = ')[1].split('\n')[0]
                        generated_tests = content.split('generated tests = ')[1].split('\n')[0]

                        # 添加到DataFrame
                        df = df.append({'System Call': folder, 'Elapsed': time_tranform(elapsed), 'Explored Paths': explored_paths, 
                                        'Avg. Constructs Per Query': avg_constructs, 'Total Queries': total_queries, 
                                        'Valid Queries': valid_queries, 'Invalid Queries': invalid_queries, 
                                        'Query Cex': query_cex, 'Total Instructions': total_instructions, 
                                        'Completed Paths': completed_paths, 'Partially Completed Paths': partially_completed_paths, 
                                        'Generated Tests': generated_tests}, ignore_index=True)
                    except IndexError:
                        # 如果格式不匹配，添加NA
                        df = df.append({'System Call': folder, 'Elapsed': 'NA', 'Explored Paths': 'NA', 
                                        'Avg. Constructs Per Query': 'NA', 'Total Queries': 'NA', 
                                        'Valid Queries': 'NA', 'Invalid Queries': 'NA', 
                                        'Query Cex': 'NA', 'Total Instructions': 'NA', 
                                        'Completed Paths': 'NA', 'Partially Completed Paths': 'NA', 
                                        'Generated Tests': 'NA'}, ignore_index=True)

    return df

# 示例：使用函数
# 注意：请将 'your_directory_path' 替换为实际的目录路径
directory_path = '/home/klee/threadx/symbolic_execution/output'
dataframe = extract_info(directory_path)
print(dataframe)
dataframe.to_excel('tables-v3/symbolic-execution-run-time-evaluation.xlsx', index=False)

