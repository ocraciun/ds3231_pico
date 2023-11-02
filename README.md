# ds3231_pico
A library for using DS3231 RTC with Raspberry Pi Pico

[DS3231 datasheet](https://www.analog.com/media/en/technical-documentation/data-sheets/DS3231.pdf)


## Setup
```cpp
/**
 * Declarations
 */
#define I2C_INSTANCE i2c0     // Identifier for I2C hardware block 0 of RP pico
#define I2C_SDA 21            // I2C SDA pin wired to ds3231
#define I2C_SCL 20            // I2C SCL pin wired to ds3231
#define DS3231_I2C_ADDR 0x68  // I2C address of ds3231
#define I2C_BAUDRATE 100*1000 // I2C communication speed

int main()
{
  stdio_init_all();

  // RP pico I2C SETUP
  i2c_init(I2C_INSTANCE, I2C_BAUDRATE);
  gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);
  gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);
  gpio_pull_up(I2C_SDA);
  gpio_pull_up(I2C_SCL);

  // Get ds3231 instance
  ds3231 rtcDevice{I2C_INSTANCE, DS3231_I2C_ADDR};
}
```


## Setting the time inside ds3231
```cpp
// Init time struct
datetime_t t = {
  .year  = 2023,
  .month = 10,
  .day   = 31,
  .dotw  = 2,
  .hour  = 18,
  .min   = 38,
  .sec   = 00
};

// Set the time inside ds3231 device
rtcDevice.setTime(&t);
```


## Reading the time from ds3231
```cpp
// RP pico time structure
datetime_t t;

// Read the time from ds3231 device
rtcDevice.readTime(&t);

// Convert the datetime_t to a string and display it
char datetime_buf[256];
char *datetime_str = &datetime_buf[0];
datetime_to_str(datetime_str, sizeof(datetime_buf), &t);
printf("\r%s      ", datetime_str);
```


## Methods
### `readTime()`
Reads the datetime from ds3231 device
```cpp
datetime_t t;
rtcDevice.readTime(&t);
```

### `setTime()`
Sets the datetime inside ds3231 device
```cpp
datetime_t t = {
  .year  = 2023,
  .month = 10,
  .day   = 31,
  .dotw  = 2,
  .hour  = 18,
  .min   = 38,
  .sec   = 00
};
rtcDevice.setTime(&t);
```

### `readSeconds()`
Reads the seconds from ds3231 device
- value between 0 - 59
```cpp
uint8_t seconds = rtcDevice.readSeconds();
```

### `setSeconds()`
Sets the seconds inside ds3231 device
- value between 0 - 59
```cpp
uint8_t seconds = 24;
rtcDevice.setSeconds(seconds);
```

### `readMinutes()`
Reads the minutes from ds3231 device
- value between 0 - 59
```cpp
uint8_t minutes = rtcDevice.readMinutes();
```

### `setMinutes()`
Sets the minutes inside ds3231 device
- value between 0 - 59
```cpp
uint8_t minutes = 24;
rtcDevice.setMinutes(minutes);
```

### `readHour()`
Reads the hour from ds3231 device
- value between 0 - 23
```cpp
uint8_t hour = rtcDevice.readHour();
```

### `setHour()`
Sets the hour inside ds3231 device
- value between 0 - 23
```cpp
uint8_t hour = 14;
rtcDevice.setHour(hour);
```

### `readDotw()`
Reads the day of the week from ds3231 device
- value between 0(Sunday) - 6(Saturday) 
```cpp
uint8_t dotw = rtcDevice.readDotw();
```

### `setDotw()`
Sets the day of the week inside ds3231 device
- value between 0(Sunday) - 6(Saturday)
```cpp
uint8_t dotw = 14;
rtcDevice.setDotw(dotw);
```

### `readDay()`
Reads the day from ds3231 device
- value between 1 - 28,29,30,31 depending on month
```cpp
uint8_t day = rtcDevice.readDay();
```

### `setDay()`
Sets the day inside ds3231 device
- value between 0 - 28,29,30,31 depending on month
```cpp
uint8_t day = 12;
rtcDevice.setDay(day);
```

### `readMonth()`
Reads the month from ds3231 device
- value between 1(January) - 12(December)
```cpp
uint8_t month = rtcDevice.readMonth();
```

### `setMonth()`
Sets the month inside ds3231 device
- value between 1(January) - 12(December)
```cpp
uint8_t month = 14;
rtcDevice.setMonth(month);
```

### `readYear()`
Reads the year from ds3231 device
- value between 2000 - 2099
```cpp
uint16_t year = rtcDevice.readYear();
```

### `setYear()`
Sets the year inside ds3231 device
- value between 2000 - 2099
```cpp
uint16_t year = 2023;
rtcDevice.setYear(year);
```

### `readRegister(address)`
Reads the content of the register
- value in BCD representation
```cpp
uint8_t hourRegAddr = 0x02;
uint8_t hourRegVal = rtcDevice.readRegister(hourRegAddr);
```

### `setRegister(address, value)`
Sets the content of the register
- value in BCD representation
```cpp
uint8_t secondsRegAddr = 0x00;
uint8_t secondsRegVal = 0x06;
rtcDevice.setRegister(secondsRegAddr, secondsRegVal);
```
