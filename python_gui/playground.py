WIDTH = 600    # 6 feet
HEIGHT = 600   # 6 feet
TITLE = "TOTEM!"
c = 0  # color, initial value
x = [0]*100 # list of size 100 initialized to 0
distance = 0
light = 0
# ser = serial.Serial('COM4',9600)


### Initialise arena and bot
PURPLE = 138,43,226
BOX1 = Rect((100, 100), (150, 150))
BOX2 = Rect((350, 100), (150, 150))
BOX3 = Rect((100, 350), (150, 150))
BOX4 = Rect((350, 350), (150, 150))


### Initialise graphics
nick = Actor('nick_small.png')
nickAV = Actor('nick_large.png')
lynch = Actor('lynch_small.png')
lynchAV = Actor('lynch_large.png')
peshkin = Actor('peshkin_small.png')
peshkinAV = Actor('peshkin_large.png')
ale = Actor('ale_small.png')
aleAV = Actor('ale_large.png')
juan = Actor('juan_small.png')
juanAV = Actor('juan_large.png')
chris = Actor('chris_small.png')
chrisAV = Actor('chris_large.png')
tiger = Actor('tiger_small.png')
tigerAV = Actor('tiger_large.png')
Y1 = 280
Y1t = 350
Y2 = 470
Y2t = 540
nickAV.pos = 130, Y1
lynchAV.pos = 300, Y1
peshkinAV.pos = 470,Y1
aleAV.pos = 90, Y2
juanAV.pos = 230, Y2 - 10
chrisAV.pos = 380, Y2
tigerAV.pos = 510, Y2
character_selected = True
###

def draw():
    if not character_selected:
        screen.fill(PURPLE)
        screen.draw.text("Select your character", (75, 80), color="orange", fontsize=60)
        screen.draw.text("for TOTEM 2019!", (135, 130), color="orange", fontsize=60)

        screen.draw.text("Prof. Marchuk", (60, Y1t), color="orange", fontsize=30)
        screen.draw.text("Prof. Lynch", (250, Y1t), color="orange", fontsize=30)
        screen.draw.text("Prof. Peshkin", (410, Y1t), color="orange", fontsize=30)

        screen.draw.text("Ale", (70, Y2t), color="orange", fontsize=30)
        screen.draw.text("Juan", (200, Y2t), color="orange", fontsize=30)
        screen.draw.text("Chris", (360, Y2t), color="orange", fontsize=30)
        screen.draw.text("Tiger", (490, Y2t), color="orange", fontsize=30)

        nickAV.draw()
        lynchAV.draw()
        peshkinAV.draw()
        aleAV.draw()
        juanAV.draw()
        chrisAV.draw()
        tigerAV.draw()

    ###

# def on_mouse_down(button, pos):
#     print("Mouse button", button, "down at", pos)

def on_mouse_down(pos):
    if not character_selected:
        if aleAV.collidepoint(pos):
            bot = ale
            screen.clear()
