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
#define dow_addr 0x03
#define day_addr 0x04
#define month_addr 0x05
#define year_addr 0x06

/**
 * @brief DS3231 wrapper class
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
   * @brief Reads the time from the DS3231 device
   * @param[out] t stores the time data
  */
  void readTime(datetime_t *t);

  /**
   * @brief Sets the time inside the DS3231 device
   * @param[in] t stores the time data
  */
  void setTime(datetime_t *t);
};

#endif