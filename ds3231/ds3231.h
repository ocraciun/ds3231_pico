#ifndef __DS3231_H
#define __DS3231_H

#include "pico/stdlib.h"
#include "hardware/i2c.h"

// I2C address of DS3231
#define DEFAULT_DEVICE_ADDRESS 0x68

// DS3231 registers address
#define sec_addr 0x00
#define min_addr 0x01
#define hour_addr 0x02
#define dotw_addr 0x03
#define day_addr 0x04
#define month_addr 0x05
#define year_addr 0x06

/**
 * @brief DS3231 wrapper class
 * @class ds3231
*/
class ds3231
{
private:
  int DEVICE_ADDRESS {DEFAULT_DEVICE_ADDRESS};
  i2c_inst_t* I2C_INSTANCE {NULL};
  uint8_t *timeBuffer;
public:
  /**
   * @brief Constructor for DS3231 wrapper
   * 
   * @param I2C_INSTANCE Identifier for I2C HW Block
   * @param DEVICE_ADDRESS I2C device address of DS3231 module
  */
  ds3231(i2c_inst_t* I2C_INSTANCE, int DEVICE_ADDRESS = DEFAULT_DEVICE_ADDRESS);
  
  /**
   * @brief Destructor for DS3231 wrapper
  */
  ~ds3231();

  /**
   * @brief Reads the content of the register
   * @param addr the address of the register
   * @returns value of the register
  */
  uint8_t readRegister(uint8_t addr);

  /**
   * @brief Sets the content of the register
   * @param addr the address of the register
   * @param value the value to write
  */
  void setRegister(uint8_t addr, uint8_t value);

  /**
   * @brief Reads the time from the DS3231 device
   * @param[out] t stores the time data
  */
  void readTime(datetime_t *t);

  /**
   * @brief Sets the time inside the DS3231 device
   * @param[in] t stores the time data
  */
  void setTime(datetime_t *t);

  /**
   * @brief Reads the seconds from the DS3231 device
   * @returns seconds value between 0 and 59
  */
  uint8_t readSeconds(void);

  /**
   * @brief Sets the seconds inside the DS3231 device
   * @param seconds value to be set between 0 and 59
  */
  void setSeconds(uint8_t seconds);

  /**
   * @brief Reads the minutes from the DS3231 device
   * @returns the minutes value between 0 and 59
  */
  uint8_t readMinutes(void);

  /**
   * @brief Sets the minutes inside the DS3231 device
   * @param minutes value to be set between 0 and 59
  */
  void setMinutes(uint8_t minutes);

  /**
   * @brief Reads the hour from the DS3231 device
   * @returns the hour value between 0 and 23
  */
  uint8_t readHour(void);

  /**
   * @brief Sets the hour inisde the DS3231 device
   * @param hour value to be set between 0 and 23
  */
  void setHour(uint8_t hour);

  /**
   * @brief Reads the day of the week from the DS3231 device
   * @returns day of the week value between 0 - Sunday and 6 - Saturday
  */
  uint8_t readDotw(void);

  /**
   * @brief Sets the day of the week inside the DS3231 device
   * @see ds3231::setDay(uint8_t day) to change the day of the month
   * @param dotw value to be set betwee 0 - Sunday and 6 - Saturday
  */
  void setDotw(uint8_t dotw);

  /**
   * @brief Reads the day from the DS3231 device
   * @returns day value between 1 and 28,29,30,31 depending on the month
  */
  uint8_t readDay(void);

  /**
   * @brief Sets the day inside the DS3231 device
   * @see ds3231::setDotw(uint8_t dotw) to change the day of the week
   * @param day value to be set between 1 and 28,29,30,31 depending on the month
  */
  void setDay(uint8_t day);

  /**
   * @brief Reads the month from the DS3231 device
   * @returns month value between 1 and 12
  */
  uint8_t readMonth(void);

  /**
   * @brief Sets the month inside the DS3231 device
   * @param month value to be set between 1 and 12
  */
  void setMonth(uint8_t month);

  /**
   * @brief Reads the year from the DS3231 device
   * @returns year value between 2000 and 2099
  */
  uint16_t readYear(void);

  /**
   * @brief Sets the year inside the DS3231 device
   * @param year value to be set between 2000 and 2099
  */
  void setYear(uint16_t year);
};

#endif
