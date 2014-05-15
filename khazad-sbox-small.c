
#include "khazad-sbox.h"


static const uint8_t sbox_small_table[16u] =
{
    0x39, 0xFE, 0xE5, 0x06, 0x5A, 0x42, 0xB3, 0xCC, 0xDF, 0xA0, 0x94, 0x6D, 0x77, 0x8B, 0x21, 0x18
};


static uint8_t khazad_sbox(uint8_t input)
{
    uint8_t         work_hi;
    uint8_t         work_lo;
    uint8_t         temp;
    uint_fast8_t    i;

    work_hi = input >> 4u;
    work_lo = input & 0xFu;

    for (i = 0; ; i++)
    {
#if 1
        if (i != 1)
        {
            work_hi = sbox_small_table[work_hi] >> 4u;      // P box
            work_lo = sbox_small_table[work_lo] & 0xFu;     // Q box
        }
        else
        {
            work_lo = sbox_small_table[work_lo] >> 4u;      // P box
            work_hi = sbox_small_table[work_hi] & 0xFu;     // Q box
        }
#else
        if (i == 1)
        {
            temp = work_hi;
            work_hi = work_lo;
            work_lo = temp;
        }
        work_hi = sbox_small_table[work_hi] >> 4u;      // P box
        work_lo = sbox_small_table[work_lo] & 0xFu;     // Q box
        if (i == 1)
        {
            temp = work_hi;
            work_hi = work_lo;
            work_lo = temp;
        }
#endif

        if (i > 1)
        {
            return (work_hi << 4u) | work_lo;
        }

        temp = work_hi;
        work_hi = (work_hi & 0xC) | (work_lo >> 2u);
        work_lo = ((temp << 2u ) & 0xC) | (work_lo & 3);
    }
}


void khazad_sbox_apply_block(uint8_t p_block[KHAZAD_BLOCK_SIZE])
{
    uint_fast8_t    i;

    for (i = 0; i < KHAZAD_BLOCK_SIZE; ++i)
    {
        p_block[i] = khazad_sbox(p_block[i]);
    }
}

void khazad_sbox_add_round_const(uint8_t p_block[KHAZAD_BLOCK_SIZE], uint_fast8_t round)
{
    uint_fast8_t    i;
    uint_fast8_t    round_start = round * KHAZAD_BLOCK_SIZE;

    for (i = 0; i < KHAZAD_BLOCK_SIZE; ++i)
    {
        p_block[i] ^= khazad_sbox(round_start + i);
    }
}

