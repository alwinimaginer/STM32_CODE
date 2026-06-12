#include <stdint.h>

// RCC register
#define RCC_APB2ENR (*(volatile uint32_t*)0x40021018)

// GPIOA registers
#define GPIOA_CRL   (*(volatile uint32_t*)0x40010800)
#define GPIOA_CRH   (*(volatile uint32_t*)0x40010804)
#define GPIOA_IDR   (*(volatile uint32_t*)0x40010808)
#define GPIOA_ODR   (*(volatile uint32_t*)0x4001080C)

// Bit positions
#define IOPAEN      (1 << 2)

#define LED_PIN     (1 << 6)   // PA6
#define BUTTON_PIN  (1 << 8)   // PA8

int main(void)
{
    // Enable GPIOA clock
    RCC_APB2ENR |= IOPAEN;

    // PA6 OUTPUT

    GPIOA_CRL &= ~(0xF << 24);
    GPIOA_CRL |=  (0x2 << 24);

    // PA8 INPUT PULL-UP

    GPIOA_CRH &= ~(0xF << 0);
    GPIOA_CRH |=  (0x8 << 0);

    // Enable internal pull-up

    GPIOA_ODR |= BUTTON_PIN;

    while(1)
    {
        // Button pressed?
        if(!(GPIOA_IDR & BUTTON_PIN))
        {
            GPIOA_ODR |= LED_PIN;      // LED ON
        }
        else
        {
            GPIOA_ODR &= ~LED_PIN;     // LED OFF
        }
    }
}

