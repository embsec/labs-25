# Challenge: RSA in Python

In this lesson, you will use the PyCryptodome Python library to sign messages and verify incoming signed messages over serial. Here is some of the documentation you will need to complete this lab:

https://pycryptodome.readthedocs.io/en/latest/src/public_key/rsa.html

https://pycryptodome.readthedocs.io/en/latest/src/signature/signature.html#signing-a-message

https://pycryptodome.readthedocs.io/en/latest/src/signature/pkcs1_pss.html

https://pycryptodome.readthedocs.io/en/latest/src/util/util.html

For clarification, this lab uses RSA PKCS1 PSS, which will point you in the direction of the correct documentation to read.

## Background

# Exercise 1: rsa_sign

The backend is expecting a signed message from file.bin. You'll send it in the following format:

[    0x100    ]
---------------
|  Signature  |
---------------
Read the message from file.bin
Read the RSA private key from key1
Hash the message using SHA-256
Sign the hashed message using RSA with PKCS1 PSS padding
Send the resulting signature over serial and print the flag
Read nad print the flag

# Exercise 2: rsa_verify

The backend will send you a series of messages in the format below:

[   0x02   ] [      variable...     ] [      0x100     ]
-------------------------------------------------------
|   Size   |          Data           |  RSA Signature  |
-------------------------------------------------------
For each message, you must verify the data using the attached signature. If verification fails, you must respond with a zero-byte '\x00'. If verification passes, you must respond with a one-byte '\x01'. When the length of the message you are about to receive is zero (a zero length frame), read a newline-terminated flag.

The RSA public key will be stored in pub1

In a loop:
    Read the size as a little endian short. Reminder: This is 2 bytes or 16 bits. ser parameters are in bytes, pwntools pack/unpack function names refer to bits.
    Read the data from serial using the size
    Read the 256 byte RSA signature
    Verify the hashed message/signature and send the appropriate byte back to serial
    Repeat until the size read from serial is 0
    
Read the flag from serial