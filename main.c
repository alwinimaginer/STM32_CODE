// stm32 LED blinking code forpractice

#include <stdint.h>

// RCC register
#define RCC_APB2ENR (*(volatile uint32_t*)0x40021018)

// GPIOA registers
#define GPIOA_CRL   (*(volatile uint32_t*)0x40010800)
#define GPIOA_ODR   (*(volatile uint32_t*)0x4001080C)

// Bit positions
#define IOPAEN      (1 << 2)
#define PIN5        (1 << 5)

void delay(void)
{
    for(volatile int i = 0; i < 5000000; i++);
}

int main(void)
{
    // 1. Enable GPIOA clock
    RCC_APB2ENR |= IOPAEN;

    // 2. Configure PA5 as output

    // Clear bits for PA5
    GPIOA_CRL &= ~(0xF << 20);

    // Set PA5 as output push-pull
    GPIOA_CRL |= (0x2 << 20);

    while(1)
    {
        // Toggle PA5
        GPIOA_ODR ^= PIN5;

        delay();
    }
}
