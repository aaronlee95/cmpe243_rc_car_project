#include "bit_count.h"


uint32_t bit_count_get_uint8(uint8_t value)
{
    uint32_t count = 0;

    for (int i = 0; i < 8; i++) {
        if (value & (1 << i)) {
            ++count;
        }
    }

    return count;
}
