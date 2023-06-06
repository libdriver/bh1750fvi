### 1. Chip

#### 1.1 Chip Info

Chip Name: STM32F407ZGT6.

Extern Oscillator: 8MHz.

UART Pin: TX/RX PA9/PA10.

IIC Pin: SCL/SDA PB8/PB9.

### 2. Development and Debugging

#### 2.1 Integrated Development Environment

LibDriver provides both Keil and IAR integrated development environment projects.

MDK is the Keil ARM project and your Keil version must be 5 or higher.Keil ARM project needs STMicroelectronics STM32F4 Series Device Family Pack and you can download from https://www.keil.com/dd2/stmicroelectronics/stm32f407zgtx.

EW is the IAR ARM project and your IAR version must be 9 or higher.

#### 2.2 Serial Port Parameter

Baud Rate: 115200.

Data Bits : 8.

Stop Bits: 1.

Parity: None.

Flow Control: None.

#### 2.3 Serial Port Assistant

We use '\n' to wrap lines.If your serial port assistant displays exceptions (e.g. the displayed content does not divide lines), please modify the configuration of your serial port assistant or replace one that supports '\n' parsing.

### 3. BH1750FVI

#### 3.1 Command Instruction

1. Show bh1750fvi chip and driver information.

   ```shell
   bh1750fvi (-i | --information)
   ```

2. Show bh1750fvi help.

   ```shell
   bh1750fvi (-h | --help)
   ```

3. Show bh1750fvi pin connections of the current board.

   ```shell
   bh1750fvi (-p | --port)
   ```

4. Run bh1750fvi read test, num means the test times.

   ```shell
   bh1750fvi (-t read | --test=read) [--addr=<0 | 1>] [--times=<num>]
   ```

5. Run bh1750fvi continuous reading function, num means the read times.

   ```shell
   bh1750fvi (-e read | --example=read) [--addr=<0 | 1>] [--times=<num>]
   ```

6. Run bh1750fvi shot reading function, num means the read times.

   ```shell
   bh1750fvi (-e shot | --example=shot) [--addr=<0 | 1>] [--times=<num>]
   ```

#### 3.2 Command Example

```shell
bh1750fvi -i

bh1750fvi: chip is ROHM BH1750FVI.
bh1750fvi: manufacturer is ROHM.
bh1750fvi: interface is IIC.
bh1750fvi: driver version is 1.0.
bh1750fvi: min supply voltage is 2.4V.
bh1750fvi: max supply voltage is 3.6V.
bh1750fvi: max current is 0.19mA.
bh1750fvi: max temperature is 85.0C.
bh1750fvi: min temperature is -40.0C.
```

```shell
bh1750fvi -p

bh1750fvi: SCL connected to GPIOB PIN8.
bh1750fvi: SDA connected to GPIOB PIN9.
```

```shell
bh1750fvi -t read --addr=0 --times=3

bh1750fvi: chip is ROHM BH1750FVI.
bh1750fvi: manufacturer is ROHM.
bh1750fvi: interface is IIC.
bh1750fvi: driver version is 1.0.
bh1750fvi: min supply voltage is 2.4V.
bh1750fvi: max supply voltage is 3.6V.
bh1750fvi: max current is 0.19mA.
bh1750fvi: max temperature is 85.0C.
bh1750fvi: min temperature is -40.0C.
bh1750fvi: start read test.
bh1750fvi: high resolution mode test.
bh1750fvi: 330.83lux.
bh1750fvi: 330.83lux.
bh1750fvi: 331.67lux.
bh1750fvi: high resolution mode2 test.
bh1750fvi: 330.83lux.
bh1750fvi: 331.25lux.
bh1750fvi: 331.25lux.
bh1750fvi: low resolution mode test.
bh1750fvi: 326.67lux.
bh1750fvi: 326.67lux.
bh1750fvi: 326.67lux.
bh1750fvi: continuous read test.
bh1750fvi: 326.67lux.
bh1750fvi: 330.00lux.
bh1750fvi: 326.67lux.
bh1750fvi: measurement time test.
bh1750fvi: set measurement time 68.
bh1750fvi: 328.09lux.
bh1750fvi: 328.09lux.
bh1750fvi: 328.09lux.
bh1750fvi: set measurement time 117.
bh1750fvi: 330.26lux.
bh1750fvi: 328.29lux.
bh1750fvi: 328.29lux.
bh1750fvi: set measurement time 209.
bh1750fvi: 330.14lux.
bh1750fvi: 330.14lux.
bh1750fvi: 330.14lux.
bh1750fvi: finish read test.
```

```shell
bh1750fvi -e read --addr=0 --times=3

1/3.
331.67lux.
2/3.
331.67lux.
3/3.
331.67lux.
```

```shell
bh1750fvi -e shot --addr=0 --times=3

1/3.
331.67lux.
2/3.
331.67lux.
3/3.
330.83lux.
```

```shell
bh1750fvi -h

Usage:
  bh1750fvi (-i | --information)
  bh1750fvi (-h | --help)
  bh1750fvi (-p | --port)
  bh1750fvi (-t read | --test=read) [--addr=<0 | 1>] [--times=<num>]
  bh1750fvi (-e read | --example=read) [--addr=<0 | 1>] [--times=<num>]
  bh1750fvi (-e shot | --example=shot) [--addr=<0 | 1>] [--times=<num>]

Options:
      --addr=<0 | 1>              Set the chip iic address.([default: 0])
  -e <read | shot>, --example=<read | shot>
                                  Run the driver example.
  -h, --help                      Show the help.
  -i, --information               Show the chip information.
  -p, --port                      Display the pin connections of the current board.
  -t <read>, --test=<read>        Run the driver test.
      --times=<num>               Set the running times.([default: 3])
```

