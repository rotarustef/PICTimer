/*
    This program is for PIC16F1937 and can be easily modified for any PIC
    Documentation: https://ww1.microchip.com/downloads/en/DeviceDoc/41364E.pdf

    OSCCON (set frequency) - page 81 
    OPTION_REG (set prescaler Timer0) - page 193 
    T1CON (set prescaler Timer1) - page 203
*/

#include <xc.h>

#define LED RD0

void uC_init(void);
void __interrupt() timer(void); 

void main(void) {
    uC_init();

    while(1){
        //  do something
    }
}

void uC_init(void){
    OSCCON = 0b01101011;    //  set the internal frequency to 4MHz
    TRISD = 0x00;           //  set all the pins on port D to be output
    ANSELD = 0x00;          //  set all the pins on port D to be digital
    PORTD = 0x00;           //  set all the pins on port D to LOW
    

    // ----- For Timer0 -----
    OPTION_REG = 0b00000111;    //  set the prescaler to 256
    TMR0IE = 1;                 //  Timer0 interrupt enable
    // ----------------------


    // ----- For Timer1 -----
    //T1CON = 0x01;             //  set the prescaler to 1
    //TMR0IE = 1;               //  Timer1 interrupt enable
    // ----------------------


    GIE = 1;                    //  Global Interrupt Enable bit enables all active interrupts
    PEIE = 1;                   //  Peripheral Interrupt Enable bit enables all active peripheral interrupts
}



// ----- For Timer0 -----
void __interrupt() timer(void){
    if(TMR0IF){     //  when the timer0 is reseted to 0 this flag will be true
        LED=~LED;   //  the LED on pin RD0 will change its state, from LOW to HIGH and vice versa
        TMR0 = 61;  //  set the timer to count 50ms
        TMR0IF = 0; //  exit from the interrupt
    }
}
// ----------------------


/*
// ----- For Timer1 -----
void __interrupt() timer(void){
    if(TMR1IF){         //  when the timer1 is reseted this flag will be true
        LED=~LED;       //  the LED on pin RD0 will change its state, from adsadas
        TMR1H = 0x3C;   //  the value for TMR1 is 15536 (0x3CB0), but because Timer1 is a 16 bit timer register and the PIC is working with 8 bit values, TMR1 is separated in the higher value and the lower value (TMR1H, TMR1L)
        TMR1L = 0xB0;   //  to write the value more easily I converted 15536 to hexadecimal 0x3CB0 and separated in half
        TMR1IF = 0;     //  exit from the interrupt
    }
}
// ----------------------
*/