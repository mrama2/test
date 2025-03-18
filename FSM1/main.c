/*(C) Ramakrishnan M
Problem Statement: When the Button is pressed, the LED must glow. 
When the button is released, the LED must turn off. */

#include <lpc17xx.h>

typedef enum
{
	LED_ON,
	LED_OFF
} eState_t;

void GPIO_init();
int get_switch_status();
int main(void)
{
	int Switch_Status;
	eState_t LED_State = LED_OFF;
	GPIO_init();
	while(1)
	{
		switch(LED_State)
		{
			case LED_OFF:
				LPC_GPIO0->FIOPIN &= ~((1<<0)| (1<<1) | (1<< 10) | (1<<11));   
				if( (Switch_Status = get_switch_status()) == 0)
				{
					LED_State = LED_ON;
				}
				break;
			case LED_ON:
				LPC_GPIO0->FIOPIN |= ((1<<0)| (1<<1) | (1<< 10) | (1<<11));           
				if( (Switch_Status = get_switch_status()) == 1)
				{
					LED_State = LED_OFF;
				}
				break;
		}
	}
}
	
/* GPIO init function to initialize GPIO*/
void GPIO_init()
{
	 LPC_GPIO1->FIODIR |= (1<<23);           /* Buzzer on PORT1.23 are output      */
	 LPC_GPIO1->FIODIR |= (1<<22);           /* Relay on PORT1.22 are output      */
	 LPC_GPIO0->FIODIR |= (1<<0)| (1<<1) | (1<< 10) | (1<<11);           
	 LPC_GPIO2->FIODIR      &= ~(1 << 11);    /* PORT2.11 defined as input       */	                                                                                                   // 1111 1111 1111 1111 1111 1111 1100 0011
   LPC_GPIO1->FIOPIN &= ~(1<<23);
}

int get_switch_status()
{
	return ((LPC_GPIO2->FIOPIN >> 11) & 0x01);
}