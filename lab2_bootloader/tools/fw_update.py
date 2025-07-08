#!/usr/bin/env python

import argparse
import serial

from util import *


def update(ser, infile):
    """After connecting to a bootloader (Tiva), send the update command ('U'), then send the contents of the firmware binary

    Args:
        ser: Serial connection
        infile: Path to compiled binary
    """
    with open(infile, "rb") as fp:
        firmware_blob = fp.read()
        print("Updating firmware: ")
        print_hex(firmware_blob)

    # firmware_blob contains all bytes in the compiled binary. They must all be written to flash by the bootloader, but first the bootloader
    # must receive them using this tool

    # Implement me!


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Firmware Update Tool")

    parser.add_argument("--port", help="Provide a USB device to flash FW to (default: /dev/ttyACM0)", default="/dev/ttyACM0")
    parser.add_argument("--firmware", help="Path to firmware image to load.")
    args = parser.parse_args()

    ser = serial.Serial(args.port, 115200)

    update(ser=ser, infile=args.firmware)
    ser.close()
