/**
 * @file
 *
 * The purpose of this "C" callbacks is to provide the code to be able
 * to call pure C functions and unit-test it in C test framework
 */
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "../_can_dbc/generated_can.h"
#include "can.h"
#include "c_gpio.h"
#include "c_i2c2.h"
#include "c_compass.h"

can_msg_t msg_pkt = {0};

bool C_period_init(void)
{
    bool cmps = false;

    if(CAN_init(can1, 100, 25, 25, NULL, NULL))
    {
        CAN_reset_bus(can1);
        CAN_bypass_filter_accept_all_msgs();
    }
    cmps = compass_init();
    return cmps;
}

bool C_period_reg_tlm(void) {
    return true;
}

void C_period_1Hz(uint32_t count){
    (void) count;
    /* CAN SETUP
    if(CAN_is_bus_off(can1))
    {
        CAN_reset_bus(can1);
        char rx_byte[256] = "";

        if(uart2_gets(rx_byte, 256, 0))
        {
            u0_dbg_printf("%s\n", rx_byte);
        }
    }*/
}
void C_period_10Hz(uint32_t count)
{
    (void) count;
}

void C_period_100Hz(uint32_t count) {
    (void) count;
    if(count % 5 == 1){
        compass_t data1 = {0};
        can_msg_t can_msg= {0};
        can_msg_t can_msg_dbg = {0};
        data1 = get_data();

        can_msg = pack_compass_data(data1);
        can_msg_dbg = pack_compass_debug(data1);

        CAN_tx(can1, &can_msg, 0);
        CAN_tx(can1, &can_msg_dbg, 0);
        compass_reset();
    }
}

void C_period_1000Hz(uint32_t count) {
    (void) count;
}
