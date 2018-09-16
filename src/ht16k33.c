/*
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 */

#include "ht16k33/ht16k33.h"
#include "ht16k33_priv.h"

/* Define the stats section and records */
STATS_SECT_START(ht16k33_stat_section)
    STATS_SECT_ENTRY(errors)
STATS_SECT_END

/* Define stat names for querying */
STATS_NAME_START(ht16k33_stat_section)
    STATS_NAME(ht16k33_stat_section, errors)
STATS_NAME_END(ht16k33_stat_section)

/* Global variable used to hold stats data */
STATS_SECT_DECL(ht16k33_stat_section) g_ht16k33stats;

#define HT16K33_LOG(lvl_, ...) \
    MODLOG_ ## lvl_(MYNEWT_VAL(HT16K33_LOG_MODULE), __VA_ARGS__)

/** Buffer for the four display characters plus a starting address byte. */
static uint8_t ht16k33_buffer_16[9] = { 0 };

/** Alpha-numeric lookup table. */
const uint16_t ht16k33_tbl_alpha[] = {
    0b0000000000000001,
    0b0000000000000010,
    0b0000000000000100,
    0b0000000000001000,
    0b0000000000010000,
    0b0000000000100000,
    0b0000000001000000,
    0b0000000010000000,
    0b0000000100000000,
    0b0000001000000000,
    0b0000010000000000,
    0b0000100000000000,
    0b0001000000000000,
    0b0010000000000000,
    0b0100000000000000,
    0b1000000000000000,
    0b0000000000000000,
    0b0000000000000000,
    0b0000000000000000,
    0b0000000000000000,
    0b0000000000000000,
    0b0000000000000000,
    0b0000000000000000,
    0b0000000000000000,
    0b0001001011001001,
    0b0001010111000000,
    0b0001001011111001,
    0b0000000011100011,
    0b0000010100110000,
    0b0001001011001000,
    0b0011101000000000,
    0b0001011100000000,
    0b0000000000000000, //
    0b0000000000000110, // !
    0b0000001000100000, // "
    0b0001001011001110, // #
    0b0001001011101101, // $
    0b0000110000100100, // %
    0b0010001101011101, // &
    0b0000010000000000, // '
    0b0010010000000000, // (
    0b0000100100000000, // )
    0b0011111111000000, // *
    0b0001001011000000, // +
    0b0000100000000000, // ,
    0b0000000011000000, // -
    0b0000000000000000, // .
    0b0000110000000000, // /
    0b0000110000111111, // 0
    0b0000000000000110, // 1
    0b0000000011011011, // 2
    0b0000000010001111, // 3
    0b0000000011100110, // 4
    0b0010000001101001, // 5
    0b0000000011111101, // 6
    0b0000000000000111, // 7
    0b0000000011111111, // 8
    0b0000000011101111, // 9
    0b0001001000000000, // :
    0b0000101000000000, // ;
    0b0010010000000000, // <
    0b0000000011001000, // =
    0b0000100100000000, // >
    0b0001000010000011, // ?
    0b0000001010111011, // @
    0b0000000011110111, // A
    0b0001001010001111, // B
    0b0000000000111001, // C
    0b0001001000001111, // D
    0b0000000011111001, // E
    0b0000000001110001, // F
    0b0000000010111101, // G
    0b0000000011110110, // H
    0b0001001000000000, // I
    0b0000000000011110, // J
    0b0010010001110000, // K
    0b0000000000111000, // L
    0b0000010100110110, // M
    0b0010000100110110, // N
    0b0000000000111111, // O
    0b0000000011110011, // P
    0b0010000000111111, // Q
    0b0010000011110011, // R
    0b0000000011101101, // S
    0b0001001000000001, // T
    0b0000000000111110, // U
    0b0000110000110000, // V
    0b0010100000110110, // W
    0b0010110100000000, // X
    0b0001010100000000, // Y
    0b0000110000001001, // Z
    0b0000000000111001, // [
    0b0010000100000000, //
    0b0000000000001111, // ]
    0b0000110000000011, // ^
    0b0000000000001000, // _
    0b0000000100000000, // `
    0b0001000001011000, // a
    0b0010000001111000, // b
    0b0000000011011000, // c
    0b0000100010001110, // d
    0b0000100001011000, // e
    0b0000000001110001, // f
    0b0000010010001110, // g
    0b0001000001110000, // h
    0b0001000000000000, // i
    0b0000000000001110, // j
    0b0011011000000000, // k
    0b0000000000110000, // l
    0b0001000011010100, // m
    0b0001000001010000, // n
    0b0000000011011100, // o
    0b0000000101110000, // p
    0b0000010010000110, // q
    0b0000000001010000, // r
    0b0010000010001000, // s
    0b0000000001111000, // t
    0b0000000000011100, // u
    0b0010000000000100, // v
    0b0010100000010100, // w
    0b0010100011000000, // x
    0b0010000000001100, // y
    0b0000100001001000, // z
    0b0000100101001001, // {
    0b0001001000000000, // |
    0b0010010010001001, // }
    0b0000010100100000, // ~
    0b0011111111111111,
};

int
ht16k33_i2c_write8(uint8_t value)
{
    int rc;
    uint8_t payload[1] = { value };

    struct hal_i2c_master_data data_struct = {
        .address = MYNEWT_VAL(HT16K33_ITF_ADDR),
        .len = 1,
        .buffer = payload
    };

    /* TODO: Add locking interface for I2C access. */

    rc = i2cn_master_write(MYNEWT_VAL(HT16K33_ITF_NUM), &data_struct,
        OS_TICKS_PER_SEC / 10, 1, MYNEWT_VAL(HT16K33_I2C_RETRIES));
    if (rc) {
        HT16K33_LOG(ERROR,
                    "Failed to write to 0x%02X with value 0x%02lX\n",
                    data_struct.address, value);
        STATS_INC(g_ht16k33stats, errors);
    }

    /* TODO: Unlock here. */

    return rc;
}

