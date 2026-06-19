#include <stdint.h>

// RCC register - to enable the clock for pins to work

#define RCC_APB2ENR (*(volatile uint32_t*)0x40021018)

// GPIOA registers

// GPIOA_CRL - Configuration Register Low
//Controls
//PA0 PA1 PA2 PA3 PA4 PA5 PA6 PA7
#define GPIOA_CRL   (*(volatile uint32_t*)0x40010800)

//GPIOA_CRH - Configuration Register High
//Controls
//PA8 PA9 PA10 PA11 PA12 PA13 PA14 PA15
#define GPIOA_CRH   (*(volatile uint32_t*)0x40010804)

// GPIOA_IDR  - Input Data Register ( Read only operation - button press)
#define GPIOA_IDR   (*(volatile uint32_t*)0x40010808)

// GPIOA_ODR - Output Data Register ( write operation - LED lighting )
#define GPIOA_ODR   (*(volatile uint32_t*)0x4001080C)

// Bit positions
#define IOPAEN      (1 << 2)   // enable clock
#define LED_PIN     (1 << 6)   // PA6
#define BUTTON_PIN  (1 << 8)   // PA8

void delay(void){
	for(volatile int i = 0 ; i < 50000 ; i ++);
}
int main(void)
{
    // Enable GPIOA clock
	// Bit 2 IOPAEN: I/O port A clock enable
    RCC_APB2ENR |= IOPAEN;

    // PA6 OUTPUT - bits 24,25,26,27
    // 24,25 - mode , 26,27 - CNF
    GPIOA_CRL &= ~(0xF << 24);
    // 24,25 - 10: Output mode, max speed 2 MHz.
    // In output mode (MODE[1:0] > 00):
    // 26,27 - 00: General purpose output push-pull
    GPIOA_CRL |=  (0x2 << 24);

    // PA8 INPUT PULL-UP - bits 0,1,2,3
    // 0,1 - mode , 2,3 - CNF
    GPIOA_CRH &= ~(0xF << 0);
    // 0,1 - 00: Input mode (reset state)
    // 2,3 - 10: Input with pull-up
    GPIOA_CRH |=  (0x8 << 0);

    // Enable internal 1-pull-up/ 0-pull-down
    // button released - PA8 = HIGH(1)
    // button pressed  - PA8 = LOW(0)
    GPIOA_ODR |= BUTTON_PIN;

    while(1)
    {
        if(!(GPIOA_IDR & BUTTON_PIN))
        {
            GPIOA_ODR ^= LED_PIN;

            // debounce
            for(volatile int i=0;i<100000;i++);

            // wait for release
            while(!(GPIOA_IDR & BUTTON_PIN));
        }
    }

}
