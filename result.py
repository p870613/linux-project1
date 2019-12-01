"""You need to change the path of file, and notice ln29"""
f1 = open(r'C:/Users/ducky/Desktop/Test/result/result_1.txt')
f2 = open(r'C:/Users/ducky/Desktop/Test/result/result_2.txt')
f3 = open(r'C:/Users/ducky/Desktop/Test/result/result_3.txt')
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
handle = ArrayHandle()
for line in range(len(result_1) - 4):
    if result_1[line][3] != '0x00000000':
        target = result_1[line][3]
        Ans2 = handle.search(result_2,target)
        Ans3 = handle.search(result_3,target)
        if Ans2 != 0:
            print("\tresult_1\n","VMA:",result_1[line][0],
            "Vir_start",result_1[line][1],
            "vir_end",result_1[line][2],
            "phy_start",result_1[line][3],
            "phy_end",result_1[line][4])
            print("\tresult_2\n","VMA:",result_2[Ans2][0],
            "Vir_start",result_2[Ans2][1],
            "vir_end",result_2[Ans2][2],
            "phy_start",result_2[Ans2][3],
            "phy_end",result_2[Ans2][4])
        if Ans3 != 0:
            print("\tresult_1\n","VMA:",result_1[line][0],
            "Vir_start",result_1[line][1],
            "vir_end",result_1[line][2],
            "phy_start",result_1[line][3],
            "phy_end",result_1[line][4])
            print("\tresult_3\n","VMA:",result_3[Ans3][0],
            "Vir_start",result_3[Ans3][1],
            "vir_end",result_3[Ans3][2],
            "phy_start",result_3[Ans3][3],
            "phy_end",result_3[Ans3][4])
"""
empty ratio
"""
print("result_1 empty ratio:", int(result_1[len(result_1)-1][0]) / int(result_1[len(result_1)-2][0]))
print("result_2 empty ratio:", int(result_2[len(result_2)-1][0]) / int(result_2[len(result_2)-2][0]))
print("result_3 empty ratio:", int(result_3[len(result_3)-1][0]) / int(result_3[len(result_3)-2][0]))

"""
sample result_1.txt

1	0x7fff6b25e000	0x7fff6b25f000	0x00000000	0x00001000
1	0x7fff6b25f000	0x7fff6b260000	0x00000000	0x00001000
2	0x7fff6b260000	0x7fff6b261000	0x00000000	0x00001000
2	0x7fff6b261000	0x7fff6b262000	0xe2345000	0xe2346000
3	0x7fff6b262000	0x7fff6b263000	0x00000000	0x00001000
3	0x7fff6b263000	0x7fff6b264000	0xe2346000	0xe2347000
4	0x7fff6b264000	0x7fff6b265000	0x00000000	0x00001000
4	0x7fff6b265000	0x7fff6b266000	0x00000000	0x00001000

#end
33212
16212
"""
"""
sample output
        result_1
 VMA: 2 Vir_start 0x7fff6b261000 vir_end 0x7fff6b262000 phy_start 0xe2345000 phy_end 0xe2346000

        result_2
 VMA: 2 Vir_start 0x7fff6b261000 vir_end 0x7fff6b262000 phy_start 0xe2345000 phy_end 0xe2346000

        result_1
 VMA: 2 Vir_start 0x7fff6b261000 vir_end 0x7fff6b262000 phy_start 0xe2345000 phy_end 0xe2346000

        result_3
 VMA: 2 Vir_start 0x7fff6b271000 vir_end 0x7fff6b272000 phy_start 0xe2345000 phy_end 0xe2346000

        result_1
 VMA: 3 Vir_start 0x7fff6b263000 vir_end 0x7fff6b264000 phy_start 0xe2346000 phy_end 0xe2347000

        result_2
 VMA: 3 Vir_start 0x7fff6b263000 vir_end 0x7fff6b264000 phy_start 0xe2346000 phy_end 0xe2347000

        result_1
 VMA: 3 Vir_start 0x7fff6b263000 vir_end 0x7fff6b264000 phy_start 0xe2346000 phy_end 0xe2347000

        result_3
 VMA: 3 Vir_start 0x7fff6b273000 vir_end 0x7fff6b274000 phy_start 0xe2346000 phy_end 0xe2347000

result_1 empty ratio: 0.488136818017584
result_2 empty ratio: 0.488136818017584
result_3 empty ratio: 0.488136818017584
"""
