
//GPIO and INT for AVR

#include <avr/io.h>
#include "AVR_Ports.h"
#include "AVR_GPIO_Declarations.h"
#include "avr/interrupt.h" //this Library is for Vectored Interrupt

int main(void)
{
	
	Pin_Direction(C, 2, input);
	Pin_Direction(D, 2, input);
	Pin_Direction(D, 3, input);
	Pin_Direction(B, 2, input);
	Pin_Direction(B, 0, output);
	Pin_Direction(A, 2, output);
	Pin_Direction(A, 3, output);

	GICR = (1<<6) | (1<<7) | (1<<5); //GICR: Bit7=INT1, Bit6=INT0, Bit5=INT2 (so we here set all three Interrupt Pins 11100000)
	sei(); //Set Global Interrupt =1

	while(1)
	{
		if(Pin_Read(C, 2) == 0) //pin is connected to ground (SW-ON)
		{
			Pin_Set(B, 0); //Set Pin B0
			Pin_Set(A,2); //Set Pin A2
			Pin_Set(A,3); //Set Pin A3
		}
	}
	
	
}

//Interrupt Service Routine for Interrupt 0
ISR(INT0_vect) //Default event for interrupting= when sense Low (Ground input)
{
	Pin_Reset(B,0); //Reset this Pin immediately 
}

//Interrupt Service Routine for Interrupt 1
ISR(INT1_vect) //Default event for interrupting= when sense Low (Ground input)
{
	Pin_Reset(A,2); //Reset this Pin immediately 
}

//Interrupt Service Routine for Interrupt 2
ISR(INT2_vect) //Default event for interrupting= when sense Low (Ground input)
{
	Pin_Reset(A,3); //Reset this Pin immediately 
}