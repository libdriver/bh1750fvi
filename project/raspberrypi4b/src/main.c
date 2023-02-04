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
#include <getopt.h>
#include <stdlib.h>

/**
 * @brief     bh1750fvi full function
 * @param[in] argc is arg numbers
 * @param[in] **argv is the arg address
 * @return    status code
 *            - 0 success
 *            - 1 run failed
 *            - 5 param is invalid
 * @note      none
 */
uint8_t bh1750fvi(uint8_t argc, char **argv)
{
    int c;
    int longindex = 0;
    const char short_options[] = "hipe:t:";
    const struct option long_options[] =
    {
        {"help", no_argument, NULL, 'h'},
        {"information", no_argument, NULL, 'i'},
        {"port", no_argument, NULL, 'p'},
        {"example", required_argument, NULL, 'e'},
        {"test", required_argument, NULL, 't'},
        {"addr", required_argument, NULL, 1},
        {"times", required_argument, NULL, 2},
        {NULL, 0, NULL, 0},
    };
    char type[33] = "unknown";
    uint32_t times = 3;
    bh1750fvi_address_t addr = BH1750FVI_ADDRESS_LOW;
    
    /* if no params */
    if (argc == 1)
    {
        /* goto the help */
        goto help;
    }
    
    /* init 0 */
    optind = 0;
    
    /* parse */
    do
    {
        /* parse the args */
        c = getopt_long(argc, argv, short_options, long_options, &longindex);
        
        /* judge the result */
        switch (c)
        {
            /* help */
            case 'h' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "h");
                
                break;
            }
            
            /* information */
            case 'i' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "i");
                
                break;
            }
            
            /* port */
            case 'p' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "p");
                
                break;
            }
            
            /* example */
            case 'e' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "e_%s", optarg);
                
                break;
            }
            
            /* test */
            case 't' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "t_%s", optarg);
                
                break;
            }
            
            /* addr */
            case 1 :
            {
                /* set the addr */
                if (strcmp("0", optarg) == 0)
                {
                    addr = BH1750FVI_ADDRESS_LOW;
                }
                else if (strcmp("1", optarg) == 0)
                {
                    addr = BH1750FVI_ADDRESS_HIGH;
                }
                else
                {
                    return 5;
                }
                
                break;
            }
            
            /* running times */
            case 2 :
            {
                /* set the times */
                times = atol(optarg);
                
                break;
            } 
            
            /* the end */
            case -1 :
            {
                break;
            }
            
            /* others */
            default :
            {
                return 5;
            }
        }
    } while (c != -1);
    
    /* run the function */
    if (strcmp("t_read", type) == 0)
    {
        /* run read test */
        if (bh1750fvi_read_test(addr, times) != 0)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    else if (strcmp("e_read", type) == 0)
    {
        uint8_t res;
        uint32_t i;
        
        /* basic init */
        res = bh1750fvi_basic_init(addr);
        if (res != 0)
        {
            return 1;
        }
        
        /* delay 1000ms */
        bh1750fvi_interface_delay_ms(1000);
        
        /* loop */
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
        
        /* deinit */
        bh1750fvi_basic_deinit();
        
        return 0;
    }
    else if (strcmp("e_shot", type) == 0)
    {
        uint8_t res;
        uint32_t i;
        
        /* shot init */
        res = bh1750fvi_shot_init(addr);
        if (res != 0)
        {
            return 1;
        }
        
        /* loop */
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
        
        /* deinit */
        bh1750fvi_shot_deinit();
        
        return 0;
    }
    else if (strcmp("h", type) == 0)
    {
        help:
        bh1750fvi_interface_debug_print("Usage:\n");
        bh1750fvi_interface_debug_print("  bh1750fvi (-i | --information)\n");
        bh1750fvi_interface_debug_print("  bh1750fvi (-h | --help)\n");
        bh1750fvi_interface_debug_print("  bh1750fvi (-p | --port)\n");
        bh1750fvi_interface_debug_print("  bh1750fvi (-t read | --test=read) [--addr=<0 | 1>] [--times=<num>]\n");
        bh1750fvi_interface_debug_print("  bh1750fvi (-e read | --example=read) [--addr=<0 | 1>] [--times=<num>]\n");
        bh1750fvi_interface_debug_print("  bh1750fvi (-e shot | --example=shot) [--addr=<0 | 1>] [--times=<num>]\n");
        bh1750fvi_interface_debug_print("\n");
        bh1750fvi_interface_debug_print("Options:\n");
        bh1750fvi_interface_debug_print("      --addr=<0 | 1>              Set the chip iic address.([default: 0])\n");
        bh1750fvi_interface_debug_print("  -e <read | shot>, --example=<read | shot>\n");
        bh1750fvi_interface_debug_print("                                  Run the driver example.\n");
        bh1750fvi_interface_debug_print("  -h, --help                      Show the help.\n");
        bh1750fvi_interface_debug_print("  -i, --information               Show the chip information.\n");
        bh1750fvi_interface_debug_print("  -p, --port                      Display the pin connections of the current board.\n");
        bh1750fvi_interface_debug_print("  -t <read>, --test=<read>        Run the driver test.\n");
        bh1750fvi_interface_debug_print("      --times=<num>               Set the running times.([default: 3])\n");

        return 0;
    }
    else if (strcmp("i", type) == 0)
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
    else if (strcmp("p", type) == 0)
    {
        /* print pin connection */
        bh1750fvi_interface_debug_print("bh1750fvi: SCL connected to GPIO3(BCM).\n");
        bh1750fvi_interface_debug_print("bh1750fvi: SDA connected to GPIO2(BCM).\n");
        
        return 0;
    }
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
        bh1750fvi_interface_debug_print("bh1750fvi: unknown status code.\n");
    }

    return 0;
}
