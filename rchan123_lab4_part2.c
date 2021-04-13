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

enum STATES{INC_DOWN, INC_UP, DEC_DOWN, DEC_UP, RESET, WAIT} state;
void tick(){
    unsigned char tmpC = PORTC;
    unsigned char a0 = ((PINA & 0x01) == 0x01)? 1 : 0;
    unsigned char a1 = ((PINA & 0x02) == 0x02)? 1 : 0;
    switch(state){
        //next state
        case INC_DOWN:
            state = INC_UP;
            state = (!a0 && a1)? DEC_DOWN : state;
            state = (a1 && a0)? RESET : state;
            break;
        case INC_UP:
            state = (a0)? INC_UP : WAIT;
            state = (a1 && a0)? RESET : state;
            break;
        case DEC_DOWN:
            state = DEC_UP;
            state = (!a1 && a0)? INC_DOWN : state;
            state = (a1 && a0)? RESET : state;
            break;
        case DEC_UP:
            state = (a1)? DEC_UP : WAIT;
            state = (a1 && a0)? RESET : state;
            break;
        case RESET:
            state = (a1 && a0)? RESET : WAIT;
            break;
        case WAIT: 
            state = (a1)? DEC_DOWN : WAIT;
            state = (a0)? INC_DOWN : state;
            state = (a1 && a0)? RESET : state;
            break;
    }
    //action at each state
    switch(state){
        case INC_DOWN:
            if(tmpC < 9)
                ++tmpC;
            PORTC = tmpC;
            break;
        case INC_UP:
            break;
        case DEC_DOWN:
            if(tmpC > 0)
                --tmpC;
            PORTC = tmpC;
            break;
        case DEC_UP:
            break;
        case RESET:
            PORTC = 0;
            break;
        case WAIT:
            break;
    }
}

int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0x00; PORTA = 0x00;
    DDRC = 0xFF; PORTC = 0x07;
    /* Insert your solution below */
    state = WAIT;
    while (1) {
        tick();
    }
    return 1;
}
