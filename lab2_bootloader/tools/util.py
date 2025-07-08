#!/usr/bin/env python


def print_hex(data):
    hex_string = " ".join(format(byte, "02x") for byte in data)
    print(hex_string)
