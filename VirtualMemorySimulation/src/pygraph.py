from mpl_toolkits.mplot3d import Axes3D
import matplotlib.pyplot as plt
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
    
    fig = plt.figure()
    gs = gridspec.GridSpec(8,8)
    ax = fig.add_subplot(gs[0:7,0:6], projection='3d')
    ax.invert_yaxis()

    ax.scatter(x, y, z, c='r', marker='o')
    ax.set_xscale('linear')
    ax.set_yscale('linear')
    ax.set_zscale('linear')
    ax.set_xlabel('Page Table(log2(size))')
    ax.set_ylabel('TLB(log2(size))')
    ax.set_zlabel('EAT (ns)')

    bx = fig.add_subplot(gs[0,7])
    bx.scatter(lin_x[0], lin_y[0])
    bx.set_xlabel("TLB")
    bx.set_ylabel('EAT (ns)')

    bx = fig.add_subplot(gs[1,7])
    bx.scatter(lin_x[1], lin_y[1])
    bx.set_xlabel("TLB")
    bx.set_ylabel('EAT (ns)')

    bx = fig.add_subplot(gs[2,7])
    bx.scatter(lin_x[2], lin_y[2])
    bx.set_xlabel("TLB")
    bx.set_ylabel('EAT (ns)')

    bx = fig.add_subplot(gs[3,7])
    bx.scatter(lin_x[3], lin_y[3])
    bx.set_xlabel("TLB")
    bx.set_ylabel('EAT (ns)')

    bx = fig.add_subplot(gs[4,7])
    bx.scatter(lin_x[4], lin_y[4])
    bx.set_xlabel("TLB")
    bx.set_ylabel('EAT (ns)')

    bx = fig.add_subplot(gs[5,7])
    bx.scatter(lin_x[5], lin_y[5])
    bx.set_xlabel("TLB")
    bx.set_ylabel('EAT (ns)')

    bx = fig.add_subplot(gs[6,7])
    bx.scatter(lin_x[6], lin_y[6])
    bx.set_xlabel("TLB")
    bx.set_ylabel('EAT (ns)')

    bx = fig.add_subplot(gs[7,7])
    bx.scatter(lin_x[7], lin_y[7])
    bx.set_xlabel("TLB")
    bx.set_ylabel('EAT (ns)')

    fig.subplots_adjust(hspace=1.5)
    #fig.subplots_adjust(left=None, bottom=None, right=None, top=None, wspace=None, hspace=None)
    plt.show()
