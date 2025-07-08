# Embsec Labs 2025

This is your personal lab repository. Each day, when we post new labs, you will get a Github pull-request. Accept the PR, then run `git pull` inside this repository. This will fetch each day's lab package.

## Lab Packages

Each lab contains the following:

1. `lab.bin`: The lab binary to flash to the Tiva

2. `starter.ipynb` or `starter.py`: Python host tool, you will write code here

3. `README.md`: This is the lab description, it contains instructions for collecting the lab flag

## Flags

Flags generally take a form similar to:

`embsec{name_of_lab_<random characters>}`

Typically, this flag will get read out over serial, so make sure your host tool (`starter.py`) is configured to read serial and prints out received data.


