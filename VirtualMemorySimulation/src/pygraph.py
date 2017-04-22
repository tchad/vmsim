from mpl_toolkits.mplot3d import Axes3D
import matplotlib.pyplot as plt
import matplotlib
import sys
import math
from matplotlib import gridspec

filename = sys.argv[1]



with open(filename, 'r') as f:
    str_data = f.read();
    data = str_data.split("\n");

    x=[]
    y=[]
    z=[]
    lin_x = [[],[],[],[],[],[],[],[]]
    lin_y = [[],[],[],[],[],[],[],[]]
    print (lin_x)


    for str_row in data:
        if str_row:
            row = str_row.split(" ")
            val_x = math.log2(int(row[1]))
            val_y = math.log2(int(row[0]))
            val_z = float(row[8])

            x.append(val_x)
            y.append(val_y)
            z.append(val_z)

            lin_x[int(val_x)-1].append(val_y)
            lin_y[int(val_x)-1].append(val_z)
    
    fig = plt.figure(1)
    ax = fig.add_subplot(111, projection='3d')
    ax.invert_yaxis()

    ax.scatter(x, y, z, c='r', marker='o')
    ax.set_xscale('linear')
    ax.set_yscale('linear')
    ax.set_zscale('linear')
    ax.set_xlabel('Page Table(log2(size))')
    ax.set_ylabel('TLB(log2(size))')
    ax.set_zlabel('EAT (ns)')

    fig = plt.figure(2)

    for i in range(0,8):
        bx = fig.add_subplot(241+i)
        bx.scatter(lin_x[i], lin_y[i])
        bx.set_xlabel("TLB")
        bx.set_ylabel('EAT (ns)')
        plt.xticks(range(0,10))
        #bx.yaxis.set_major_formatter(matplotlib.ticker.ScalarFormatter(useOffset=True))
        #bx.ticklabel_format(useOffset=True)
        bx.get_yaxis().get_major_formatter().set_useOffset(True)

    plt.show()

'''
    bx = fig.add_subplot(242)
    bx.scatter(lin_x[1], lin_y[1])
    bx.set_xlabel("TLB")
    bx.set_ylabel('EAT (ns)')
    plt.xticks(range(0,10))
    bx.yaxis.set_major_formatter(matplotlib.ticker.ScalarFormatter(useOffset=True))

    bx = fig.add_subplot(243)
    bx.scatter(lin_x[2], lin_y[2])
    bx.set_xlabel("TLB")
    bx.set_ylabel('EAT (ns)')
    plt.xticks(range(0,10))

    bx = fig.add_subplot(244)
    bx.scatter(lin_x[3], lin_y[3])
    bx.set_xlabel("TLB")
    bx.set_ylabel('EAT (ns)')
    plt.xticks(range(0,10))

    bx = fig.add_subplot(245)
    bx.scatter(lin_x[4], lin_y[4])
    bx.set_xlabel("TLB")
    bx.set_ylabel('EAT (ns)')
    plt.xticks(range(0,10))

    bx = fig.add_subplot(246)
    bx.scatter(lin_x[5], lin_y[5])
    bx.set_xlabel("TLB")
    bx.set_ylabel('EAT (ns)')
    plt.xticks(range(0,10))

    bx = fig.add_subplot(247)
    bx.scatter(lin_x[6], lin_y[6])
    bx.set_xlabel("TLB")
    bx.set_ylabel('EAT (ns)')
    plt.xticks(range(0,10))

    bx = fig.add_subplot(248)
    bx.scatter(lin_x[7], lin_y[7])
    bx.set_xlabel("TLB")
    bx.set_ylabel('EAT (ns)')
    plt.xticks(range(0,10))
'''

