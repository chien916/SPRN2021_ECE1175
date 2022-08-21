from sense_hat import SenseHat
from time import sleep
from random import randrange
sense = SenseHat()
sense.set_imu_config(False, False, True)  # gyroscope only
direction = 3  # 0,1,2,3
row_num = 0
while True:
    white = [0, 0, 0]
    matrix = [white for _ in range(0, 64)]
    color = [randrange(1, 255),randrange(1, 255),randrange(10, 100)]
    for i in range(row_num * 8, row_num * 8 + 8):
        matrix[i] = color
    sense.set_pixels(matrix)
    sense.set_rotation(90 * direction)
    # raw = sense.get_gyroscope_raw()
    # print("x: {x}, y: {y}, z: {z}".format(**raw))
    sleep(0.05)
    if (row_num == 7):
        row_num = 0
        raw = sense.get_accelerometer_raw()
        if (abs(raw['x']) - abs(raw['y']) > 0):
            if (raw['x'] < 0):
                direction = 1
            else:
                direction = 3
        else:
            if (raw['y'] < 0):
                direction = 2
            else:
                direction = 0
    else:
        row_num = row_num + 1
