/*!
 * @file SM_HomeAutomation.h
 * 
 * Designed specifically to work with the Sequent Microsysatems 
 * Home Automation 8-Layer Stackable HAT for Raspberry Pi
 * 
 * ----> https://sequentmicrosystems.com/collections/home-automation/products/raspberry-pi-home-automation-card
 * 
 *   This card use I2C to communicate.
 *   
 *   Written by Alexandru Burcea for Sequent Microsystems
 * 
 *   Software License Agreement (BSD License)
 *
 *  Copyright (c) 2023, Sequent Microsystems 
 *  
 */

#ifndef SM_HOME_AUTOMATION_H_
#define SM_HOME_AUTOMATION_H_

#include "Arduino.h"
#include <inttypes.h>

#define ERROR -1
#define OK 0
#define HA_ADC_CH_NO  8
#define HA_ADC_RAW_VAL_SIZE  2
#define HA_DAC_CH_NO 4
#define HA_DAC_MV_VAL_SIZE 2
#define HA_DAC_MAX_VAL_MV 10000
#define HA_RELAY_CH_NO 8
#define HA_OD_CH_NO 4
#define HA_OD_RAW_SIZE 2
#define HA_OD_RAW_VAL_MAX 10000
#define HA_OD_PWM_FREQ_MAX_HZ 64000
#define HA_OD_PWM_FREQ_MIN_HZ 10
#define HA_OPTO_CH_NO 8
#define HA_GPIO_CH_NO 4
#define HA_COUNTER_SIZE 4
#define HA_OPTO_ENC_CH_NO 4
#define HA_CALIBRATION_KEY 0xaa
#define HA_RESET_CALIBRATION_KEY 0x55

typedef enum {
  HA_COUNT_DISABLE = 0,
  HA_COUNT_RISING = 1,
  HA_COUNT_FALLING = 2,
  HA_COUNT_BOTH = 3
}haCountSettings_t;

enum
{
  HA_I2C_MEM_RELAY_VAL_ADD = 0,
  HA_I2C_MEM_RELAY_SET_ADD,
  HA_I2C_MEM_RELAY_CLR_ADD,
  HA_I2C_MEM_OPTO_IN_ADD,
  HA_I2C_MEM_GPIO_VAL_ADD,
  HA_I2C_MEM_GPIO_SET_ADD,
  HA_I2C_MEM_GPIO_CLR_ADD,
  HA_I2C_MEM_GPIO_DIR_ADD,
  HA_I2C_MEM_ADC_VAL_RAW_ADD,
  HA_I2C_MEM_ADC_VAL_MV_ADD = HA_I2C_MEM_ADC_VAL_RAW_ADD + HA_ADC_CH_NO * HA_ADC_RAW_VAL_SIZE,
  HA_I2C_MEM_DAC_VAL_MV_ADD = HA_I2C_MEM_ADC_VAL_MV_ADD + HA_ADC_CH_NO * HA_ADC_RAW_VAL_SIZE,
  HA_I2C_MEM_OD_PWM_VAL_RAW_ADD = HA_I2C_MEM_DAC_VAL_MV_ADD + HA_DAC_CH_NO * HA_DAC_MV_VAL_SIZE,
  HA_I2C_MEM_OPTO_IT_RISING_ADD = HA_I2C_MEM_OD_PWM_VAL_RAW_ADD + HA_DAC_CH_NO * HA_DAC_MV_VAL_SIZE,
  HA_I2C_MEM_OPTO_IT_FALLING_ADD,
  HA_I2C_MEM_GPIO_EXT_IT_RISING_ADD,
  HA_I2C_MEM_GPIO_EXT_IT_FALLING_ADD,
  HA_I2C_MEM_OPTO_CNT_RST_ADD,
  HA_I2C_MEM_GPIO_CNT_RST_ADD,
  HA_I2C_MEM_DIAG_TEMPERATURE_ADD,
  HA_I2C_MEM_DIAG_3V3_MV_ADD,
  HA_I2C_MEM_DIAG_3V3_MV_ADD1,
  HA_I2C_MEM_CALIB_VALUE,
  HA_I2C_MEM_CALIB_CHANNEL = HA_I2C_MEM_CALIB_VALUE + 2,//ADC channels [1,8]; DAC channels [9, 12]
  HA_I2C_MEM_CALIB_KEY, //write calib point 0xaa; reset calibration on the channel 0x55
  HA_I2C_MEM_CALIB_STATUS,
  HA_I2C_MEM_OPTO_ENC_ENABLE_ADD ,
  HA_I2C_MEM_GPIO_ENC_ENABLE_ADD,
  HA_I2C_MEM_OPTO_ENC_CNT_RST_ADD,
  HA_I2C_MEM_GPIO_ENC_CNT_RST_ADD,
  HA_I2C_MEM_WDT_RESET_ADD = 100,
  HA_I2C_MEM_WDT_INTERVAL_SET_ADD,
  HA_I2C_MEM_WDT_INTERVAL_GET_ADD = HA_I2C_MEM_WDT_INTERVAL_SET_ADD + 2,
  HA_I2C_MEM_WDT_INIT_INTERVAL_SET_ADD = HA_I2C_MEM_WDT_INTERVAL_GET_ADD + 2,
  HA_I2C_MEM_WDT_INIT_INTERVAL_GET_ADD = HA_I2C_MEM_WDT_INIT_INTERVAL_SET_ADD + 2,
  HA_I2C_MEM_WDT_RESET_COUNT_ADD = HA_I2C_MEM_WDT_INIT_INTERVAL_GET_ADD + 2,
  HA_I2C_MEM_WDT_CLEAR_RESET_COUNT_ADD = HA_I2C_MEM_WDT_RESET_COUNT_ADD + 2,
  HA_I2C_MEM_WDT_POWER_OFF_INTERVAL_SET_ADD,
  HA_I2C_MEM_WDT_POWER_OFF_INTERVAL_GET_ADD = HA_I2C_MEM_WDT_POWER_OFF_INTERVAL_SET_ADD + 4,
  HA_I2C_MEM_REVISION_HW_MAJOR_ADD = 0x78,
  HA_I2C_MEM_REVISION_HW_MINOR_ADD,
  HA_I2C_MEM_REVISION_MAJOR_ADD,
  HA_I2C_MEM_REVISION_MINOR_ADD,
  HA_I2C_DBG_FIFO_SIZE,
  HA_I2C_DBG_FIFO_ADD = HA_I2C_DBG_FIFO_SIZE + 2,
  HA_I2C_DBG_CMD,
  HA_I2C_MEM_OPTO_EDGE_COUNT_ADD,
  HA_I2C_MEM_OPTO_EDGE_COUNT_END_ADD = HA_I2C_MEM_OPTO_EDGE_COUNT_ADD + HA_COUNTER_SIZE * HA_OPTO_CH_NO,//!gap
  HA_I2C_MEM_OD_PWM_FREQUENCY, //2 bytes
  HA_I2C_MEM_ADD_RESERVED = 0xaa,
  HA_I2C_MEM_GPIO_EDGE_COUNT_ADD,
  HA_I2C_MEM_OPTO_ENC_COUNT_ADD = HA_I2C_MEM_GPIO_EDGE_COUNT_ADD + HA_COUNTER_SIZE * HA_GPIO_CH_NO,
  HA_I2C_MEM_GPIO_ENC_COUNT_ADD = HA_I2C_MEM_OPTO_ENC_COUNT_ADD + HA_COUNTER_SIZE * HA_OPTO_CH_NO/2,
  HA_I2C_MEM_GPIO_ENC_COUNT_END_ADD = HA_I2C_MEM_GPIO_ENC_COUNT_ADD + HA_COUNTER_SIZE * HA_GPIO_CH_NO/2,
  HA_SLAVE_BUFF_SIZE 
};

