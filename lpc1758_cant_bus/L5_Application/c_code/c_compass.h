/*
 * c_compass.h
 *
 *  Created on: Apr 25, 2019
 *      Author: aaron.lee
 */

#ifndef C_COMPASS_H_
#define C_COMPASS_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include "can.h"
#include "../../_can_dbc/generated_can.h"


typedef struct{
    int16_t x;                      //Debug
    int16_t y;                      //Debug
    double heading;
}compass_t;

bool compass_init(void);
void compass_reset(void);
bool check_who_am_i_reg(void);
float get_heading(int16_t x, int16_t y);
compass_t get_data(void);
can_msg_t pack_compass_data(compass_t cmps);
can_msg_t pack_compass_debug(compass_t data);

bool check_quad_one(int16_t x, int16_t y);
bool check_quad_four(int16_t x, int16_t y);
bool check_quad_two(int16_t x, int16_t y);
bool check_quad_three(int16_t x, int16_t y);



#ifdef __cplusplus
}
#endif
#endif /* C_COMPASS_H_ */
