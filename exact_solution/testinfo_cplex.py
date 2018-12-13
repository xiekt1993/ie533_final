import numpy as np
time = 100

f= open("experiment/test_csr.data","r")
line = f.readlines()

f2 = f= open("experiment/test_info.data","r")
line2 = f2.readlines()

# write nodes number
result = []
line_1 = ['N = ' + line[0][:-1] + ';\n']
result += line_1

# write t
line_2 = 'T={'
line_3 = 'T2={'
for i in range(time + 1):
    line_2 += '"' + str(i) + '",'
line_3 += line_2[3:-5]
line_2 = line_2[:-1] + '};\n'
line_3 += '};\n'
result += [line_2]
result += [line_3]

# write node set
line_4 = 'Node={'
for i in range(int(line[0][:-1])):
    line_4 += '"' + str(i+1) + '",'
line_4 += '};\n'
result += [line_4]

# write link set
row_ptr = np.array(line[2][:-2].split(' '))
col_inx = np.array(line[4][:-2].split(' '))
line_5 = 'Link=['
for i in range(int(line[0][:-1])):
    rowzeros = np.zeros(int(line[0][:-1]))
    for j in range(int(row_ptr[i]), int(row_ptr[i+1])):
        rowzeros[int(col_inx[j])] = 1
    line_5 += '['
    for k in range(int(line[0][:-1])):
        line_5 += str(int(rowzeros[k]))+','
    line_5 = line_5[:-1] +'],'
        #line_5 += '[' + str(i+1) + ',' + str(int(col_inx[j])+1) + '],'
line_5 = line_5[:-1] + '];\n'
result += [line_5]

# write beta
beta = np.array(line[1][:-2].split(' '))
line_6 = 'Beta=['
for i in range(int(line[0][:-1])):
    line_6 += beta[i] + ','
line_6 = line_6[:-1] + '];\n'
result += [line_6]

# write w
line_7 = 'w=['
influence = np.array(line[3][:-2].split(' '))
count = 0
for i in range(int(line[0][:-1])):
    rowzeros = np.zeros(int(line[0][:-1]))
    for j in range(int(row_ptr[i]), int(row_ptr[i+1])):
        rowzeros[int(col_inx[j])] = influence[count]
        count +=1
    line_7 += '['
    for k in range(int(line[0][:-1])):
        line_7 += str(rowzeros[k])+','
    line_7 = line_7[:-1] +'],'
        #line_5 += '[' + str(i+1) + ',' + str(int(col_inx[j])+1) + '],'
line_7 = line_7[:-1] + '];\n'
result += [line_7]

# write NS
NS = np.array(line2[0][:-2].split(' '))
if NS[np.where(NS=='2')].shape[0]==0:
    line_8 = 'NS={};\n'
else:
    line_8 = 'NS={'
    for i in np.where(NS=='2')[0]:
        line_8 += '"' + str(int(i)+1) + '",'
    line_8 = line_8[:-1] + '};\n'
result += [line_8]

# write m

# write p_plus and minus
line_9 = 'p_plus =' + line2[2][:-1] +';\n'
line_10 = 'p_minus =' + line2[3][:-1] +';\n'
result += [line_9]
result += [line_10]

with open("test.dat", "w") as output:
    for i in range(len(result)):
        output.write(str(result[i]))
