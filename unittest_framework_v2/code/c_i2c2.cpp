/*
 * c_i2c2.cpp
 *
 *  Created on: Apr 18, 2019
 *      Author: Aaron
 */

#include "c_i2c2.h"
#include "compass.hpp"
#include "i2c2.hpp"
#include "io.hpp"
#include <stdio.h>
#include "c_gpio.h"

const signed int x_offset = 32;
const signed int y_offset = 105;

#define object compass::getInstance()

void c_setContinuousMeasurementMode(void)
{
    object.setContinuousMeasurementMode();
}

void c_setSingleMeasurementMode(void)
{
    object.setSingleMeasurementMode();
}

void c_compass_softReset(void){
    object.softReset();
}

int16_t c_compass_getX(void)
{
    return object.getX() + x_offset;
}

int16_t c_compass_getY(void)
{
    return object.getY() - y_offset;
}

int16_t c_compass_getZ(void)
{
    return object.getZ();
}

uint8_t c_getWhoAmIReg(void)
{
    return object.getWhoAmIReg();
}