int
ht16k33_i2c_writelen(uint8_t *buffer, uint8_t len)
{
    int rc;
    uint8_t payload[16] = { 0 };

    struct hal_i2c_master_data data_struct = {
        .address = MYNEWT_VAL(HT16K33_ITF_ADDR),
        .len = len,
        .buffer = payload
    };

    if (len > sizeof(payload)) {
        rc = OS_EINVAL;
        goto err;
    }

    memcpy(payload, buffer, len);

    /* TODO: Add locking interface for I2C access. */

    /* Write data */
    rc = i2cn_master_write(MYNEWT_VAL(HT16K33_ITF_NUM), &data_struct,
        OS_TICKS_PER_SEC / 10, len, MYNEWT_VAL(HT16K33_I2C_RETRIES));
    if (rc) {
        HT16K33_LOG(ERROR, "I2C access failed at address 0x%02X\n",
                    data_struct.address);
        STATS_INC(g_ht16k33stats, errors);
        goto err;
    }

err:
    /* TODO: Unlock here. */

    return rc;
}

int
ht16k33_init(uint8_t brightness)
{
    int rc;

    /* Insert a short delay to allow the IC to start up. */
    os_time_delay((1 * OS_TICKS_PER_SEC)/1000);

    /* Initialise the stats entry. */
    rc = stats_init(
        STATS_HDR(g_ht16k33stats),
        STATS_SIZE_INIT_PARMS(g_ht16k33stats, STATS_SIZE_32),
        STATS_NAME_INIT_PARMS(ht16k33_stat_section));
    if (rc != 0) {
        goto err;
    }

    /* Register the entry with the stats registry. */
    rc = stats_register("ht16k33", STATS_HDR(g_ht16k33stats));
    if (rc != 0) {
        goto err;
    }

    /* Enable the controller. */
    rc = ht16k33_write_cmd(HT16K33_REG_CMD_MODE_ON);
    if (rc != 0) {
        goto err;
    }

    /* Clear the display. */
    rc = ht16k33_clear();
    if (rc != 0) {
        goto err;
    }

    /* Turn the display on. */
    rc = ht16k33_write_cmd(HT16K33_REG_DISP_ON_BLINK_NONE);
    if (rc != 0) {
        goto err;
    }

    /* Set the display brightness */
    rc = ht16k33_write_cmd(brightness);
    if (rc != 0) {
        goto err;
    }

    return (0);
err:
    return (rc);
}

int
ht16k33_clear(void)
{
    int rc;

    /* Clear the buffer. */
    memset(ht16k33_buffer_16, 0, sizeof(ht16k33_buffer_16));

    rc = ht16k33_i2c_writelen(ht16k33_buffer_16,
        sizeof(ht16k33_buffer_16));
    if (rc != 0) {
        goto err;
    }

    return 0;
err:
    return rc;
}

int
ht16k33_write_cmd(uint8_t reg)
{
    int rc;

    rc = ht16k33_i2c_write8(reg);
    if (rc != 0) {
        goto err;
    }

    return 0;
err:
    return rc;
}

int
ht16k33_write_num(uint8_t addr, uint8_t value, bool dec)
{
    int rc;

    /* Make sure we stay in range. */
    if (value > 9) {
        rc = OS_EINVAL;
        goto err;
    }

    /* Set the address and hex data. */
    ht16k33_buffer_16[addr*2+1] = (ht16k33_tbl_alpha[value + 48] & 0xFF);
    ht16k33_buffer_16[addr*2+2] = (ht16k33_tbl_alpha[value + 48] >> 8) & 0xFF;

    /* Add the decimal point to the output if requested. */
    if (dec) {
        ht16k33_buffer_16[addr*2+2] |= 0x40;
    }

    rc = ht16k33_i2c_writelen(ht16k33_buffer_16, sizeof(ht16k33_buffer_16));
    if (rc != 0) {
        goto err;
    }

    return 0;
err:
    return rc;
}

int
ht16k33_write_hex(uint8_t addr, uint8_t value, bool dec)
{
    int rc;

    /* Make sure we stay in range. */
    if (value > 0xF) {
        rc = OS_EINVAL;
        goto err;
    }

    if (value < 10) {
        /* Handle decimal values 0..9 */
        return ht16k33_write_num(addr, value, dec);
    } else {
        /* Display HEX value as ASCII */
        return ht16k33_write_alpha(addr, value+55, dec);
    }

err:
    return rc;
}

int
ht16k33_write_alpha(uint8_t addr, uint8_t value, bool dec)
{
    int rc;

    /* Make sure we stay in range. */
    if (value >= 128) {
        rc = OS_EINVAL;
        goto err;
    }

    /* Set the address and hex data. */
    ht16k33_buffer_16[addr*2+1] = (ht16k33_tbl_alpha[value] & 0xFF);
    ht16k33_buffer_16[addr*2+2] = (ht16k33_tbl_alpha[value] >> 8) & 0xFF;

    /* Add the decimal point to the output if requested. */
    if (dec) {
        ht16k33_buffer_16[addr*2+2] |= 0x40;
    }

    rc = ht16k33_i2c_writelen(ht16k33_buffer_16, sizeof(ht16k33_buffer_16));
    if (rc != 0) {
        goto err;
    }

    return 0;
err:
    return rc;
}
