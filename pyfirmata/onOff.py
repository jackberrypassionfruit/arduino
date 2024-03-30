import pyfirmata
import time

board = pyfirmata.Arduino('/dev/ttyACM0')

it = pyfirmata.util.Iterator(board)
it.start()

board.digital[10].mode = pyfirmata.INPUT

# digital_input = board.get_pin('d:10:i')
# led = board.get_pin('d:12:o')

while True:
    sw = board.digital[10].read()
    # sw = digital_input.read()
    if sw is True:
        board.digital[12].write(1)
        # led.write(1)
    else:
        board.digital[12].write(0)
        # led.write(0)
    time.sleep(0.01)