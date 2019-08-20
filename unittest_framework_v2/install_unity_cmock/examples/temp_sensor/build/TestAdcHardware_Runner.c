/* AUTOGENERATED FILE. DO NOT EDIT. */

/*=======Test Runner Used To Run Each Test Below=====*/
#define RUN_TEST(TestFunc, TestLineNum) \
{ \
  Unity.CurrentTestName = #TestFunc; \
  Unity.CurrentTestLineNumber = TestLineNum; \
  Unity.NumberOfTests++; \
  CMock_Init(); \
  UNITY_CLR_DETAILS(); \
  if (TEST_PROTECT()) \
  { \
      setUp(); \
      TestFunc(); \
  } \
  if (TEST_PROTECT()) \
  { \
    tearDown(); \
    CMock_Verify(); \
  } \
  CMock_Destroy(); \
  UnityConcludeTest(); \
}

/*=======Automagically Detected Files To Include=====*/
#ifdef __WIN32__
#define UNITY_INCLUDE_SETUP_STUBS
#endif
#include "unity.h"
#include "cmock.h"
#ifndef UNITY_EXCLUDE_SETJMP_H
#include <setjmp.h>
#endif
#include <stdio.h>
#include "Types.h"
#include "Types.h"
#include "AdcHardware.h"
#include "MockAdcHardwareConfigurator.h"
#include "MockAdcTemperatureSensor.h"

/*=======External Functions This Runner Calls=====*/
extern void setUp(void);
extern void tearDown(void);
extern void testInitShouldDelegateToConfiguratorAndTemperatureSensor(void);
extern void testGetSampleCompleteShouldReturn_FALSE_WhenTemperatureSensorSampleReadyReturns_FALSE(void);
extern void testGetSampleCompleteShouldReturn_TRUE_WhenTemperatureSensorSampleReadyReturns_TRUE(void);
extern void testGetSampleShouldDelegateToAdcTemperatureSensor(void);


/*=======Mock Management=====*/
static void CMock_Init(void)
{
  MockAdcHardwareConfigurator_Init();
  MockAdcTemperatureSensor_Init();
}
static void CMock_Verify(void)
{
  MockAdcHardwareConfigurator_Verify();
  MockAdcTemperatureSensor_Verify();
}
static void CMock_Destroy(void)
{
  MockAdcHardwareConfigurator_Destroy();
  MockAdcTemperatureSensor_Destroy();
}

/*=======Suite Setup=====*/
static void suite_setup(void)
{
#if defined(UNITY_WEAK_ATTRIBUTE) || defined(UNITY_WEAK_PRAGMA)
  suiteSetUp();
#endif
}

/*=======Suite Teardown=====*/
static int suite_teardown(int num_failures)
{
#if defined(UNITY_WEAK_ATTRIBUTE) || defined(UNITY_WEAK_PRAGMA)
  return suiteTearDown(num_failures);
#else
  return num_failures;
#endif
}

/*=======Test Reset Option=====*/
void resetTest(void);
void resetTest(void)
{
  CMock_Verify();
  CMock_Destroy();
  tearDown();
  CMock_Init();
  setUp();
}


/*=======MAIN=====*/
int main(void)
{
  suite_setup();
  UnityBegin("test/TestAdcHardware.c");
  RUN_TEST(testInitShouldDelegateToConfiguratorAndTemperatureSensor, 15);
  RUN_TEST(testGetSampleCompleteShouldReturn_FALSE_WhenTemperatureSensorSampleReadyReturns_FALSE, 25);
  RUN_TEST(testGetSampleCompleteShouldReturn_TRUE_WhenTemperatureSensorSampleReadyReturns_TRUE, 31);
  RUN_TEST(testGetSampleShouldDelegateToAdcTemperatureSensor, 37);

  CMock_Guts_MemFreeFinal();
  return suite_teardown(UnityEnd());
}