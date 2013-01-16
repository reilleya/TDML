import pygame

readlevel = []
level = []
floor = 0

for crap in range(0, 31):
    level.append([])
    for i in range(0, 31):
        level[-1].append([0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0])

pygame.init()

screen = pygame.display.set_mode([600,600])

running = True

pygame.display.set_caption("Crappy Level Editor: Floor "+str(floor))

while running:
    for event in pygame.event.get():
        if event.type == pygame.MOUSEBUTTONDOWN:
            if event.button == 1:
                posx = event.pos[0]/20
                posy = event.pos[1]/20
                if level[floor][posy][posx] == 0:
                    level[floor][posy][posx] = 1
                else:
                    level[floor][posy][posx] = 0
            if event.button==5:
                if floor<29:
                    floor+=1
                pygame.display.set_caption("Crappy Level Editor: Floor "+str(floor))
            if event.button==4:
                if floor > 0:
                    floor-=1
                pygame.display.set_caption("Crappy Level Editor: Floor "+str(floor))
        
        if event.type == pygame.KEYDOWN:
            if event.key == pygame.K_s:
                fileop = open("output.txt", "w")
                for flor in level:
                    for y in flor:
                        for x in y:
                            fileop.write(str(x))    
                        fileop.write("\n")
                fileop.close()
                
            if event.key == pygame.K_l:
                fileop = open("output.txt", "r")
                readlevel = []
                for r in fileop.readlines():
                    readlevel.append(r)
                for q in range(0, 30):
                    #print q
                    for i in range(0, 30):
                        #print "\t"+str(i)
                        for p in range(0, 30):
                            #print "\t\t"+str(p)
                            level[q][i][p]=int(readlevel[(q*31)+i][p])
                            
            if event.key == pygame.K_e:
                r = open("output.wor", "w")
                ink = 0
                for f in range(0, 30):
                    for y in range(0, 30):
                        for x in range(0, 30):
                            if level[f][y][x] == 1:
                                if level[f+1][y][x]==0:
                                    r.write("Resources/Common/Crate/Top/model.tdm ?\n")
                                    r.write("0 ?\n")
                                    r.write("0 ?\n")
                                    r.write(str(y*2)+" ? "+str(1+(2*f))+" ? "+str(x*2)+" ?\n")
                                    r.write("0.0 ? 0.0 ? 0.0 ?\n")
                                    r.write("1.0 ? 1.0 ? 1.0 ?\n")
                                    r.write("cratetop"+str(ink)+" ?\n")
                                    r.write("crate ?\n")
                                    r.write("Resources/Common/static.beh ?\n")
                                    r.write("Resources/Common/Crate/Top/material1.mdf ?\n")
                                    r.write("[\n")
                                    ink+=1
                                    
                                if level[f][y+1][x]==0:
                                    r.write("Resources/Common/Crate/Side/model.tdm ?\n")
                                    r.write("0 ?\n")
                                    r.write("0 ?\n")
                                    r.write(str((y*2)+1)+" ? "+str(2*f)+" ? "+str(x*2)+" ?\n")
                                    r.write("0.0 ? 90.0 ? 0.0 ?\n")
                                    r.write("1.0 ? 1.0 ? 1.0 ?\n")
                                    r.write("crateside"+str(ink)+" ?\n")
                                    r.write("crate ?\n")
                                    r.write("Resources/Common/static.beh ?\n")
                                    r.write("Resources/Common/Crate/Side/material1.mdf ?\n")
                                    r.write("[\n")
                                    ink+=1
                                    
                                if level[f][y-1][x]==0:
                                    r.write("Resources/Common/Crate/Side/model.tdm ?\n")
                                    r.write("0 ?\n")
                                    r.write("0 ?\n")
                                    r.write(str((y*2)-1)+" ? "+str(2*f)+" ? "+str(x*2)+" ?\n")
                                    r.write("0.0 ? 270.0 ? 0.0 ?\n")
                                    r.write("1.0 ? 1.0 ? 1.0 ?\n")
                                    r.write("crateside"+str(ink)+" ?\n")
                                    r.write("crate ?\n")
                                    r.write("Resources/Common/static.beh ?\n")
                                    r.write("Resources/Common/Crate/Side/material1.mdf ?\n")
                                    r.write("[\n")
                                    ink+=1
                                    
                                if x<29:
                                    if level[f][y][x+1]==0:
                                        r.write("Resources/Common/Crate/Side/model.tdm ?\n")
                                        r.write("0 ?\n")
                                        r.write("0 ?\n")
                                        r.write(str(y*2)+" ? "+str(2*f)+" ? "+str((x*2)+1)+" ?\n")
                                        r.write("0.0 ? 0.0 ? 0.0 ?\n")
                                        r.write("1.0 ? 1.0 ? 1.0 ?\n")
                                        r.write("crateside"+str(ink)+" ?\n")
                                        r.write("crate ?\n")
                                        r.write("Resources/Common/static.beh ?\n")
                                        r.write("Resources/Common/Crate/Side/material1.mdf ?\n")
                                        r.write("[\n")
                                        ink+=1
                                        
                                if x>0:
                                    if level[f][y][x-1]==0:
                                        r.write("Resources/Common/Crate/Side/model.tdm ?\n")
                                        r.write("0 ?\n")
                                        r.write("0 ?\n")
                                        r.write(str(y*2)+" ? "+str(2*f)+" ? "+str((x*2)-1)+" ?\n")
                                        r.write("0.0 ? 180.0 ? 0.0 ?\n")
                                        r.write("1.0 ? 1.0 ? 1.0 ?\n")
                                        r.write("crateside"+str(ink)+" ?\n")
                                        r.write("crate ?\n")
                                        r.write("Resources/Common/static.beh ?\n")
                                        r.write("Resources/Common/Crate/Side/material1.mdf ?\n")
                                        r.write("[\n")
                                        ink+=1
                                        
                r.write("Resources/Common/Character/model.tdm ?\n")
                r.write("0 ?\n")
                r.write("0 ?\n")
                r.write("0.0 ? 0.0 ? 0.0 ?\n")
                r.write("0.0 ? 0.0 ? 0.0 ?\n")
                r.write("0.5 ? 0.5 ? 0.5 ?\n")
                r.write("Character ?\n")
                r.write("Character ?\n")
                r.write("Resources/Common/static.beh ?\n")
                r.write("Resources/Common/Character/material.mdf ?\n")
                r.write("[\n")
                
        if event.type == pygame.QUIT:
            running = False
            
    screen.fill([255,255,255])
    for y in range(0, 30):
        for x in range(0, 30):
            if level[floor][y][x] == 1:
                pygame.draw.rect(screen, [0,0,0], [x*20, y*20, 20, 20], 0)
    pygame.display.flip()