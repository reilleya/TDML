import os

print "~"*50
print "Pak Packer"
print "For use with Eggplant Animation's TDML"
print "Created by Andrew Reilley"
print "~"*50

print
dir = raw_input("Please specify a directory of resources to be packed: ")
print
print "Packing Directory: '"+dir+"'"
print "\tReading Directory Tree..."
direc = os.walk(dir)
for name, subs, files in direc:
    print "\t"+str(name)
    for sub in subs:
        print "\t\t"+sub
    #print "\t\t"+str(subs)
    #print "\t\t\t"+str(files)
#print path
#print dirs
#print files
print "\tRead Directory Tree."
print "Packed Directory."