from sense_hat import SenseHat
from time import sleep
sense = SenseHat()
while True:
    sense.load_image("/home/pi/Documents/lab2/turn_0.png")
    sleep(0.3)
    sense.load_image("/home/pi/Documents/lab2/turn_black.png")
    sleep(0.3)
    sense.load_image("/home/pi/Documents/lab2/turn_1.png")
    sleep(0.3)
    sense.load_image("/home/pi/Documents/lab2/turn_black.png")
    sleep(0.3)