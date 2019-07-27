import serial

serial_conn = serial.Serial('/dev/cu.usbserial-AC00MB9L', 19200)

f = open('rand.binary', 'wb')

while True:
    data_byte = serial_conn.read()

    f.write(data_byte)
    f.flush()
