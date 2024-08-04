[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver BH1750FVI

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/bh1750fvi/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE)

BH1750FVI is an digital Ambient Light Sensor IC for I2C bus interface. This IC is the most suitable to obtain the ambient light data for adjusting LCD and Keypad backlight power of Mobile phone. It is possible to detect wide range at High resolution.It can be used in Mobile phone, LCD TV, NOTE PC, Portable game machine, Digital camera, Digital video camera, PDA, LCD display and so on.

LibDriver BH1750FVI is the full function driver of BH1750FVI launched by LibDriver.It provides continuous  mode brightness reading, single mode brightness reading and other functions. LibDriver is MISRA compliant.

### Table of Contents

  - [Instruction](#Instruction)
  - [Install](#Install)
  - [Usage](#Usage)
    - [example basic](#example-basic)
    - [example shot](#example-shot)
  - [Document](#Document)
  - [Contributing](#Contributing)
  - [License](#License)
  - [Contact Us](#Contact-Us)

### Instruction

/src includes LibDriver BH1750FVI source files.

/interface includes LibDriver BH1750FVI IIC platform independent template.

/test includes LibDriver BH1750FVI driver test code and this code can test the chip necessary function simply.

/example includes LibDriver BH1750FVI sample code.

/doc includes LibDriver BH1750FVI offline document.

/datasheet includes BH1750FVI datasheet.

/project includes the common Linux and MCU development board sample code. All projects use the shell script to debug the driver and the detail instruction can be found in each project's README.md.

/misra includes the LibDriver MISRA code scanning results.

### Install

Reference /interface IIC platform independent template and finish your platform IIC driver.

Add the /src directory, the interface driver for your platform, and your own drivers to your project, if you want to use the default example drivers, add the /example directory to your project.

### Usage

You can refer to the examples in the /example directory to complete your own driver. If you want to use the default programming examples, here's how to use them.

#### example basic

```C
#include "driver_bh1750fvi_basic.h"

uint8_t res;
uint32_t i, times;
bh1750fvi_address_t address;

/* set hardware params */
times = 3;
address = BH1750FVI_ADDRESS_LOW;

...
    
/* basic init */
res = bh1750fvi_basic_init(address);
if (res != 0)
{
    return 1;
}

/* delay 1000ms */
bh1750fvi_interface_delay_ms(1000);

...
    
for (i = 0; i < times; i++)
{
    float lux;

    /* basic read */
    res = bh1750fvi_basic_read(&lux);
    if (res != 0)
    {
        (void)bh1750fvi_basic_deinit();
        
        return 1;
    }

    /* output */
    bh1750fvi_interface_debug_print("%d/%d.\n", i + 1, times);
    bh1750fvi_interface_debug_print("%.2flux.\n", lux);

    /* delay 1000ms */
    bh1750fvi_interface_delay_ms(1000);
    
    ...
}

...
    
(void)bh1750fvi_basic_deinit();

return 0;
```

#### example shot

```C
#include "driver_bh1750fvi_shot.h"

uint8_t res;
uint32_t i, times;
bh1750fvi_address_t address;

/* set hardware params */
times = 3;
address = BH1750FVI_ADDRESS_LOW;

...
    
/* shot init */
res = bh1750fvi_shot_init(address);
if (res != 0)
{
    return 1;
}

...
    
for (i = 0; i < times; i++)
{
    float lux;

    /* shot read */
    res = bh1750fvi_shot_read(&lux);
    if (res != 0)
    {
        (void)bh1750fvi_shot_deinit();
        
        return 1;
    }

    /* output */
    bh1750fvi_interface_debug_print("%d/%d.\n", i + 1, times);
    bh1750fvi_interface_debug_print("%.2flux.\n", lux);

    /* delay 1000ms */
    bh1750fvi_interface_delay_ms(1000);
    
    ...
}

...
    
(void)bh1750fvi_shot_deinit();

return 0;
```

### Document

Online documents: [https://www.libdriver.com/docs/bh1750fvi/index.html](https://www.libdriver.com/docs/bh1750fvi/index.html).

Offline documents: /doc/html/index.html.

### Contributing

Please refer to CONTRIBUTING.md.

### License

Copyright (c) 2015 - present LibDriver All rights reserved



The MIT License (MIT) 



Permission is hereby granted, free of charge, to any person obtaining a copy

of this software and associated documentation files (the "Software"), to deal

in the Software without restriction, including without limitation the rights

to use, copy, modify, merge, publish, distribute, sublicense, and/or sell

copies of the Software, and to permit persons to whom the Software is

furnished to do so, subject to the following conditions: 



The above copyright notice and this permission notice shall be included in all

copies or substantial portions of the Software. 



THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR

IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,

FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE

AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER

LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,

OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE

SOFTWARE. 

### Contact Us

Please send an e-mail to lishifenging@outlook.com.