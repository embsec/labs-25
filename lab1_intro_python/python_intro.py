import time
import serial

# Define serial connection
ser = serial.Serial("/dev/ttyACM0", 115200)
# Define timeout
ser.timeout = 3

def exercise1_write():
    # Write "Hello" to the board

def read_flag():
    # Use the serial library to read a full line (all text until a '\n' newline character) to retreive the flag from the Tiva board

def exercise2_if_statements():
    # Read age byte from serial device

    # Convert age to an integer
    
    # Determine age category using if, elif, else

    # Send category to serial device

def exercise3_mod():
    # Read 2 random bytes from serial device (remember, these will be in bytes format)

    # Compare the integers, perform a modulus operation, and write the result back to board: larger_num % smaller_num

def main():
    # Write a confirmation message to the serial device to confirm connection to start communication

    # Implement me: Wait for the Tiva to send an 'R' byte

    # Call exercise 1 write function 
    exercise1_write()
    print(read_flag())

    # Get flag from calling exercise 2 function
    exercise2_if_statements()
    print(read_flag())

    # Get flag from calling exercise 3 function
    exercise3_mod()
    print(read_flag())

    ser.close()

if __name__ =="__main__":
    main()
