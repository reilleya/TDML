class point():
    def __init__(self, x, y, z):
        self.x = x
        self.y = y
        self.z = z

class normal():
    def __init__(self, x, y, z):
        self.x = x
        self.y = y
        self.z = z
        
class uvpoint():
    def __init__(self, u,v):
        self.u = u
        self.v = v

class face():
    def __init__(self):
        self.points = []
        self.uvcoords = []
        self.normals = []

text = []
verts = []
norms =[]
faces = []
coordinates = []
materialimg = ""

print "~"*50
print "OBJ to TDM converter"
print "For use with Eggplant Animation's TDML"
print "Created by Andrew Reilley"
print "~"*50
fileloc = raw_input("Type the name of the file you would like to convert >>> ")
print
print "Loading file from "+fileloc+"..."
f = open(fileloc, "r")
print "Loaded file!"
print "Parsing file..."
print "\tReading file..."
for line in f.read().split("\n"):
    print "\t\tReading line "+str(len(text))
    text.append(line.split(" "))
print "\tRead file!"
print "\tInterpreting data..."
for line in text:
    if line[0] == "usemtl":
        print "\t\tMaterial file at line: "+str(text.index(line))
        materialimg = line[1]
    if line[0] == "v":
        print "\t\tVertex at line: "+str(text.index(line))
        verts.append(point(line[1],line[2],line[3]))
    if line[0] == "vt":
        print "\t\tUV coordinate at line: "+str(text.index(line))
        coordinates.append(uvpoint(line[1],line[2]))
    if line[0] == "vn":
        print "\t\tNormal at line: "+str(text.index(line))
        norms.append(normal(line[1],line[2],line[3]))
    if line[0] == "f":
        print "\t\tFace at line: "+str(text.index(line))
        nf = face()
        print "\t\t\tReading vertices..."
        for p in range(1, len(line)):
            print "\t\t\t\tReading vertex: "+str(p)
            pid = int(line[p].split("/")[0])-1
            nf.points.append(verts[pid])
        print "\t\t\tRead vertices!"
        print "\t\t\tReading coordinates..."
        for p in range(1, len(line)):
            pid = int(line[p].split("/")[1])-1
            nf.uvcoords.append(coordinates[pid])
        print "\t\t\tRead coordinates!"
        print "\t\t\tReading normals..."
        for p in range(1, len(line)):
            pid = int(line[p].split("/")[2])-1
            nf.normals.append(norms[pid])
        print "\t\t\tRead vertices!"
        faces.append(nf)
print "\tData Interpreted!"
print "Parsed file!"
print "Closing file..."
f.close()
print "File closed!"
print "~"*50
#print "\a"
dest = raw_input("What would you like to save the result as?>>> ")
print
print "Opening data file..."
datafile = open(dest+".tdm", "w")
print "Opened data file!"
print "Opening material file..."
matfile = open(dest+".mdf", "w")
print "Material file opened!"
print "Writing data file..."
for face in faces:
    print "\tOpening face..."
    for i in range(0, len(face.points)):
        datafile.write(face.points[i].x+" "+face.points[i].y+" "+face.points[i].z+" "+face.normals[i].x +" " +face.normals[i].y +" "+face.normals[i].z +" ?\n")
    datafile.write("[\n")
    print "\tClosed face!"
print "Wrote data file!"
print "Writing material file..."
matfile.write(materialimg+" ?\n")
for face in faces:
    print "\tOpening face..."
    for poin in face.uvcoords:
        matfile.write(poin.u+" "+str(1-float(poin.v)) +" ?\n")
    matfile.write("[\n")
    print "\tClosed face!"
print "Wrote material file!"
print "Closing data file..."
datafile.close()
print "Closed data file!"
print "Closing material file..."
matfile.close()
print "Closed material file!"
print "~"*50
print "Done!"
