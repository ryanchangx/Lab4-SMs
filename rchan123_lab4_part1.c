/*	Author: Ryan Chang
 *  Partner(s) Name: 
 *	Lab Section: 023
 *	Assignment: Lab 4 Exercise 1
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum STATES{DOWN, UP, WAIT} state;
void tick(){
    unsigned char tmpB = PORTB;
    switch(state){
        case DOWN:
            state = UP;
            break;
        case UP:
            state = (PINA == 0x01)? UP : WAIT;
            break;
        case WAIT:
            state = (PINA == 0x01)? DOWN : WAIT;
            break;
    }
    switch(state){
        case DOWN:
            PORTB = (tmpB == 0x02)? 0x01 : 0x02;
            break;
        case UP:
            break;
        case WAIT:
            break;
    }
    
}

int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0x00; PORTA = 0x00;
    DDRB = 0xFF; PORTB = 0x01;
    /* Insert your solution below */
    state = WAIT;
    while (1) {
        tick();
    }
    return 1;
}
