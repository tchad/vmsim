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
from random import randrange
from random import choice
import codecs
import random
import sys
import time


refs = []
store = ""
store_max = 65536

if __name__ == "__main__":
    store = sys.argv[1]
    timeseed = int(time.time())
    random.seed(timeseed)  # Seed Random
    
#   We'll Generate the test case here: The pattern will mimic a locality scope 
    
    i = 0
    while(i < 30):  # Number of test cases
        base = int(randrange(0, 32768))
        refnum = 0
        if(randrange(0, 2) == 1):
           refnum = int(randrange(0, 32768))
        else:
           refnum = int(randrange(0, 256))
        if(base + refnum >= store_max):
            print("Address out of bound")
            sys.exit()
        j = randrange(2, 3)
        while (j > 0):
            refs.append((base, refnum))
            j -= 1
        j = randrange(0, 2)
        choice_obj = choice(refs)
        while (j > 0):
            refs.append(choice_obj)
            print choice_obj
            j -= 1
        i += 1

    f = open(store, "rb")
    fmap = open("map.txt", "w")
    faddr = open("addresses.txt", "w")
    fcorrect = open("correct.txt", "w")

    
    fmap.write("(base, number fo reads from base)\n")

    for elem in refs:
        fmap.write(str(elem) + "\n")
        base = elem[0];
        accessnum = elem[1]

        i = 0
        while(i <= accessnum):
            addr = randrange(base, base + accessnum)
            faddr.write(str(addr) + "\n")
            f.seek(addr);
            byte = f.read(1)
#             This gentestdata2 int.from_bytes method is not available in the Python 2.7.12, So use the workaround 
#             val = int.from_bytes(byte, byteorder="big", signed=True)
            val = int(codecs.encode(byte, 'hex'), 16)
            if(val > 128):  # The val produced is unsigned, change it to signed 
                val = (256 - val) * -1
            outstr = "Virtual address: " + str(addr) + " Physical address: 0 Value: " + str(val) + "\n"
            fcorrect.write(outstr)
            i+=1

    
    f.close()
    fmap.close()
    faddr.close()
    fcorrect.close()


        