#define HA_SLAVE_OWN_ADDRESS_BASE 0x28

/*!
 * @brief Main Home Automation class
 */
class SM_Home_Automation
{
  public:
    SM_Home_Automation(uint8_t stack = 0);
    /*!
     * @brief Check card presence
     * @return Returns true is successful
     */
    bool begin();
    /*!
     * @brief Return card existance status
     * @return Returns true if card is present
     */
    bool isAlive();
    /*!
     * @brief Set one relay state
     * @param relay Relay number 1..8 as are printed on the card
     * @param val The new state of the realay true: energised
     * @return Returns true if successful
     */
    bool writeRelay(uint8_t relay, bool val);
    /*!
     * @brief Write all relays state as a 8 bits bitmap
     * @param val The bitmap of the relays
     * @return Returns true if successful
     */
    bool writeRelay(uint8_t val);
    /*!
     * @brief Read the value in millivolts of on analog input channel, range 0 ... 3300
     * @param channel The analog input channel number 1..8
     * @return Returns analog input millivolts 
     */
    int readAanalogMv(uint8_t channel);
    /*!
     * @brief Write the analog output ports voltage in millivolts, range 0 to 10V
     * @param channel Analog (0-10V) output channel number [1..4]
     * @param val Votage output in millivolts [0..10000]
     * @return Returns true if successful
     */
    bool writeAnalogMv(uint8_t channel, int val);
    bool writeOdPwm(uint8_t channel, float val);
    bool writePwmFreq(int val);
    int readOpto(uint8_t channel);
    int readOpto();
    bool cfgOptoCounter(uint8_t channel, haCountSettings_t settings);
    int readOptoCounter(uint8_t channel);
    bool resetOptoCounter(uint8_t channel);
    bool cfgOptoEncoder(uint8_t channel, bool enable);
    int readOptoEncoder(uint8_t channel);
    bool resetOptoEncoder(uint8_t channel);
   
  private:
    uint8_t _hwAdd;
    bool _detected;
    int writeBuff(uint8_t add, uint8_t* buff, uint8_t size);
    int readBuff(uint8_t add, uint8_t* buff, uint8_t size);
    int writeByte(uint8_t add, uint8_t value);
    int writeWord(uint8_t add, uint16_t value);
    int writeDWord(uint8_t add, uint32_t value);
    int readByte(uint8_t add, uint8_t* value);
    int readWord(uint8_t add, uint16_t* value);
    int readDWord(uint8_t add, uint32_t* value);
    int readSignedDWord(uint8_t add, int32_t* value);
};

#endif //SM_HOME_H_
