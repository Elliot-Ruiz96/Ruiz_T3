#ifndef RGB_H_
#define RGB_H_

#include <stdio.h>
#include "pin_mux.h"
#include "fsl_gpio.h"
#include "fsl_port.h"
#include "fsl_common.h"

typedef enum {
	RED,
	BLUE,
	PURPLE,
	WHITE,
	YELLOW,
	GREEN,
}State_name_t;

State_name_t current_state;

uint32_t Sw, Sw2, Sw3;

#define CORE_FREQ	21000000u
#define DELAY		1000000u

#define ONE   		(0x01u)										// Sw2 Izquierda
#define TWO   		(0x02u)										// Sw3 Derecha
#define THREE 		(0x03u)										// Start
#define ZERO		(0x00u)										// Sw3 X2

#define PIN22       22u
#define PIN21       21u
#define PIN26		26u

#define PIN6        6u
#define PIN4        4u

void Start_State();
void Initialize();
void YELLOW_RGB();
void RED_RGB();
void PURPLE_RGB();
void GREEN_RGB();
void BLUE_RGB();
void WHITE_RGB();

#endif /* RGB_H_ */
