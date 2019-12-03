#ifndef TIME_H
#define TIME_H

#include <avr/io.h>
#include <avr/interrupt.h>

volatile unsigned char TimerFlag = 0;

unsigned long _avr_timer_M = 1; 
unsigned long _avr_timer_cntcurr = 0;

typedef struct _Task
{
    int state;
    unsigned long period;
    unsigned long elapsedTime;
    int (*TickFct) (int);
} Task;

void TimerISR();

void TimerOn()
{

    TCCR1B = 0x0B;
    OCR1A = 125;
    TIMSK1 = 0x02;
    TCNT1 = 0;

    _avr_timer_cntcurr = _avr_timer_M;
    SREG |= 0x80;
}

void TimerOff()
{
    TCCR1B = 0x00;
}

ISR(TIMER1_COMPA_vect)
{
    _avr_timer_cntcurr--;
    if(_avr_timer_cntcurr == 0)
    {
        TimerISR();
        _avr_timer_cntcurr = _avr_timer_M;
    }
}

void TimerSet(unsigned long M)
{
    _avr_timer_M = M;
    _avr_timer_cntcurr = _avr_timer_M;
}

#endif

