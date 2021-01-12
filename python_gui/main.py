import serial
import string
import time

WIDTH = 820    # 6 feet
HEIGHT = 700
TITLE = "TOTEM!"
c = 0  # color, initial value
x = [0]*100 # list of size 100 initialized to 0
distance = 0
light = 0
xpos1 = 0
ypos1 = 0
pressed = 0
edge_distance = 0
ser = serial.Serial('COM4',9600)

### Initialise arena
PURPLE = 138,43,226
BOX1 = Rect((100, 100), (150, 150))
BOX2 = Rect((350, 100), (150, 150))
BOX3 = Rect((100, 350), (150, 150))
BOX4 = Rect((350, 350), (150, 150))

### Initialise bot graphics
nick_ = 'nick_small.png'
lynch_ = 'lynch_small.png'
peshkin_ = 'peshkin_small.png'
ale_ = 'ale_small.png'
juan_ = 'juan_small.png'
chris_ = 'chris_small.png'
tiger_ = 'tiger_small.png'

nick = Actor(nick_)
bot = Actor(nick_)
lynch = Actor(lynch_)
peshkin = Actor(peshkin_)
ale = Actor(ale_)
juan = Actor(juan_)
chris = Actor(chris_)
tiger = Actor(tiger_)
Y1 = 650
Y1t = 700
Y2 = Y1
Y2t = Y1t
nick.pos = 60, Y1
lynch.pos = 140, Y1
peshkin.pos = 220,Y1
ale.pos = 300, Y2
juan.pos = 380, Y2 - 10
chris.pos = 460, Y2
tiger.pos = 540, Y2
###

# POSITION CALIBRATION CONSTANTS
bx = [2.978754801577001e+02,-1.648988881665044,-93.660466396540240,-6.816351604487213]
by = [-4.420875473234094e+02,1.471986752577587e+02,-1.675776772422335,0.568207165480135]

tt = time.time()

def draw():   # In Pygame Zero, there's no main() and no functions called. It automatically calls draw() and update() 30 times a second
    screen.fill((255, 255, 255))  # RGB
    ### Draw arena
    screen.draw.filled_rect(BOX1, PURPLE)
    screen.draw.filled_rect(BOX2, PURPLE)
    screen.draw.filled_rect(BOX3, PURPLE)
    screen.draw.filled_rect(BOX4, PURPLE)
    screen.draw.filled_rect(Rect((0, 600), (600, 100)), PURPLE)
    screen.draw.filled_rect(Rect((600, 0), (120, HEIGHT)), PURPLE)
    ### print values, top left to bottom right, ypos is inverted
    screen.draw.text(str(distance), (610, 50), color="orange", fontsize=40)
    screen.draw.text(str(light), (610, 150), color="green", fontsize=40)
    screen.draw.text(str(xpos1), (610, 250), color="cyan", fontsize=40)
    screen.draw.text(str(ypos1), (700, 250), color="cyan", fontsize=40)
    screen.draw.text(str(edge_distance), (610, 350), color="red", fontsize=40)
    if (pressed == 1):
        screen.draw.text("yes (noice)", (610, 450), color="magenta", fontsize=40)
    elif (pressed == 0):
        screen.draw.text("no :(", (610, 450), color="magenta", fontsize=40)
    screen.draw.text("distance:", (610, 10), color="pink", fontsize=40)
    screen.draw.text("light proximity:", (610, 100), color="green", fontsize=40)
    screen.draw.text("x , y:", (610, 200), color="cyan", fontsize=40)
    screen.draw.text("pressed?", (610, 400), color="magenta", fontsize=40)
    screen.draw.text("edge distance", (610, 300), color="red", fontsize=40)

    ###
    bot.draw()
    nick.draw()
    lynch.draw()
    peshkin.draw()
    ale.draw()
    juan.draw()
    chris.draw()
    tiger.draw()
#     print(time.time() - tt)


def plot(data,xpos,ypos,r,g,b):
    ypos = HEIGHT - ypos # flip the y axis
    for i in range(1, len(data)):
        screen.draw.line((xpos+i,ypos),(xpos+i,ypos-x[i]),(r,g,b))

def update(dt):  # called first
    global HEIGHT, x, distance, light, xpos1, ypos1, pressed, edge_distance, tt
#     tt = time.time()
    ### CALIBRATION CURVE FOR VIVE SENSOR
    bot_position_update()
    ###
#     while ser.in_waiting:  # ser. from serial library, =serial.available()
#         line = ser.read_until().strip() #strip() removes the \r\n
#         values = line.decode('ascii').split(' ')
#         print(values)
#         if(values[0] == 'a'):
#              distance = int(values[1])
#         if(values[0] == 'b'):
#              light = int(values[1])
#         if(values[0] == 'c'):
#              xpos1 = float(values[1])
#         if(values[0] == 'd'):
#              ypos1 = float(values[1])
#         if(values[0] == 'e'):
#              pressed = int(values[1])
#         if(values[0] == 'f'):
#              edge_distance = float(values[1])

#     if bot.left > WIDTH:
#         bot.right = 0
#     if bot.right < 0:
#         bot.left = WIDTH
#     if bot.top > HEIGHT:
#         bot.bottom = 0
#     if bot.bottom < 0:
#         bot.top = HEIGHT

#     if keyboard.left:
#         bot.x -= 3
#     elif keyboard.right:
#         bot.x += 3
#     elif keyboard.up:
#         bot.y -= 3
#     elif keyboard.down:
#         bot.y += 3


def bot_position_update():
    bot.x = bx[0] + bx[1]*xpos1 + bx[2]*ypos1 + bx[3]*xpos1*ypos1
    bot.y = 600 - (by[0] + by[1]*xpos1 + by[2]*ypos1 + by[3]*xpos1*ypos1)

def on_mouse_down(button, pos):
    print("Mouse button", button, "down at", pos)
    if ale.collidepoint(pos):
        bot.image = ale_
    elif juan.collidepoint(pos):
        bot.image = juan_
    elif chris.collidepoint(pos):
        bot.image = chris_
    elif tiger.collidepoint(pos):
        bot.image = tiger_
    elif nick.collidepoint(pos):
        bot.image = nick_
    elif lynch.collidepoint(pos):
        bot.image = lynch_
    elif peshkin.collidepoint(pos):
        bot.image = peshkin_
    else:
        ser.write(b'w')

# def on_mouse_up(button, pos):
#     print("Mouse button", button, "up at", pos)
#     ser.write(b'p') ##robot is stationary when mouse is not clicked

def on_key_down(key): #key names are saved in CAPS
    if key.name == 'X':
        ser.write(b'x')
        #print("Sent x")
    if key.name == 'C':
        ser.write(b'c')
        #print("Sent c")
    if key.name == 'W':
        ser.write(b'w')
    if key.name == 'S':
        ser.write(b's')
    if key.name == 'A':
        ser.write(b'a')
    if key.name == 'D':
        ser.write(b'd')
    if key.name == 'P':
        ser.write(b'p')
    if key.name == 'Z':
        ser.write(b'z')
    if key.name == 'T':
        ser.write(b't')
        sounds.release.play()
    if key.name == 'G':
        ser.write(b'g')
        sounds.strike.play()
    if key.name == 'N':
        ser.write(b'n')