///*
// * c_gpio.cpp
// *
// *  Created on: Feb 27, 2019
// *      Author: diarm
// */
//
#include "gpio.hpp"
#include "c_gpio.h"
#include "io.hpp"

GPIO ExternalLED(P1_19);

void LED_init( void )
{
    ExternalLED.setAsOutput();
    ExternalLED.setLow();
}

void LED_set( void )
{
    ExternalLED.setHigh();
    LE.on(1);

}

void LED_toggle( uint8_t led )
{
    LE.toggle(led);
}

void LED_clr( void )
{
    ExternalLED.setLow();
    LE.off(1);
}

void Switch_init( void )
{
    SW.init();
}

bool Switch_get( int button )
{
    return SW.getSwitch(button);
}

void Send_message( can_msg_t *msg, bool is_pressed )
{
    msg->data.bytes[0] = (is_pressed) ? 0x258 : 0x00;
}

bool Receive_message( can_msg_t *msg )
{
    return (msg->data.bytes[0]);
}
