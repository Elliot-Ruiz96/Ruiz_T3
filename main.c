#include <stdio.h>
#include "fsl_clock.h"
#include "fsl_gpio.h"
#include "fsl_port.h"
#include "fsl_common.h"

#define PIN21      	21u
#define	PIN22		22u
#define PIN26		26u

gpio_pin_config_t led_config = {
        kGPIO_DigitalOutput,
        1,
    };

int main(void) {

	// Habilitamos los relojes de los Puertos a usar

	CLOCK_EnableClock(kCLOCK_PortB);								// Red and Blue LED
	CLOCK_EnableClock(kCLOCK_PortE);								// Green LED

	// Funcion de GPIO

	PORT_SetPinMux(PORTB, PIN21, kPORT_MuxAsGpio); 					// Blue LED GPIO
	PORT_SetPinMux(PORTB, PIN22, kPORT_MuxAsGpio); 					// Red LED GPIO
	PORT_SetPinMux(PORTE, PIN26, kPORT_MuxAsGpio); 					// Green LED GPIO

	GPIO_PinInit(GPIOB, PIN22, &led_config);
	GPIO_PinInit(GPIOB, PIN21, &led_config);
	GPIO_PinInit(GPIOE, PIN26, &led_config);

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
