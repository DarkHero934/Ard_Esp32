import serial
import keyboard

esp32_serial_port = 'COM6'
arduino_serial_port = 'COM7'
serial_baudrate = 115200

arduino_ser = serial.Serial(arduino_serial_port, serial_baudrate)
esp_ser = serial.Serial(esp32_serial_port, serial_baudrate)

esp_ser.dtr = 0
esp_ser.rts = 0

try:
    while True:
        incoming_message = esp_ser.read(1)

        print(incoming_message.decode('utf-8'), end = "")

        arduino_ser.write(incoming_message)

        if keyboard.is_pressed('esc'):
            print("Exiting program.")
            break
except:
    print('An error occurrued. Exiting program.')
finally:
    arduino_ser.close()
    esp_ser.close()