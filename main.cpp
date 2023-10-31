#include <stdio.h>

#include "ds3231.h"

#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "pico/util/datetime.h"

#define I2C_INSTANCE i2c0
#define I2C_SDA 21
#define I2C_SCL 20
#define DS3231_I2C_ADDR 0x68
#define I2C_BAUDRATE 100*1000

int main()
{
  stdio_init_all();

  // I2C SETUP
  i2c_init(I2C_INSTANCE, I2C_BAUDRATE);
  gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);
  gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);
  gpio_pull_up(I2C_SDA);
  gpio_pull_up(I2C_SCL);

  ds3231 rtcDevice{I2C_INSTANCE, DS3231_I2C_ADDR};

  // Init time
  datetime_t t = {
    .year  = 2023,
    .month = 10,
    .day   = 31,
    .dotw  = 2,
    .hour  = 18,
    .min   = 38,
    .sec   = 00
  };

  char datetime_buf[256];
  char *datetime_str = &datetime_buf[0];

  sleep_ms(250);

  // Set ds3231 time
  rtcDevice.setTime(&t);


  while (true)
  {
    rtcDevice.readTime(&t);
    datetime_to_str(datetime_str, sizeof(datetime_buf), &t);
    printf("\r%s      ", datetime_str);
    sleep_ms(100);
  }
}