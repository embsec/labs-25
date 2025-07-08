# Insecure Bootloader Development Guide

Installation and development guide for a basic bootloader. The development of this bootloader will serve as a starting point for the design project.

Lab 2 requires you to implement a very basic bootloader and fw_update tool. Later on, during the design challenge, you will want to address certain vulnerabilities in this Lab 2. For now though, implement the `load_firmware` function in `booloader.c` and `update_firmware` function in `fw_update.py` to create a functional bootloader system. This lab does not have a flag.

# Project Structure
```
├── bootloader *
│   ├── bin
│   │   ├── bootloader.bin
│   ├── src
│   │   ├── bootloader.c
│   │   ├── startup_gcc.c
│   ├── bootloader.ld
│   ├── Makefile
├── firmware
│   ├── bin
│   │   ├── firmware.bin
│   ├── lib
│   ├── src
├── lib
│   ├── driverlib
│   ├── inc
│   ├── uart
├── tools *
│   ├── bl_build.py
│   ├── fw_update.py
│   ├── util.py
├── README.md

Directories marked with * are not fully implemented
```

## Bootloader

The `bootloader` directory contains source code that is compiled and loaded onto the TM4C (Tiva) microcontroller. The bootloader manages which firmware can be updated to the Tiva. When connected to the `fw_update` tool, the bootloader accepts a new firmware.

The bootloader will then hand over control to the firmware.

If no update is available, the bootloader simply hands control to the current firmware.

## Tools

There are two Python scripts in the `tools` directory:

1. `bl_build.py`: Provision the bootloader
3. `fw_update.py`: Update the firmware to a TM4C with a provisioned bootloader

### `bl_build.py`

This script calls `make` in the `bootloader` directory. It is used to create a new bootloader module binary for a new Tiva deployment.

### `fw_update.py`

This script communicates with a bootloader over serial to provide a firmware bundle.

# Setting Up a Deployment

## Building and Flashing the Bootloader

1. Enter the `tools` directory and run `bl_build.py`

```
cd ./tools
python bl_build.py
```

2. Flash the bootloader using `lm4flash` tool
   
```
sudo lm4flash ../bootloader/bin/bootloader.bin
```

This loads the bootloader module onto the Tiva. Next, the initial firmware must be installed.

## Bundling and Updating Firmware

1. Enter the firmware directory and `make` the example firmware.

```
cd ./firmware
make
```

2. Reset the TM4C by pressig the RESET button

3. Run `fw_update.py`

```
python fw_update.py --firmware ../firmware/bin/firmware.bin
```

## Interacting with the Bootloader

Using `pyserial` module:

```
python -m serial.tools.miniterm /dev/ttyACM0 115200
```

You should first see the bootloader serial interface:

```
Welcome to the BWSI Vehicle Update Service!
Send "U" to update, and "B" to run the firmware.
```

Type 'B' to boot the loaded firmware.

You should then see the firmware's MITRE CAR diagnostics interface:

```
  __  __ _____ _______ _____  ______    _____          _____
 |  \/  |_   _|__   __|  __ \|  ____|  / ____|   /\   |  __ \
 | \  / | | |    | |  | |__) | |__    | |       /  \  | |__) |
 | |\/| | | |    | |  |  _  /|  __|   | |      / /\ \ |  _  /
 | |  | |_| |_   | |  | | \ \| |____  | |____ / ____ \| | \ \
 |_|  |_|_____|  |_|  |_|  \_\______|  \_____/_/    \_\_|  \_\

 (    (                      )    )  (         (         (
 )\ ) )\ )   (     (      ( /( ( /(  )\ ) *   ))\ )  (   )\ )
(()/((()/(   )\    )\ )   )\()))\())(()/` )  /(()/(  )\ (()/(
 /(_))/(_)((((_)( (()/(  ((_)\((_)\  /(_)( )(_)/(_)(((_) /(_))
(_))_(_))  )\ _ )\ /(_))_ _((_) ((_)(_))(_(_()(_)) )\___(_))
 |   |_ _| (_)_\(_(_)) __| \| |/ _ \/ __|_   _|_ _((/ __/ __|
 | |) | |   / _ \   | (_ | .` | (_) \__ \ | |  | | | (__\__ \
 |___|___| /_/ \_\   \___|_|\_|\___/|___/ |_| |___| \___|___/

Type "HELP" for a listing of commands.

->MITRE Car Diagnotics System Commands:
 * HELP - This message
 * EMISSIONS - Query emissions system status
 * SAFETY - Query safety system status
 * INFOTAINMENT - Query information/entertainment system status
 * SECURITY - Query cybersecurity system status
 * FLAG - ???
```
