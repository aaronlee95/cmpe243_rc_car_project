/*
 * c_i2c2.h
 *
 *  Created on: Apr 18, 2019
 *      Author: Aaron
 */

#ifndef C_I2C2_H_
#define C_I2C2_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>

void c_setContinuousMeasurementMode(void);
void c_setSingleMeasurementMode(void);
bool check_data_ready(void);
uint8_t c_getWhoAmIReg(void);
int16_t c_compass_getY(void);
int16_t c_compass_getX(void);
int16_t c_compass_getZ(void);
void c_compass_softReset(void);

#ifdef __cplusplus
}



#endif
#endif /* C_I2C2_H_ */
