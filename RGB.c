#include "RGB.h"

void RED_RGB(){

	GPIO_PortSet(GPIOB, 1u << PIN21);
	GPIO_PortSet(GPIOB, 1u << PIN22);
	GPIO_PortSet(GPIOE, 1u << PIN26);
	GPIO_PortToggle(GPIOB, 1u << PIN22);					// RED
 	SDK_DelayAtLeastUs(DELAY, CORE_FREQ);

}

void PURPLE_RGB(){

	GPIO_PortSet(GPIOB, 1u << PIN21);
	GPIO_PortSet(GPIOB, 1u << PIN22);
	GPIO_PortSet(GPIOE, 1u << PIN26);
	GPIO_PortToggle(GPIOB, 1u << PIN21);					// PURPLE
	GPIO_PortToggle(GPIOB, 1u << PIN22);
	SDK_DelayAtLeastUs(DELAY, CORE_FREQ);

}

void BLUE_RGB(){

	GPIO_PortSet(GPIOB, 1u << PIN21);
	GPIO_PortSet(GPIOB, 1u << PIN22);
	GPIO_PortSet(GPIOE, 1u << PIN26);
	GPIO_PortToggle(GPIOB, 1u << PIN21);					// BLUE
	SDK_DelayAtLeastUs(DELAY, CORE_FREQ);

}

void WHITE_RGB(){

	GPIO_PortSet(GPIOB, 1u << PIN21);
	GPIO_PortSet(GPIOB, 1u << PIN22);
	GPIO_PortSet(GPIOE, 1u << PIN26);
	GPIO_PortToggle(GPIOB, 1u << PIN21);					// WHITE
	GPIO_PortToggle(GPIOB, 1u << PIN22);
	GPIO_PortToggle(GPIOE, 1u << PIN26);
	SDK_DelayAtLeastUs(DELAY, CORE_FREQ);

}

void YELLOW_RGB(){
	GPIO_PortSet(GPIOB, 1u << PIN21);
	GPIO_PortSet(GPIOB, 1u << PIN22);
	GPIO_PortSet(GPIOE, 1u << PIN26);
	GPIO_PortToggle(GPIOB, 1u << PIN22);					// YELLOW
	GPIO_PortToggle(GPIOE, 1u << PIN26);
 	SDK_DelayAtLeastUs(DELAY, CORE_FREQ);
}

void GREEN_RGB(){

	GPIO_PortSet(GPIOB, 1u << PIN21);
	GPIO_PortSet(GPIOB, 1u << PIN22);
	GPIO_PortSet(GPIOE, 1u << PIN26);
	GPIO_PortToggle(GPIOE, 1u << PIN26);					// GREEN
    SDK_DelayAtLeastUs(DELAY, CORE_FREQ);

}
