#define BASE_PERIPHERAL_ADDR 			(0x40000000UL)
#define AHB1_PERIPHERAL_OFFSET_ADDR 	(0x00020000UL)
#define AHB1_BASE_ADDR 					(BASE_PERIPHERAL_ADDR + AHB1_PERIPHERAL_OFFSET_ADDR)

#define GPIO_OFFSET_ADDR 				(0x0000UL)
#define GPIO_BASE_ADDR 					(AHB1_BASE_ADDR + GPIO_OFFSET_ADDR)

#define RCC_OFFSET 						(0x3800UL)
#define RCC_BASE						(AHB1_BASE_ADDR + RCC_OFFSET)
#define RCC_AHB1ENR_OFFSET 				(0x30UL)
#define RCC_AHB1EN_R					(*(unsigned volatile int *)(RCC_BASE + RCC_AHB1ENR_OFFSET))

#define MODE_R_OFFSET					(0x00UL)
#define GPIO_MODE_R						(*(unsigned volatile int *)(GPIO_BASE_ADDR + MODE_R_OFFSET))

#define OD_R_OFFSET						(0x14UL)
#define GPIO_A_OD_R						(*(unsigned volatile int *)(GPIO_BASE_ADDR + OD_R_OFFSET))


#define GPIO_A_EN						(1U<<0)
#define LED_PIN_5						(1U<<5)


int main(void){

	// enable clock access to GPIO A port, OR it with GPIO_A_EN to maintain the value of other bits
	RCC_AHB1EN_R |= GPIO_A_EN;

	// set port A pin 5 as output
	GPIO_MODE_R |= (1U<<10); //set bit 10 to 1
	GPIO_MODE_R &=~ (1U<<11); //set bit 11 to 0

	while(1){
		// set port A pin5 as high
		GPIO_A_OD_R |= LED_PIN_5;
	}
}
