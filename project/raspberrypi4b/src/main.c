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
 * @file      main.c
 * @brief     main source file
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
#include "driver_bh1750fvi_basic.h"
#include "driver_bh1750fvi_shot.h"
#include <stdlib.h>

/**
 * @brief     bh1750fvi full function
 * @param[in] argc is arg numbers
 * @param[in] **argv is the arg address
 * @return    status code
 *             - 0 success
 *             - 1 run failed
 *             - 5 param is invalid
 * @note      none
 */
uint8_t bh1750fvi(uint8_t argc, char **argv)
{
    if (argc == 1)
    {
        goto help;
    }
    else if (argc == 2)
    {
        if (strcmp("-i", argv[1]) == 0)
        {
            bh1750fvi_info_t info;
            
            /* print bh1750fvi info */
            bh1750fvi_info(&info);
            bh1750fvi_interface_debug_print("bh1750fvi: chip is %s.\n", info.chip_name);
            bh1750fvi_interface_debug_print("bh1750fvi: manufacturer is %s.\n", info.manufacturer_name);
            bh1750fvi_interface_debug_print("bh1750fvi: interface is %s.\n", info.interface);
            bh1750fvi_interface_debug_print("bh1750fvi: driver version is %d.%d.\n", info.driver_version / 1000, (info.driver_version % 1000) / 100);
            bh1750fvi_interface_debug_print("bh1750fvi: min supply voltage is %0.1fV.\n", info.supply_voltage_min_v);
            bh1750fvi_interface_debug_print("bh1750fvi: max supply voltage is %0.1fV.\n", info.supply_voltage_max_v);
            bh1750fvi_interface_debug_print("bh1750fvi: max current is %0.2fmA.\n", info.max_current_ma);
            bh1750fvi_interface_debug_print("bh1750fvi: max temperature is %0.1fC.\n", info.temperature_max);
            bh1750fvi_interface_debug_print("bh1750fvi: min temperature is %0.1fC.\n", info.temperature_min);
            
            return 0;
        }
        else if (strcmp("-p", argv[1]) == 0)
        {
            /* print pin connection */
            bh1750fvi_interface_debug_print("bh1750fvi: SCL connected to GPIO3(BCM).\n");
            bh1750fvi_interface_debug_print("bh1750fvi: SDA connected to GPIO2(BCM).\n");
            
            return 0;
        }
        else if (strcmp("-h", argv[1]) == 0)
        {
            /* show bh1750fvi help */
            
            help:
            bh1750fvi_interface_debug_print("bh1750fvi -i\n\tshow bh1750fvi chip and driver information.\n");
            bh1750fvi_interface_debug_print("bh1750fvi -h\n\tshow bh1750fvi help.\n");
            bh1750fvi_interface_debug_print("bh1750fvi -p\n\tshow bh1750fvi pin connections of the current board.\n");
            bh1750fvi_interface_debug_print("bh1750fvi -t read -a (0 | 1) <times>\n\trun bh1750fvi read test.times means the test times.\n");
            bh1750fvi_interface_debug_print("bh1750fvi -c basic -a (0 | 1) <times>\n\trun bh1750fvi continuous reading function.times means the read times.\n");
            bh1750fvi_interface_debug_print("bh1750fvi -c shot -a (0 | 1) <times>\n\trun bh1750fvi shot reading function.times means the read times.\n");
            
            return 0;
        }
        else
        {
            return 5;
        }
    }
    else if (argc == 6)
    {
        /* run test */
        if (strcmp("-t", argv[1]) == 0)
        {
            /* read function */
            if (strcmp("read", argv[2]) == 0)
            {
                bh1750fvi_address_t address;
                
                if (strcmp("-a", argv[3]) != 0)
                {
                    return 5;
                }
                if (strcmp("0", argv[4]) == 0)
                {
                    address = BH1750FVI_ADDRESS_LOW;
                }
                else if (strcmp("1", argv[4]) == 0)
                {
                    address = BH1750FVI_ADDRESS_HIGH;
                }
                else
                {
                    return 5;
                }
        
                /* run read test */
                if (bh1750fvi_read_test(address, atoi(argv[5])) != 0)
                {
                    return 1;
                }
                else
                {
                    return 0;
                }
            }
            /* param is invalid */
            else
            {
                return 5;
            }
        }
        /* run function */
        else if (strcmp("-c", argv[1]) == 0)
        {
            /* read function */
            if (strcmp("read", argv[2]) == 0)
            {
                uint8_t res;
                uint32_t i, times;
                bh1750fvi_address_t address;
                
                if (strcmp("-a", argv[3]) != 0)
                {
                    return 5;
                }
                if (strcmp("0", argv[4]) == 0)
                {
                    address = BH1750FVI_ADDRESS_LOW;
                }
                else if (strcmp("1", argv[4]) == 0)
                {
                    address = BH1750FVI_ADDRESS_HIGH;
                }
                else
                {
                    return 5;
                }
                
                /* convert the times */
                times = atoi(argv[5]);
                
                /* basic init */
                res = bh1750fvi_basic_init(address);
                if (res != 0)
                {
                    return 1;
                }
                
                /* delay 1000ms */
                bh1750fvi_interface_delay_ms(1000);
                
                for (i = 0; i < times; i++)
                {
                    float lux;
                    
                    /* basic read */
                    res = bh1750fvi_basic_read(&lux);
                    if (res != 0)
                    {
                        return 1;
                    }
                    
                    /* output */
                    bh1750fvi_interface_debug_print("%d/%d.\n", i + 1, times);
                    bh1750fvi_interface_debug_print("%.2flux.\n", lux);
                    
                    /* delay 1000ms */
                    bh1750fvi_interface_delay_ms(1000);
                }
                
                return bh1750fvi_basic_deinit();
            }
            else if (strcmp("shot", argv[2]) == 0)
            {
                uint8_t res;
                uint32_t i, times;
                bh1750fvi_address_t address;
                
                if (strcmp("-a", argv[3]) != 0)
                {
                    return 5;
                }
                if (strcmp("0", argv[4]) == 0)
                {
                    address = BH1750FVI_ADDRESS_LOW;
                }
                else if (strcmp("1", argv[4]) == 0)
                {
                    address = BH1750FVI_ADDRESS_HIGH;
                }
                else
                {
                    return 5;
                }
                
                /* convert the times */
                times = atoi(argv[5]);
                
                /* shot init */
                res = bh1750fvi_shot_init(address);
                if (res != 0)
                {
                    return 1;
                }
                
                for (i = 0; i < times; i++)
                {
                    float lux;
                    
                    /* shot read */
                    res = bh1750fvi_shot_read(&lux);
                    if (res != 0)
                    {
                        return 1;
                    }
                    
                    /* output */
                    bh1750fvi_interface_debug_print("%d/%d.\n", i + 1, times);
                    bh1750fvi_interface_debug_print("%.2flux.\n", lux);
                    
                    /* delay 1000ms */
                    bh1750fvi_interface_delay_ms(1000);
                }
                
                return bh1750fvi_shot_deinit();
            }
            /* param is invalid */
            else
            {
                return 5;
            }
        }
        /* param is invalid */
        else
        {
            return 5;
        }
    }
    /* param is invalid */
    else
    {
        return 5;
    }
}

/**
 * @brief     main function
 * @param[in] argc is arg numbers
 * @param[in] **argv is the arg address
 * @return    status code
 *             - 0 success
 * @note      none
 */
int main(uint8_t argc, char **argv)
{
    uint8_t res;

    res = bh1750fvi(argc, argv);
    if (res == 0)
    {
        /* run success */
    }
    else if (res == 1)
    {
        bh1750fvi_interface_debug_print("bh1750fvi: run failed.\n");
    }
    else if (res == 5)
    {
        bh1750fvi_interface_debug_print("bh1750fvi: param is invalid.\n");
    }
    else
    {
        bh1750fvi_interface_debug_print("bh1750fvi: unknow status code.\n");
    }

    return 0;
}
