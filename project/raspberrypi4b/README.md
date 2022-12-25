### 1. Board

#### 1.1 Board Info

Board Name: Raspberry Pi 4B.

IIC Pin: SCL/SDA GPIO3/GPIO2.

### 2. Install

#### 2.1 Dependencies

Install the necessary dependencies.

```shell
sudo apt-get install libgpiod-dev pkg-config cmake -y
```

#### 2.2 Makefile

Build the project.

```shell
make
```

Install the project and this is optional.

```shell
sudo make install
```

Uninstall the project and this is optional.

```shell
sudo make uninstall
```

#### 2.3 CMake

Build the project.

```shell
mkdir build && cd build 
cmake .. 
make
```

Install the project and this is optional.

```shell
sudo make install
```

Uninstall the project and this is optional.

```shell
sudo make uninstall
```

Test the project and this is optional.

```shell
make test
```

Find the compiled library in CMake. 

```cmake
find_package(bh1750fvi REQUIRED)
```


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
./bh1750fvi -i

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
./bh1750fvi -p

bh1750fvi: SCL connected to GPIO3(BCM).
bh1750fvi: SDA connected to GPIO2(BCM).
```

```shell
./bh1750fvi -t read --addr=0 --times=3

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
bh1750fvi: 255.00lux.
bh1750fvi: 254.17lux.
bh1750fvi: 253.33lux.
bh1750fvi: high resolution mode2 test.
bh1750fvi: 252.50lux.
bh1750fvi: 252.50lux.
bh1750fvi: 252.50lux.
bh1750fvi: low resolution mode test.
bh1750fvi: 250.00lux.
bh1750fvi: 250.00lux.
bh1750fvi: 250.00lux.
bh1750fvi: continuous read test.
bh1750fvi: 250.00lux.
bh1750fvi: 250.00lux.
bh1750fvi: 250.00lux.
bh1750fvi: measurement time test.
bh1750fvi: set measurement time 83.
bh1750fvi: 249.40lux.
bh1750fvi: 249.40lux.
bh1750fvi: 249.40lux.
bh1750fvi: set measurement time 136.
bh1750fvi: 250.29lux.
bh1750fvi: 250.29lux.
bh1750fvi: 250.29lux.
bh1750fvi: set measurement time 227.
bh1750fvi: 251.28lux.
bh1750fvi: 251.28lux.
bh1750fvi: 251.28lux.
bh1750fvi: finish read test.
```

```shell
./bh1750fvi -e read --addr=0 --times=3

1/3.
251.67lux.
2/3.
250.83lux.
3/3.
251.67lux.
```

```shell
./bh1750fvi -e shot --addr=0 --times=3

1/3.
250.00lux.
2/3.
251.67lux.
3/3.
251.67lux.
```

```shell
./bh1750fvi -h

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

