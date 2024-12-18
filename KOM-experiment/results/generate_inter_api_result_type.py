import pandas as pd
from collections import defaultdict
import matplotlib.pyplot as plt
import seaborn as sns
def find_and_count_ok_functions(file_path):
    # 读取Excel文件
    df = pd.read_excel(file_path, header=None,engine='openpyxl')

    # 获取函数类型
    row_functions = df.iloc[0, 1:].apply(lambda x: x.split('_')[0])
    col_functions = df.iloc[1:, 0].apply(lambda x: x.split('_')[0])

    # 创建字典来存储统计信息
    ok_count = defaultdict(int)

    # 查找包含“ok”的单元格并更新统计信息
    for row in range(1, df.shape[0]):
        for col in range(1, df.shape[1]):
            if row == col:
                continue
            if df.iloc[row, col] == "ok":
                row_type = row_functions[col]
                col_type = col_functions[row]
                pair = (row_type, col_type)
                ok_count[pair] += 1

    return ok_count

# 使用例子



# 将数据转换为适合制图的格式
def prepare_data_for_plot(data):
    rows = []
    for (type1, type2), count in data.items():
        rows.append([type1, type2, count])
    return pd.DataFrame(rows, columns=['Type of malicious kernel object', 'Type forged kenrel object', 'Count'])



file_path = 'output.xlsx'  # 替换为您的文件路径
ok_count = find_and_count_ok_functions(file_path)
for pair, count in ok_count.items():
    print(f"{pair}: {count}")
# 准备数据


df = prepare_data_for_plot(ok_count)

# 创建一个热力图
plt.figure(figsize=(10, 8))
pivot_table = df.pivot("Type of malicious kernel object", "Type forged kenrel object", "Count")
ax = sns.heatmap(pivot_table, annot=True, fmt="d", cmap="YlGnBu",annot_kws={"size": 12})
ax.set_xticklabels(ax.get_xticklabels(), fontsize=12)
ax.set_yticklabels(ax.get_yticklabels(), fontsize=12)
plt.xlabel("Type forged kenrel object", fontsize=12,fontweight='bold')  # 增加 x 轴标签的字体大小
plt.ylabel("Type of malicious kernel object", fontsize=12,fontweight='bold')  # 增加 y 轴标签的字体大小
plt.title("",fontsize=12,fontweight='bold')
output_image_filename = 'system_call_counts_to_construct_different_type_of_forged_kernel_object.png'
plt.savefig(output_image_filename)