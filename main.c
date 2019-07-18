/*
 * File:   main.c
 * Author: Navindu Dananga
 *
 * Created on June 9, 2019, 7:51 PM
 */

#define _XTAL_FREQ 4000000


// PIC16F877 Configuration Bit Settings

// 'C' source line config statements

// CONFIG
#pragma config FOSC = XT        // Oscillator Selection bits (XT oscillator)
#pragma config WDTE = OFF     // Watchdog Timer Enable bit (WDT enabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config CP = OFF         // FLASH Program Memory Code Protection bits (Code protection off)
#pragma config BOREN = OFF          // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP = OFF        // Low Voltage In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EE Memory Code Protection (Code Protection off)
#pragma config WRT = OFF        // FLASH Program Memory Write Enable (Unprotected program memory may not be written to by EECON control)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#define RS RD2
#define EN RD3
#define D4 RD4
#define D5 RD5
#define D6 RD6
#define D7 RD7

#include <xc.h>
#include "lcd.h"
#include <stdio.h>
#include <string.h>

char votes[16];

void main(void) {
    TRISB = 0xFF;
    TRISD = 0x00;
    TRISC = 0x00;
    PORTB = 0x00;
    PORTC = 0x00;
    
    PORTCbits.RC0 = 1; //power indicator
    PORTDbits.RD0 = 0;
    int accessToVote = 0;  //rb0
    int ttlVotesOf_A = 0;  //rb1
    int ttlVotesOf_B = 0;  //rb2
    int ttlVotesOf_C = 0;  //rb3
    
    Lcd_Init();
    Lcd_Set_Cursor(1,1);
    Lcd_Write_String(" Voting System ");
    __delay_ms(1000);
    Lcd_Clear();
    sprintf(votes, "  A:%d B:%d C:%d", ttlVotesOf_A, ttlVotesOf_B, ttlVotesOf_C);
    Lcd_Set_Cursor(1,1);
    Lcd_Write_String(votes); 
   
    
    while(1){
        if(PORTBbits.RB0 == 1) {
            accessToVote = 1;
        }
        int pressBtnOf_A = (PORTBbits.RB1 == 1) && (PORTBbits.RB2 == 0) && (PORTBbits.RB3 == 0);
        int pressBtnOf_B = (PORTBbits.RB1 == 0) && (PORTBbits.RB2 == 1) && (PORTBbits.RB3 == 0); 
        int pressBtnOf_C = (PORTBbits.RB1 == 0) && (PORTBbits.RB2 == 0) && (PORTBbits.RB3 == 1); 
        
        if(accessToVote){
            PORTDbits.RD1 = 1;
            Lcd_Set_Cursor(2,1);
            Lcd_Write_String("You Can Vote Now"); 
            if(pressBtnOf_A){
                PORTDbits.RD0 = 1;
                PORTCbits.RC1 = 1;
                ttlVotesOf_A += 1;
                accessToVote = 0;
                Lcd_Set_Cursor(2,1);
                Lcd_Write_String("Thanks for Vote ");
                __delay_ms(500);
                PORTCbits.RC1 = 0;
            }
            if(pressBtnOf_B){
                PORTDbits.RD0 = 1;
                PORTCbits.RC2 = 1;
                ttlVotesOf_B += 1;
                accessToVote = 0;
                Lcd_Set_Cursor(2,1);
                Lcd_Write_String("Thanks for Vote ");
                __delay_ms(500);
                PORTCbits.RC2 = 0;
            }
            if(pressBtnOf_C){
                PORTDbits.RD0 = 1;
                PORTCbits.RC3 = 1;
                ttlVotesOf_C += 1;
                accessToVote = 0;
                Lcd_Set_Cursor(2,1);
                Lcd_Write_String("Thanks for Vote ");
                __delay_ms(500);
                PORTCbits.RC3 = 0;
            }
            sprintf(votes, "A:%d B:%d C:%d", ttlVotesOf_A, ttlVotesOf_B, ttlVotesOf_C);
            int a = strlen(votes);
            int y = (16 - a > 0)? (16 - a)/2 + 1 : 1; 
            Lcd_Set_Cursor(1,y);
            Lcd_Write_String(votes); 
        }else{ 
            PORTDbits.RD0 = 0;
            PORTDbits.RD1 = 0;
            Lcd_Set_Cursor(2,1);
            Lcd_Write_String(" Access denied ");
        }
    }
}
