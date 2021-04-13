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

enum STATES{LOCKED, POUND_DOWN, POUND_UP, UNLOCKED} state;
void tick(){
    //next state
    switch(state){
        case LOCKED:
            state = (PINA == 0x04)? POUND_DOWN : LOCKED;
            state = ((PINA >> 7) == 0x01)? LOCKED : state;
            break;
        case POUND_DOWN:
            state = (PINA == 0x04)? POUND_DOWN : LOCKED;
            state = (PINA == 0x00)? POUND_UP : state;
            state = ((PINA >> 7) == 0x01)? LOCKED : state;
            break;
        case POUND_UP:
            state = (PINA == 0x00)? POUND_UP : state;
            state = (PINA = 0x02)? UNLOCKED : state;
            state = ((PINA >> 7) == 0x01)? LOCKED : state;
            break;
        case UNLOCKED:
            state = ((PINA >> 7) == 0x01)? LOCKED : state;
            break;
    }
    //action at each state
    switch(state){
        case LOCKED:
            PORTB = 0x00;
            break;
        case POUND_DOWN:
            break;
        case POUND_UP:
            break;
        case UNLOCKED:
            PORTB = 0x01;
            break;
    }
}

int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0x00; PORTA = 0x00;
    DDRB = 0xFF; PORTB = 0x07;
    /* Insert your solution below */
    state = LOCKED;
    while (1) {
        tick();
    }
    return 1;
}
