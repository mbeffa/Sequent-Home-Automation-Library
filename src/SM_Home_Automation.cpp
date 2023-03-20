extern "C"
{
#include <inttypes.h>
}

#include "Arduino.h"
#include "Wire.h"
#include "SM_Home_Automation.h"

SM_Home_Automation::SM_Home_Automation(uint8_t stack)
{
  if (stack > 7)
    stack = 7;
  _hwAdd = HA_SLAVE_OWN_ADDRESS_BASE + stack;
  _detected = false;
}

bool SM_Home_Automation::begin()
{
  uint8_t value = 0;
  if ( 0 == readByte(HA_I2C_MEM_REVISION_MAJOR_ADD, &value))
  {
    _detected = true;
  }
  return _detected;
}

bool SM_Home_Automation::isAlive()
{
  return _detected;
}

bool SM_Home_Automation::writeRelay(uint8_t relay, bool val)
{
  if (relay > HA_RELAY_CH_NO || relay == 0)
  {
    return false;
  }
  if (val)
  {
    if (OK == writeByte(HA_I2C_MEM_RELAY_SET_ADD, relay))
      return true;
  }
  else
  {
    if (OK == writeByte(HA_I2C_MEM_RELAY_CLR_ADD, relay))
      return true;
  }
  return false;
}

bool SM_Home_Automation::writeRelay(uint8_t val)
{
  if (OK == writeByte(HA_I2C_MEM_RELAY_VAL_ADD, val))
    return true;
  return false;
}

int SM_Home_Automation::readAanalogMv(uint8_t channel)
{
  int ret = 0;
  uint16_t val = 0;

  if (channel < 1 || channel > HA_ADC_CH_NO)
  {
    return -1;
  }
  ret = readWord(HA_I2C_MEM_ADC_VAL_MV_ADD + (channel - 1) * HA_DAC_MV_VAL_SIZE, &val);
  if (ret < 0)
    return ret;
  return val;
}

bool SM_Home_Automation::writeAnalogMv(uint8_t channel, int val)
{
  if (channel < 1 || channel > HA_DAC_CH_NO)
  {
    return false;
  }

  if (val < 0 || val > HA_DAC_MAX_VAL_MV)
  {
    return false;
  }
  if (OK == writeWord(HA_I2C_MEM_DAC_VAL_MV_ADD + (channel - 1) * HA_DAC_MV_VAL_SIZE, (uint16_t)val))
    return true;
  return false;
}


bool SM_Home_Automation::writeOdPwm(uint8_t channel, float val)
{
  if (channel < 1 || channel > HA_OD_CH_NO)
  {
    return false;
  }
  if ( val < 0 || val > 100)
  {
    return false;
  }
  return writeWord(HA_I2C_MEM_OD_PWM_VAL_RAW_ADD + (channel - 1) * HA_DAC_MV_VAL_SIZE, (uint16_t)(val * 100));
}


bool SM_Home_Automation::writePwmFreq(int val)
{
  if (val < HA_OD_PWM_FREQ_MIN_HZ || val > HA_OD_PWM_FREQ_MAX_HZ)
  {
    return false;
  }
 return (OK == writeWord(HA_I2C_MEM_OD_PWM_FREQUENCY, (uint16_t)val));
}


int SM_Home_Automation::readOpto(uint8_t channel)
{
  uint8_t aux = 0;

  if (channel < 1 || channel > HA_OPTO_CH_NO)
  {
    return ERROR;
  }
  if (readByte(HA_I2C_MEM_OPTO_IN_ADD, &aux) == OK)
  {
    if (aux & 1 << (channel - 1))
    {
      return 1;
    }
    else
    {
      return 0;
    }
  }
  return ERROR;
}

/**
   Get the optically isolated inspus as a 8 bits bitmap
   Returns the opto bitmap or -1 in case of error
*/
int SM_Home_Automation::readOpto()
{
  uint8_t aux = 0;

  if (readByte(HA_I2C_MEM_OPTO_IN_ADD, &aux) == OK)
  {
    return aux;
  }
  return -1;
}

/**
   Configure counter on opto input channel
    channel 1..8
    settings 0 -disable counter; 1 - enable falling edge; 2 enable rising edge counter
*/
bool SM_Home_Automation::cfgOptoCounter(uint8_t channel, haCountSettings_t settings)
{
  uint8_t buff[2] = {0, 0};
  uint16_t aux = 0;

  if (channel < 1 || channel > HA_OPTO_CH_NO)
  {
    return false;
  }

  if (readWord(HA_I2C_MEM_OPTO_IT_RISING_ADD, (uint16_t*)buff) != OK)
  {
    return false;
  }
  switch (settings)
  {
    case HA_COUNT_DISABLE:
      buff[0] &= ~(uint8_t)(1 << (channel - 1));
      buff[1] &= ~(uint8_t)(1 << (channel - 1));
      break;
    case HA_COUNT_RISING:
      buff[0] &= ~(uint8_t)(1 << (channel - 1));
      buff[1] |= (uint8_t)(1 << (channel - 1));
      break;
    case HA_COUNT_FALLING:
      buff[0] |= (uint8_t)(1 << (channel - 1));
      buff[1] &= ~(uint8_t)(1 << (channel - 1));
      break;
    case HA_COUNT_BOTH:
      buff[0] |= (uint8_t)(1 << (channel - 1));
      buff[1] |= (uint8_t)(1 << (channel - 1));
      break;
    default:
      return ERROR;
      break;
  }
  memcpy(&aux, buff, 2);
  return (OK == writeWord(HA_I2C_MEM_OPTO_IT_RISING_ADD, aux));
}

