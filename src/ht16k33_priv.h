/*
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * resarding copyright ownership.  The ASF licenses this file
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

#ifndef __HT16K33_PRIV_H__
#define __HT16K33_PRIV_H__

#include "os/mynewt.h"
#include "hal/hal_i2c.h"
#include "i2cn/i2cn.h"
#include "modlog/modlog.h"
#include "stats/stats.h"
#include "syscfg/syscfg.h"
#include "ht16k33/ht16k33.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Writes a single byte to the HT16K33.
 *
 * @param value     The value to write to the HT16K33.
 *
 * @return 0 o, success, error code on error.
 */
int ht16k33_i2c_write8(uint8_t value);

/**
 * Writes multiple bytes to the HT16K33.
 *
 * @param buffer    Pointer to the buffer containing the data to write.
 * @param len       The number of bytes in the data buffer (max 8!).
 *
 * @return 0 o, success, error code on error.
 */
int ht16k33_i2c_writelen(uint8_t *buffer, uint8_t len);

#ifdef __cplusplus
}
#endif

#endif /* __HT16K33_PRIV_H__ */
