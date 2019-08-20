/**
 * @file
 * This is a C header file that other C code can use to access UART2
 * driver that is written in C++
 *
 * Note that we have a C header file, but its implementation in C++
 * such that we can invoke C++ Uart driver
 *
 * The C Unit-test framework can use this header file to "Mock" the
 * UART2 API and carry out the tests.
 */
#ifndef UART2_C_H__
#define UART2_C_H__
#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>

bool uart2_getchar(char *byte, uint32_t timeout_ms);
bool uart2_init(unsigned int baudRate, int rxQSize, int txQSize);
bool uart2_gets(char* pBuff, int maxLen, unsigned int timeout);
bool uart2_puts(const char* pString, unsigned int timeout);

#ifdef __cplusplus
}
#endif
#endif /* UART2_C_H__ */

#ifndef UART0_C_H__
#define UART0_C_H__
#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>

bool my_uart0_puts(const char* pString, unsigned int timeout);

#ifdef __cplusplus
}
#endif
#endif /* UART2_C_H__ */