int SM_Home_Automation::readOptoCounter(uint8_t channel)
{
  uint32_t val = 0;

  if (channel < 1 || channel > HA_OPTO_CH_NO)
  {
    return ERROR;
  }
  if (readDWord(HA_I2C_MEM_OPTO_EDGE_COUNT_ADD + (channel - 1) * HA_COUNTER_SIZE, &val) != OK)
  {
    return ERROR;
  }
  return val;
}

bool SM_Home_Automation::resetOptoCounter(uint8_t channel)
{
  if (channel < 1 || channel > HA_OPTO_CH_NO)
  {
    return false;
  }
  return (OK == writeByte(HA_I2C_MEM_OPTO_CNT_RST_ADD, channel));
}

bool SM_Home_Automation::cfgOptoEncoder(uint8_t channel, bool enable)
{
  uint8_t aux = 0;
  if (channel < 1 || channel > HA_OPTO_CH_NO / 2)
  {
    return false;
  }
  
  if (readByte(HA_I2C_MEM_OPTO_ENC_ENABLE_ADD, &aux) != OK)
  {
    return false;
  }
  if (!enable)
  {
    aux &= ~(uint8_t)(1 << (channel - 1));
  }
  else
  {
    aux |= (uint8_t)(1 << (channel - 1));
  }
  return (OK == writeByte(HA_I2C_MEM_OPTO_ENC_ENABLE_ADD, aux));
}

int SM_Home_Automation::readOptoEncoder(uint8_t channel)
{
  int32_t val = 0;

  if (channel < 1 || channel > HA_OPTO_CH_NO / 2)
  {
    return ERROR;
  }
  if (readSignedDWord(HA_I2C_MEM_OPTO_ENC_COUNT_ADD + (channel - 1) * HA_COUNTER_SIZE, &val) != OK)
  {
    return ERROR;
  }
  return val;
}

bool SM_Home_Automation::resetOptoEncoder(uint8_t channel)
{
  if (channel < 1 || channel > HA_OPTO_CH_NO / 2)
  {
    return false;
  }
  return (OK == writeByte(HA_I2C_MEM_GPIO_ENC_CNT_RST_ADD, channel));
}

/***************** HA_I2C access functions *********************************
 *  *********************************************************************
*/
int SM_Home_Automation::writeByte(uint8_t add, uint8_t value)
{
  Wire.begin();
  Wire.beginTransmission(_hwAdd);
  Wire.write(add);
  Wire.write(value);
  return Wire.endTransmission();
}

int SM_Home_Automation::writeWord(uint8_t add, uint16_t value)
{
  uint8_t buff[2];

  memcpy(buff, &value, 2);
  Wire.begin();
  Wire.beginTransmission(_hwAdd);
  Wire.write(add);
  Wire.write(buff[0]);
  Wire.write(buff[1]);
  return Wire.endTransmission();

}
int SM_Home_Automation::writeDWord(uint8_t add, uint32_t value)
{
  uint8_t buff[4];
  int i = 0;

  memcpy(buff, &value, 4);
  Wire.begin();
  Wire.beginTransmission(_hwAdd);
  Wire.write(add);
  for (i = 0; i < 4; i++)
  {
    Wire.write(buff[i]);
  }
  return Wire.endTransmission();

}
int SM_Home_Automation::readByte(uint8_t add, uint8_t* value)
{
  if (0 == value)
  {
    return -1;
  }
  Wire.begin();
  Wire.beginTransmission(_hwAdd);
  Wire.write(add);
  if (Wire.endTransmission() != 0)
  {
    return -1;
  }
  Wire.requestFrom(_hwAdd, (uint8_t)1);
  if (1 <= Wire.available())
  {
    *value = Wire.read();
  }
  else
  {
    return -1;
  }
  return 0;
}
int SM_Home_Automation::readWord(uint8_t add, uint16_t* value)
{
  uint8_t buff[2];

  if (0 == value)
  {
    return -1;
  }
  Wire.begin();
  Wire.beginTransmission(_hwAdd);
  Wire.write(add);
  if (Wire.endTransmission() != 0)
  {
    return -1;
  }
  Wire.requestFrom(_hwAdd, (uint8_t)2);
  if (2 <= Wire.available())
  {
    buff[0] = Wire.read();
    buff[1] = Wire.read();
  }
  else
  {
    return -1;
  }
  memcpy(value, buff, 2);
  return 0;
}

int SM_Home_Automation::readDWord(uint8_t add, uint32_t* value)
{
  uint8_t buff[4];
  int i = 0;

  if (0 == value)
  {
    return -1;
  }
  Wire.begin();
  Wire.beginTransmission(_hwAdd);
  Wire.write(add);
  if (Wire.endTransmission() != 0)
  {
    return -1;
  }
  Wire.requestFrom(_hwAdd, (uint8_t)2);
  if (4 <= Wire.available())
  {
    for (i = 0; i < 4; i++)
    {
      buff[i] = Wire.read();
    }
  }
  else
  {
    return -1;
  }
  memcpy(value, buff, 4);
  return 0;
}

int SM_Home_Automation::readSignedDWord(uint8_t add, int32_t* value)
{
  uint8_t buff[4];
  int i = 0;

  if (0 == value)
  {
    return -1;
  }
  Wire.begin();
  Wire.beginTransmission(_hwAdd);
  Wire.write(add);
  if (Wire.endTransmission() != 0)
  {
    return -1;
  }
  Wire.requestFrom(_hwAdd, (uint8_t)2);
  if (4 <= Wire.available())
  {
    for (i = 0; i < 4; i++)
    {
      buff[i] = Wire.read();
    }
  }
  else
  {
    return -1;
  }
  memcpy(value, buff, 4);
  return 0;
}
