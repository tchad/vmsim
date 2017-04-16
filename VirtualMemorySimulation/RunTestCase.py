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
                tempstring = (subprocess.check_output([executables, addressfile, '-s', '-t %s' % k, '-p %s' % j], shell=False))
                fres.write(tempstring)
                k = k * 2
            j = j * 2
        
        i += 1
    fres.close()
    
