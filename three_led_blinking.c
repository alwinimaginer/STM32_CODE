 #include <stdint.h>

// RCC register
#define RCC_APB2ENR (*(volatile uint32_t*)0x40021018)

// GPIOA registers
#define GPIOA_CRL   (*(volatile uint32_t*)0x40010800)
#define GPIOA_ODR   (*(volatile uint32_t*)0x4001080C)

// Bit positions
#define IOPAEN      (1 << 2)
#define PIN7        (1 << 7)
#define PIN6        (1 << 6)
#define PIN5        (1 << 5)


void delay(void)
{
    for(volatile int i = 0; i < 500000; i++);
}

int main(void)
{
    // 1. Enable GPIOA clock
    RCC_APB2ENR |= IOPAEN;

    // 2. Configure PA5 and PA6 as output

    // Clear bits for PA7 (EXTERNAL)
       GPIOA_CRL &= ~(0xF << 28);

       // Set PA6 as output push-pull
       GPIOA_CRL |= (0x2 << 28);


    // Clear bits for PA6 (EXTERNAL)
    GPIOA_CRL &= ~(0xF << 24);

    // Set PA6 as output push-pull
    GPIOA_CRL |= (0x2 << 24);

    // Clear bits for PA5 (LED1)
     GPIOA_CRL &= ~(0xF << 20);

    // Set PA5 as output push-pull
    GPIOA_CRL |= (0x2 << 20);

    while(1)
    {

     // Toggle PA5(LED1)
     GPIOA_ODR ^= PIN5;

     delay();

     // Toggle PA6(EXTERNAL)
     GPIOA_ODR ^= PIN6;

     delay();


     // Toggle PA7(EXTERNAL)
     GPIOA_ODR ^= PIN7;

     delay();

    }
}
