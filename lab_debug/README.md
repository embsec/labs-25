# Lab 3: Debug

This lab will test your debugging abilities. You have been provided with lab3 source code, but it's riddled with errors!

Use `openocd`, `gdb`, and your debugging skills to fix up this program!

## String Checksum Generation Tool

This tool will provide us with a checksum byte to use to add integrity to our messages. It takes a string (entered through the serial interface), computes a checksum byte, then returns the byte to the user. See the example below.

## Lab 3 Objective

Fix the checksum program by using the debugger interface to the board. When you have debugged the program, you can interact with the tool to provide the flag, which is made up of a series of checksums (yes you could compute the checksums yourself, but please work through this debugging exercise!):

Flag = embsec(lab3_debug_[cs1][cs2][cs3][cs4][cs5][cs6][cs7][cs8])

Where csN is the checksum byte for the following strings:

cs1 = "bwsi"
cs2 = "is"
cs3 = "transformational"
cs4 = "embsec"
cs5 = "rules"
cs6 = "debugging"
cs7 = "gets"
cs8 = "easier"

### Interact with the tool

Connect to the checksum generation tool using `pyserial`:

```
python -m serial.tools.miniterm /dev/<Tiva Port Name> 115200
```

Interact by following the prompts:
```
Type 'c' to enter 'checksum mode'.
Type a string to generate a checksum: test
String received: test
Bytes received: 74 65 73 74 
Checksum byte: 16 
```

### Checksum formula

The checksum byte is the result of xoring all string bytes together (ignoring the newline byte or null terminator byte)
```
0x74 ^ 0x65 ^ 0x73 ^ 0x74 = 0x16
```

### Debug the Program

#### `openocd`

`openocd` allows us to interface with the ICDI debugger

Install with `sudo apt install openocd` for linux/docker or `brew install open-ocd`

Run with:

Linux/Docker:
```
openocd -f /usr/share/openocd/scripts/board/ti_ek-tm4c123gxl.cfg
```

Mac:
```
openocd -f /opt/homebrew/share/openocd/scripts/interface/ti-icdi.cfg -f /opt/homebrew/share/openocd/scripts/board/ti_ek-tm4c123gxl.cfg
```

This opens a port for GDB to connect to.

#### `gdb`

`gdb` is the debugger tool we interface with

This should come installed with the `arm-none-eabi` toolchain we've been using

Run with:
`arm-none-eabi-gdb -ex "target extended-remote localhost:3333" <path to file to debug>.axf`

Reset the board with `monitor reset halt` inside GDB.

Load symbols using `load` inside GDB.

Break `main` function: `break main`

Continue to breakpoint: `continue`
