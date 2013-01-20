import sys, os
totlength = 0
numfiles = 0
exceptions = ["glew.c", "glew.h", "glxew.h", "LodePNG.cpp", "LodePNG.h", "wglew.h"]

def simplecount(filename):
	try:
		lines = 0
		for line in open(filename):
			lines += 1
		return lines
	except:
		return 0

for (path, dirs, files) in os.walk("C:/Users/Andrew/Desktop/NCC/OpenGL/3D Model Loader/3D Model Loader/TDML"):
    for f in files:
        if not f in exceptions:
            if ".cpp" in f or ".h" in f:
                print f
                totlength+=simplecount("C:/Users/Andrew/Desktop/NCC/OpenGL/3D Model Loader/3D Model Loader/TDML/"+f)

print "Total lines of code: "+str(totlength)