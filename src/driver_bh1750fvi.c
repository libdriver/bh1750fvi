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
 * @file      driver_bh1750fvi.c
 * @brief     driver bh1750fvi source file
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

#include "driver_bh1750fvi.h"

/**
 * @brief chip information definition
 */
#define CHIP_NAME                 "ROHM BH1750FVI"        /**< chip name */
#define MANUFACTURER_NAME         "ROHM"                  /**< manufacturer name */
#define SUPPLY_VOLTAGE_MIN        2.4f                    /**< chip min supply voltage */
#define SUPPLY_VOLTAGE_MAX        3.6f                    /**< chip max supply voltage */
#define MAX_CURRENT               0.19f                   /**< chip max current */
#define TEMPERATURE_MIN           -40.0f                  /**< chip min operating temperature */
#define TEMPERATURE_MAX           85.0f                   /**< chip max operating temperature */
#define DRIVER_VERSION            1000                    /**< driver version */

/**
 * @brief chip command definition
 */
#define BH1750FVI_COMMAND_POWER_DOWN                             0x00        /**< power down command */
#define BH1750FVI_COMMAND_POWER_ON                               0x01        /**< power on command */
#define BH1750FVI_COMMAND_RESET                                  0x07        /**< reset command */
#define BH1750FVI_COMMAND_CONTINUOUSLY_H_RESOLUTION_MODE         0x10        /**< continuously h-resolution mode command */
#define BH1750FVI_COMMAND_CONTINUOUSLY_H_RESOLUTION_MODE2        0x11        /**< continuously h-resolution mode2 command */
#define BH1750FVI_COMMAND_CONTINUOUSLY_L_RESOLUTION_MODE         0x13        /**< continuously l-resolution mode command */
#define BH1750FVI_COMMAND_ONE_TIME_H_RESOLUTION_MODE             0x20        /**< one time h-resolution mode command */
#define BH1750FVI_COMMAND_ONE_TIME_H_RESOLUTION_MODE2            0x21        /**< one time h-resolution mode2 command */
#define BH1750FVI_COMMAND_ONE_TIME_L_RESOLUTION_MODE             0x23        /**< one time l-resolution mode command */
#define BH1750FVI_COMMAND_CHANGE_MEASUREMENT_TIME_HIGH           0x40        /**< change measurement time high command */
#define BH1750FVI_COMMAND_CHANGE_MEASUREMENT_TIME_LOW            0x60        /**< change measurement time low command */

/**
 * @brief      read bytes
 * @param[in]  *handle points to a bh1750fvi handle structure
 * @param[out] *data points to a data buffer
 * @param[in]  len is the data length
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 * @note       none
 */
static uint8_t a_bh1750fvi_iic_read(bh1750fvi_handle_t *handle, uint8_t *data, uint16_t len)
{
    if (handle->iic_read_cmd(handle->iic_addr, data, len) != 0)        /* read the register */
    {
        return 1;                                                      /* return error */
    }
    else
    {
        return 0;                                                      /* success return 0 */
    }
}

/**
 * @brief     write bytes
 * @param[in] *handle points to a bh1750fvi handle structure
 * @param[in] *data points to a data buffer
 * @param[in] len is the data length
 * @return    status code
 *            - 0 success
 *            - 1 write failed
 * @note      none
 */
static uint8_t a_bh1750fvi_iic_write(bh1750fvi_handle_t *handle, uint8_t *data, uint16_t len)
{
    if (handle->iic_write_cmd(handle->iic_addr, data, len) != 0)        /* write the register */
    {
        return 1;                                                       /* return error */
    }
    else
    {
        return 0;                                                       /* success return 0 */
    }
}

/**
 * @brief     set the address pin
 * @param[in] *handle points to a bh1750fvi handle structure
 * @param[in] addr_pin is the chip address pins
 * @return    status code
 *            - 0 success
 *            - 2 handle is NULL
 * @note      none
 */
uint8_t bh1750fvi_set_addr_pin(bh1750fvi_handle_t *handle, bh1750fvi_address_t addr_pin)
{
    if (handle == NULL)                 /* check handle */
    {
        return 2;                       /* return error */
    }

    handle->iic_addr = addr_pin;        /* set iic addr */
    
    return 0;                           /* success return 0 */
}

