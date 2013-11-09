import sys, os#, #easygui
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

for (path, dirs, files) in os.walk("E:/TDML/TDML"):
    for f in files:
        if not f in exceptions:
            if ".cpp" in f or ".h" in f:
                print f
                totlength+=simplecount("E:/TDML/TDML/"+f)

for (path, dirs, files) in os.walk("E:/TDML/Tools"):
    for f in files:
        if not f in exceptions:
            if ".py" in f:
                print f
                totlength+=simplecount("E:/TDML/Tools/"+f)

for (path, dirs, files) in os.walk("E:/TDML/TDML/Shaders"):
    for f in files:
        if not f in exceptions:
            if ".frag" in f or ".vert" in f:
                print f
                totlength+=simplecount("E:/TDML/Tools/"+f)
                

print "Total lines of code: "+str(totlength)
raw_input()
#easygui.msgbox("Total lines of code: "+str(totlength), "Count.py")
