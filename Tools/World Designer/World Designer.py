import pygame, random

objects = []

renderlist = []
#[[thirdval1, color1, rect1, selected1],[thirdval2, color2, rect2, selected2],[thirdval3, color3, rect3, selected3]]

cat = 0

dir = "C:/Users/Andrew/Desktop/NCC/OpenGL/3D Model Loader/3D Model Loader/LightingLand/"

class object:
    def __init__(self):
        self.selected = False
        self.pos = [0,0,0]
        self.rotation = [0,0,0]
        self.scale = [1,1,1]
        self.dimensions = [-1, -1, -1, 1, 1, 1]
        self.model = "null.tdm"
        self.material = "null.mdf"
        self.behaviors = "null.beh"
        self.name = "nullname"
        self.type = "nulltype"
        self.visible = False
        self.wireframe = False
        self.color = [random.randint(0,255),random.randint(0,255),random.randint(0,255)]
    
    def write(self, OutputFile):
        OutputFile.write(self.model+" ?\n")
        OutputFile.write(str(int(self.wireframe))+" ?\n")
        OutputFile.write(str(int(self.visible))+" ?\n")
        OutputFile.write(str(self.pos[0])+" ? "+str(self.pos[1])+" ? "+str(self.pos[2])+" ?\n")
        OutputFile.write(str(self.rotation[0])+" ? "+str(self.rotation[1])+" ? "+str(self.rotation[2])+" ?\n")
        OutputFile.write(str(self.scale[0])+" ? "+str(self.scale[1])+" ? "+str(self.scale[2])+" ?\n")
        OutputFile.write(self.name+" ?\n")
        OutputFile.write(self.type+" ?\n")
        OutputFile.write(self.behaviors+" ?\n")
        OutputFile.write(self.material+" ?\n")
        OutputFile.write("[\n")
        
    def loadDimensions(self):
        dfile = open(dir+self.model)
        data = dfile.readlines()
        for i in range(0, len(data)):
            data[i] = data[i].strip("?").strip("\n").split(" ")
        
        for d in data:
            if len(d) > 1:
                if float(d[0])<self.dimensions[0]:
                    self.dimensions[0] = float(d[0])
                if float(d[0])>self.dimensions[3]:
                    self.dimensions[3] = float(d[0])
                if float(d[1])<self.dimensions[1]:
                    self.dimensions[1] = float(d[1])
                if float(d[1])>self.dimensions[4]:
                    self.dimensions[4] = float(d[1])
                if float(d[2])<self.dimensions[2]:
                    self.dimensions[2] = float(d[2])
                if float(d[2])>self.dimensions[5]:
                    self.dimensions[5] = float(d[2])
            
        dfile.close()
        
    def prepare_render(self):
        renderl = []
        renderl.append(self.pos[czax])
        renderl.append(self.color)
        renderl.append(pygame.rect.Rect(
        
        600-flip_x*(czoom*(self.pos[cxax]-(self.dimensions[cxax]*self.scale[cxax]))+cpos[0]),
        325-flip_y*(czoom*(self.pos[cyax]-(self.dimensions[cyax]*self.scale[cyax]))+cpos[1]),
        
        (abs(self.dimensions[cxax])+self.dimensions[cxax+3])*self.scale[cxax]*czoom, 
        (abs(self.dimensions[cyax])+self.dimensions[cyax+3])*self.scale[cyax]*czoom
        ))
        if flip_x == -1:
            renderl[-1].x -= self.dimensions[cxax]
        #renderl.append([600-flip_x*(czoom*(self.pos[cxax]-(self.dimensions[cxax]*self.scale[cxax]))+cpos[0]), 325-flip_y*(czoom*(self.pos[cyax]-(self.dimensions[cyax]*self.scale[cyax]))+cpos[1]), (abs(self.dimensions[cxax])+self.dimensions[cxax+3])*self.scale[cxax]*czoom, (abs(self.dimensions[cyax])+self.dimensions[cyax+3])*self.scale[cyax]*czoom])
        renderl.append(self.selected)
        return renderl

def scaleLocalCoords(coords):
    click_x = -flip_x*((coords[0]-600)-cpos[0])/czoom
    click_y = -flip_y*((coords[1]-325)-cpos[1])/czoom
    return [click_x, click_y]
    
def getLocalMouse():
    c = pygame.mouse.get_pos()
    coords = [c[0], c[1]]
    return scaleLocalCoords(coords)


def deselect_all():
    global world
    for obj in world:
        obj.selected = False

