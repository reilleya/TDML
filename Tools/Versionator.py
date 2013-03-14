print "Running Versionator..."
print "\tIncrementing version number..."
fileconts=[]
modfile = open("C:/Users/Andrew/Desktop/NCC/OpenGL/3D Model Loader/3D Model Loader/TDML/version.cpp", "r")
for line in modfile:
    if "build =" in line:
        oldbuild = str(line[-7:-3])
        intver = int(line[-7:-3])
        intver+=1
        strver = str(intver)
        if len(strver) == 1:
            newbuild = "000"+strver
        elif len(strver) == 2:
            newbuild = "00"+strver
        elif len(strver) == 3:
            newbuild = "0"+strver
        else:
            newbuild = strver
        line = line.replace(oldbuild, newbuild)
        print "Build Number: "+newbuild
    fileconts.append(line)
modfile.close()
writefile = open("C:/Users/Andrew/Desktop/NCC/OpenGL/3D Model Loader/3D Model Loader/TDML/version.cpp", "w")
for liner in fileconts:
	writefile.write(liner)
writefile.close()
print "Done!"