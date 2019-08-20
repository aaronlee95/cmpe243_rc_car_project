/*
 * c_gpio.h
 *
 *  Created on: Feb 27, 2019
 *      Author: ntwong0
 */

#ifndef GPIO_C_H__
#define GPIO_C_H__
#ifdef __cplusplus
extern "C" {
#endif

//#include "gpio.hpp"
#include <stdint.h>
#include <stdbool.h>
#include "can.h"

void LED_init( void );
void LED_toggle(  uint8_t led  );
void LED_set( void );
void LED_clr( void );
void Switch_init( void );
bool Switch_get( int button );
void Send_message( can_msg_t *msg, bool is_pressed);
bool Receive_message( can_msg_t *msg );

//GPIO LED(P1_19);

//void LED_init(GPIO* somePin)
//{
//    somePin->setAsOutput();
//    somePin->setLow();
//}

//void LED_set(GPIO* somePin)
//{
//    somePin->setHigh();
//}

//void LED_clr(GPIO* somePin)
//{
//    somePin->setLow();
//}


#ifdef __cplusplus
}
#endif
#endif /* GPIO_C_H__ */
