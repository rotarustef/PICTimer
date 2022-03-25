# PIC timer with interrupt

### This is a simple program written for PIC16F1937 microcontroller that can calculate a delay, but with a few modifications can be used for any PIC.

***

##  How does it work

### The formula is 
```
TMR_MAX_VAL-((Delay * Fosc)/(Presc*4))
```
### This PIC16F1937 has two timers (TMR0, TMR1). TMR0 is an 8 bit timer register that can count from 0 to 255 and TMR1 is a 16 bit timer register that can count from 0 to 65535.

### For a timer to start counting it needs to have a clock. The microcontroller simply count in sync with the clock, so for a clock signal with the frequency of 4MHz we have 4000000 ticks per second. When the timer register exceeds the maximum value it again starts from 0. 

### Using an interrupt, every time a timer register restarts, a function called Interrupt Service Routine (ISR) starts executing.

### Because I used an internal clock the microcontroller divides the frequency of 4MHz by 4 and the result is 1MHz. After this we can use a prescaler to skip a certain number of microcontroller clock ticks (it will increment a timer every 2, 8, 16 ticks).

***

## Example

### Let's say that we want to make a LED blink 50ms. To achieve this delay we need to tell the microcontroller when 50ms has passed to light up the LED. 

### The PIC microcontroller has a register called OSCCON. In this register we can set a specific clock frequency (internal/external). I set an internal frequency of 4MHz which will be devide by 4 leaving us with 1MHz.

### For a 50ms delay in 1MHz the ticks will be:
```
50*10^-3 * 10^6 = 50000 ticks
```

### For this exemple I will use Timer0. Because this timer conuts 256 ticks, we need to use a prescaler to *skip* some ticks.

### To use a prescaler for Timer0 we will need to set the OPTION_REG register. This PIC has this values (2, 4, 8, 16, 32, 64, 128, 256).

### If we set the prescaler to 128 the result will be bigger than 256 and we need to find another value:
```
50000/128 ~= 390
```

### The appropriate value is 256:
```
50000/256 ~= 195
```

### The timer will count up to 195 in 50 ms, but to achieve the end result we need to subtract the value from 256 so that the timer will cout only 195 ticks.
```
256 - 195 = 61
```
### This value needs to bee assigned to TMR0 for the timer to be complete.
