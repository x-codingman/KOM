import os
import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns
import json

def count_json_files_in_folder(folder_path):
    """统计指定文件夹中JSON文件的数量"""
    for f in os.listdir(folder_path):
        if f.endswith('.json'):
            path = os.path.join(folder_path, f)
            check_value_controllable(path)
    return len([f for f in os.listdir(folder_path) if f.endswith('.json')])

def check_value_controllable(json_file):
    """
    Check if the given JSON file contains any entries with the key 'value_controllable' set to true.
    
    Parameters:
    json_file (str): Path to the JSON file.
    """
    try:
        with open(json_file, 'r') as file:
            data = json.load(file)

        # Recursive function to search for the key in a nested dictionary
        def search_key(d):
            if isinstance(d, dict):
                if d.get('value_controllable') == True:
                    print(json_file)
                for v in d.values():
                    search_key(v)
            elif isinstance(d, list):
                for item in d:
                    search_key(item)

        search_key(data)

    except json.JSONDecodeError:
        print("Error: The file is not a valid JSON file.")
    except FileNotFoundError:
        print(f"Error: The file {json_file} was not found.")

def generate_folders_report(base_path):
    """生成包含文件夹名称和JSON文件数量的表格"""
    folders_report = []

    # 遍历基础路径下的所有子文件夹
    for folder_name in os.listdir(base_path):
        folder_path = os.path.join(base_path, folder_name)
        if os.path.isdir(folder_path):
            json_count = count_json_files_in_folder(folder_path)
            type_name = folder_name.split("_")[0].upper()
            folders_report.append([folder_name,type_name, json_count])

    

    # 创建DataFrame并返回
    return pd.DataFrame(folders_report, columns=['API Name', "Type", 'Privileged Pointers Dereference'])

def plot_histogram(df):
    """根据Type绘制直方图"""
    # plt.figure(figsize=(10, 6))
    # sns.boxplot(x='Type', y='Privileged Pointers Dereference', hue='Type', data=df)
    # plt.title('Privileged Pointers Dereference by API Type')
    # plt.xlabel('Type')
    # plt.ylabel('Privileged Pointers Dereference Count')
    # #plt.legend(title='Type')
    # output_image_filename = 'dereference_pointer_boxplot.png'
    # plt.savefig(output_image_filename)

    # 根据每个type画
    # df_sorted = df.sort_values(by='Type')

    # # 绘制直方图
    # plt.figure(figsize=(12, 3))
    # bar_plot=sns.barplot(x='API Name', y='Privileged Pointers Dereference', hue='Type', data=df_sorted)
    # # 调整直方图的宽度
    # for patch in bar_plot.patches:
    #     current_width = patch.get_width()
    #     new_width = current_width * 2  # 修改这个比例来调整宽度
    #     patch.set_width(new_width)
    #     patch.set_x(patch.get_x() + current_width - new_width / 2)
    # plt.title('Privileged Pointers Dereference by API Name')
    # plt.xlabel('API Name')
    # plt.xticks(rotation=30, ha='right',fontsize=6)
    # plt.ylabel('Privileged Pointers Dereference Count')
    # plt.yscale('log')
    # plt.legend(title='Type')
    # output_image_filename = 'dereference_pointer_histogram.png'
    # plt.savefig(output_image_filename)

    # 绘制直方图
    plt.figure(figsize=(8, 6))
    sns.histplot(df['Privileged Pointers Dereference'], bins=20, kde=False, color='blue')

    #plt.title('Distribution of Privileged Pointers Dereference')
    plt.xlabel('Number of Privileged Pointers Dereference',fontsize=12,fontweight='bold')
    plt.ylabel('Number of System Calls',fontsize=12,fontweight='bold')
    plt.yticks([0, 5, 10, 20, 50], ['0', '5', '10', '20', '50'])
    #plt.xticks([0, 100, 200, 300, 400,500,600,700,800,1000], ['0', '100', '200', '300', '400','500','600','700','800','900','1000'])
    output_image_filename = 'dereference_pointer_histogram.png'
    plt.savefig(output_image_filename)

base_path = '/home/klee/threadx/symbolic_execution/output'  # 替换为你的基础路径
# 生成报告并保存为Excel文件
report_df = generate_folders_report(base_path)
report_df.to_excel('dereference_pointer_report.xlsx', index=False)

# 绘制直方图
plot_histogram(report_df)
