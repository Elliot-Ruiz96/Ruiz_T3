#include <stdio.h>
#include "pin_mux.h"
#include "fsl_gpio.h"
#include "fsl_port.h"
#include "fsl_common.h"

uint8_t g_ButtonPress = 0;

 gpio_pin_config_t sw_config = {
        kGPIO_DigitalInput,
        0,
    };

gpio_pin_config_t led_config = {
        kGPIO_DigitalOutput,
        1,
    };

gpio_pin_config_t analyzer_config = {
        kGPIO_DigitalOutput,
        1,
};

#define PIN22       22u
#define PIN21       21u
#define PIN26		26u

#define PIN2		2u
#define PIN3		3u

#define PIN6        6u
#define PIN4        4u

#define ONE   		(0x01u)										// Sw2 Izquierda
#define TWO   		(0x02u)										// Sw3 Derecha
#define THREE 		(0x03u)										// Start
#define ZERO		(0x00u)										// Sw3 X2

#define CORE_FREQ	21000000u
#define DELAY		1000000u

typedef enum {
	RED,
	BLUE,
	PURPLE,
	WHITE,
	YELLOW,
	GREEN,
}State_name_t;

int main(void) {

	uint32_t Sw2, Sw3, Sw;

	State_name_t current_state = YELLOW;

	const port_pin_config_t sw_pin_config = {
	    kPORT_PullUp,                                            /* Internal pull-up resistor is enabled */
	    kPORT_FastSlewRate,                                      /* Fast slew rate is configured */
	    kPORT_PassiveFilterDisable,                              /* Passive filter is disabled */
	    kPORT_OpenDrainDisable,                                  /* Open drain is disabled */
	    kPORT_HighDriveStrength,                                 /* High drive strength is configured */
	    kPORT_MuxAsGpio,                                         /* Pin is configured as PTA4 */
	    kPORT_UnlockRegister                                     /* Pin Control Register fields [15:0] are not locked */
	  };

  CLOCK_EnableClock(kCLOCK_PortA);
  CLOCK_EnableClock(kCLOCK_PortB);
  CLOCK_EnableClock(kCLOCK_PortC);
  CLOCK_EnableClock(kCLOCK_PortE);

  PORT_SetPinConfig(PORTA, PIN4, &sw_pin_config);
  PORT_SetPinConfig(PORTC, PIN6, &sw_pin_config);

  GPIO_PinInit(GPIOA, PIN4, &sw_config);
  GPIO_PinInit(GPIOC, PIN6, &sw_config);

  PORT_SetPinMux(PORTB, PIN22, kPORT_MuxAsGpio);
  PORT_SetPinMux(PORTB, PIN21, kPORT_MuxAsGpio);
  PORT_SetPinMux(PORTE, PIN26, kPORT_MuxAsGpio);

  PORT_SetPinMux(PORTB, PIN2, kPORT_MuxAsGpio);
  PORT_SetPinMux(PORTB, PIN3, kPORT_MuxAsGpio);

  GPIO_PinInit(GPIOB, PIN22, &led_config);
  GPIO_PinInit(GPIOB, PIN21, &led_config);
  GPIO_PinInit(GPIOE, PIN26, &led_config);

  GPIO_PinInit(GPIOB, PIN2, &analyzer_config);
  GPIO_PinInit(GPIOB, PIN3, &analyzer_config);

    while(1) {

    	Sw3 = GPIO_PinRead(GPIOA, PIN4);
    	Sw2 = GPIO_PinRead(GPIOC, PIN6);
    	Sw3 = Sw3 << 1;
		Sw = Sw2 | Sw3;
		printf("Sw2: %d \n", Sw2);
		printf("Sw3: %d \n", Sw3);
		printf("Sw: %d \n", Sw);
		printf("State: %d \n", current_state);
		if (Sw == TWO && Sw3 == 0){											// Si se presiona por segunda vez S3 seguida
			Sw = ZERO;
		}

			switch (current_state) {
				case YELLOW:

					GPIO_PortSet(GPIOB, 1u << PIN21);
					GPIO_PortSet(GPIOB, 1u << PIN22);
					GPIO_PortSet(GPIOE, 1u << PIN26);
					GPIO_PortToggle(GPIOB, 1u << PIN22);					// YELLOW
			    	GPIO_PortToggle(GPIOE, 1u << PIN26);
			     	SDK_DelayAtLeastUs(DELAY, CORE_FREQ);

			     	if (ONE == Sw){
			     		current_state = GREEN;
			     	}
			     	else if (TWO == Sw){
			     		current_state = BLUE;
			     	}
			     	else if (THREE == Sw){
						current_state = RED;
					}
					else if(ZERO == Sw){
						current_state = GREEN;
					}
					else{
						current_state = YELLOW;
					}
				break;

				case RED:

					GPIO_PortSet(GPIOB, 1u << PIN21);
					GPIO_PortSet(GPIOB, 1u << PIN22);
					GPIO_PortSet(GPIOE, 1u << PIN26);
					GPIO_PortToggle(GPIOB, 1u << PIN22);					// RED
			     	SDK_DelayAtLeastUs(DELAY, CORE_FREQ);

					switch (Sw) {
						case ONE:
							current_state = GREEN;
						break;
						case TWO:
							current_state = BLUE;
						break;
						case THREE:
							current_state = PURPLE;
						break;
						case ZERO:
							current_state = GREEN;
							break;
						default:
							current_state = RED;
						break;
					}
				break;

				case PURPLE:

					GPIO_PortSet(GPIOB, 1u << PIN21);
					GPIO_PortSet(GPIOB, 1u << PIN22);
					GPIO_PortSet(GPIOE, 1u << PIN26);
					GPIO_PortToggle(GPIOB, 1u << PIN21);					// PURPLE
			    	GPIO_PortToggle(GPIOB, 1u << PIN22);
			     	SDK_DelayAtLeastUs(DELAY, CORE_FREQ);

			     	if (ONE == Sw){
			     		current_state = GREEN;
			     	}
			     	else if (TWO == Sw){
			     		current_state = BLUE;
			     	}
			     	else if (THREE == Sw){
						current_state = YELLOW;
					}
					else if(ZERO == Sw){
						current_state = YELLOW;
					}
					else{
						current_state = PURPLE;
					}
				break;

				case GREEN:

					GPIO_PortSet(GPIOB, 1u << PIN21);
					GPIO_PortSet(GPIOB, 1u << PIN22);
					GPIO_PortSet(GPIOE, 1u << PIN26);
					GPIO_PortToggle(GPIOE, 1u << PIN26);					// GREEN
			     	SDK_DelayAtLeastUs(DELAY, CORE_FREQ);

					switch (Sw) {

						case ONE:
							current_state = BLUE;
						break;
						case TWO:
							current_state = BLUE;
						break;
						case THREE:
							current_state = YELLOW;
						break;
						case ZERO:
							current_state = PURPLE;
							break;
						default:
							current_state = GREEN;
						break;
				}
				break;

					case BLUE:

						GPIO_PortSet(GPIOB, 1u << PIN21);
						GPIO_PortSet(GPIOB, 1u << PIN22);
						GPIO_PortSet(GPIOE, 1u << PIN26);
						GPIO_PortToggle(GPIOB, 1u << PIN21);					// BLUE
				     	SDK_DelayAtLeastUs(DELAY, CORE_FREQ);

						if (ONE == Sw){
							current_state = RED;
						}
						else if (TWO == Sw){
							current_state = WHITE;
						}
						else if (THREE == Sw){
							current_state = YELLOW;
						}
						else if (ZERO == Sw){
							current_state = GREEN;
						}
						else{
							current_state = BLUE;
						}
					break;

					case WHITE:

						GPIO_PortSet(GPIOB, 1u << PIN21);
						GPIO_PortSet(GPIOB, 1u << PIN22);
						GPIO_PortSet(GPIOE, 1u << PIN26);
						GPIO_PortToggle(GPIOB, 1u << PIN21);					// WHITE
				    	GPIO_PortToggle(GPIOB, 1u << PIN22);
				    	GPIO_PortToggle(GPIOE, 1u << PIN26);
				     	SDK_DelayAtLeastUs(DELAY, CORE_FREQ);

						switch (Sw){

							case ONE:
								current_state = GREEN;
								break;
							case TWO:
								current_state = RED;
							break;
							case THREE:
								current_state = YELLOW;
								break;
							case ZERO:
								current_state = GREEN;
								break;
							default:
								current_state = WHITE;
							break;
					}
					break;

				default:
					GPIO_PortSet(GPIOB, 1u << PIN21);
					GPIO_PortSet(GPIOB, 1u << PIN22);
					GPIO_PortSet(GPIOE, 1u << PIN26);
					GPIO_PortToggle(GPIOB, 1u << PIN22);					// YELLOW
			    	GPIO_PortToggle(GPIOE, 1u << PIN26);
					current_state = YELLOW;
			     	SDK_DelayAtLeastUs(DELAY, CORE_FREQ);
					break;
			}

			SDK_DelayAtLeastUs(DELAY, CORE_FREQ);

    }
    return 0 ;
}
