import numpy as np
import os
from scipy import sparse
import networkx as nx
import shutil
import time

def trans(csr_filename, info_filename, output, find_PS=False, eignodes = False, k =5):
    f= open(csr_filename,"r")
    line = f.readlines()

    f2 = f= open(info_filename,"r")
    line2 = f2.readlines()

    # write nodes number
    result = []
    N = int(line[0][:-1])
    line_1 = 'set N := '
    for i in range(N):
        line_1 += str(i) +' '
    line_1 = line_1[:-1] + ';\n'
    result += line_1
    
    # write T
    time1 = int(line2[1][:-1])
    line_2 = 'set T:='
    line_3 = 'set T_pos:='
    for i in range(time1):
        line_2 += str(i) +' '
    line_3 += line_2[9:-1]
    line_2 = line_2[:-1] + ';\n'
    line_3 += ';\n'
    result += [line_2]
    result += [line_3]
    
    # write link set
    row_ptr = np.array(line[2][:-2].split(' '))
    col_inx = np.array(line[4][:-2].split(' '))
    line_5 = 'set A:='
    A_set = []
    for i in range(int(line[0][:-1])):
        for j in range(int(row_ptr[i]), int(row_ptr[i+1])):
            line_5 += '(' + str(i) + ',' + str(int(col_inx[j])) + ') '
            A_set += [str(i) + ',' + str(int(col_inx[j]))]
    line_5 = line_5[:-1] + ';\n'
    result += [line_5]
    
    # write NS
    NS = (np.array(line2[0][:-2].split(' ')).astype(int)/2).astype(int)
    line_8 = 'param: NS:=\n'
    for i in range(len(NS)):
        line_8 += str(i)+' ' + str(NS[i]) + '\n'
    line_8 = line_8[:-1] + ';\n'
    result += [line_8]
    
    # write beta
    beta = np.array(line[1][:-2].split(' '))
    line_6 = 'param: beta:=\n'
    for i in range(int(line[0][:-1])):
        line_6 += str(i)+' ' + beta[i] + '\n'
    line_6 = line_6[:-1] + ';\n'
    result += [line_6]
    
    # write w
    line_7 = 'param w:=\n'
    influence = np.array(line[3][:-2].split(' '))
    
    for i in range(len(influence)):
        line_7 += A_set[i] + ' ' + influence[i] + '\n'

    line_7 = line_7[:-1] + ';'
    result += [line_7]

    
    if find_PS == False:
        with open(output, "w") as output:
            for i in range(len(result)):
                output.write(str(result[i]))
    
    if find_PS == True:
        row_ptr = np.array(line[2][:-2].split(' ')).astype(int)
        col_inx = np.array(line[4][:-2].split(' ')).astype(int)
        data = np.ones(len(col_inx))
        N = int(line[0][:-1])
        
        mtx = sparse.csr_matrix((data, col_inx, row_ptr), shape=(N,N))
        mtx.todense()
        
        G = nx.from_scipy_sparse_matrix(mtx)
        start_time = time.time()
        eig_centrality = nx.eigenvector_centrality_numpy(G)
        print('eig_centrality:',output, time.time()-start_time)
        degree_centrality = nx.degree_centrality(G)
        
        eig_nodes = sorted(eig_centrality, key=eig_centrality.get, reverse=True)[:k+NS.sum()]
        eig_nodes = [i for i in eig_nodes if i not in list(np.where(NS == 1)[0])][:k]
        degree_nodes = sorted(degree_centrality, key=degree_centrality.get, reverse=True)[:k+NS.sum()]
        degree_nodes = [i for i in degree_nodes if i not in list(np.where(NS == 1)[0])][:k]
        
        line_9 = '\nparam: PS1:=\n'
        PS_vec = np.zeros(N)

        if eignodes == True:
            PS_vec[eig_nodes] = 1
            PS_vec = PS_vec.astype(int)
            for i in range(len(PS_vec)):
                line_9 += str(i)+' ' + str(PS_vec[i]) + '\n'
            line_9 = line_9[:-1] + ';\n'
            result += [line_9]
        else:
            PS_vec[degree_nodes] = 1
            PS_vec = PS_vec.astype(int)
            for i in range(len(PS_vec)):
                line_9 += str(i)+' ' + str(PS_vec[i]) + '\n'
            line_9 = line_9[:-1] + ';\n'
            result += [line_9]
        
        with open(output, "w") as output:
            for i in range(len(result)):
                output.write(str(result[i]))    

thisdir = os.getcwd()
csr_file = []
info_file= []
for r, d, f in os.walk(thisdir):
    for file in f:
        if "exp_csr_" in file:
            csr_file += [os.path.join(r, file)]

for r, d, f in os.walk(thisdir):
    for file in f:
        if "exp_info" in file:
            info_file += [os.path.join(r, file)]
            
if os.path.isdir('ampltest1'):
    shutil.rmtree('ampltest1')
if os.path.isdir('ampltest_eig1'):
    shutil.rmtree('ampltest_eig1')
if os.path.isdir('ampltest_degree1'):
    shutil.rmtree('ampltest_degree1')
    
os.mkdir('ampltest1')
os.mkdir('ampltest_eig1')
os.mkdir('ampltest_degree1')

for j in range(len(info_file)):
    trans(csr_file[j], info_file[j], 'ampltest1\\test_' + info_file[j][72:-5] +'.dat')
    trans(csr_file[j], info_file[j], 'ampltest_eig1\\test_' + info_file[j][72:-5] +'.dat',find_PS=True,eignodes=True, k =5)
    trans(csr_file[j], info_file[j], 'ampltest_degree1\\test_' + info_file[j][72:-5] +'.dat',find_PS=True,eignodes=False, k =5)