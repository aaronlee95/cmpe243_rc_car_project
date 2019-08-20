#include "c_uart2.h"
#include "uart2.hpp"
#include "uart0.hpp"

// Assuming UART2 is already initialized
// You may want to also add uart2_init() in C

bool uart2_getchar(char *byte, uint32_t timeout_ms) {
    return Uart2::getInstance().getChar(byte, timeout_ms);
}

bool uart2_init(unsigned int baudRate, int rxQSize=32, int txQSize=64)
{
    return Uart2::getInstance().init(baudRate, rxQSize, txQSize);
}

bool uart2_gets(char* pBuff, int maxLen, unsigned int timeout)
{
    return Uart2::getInstance().gets(pBuff, maxLen, timeout);
}

bool uart2_puts(const char* pString, unsigned int timeout)
{
    return Uart2::getInstance().put(pString, timeout);
}

bool my_uart0_puts(const char* pString, unsigned int timeout)
{
    return Uart0::getInstance().put(pString, timeout);
}
