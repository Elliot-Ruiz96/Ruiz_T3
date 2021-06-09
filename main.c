#include "RGB.h"

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

#define PIN2		2u
#define PIN3		3u

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

  Start_State();

    while(1) {

    	Initialize();

			switch (current_state) {
				case YELLOW:
					YELLOW_RGB();
				break;

				case RED:
					RED_RGB();
				break;

				case PURPLE:
					PURPLE_RGB();
				break;

				case GREEN:
					GREEN_RGB();
				break;

				case BLUE:
					BLUE_RGB();
				break;

				case WHITE:
					WHITE_RGB();
				break;
				default:
					Start_State();
				break;
			}

			SDK_DelayAtLeastUs(DELAY, CORE_FREQ);

    }
    return 0 ;
}
