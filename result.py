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
struct
    vma | page_start | page_end | phy_start | phy_end
"""
class ArrayHandle:
    def search(self,array,target):
        for index_x in range(len(array)):
            if target in array[index_x]:
                return index_x
        return 0

"""
compare result_1 to result_2,3
"""
count_1 = 0
count_2 = 0
count_3 = 0

handle = ArrayHandle()
for line in range(len(result_1) - 4):
    line_change = line + 1
    if result_1[line_change][3] != '0x000000000':
        target = result_1[line_change][3]
        Ans2 = handle.search(result_2,target)
        Ans3 = handle.search(result_3,target)
        if Ans2 != 0:
            print("phy_start",result_1[line_change][3],
            "phy_end",result_1[line_change][4])
            print("result_1\n","VMA:",result_1[line_change][0],
            "Vir_start",result_1[line_change][1],
            "vir_end",result_1[line_change][2])
            print("result_2\n","VMA:",result_2[Ans2][0],
            "Vir_start",result_2[Ans2][1],
            "vir_end",result_2[Ans2][2])
            count_2 = count_2 + 1

            if Ans3 != 0:
                print("result_3\n","VMA:",result_3[Ans3][0],
                "Vir_start",result_3[Ans3][1],
                "vir_end",result_3[Ans3][2])
                count_3 = count_3 + 1
            print("----------------------")
            count_1 = count_1 + 1
        else:
            if Ans3 != 0:
                print("phy_start",result_1[line_change][3],
                "phy_end",result_1[line_change][4])
                print("result_1\n","VMA:",result_1[line_change][0],
                "Vir_start",result_1[line_change][1],
                "vir_end",result_1[line_change][2])
                print("result_3\n","VMA:",result_3[Ans3][0],
                "Vir_start",result_3[Ans3][1],
                "vir_end",result_3[Ans3][2])
                count_3 = count_3 + 1
                count_1 = count_1 + 1
                print("----------------------")
"""
VMA range
"""
range = 1
while range < len(result_1) - 4:
    hold = result_1[range][0]
    range_before = range
    range = range + 1
    while (result_1[range][0] == hold) and (range <= len(result_1) - 4):
        range = range + 1
    print("result_1 VMA ",hold,"\n"
    "range begin: ",result_1[range_before][1],
    "\tend: ",result_1[range - 1][2])
range = 1
while range < len(result_2) - 4:
    hold = result_2[range][0]
    range_before = range
    range = range + 1
    while (result_2[range][0] == hold) and (range <= len(result_2) - 4):
        range = range + 1
    print("result_2 VMA ",hold,"\n"
    "range begin: ",result_2[range_before][1],
    "\tend: ",result_2[range - 1][2])
range = 1
while range < len(result_3) - 4:
    hold = result_3[range][0]
    range_before = range
    range = range + 1
    while (result_3[range][0] == hold) and (range <= len(result_1) - 4):
        range = range + 1
    print("result_3 VMA ",hold,"\n"
    "range begin: ",result_3[range_before][1],
    "\tend: ",result_3[range - 1][2])

"""
empty ratio
"""
print("result_1 empty ratio:", int(result_1[len(result_1)-2][0]) / int(result_1[len(result_1)-1][0]))
print("\t the same ratio:", count_1 / int(result_1[len(result_1)-1][0]))
print("result_2 empty ratio:", int(result_2[len(result_2)-2][0]) / int(result_2[len(result_2)-1][0]))
print("\t the same ratio:", count_2 / int(result_2[len(result_2)-1][0]))
print("result_3 empty ratio:", int(result_3[len(result_3)-2][0]) / int(result_3[len(result_3)-1][0]))
print("\t the same ratio:", count_3 / int(result_3[len(result_3)-1][0]))
