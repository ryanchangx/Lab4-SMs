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

enum STATES{WAIT, DOWN, UP, TRIGGER} state;
unsigned char order[4] = {4,1,2,1};
int i = 0;

void tick(){
    //next state
    switch(state){
        case WAIT:
            state = (PINA == order[0])? DOWN : WAIT;
            break;
        case DOWN:
            ++i;
            if(PINA == order[i]){
                state = WAIT;
                i = 0;
            }
            else{
                state = (i == 3)? TRIGGER : UP;
            }
            break;
        case UP:
            state = DOWN;
            state = (PINA == 0x00)? UP : state;
            break;
        case TRIGGER:
            state = WAIT;
            break;
    }
    //action at each state
    switch(state){
        case WAIT:
            PORTB = ((PINA >> 7) == 0x01)? 0x00 : PORTB;
            break;
        case DOWN:
            PORTB = ((PINA >> 7) == 0x01)? 0x00 : PORTB;
            break;
        case UP:
            PORTB = ((PINA >> 7) == 0x01)? 0x00 : PORTB;
            break;
        case TRIGGER:
            PORTB = (PORTB == 0x01)? 0x00: 0x01;
            break;
    }
}

int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0x00; PORTA = 0x00;
    DDRB = 0xFF; PORTB = 0x00;
    /* Insert your solution below */
    state = WAIT;
    while (1) {
        tick();
    }
    return 1;
}
