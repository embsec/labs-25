import serial
import struct

from Cryptodome.Signature import pss
from Cryptodome.Hash import SHA256
from Cryptodome.PublicKey import RSA

# Uncomment the line below to use a serial device (top for Mac, bottom for Windows/Linux)
#ser = serial.Serial("/dev/tty.usbmodem0E23A4641", 115200)
#ser = serial.Serial("/dev/ttyACM0", 115200)

def exercise_1_rsa_sign():
    # Read file.bin using Python open() function
    
    # Write file length followed by message

    # Read in the RSA private key from key1
    # See: https://pycryptodome.readthedocs.io/en/latest/src/public_key/rsa.html

    # Hash the message using SHA-256

    # Sign the hashed message using the PSS signing algorithm
    # See: https://pycryptodome.readthedocs.io/en/latest/src/signature/pkcs1_pss.html

    # Send full signature over serial

    # Read back the flag
    # print(ser.readline())


def exercise_2_rsa_verify():
    # Load the RSA public key from 'pub1' using RSA.import_key

    while True:
        # Read 2 bytes from serial to get the size of the incoming message (little-endian unsigned short)

        # If size is 0, break the loop and read the final flag

        # Read 'size' bytes of message data from the serial device

        # Read 256 bytes of RSA signature from the serial device

        # Hash the message using SHA-256

        # Verify the signature
        # If the signature is valid, send b'\x01' over serial
        # If the signature is invalid, send b'\x00' over serial

    # Read and print back the flag
    # print(ser.readline())

def main():
    # RSA Lab Exercises:
    exercise_1_rsa_sign()
    exercise_2_rsa_verify()


if __name__ =="__main__":
    main()