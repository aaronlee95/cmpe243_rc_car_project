#include "unity.h"
#include "Mockcan.h"
#include "Mockc_i2c2.h"
// #include "Mockc_compass.h"
#include "c_compass.h"
#include "Mockc_gpio.h"
# define M_PI           3.14159265358979323846

void test_quad_one(void)
{
    TEST_ASSERT_TRUE(check_quad_one(100, 100));
    TEST_ASSERT_TRUE(check_quad_one(50, 50));
    TEST_ASSERT_FALSE(check_quad_one(-100, -100));
    TEST_ASSERT_FALSE(check_quad_one(-100, 75));
    TEST_ASSERT_FALSE(check_quad_one(180, -209)); 
    TEST_ASSERT_FALSE(check_quad_one(180, 0)); 
    TEST_ASSERT_FALSE(check_quad_one(0, 209)); 
}

void test_quad_two(void)
{
    TEST_ASSERT_TRUE(check_quad_two(-150, 1));
    TEST_ASSERT_TRUE(check_quad_two(-50, 78)); 
    TEST_ASSERT_TRUE(check_quad_two(-1, 190));
    TEST_ASSERT_FALSE(check_quad_two(-45, -45)); 
    TEST_ASSERT_FALSE(check_quad_two(50, 50)); 
    TEST_ASSERT_FALSE(check_quad_two(-30, -80)); 
    TEST_ASSERT_FALSE(check_quad_two(50, -60)); 
    TEST_ASSERT_FALSE(check_quad_two(-180, -0)); 
    TEST_ASSERT_FALSE(check_quad_two(0, 60)); 
}

void test_quad_three(void)
{
    TEST_ASSERT_TRUE(check_quad_three(-150, -1)); 
    TEST_ASSERT_TRUE(check_quad_three(-1, -150)); 
    TEST_ASSERT_TRUE(check_quad_three(-39, -68)); 
    TEST_ASSERT_FALSE(check_quad_three(1, 200)); 
    TEST_ASSERT_FALSE(check_quad_three(200, 1)); 
    TEST_ASSERT_FALSE(check_quad_three(-1, 1)); 
    TEST_ASSERT_FALSE(check_quad_three(1, -1));
    TEST_ASSERT_FALSE(check_quad_three(-180, 0)); 
    TEST_ASSERT_FALSE(check_quad_three(0, -120)); 
}

void test_quad_four(void)
{
    TEST_ASSERT_TRUE(check_quad_four(1, -195)); 
    TEST_ASSERT_TRUE(check_quad_four(180, -1)); 
    TEST_ASSERT_TRUE(check_quad_four(80, -80));
    TEST_ASSERT_FALSE(check_quad_four(80, 0));
    TEST_ASSERT_FALSE(check_quad_four(-180,0)); 
    TEST_ASSERT_FALSE(check_quad_four(-50, -1)); 
    TEST_ASSERT_FALSE(check_quad_four(-50, 50));
    TEST_ASSERT_FALSE(check_quad_four(50,50));
}

void test_checkWhoAmIReg(void)
{
    c_getWhoAmIReg_ExpectAndReturn(0x48);
    TEST_ASSERT_TRUE(c_getWhoAmIReg()); 
    c_getWhoAmIReg_ExpectAndReturn(0x00);
    TEST_ASSERT_FALSE(c_getWhoAmIReg());  
}

void test_compass_init(void)
{
    c_getWhoAmIReg_ExpectAndReturn(0x48);
    c_setSingleMeasurementMode_Expect();
    LED_toggle_Expect(0x1); 
    TEST_ASSERT_TRUE(compass_init());

    c_getWhoAmIReg_ExpectAndReturn(0x12);
    LED_toggle_Expect(2);
    TEST_ASSERT_FALSE(compass_init()); 
}

void test_compass_reset(void)
{
    c_compass_softReset_Expect();
    c_getWhoAmIReg_ExpectAndReturn(0x48);
    c_setSingleMeasurementMode_Expect();
    LED_toggle_Expect(0x1); 
    compass_reset();

    c_compass_softReset_Expect();
    c_getWhoAmIReg_ExpectAndReturn(0x8);
    LED_toggle_Expect(2);
    compass_reset();
}

void test_compass_get_heading(void)
{   
    TEST_ASSERT_EQUAL(get_heading(0, 180), 0);
    TEST_ASSERT_EQUAL(get_heading(180, 0), 90); 
    TEST_ASSERT_EQUAL(get_heading(0, -190), 180);
    TEST_ASSERT_EQUAL(get_heading(-180, 0), 270);

    // Test Q1 and Q4
    TEST_ASSERT_EQUAL(get_heading(5 , 2), 68); 
    TEST_ASSERT_EQUAL(get_heading(100, -199), 153);
    TEST_ASSERT_EQUAL(get_heading(80, -75), 133);
    TEST_ASSERT_EQUAL(get_heading(2, -75), 178);
    TEST_ASSERT_EQUAL(get_heading(75, -2), 91);
    
    //TEST Q2 
    TEST_ASSERT_EQUAL(get_heading(-100, 100), 315);
    TEST_ASSERT_EQUAL(get_heading(-100, 2), 271);
    TEST_ASSERT_EQUAL(get_heading(-1, 5), 348);
    TEST_ASSERT_EQUAL(get_heading(-4, 4), 315);
    TEST_ASSERT_EQUAL(get_heading(-23, 67), 341);
    TEST_ASSERT_EQUAL(get_heading(-1, 100), 359);

    //TEST Q3
    TEST_ASSERT_EQUAL(get_heading(-100, -19), 259);
    TEST_ASSERT_EQUAL(get_heading(-50, -2), 267);
    TEST_ASSERT_EQUAL(get_heading(-45, -45), 225);

}

// void test_compass_get_data(void)
// {

//     compass_t expect = {0};
//     expect.x = c_compass_getX_ExpectAndReturn(50);
//     expect.y = c_compass_getY_ExpectAndReturns(50);
//     expect.heading = get_heading_ExpectAndReturn(45)
//     get_data_ExpectAndReturn(expect);
// }

