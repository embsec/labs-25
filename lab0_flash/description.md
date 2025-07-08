# Lab 0: Flashing the Tiva

This challenge introduces the concept of flashing a lab to the board. You must load lab firmware (lab.bin) onto the Tiva in order to execute a lab. Later labs will include a host tool component. This lab can be completed by flashing the firmware successfully. 

## Background

Required tools:

- `lm4flash`

This tool is available on Unix systems, and in the Docker dev environment.

### Flash a binary to the Tiva:

With the Tiva connected:

`sudo lm4flash path/to/binary.bin` In this case, the relative path to the binary provided you are in the flash_example folder will simply be 'challenge.bin'.

Tip: You can check the connection to the board with `ls /dev`. It will likely show up as something like 'ttyACM0'. If you are not sure which port corresponds to the Tiva board, with the board unlugged from your laptop, run `ls /dev` in a terminal. It will show the list of ports. Connect the board and run `ls /dev` again. There should be one new port listed and that corresponds to your Tiva board.

# Exercise 1: Flashing a Binary File to the Tiva Board

Flash `lab.bin` to the board using `lm4flash`. Submit the flag to your personal discord channel in the format `embsec{flash_lab_<flag>}`

You will get `<flag>` after flashing the lab.
