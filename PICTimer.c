#include <stdio.h>
#include <stdlib.h>

#define TMR0 256
#define TMR1 65536

void setTimer(float delay, int fosc);

int main(void){

    float delay = 0.0; 
    int freq = 0, run = 1;
    char c = ' ';

    do{
        printf("\nDelay(s): ");
		fflush(stdin);
        if (scanf("%f", &delay) != 1){
            printf("Abort.");
            exit(1);
        }

        printf("Frequency(MHz): ");
		fflush(stdin);
        if (scanf("%d", &freq) != 1){
            printf("Abort.");
            exit(1);
        }
        
        setTimer(delay, freq);

        printf("\nContinue? [Y/n] ");
        fflush(stdin);
        c = getchar();
        if (c == 'n' || c == 'N')
            run = 0;
    } while (run);
    
    return 0;
}

void setTimer(float delay, int fosc){
    
    int val = 0, y = 0x100, TMR1H = 0x00, TMR1L = 0x00; 
    int presc0[8] = {2,4,8,16,32,64,128,256}, presc1[4] = {1,2,4,8}; 

    for (int i = 0; i < 8; i++){
        val = (int)((TMR0-((delay * fosc)/(presc0[i]*4)))+0.5f);
        if (val > 0){
            printf("\nTimer0:\n\tTMR0= %d;\n\tOPTION_REG= 0x%X;  | (%d)", val, presc0[i], presc0[i]);
            break;
        }
    }
    
    for (int i = 0; i < 4; i++){
        val = (int)((TMR1-((delay * fosc)/(presc1[i]*4)))+0.5f);
        if (val > 0){
            TMR1H = val / y;
            TMR1L = val % y;
            printf("\nTimer1:\n\tTMR1H= 0x%X;\n\tTMR1L= 0x%X;\n\tT1CON= 0x%X;  | (%d)", TMR1H, TMR1L, presc1[i], presc1[i]);
            break;
        }
    }   
    if (val <= 0){
        printf("\nError.");
    }
}