# Challenge: Python Introduction

For our labs we are going to need a way for our computers to talk to the Tiva microcontroller. This is where the Python pyserial module comes in. You can find the pyserial API at [pyserial API](https://pyserial.readthedocs.io/en/latest/pyserial_api.html). To save you some time, we'll point out a few useful functions and help with setting up a serial connection between your computer and the Tiva board. 

## Background

Define a serial connection using the device port and the baud rate. 

`import serial`
`ser = serial.Serial("/dev/ttyACM0", 115200)`


In this case, we see that the port is located at "/dev/ttyACM0", however, it may be named differently. We can check for what ports are available by opening a terminal and typing `ls /dev`. 

If you are unsure of which port corresponds to your board, first run `ls /dev` in your terminal with the Tiva board unplugged. This will list all current ports you have access to. Then, connect your Tiva board to your laptop and run `ls /dev` in the terminal again. Locate the new port that is added to your list. That is what you will use to connect to the Tiva.

The baud rate in this instance is set to 115200. What does this mean? It refers to the number of binary bits transferred per second. In other terms, it determines the speed at which data is sent over the serial port. This is usually specified in the documentation for the device you are communicating with (in this case, the Tiva board). 

Read about baudrates here: https://en.wikipedia.org/wiki/Baud

A few useful functions once we have defined the connection 'ser' include:

1. ser.read(int length): reads length number of bytes from device
2. ser.readline(): reads until a newline character "\n" is found
3. ser.write(b"Hello\n"): in this case, writes ASCII bytes 'H', 'e', 'l', 'l', 'o', plus a newline to the device
4. ser.close(): closes the serial port connection
 
 It is important to note that when ser.read is used, it returns a value in bytes format. If we are manipulating this value in any way in python, we likely want to change it to a variable type that is easier to work with. Python has some built-in functions that can help us out here. For example, to convert between bytes and integers in Python, we can use:

`integer_value = int.from_bytes(byte_data, byteorder='little')  # Use 'big' or 'little' for byte order (endianness)`

`byte_data = integer_value.to_bytes(2, byteorder='little')  # Specify the number of bytes and byte order`


Other useful resources for this challenge:

https://www.programiz.com/python-programming/if-elif-else

https://realpython.com/python-modulo-operator/

# Lab Details

There are three exercises in this lab. You will build a Python script that solves each exercise sequentially. See `python_intro.py` for starter code.

After a reset (the button closest to the USB cable), the board will send an ASCII 'R', indicating it has just booted. Your script should wait until it receives this R before executing your solution functions.

Implement and use the `read_flag` function to retreive flags after each solution.

# Exercise 1: Serial Read and Write

For the first exercise, write the ASCII string 'hello' to the board using the write_exercise1 function. The flag will then be sent back from the Tiva board over the serial connection. You will then use read_line_exercise1 to read the flag and print it out.

# Exercise 2: If, Elif, Else

For this exercise you will first read data in the form of a single byte from the serial device. This byte represents the age of a person. Use if, elif, and else statements to check which age range the person falls under:

* Younger than 13 = 'child'
* Between 13 and 19, inclusive = 'teenager'
* Older than 19 = 'adult'

Use `ser.write` to send the age range string back to the Tiva to retreive the flag.

# Exercise 3: Mod

For this exercise the serial device will send two random bytes. Read both bytes and convert them to numbers. Use the mod function to write back to the device the larger number MOD the smaller number. If done correctly, you will then be able to read the flag from the board.
