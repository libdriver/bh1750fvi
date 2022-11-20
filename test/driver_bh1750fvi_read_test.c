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
 * @file      driver_bh1750fvi_read_test.c
 * @brief     driver bh1750fvi read test source file
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

#include "driver_bh1750fvi_read_test.h"
#include <stdlib.h>

static bh1750fvi_handle_t gs_handle;        /**< bh1750fvi handle */

/**
 * @brief     read test
 * @param[in] addr is the iic device address
 * @param[in] times is the test times
 * @return    status code
 *            - 0 success
 *            - 1 test failed
 * @note      none
 */
uint8_t bh1750fvi_read_test(bh1750fvi_address_t addr, uint32_t times)
{
    uint8_t res;
    uint8_t t;
    uint16_t raw;
    float lux;
    uint32_t i;
    bh1750fvi_info_t info;
    
    /* link interface function */
    DRIVER_BH1750FVI_LINK_INIT(&gs_handle, bh1750fvi_handle_t);
    DRIVER_BH1750FVI_LINK_IIC_INIT(&gs_handle, bh1750fvi_interface_iic_init);
    DRIVER_BH1750FVI_LINK_IIC_DEINIT(&gs_handle, bh1750fvi_interface_iic_deinit);
    DRIVER_BH1750FVI_LINK_IIC_READ_CMD(&gs_handle, bh1750fvi_interface_iic_read_cmd);
    DRIVER_BH1750FVI_LINK_IIC_WRITE_CMD(&gs_handle, bh1750fvi_interface_iic_write_cmd);
    DRIVER_BH1750FVI_LINK_DELAY_MS(&gs_handle, bh1750fvi_interface_delay_ms);
    DRIVER_BH1750FVI_LINK_DEBUG_PEINT(&gs_handle, bh1750fvi_interface_debug_print);
    
    /* get information */
    res = bh1750fvi_info(&info);
    if (res != 0)
    {
        bh1750fvi_interface_debug_print("bh1750fvi: get info failed.\n");
       
        return 1;
    }
    else
    {
        /* print chip info */
        bh1750fvi_interface_debug_print("bh1750fvi: chip is %s.\n", info.chip_name);
        bh1750fvi_interface_debug_print("bh1750fvi: manufacturer is %s.\n", info.manufacturer_name);
        bh1750fvi_interface_debug_print("bh1750fvi: interface is %s.\n", info.interface);
        bh1750fvi_interface_debug_print("bh1750fvi: driver version is %d.%d.\n", info.driver_version / 1000, (info.driver_version % 1000) / 100);
        bh1750fvi_interface_debug_print("bh1750fvi: min supply voltage is %0.1fV.\n", info.supply_voltage_min_v);
        bh1750fvi_interface_debug_print("bh1750fvi: max supply voltage is %0.1fV.\n", info.supply_voltage_max_v);
        bh1750fvi_interface_debug_print("bh1750fvi: max current is %0.2fmA.\n", info.max_current_ma);
        bh1750fvi_interface_debug_print("bh1750fvi: max temperature is %0.1fC.\n", info.temperature_max);
        bh1750fvi_interface_debug_print("bh1750fvi: min temperature is %0.1fC.\n", info.temperature_min);
    }
    
    /* start read test */
    bh1750fvi_interface_debug_print("bh1750fvi: start read test.\n");
    
    /* set addr pin test */
    res = bh1750fvi_set_addr_pin(&gs_handle, addr);
    if (res != 0)
    {
        bh1750fvi_interface_debug_print("bh1750fvi: set addr pin test.\n");
        
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
    
    /* high resolution mode test */
    bh1750fvi_interface_debug_print("bh1750fvi: high resolution mode test.\n");
    
    /* high resolution mode */
    res = bh1750fvi_set_mode(&gs_handle, BH1750FVI_MODE_HIGH_RESOLUTION_MODE);
    if (res != 0)
    {
        bh1750fvi_interface_debug_print("bh1750fvi: set mode failed.\n");
        (void)bh1750fvi_deinit(&gs_handle);
        
        return 1;
    }
    
    for (i = 0; i < times; i++)
    {
        /* single read */
        res = bh1750fvi_single_read(&gs_handle, &raw, &lux);
        if (res != 0)
        {
            bh1750fvi_interface_debug_print("bh1750fvi: single read failed.\n");
            (void)bh1750fvi_deinit(&gs_handle);
            
            return 1;
        }
        
        /* output */
        bh1750fvi_interface_debug_print("bh1750fvi: %0.2flux.\n", lux);
        
        /* delay 1000 ms */
        bh1750fvi_interface_delay_ms(1000);
    }
    
    /* high resolution mode2 test */
    bh1750fvi_interface_debug_print("bh1750fvi: high resolution mode2 test.\n");
    
    /* high resolution mode2 */
    res = bh1750fvi_set_mode(&gs_handle, BH1750FVI_MODE_HIGH_RESOLUTION_MODE2);
    if (res != 0)
    {
        bh1750fvi_interface_debug_print("bh1750fvi: set mode failed.\n");
        (void)bh1750fvi_deinit(&gs_handle);
        
        return 1;
    }
    
    for (i = 0; i < times; i++)
    {
        /* single read */
        res = bh1750fvi_single_read(&gs_handle, &raw, &lux);
        if (res != 0)
        {
            bh1750fvi_interface_debug_print("bh1750fvi: single read failed.\n");
            (void)bh1750fvi_deinit(&gs_handle);
            
            return 1;
        }
        
        /* output */
        bh1750fvi_interface_debug_print("bh1750fvi: %0.2flux.\n", lux);
        
        /* delay 1000 ms */
        bh1750fvi_interface_delay_ms(1000);
    }
    
    /* low resolution mode test */
    bh1750fvi_interface_debug_print("bh1750fvi: low resolution mode test.\n");
    
    /* low resolution mode */
    res = bh1750fvi_set_mode(&gs_handle, BH1750FVI_MODE_LOW_RESOLUTION_MODE);
    if (res != 0)
    {
        bh1750fvi_interface_debug_print("bh1750fvi: set mode failed.\n");
        (void)bh1750fvi_deinit(&gs_handle);
        
        return 1;
    }
    
    for (i = 0; i < times; i++)
    {
        /* single read */
        res = bh1750fvi_single_read(&gs_handle, &raw, &lux);
        if (res != 0)
        {
            bh1750fvi_interface_debug_print("bh1750fvi: single read failed.\n");
            (void)bh1750fvi_deinit(&gs_handle);
            
            return 1;
        }
        
        /* output */
        bh1750fvi_interface_debug_print("bh1750fvi: %0.2flux.\n", lux);
        
        /* delay 1000 ms */
        bh1750fvi_interface_delay_ms(1000);
    }
    
    /* continuous read test */
    bh1750fvi_interface_debug_print("bh1750fvi: continuous read test.\n");
    
    /* start continuous read */
    res = bh1750fvi_start_continuous_read(&gs_handle);
    if (res != 0)
    {
        bh1750fvi_interface_debug_print("bh1750fvi: start continuous read failed.\n");
        (void)bh1750fvi_deinit(&gs_handle);
        
        return 1;
    }
    
    for (i = 0; i < times; i++)
    {
        /* continuous read */
        res = bh1750fvi_continuous_read(&gs_handle, &raw, &lux);
        if (res != 0)
        {
            bh1750fvi_interface_debug_print("bh1750fvi: continuous read failed.\n");
            (void)bh1750fvi_deinit(&gs_handle);
            
            return 1;
        }
        
        /* output */
        bh1750fvi_interface_debug_print("bh1750fvi: %0.2flux.\n", lux);
        
        /* delay 1000 ms */
        bh1750fvi_interface_delay_ms(1000);
    }
    
    /* stop continuous read */
    res = bh1750fvi_stop_continuous_read(&gs_handle);
    if (res != 0)
    {
        bh1750fvi_interface_debug_print("bh1750fvi: stop continuous read failed.\n");
        (void)bh1750fvi_deinit(&gs_handle);
        
        return 1;
    }
    
    /* measurement time test */
    bh1750fvi_interface_debug_print("bh1750fvi: measurement time test.\n");
    
    t = rand() % 50 + 50;
    res = bh1750fvi_set_measurement_time(&gs_handle, t);
    if (res != 0)
    {
        bh1750fvi_interface_debug_print("bh1750fvi: set measurement time failed.\n");
        (void)bh1750fvi_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set measurement time */
    bh1750fvi_interface_debug_print("bh1750fvi: set measurement time %d.\n", t);
    
    for (i = 0; i < times; i++)
    {
        /* single read */
        res = bh1750fvi_single_read(&gs_handle, &raw, &lux);
        if (res != 0)
        {
            bh1750fvi_interface_debug_print("bh1750fvi: single read failed.\n");
            (void)bh1750fvi_deinit(&gs_handle);
            
            return 1;
        }
        
        /* output */
        bh1750fvi_interface_debug_print("bh1750fvi: %0.2flux.\n", lux);
        
        /* delay 1000 ms */
        bh1750fvi_interface_delay_ms(1000);
    }
    
    t = rand() % 50 + 100;
    res = bh1750fvi_set_measurement_time(&gs_handle, t);
    if (res != 0)
    {
        bh1750fvi_interface_debug_print("bh1750fvi: set measurement time failed.\n");
        (void)bh1750fvi_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set measurement time */
    bh1750fvi_interface_debug_print("bh1750fvi: set measurement time %d.\n", t);
    
    for (i = 0; i < times; i++)
    {
        /* single read */
        res = bh1750fvi_single_read(&gs_handle, &raw, &lux);
        if (res != 0)
        {
            bh1750fvi_interface_debug_print("bh1750fvi: single read failed.\n");
            (void)bh1750fvi_deinit(&gs_handle);
            
            return 1;
        }
        
        /* output */
        bh1750fvi_interface_debug_print("bh1750fvi: %0.2flux.\n", lux);
        
        /* delay 1000 ms */
        bh1750fvi_interface_delay_ms(1000);
    }
    
    t = rand() % 50 + 200;
    res = bh1750fvi_set_measurement_time(&gs_handle, t);
    if (res != 0)
    {
        bh1750fvi_interface_debug_print("bh1750fvi: set measurement time failed.\n");
        (void)bh1750fvi_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set measurement time */
    bh1750fvi_interface_debug_print("bh1750fvi: set measurement time %d.\n", t);
    
    for (i = 0; i < times; i++)
    {
        /* single read */
        res = bh1750fvi_single_read(&gs_handle, &raw, &lux);
        if (res != 0)
        {
            bh1750fvi_interface_debug_print("bh1750fvi: single read failed.\n");
            (void)bh1750fvi_deinit(&gs_handle);
            
            return 1;
        }
        
        /* output */
        bh1750fvi_interface_debug_print("bh1750fvi: %0.2flux.\n", lux);
        
        /* delay 1000 ms */
        bh1750fvi_interface_delay_ms(1000);
    }
    
    /* power down */
    res = bh1750fvi_power_down(&gs_handle);
    if (res != 0)
    {
        bh1750fvi_interface_debug_print("bh1750fvi: power down failed.\n");
        (void)bh1750fvi_deinit(&gs_handle);
        
        return 1;
    }
    
    /* finish read test */
    bh1750fvi_interface_debug_print("bh1750fvi: finish read test.\n");
    (void)bh1750fvi_deinit(&gs_handle);
    
    return 0;
}
