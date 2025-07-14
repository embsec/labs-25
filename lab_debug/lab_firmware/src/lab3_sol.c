#include <stdbool.h>
#include <stdint.h>
#include <string.h>

// Hardware Imports
#include "inc/hw_memmap.h"    // Peripheral Base Addresses
#include "inc/hw_types.h"     // Boolean type
#include "inc/tm4c123gh6pm.h" // Peripheral Bit Masks and Registers
// #include "inc/hw_ints.h" // Interrupt numbers

// Driver API Imports
#include "driverlib/flash.h"     // FLASH API
#include "driverlib/interrupt.h" // Interrupt API
#include "driverlib/sysctl.h"    // System control API (clock/reset)

// Application Imports
#include "driverlib/gpio.h"
#include "uart/uart.h"

// Forward declarations
void loop(void);
uint8_t compute_checksum(uint8_t*, int);
uint8_t read_pkt(void);
void uart_write_hex_bytes(uint8_t, uint8_t* , uint32_t);

int main(void) {
    initialize_uarts(UART0);    // Don't forget to initialize uarts!
    while (1) {
        loop();
    }
}

uint8_t compute_checksum(uint8_t* data, int len) {  // Return a byte, data should be pointer to bytes
    uint8_t check_byte = 0x00;
    for (int i = 0; i < len; i++) {     // Dont count too high
        check_byte = check_byte ^ data[i];
    }
    return check_byte;  // Return value, not pointer
}

uint8_t read_pkt(void) {
    uint8_t data[100];  // This must be small enough to fit on stack
    int resp;
    uint32_t cursor = 0;

    // Read until newline
    do {
        data[cursor] = uart_read(UART0, BLOCKING, &resp);   // Don't use addr of resp, use resp (writes to addr 0)
        uart_write(UART0, data[cursor++]); // Append ++, not prepend
    }
    while(data[cursor - 1] != '\n');    // Check curser - 1, check for newline
    data[cursor - 1] = '\0'; // Add null terminator, use prepended ++
    int data_len = strlen((char*) data) - 1;

    // Compute checksum for string
    uint8_t check_sum_byte = compute_checksum(data, data_len);    // Don't include newline in checksum calc
    
    // Print result:
    uart_write_str(UART0, "String received: ");
    data[cursor] = '\0'; // Add null terminator, use prepended ++
    uart_write_str(UART0, (char*) data);
    nl(UART0);

    uart_write_str(UART0, "Bytes received: ");
    uart_write_hex_bytes(UART0, data, data_len);
    nl(UART0);

    uart_write_str(UART0, "Checksum byte: ");
    uart_write_hex_bytes(UART0, &check_sum_byte, 1); // Use pointer to checksum byte
    nl(UART0);

    return check_sum_byte;
}

void loop(void) {
    int resp;

    uart_write_str(UART0, "Type 'c' to enter 'checksum mode'.\n");
    uint32_t instruction = uart_read(UART0, BLOCKING, &resp);

    // Receive packet to generate checksum
    if (instruction == 'c') {
        uart_write_str(UART0, "Type a string to generate a checksum: ");
        read_pkt();
    }   
}

/*
 * Utility function to write bytes as human readable hex from a buffer
 * USE FOR DEBUG PURPOSES ONLY
 */
void uart_write_hex_bytes(uint8_t uart, uint8_t * start, uint32_t len) {
    for (uint8_t * cursor = start; cursor < (start + len); cursor += 1) {
        uint8_t data = *((uint8_t *)cursor);
        uint8_t right_nibble = data & 0xF;
        uint8_t left_nibble = (data >> 4) & 0xF;
        char byte_str[3];
        if (right_nibble > 9) {
            right_nibble += 0x37;
        } else {
            right_nibble += 0x30;
        }
        byte_str[1] = right_nibble;
        if (left_nibble > 9) {
            left_nibble += 0x37;
        } else {
            left_nibble += 0x30;
        }
        byte_str[0] = left_nibble;
        byte_str[2] = '\0';

        uart_write_str(uart, byte_str);
        uart_write_str(uart, " ");
    }
}