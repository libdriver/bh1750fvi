### 1. Chip

#### 1.1 Chip Info

chip name : STM32F407ZGT6.

extern oscillator : 8MHz.

uart pin: TX/RX PA9/PA10.

iic pin: SCL/SDA PB8/PB9.

### 2. Shell

#### 2.1 Shell Parameter

baud rate: 115200.

data bits : 8.

stop bits: 1.

parity: none.

flow control: none.

### 3. BH1750FVI

#### 3.1 Command Instruction

​           bh1750fvi is a basic command which can test all bh1750fvi driver function:

​           -i        show bh1750fvi chip and driver information.

​           -h       show bh1750fvi help.

​           -p       show bh1750fvi pin connections of the current board.

​           -t read -a  (0 | 1)  <times>         run bh1750fvi read test.times means the test times.

​           -c (basic -a (0 | 1)  <times> | shot -a (0 | 1)  <times>)

​           -c basic -a (0 | 1)  <times>       run bh1750fvi continuous reading function.times means the read times.

​           -c shot -a (0 | 1)  <times>       run bh1750fvi shot reading function.times means the read times.

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
bh1750fvi -t read -a 0 3

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
bh1750fvi: 567.50lux.
bh1750fvi: 565.83lux.
bh1750fvi: 566.67lux.
bh1750fvi: high resolution mode2 test.
bh1750fvi: 566.25lux.
bh1750fvi: 566.25lux.
bh1750fvi: 565.83lux.
bh1750fvi: low resolution mode test.
bh1750fvi: 563.33lux.
bh1750fvi: 563.33lux.
bh1750fvi: 563.33lux.
bh1750fvi: continuous read test.
bh1750fvi: 563.33lux.
bh1750fvi: 563.33lux.
bh1750fvi: 563.33lux.
bh1750fvi: measurement time test.
bh1750fvi: set measurement time 64.
bh1750fvi: 560.62lux.
bh1750fvi: 560.62lux.
bh1750fvi: 560.62lux.
bh1750fvi: set measurement time 148.
bh1750fvi: 564.12lux.
bh1750fvi: 564.12lux.
bh1750fvi: 564.12lux.
bh1750fvi: set measurement time 247.
bh1750fvi: 564.29lux.
bh1750fvi: 564.29lux.
bh1750fvi: 564.29lux.
bh1750fvi: finish read test.
```

```shell
bh1750fvi -c read -a 0 3

1/3.
560.83lux.
2/3.
562.50lux.
3/3.
562.50lux.
```

```shell
bh1750fvi -c shot -a 0 3

1/3.
562.50lux.
2/3.
562.50lux.
3/3.
563.33lux.
```

```shell
bh1750fvi -h

bh1750fvi -i
	show bh1750fvi chip and driver information.
bh1750fvi -h
	show bh1750fvi help.
bh1750fvi -p
	show bh1750fvi pin connections of the current board.
bh1750fvi -t read -a (0 | 1) <times>
	run bh1750fvi read test.times means the test times.
bh1750fvi -c basic -a (0 | 1) <times>
	run bh1750fvi continuous reading function.times means the read times.
bh1750fvi -c shot -a (0 | 1) <times>
	run bh1750fvi shot reading function.times means the read times.
```

