#include<stdint.h>

#define BASE_PERIPHERAL_ADDR 			(0x40000000UL)
#define AHB1_PERIPHERAL_OFFSET_ADDR 	(0x00020000UL)
#define AHB1_BASE_ADDR 					(BASE_PERIPHERAL_ADDR + AHB1_PERIPHERAL_OFFSET_ADDR)

#define GPIO_OFFSET_ADDR 				(0x0000UL)
#define GPIO_BASE_ADDR 					(AHB1_BASE_ADDR + GPIO_OFFSET_ADDR)

#define RCC_OFFSET 						(0x3800UL)
#define RCC_BASE						(AHB1_BASE_ADDR + RCC_OFFSET)



#define GPIO_A_EN						(1U<<0)
#define LED_PIN_5						(1U<<5)

// according to MISRA-C standard
#define __IO volatile

typedef struct {
	__IO uint32_t MODER;  	/* < GPIO port mode register, 					Address offset: 0x00 	  */
	uint32_t DUMMY[4];
	__IO uint32_t ODR;  	/* < GPIO port output data register, 			Address offset: 0x14 	  */
}GPIO_TypeDef;

typedef struct {
	uint32_t DUMMY[12];
	__IO uint32_t AHB1ENR; /* !< RCC AHB1 peripheral clock register, Address offset: 0x30 */

} RCC_TypeDef;

#define RCC		((RCC_TypeDef*) RCC_BASE)
#define GPIOA	((GPIO_TypeDef*) GPIO_BASE_ADDR)

int main(void){

	// enable clock access to GPIO A port, OR it with GPIO_A_EN to maintain the value of other bits

	// this is functional way
	// RCC_AHB1EN_R |= GPIO_A_EN;

	//this is with struct
	RCC->AHB1ENR |= GPIO_A_EN;

	// set port A pin 5 as output

	// this is functional way
	//GPIO_MODE_R |= (1U<<10 ); //set bit 10 to 1
	//GPIO_MODE_R &=~ (1U<<11); //set bit 11 to 0

	//this is with struct
	GPIOA->MODER |= (1U<<10 );
	GPIOA->MODER &=~ (1U<<11);

	while(1){
		// set port A pin5 as high

		// this is functional way
		//GPIO_A_OD_R |= LED_PIN_5;

		//this is with struct
		GPIOA->ODR ^= LED_PIN_5;

		for(int i=0; i <100000; i++){}

	}
}
