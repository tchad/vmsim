#!/usr/bin/env python
import subprocess
import sys

refs = []

if __name__ == "__main__":
    executables = sys.argv[1]  # Location of executable
    fres = open("endresult.txt", "w")
    i = 0;
    while (i < 3):
#         print "Data %s" % (i)
        fres.write("Data %s\n" % (i))
        addressfile = "src/misc/data%s%s" % (i, "/addresses.txt")
        j = 2
        while (j <= 256):
            k = 2
            while(k <= j):
#                 print "Page Table Size = %s\nTLB Size = %s" % (j, k)
                tempstring = (subprocess.check_output([executables, addressfile, "-t %s -p %s" % (k, j)], shell=False))
                tempstring = tempstring[tempstring.find("TLB Hit"):]
                eat = (tempstring[tempstring.find("Effective Access Time: "):]).split()[3]
#                 print str(j) + " " + str(k) + " " + eat[:-2]
                fres.write(str(j) + " " + str(k) + " " + eat[:-2] + "\n")
#                 print tempstring
                k = k * 2
            j = j * 2
        
        i += 1
    fres.close()
    
