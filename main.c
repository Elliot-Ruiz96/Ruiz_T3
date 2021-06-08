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

#define PIN22         22u
#define PIN21         21u
#define PIN26         26u

#define PIN6         6u
#define PIN4         4u

#define ZERO  (0x00u)
#define ONE   (0x01u)
#define TWO   (0x02u)
#define THREE (0x03u)

typedef enum {
	RED,
	BLUE,
	PURPLE,
	WHITE,
	YELLOW,
	GREEN,
}State_name_t;

int main(void) {

	uint32_t sw2, sw3, sw;

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

  GPIO_PinInit(GPIOB, PIN22, &led_config);
  GPIO_PinInit(GPIOB, PIN21, &led_config);
  GPIO_PinInit(GPIOE, PIN26, &led_config);

    while(1) {

    	sw3 = GPIO_PinRead(GPIOA, PIN4);
    	sw2 = GPIO_PinRead(GPIOC, PIN6);
    	sw3 = sw3 << 1;
		sw = sw2 | sw3;

			switch (current_state) {
				case YELLOW:

					GPIO_PortSet(GPIOB, 1u << PIN21);//BLUE
					GPIO_PortClear(GPIOB, 1u << PIN22);//RED
					GPIO_PortSet(GPIOE, 1u << PIN26);//GREE

					if(ZERO == total_input)
					{
						current_state = WHITE;
					}
					else if(ONE == total_input)
					{
						current_state = BLUE;
					}
					else if(TWO == total_input)
					{
						current_state = PURPLE;
					}
					else if (THREE == total_input)
					{
						current_state = RED;
					}
					else
					{
						current_state = RED;
					}
				break;

				case BLUE:

					GPIO_PortSet(GPIOB, 1u << PIN21);//BLUE
					GPIO_PortClear(GPIOB, 1u << PIN22);//RED
					GPIO_PortSet(GPIOE, 1u << PIN26);//GREE

					switch (total_input) {
						case ZERO:
							current_state = BLUE;
						break;
						case ONE:
							current_state = BLUE;
						break;
						case TWO:
							current_state = RED;
						break;
						case THREE:
							current_state = PURPLE;
						break;
						default:
							current_state = BLUE;
						break;
					}
				break;
				case PURPLE:

					GPIO_PortClear(GPIOB, 1u << PIN21);//BLUE
					GPIO_PortClear(GPIOB, 1u << PIN22);//RED
					GPIO_PortSet(GPIOE, 1u << PIN26);//GREE

					if(ONE == total_input)
					{
						current_state = RED;
					}
					else if(ONE == total_input)
					{
						current_state = PURPLE;
					}
					else if(TWO == total_input)
					{
						current_state = PURPLE;
					}
					else if (THREE == total_input)
					{
						current_state = BLUE;
					}
					else
					{
						current_state = PURPLE;
					}
				break;
				case WHITE:

					GPIO_PortClear(GPIOB, 1u << PIN21);//BLUE
					GPIO_PortClear(GPIOB, 1u << PIN22);//RED
					GPIO_PortClear(GPIOE, 1u << PIN26);//GREE

					switch (total_input) {
						case ZERO:
							current_state = WHITE;
						break;
						case ONE:
							current_state = BLUE;
						break;
						case TWO:
							current_state = PURPLE;
						break;
						case THREE:
							current_state = RED;
						break;
						default:
							current_state = WHITE;
						break;
				}
				break;
				default:
					GPIO_PortSet(GPIOB, 1u << PIN21);//BLUE
					GPIO_PortSet(GPIOB, 1u << PIN22);//RED
					GPIO_PortSet(GPIOE, 1u << PIN26);//GREE

					current_state = RED;
					break;
			}

			SDK_DelayAtLeastUs(1000000,21000000);
    }
    return 0 ;
}
