import turtle
import random

# Set up the screen
wn = turtle.Screen()
wn.title("2048 by Alexander Potiagalov")
wn.bgcolor("black")
wn.setup(width=450, height=400)
wn.tracer(0)

# Score
score = 0

# Grid list
grid = [
    [0, 0, 0, 0],
    [0, 0, 0, 0],
    [0, 0, 0, 0],
    [0, 0, 0, 0]
]

grid_merged = [
    [False, False, False, False],
    [False, False, False, False],
    [False, False, False, False],
    [False, False, False, False]
]

# Pen for grid and scoreboard
pen = turtle.Turtle()
pen.speed(0)
pen.shape("square")
pen.color("white")
pen.penup()
pen.hideturtle()
pen.turtlesize(stretch_wid=2, stretch_len=2, outline=2)
pen.goto(0, 260)

# Scoreboard
score_pen = turtle.Turtle()
score_pen.speed(0)
score_pen.color("white")
score_pen.penup()
score_pen.hideturtle()
score_pen.goto(0, 140)

def update_scoreboard():
    score_pen.clear()
    score_pen.write(f"Score: {score}", align="center", font=("Courier", 24, "normal"))

# Functions
def draw_grid():
    colors = {
        0: "white",
        2: "yellow",
        4: "orange",
        8: "pink",
        16: "red",
        32: "light green",
        64: "green",
        128: "light purple",
        256: "purple",
        512: "gold",
        1024: "silver",
        2048: "black"
    }

    # Top -100, 100
    grid_y = 0
    y = 120
    # Draw the grid
    for row in grid:
        grid_x = 0
        x = -120
        y -= 45
        for column in row:
            x += 45
            pen.goto(x, y)
            
            # Set the color based on the value
            value = grid[grid_y][grid_x]
            color = colors[value]

            pen.color(color)
            pen.stamp()

            pen.color("blue")
            if column == 0:
                number = ""
            else:
                number = str(column)

            pen.sety(pen.ycor() - 10)
            pen.write(number, align="center", font=("Courier", 14, "bold"))
            pen.sety(pen.ycor() + 10)

            grid_x += 1
        
        grid_y += 1

def add_random():
    added = False
    while not added:
        x = random.randint(0, 3)
        y = random.randint(0, 3)

        value = random.choice([2, 4])

        if grid[y][x] == 0:
            grid[y][x] = value
            added = True

def up():
    global score
    for _ in range(4):
        for y in range(1, 4):
            for x in range(0, 4):
                # Empty
                if grid[y-1][x] == 0:
                    grid[y-1][x] = grid[y][x]
                    grid[y][x] = 0
                    continue
            
                # Same
                if grid[y-1][x] == grid[y][x] and not grid_merged[y-1][x]:
                    grid[y-1][x] = grid[y][x] * 2
                    score += grid[y-1][x]  # Add to score
                    grid_merged[y-1][x] = True
                    grid[y][x] = 0
    reset_grid_merged()
    add_random()
    update_scoreboard()
    draw_grid()

def down():
    global score
    for _ in range(4):
        for y in range(2, -1, -1):
            for x in range(0, 4):
                # Empty
                if grid[y+1][x] == 0:
                    grid[y+1][x] = grid[y][x]
                    grid[y][x] = 0
                    continue
            
                # Same
                if grid[y+1][x] == grid[y][x] and not grid_merged[y+1][x]:
                    grid[y+1][x] = grid[y][x] * 2
                    score += grid[y+1][x]  # Add to score
                    grid_merged[y+1][x] = True
                    grid[y][x] = 0
    reset_grid_merged()
    add_random()
    update_scoreboard()
    draw_grid()

def left():
    global score
    for _ in range(4):
        for y in range(0, 4):
            for x in range(1, 4):
                # Empty
                if grid[y][x-1] == 0:
                    grid[y][x-1] = grid[y][x]
                    grid[y][x] = 0
                    continue
                
                # Same
                if grid[y][x-1] == grid[y][x] and not grid_merged[y][x-1]:
                    grid[y][x-1] = grid[y][x] * 2
                    score += grid[y][x-1]  # Add to score
                    grid_merged[y][x-1] = True
                    grid[y][x] = 0
    reset_grid_merged()
    add_random()
    update_scoreboard()
    draw_grid()

def right():
    global score
    for _ in range(4):
        for y in range(0, 4):
            for x in range(2, -1, -1):
                # Empty
                if grid[y][x+1] == 0:
                    grid[y][x+1] = grid[y][x]
                    grid[y][x] = 0
                    continue
                
                # Same
                if grid[y][x+1] == grid[y][x] and not grid_merged[y][x+1]:
                    grid[y][x+1] = grid[y][x] * 2
                    score += grid[y][x+1]  # Add to score
                    grid_merged[y][x+1] = True
                    grid[y][x] = 0
    reset_grid_merged()
    add_random()
    update_scoreboard()
    draw_grid()

def reset_grid_merged():
    global grid_merged
    grid_merged = [
        [False, False, False, False],
        [False, False, False, False],
        [False, False, False, False],
        [False, False, False, False]
    ]

# Initialize the game
draw_grid()
add_random()
update_scoreboard()

# Keyboard bindings
wn.listen()
wn.onkeypress(left, "Left")
wn.onkeypress(right, "Right")
wn.onkeypress(up, "Up")
wn.onkeypress(down, "Down")

wn.mainloop()
