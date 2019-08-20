#include "unity.h" // Single Unity Test Framework include
#include <stdio.h>

#include "c_period_callbacks.h"

// Mock the UART2 and UART3 C header API
#include "Mockc_uart2.h"
#include "Mockc_uart3.h"

void setUp(void) {
}
void tearDown(void) {
}

void test_C_period_init(void) {
  uart3_init_ExpectAndReturn(9600, 256, 256, true);
  TEST_ASSERT_TRUE(C_period_init());
}

void test_C_period_reg_tlm(void) {
  TEST_ASSERT_TRUE(C_period_reg_tlm());
}

void test_C_period_1Hz(void) {
  C_period_1Hz(0);
}

void test_C_period_10Hz(void) {
  C_period_10Hz(0);
}

void test_C_period_100Hz(void) {
  char * out = "fruit";
  uart3_puts_ExpectAndReturn(out, 0, true);
  uart3_gets_ExpectAndReturn("", 256, 0, true);
  my_uart0_puts_ExpectAndReturn("", 0, true);
  C_period_100Hz(0);
}

void test_C_period_1000Hz(void) {
  C_period_1000Hz(0);
}
