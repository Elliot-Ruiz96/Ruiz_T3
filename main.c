#include <stdio.h>
#include <stdint.h>
#include "fsl_clock.h"
#include "fsl_gpio.h"
#include "fsl_port.h"
#include "fsl_common.h"

#define PIN4      	4u
#define	PIN6		6u

#define CORE_FREQ	21000000u
#define DELAY		1000000u

uint8_t g_ButtonPress = 0;

gpio_pin_config_t sw_config = {
       kGPIO_DigitalInput,
       0,
   };

// Interrupcion en PORTA

void PORTA_IRQHandler(void)
{

    GPIO_PortClearInterruptFlags(GPIOA, 1U << PIN4);
    g_ButtonPress = true;
    SDK_ISR_EXIT_BARRIER;
}

// Interrupcion en PORTC

void PORTC_IRQHandler(void)
{

    GPIO_PortClearInterruptFlags(GPIOC, 1U << PIN6);
    g_ButtonPress = true;
    SDK_ISR_EXIT_BARRIER;
}

int main(void) {

	const port_pin_config_t sw_pin_config = {
		    kPORT_PullUp,                                            /* Internal pull-up resistor is enabled */
		    kPORT_FastSlewRate,                                      /* Fast slew rate is configured */
		    kPORT_PassiveFilterDisable,                              /* Passive filter is disabled */
		    kPORT_OpenDrainDisable,                                  /* Open drain is disabled */
		    kPORT_HighDriveStrength,                                 /* High drive strength is configured */
		    kPORT_MuxAsGpio,                                         /* Pin is configured as PTA4 */
		    kPORT_UnlockRegister                                     /* Pin Control Register fields [15:0] are not locked */
		  };

	// Habilitamos los relojes de los Puertos a usar

	CLOCK_EnableClock(kCLOCK_PortA);								// Switch 3
	CLOCK_EnableClock(kCLOCK_PortC);								// Switch 2

	// Funcion de GPIO

	PORT_SetPinMux(PORTA, PIN4, kPORT_MuxAsGpio); 					// Switch 3 GPIO
	PORT_SetPinMux(PORTC, PIN6, kPORT_MuxAsGpio); 					// Switch 2 GPIO

	PORT_SetPinConfig(PORTA, PIN4, &sw_pin_config);					// Activacion de Switch 3
	PORT_SetPinConfig(PORTC, PIN6, &sw_pin_config);					// Activacion de Switch 2

	GPIO_PinInit(GPIOA, PIN4, &sw_config);
	GPIO_PinInit(GPIOC, PIN6, &sw_config);

	PORT_SetPinInterruptConfig(PORTA, PIN4, kPORT_InterruptFallingEdge);
	PORT_SetPinInterruptConfig(PORTC, PIN6, kPORT_InterruptFallingEdge);

	NVIC_EnableIRQ(PORTA_IRQn);
	NVIC_EnableIRQ(PORTC_IRQn);

	NVIC_SetPriority(PORTA_IRQn, 1);
	NVIC_SetPriority(PORTC_IRQn, 1);


    while(1){

    	printf("Boton: %d \n", g_ButtonPress);

    	if(g_ButtonPress)
    	    	{
    	    		g_ButtonPress = false;
    	    	}

    	SDK_DelayAtLeastUs(DELAY, CORE_FREQ);

    }
    return 0 ;
}
