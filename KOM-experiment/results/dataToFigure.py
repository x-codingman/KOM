import pandas as pd
import matplotlib.pyplot as plt

# 读取Excel文件
filename = 'output.xlsx'  # 替换为你的文件名
df = pd.read_excel(filename, index_col=0, engine='openpyxl')

# 初始化一个空的字典来存储结果
result = {}
num=0
# 遍历每一行来计算“ok”的数量
for function in df.index:
    count_ok = df.loc[function].value_counts().get('ok', 0)
    result[function] = count_ok-1
    if count_ok >=10:
        num=num+1



# 转换数据为图表所需格式
functions = list(result.keys())
counts = list(result.values())

# 创建直方图
plt.figure(figsize=(12, 3))
plt.bar(functions, counts, width=0.6,color='grey' )

# 设置X轴标签为斜着放置
plt.xticks(rotation=30, ha='right',fontsize=8)

# 添加标题和轴标签

#plt.xlabel('System call APIs',weight='bold')
plt.ylabel('Number of combinations\nthat can be exploited')

# 显示图表
plt.tight_layout()

output_image_filename = 'counts_of_exploitable_apis.png'
plt.tight_layout()
plt.savefig(output_image_filename)
print(num)


