#!/usr/bin/env python

'''
Usage:
    NOTE: DO NOT EXECUTE IN FOLDER THAT ALREADY CONTAIN address.txt and correct.txt 
    they will get overwritten!!!!!!!!!!!!!!!!!!!!!!

    To execute give the path to backing store and then follow by set of tuples of
    base_page_number,number_of_iterations_from_that_point

    The resulting address.txt and correct.txt will get generated. The correct.txt will not have proper
    frame data as it is useless for different sizes of page table.

    The map.txt will contain the given set as parameter for book keeping

    Example:
    ./gentestdata.py ../../Debug/BACKING_STORE.bin 30198,2 18295,3 11,5
'''
import sys

refs = []
store = ""
store_max = 65536

if __name__ == "__main__":
    store = sys.argv[1]
    for i in range(2,len(sys.argv)):
        lst = sys.argv[i].split(",")
        base = int(lst[0])
        refnum = int(lst[1])
        refs.append((base, refnum))

        if(base+refnum >= store_max):
            print("Address out of bound")
            sys.exit()

    f = open(store, "rb")
    fmap = open("map.txt", "w")
    faddr = open("addresses.txt", "w")
    fcorrect = open("correct.txt", "w")

    
    fmap.write("(base, number fo reads from base)\n")

    for elem in refs:
        fmap.write(str(elem) + "\n")
        base = elem[0];
        accessnum = elem[1]

        f.seek(base);
        for addr in range(base, base+accessnum):
            faddr.write(str(addr)+"\n")
            byte = f.read(1)
            val = int.from_bytes(byte, byteorder="big", signed=True)
            outstr = "Virtual address: " + str(addr) + " Physical address: 0 Value: " + str(val) +"\n"
            fcorrect.write(outstr)

    
    f.close()
    fmap.close()
    faddr.close()
    fcorrect.close()


        



