from sense_hat import SenseHat
from time import sleep
from random import randrange

sense = SenseHat()
while True:
    white = [0, 0, 0]
    matrix = [white for _ in range(0, 64)]
    for i in range(8):
        color = [randrange(1, 255), randrange(1, 255), randrange(10, 100)]
        matrix = [white for _ in range(0, 64)]
        row = i
        col = 0
        while col <= i:
            matrix[row*8+col] = color
            row -= 1
            col += 1
        sense.set_pixels(matrix)
        sleep(0.05)
    for i in range(1,8):
        color = [randrange(1, 255), randrange(1, 255), randrange(10, 100)]
        matrix = [white for _ in range(0, 64)]
        row = i
        col = 7
        while col >= i:
            matrix[row*8+col] = color
            row += 1
            col -= 1
        sense.set_pixels(matrix)
        sleep(0.05)