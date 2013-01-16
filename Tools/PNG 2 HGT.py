import pygame

pygame.init()

data = []
datastring=""

print "~"*50
print "PNG to HGT converter"
print "For use with Eggplant Animation's TDML"
print "Created by Andrew Reilley"
print "~"*50

fileloc = raw_input("Type the name of the file you would like to convert >>> ")
print

print "Loading file from "+fileloc+"..."
surf = pygame.image.load(fileloc)
print "Loaded file!"

print "Parsing File..."
for x in range(0, surf.get_height()):
    print "\tReading pixels at X: "+str(x)
    data.append([])
    for y in range(0, surf.get_height()):
        data[-1].append(surf.get_at([x,y]))
print "Parsed File!"

print "Verifying Data"
for x in range(0, len(data)):
    for y in range(0, len(data[x])):
        if data[x][y][0]==data[x][y][0]==data[x][y][0]:
            pass
        else:
            print "\tError Pixel at: "+str(x)+", "+str(y)
            print "\t\tCorrecting..."
            data[x][y][1]=data[x][y][0]
            data[x][y][2]=data[x][y][0]
            print "\t\tCorrected!"
print "Verified Data!"

print "Generating DataString..."
for x in range(0, len(data)):
    print "\tWriting DataString for X: "+str(x)
    for y in range(0, len(data[x])):
        datastring+=str(data[x][y][0])+" "
    datastring+="?\n"
    print "\tWrote DataString for X: "+str(x)
print "Generated DataString!"

print "~"*50

dest = raw_input("What would you like to save the result as?>>> ")
print

print "Opening heightmap file..."
datafile = open(dest+".hgt", "w")
print "Opened heightmap file!"

print "Writing DataString..."
datafile.write(datastring)
print "Wrote Datastring!"

print "Closing heightmap file..."
datafile.close()
print "Closed heightmap file!"

print "~"*50

print "Done!"