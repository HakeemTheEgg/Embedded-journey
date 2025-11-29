#include <stdio.h>
#include <stdint.h>

typedef struct {
    volatile uint8_t DIR;
    volatile uint8_t OUT;
    volatile uint8_t IN;
    volatile uint8_t PORT;
}dio_port_t;

dio_port_t SIMULATED_PORT_B;

void pin_mode(dio_port_t *port, uint8_t pin, uint8_t direction);
void digital_write(dio_port_t *port, uint8_t pin, uint8_t value);
uint8_t digital_read(dio_port_t *port, uint8_t pin);





int main(void) {
    SIMULATED_PORT_B.DIR = 0;
    SIMULATED_PORT_B.OUT = 0;
    SIMULATED_PORT_B.IN = 0x0A;

    printf("Initial state:\n");
    printf("DIR: 0x%02X, OUT: 0x%02X, IN: 0x%02X\n",
           SIMULATED_PORT_B.DIR, SIMULATED_PORT_B.OUT, SIMULATED_PORT_B.IN);


    pin_mode(&SIMULATED_PORT_B, 5, 1);
    digital_write(&SIMULATED_PORT_B, 5, 1);


    pin_mode(&SIMULATED_PORT_B, 2, 0);
    uint8_t pin_state = digital_read(&SIMULATED_PORT_B, 2);

    printf("\nAfter configuration:\n");
    printf("DIR: 0x%02X, OUT: 0x%02X, IN: 0x%02X\n",
           SIMULATED_PORT_B.DIR, SIMULATED_PORT_B.OUT, SIMULATED_PORT_B.IN);
    printf("State of pin 2: %d\n", pin_state);


    uint8_t pin1_state = digital_read(&SIMULATED_PORT_B, 1);
    printf("State of pin 1: %d\n", pin1_state);

    return 0;

}

void pin_mode(dio_port_t *port, uint8_t pin, uint8_t direction) {
    if (direction == 1) {
        port->DIR |= (1<<pin);
    }
    else {
        port->DIR &= ~(1<<pin);
    }
}
void digital_write(dio_port_t *port, uint8_t pin, uint8_t value) {
    if (value == 1) {
        port->OUT |= (1<<pin);
    }
    else {
        port->OUT &= ~(1<<pin);
    }
}
uint8_t digital_read(dio_port_t *port, uint8_t pin) {
    if (port->IN & (1<<pin)) {
        return 1;
    }
    else {
        return 0;
    }
}