/**
 * @brief      get the address pin
 * @param[in]  *handle points to a bh1750fvi handle structure
 * @param[out] *addr_pin points to a chip address pins buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 * @note       none
 */
uint8_t bh1750fvi_get_addr_pin(bh1750fvi_handle_t *handle, bh1750fvi_address_t *addr_pin)
{
    if (handle == NULL)                                         /* check handle */
    {
        return 2;                                               /* return error */
    }

    *addr_pin = (bh1750fvi_address_t)(handle->iic_addr);        /*get iic address */
    
    return 0;                                                   /* success return 0 */
}

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
uint8_t bh1750fvi_set_mode(bh1750fvi_handle_t *handle, bh1750fvi_mode_t mode)
{
    if (handle == NULL)                        /* check handle */
    {
        return 2;                              /* return error */
    }
    if (handle->inited != 1)                   /* check handle initialization */
    {
        return 3;                              /* return error */
    }
    
    handle->mode = (uint8_t)(mode);            /* set the mode */
    
    return 0;                                  /* success return 0 */
}

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
uint8_t bh1750fvi_get_mode(bh1750fvi_handle_t *handle, bh1750fvi_mode_t *mode)
{
    if (handle == NULL)                              /* check handle */
    {
        return 2;                                    /* return error */
    }
    if (handle->inited != 1)                         /* check handle initialization */
    {
        return 3;                                    /* return error */
    }
    
    *mode = (bh1750fvi_mode_t)(handle->mode);        /* get the mode */
    
    return 0;                                        /* success return 0 */
}

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
uint8_t bh1750fvi_init(bh1750fvi_handle_t *handle)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                               /* check handle */
    {
        return 2;                                                                     /* return error */
    }
    if (handle->debug_print == NULL)                                                  /* check debug_print */
    {
        return 3;                                                                     /* return error */
    }
    if (handle->iic_init == NULL)                                                     /* check iic_init */
    {
        handle->debug_print("bh1750fvi: iic_init is null.\n");                        /* iic_init is null */
        
        return 3;                                                                     /* return error */
    }
    if (handle->iic_deinit == NULL)                                                   /* check iic_deinit */
    {
        handle->debug_print("bh1750fvi: iic_deinit is null.\n");                      /* iic_deinit is null */
        
        return 3;                                                                     /* return error */
    }
    if (handle->iic_read_cmd == NULL)                                                 /* check iic_read_cmd */
    {
        handle->debug_print("bh1750fvi: iic_read_cmd is null.\n");                    /* iic_read_cmd is null */
        
        return 3;                                                                     /* return error */
    }
    if (handle->iic_write_cmd == NULL)                                                /* check iic_write_cmd */
    {
        handle->debug_print("bh1750fvi: iic_write_cmd is null.\n");                   /* iic_write_cmd is null */
        
        return 3;                                                                     /* return error */
    }
    if (handle->delay_ms == NULL)                                                     /* check delay_ms */
    {
        handle->debug_print("bh1750fvi: delay_ms is null.\n");                        /* delay_ms is null */
        
        return 3;                                                                     /* return error */
    }
    
    if (handle->iic_init() != 0)                                                      /* iic init */
    {
        handle->debug_print("bh1750fvi: iic init failed.\n");                         /* iic init failed */
        
        return 1;                                                                     /* return error */
    }
    
    prev = BH1750FVI_COMMAND_POWER_ON;                                                /* set the command */
    res = a_bh1750fvi_iic_write(handle, &prev, 1);                                    /* write the command */
    if (res != 0)                                                                     /* check error */
    {
        handle->debug_print("bh1750fvi: power on failed.\n");                         /* power on failed */
        (void)handle->iic_deinit();                                                   /* iic deinit */
        
        return 4;                                                                     /* return error */
    }
    handle->delay_ms(5);                                                              /* delay 5ms */
    prev = BH1750FVI_COMMAND_RESET;                                                   /* set the command */
    res = a_bh1750fvi_iic_write(handle, &prev, 1);                                    /* write the command */
    if (res != 0)                                                                     /* check error */
    {
        handle->debug_print("bh1750fvi: reset failed.\n");                            /* reset failed */
        (void)handle->iic_deinit();                                                   /* iic deinit */
        
        return 5;                                                                     /* return error */
    }
    handle->delay_ms(5);                                                              /* delay 5ms */
    prev = BH1750FVI_COMMAND_CHANGE_MEASUREMENT_TIME_HIGH | ((69 >> 5) & 0x07);       /* set the command */
    res = a_bh1750fvi_iic_write(handle, &prev, 1);                                    /* write the command */
    if (res != 0)                                                                     /* check error */
    {
        handle->debug_print("bh1750fvi: set measurement time failed.\n");             /* set measurement time failed */
        
        return 1;                                                                     /* return error */
    }
    prev = BH1750FVI_COMMAND_CHANGE_MEASUREMENT_TIME_LOW | ((69 >> 0) & 0x1F);        /* set the command */
    res = a_bh1750fvi_iic_write(handle, &prev, 1);                                    /* write the command */
    if (res != 0)                                                                     /* check error */
    {
        handle->debug_print("bh1750fvi: set measurement time failed.\n");             /* set measurement time failed */
        
        return 1;                                                                     /* return error */
    }
    handle->delay_ms(5);                                                              /* delay 5ms */
    handle->mode = BH1750FVI_MODE_HIGH_RESOLUTION_MODE;                               /* high resolution mode */
    handle->t = 69;                                                                   /* set default 69 */
    handle->inited = 1;                                                               /* flag finish initialization */
    
    return 0;                                                                         /* success return 0 */
}

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
uint8_t bh1750fvi_deinit(bh1750fvi_handle_t *handle)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                /* check handle */
    {
        return 2;                                                      /* return error */
    }
    if (handle->inited != 1)                                           /* check handle initialization */
    {
        return 3;                                                      /* return error */
    }
    
    prev = BH1750FVI_COMMAND_POWER_DOWN;                               /* set the command */
    res = a_bh1750fvi_iic_write(handle, &prev, 1);                     /* write the command */
    if (res != 0)                                                      /* check error */
    {
        handle->debug_print("bh1750fvi: power down failed.\n");        /* power down failed */
        
        return 4;                                                      /* return error */
    }
    res = handle->iic_deinit();                                        /* iic deinit */
    if (res != 0)                                                      /* check error */
    {
        handle->debug_print("bh1750fvi: iic deinit failed.\n");        /* iic deinit failed */
        
        return 1;                                                      /* return error */
    }
    handle->inited = 0;                                                /* flag closed */
    
    return 0;                                                          /* success return 0 */
}

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
uint8_t bh1750fvi_power_down(bh1750fvi_handle_t *handle)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                /* check handle */
    {
        return 2;                                                      /* return error */
    }
    if (handle->inited != 1)                                           /* check handle initialization */
    {
        return 3;                                                      /* return error */
    }
    
    prev = BH1750FVI_COMMAND_POWER_DOWN;                               /* set the command */
    res = a_bh1750fvi_iic_write(handle, &prev, 1);                     /* write the command */
    if (res != 0)                                                      /* check error */
    {
        handle->debug_print("bh1750fvi: power down failed.\n");        /* power down failed */
        
        return 1;                                                      /* return error */
    }
    
    return 0;                                                          /* success return 0 */
}

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
uint8_t bh1750fvi_power_on(bh1750fvi_handle_t *handle)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                              /* check handle */
    {
        return 2;                                                    /* return error */
    }
    if (handle->inited != 1)                                         /* check handle initialization */
    {
        return 3;                                                    /* return error */
    }
    
    prev = BH1750FVI_COMMAND_POWER_ON;                               /* set the command */
    res = a_bh1750fvi_iic_write(handle, &prev, 1);                   /* write the command */
    if (res != 0)                                                    /* check error */
    {
        handle->debug_print("bh1750fvi: power on failed.\n");        /* power on failed */
        
        return 1;                                                    /* return error */
    }
    
    return 0;                                                        /* success return 0 */
}

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
uint8_t bh1750fvi_reset(bh1750fvi_handle_t *handle)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                           /* check handle */
    {
        return 2;                                                 /* return error */
    }
    if (handle->inited != 1)                                      /* check handle initialization */
    {
        return 3;                                                 /* return error */
    }
    
    prev = BH1750FVI_COMMAND_RESET;                               /* set the command */
    res = a_bh1750fvi_iic_write(handle, &prev, 1);                /* write the command */
    if (res != 0)                                                 /* check error */
    {
        handle->debug_print("bh1750fvi: reset failed.\n");        /* reset failed */
        
        return 1;                                                 /* return error */
    }
    
    return 0;                                                     /* success return 0 */
}

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
uint8_t bh1750fvi_set_measurement_time(bh1750fvi_handle_t *handle, uint8_t t)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                               /* check handle */
    {
        return 2;                                                                     /* return error */
    }
    if (handle->inited != 1)                                                          /* check handle initialization */
    {
        return 3;                                                                     /* return error */
    }
    if ((t < 31) || (t > 254))                                                        /* check t */
    {
        handle->debug_print("bh1750fvi: t < 31 or t > 254.\n");                       /* t < 31 or t > 254 */
        
        return 4;                                                                     /* return error */
    }
    
    prev = BH1750FVI_COMMAND_CHANGE_MEASUREMENT_TIME_HIGH | ((t >> 5) & 0x07);        /* set the command */
    res = a_bh1750fvi_iic_write(handle, &prev, 1);                                    /* write the command */
    if (res != 0)                                                                     /* check error */
    {
        handle->debug_print("bh1750fvi: set measurement time failed.\n");             /* set measurement time failed */
        
        return 1;                                                                     /* return error */
    }
    prev = BH1750FVI_COMMAND_CHANGE_MEASUREMENT_TIME_LOW | ((t >> 0) & 0x1F);         /* set the command */
    res = a_bh1750fvi_iic_write(handle, &prev, 1);                                    /* write the command */
    if (res != 0)                                                                     /* check error */
    {
        handle->debug_print("bh1750fvi: set measurement time failed.\n");             /* set measurement time failed */
        
        return 1;                                                                     /* return error */
    }
    handle->t = t;                                                                    /* save the time */
    
    return 0;                                                                         /* success return 0 */
}

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
uint8_t bh1750fvi_single_read(bh1750fvi_handle_t *handle, uint16_t *raw, float *lux)
{
    uint8_t res;
    uint8_t prev;
    uint8_t buf[2];
    
    if (handle == NULL)                                                             /* check handle */
    {
        return 2;                                                                   /* return error */
    }
    if (handle->inited != 1)                                                        /* check handle initialization */
    {
        return 3;                                                                   /* return error */
    }
    
    if (handle->mode == BH1750FVI_MODE_HIGH_RESOLUTION_MODE)                        /* high resolution mode */
    {
        prev = BH1750FVI_COMMAND_ONE_TIME_H_RESOLUTION_MODE;                        /* high resolution mode command */
    }
    else if (handle->mode == BH1750FVI_MODE_HIGH_RESOLUTION_MODE2)                  /* high resolution mode2 */
    {
        prev = BH1750FVI_COMMAND_ONE_TIME_H_RESOLUTION_MODE2;                       /* high resolution mode2 command */
    }
    else if (handle->mode == BH1750FVI_MODE_LOW_RESOLUTION_MODE)                    /* low resolution mode */
    {
        prev = BH1750FVI_COMMAND_ONE_TIME_L_RESOLUTION_MODE;                        /* low resolution mode command */
    }
    else
    {
        handle->debug_print("bh1750fvi: mode is invalid.\n");                       /* mode is invalid */
        
        return 4;                                                                   /* return error */
    }
    
    res = a_bh1750fvi_iic_write(handle, &prev, 1);                                  /* write the command */
    if (res != 0)                                                                   /* check error */
    {
        handle->debug_print("bh1750fvi: set measurement time failed.\n");           /* set measurement time failed */
        
        return 1;                                                                   /* return error */
    }
    if (handle->mode == BH1750FVI_MODE_HIGH_RESOLUTION_MODE)                        /* high resolution mode */
    {
        handle->delay_ms((uint32_t)(180.0f * (float)(handle->t) / 69.0f));          /* delay the max time */
    }
    else if (handle->mode == BH1750FVI_MODE_HIGH_RESOLUTION_MODE2)                  /* high resolution mode2 */
    {
        handle->delay_ms((uint32_t)(180.0f * (float)(handle->t) / 69.0f));          /* delay the max time */
    }
    else                                                                            /* low resolution mode */
    {
        handle->delay_ms((uint32_t)(24.0f * (float)(handle->t) / 69.0f));           /* delay the max time */
    }
    res = a_bh1750fvi_iic_read(handle, buf, 2);                                     /* read data */
    if (res != 0)                                                                   /* check error */
    {
        handle->debug_print("bh1750fvi: read data failed.\n");                      /* read data failed */
        
        return 1;                                                                   /* return error */
    }
    *raw = (((uint16_t)buf[0]) << 8) | buf[1];                                      /* get the raw data */
    if (handle->mode == BH1750FVI_MODE_HIGH_RESOLUTION_MODE)                        /* high resolution mode */
    {
        *lux = (float)(*raw) / 1.2f * (69.0f / ((float)(handle->t)));               /* convert */
    }
    else if (handle->mode == BH1750FVI_MODE_HIGH_RESOLUTION_MODE2)                  /* high resolution mode2 */
    {
        *lux = (float)(*raw) / 1.2f * (69.0f / ((float)(handle->t))) / 2.0f;        /* convert */
    }
    else                                                                            /* low resolution mode */
    {
        *lux = (float)(*raw) / 1.2f * (69.0f / ((float)(handle->t)));               /* convert */
    }
    
    return 0;                                                                       /* success return 0 */
}

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
uint8_t bh1750fvi_continuous_read(bh1750fvi_handle_t *handle, uint16_t *raw, float *lux)
{
    uint8_t res;
    uint8_t buf[2];
    
    if (handle == NULL)                                                             /* check handle */
    {
        return 2;                                                                   /* return error */
    }
    if (handle->inited != 1)                                                        /* check handle initialization */
    {
        return 3;                                                                   /* return error */
    }
    
    res = a_bh1750fvi_iic_read(handle, buf, 2);                                     /* read data */
    if (res != 0)                                                                   /* check error */
    {
        handle->debug_print("bh1750fvi: read data failed.\n");                      /* read data failed */
        
        return 1;                                                                   /* return error */
    }
    *raw = (((uint16_t)buf[0]) << 8) | buf[1];                                      /* get the raw data */
    if (handle->mode == BH1750FVI_MODE_HIGH_RESOLUTION_MODE)                        /* high resolution mode */
    {
        *lux = (float)(*raw) / 1.2f * (69.0f / ((float)(handle->t)));               /* convert */
    }
    else if (handle->mode == BH1750FVI_MODE_HIGH_RESOLUTION_MODE2)                  /* high resolution mode2 */
    {
        *lux = (float)(*raw) / 1.2f * (69.0f / ((float)(handle->t))) / 2.0f;        /* convert */
    }
    else                                                                            /* low resolution mode */
    {
        *lux = (float)(*raw) / 1.2f * (69.0f / ((float)(handle->t)));               /* convert */
    }
    
    return 0;                                                                       /* success return 0 */
}

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
uint8_t bh1750fvi_start_continuous_read(bh1750fvi_handle_t *handle)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                          /* check handle */
    {
        return 2;                                                                /* return error */
    }
    if (handle->inited != 1)                                                     /* check handle initialization */
    {
        return 3;                                                                /* return error */
    }
    
    if (handle->mode == BH1750FVI_MODE_HIGH_RESOLUTION_MODE)                     /* high resolution mode */
    {
        prev = BH1750FVI_COMMAND_CONTINUOUSLY_H_RESOLUTION_MODE;                 /* high resolution mode command */
    }
    else if (handle->mode == BH1750FVI_MODE_HIGH_RESOLUTION_MODE2)               /* high resolution mode2 */
    {
        prev = BH1750FVI_COMMAND_CONTINUOUSLY_H_RESOLUTION_MODE2;                /* high resolution mode2 command */
    }
    else if (handle->mode == BH1750FVI_MODE_LOW_RESOLUTION_MODE)                 /* low resolution mode */
    {
        prev = BH1750FVI_COMMAND_CONTINUOUSLY_L_RESOLUTION_MODE;                 /* low resolution mode command */
    }
    else
    {
        handle->debug_print("bh1750fvi: mode is invalid.\n");                    /* mode is invalid */
        
        return 4;                                                                /* return error */
    }
    
    res = a_bh1750fvi_iic_write(handle, &prev, 1);                               /* write the command */
    if (res != 0)                                                                /* check error */
    {
        handle->debug_print("bh1750fvi: set measurement time failed.\n");        /* set measurement time failed */
        
        return 1;                                                                /* return error */
    }
    
    return 0;                                                                    /* success return 0 */
}

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
uint8_t bh1750fvi_stop_continuous_read(bh1750fvi_handle_t *handle)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                          /* check handle */
    {
        return 2;                                                                /* return error */
    }
    if (handle->inited != 1)                                                     /* check handle initialization */
    {
        return 3;                                                                /* return error */
    }
    
    if (handle->mode == BH1750FVI_MODE_HIGH_RESOLUTION_MODE)                     /* high resolution mode */
    {
        prev = BH1750FVI_COMMAND_ONE_TIME_H_RESOLUTION_MODE;                     /* high resolution mode command */
    }
    else if (handle->mode == BH1750FVI_MODE_HIGH_RESOLUTION_MODE2)               /* high resolution mode2 */
    {
        prev = BH1750FVI_COMMAND_ONE_TIME_H_RESOLUTION_MODE2;                    /* high resolution mode2 command */
    }
    else if (handle->mode == BH1750FVI_MODE_LOW_RESOLUTION_MODE)                 /* low resolution mode */
    {
        prev = BH1750FVI_COMMAND_ONE_TIME_L_RESOLUTION_MODE;                     /* low resolution mode command */
    }
    else
    {
        handle->debug_print("bh1750fvi: mode is invalid.\n");                    /* mode is invalid */
        
        return 4;                                                                /* return error */
    }
    
    res = a_bh1750fvi_iic_write(handle, &prev, 1);                               /* write the command */
    if (res != 0)                                                                /* check error */
    {
        handle->debug_print("bh1750fvi: set measurement time failed.\n");        /* set measurement time failed */
        
        return 1;                                                                /* return error */
    }
    
    return 0;                                                                    /* success return 0 */
}

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
uint8_t bh1750fvi_set_reg(bh1750fvi_handle_t *handle, uint8_t *buf, uint16_t len)
{
    if (handle == NULL)                                    /* check handle */
    {
        return 2;                                          /* return error */
    }
    if (handle->inited != 1)                               /* check handle initialization */
    {
        return 3;                                          /* return error */
    }
    
    return a_bh1750fvi_iic_write(handle, buf, len);        /* write command */
}

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
uint8_t bh1750fvi_get_reg(bh1750fvi_handle_t *handle, uint8_t *buf, uint16_t len)
{
    if (handle == NULL)                                   /* check handle */
    {
        return 2;                                         /* return error */
    }
    if (handle->inited != 1)                              /* check handle initialization */
    {
        return 3;                                         /* return error */
    }
    
    return a_bh1750fvi_iic_read(handle, buf, len);        /* read command */
}

