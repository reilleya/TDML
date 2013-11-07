import os

bigstr = ""

for x, y, z in os.walk("TDML"):
    print x
    print y
    print z
    print "loopi"
    for zz in z:
        print zz
        try:
            f = open("TDML/"+zz, "r")
            bigstr+=f.read()+"\n"
            f.close()
        except:
            pass
        
ff = open("bigtext.txt", "w")

ff.write(bigstr)

ff.close()
