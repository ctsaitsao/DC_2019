import serial
import string

WIDTH = 600    # 6 feet
HEIGHT = 700
TITLE = "TOTEM!"
c = 0  # color, initial value
x = [0]*100 # list of size 100 initialized to 0
distance = 0
light = 0
xpos1 = 0
ypos1 = 0
pressed = 0
ser = serial.Serial('COM5',9600)

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


def draw():   # In Pygame Zero, there's no main() and no functions called. It automatically calls draw() and update() 30 times a second
    screen.fill((255, 255, 255))  # RGB
    plot(x,10,HEIGHT/2,0,0,255) # data, xpos, ypos, red, green, blue
    screen.draw.text(str(distance), (500, 50), color="orange", fontsize=40) # top left to bottom right, ypos is inverted
    screen.draw.text(str(light), (20, 50), color="orange", fontsize=40)
    screen.draw.text(str(xpos1), (20, 550), color="orange", fontsize=40)
    screen.draw.text(str(ypos1), (100, 550), color="orange", fontsize=40)
    if (pressed == 1):
        screen.draw.text("yes (nice)", (450, 550), color="orange", fontsize=40)
    elif (pressed == 0):
        screen.draw.text("no :(", (450, 550), color="orange", fontsize=40)
    screen.draw.text("distance:", (450, 0), color="orange", fontsize=40) # top left to bottom right, ypos is inverted
    screen.draw.text("light proximity:", (0, 0), color="orange", fontsize=40)
    screen.draw.text("x , y:", (20, 520), color="orange", fontsize=40)
    screen.draw.text("pressed?", (400, 520), color="orange", fontsize=40)
    ### Draw arena
    screen.draw.filled_rect(BOX1, PURPLE)
    screen.draw.filled_rect(BOX2, PURPLE)
    screen.draw.filled_rect(BOX3, PURPLE)
    screen.draw.filled_rect(BOX4, PURPLE)
    ###
    bot.draw()
    nick.draw()
    lynch.draw()
    peshkin.draw()
    ale.draw()
    juan.draw()
    chris.draw()
    tiger.draw()
    bot.pos = xpos1*25, ypos1*25

def plot(data,xpos,ypos,r,g,b):
    ypos = HEIGHT - ypos # flip the y axis
    for i in range(1, len(data)):
        screen.draw.line((xpos+i,ypos),(xpos+i,ypos-x[i]),(r,g,b))

def update(dt):  # called first
    global c, HEIGHT, x, distance, light, xpos1, ypos1, pressed
    c = (c + 1) % 256   # it would get to 255 and go back to 0
    while ser.in_waiting:  # ser. from serial library, =serial.available()
        line = ser.read_until().strip() #strip() removes the \r\n
        values = line.decode('ascii').split(' ')
        #print(values)
        if(values[0] == 'x'):
            x[int(values[1])] = int(values[2])  # necessary for a sine wave
            #print(x)
        if(values[0] == 'a'):
             distance = int(values[1])
        if(values[0] == 'b'):
             light = int(values[1])
        if(values[0] == 'c'):
             xpos1 = float(values[1])
        if(values[0] == 'd'):
             ypos1 = float(values[1])
        if(values[0] == 'e'):
             pressed = int(values[1])


#             print(light)
#      Update bot's position
#     bot.x =
#     bot.y =
    # if bot.left > WIDTH:
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
        ser.write(b'w') # robot moves forward when mouse is clicked

def on_mouse_up(button, pos):
    #print("Mouse button", button, "up at", pos)
    ser.write(b'p') # robot is stationary when mouse is not clicked

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
    if key.name == 'Q':
        ser.write(b'q')
        sounds.release.play()
    if key.name == 'E':
        ser.write(b'e')
        sounds.strike.play()
    if key.name == 'N':
        ser.write(b'n')
