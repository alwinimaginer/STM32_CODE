#include<stdint.h>
#include<stdio.h>

#define RCC_APB2ENR (*(volatile uint32_t*) 0x40021018)

typedef struct {
	volatile uint32_t CRL; // offset : 0x00
	volatile uint32_t CRH; // offset : 0x04
	volatile uint32_t IDR; // offset : 0x08
	volatile uint32_t ODR; // offset : 0x0C
}GPIOA_typedef;

#define GPIOA ((GPIOA_typedef*) 0x40010800) // GPIOA points the struct
#define IOPAEN      (1 << 2)   // enable clock
#define LED_PIN0    (1 << 5)   // PA5 - RED    -D13  - red   wire
#define LED_PIN1    (1 << 6)   // PA6 - YELLOW -D12  - brown wire
#define LED_PIN2    (1 << 7)   // PA7 - GREEN  -D11  - green wire


typedef enum {                 // enum for different states of light
	RED,
	YELLOW,
	GREEN
}trafficstate;

void delay(void){
	volatile uint32_t i;
	for(i = 0; i < 50000; i ++);
}

void red_led(){
	GPIOA->ODR &= ~(LED_PIN1|LED_PIN2);
	GPIOA->ODR |= LED_PIN0;
}

void yellow_led(){
	GPIOA->ODR &= ~(LED_PIN0|LED_PIN2);
	GPIOA->ODR |= LED_PIN1;
}

void green_led(){
	GPIOA->ODR &= ~(LED_PIN0|LED_PIN1);
	GPIOA->ODR |= LED_PIN2;
}

int main(){
    // enble clock for bus 2
     RCC_APB2ENR |= IOPAEN;
	// PA5 OUTPUT - bits 23,22,21,20
	// 20,21 - mode , 22,23 - CNF
	 GPIOA->CRL &= ~(0xF << 20);
    // 20,21 - 10: Output mode, max speed 2 MHz.
    // In output mode (MODE[1:0] > 00):
	// 22,23 - 00: General purpose output push-pull
	 GPIOA->CRL |=  (0x2 << 20);

	// PA6 OUTPUT - bits 24,25,26,27
    // 24,25 - mode , 26,27 - CNF
	 GPIOA->CRL &= ~(0xF << 24);
	// 24,25 - 10: Output mode, max speed 2 MHz.
	// In output mode (MODE[1:0] > 00):
	// 26,27 - 00: General purpose output push-pull
	 GPIOA->CRL |=  (0x2 << 24);

	// PA7 OUTPUT - bits 28,29,30,31
	// 28,29 - mode , 30,31 - CNF
	 GPIOA->CRL &= ~(0xF << 28);
	// 28,29 - 10: Output mode, max speed 2 MHz.
	// In output mode (MODE[1:0] > 00):
	// 30,31 - 00: General purpose output push-pull
	 GPIOA->CRL |=  (0x2 << 28);

	trafficstate state = RED; // initialize the status of the light

	while(1){
		switch(state){
		case RED:
			printf("RED Light\n");
			red_led();
			state = YELLOW;
			break;

		case YELLOW:
			printf("YELLOW Light\n");
			yellow_led();
			state = GREEN;
			break;

		case GREEN:
		    printf("GREEN Light\n");
		    green_led();
			state = RED;
			break;

		}
		delay();
	}
}
