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

/**
 * \defgroup HT16K33 ht15k33
 *
 * Functions to work with the HT16K33 14-segment display driver.
 */

 #ifndef _MB_HT16K33_H_
 #define _MB_HT16K33_H_

 #include <stdint.h>
 #include "os/mynewt.h"

/**
 * @addtogroup DEFINES Defines
 *
 * HTK16K33-related public DEFINEs.
 *
 * \ingroup HT16K33
 * @{ */

 /** Sets the IC operating mode to ON via the COMMAND register. */
 #define HT16K33_REG_CMD_MODE_ON              (0b00100001)

 /** Sets the IC operating mode to STANDBY via the COMMAND register. */
 #define HT16K33_REG_CMD_MODE_STDBY           (0b00100000)

 /** Turns the display on and sets blinky rate to 0. */
 #define HT16K33_REG_DISP_ON_BLINK_NONE       (0b10000001)

 /** Turns the display on and sets blinky rate to 2Hz. */
 #define HT16K33_REG_DISP_ON_BLINK_2HZ        (0b10000011)

 /** Turns the display on and sets blinky rate to 1Hz. */
 #define HT16K33_REG_DISP_ON_BLINK_1HZ        (0b10000101)

 /** Turns the display on and sets blinky rate to 0.5Hz. */
 #define HT16K33_REG_DISP_ON_BLINK_0_5HZ      (0b10000111)

 /** Turns the display off. */
 #define HT16K33_REG_DISP_OFF                 (0b00000000)

 /* Sets the display dimming duty cycle (brightness) to 1/16. */
 #define HTK16K33_REG_DIM_1                   (0b11100000)

 /* Sets the display dimming duty cycle (brightness) to 2/16. */
 #define HTK16K33_REG_DIM_2                   (0b11100001)

 /* Sets the display dimming duty cycle (brightness) to 3/16. */
 #define HTK16K33_REG_DIM_3                   (0b11100010)

 /* Sets the display dimming duty cycle (brightness) to 4/16. */
 #define HTK16K33_REG_DIM_4                   (0b11100011)

 /* Sets the display dimming duty cycle (brightness) to 5/16. */
 #define HTK16K33_REG_DIM_5                   (0b11100100)

 /* Sets the display dimming duty cycle (brightness) to 6/16. */
 #define HTK16K33_REG_DIM_6                   (0b11100101)

 /* Sets the display dimming duty cycle (brightness) to 7/16. */
 #define HTK16K33_REG_DIM_7                   (0b11100110)

 /* Sets the display dimming duty cycle (brightness) to 8/16. */
 #define HTK16K33_REG_DIM_8                   (0b11100111)

 /* Sets the display dimming duty cycle (brightness) to 9/16. */
 #define HTK16K33_REG_DIM_9                   (0b11101000)

 /* Sets the display dimming duty cycle (brightness) to 10/16. */
 #define HTK16K33_REG_DIM_10                  (0b11101001)

 /* Sets the display dimming duty cycle (brightness) to 11/16. */
 #define HTK16K33_REG_DIM_11                  (0b11101010)

 /* Sets the display dimming duty cycle (brightness) to 12/16. */
 #define HTK16K33_REG_DIM_12                  (0b11101011)

 /* Sets the display dimming duty cycle (brightness) to 13/16. */
 #define HTK16K33_REG_DIM_13                  (0b11101100)

 /* Sets the display dimming duty cycle (brightness) to 14/16. */
 #define HTK16K33_REG_DIM_14                  (0b11101101)

 /* Sets the display dimming duty cycle (brightness) to 15/16. */
 #define HTK16K33_REG_DIM_15                  (0b11101110)

 /* Sets the display dimming duty cycle (brightness) to 16/16. */
 #define HTK16K33_REG_DIM_16                  (0b11101111)

 /** @} */ /* End of DEFINES group */

 #ifdef __cplusplus
 extern "C" {
 #endif

/**
 * @addtogroup FUNC Functions
 *
 * Functions to work with the HT16K33.
 *
 * \ingroup HT16K33
 *  @{ */

/**
 * Initialises and enables the display controller and the display.
 *
 * @param brightness    The brightness register value to apply.
 *
 * @return 0 on success, an error code on error.
 */
int ht16k33_init(uint8_t brightness);


/**
 * Clears the display.
 *
 * @return 0 on success, an error code on error.
 */
int ht16k33_clear(void);

/**
 * Writes a command byte to the HT16K33.
 *
 * @param reg       The register value to write.
 *
 * @return 0 on success, an error code on error.
 */
int ht16k33_write_cmd(uint8_t reg);

/**
 * Writes a decimal value to the specified address on the HT16K33.
 *
 * @param addr      The address to write data to.
 * @param value     The decimal value to write to 'addr'.
 * @param dec       Whether or not to display the decimal point.
 *
 * @return 0 on success, an error code on error.
 */
int ht16k33_write_num(uint8_t addr, uint8_t value, bool dec);

/**
 * Writes a hexadecimal value to the specified address on the HT16K33.
 *
 * @param addr      The address to write data to.
 * @param value     The hexadecimal value to write to 'addr'.
 * @param dec       Whether or not to display the decimal point.
 *
 * @return 0 on success, an error code on error.
 */
int ht16k33_write_hex(uint8_t addr, uint8_t value, bool dec);

/**
 * Writes an alpha-numeric value to the specified address on the HT16K33.
 *
 * @param addr      The address to write data to.
 * @param value     The alpha-numeric value to write to 'addr'.
 * @param dec       Whether or not to display the decimal point.
 *
 * @return 0 on success, an error code on error.
 */
int ht16k33_write_alpha(uint8_t addr, uint8_t value, bool dec);

#if MYNEWT_VAL(HT16K33_CLI)
/**
 * Initialises the shell command for this driver if enabled in syscfg.yml.
 *
 * @return 0 on success, an error code on error.
 **/
int ht16k33_shell_init(void);
#endif

/** @} */ /* End of FUNC group */

#ifdef __cplusplus
}
#endif

#endif /* _MB_HT16K33_H_ */

/** @} */ /* End of HT16K33 group */
