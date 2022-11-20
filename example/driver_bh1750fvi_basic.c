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
 * @file      driver_bh1750fvi_basic.c
 * @brief     driver bh1750fvi basic source file
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

#include "driver_bh1750fvi_basic.h"

static bh1750fvi_handle_t gs_handle;        /**< bh1750fvi handle */

/**
 * @brief     basic example init
 * @param[in] addr_pin is the iic device address
 * @return    status code
 *            - 0 success
 *            - 1 init failed
 * @note      none
 */
uint8_t bh1750fvi_basic_init(bh1750fvi_address_t addr_pin)
{
    uint8_t res;
    
    /* link interface function */
    DRIVER_BH1750FVI_LINK_INIT(&gs_handle, bh1750fvi_handle_t);
    DRIVER_BH1750FVI_LINK_IIC_INIT(&gs_handle, bh1750fvi_interface_iic_init);
    DRIVER_BH1750FVI_LINK_IIC_DEINIT(&gs_handle, bh1750fvi_interface_iic_deinit);
    DRIVER_BH1750FVI_LINK_IIC_READ_CMD(&gs_handle, bh1750fvi_interface_iic_read_cmd);
    DRIVER_BH1750FVI_LINK_IIC_WRITE_CMD(&gs_handle, bh1750fvi_interface_iic_write_cmd);
    DRIVER_BH1750FVI_LINK_DELAY_MS(&gs_handle, bh1750fvi_interface_delay_ms);
    DRIVER_BH1750FVI_LINK_DEBUG_PEINT(&gs_handle, bh1750fvi_interface_debug_print);
    
    /* set the addr pin */
    res = bh1750fvi_set_addr_pin(&gs_handle, addr_pin);
    if (res != 0)
    {
        bh1750fvi_interface_debug_print("bh1750fvi: set addr pin failed.\n");
       
        return 1;
    }
    
    /* init */
    res = bh1750fvi_init(&gs_handle);
    if (res != 0)
    {
        bh1750fvi_interface_debug_print("bh1750fvi: init failed.\n");
       
        return 1;
    }
    
    /* power on */
    res = bh1750fvi_power_on(&gs_handle);
    if (res != 0)
    {
        bh1750fvi_interface_debug_print("bh1750fvi: power on failed.\n");
        (void)bh1750fvi_deinit(&gs_handle);
       
        return 1;
    }
    
    /* set mode */
    res = bh1750fvi_set_mode(&gs_handle, BH1750FVI_BASIC_DEFAULT_MODE);
    if (res != 0)
    {
        bh1750fvi_interface_debug_print("bh1750fvi: set mode failed.\n");
        (void)bh1750fvi_deinit(&gs_handle);
       
        return 1;
    }
    
    /* set measurement time */
    res = bh1750fvi_set_measurement_time(&gs_handle, BH1750FVI_BASIC_DEFAULT_MEASUREMENT_TIME);
    if (res != 0)
    {
        bh1750fvi_interface_debug_print("bh1750fvi: set measurement time failed.\n");
        (void)bh1750fvi_deinit(&gs_handle);
       
        return 1;
    }
    
    /* start continuous read */
    res = bh1750fvi_start_continuous_read(&gs_handle);
    if (res != 0)
    {
        bh1750fvi_interface_debug_print("bh1750fvi: start continuous read failed.\n");
        (void)bh1750fvi_deinit(&gs_handle);
       
        return 1;
    }
    
    return 0;
}

/**
 * @brief      basic example read
 * @param[out] *lux points to a converted lux buffer
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 * @note       none
 */
uint8_t bh1750fvi_basic_read(float *lux)
{
    uint8_t res;
    uint16_t raw;
    
    /* continuous read */
    res = bh1750fvi_continuous_read(&gs_handle, &raw, lux);
    if (res != 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/**
 * @brief  basic example deinit
 * @return status code
 *         - 0 success
 *         - 1 deinit failed
 * @note   none
 */
uint8_t bh1750fvi_basic_deinit(void)
{
    uint8_t res;
    
    /* stop continuous read */
    res = bh1750fvi_stop_continuous_read(&gs_handle);
    if (res != 0)
    {
        return 1;
    }
    
    /* deinit */
    res = bh1750fvi_deinit(&gs_handle);
    if (res != 0)
    {
        return 1;
    }
    
    return 0;
}
