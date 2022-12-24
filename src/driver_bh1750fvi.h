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
 * @file      driver_bh1750fvi.h
 * @brief     driver bh1750fvi header file
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

#ifndef DRIVER_BH1750FVI_H
#define DRIVER_BH1750FVI_H

#include <stdio.h>
#include <stdint.h>
#include <string.h>

#ifdef __cplusplus
extern "C"{
#endif

/**
 * @defgroup bh1750fvi_driver bh1750fvi driver function
 * @brief    bh1750fvi driver modules
 * @{
 */

/**
 * @addtogroup bh1750fvi_basic_driver
 * @{
 */

/**
 * @brief bh1750fvi address enumeration definition
 */
typedef enum
{
    BH1750FVI_ADDRESS_LOW  = 0x46,        /**< addr low */
    BH1750FVI_ADDRESS_HIGH = 0xB8,        /**< addr high */
} bh1750fvi_address_t;

/**
 * @brief bh1750fvi mode enumeration definition
 */
typedef enum
{
    BH1750FVI_MODE_HIGH_RESOLUTION_MODE  = 0x0,        /**< 1lx resolution */
    BH1750FVI_MODE_HIGH_RESOLUTION_MODE2 = 0x1,        /**< 0.5lx resolution */
    BH1750FVI_MODE_LOW_RESOLUTION_MODE   = 0x2,        /**< 4lx resolution */
} bh1750fvi_mode_t;

/**
 * @brief bh1750fvi handle structure definition
 */
typedef struct bh1750fvi_handle_s
{
    uint8_t iic_addr;                                                          /**< iic device address */
    uint8_t (*iic_init)(void);                                                 /**< point to an iic_init function address */
    uint8_t (*iic_deinit)(void);                                               /**< point to an iic_deinit function address */
    uint8_t (*iic_read_cmd)(uint8_t addr, uint8_t *buf, uint16_t len);         /**< point to an iic_read_cmd function address */
    uint8_t (*iic_write_cmd)(uint8_t addr, uint8_t *buf, uint16_t len);        /**< point to an iic_write_cmd function address */
    void (*delay_ms)(uint32_t ms);                                             /**< point to a delay_ms function address */
    void (*debug_print)(const char *const fmt, ...);                           /**< point to a debug_print function address */
    uint8_t mode;                                                              /**< chip mode */
    uint8_t t;                                                                 /**< measurement time */
    uint8_t inited;                                                            /**< inited flag */
} bh1750fvi_handle_t;

/**
 * @brief bh1750fvi information structure definition
 */
typedef struct bh1750fvi_info_s
{
    char chip_name[32];                /**< chip name */
    char manufacturer_name[32];        /**< manufacturer name */
    char interface[8];                 /**< chip interface name */
    float supply_voltage_min_v;        /**< chip min supply voltage */
    float supply_voltage_max_v;        /**< chip max supply voltage */
    float max_current_ma;              /**< chip max current */
    float temperature_min;             /**< chip min operating temperature */
    float temperature_max;             /**< chip max operating temperature */
    uint32_t driver_version;           /**< driver version */
} bh1750fvi_info_t;

/**
 * @}
 */

/**
 * @defgroup bh1750fvi_link_driver bh1750fvi link driver function
 * @brief    bh1750fvi link driver modules
 * @ingroup  bh1750fvi_driver
 * @{
 */

/**
 * @brief     initialize bh1750fvi_handle_t structure
 * @param[in] HANDLE points to a bh1750fvi handle structure
 * @param[in] STRUCTURE is bh1750fvi_handle_t
 * @note      none
 */
#define DRIVER_BH1750FVI_LINK_INIT(HANDLE, STRUCTURE)               memset(HANDLE, 0, sizeof(STRUCTURE))

/**
 * @brief     link iic_init function
 * @param[in] HANDLE points to a bh1750fvi handle structure
 * @param[in] FUC points to an iic_init function address
 * @note      none
 */
#define DRIVER_BH1750FVI_LINK_IIC_INIT(HANDLE, FUC)                 (HANDLE)->iic_init = FUC

/**
 * @brief     link iic_deinit function
 * @param[in] HANDLE points to a bh1750fvi handle structure
 * @param[in] FUC points to an iic_deinit function address
 * @note      none
 */
#define DRIVER_BH1750FVI_LINK_IIC_DEINIT(HANDLE, FUC)               (HANDLE)->iic_deinit = FUC

/**
 * @brief     link iic_read_cmd function
 * @param[in] HANDLE points to a bh1750fvi handle structure
 * @param[in] FUC points to an iic_read_cmd function address
 * @note      none
 */
#define DRIVER_BH1750FVI_LINK_IIC_READ_CMD(HANDLE, FUC)             (HANDLE)->iic_read_cmd = FUC

/**
 * @brief     link iic_write_cmd function
 * @param[in] HANDLE points to a bh1750fvi handle structure
 * @param[in] FUC points to an iic_write_cmd function address
 * @note      none
 */
#define DRIVER_BH1750FVI_LINK_IIC_WRITE_CMD(HANDLE, FUC)            (HANDLE)->iic_write_cmd = FUC

/**
 * @brief     link delay_ms function
 * @param[in] HANDLE points to a bh1750fvi handle structure
 * @param[in] FUC points to a delay_ms function address
 * @note      none
 */
#define DRIVER_BH1750FVI_LINK_DELAY_MS(HANDLE, FUC)                 (HANDLE)->delay_ms = FUC

/**
 * @brief     link debug_print function
 * @param[in] HANDLE points to a bh1750fvi handle structure
 * @param[in] FUC points to a debug_print function address
 * @note      none
 */
#define DRIVER_BH1750FVI_LINK_DEBUG_PEINT(HANDLE, FUC)              (HANDLE)->debug_print = FUC

/**
 * @}
 */

/**
 * @defgroup bh1750fvi_basic_driver bh1750fvi basic driver function
 * @brief    bh1750fvi basic driver modules
 * @ingroup  bh1750fvi_driver
 * @{
 */

/**
 * @brief      get chip's information
 * @param[out] *info points to a bh1750fvi info structure
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 * @note       none
 */
uint8_t bh1750fvi_info(bh1750fvi_info_t *info);

/**
 * @brief     set the address pin
 * @param[in] *handle points to a bh1750fvi handle structure
 * @param[in] addr_pin is the chip address pins
 * @return    status code
 *            - 0 success
 *            - 2 handle is NULL
 * @note      none
 */
uint8_t bh1750fvi_set_addr_pin(bh1750fvi_handle_t *handle, bh1750fvi_address_t addr_pin);

/**
 * @brief      get the address pin
 * @param[in]  *handle points to a bh1750fvi handle structure
 * @param[out] *addr_pin points to a chip address pins buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 * @note       none
 */
uint8_t bh1750fvi_get_addr_pin(bh1750fvi_handle_t *handle, bh1750fvi_address_t *addr_pin);

/**
 * @brief     set the mode
 * @param[in] *handle points to a bh1750fvi handle structure
 * @param[in] mode is the set mode
 * @return    status code
 *            - 0 success
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t bh1750fvi_set_mode(bh1750fvi_handle_t *handle, bh1750fvi_mode_t mode);

/**
 * @brief      get the mode
 * @param[in]  *handle points to a bh1750fvi handle structure
 * @param[out] *mode points to a mode buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t bh1750fvi_get_mode(bh1750fvi_handle_t *handle, bh1750fvi_mode_t *mode);

/**
 * @brief     initialize the chip
 * @param[in] *handle points to a bh1750fvi handle structure
 * @return    status code
 *            - 0 success
 *            - 1 iic failed
 *            - 2 handle is NULL
 *            - 3 linked functions is NULL
 *            - 4 power on failed
 *            - 5 reset failed
 * @note      none
 */
uint8_t bh1750fvi_init(bh1750fvi_handle_t *handle);

/**
 * @brief     close the chip
 * @param[in] *handle points to a bh1750fvi handle structure
 * @return    status code
 *            - 0 success
 *            - 1 iic deinit failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 power down failed
 * @note      none
 */
uint8_t bh1750fvi_deinit(bh1750fvi_handle_t *handle);

/**
 * @brief      read data from the chip once
 * @param[in]  *handle points to a bh1750fvi handle structure
 * @param[out] *raw points to a raw lux buffer
 * @param[out] *lux points to a converted lux buffer
 * @return     status code
 *             - 0 success
 *             - 1 single read failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 *             - 4 mode is invalid
 * @note       none
 */
uint8_t bh1750fvi_single_read(bh1750fvi_handle_t *handle, uint16_t *raw, float *lux);

/**
 * @brief      read data from the chip continuously
 * @param[in]  *handle points to a bh1750fvi handle structure
 * @param[out] *raw points to a raw lux buffer
 * @param[out] *lux points to a converted lux buffer
 * @return     status code
 *             - 0 success
 *             - 1 continuous read failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       this function can be used only after run bh1750fvi_start_continuous_read
 *             and can be stopped by bh1750fvi_stop_continuous_read
 */
uint8_t bh1750fvi_continuous_read(bh1750fvi_handle_t *handle, uint16_t *raw, float *lux);

/**
 * @brief     start chip reading
 * @param[in] *handle points to a bh1750fvi handle structure
 * @return    status code
 *            - 0 success
 *            - 1 start continuous read failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 mode is invalid
 * @note      none
 */
uint8_t bh1750fvi_start_continuous_read(bh1750fvi_handle_t *handle);

/**
 * @brief     stop chip reading
 * @param[in] *handle points to a bh1750fvi handle structure
 * @return    status code
 *            - 0 success
 *            - 1 stop continuous read failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 mode is invalid
 * @note      none
 */
uint8_t bh1750fvi_stop_continuous_read(bh1750fvi_handle_t *handle);

/**
 * @brief     power down
 * @param[in] *handle points to a bh1750fvi handle structure
 * @return    status code
 *            - 0 success
 *            - 1 power down failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t bh1750fvi_power_down(bh1750fvi_handle_t *handle);

/**
 * @brief     power on
 * @param[in] *handle points to a bh1750fvi handle structure
 * @return    status code
 *            - 0 success
 *            - 1 power on failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t bh1750fvi_power_on(bh1750fvi_handle_t *handle);

/**
 * @brief     reset
 * @param[in] *handle points to a bh1750fvi handle structure
 * @return    status code
 *            - 0 success
 *            - 1 reset failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t bh1750fvi_reset(bh1750fvi_handle_t *handle);

/**
 * @brief     set the measurement time
 * @param[in] *handle points to a bh1750fvi handle structure
 * @param[in] t is the set measurement time
 * @return    status code
 *            - 0 success
 *            - 1 set measurement time failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 t < 31 or t > 254
 * @note      31 <= t <= 254
 */
uint8_t bh1750fvi_set_measurement_time(bh1750fvi_handle_t *handle, uint8_t t);

/**
 * @}
 */

/**
 * @defgroup bh1750fvi_extern_driver bh1750fvi extern driver function
 * @brief    bh1750fvi extern driver modules
 * @ingroup  bh1750fvi_driver
 * @{
 */

/**
 * @brief     set the chip register
 * @param[in] *handle points to a bh1750fvi handle structure
 * @param[in] *buf points to a data buffer.
 * @param[in] len is the data buffer
 * @return    status code
 *            - 0 success
 *            - 1 write failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t bh1750fvi_set_reg(bh1750fvi_handle_t *handle, uint8_t *buf, uint16_t len);

/**
 * @brief      get the chip register
 * @param[in]  *handle points to a bh1750fvi handle structure
 * @param[out] *buf points to a data buffer.
 * @param[in]  len is the data buffer
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t bh1750fvi_get_reg(bh1750fvi_handle_t *handle, uint8_t *buf, uint16_t len);

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif
