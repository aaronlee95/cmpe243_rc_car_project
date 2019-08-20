#include "compass.hpp"
#include "io.hpp"

/*
 * MPU9255 Magnetometer
 */

uint8_t compass::getWhoAmIReg(void){
    return readReg(WhoAmIReg);
}
void compass::setSingleMeasurementMode(void){
   writeReg(control1, singleMeasMode1_16bit);
}

void compass::setContinuousMeasurementMode(void)
{
    writeReg(control1,continuousMeasMode2);
}

int16_t compass::getX()
{
    int16_t x;
    x = ((getX_msb() << 8) | getX_lsb());
    return x;

}

int16_t compass::getY()
{
    int16_t y;
    y = ((getY_msb() << 8) | getY_lsb());
    return y;
}

int16_t compass::getZ()
{
    return ((getZ_msb() << 8) | getZ_lsb());
}

int16_t compass::getX_lsb(){
    return readReg(X_LSB);
}
int16_t compass::getX_msb(){
    return readReg(X_MSB);
}
int16_t compass::getY_lsb(){
    return readReg(Y_LSB);
}
int16_t compass::getY_msb(){
    return readReg(Y_MSB);
}
int16_t compass::getZ_lsb(){
    return readReg(Z_LSB);
}
int16_t compass::getZ_msb(){
    return readReg(Z_MSB);
}

float compass::mx_sensitivity(){
    return (((readReg(ASAX) -128)*0.5)/128)+1;
}

float compass::my_sensitivity(){
    return (((readReg(ASAY) -128)*0.5)/128)+1;
}
float compass::mz_sensitivity(){
    return (((readReg(ASAZ) -128)*0.5)/128)+1;
}

void compass::softReset(){
    writeReg(control2, 0x1);
}
