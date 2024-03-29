import pyfirmata
import time, subprocess

board = pyfirmata.Arduino('/dev/ttyACM1')
LED_PIN = 13
BUTTON_PIN = 10
it = pyfirmata.util.Iterator(board)
it.start()

board.digital[BUTTON_PIN].mode = pyfirmata.INPUT
# digital_input = board.get_pin('d:BUTTON_PIN:i')
# led = board.get_pin('d:12:o')

led_state = False
clicked = False

while True:
  button_pin = board.digital[BUTTON_PIN].read()
  
  if button_pin is True and clicked is False:
    clicked = True
    if led_state:
      led_state = False
      board.digital[LED_PIN].write(0)
      subprocess.call(['firefox', 'http://www.pornhub.com'])
    else:
      led_state = True
      board.digital[LED_PIN].write(1)
  elif button_pin is False and clicked is True:
    clicked = False
  time.sleep(0.01)