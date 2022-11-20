/**
 * Copyright (c) 2015 - present LibDriver All rights reserved
 * 
 * The MIT License (MIT)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE. 
 *
 * @file      driver_bh1750fvi_basic.h
 * @brief     driver bh1750fvi basic header file
 * @version   1.0.0
 * @author    Shifeng Li
 * @date      2022-11-30
 *
 * <h3>history</h3>
 * <table>
 * <tr><th>Date        <th>Version  <th>Author      <th>Description
 * <tr><td>2022/11/30  <td>1.0      <td>Shifeng Li  <td>first upload
 * </table>
 */

#ifndef DRIVER_BH1750FVI_BASIC_H
#define DRIVER_BH1750FVI_BASIC_H

#include "driver_bh1750fvi_interface.h"

#ifdef __cplusplus
extern "C"{
#endif

/**
 * @defgroup bh1750fvi_example_driver bh1750fvi example driver function
 * @brief    bh1750fvi example driver modules
 * @ingroup  bh1750fvi_driver
 * @{
 */

/**
 * @brief bh1750fvi basic example default definition
 */
#define BH1750FVI_BASIC_DEFAULT_MODE                    BH1750FVI_MODE_HIGH_RESOLUTION_MODE        /**< high resolution mode */
#define BH1750FVI_BASIC_DEFAULT_MEASUREMENT_TIME        69                                         /**< measurement time 69 */

/**
 * @brief     basic example init
 * @param[in] addr_pin is the iic device address
 * @return    status code
 *            - 0 success
 *            - 1 init failed
 * @note      none
 */
uint8_t bh1750fvi_basic_init(bh1750fvi_address_t addr_pin);

/**
 * @brief      basic example read
 * @param[out] *lux points to a converted lux buffer
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 * @note       none
 */
uint8_t bh1750fvi_basic_read(float *lux);

/**
 * @brief  basic example deinit
 * @return status code
 *         - 0 success
 *         - 1 deinit failed
 * @note   none
 */
uint8_t bh1750fvi_basic_deinit(void);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif
