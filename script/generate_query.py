import random

def generate_range_file(filename, n):
    with open(filename, 'w') as file:
        # 写入文件头部
        file.write(f"{n}\n")
        for _ in range(n):
            # 生成范围内的随机整数，保证第一个数小于或等于第二个数
            lower_bound = random.randint(1, 10**6)
            upper_bound = random.randint(lower_bound, 10**6 + lower_bound)
            # 将数据写入文件
            file.write(f"{lower_bound} {upper_bound}\n")

# 定义文件名和行数
filename = "range_data.txt"
n = 5  # 可以修改为所需行数

generate_range_file(filename, n)
