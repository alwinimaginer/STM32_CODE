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
#define PIN3        (1 << 3)


void delay(void)
{
    for(volatile int i = 0; i < 500000; i++);
}

int main(void)
{
    // 1. Enable GPIOA clock
    RCC_APB2ENR |= IOPAEN;

    // 2. Configure PA6, PA7 and PA3 as output

    // Clear bits for PA3 (EXTERNAL)
        GPIOA_CRL &= ~(0xF << 12);

      // Set PA3 as output push-pull
        GPIOA_CRL |= (0x2 << 12);

    // Clear bits for PA7 (EXTERNAL)
       GPIOA_CRL &= ~(0xF << 28);

       // Set PA7 as output push-pull
       GPIOA_CRL |= (0x2 << 28);


    // Clear bits for PA6 (EXTERNAL)
    GPIOA_CRL &= ~(0xF << 24);

    // Set PA6 as output push-pull
    GPIOA_CRL |= (0x2 << 24);



    while(1)
    {

     // Toggle PA3(EXTERNAL) D0
     GPIOA_ODR ^= PIN3;

     delay();

     GPIOA_ODR ^= PIN3;


     // Toggle PA6(EXTERNAL) D12
     GPIOA_ODR ^= PIN6;

     delay();

     GPIOA_ODR ^= PIN6;


     // Toggle PA7(EXTERNAL) D11
     GPIOA_ODR ^= PIN7;

     delay();

     GPIOA_ODR ^= PIN7;


    }
}
