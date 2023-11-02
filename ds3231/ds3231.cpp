#include "ds3231.h"

/**
 * Convert bcd value to decimal value
 * @param val BCD value
 * @returns decimal representation of `val`
 */
static inline uint8_t bcd_decimal(uint8_t val)
{
    return ((val & 0xF0) >> 4) * 10 + (val & 0x0F);
}

/**
 * Convert decimal value to bcd value
 * @param val decimal value
 * @returns BCD represantation of `val`
 */
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

uint8_t ds3231::readRegister(uint8_t addr)
{
  // Start reading from adress
  timeBuffer[0] = addr;
  i2c_write_blocking(I2C_INSTANCE, DEVICE_ADDRESS, timeBuffer, 1, true);

  // Start reading 1 byte
  i2c_read_blocking(I2C_INSTANCE, DEVICE_ADDRESS, timeBuffer, 1, true);

  return timeBuffer[0];
}

void ds3231::setRegister(uint8_t addr, uint8_t value)
{
  timeBuffer[0] = addr;
  timeBuffer[1] = value;

  i2c_write_blocking(I2C_INSTANCE, DEVICE_ADDRESS, timeBuffer, 2, true);
}

void ds3231::readTime(datetime_t *t)
{
  // Start reading from seconds adress
  timeBuffer[0] = sec_addr;
  i2c_write_blocking(I2C_INSTANCE, DEVICE_ADDRESS, timeBuffer, 1, true);

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

uint8_t ds3231::readSeconds()
{
  return bcd_decimal(readRegister(sec_addr));
}

void ds3231::setSeconds(uint8_t seconds)
{
  setRegister(sec_addr, decimal_bcd(seconds));
}

uint8_t ds3231::readMinutes()
{
  return bcd_decimal(readRegister(min_addr));
}

void ds3231::setMinutes(uint8_t minutes)
{
  setRegister(min_addr, decimal_bcd(minutes));
}

uint8_t ds3231::readHour()
{
  return bcd_decimal(readRegister(hour_addr));
}

void ds3231::setHour(uint8_t hour)
{
  setRegister(hour_addr, decimal_bcd(hour));
}

uint8_t ds3231::readDotw()
{
  // datetime_t keeps dotw from 0 to 6, while ds3231 from 1 to 7
  return bcd_decimal(readRegister(dotw_addr)) - 1;
}

void ds3231::setDotw(uint8_t dotw)
{
  // datetime_t keeps dotw from 0 to 6, while ds3231 from 1 to 7
  setRegister(dotw_addr, decimal_bcd(dotw + 1));
}

uint8_t ds3231::readDay()
{
  return bcd_decimal(readRegister(day_addr));
}

void ds3231::setDay(uint8_t day)
{
  setRegister(day_addr, decimal_bcd(day));
}

uint8_t ds3231::readMonth()
{
  return bcd_decimal(readRegister(month_addr));
}

void ds3231::setMonth(uint8_t month)
{
  setRegister(month_addr, decimal_bcd(month));
}

uint16_t ds3231::readYear()
{
  // datetime_t keeps year as uint16_t (0 to 4095), while ds3231 as uint8_t (0 to 99)
  return bcd_decimal(readRegister(year_addr)) + 2000;
}

void ds3231::setYear(uint16_t year)
{
  // datetime_t keeps year as uint16_t (0 to 4095), while ds3231 as uint8_t (0 to 99)
  setRegister(year_addr, decimal_bcd(year - 2000));
}