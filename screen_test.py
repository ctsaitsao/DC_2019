import serial
import string

WIDTH = 600    # 6 feet
HEIGHT = 600   # 6 feet
TITLE = "TOTEM!"
c = 0  # color, initial value
x = [0]*100 # list of size 100 initialized to 0
distance = 0
light = 0
# ser = serial.Serial('COM4',9600)


### Initialise arena and nick
PURPLE = 138,43,226
BOX1 = Rect((100, 100), (150, 150))
BOX2 = Rect((350, 100), (150, 150))
BOX3 = Rect((100, 350), (150, 150))
BOX4 = Rect((350, 350), (150, 150))
nick = Actor('nick.png')
nick.pos = 100, 56
x_pos, y_pos = nick.pos
vector = nick.topleft
###

def draw():   # In Pygame Zero, there's no main() and no functions called. It automatically calls draw() and update() 30 times a second
    screen.fill((0, 0, c))  # RGB

    ### Draw arena
    screen.draw.filled_rect(BOX1, PURPLE)
    screen.draw.filled_rect(BOX2, PURPLE)
    screen.draw.filled_rect(BOX3, PURPLE)
    screen.draw.filled_rect(BOX4, PURPLE)
    nick.draw()
    ###

    plot(x,10,HEIGHT/2,0,0,255) # data, xpos, ypos, red, green, blue
    plot(x,10,HEIGHT/2,0,0,255) # data, xpos, ypos, red, green, blue

    screen.draw.text(str(distance), (360, 20), color="orange", fontsize=60) # top left to bottom right, ypos is inverted
    screen.draw.text(str(light), (0, 20), color="orange", fontsize=60)

def plot(data,xpos,ypos,r,g,b):
    ypos = HEIGHT - ypos # flip the y axis
    # for i in range(1, len(data)):
    #     screen.draw.line((xpos+i,ypos),(xpos+i,ypos-x[i]),(r,g,b))

def update(dt):  # called first
    global c, HEIGHT, x, distance, light
    c = (c + 1) % 256   # it would get to 255 and go back to 0
#     while ser.in_waiting:  # ser. from serial library, =serial.available()
#         line = ser.read_until().strip() #strip() removes the \r\n
#         values = line.decode('ascii').split(' ')
#         #print(values)
#         if(values[0] == 'x'):
#             x[int(values[1])] = int(values[2])  # necessary for a sine wave
#             #print(x)
#         if(values[0] == 'a'):
#             distance = int(values[1])
#         if(values[0] == 'b'):
#             light = int(values[1])
# #             print(light)

    ### Update nick's position
    nick.angle += 1

    # nick.x =
    # nick.y =
    if nick.left > WIDTH:
        nick.right = 0
    if nick.right < 0:
        nick.left = WIDTH
    if nick.top > HEIGHT:
        nick.bottom = 0
    if nick.bottom < 0:
        nick.top = HEIGHT
    ###
    if keyboard.left:
        nick.x -= 3
    elif keyboard.right:
        nick.x += 3
    elif keyboard.up:
        nick.y -= 3
    elif keyboard.down:
        nick.y += 3


def on_mouse_down(button, pos):
    print("Mouse button", button, "down at", pos)
    nick.x = pos[0]
    nick.y = pos[1]

    # ser.write(b'w') # robot moves forward when mouse is clicked

def on_mouse_up(button, pos):
    print("Mouse button", button, "up at", pos)
    # ser.write(b'p') # robot is stationary when mouse is not clicked

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
    if key.name == 'E':
        ser.write(b'e')
