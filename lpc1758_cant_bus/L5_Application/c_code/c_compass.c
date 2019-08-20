/*
 * c_compass.c
 *
 *  Created on: Apr 25, 2019
 *      Author: aaron.lee
 */
#include "c_compass.h"
#include "c_i2c2.h"
#include "c_gpio.h"
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
# define M_PI           3.14159265358979323846
static const unsigned int mWhoAmIExpectedValue  = 0x48;

bool check_who_am_i_reg(void){
    if(c_getWhoAmIReg() == mWhoAmIExpectedValue){
        return true;
    }
    else{
        return false;
    }
}

bool compass_init(void){
    if(check_who_am_i_reg()){
        //c_setSingleMeasurementMode();
        c_setContinuousMeasurementMode();
        LED_toggle(1);
        return true;
    }
    else{
        LED_toggle(2);
        return false;
    }
}

void compass_reset(void){
    c_compass_softReset();
    compass_init();
}

compass_t get_data(void){
    int16_t _x, _y;
    _x = 0;
    _y = 0;
    compass_t data;

    for(int i = 0; i < 8; i++)
    {
        _x += c_compass_getX();
        _y += c_compass_getY();
    }

    _x = _x/8;
    _y = _y/8;

    data.x = _x;
    data.y = _y;
    data.heading = get_heading(_x, _y);

    //data.x = c_compass_getX();
    //data.y = c_compass_getY();
    //data.heading = get_heading(data.x, data.y);
    return data;
}

can_msg_t pack_compass_data(compass_t data)
{
    LOCALIZE_IMU_t cmps_msg = {0};
    cmps_msg.IMU_COMPASS = data.heading;
    cmps_msg.IMU_STATUS = 0x1;
    can_msg_t can_msg = {0};
    dbc_msg_hdr_t msg_hdr = dbc_encode_LOCALIZE_IMU(can_msg.data.bytes, &cmps_msg);

    can_msg.msg_id = msg_hdr.mid;
    can_msg.frame_fields.data_len = msg_hdr.dlc;
    return can_msg;
}

can_msg_t pack_compass_debug(compass_t data)
{
    LOCALIZE_IMU_DEBUG_t cmps_dbg = {0};
    cmps_dbg.IMU_COMPASS_X = data.x;
    cmps_dbg.IMU_COMPASS_Y = data.y;
    can_msg_t can_msg = {0};
    dbc_msg_hdr_t msg_hdr = dbc_encode_LOCALIZE_IMU_DEBUG(can_msg.data.bytes, &cmps_dbg);
    can_msg.msg_id = msg_hdr.mid;
    can_msg.frame_fields.data_len = msg_hdr.dlc;

    return can_msg;
}

bool check_quad_one(int16_t x, int16_t y)
{
    if((x > 0) && (y > 0)){
        return true;
    }
    return false;
}

bool check_quad_four(int16_t x, int16_t y)
{
    if((x > 0) && (y < 0)){
        return true;
    }
    return false;
}

bool check_quad_two(int16_t x, int16_t y){
    if((x < 0) && (y > 0)){
        return true;
    }
    return false;
}

bool check_quad_three(int16_t x, int16_t y){
    if((x < 0) && (y < 0)){
        return true;
    }
    return false;
}

float get_heading(int16_t x, int16_t y){
    float angle = 0;

    if(0 == x){
        if(y > 0)
            angle = 0;
        else if(y < 0)
            angle = 180;
    }
    else if(0 == y){
        if(x > 0)
            angle = 90;
        else if(x < 0)
            angle = 270;
    }
    else if(check_quad_one(x, y) || check_quad_four(x, y)){
        float tmp;
        tmp = atan2(y, x) * (180/M_PI);
        angle = 90 - tmp;
    }
    else if(check_quad_three(x, y)){
        float tmp;
        tmp = atan2(y, x) * (180/M_PI);
        tmp = 180 - abs(tmp);
        angle = 270 - tmp;
        return angle;
    }
    else if(check_quad_two(x, y)){
        float tmp;
        tmp = atan2(y, x) * (180/M_PI);
        angle = 270 + (180 - tmp);
        return angle;
    }

    return angle;
}
