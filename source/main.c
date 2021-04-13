/*	Author: ryan
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
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
            if(PORTB == 0x02)
                PORTB = tmpB >> 1;
            else
                PORTB = tmpB << 1;
            state = UP;
            break;
        case UP:
            if(PINA == 0x00)
                state = WAIT;
            break;
        case WAIT:
            if(PINA == 0x01)
                state = DOWN;
            break;
        default:
            state = WAIT;
    }
    
}

int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0x00; PORTA = 0x00;
    DDRB = 0X03; PORTB = 0x01;
    /* Insert your solution below */
    while (1) {
        tick();
    }
    return 1;
}