/**
 * @brief      get chip's information
 * @param[out] *info points to a bh1750fvi info structure
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 * @note       none
 */
uint8_t bh1750fvi_info(bh1750fvi_info_t *info)
{
    if (info == NULL)                                               /* check handle */
    {
        return 2;                                                   /* return error */
    }
    
    memset(info, 0, sizeof(bh1750fvi_info_t));                      /* initialize bh1750fvi info structure */
    strncpy(info->chip_name, CHIP_NAME, 32);                        /* copy chip name */
    strncpy(info->manufacturer_name, MANUFACTURER_NAME, 32);        /* copy manufacturer name */
    strncpy(info->interface, "IIC", 8);                             /* copy interface name */
    info->supply_voltage_min_v = SUPPLY_VOLTAGE_MIN;                /* set minimal supply voltage */
    info->supply_voltage_max_v = SUPPLY_VOLTAGE_MAX;                /* set maximum supply voltage */
    info->max_current_ma = MAX_CURRENT;                             /* set maximum current */
    info->temperature_max = TEMPERATURE_MAX;                        /* set minimal temperature */
    info->temperature_min = TEMPERATURE_MIN;                        /* set maximum temperature */
    info->driver_version = DRIVER_VERSION;                          /* set driver version */
    
    return 0;                                                       /* success return 0 */
}
