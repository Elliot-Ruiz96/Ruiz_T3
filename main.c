#include <stdio.h>
#include "fsl_clock.h"
#include "fsl_gpio.h"
#include "fsl_port.h"
#include "fsl_common.h"

#define PIN4      	4u
#define	PIN6		6u
#define PIN21      	21u
#define	PIN22		22u
#define PIN26		26u

gpio_pin_config_t led_config = {
        kGPIO_DigitalOutput,
        1,
    };

gpio_pin_config_t sw_config = {
       kGPIO_DigitalInput,
       0,
   };

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
	CLOCK_EnableClock(kCLOCK_PortB);								// Red and Blue LED
	CLOCK_EnableClock(kCLOCK_PortC);								// Switch 2
	CLOCK_EnableClock(kCLOCK_PortE);								// Green LED

	// Funcion de GPIO

	PORT_SetPinMux(PORTB, PIN21, kPORT_MuxAsGpio); 					// Blue LED GPIO
	PORT_SetPinMux(PORTB, PIN22, kPORT_MuxAsGpio); 					// Red LED GPIO
	PORT_SetPinMux(PORTE, PIN26, kPORT_MuxAsGpio); 					// Green LED GPIO
	PORT_SetPinMux(PORTA, PIN4, kPORT_MuxAsGpio); 					// Switch 3 GPIO
	PORT_SetPinMux(PORTC, PIN6, kPORT_MuxAsGpio); 					// Switch 2 GPIO

	PORT_SetPinConfig(PORTA, PIN4, &sw_pin_config);				// Activacion de Switch 3
	PORT_SetPinConfig(PORTC, PIN6, &sw_pin_config);				// Activacion de Switch 2

	GPIO_PinInit(GPIOB, PIN22, &led_config);
	GPIO_PinInit(GPIOB, PIN21, &led_config);
	GPIO_PinInit(GPIOE, PIN26, &led_config);
	GPIO_PinInit(GPIOA, PIN4, &swe_config);
	GPIO_PinInit(GPIOC, PIN6, &sw_config);

    while(1){

    	// Start

    	GPIO_PortToggle(GPIOB, 1u << PIN22);					// YELLOW
    	GPIO_PortToggle(GPIOE, 1u << PIN26);
    	GPIO_PortToggle(GPIOB, 1u << PIN22);					// RED
    	GPIO_PortToggle(GPIOB, 1u << PIN21);					// PURPLE
    	GPIO_PortToggle(GPIOB, 1u << PIN22);

    	// Sw2

    	GPIO_PortToggle(GPIOE, 1u << PIN26);					// GREEN
    	GPIO_PortToggle(GPIOB, 1u << PIN21);					// BLUE
    	GPIO_PortToggle(GPIOB, 1u << PIN22);					// RED

    	// Sw3

    	GPIO_PortToggle(GPIOB, 1u << PIN21);					// BLUE
    	GPIO_PortToggle(GPIOB, 1u << PIN21);					// WHITE
    	GPIO_PortToggle(GPIOB, 1u << PIN22);
    	GPIO_PortToggle(GPIOE, 1u << PIN26);
    	GPIO_PortToggle(GPIOB, 1u << PIN22);					// RED

    	// Sw3 x2

    	GPIO_PortToggle(GPIOE, 1u << PIN26);					// GREEN
    	GPIO_PortToggle(GPIOB, 1u << PIN21);					// PURPLE
    	GPIO_PortToggle(GPIOB, 1u << PIN22);
    	GPIO_PortToggle(GPIOB, 1u << PIN22);					// YELLOW
    	GPIO_PortToggle(GPIOE, 1u << PIN26);

    }
    return 0 ;
}
