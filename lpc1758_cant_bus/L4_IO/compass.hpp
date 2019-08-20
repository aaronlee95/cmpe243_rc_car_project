#ifndef COMPASS_HPP_
#define COMPASS_HPP_

#include <stdbool.h>
#include "i2c2_device.hpp"      //I2C Device Base Class

class compass : private i2c2_device, public SingletonTemplate<compass>
{
    public:
        compass() : i2c2_device(I2CAddr_Compass){}
        uint8_t getWhoAmIReg();
        void setSingleMeasurementMode();
        void setContinuousMeasurementMode();
        void setFuseROMaccessmode();
        void setPowerDownMode();
        void softReset();
        int16_t getX();
        int16_t getY();
        int16_t getZ();

        int16_t getX_lsb();
        int16_t getX_msb();
        int16_t getY_lsb();
        int16_t getY_msb();
        int16_t getZ_lsb();
        int16_t getZ_msb();

        //For calibration
        float mx_sensitivity();
        float my_sensitivity();
        float mz_sensitivity();
        /*bool data_ready_status();
*/

    private:
        friend class SingletonTemplate<compass>;
        static const unsigned int mWhoAmIExpectedValue  = 0x48;
        static const unsigned int continuousMeasMode1   = 0x12;
        static const unsigned int continuousMeasMode2   = 0x16;
        static const unsigned int singleMeasMode1_16bit = 0x11;
        static const unsigned int FuseROMaccessMode     = 0x1F;
        static const unsigned int powerDownMode         = 0x00;


        typedef enum{
            //Read Only Registers
            WhoAmIReg=0x0 ,
                 info=0x1 ,
              status1=0x2 , status2=0x9,
                X_LSB=0x3 , X_MSB=0x4,
                Y_LSB=0x5 , Y_MSB=0x6,
                Z_LSB=0x7 , Z_MSB=0x8,
                 ASAX=0x10, ASAY=0x11, ASAZ=0x12,

            //Write/Read Registers
            control1=0xA,  control2=0xB,
                ASTC=0xC,  TS1=0xD,
                TS2 =0xE,  I2CDIS=0xF
        }__attribute__ ((packed)) RegisterMap;
};

#endif /* COMPASS_HPP_ */
