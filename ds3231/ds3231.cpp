#include "ds3231.h"

// Convert bcd value to decimal value
static inline uint8_t bcd_decimal(uint8_t val)
{
    return ((val & 0xF0) >> 4) * 10 + (val & 0x0F);
}

// Convert decimal value to bcd value
static inline uint8_t decimal_bcd(uint8_t val)
{
  return (val / 10 << 4) | (val % 10);
}

ds3231::ds3231(i2c_inst_t* I2C_INSTANCE, int DEVICE_ADDRESS)
  : I2C_INSTANCE {I2C_INSTANCE}
  , DEVICE_ADDRESS {DEVICE_ADDRESS}
{
  timeBuffer = new uint8_t[8] {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
}

ds3231::~ds3231()
{
  delete[] timeBuffer;
}

void ds3231::readTime(datetime_t *t)
{
  // Start reading from seconds adress
  i2c_write_blocking(I2C_INSTANCE, DEVICE_ADDRESS, sec_addr, 1, true);

  // Start reading 7 bytes
  i2c_read_blocking(I2C_INSTANCE, DEVICE_ADDRESS, timeBuffer, 7, true);

  t->sec = bcd_decimal(timeBuffer[0]);
  t->min = bcd_decimal(timeBuffer[1]);
  t->hour = bcd_decimal(timeBuffer[2]);
  t->dotw = bcd_decimal(timeBuffer[3]) - 1;
  t->day = bcd_decimal(timeBuffer[4]);
  t->month = bcd_decimal(timeBuffer[5]);
  t->year = bcd_decimal(timeBuffer[6]) + 2000;
}

void ds3231::setTime(datetime_t *t)
{
  // Start writing from seconds address
  timeBuffer[0] = sec_addr;
  timeBuffer[1] = decimal_bcd(t->sec);
  timeBuffer[2] = decimal_bcd(t->min);
  timeBuffer[3] = decimal_bcd(t->hour);
  // datetime_t keeps dotw from 0 to 6, while ds3231 from 1 to 7
  timeBuffer[4] = decimal_bcd(t->dotw + 1);
  timeBuffer[5] = decimal_bcd(t->day);
  timeBuffer[6] = decimal_bcd(t->month);
  // datetime_t keeps year as uint16_t (0 to 4095), while ds3231 as uint8_t (0 to 99)
  timeBuffer[7] = decimal_bcd(t->year - 2000);

  // Send data over i2c
  i2c_write_blocking(I2C_INSTANCE, DEVICE_ADDRESS, timeBuffer, 8, true);
}
