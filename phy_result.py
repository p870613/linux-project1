import os

f1 = open(r'%s/result_1.txt' %os.getcwd())
f2 = open(r'%s/result_2.txt' %os.getcwd())
f3 = open(r'%s/result_3.txt' %os.getcwd())
result_1 = []
result_2 = []
result_3 = []
for line in f1:
    result_1.append(line.split('\t'))
for line in f2:
    result_2.append(line.split('\t'))
for line in f3:
    result_3.append(line.split('\t'))

"""
non-zero phy
"""
f_w1 = open("result_1_phy.txt","w")
f_w1.write("PAGE_TABLE\n")
for line in range(len(result_1) - 4):
    new_line = line + 1
    if result_1[new_line][3] != "0x000000000" :
        lines = [result_1[new_line][0],"\t",
        result_1[new_line][1],"\t",
        result_1[new_line][2],"\t",
        result_1[new_line][3],"\t",
        result_1[new_line][4]]
        write_string = ''.join(lines)
        f_w1.write(write_string)

f_w2 = open("result_2_phy.txt","w")
f_w2.write("PAGE_TABLE\n")
for line in range(len(result_2) - 4):
    new_line = line + 1
    if result_2[new_line][3] != "0x000000000" :
        lines = [result_1[new_line][0],"\t",
        result_2[new_line][1],"\t",
        result_2[new_line][2],"\t",
        result_2[new_line][3],"\t",
        result_2[new_line][4]]
        write_string = ''.join(lines)
        f_w2.write(write_string)

f_w3 = open("result_3_phy.txt","w")
f_w3.write("PAGE_TABLE\n")
for line in range(len(result_3) - 4):
    new_line = line + 1
    if result_3[new_line][3] != "0x000000000" :
        lines = [result_3[new_line][0],"\t",
        result_3[new_line][1],"\t",
        result_3[new_line][2],"\t",
        result_3[new_line][3],"\t",
        result_3[new_line][4]]
        write_string = ''.join(lines)
        f_w3.write(write_string)
