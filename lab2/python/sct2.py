from sense_hat import SenseHat
import time
sense = SenseHat()
print("test")
while True:
    for event in sense.stick.get_events():
        if (event.action == "pressed"):
            if (event.direction == "left"):
                sense.show_message("Left",text_colour=[255, 0, 0])
            elif (event.direction == "middle"):
                sense.show_message("Middle",text_colour=[0, 255, 0])
            elif (event.direction == "right"):
                sense.show_message("Right",text_colour=[0, 0, 255])
            elif(event.direction == "up"):
                sense.show_message("Up",text_colour=[255, 0, 255])
            elif(event.direction == "down"):
                sense.show_message("Down",text_colour=[255, 0, 150])
        time.sleep(0.2)
