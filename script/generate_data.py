import random

def generate_data_file(filename, n, d):
    with open(filename, 'w') as file:
        # 写入文件头部
        file.write(f"{n} {d}\n")
        for _ in range(n):
            # 生成d维度的随机整数，每个整数在1到10^9范围内
            data = [str(random.randint(1, 10**9)) for _ in range(d)]
            # 将数据写入文件
            file.write(" ".join(data) + "\n")

# 定义文件名和行数及维度数
filename = "data.txt"
n = 5  # 可以修改为所需行数
d = 6  # 可以修改为所需维度数

generate_data_file(filename, n, d)
