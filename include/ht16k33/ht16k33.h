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

 #ifdef __cplusplus
 extern "C" {
 #endif

/**
 * @addtogroup STRUCTS Structs and Enums
 *
 * HT16K33-related structs and enums.
 *
 * \ingroup HT16K33
 *  @{ */

/** @} */ /* End of STRUCT group */

/**
 * @addtogroup FUNC Functions
 *
 * Functions to work with the HT16K33.
 *
 * \ingroup HT16K33
 *  @{ */

int ht16k33_init(void);

/** @} */ /* End of FUNC group */

#if MYNEWT_VAL(HT16K33_CLI)
int ht16k33_shell_init(void);
#endif

#ifdef __cplusplus
}
#endif

#endif /* _MB_HT16K33_H_ */

/** @} */ /* End of HT16K33 group */
