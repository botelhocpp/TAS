import argparse
import serial
import time

def flash(binary_file, port):
    try:
        ser = serial.Serial(port=port, baudrate=115200, bytesize=serial.EIGHTBITS, 
                    timeout=1, stopbits=serial.STOPBITS_ONE, parity=serial.PARITY_NONE)
    except serial.SerialException as e:
        print(f"Error opening serial port: {e}")
        return

    try:
        with open(binary_file, "rb") as file:
            read_bin_file = True
            i = 0
            while read_bin_file:
                palavra = file.read(2)
                
                if len(palavra) < 2:
                    palavra = b'\xff\xff'
                    read_bin_file = False

                ser.reset_output_buffer()
                ser.flush()

                time.sleep(0.001)
                ser.write(palavra[0:1])

                time.sleep(0.001)
                ser.write(palavra[1:2])

                print(f"{i+1}: 0x{palavra[1:2].hex()}{palavra[0:1].hex()} ")
                i = i + 1
        
    except FileNotFoundError:
        print(f"File '{binary_file}' not found.")
    finally:
        ser.close()

if __name__ == '__main__':
    parser = argparse.ArgumentParser(description="Send a binary file throutgh serial port to the TRISC-16 microcontroller.")
    parser.add_argument("file", help="Binary file path")
    parser.add_argument("port", help="Serial port (ex: COM3, /dev/ttyUSB0)")
    
    args = parser.parse_args()
    flash(args.file, args.port)