def loadWorld(filename):
    pygame.display.set_caption("TDML::WD('"+filename+"')")
    world = []
    objd = []
    f = open(filename,"r")
    data = f.readlines()
    for i in range(0,len(data)):
        data[i] = data[i].strip("\n").strip("?").strip(" ")
    for d in data:
        if d=="[":
            world.append(object())
            world[-1].model = objd[0]
            world[-1].wireframe = bool(int(objd[1]))
            world[-1].visible = bool(int(objd[2]))
            world[-1].pos = objd[3].split("?")
            for pos in range(0, 3):
                world[-1].pos[pos]=float(world[-1].pos[pos])
            world[-1].rotation = objd[4].split("?")
            for rot in range(0, 3):
                world[-1].rotation[rot]=float(world[-1].rotation[rot])
            world[-1].scale = objd[5].split("?")
            for scl in range(0, 3):
                world[-1].scale[scl]=float(world[-1].scale[scl])
            world[-1].name = objd[6]
            world[-1].type = objd[7]
            world[-1].behaviors = objd[8]
            world[-1].material = objd[9]
            world[-1].loadDimensions()
            objd = []
        else:
            objd.append(d)
    f.close()
    world[-1].selected = True
    return world


flip_x = 1
flip_y = 1

cxax = 0
cyax = 1
czax = 2
back = False

czoom = 1.0
cpos = [0,0]

pygame.init()
pygame.key.set_repeat(1, 100)

pygame.display.set_caption("TDML::WD('null.wor')")
world = loadWorld(dir+"world1.wor")
screen = pygame.display.set_mode([1200,650])
screen.fill([255,255,255])

running = True

while running:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False
        
        if event.type == pygame.MOUSEMOTION:
            if pygame.mouse.get_pressed()[2]:
                click = getLocalMouse()
                click_x = click[0]
                click_y = click[1]
                for obj in world:
                    if obj.selected:
                        if click_x > obj.pos[cxax]+(obj.dimensions[cxax]*obj.scale[cxax]) and click_x < obj.pos[cxax]+(obj.dimensions[cxax+3]*obj.scale[cxax]):
                            if click_y > obj.pos[cyax]+(obj.dimensions[cyax]*obj.scale[cyax]) and click_y < obj.pos[cyax]+(obj.dimensions[cyax+3]*obj.scale[cyax]):
                                co = [event.rel[0]/czoom, event.rel[1]/czoom]
                                #print co
                                #obj.scale[cxax] += co[0]
                                #obj.scale[cyax] -= co[1]
                                obj.pos[cxax]-=co[0]
                                obj.pos[cyax]-=co[1]
            
        if event.type == pygame.MOUSEBUTTONDOWN:
            if event.button == 1:
                click = getLocalMouse()
                click_x = click[0]
                click_y = click[1]
                for obj in world:
                    if click_x > obj.pos[cxax]+(obj.dimensions[cxax]*obj.scale[cxax]) and click_x < obj.pos[cxax]+(obj.dimensions[cxax+3]*obj.scale[cxax]):
                        if click_y > obj.pos[cyax]+(obj.dimensions[cyax]*obj.scale[cyax]) and click_y < obj.pos[cyax]+(obj.dimensions[cyax+3]*obj.scale[cyax]):
                            deselect_all()
                            obj.selected = True

            if event.button == 4:
                czoom += 0.25
                
            if event.button == 5:
                if czoom > 0.25:
                    czoom -= 0.25
                    
        if event.type == pygame.KEYDOWN:
            if event.key == pygame.K_LEFT:
                cpos[0]+=4
            if event.key == pygame.K_RIGHT:
                cpos[0]-=4
            if event.key == pygame.K_UP:
                cpos[1]+=4
            if event.key == pygame.K_DOWN:
                cpos[1]-=4
                
            if event.key == pygame.K_KP8:
                #top view
                cxax = 0
                cyax = 2
                czax = 1
                back = False
                flip_x = 1
                flip_y = 1
                
            if event.key == pygame.K_KP2:
                #top view
                cxax = 0
                cyax = 2
                czax = 1
                back = True
                flip_x = 1
                flip_y = 1
            
            if event.key == pygame.K_KP5:
                #front view
                cxax = 0
                cyax = 1
                czax = 2
                back = False
                flip_x = 1
                flip_y = 1
            
            if event.key == pygame.K_KP0:
                #back view
                cxax = 0
                cyax = 1
                czax = 2
                back = True
                flip_x = 1
                flip_y = 1
                
            if event.key == pygame.K_KP4:
                #side view
                cxax = 2
                cyax = 1
                czax = 0
                back = False
                flip_x = 1
                flip_y = 1
                
            if event.key == pygame.K_KP6:
                #other side view
                cxax = 2
                cyax = 1
                czax = 0
                back = True
                flip_x = 1
                flip_y = 1

            if event.key == pygame.K_s:
                fi = open("test.wor", "w")
                for item in world:
                    item.write(fi)
                fi.close()
                
            if event.key == pygame.K_v:
                world.append(object())
                
    screen.fill([255,255,255])
    
    for o in world:
        renderlist.append(o.prepare_render())
            
    renderlist.sort()
    
    if back:
        for r in reversed(renderlist):
            pygame.draw.rect(screen, r[1], r[2], 0)
            if r[3]:
                pygame.draw.ellipse(screen, [0,0,0], r[2], 0)
    else:
        for r in renderlist:
            pygame.draw.rect(screen, r[1], r[2], 0)
            if r[3]:
                pygame.draw.ellipse(screen, [0,0,0], r[2], 0)
            
    renderlist = []
    
    pygame.display.flip()
