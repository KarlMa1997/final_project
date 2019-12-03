#ifndef PLAYERMOVEMENT_H
#define PLAYERMOVEMENT_H

#include "customChar.h"
#include "io.h" 

#define R (~PINA & 0x10) 
#define D (~PINA & 0x04) 
#define ROW1_BEGIN 1
#define ROW2_BEGIN 17

unsigned char inMenu;

unsigned long playerMovementPeriod = 50;
unsigned long ms250 = 5;

enum MovementFlag
{
    FALSE,
    TRUE
} dodging;

enum PlayerMovementStates
{
    WAIT,
    DODGE 
};

void spriteUpdate(unsigned char currSprite)
{
    LCD_Cursor(ROW1_BEGIN);
    LCD_WriteData(currSprite);
}

int playerMovementTick(int state)
{
    static unsigned long count = 0;
    static unsigned char sprite = 0; 

    switch(state)
    {
        case WAIT:
        {
            if(inMenu == 0)
            {
                if(D)
                {
                    state = DODGE; 

                    LCD_Cursor(ROW1_BEGIN);
                    LCD_WriteData(' ');
                }
                else
                {
                    state = WAIT; 
                }
            }
            break;
        }

        case DODGE:
        {
            if(D) 
            {
                state = DODGE; 
            }
            else
            {
                state = WAIT;
           
                LCD_Cursor(ROW2_BEGIN);
                LCD_WriteData(' ');
                LCD_Cursor(ROW1_BEGIN);
                LCD_WriteData(PL_STATIONARY);
            }

            break;
        }
    }

    switch(state)
    {
        case WAIT: 
        {
            count = 0; 
            dodging = FALSE;
            
            break;
        }

        case DODGE:
        {
            dodging = TRUE;
            
            LCD_Cursor(ROW2_BEGIN);
            LCD_WriteData(PL_KNEEL);

            break;
        }
    }

    return state;
}

#endif
