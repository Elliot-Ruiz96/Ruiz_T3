#include "RGB.h"

void Start_State(){
	GPIO_PortSet(GPIOB, 1u << PIN21);
	GPIO_PortSet(GPIOB, 1u << PIN22);
	GPIO_PortSet(GPIOE, 1u << PIN26);
	GPIO_PortToggle(GPIOB, 1u << PIN22);					// YELLOW
	GPIO_PortToggle(GPIOE, 1u << PIN26);
	current_state = YELLOW;
 	SDK_DelayAtLeastUs(DELAY, CORE_FREQ);
}

void Initialize(){
	Sw3 = GPIO_PinRead(GPIOA, PIN4);
	Sw2 = GPIO_PinRead(GPIOC, PIN6);
	Sw3 = Sw3 << 1;
	Sw = Sw2 | Sw3;
	printf("Sw2: %d \n", Sw2);
	printf("Sw3: %d \n", Sw3);
	printf("Sw: %d \n", Sw);
	printf("State: %d \n", current_state);
}

void YELLOW_RGB(){
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
}

void RED_RGB(){
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

}
void PURPLE_RGB(){

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
}

void GREEN_RGB(){
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

}

void BLUE_RGB(){

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
	}						else if (THREE == Sw){
		current_state = YELLOW;
	}
	else if (ZERO == Sw){
		current_state = GREEN;
	}						else{
		current_state = BLUE;
	}

}

void WHITE_RGB(){

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
		break;							case ZERO:
			current_state = GREEN;
		break;
		default:
			current_state = WHITE;
		break;
	}

}
