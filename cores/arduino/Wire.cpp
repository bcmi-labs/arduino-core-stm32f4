/*
  TwoWire.cpp - TWI/I2C library for Wiring & Arduino
  Copyright (c) 2006 Nicholas Zambetti.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

  Modified 2012 by Todd Krein (todd@krein.org) to implement repeated starts
*/

/*
 * Arduino srl - www.arduino.org
 * 2016 Jun 9: Edited Francesco Alessi (alfran) - francesco@arduino.org
 */

extern "C" {
  #include <stdlib.h>
  #include <string.h>
  #include <inttypes.h>
  #include "stm32f4xx_hal.h"
}

#include "Wire.h"

#define FLAG_TIMEOUT ((int)0x1000)
#define LONG_TIMEOUT ((int)0x8000)

// Constructors ////////////////////////////////////////////////////////////////
TwoWire::TwoWire(I2C_TypeDef *twi)
{
  I2cHandle.Instance = twi;
  memset(rxBuffer, 0, BUFFER_LENGTH);
  rxBufferIndex = 0;
  rxBufferLength = 0;
  txAddress = 0;
  txBufferIndex = 0;
  txBufferLength = 0;
  transmitting = 0;
  defaultAddress = 0x00;
}

// Public Methods //////////////////////////////////////////////////////////////

void TwoWire::begin(void)
{
  GPIO_InitTypeDef  GPIO_InitStruct;
  I2C_TypeDef *twi = (I2C_TypeDef *)I2cHandle.Instance;

  rxBufferIndex = 0;
  rxBufferLength = 0;

  txBufferIndex = 0;
  txBufferLength = 0;

  //twi_init();
  if(twi == HAL_I2C3)
  {
    /* Enable GPIO TX/RX clock */
    __HAL_RCC_GPIOH_CLK_ENABLE();

    /* Enable I2Cx clock */
    __HAL_RCC_I2C3_CLK_ENABLE();

    /* I2C SCL GPIO pin configuration  */
    GPIO_InitStruct.Pin       = GPIO_PIN_7;
    GPIO_InitStruct.Mode      = GPIO_MODE_AF_OD;
    GPIO_InitStruct.Pull      = GPIO_PULLUP;
    GPIO_InitStruct.Speed     = GPIO_SPEED_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF4_I2C3;
    HAL_GPIO_Init(HAL_GPIOH, &GPIO_InitStruct);

    /* I2C SDA GPIO pin configuration  */
    GPIO_InitStruct.Pin       = GPIO_PIN_8;
    GPIO_InitStruct.Alternate = GPIO_AF4_I2C3;
    HAL_GPIO_Init(HAL_GPIOH, &GPIO_InitStruct);

    HAL_NVIC_SetPriority(I2C3_ER_IRQn, 0, 1);
    HAL_NVIC_EnableIRQ(I2C3_ER_IRQn);
    HAL_NVIC_SetPriority(I2C3_EV_IRQn, 0, 2);
    HAL_NVIC_EnableIRQ(I2C3_EV_IRQn);
  }
  else if(twi == HAL_I2C2)
  {
    /* Enable GPIO TX/RX clock */
    __HAL_RCC_GPIOB_CLK_ENABLE();

  /* Enable I2Cx clock */
    __HAL_RCC_I2C1_CLK_ENABLE();

    /* I2C SCL GPIO pin configuration  */
    GPIO_InitStruct.Pin       = GPIO_PIN_6;
    GPIO_InitStruct.Mode      = GPIO_MODE_AF_OD;
    GPIO_InitStruct.Pull      = GPIO_PULLUP;
    GPIO_InitStruct.Speed     = GPIO_SPEED_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF4_I2C1;
    HAL_GPIO_Init(HAL_GPIOB, &GPIO_InitStruct);

    /* I2C SDA GPIO pin configuration  */
    GPIO_InitStruct.Pin       = GPIO_PIN_7;
    GPIO_InitStruct.Alternate = GPIO_AF4_I2C1;
    HAL_GPIO_Init(HAL_GPIOB, &GPIO_InitStruct);

    HAL_NVIC_SetPriority(I2C2_ER_IRQn, 0, 1);
    HAL_NVIC_EnableIRQ(I2C2_ER_IRQn);
    HAL_NVIC_SetPriority(I2C2_EV_IRQn, 0, 2);
    HAL_NVIC_EnableIRQ(I2C2_EV_IRQn);
  }
  else if(twi == HAL_I2C1)
  {
    /* Enable GPIO TX/RX clock */
    __HAL_RCC_GPIOB_CLK_ENABLE();

  /* Enable I2Cx clock */
    __HAL_RCC_I2C1_CLK_ENABLE();

    /* I2C SCL GPIO pin configuration  */
    GPIO_InitStruct.Pin       = GPIO_PIN_6;
    GPIO_InitStruct.Mode      = GPIO_MODE_AF_OD;
    GPIO_InitStruct.Pull      = GPIO_PULLUP;
    GPIO_InitStruct.Speed     = GPIO_SPEED_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF4_I2C1;
    HAL_GPIO_Init(HAL_GPIOB, &GPIO_InitStruct);

    /* I2C SDA GPIO pin configuration  */
    GPIO_InitStruct.Pin       = GPIO_PIN_7;
    GPIO_InitStruct.Alternate = GPIO_AF4_I2C1;
    HAL_GPIO_Init(HAL_GPIOB, &GPIO_InitStruct);

    HAL_NVIC_SetPriority(I2C1_ER_IRQn, 0, 1);
    HAL_NVIC_EnableIRQ(I2C1_ER_IRQn);
    HAL_NVIC_SetPriority(I2C1_EV_IRQn, 0, 2);
    HAL_NVIC_EnableIRQ(I2C1_EV_IRQn);
  } else
  {
    // Do nothing
  }

  /*##-1- Configure the I2C peripheral ######################################*/
  I2cHandle.Init.ClockSpeed      = 100000;
  I2cHandle.Init.DutyCycle       = I2C_DUTYCYCLE_2;
  I2cHandle.Init.OwnAddress1     = defaultAddress;
  I2cHandle.Init.AddressingMode  = I2C_ADDRESSINGMODE_7BIT;
  I2cHandle.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  I2cHandle.Init.OwnAddress2     = 0x0;
  I2cHandle.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  I2cHandle.Init.NoStretchMode   = I2C_NOSTRETCH_DISABLE;

  HAL_I2C_Init(&I2cHandle);

  /*##-3- Put I2C peripheral in listen mode process ###########################*/
  HAL_I2C_EnableListen_IT(&I2cHandle);
}

void TwoWire::begin(uint8_t address)
{
  defaultAddress = (address << 1);
  begin();
}

void TwoWire::begin(int address)
{
  begin((uint8_t)address);
}

void TwoWire::setClock(uint32_t frequency)
{
  // wait before init
  int timeout = LONG_TIMEOUT;
  while ((__HAL_I2C_GET_FLAG(&I2cHandle, I2C_FLAG_BUSY)) && (timeout-- != 0));

  //TWBR = ((F_CPU / frequency) - 16) / 2;
  I2cHandle.Init.ClockSpeed      = frequency;
  I2cHandle.Init.DutyCycle       = I2C_DUTYCYCLE_2;
  I2cHandle.Init.OwnAddress1     = defaultAddress;
  I2cHandle.Init.AddressingMode  = I2C_ADDRESSINGMODE_7BIT;
  I2cHandle.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  I2cHandle.Init.OwnAddress2     = 0x0;
  I2cHandle.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  I2cHandle.Init.NoStretchMode   = I2C_NOSTRETCH_DISABLE;
  HAL_I2C_Init(&I2cHandle);
}

uint8_t TwoWire::requestFrom(uint8_t address, uint8_t quantity, uint8_t sendStop)
{
  uint8_t ret_val;

  disableInterrupt();

  // clamp to buffer length
  if(quantity > BUFFER_LENGTH){
    quantity = BUFFER_LENGTH;
  }
  // perform blocking read into buffer
  int read = i2c_master_read((address << 1), (char *)rxBuffer, quantity, sendStop);

  if(read < 0)
  {
    ret_val = 0;
  }else
  {
    ret_val = read;
  }

  // set rx buffer iterator vars
  rxBufferIndex = 0;
  rxBufferLength = ret_val;

  enableInterrupt();

  return ret_val;
}

uint8_t TwoWire::requestFrom(uint8_t address, uint8_t quantity)
{
  return requestFrom((uint8_t)address, (uint8_t)quantity, (uint8_t)true);
}

uint8_t TwoWire::requestFrom(int address, int quantity)
{
  return requestFrom((uint8_t)address, (uint8_t)quantity, (uint8_t)true);
}

uint8_t TwoWire::requestFrom(int address, int quantity, int sendStop)
{
  return requestFrom((uint8_t)address, (uint8_t)quantity, (uint8_t)sendStop);
}

void TwoWire::beginTransmission(uint8_t address)
{
  // indicate that we are transmitting
  transmitting = 1;
  // set address of targeted slave
  txAddress = address;
  // reset tx buffer iterator vars
  txBufferIndex = 0;
  txBufferLength = 0;
}

void TwoWire::beginTransmission(int address)
{
  beginTransmission((uint8_t)address);
}

//
//  Originally, 'endTransmission' was an f(void) function.
//  It has been modified to take one parameter indicating
//  whether or not a STOP should be performed on the bus.
//  Calling endTransmission(false) allows a sketch to
//  perform a repeated start.
//
//  WARNING: Nothing in the library keeps track of whether
//  the bus tenure has been properly ended with a STOP. It
//  is very possible to leave the bus in a hung state if
//  no call to endTransmission(true) is made. Some I2C
//  devices will behave oddly if they do not see a STOP.
//
uint8_t TwoWire::endTransmission(uint8_t sendStop)
{
  // transmit buffer (blocking)
  disableInterrupt();

  int8_t ret = i2c_master_write((txAddress << 1), (const char *)txBuffer, txBufferLength, sendStop);
  // reset tx buffer iterator vars
  txBufferIndex = 0;
  txBufferLength = 0;
  // indicate that we are done transmitting
  transmitting = 0;

  enableInterrupt();

  return ret;
}

//  This provides backwards compatibility with the original
//  definition, and expected behaviour, of endTransmission
//
uint8_t TwoWire::endTransmission(void)
{
  return endTransmission(true);
}

// must be called in:
// slave tx event callback
// or after beginTransmission(address)
size_t TwoWire::write(uint8_t data)
{
  if(transmitting){
    // in master transmitter mode
    // don't bother if buffer is full
    if(txBufferLength >= BUFFER_LENGTH){
      return 0;
    }
    // put byte in tx buffer
    txBuffer[txBufferIndex] = data;
    ++txBufferIndex;
    // update amount in buffer
    txBufferLength = txBufferIndex;
  }else{
    // in slave send mode
  // transmit buffer (blocking)
    disableInterrupt();

    // reply to master
  i2c_slave_write((const char *)&data, 1);

  enableInterrupt();

  HAL_I2C_EnableListen_IT(&I2cHandle);
  }
  return 1;
}

// must be called in:
// slave tx event callback
// or after beginTransmission(address)
size_t TwoWire::write(const uint8_t *data, size_t quantity)
{
  if(transmitting){
  // in master transmitter mode
    for(size_t i = 0; i < quantity; ++i){
      write(data[i]);
    }
  }else{
    // in slave send mode
    // reply to master
  disableInterrupt();

  i2c_slave_write((const char *)data, quantity);

  enableInterrupt();

  HAL_I2C_EnableListen_IT(&I2cHandle);
  }
  return quantity;
}

// must be called in:
// slave rx event callback
// or after requestFrom(address, numBytes)
int TwoWire::available(void)
{
  return rxBufferLength - rxBufferIndex;
}

// must be called in:
// slave rx event callback
// or after requestFrom(address, numBytes)
int TwoWire::read(void)
{
  int value = -1;

  // get each successive byte on each call
  if(rxBufferIndex < rxBufferLength){
    value = rxBuffer[rxBufferIndex];
    ++rxBufferIndex;
  }

  return value;
}

// must be called in:
// slave rx event callback
// or after requestFrom(address, numBytes)
int TwoWire::peek(void)
{
  int value = -1;

  if(rxBufferIndex < rxBufferLength){
    value = rxBuffer[rxBufferIndex];
  }

  return value;
}

void TwoWire::flush(void)
{
  // XXX: to be implemented.
}

// sets function called on slave write
void TwoWire::onReceive( void (*function)(int) )
{
  user_onReceive = function;
}

// sets function called on slave read
void TwoWire::onRequest( void (*function)(void) )
{
  user_onRequest = function;
}

int TwoWire::i2c_master_start()
{
    I2C_TypeDef *i2c = (I2C_TypeDef *)I2cHandle.Instance;

    int timeout;

    // Clear Acknowledge failure flag
    __HAL_I2C_CLEAR_FLAG(&I2cHandle, I2C_FLAG_AF);

    // Wait the STOP condition has been previously correctly sent
  // This timeout can be avoid in some specific cases by simply clearing the STOP bit
    timeout = FLAG_TIMEOUT;
    while ((i2c->CR1 & I2C_CR1_STOP) == I2C_CR1_STOP) {
        if ((timeout--) == 0) {
            return 1;
        }
    }

    // Generate the START condition
    i2c->CR1 |= I2C_CR1_START;

    // Wait the START condition has been correctly sent
    timeout = FLAG_TIMEOUT;
    while (__HAL_I2C_GET_FLAG(&I2cHandle, I2C_FLAG_SB) == RESET) {
        if ((timeout--) == 0) {
            return 1;
        }
    }

    return 0;
}

int TwoWire::i2c_master_stop()
{
  I2C_TypeDef *i2c = (I2C_TypeDef *)I2cHandle.Instance;

    // Generate the STOP condition
    i2c->CR1 |= I2C_CR1_STOP;

    return 0;
}

int TwoWire::i2c_master_read(uint8_t address, char *data, uint8_t length, uint8_t stop)
{
    I2C_TypeDef *i2c = (I2C_TypeDef *)I2cHandle.Instance;
    int timeout;
    int count;
    int value;
    int ret;

    i2c_master_start();

    // Wait until SB flag is set
    timeout = FLAG_TIMEOUT;
    while (__HAL_I2C_GET_FLAG(&I2cHandle, I2C_FLAG_SB) == RESET) {
        timeout--;
        if (timeout == 0) {
            return -1;
        }
    }

    i2c->DR = __HAL_I2C_7BIT_ADD_READ(address);

    // Wait address is acknowledged
    timeout = FLAG_TIMEOUT;
    while (__HAL_I2C_GET_FLAG(&I2cHandle, I2C_FLAG_ADDR) == RESET) {
        timeout--;
        if (timeout == 0) {
            return -1;
        }
    }
    __HAL_I2C_CLEAR_ADDRFLAG(&I2cHandle);

    // Read all bytes except last one
    for (count = 0; count < (length - 1); count++) {
        ret = i2c_master_byte_read(&value, 0);
        if(ret)
        {
          return -1;
        }
        data[count] = (char)value;
    }

    // If not repeated start, send stop.
    // Warning: must be done BEFORE the data is read.
    if (stop) {
        i2c_master_stop();
    }

    // Read the last byte
    ret = i2c_master_byte_read(&value, 1);
    if(ret)
    {
      return -1;
    }
    data[count] = (char)value;

    return length;
}

int TwoWire::i2c_master_write(int address, const char *data, int length, int stop)
{
  I2C_TypeDef *i2c = (I2C_TypeDef *)I2cHandle.Instance;
    int timeout;
    int count;

    i2c_master_start();

    // Wait until SB flag is set
    timeout = FLAG_TIMEOUT;
    while (__HAL_I2C_GET_FLAG(&I2cHandle, I2C_FLAG_SB) == RESET) {
        timeout--;
        if (timeout == 0) {
            return 4;
        }
    }

    i2c->DR = __HAL_I2C_7BIT_ADD_WRITE(address);

    // Wait address is acknowledged
    timeout = FLAG_TIMEOUT;
    while (__HAL_I2C_GET_FLAG(&I2cHandle, I2C_FLAG_ADDR) == RESET) {
        timeout--;
        if (timeout == 0) {
            return 2;
        }
    }
    __HAL_I2C_CLEAR_ADDRFLAG(&I2cHandle);

    for (count = 0; count < length; count++) {
        if (i2c_master_byte_write(data[count]) != 1) {
            return 3;
        }
    }

    // If not repeated start, send stop.
    if (stop) {
        i2c_master_stop();
    }

    return 0;
}

int TwoWire::i2c_master_byte_read(int *value, int last)
{
  I2C_TypeDef *i2c = (I2C_TypeDef *)I2cHandle.Instance;
    int timeout;

    if (last) {
        // Don't acknowledge the last byte
        i2c->CR1 &= ~I2C_CR1_ACK;
    } else {
        // Acknowledge the byte
        i2c->CR1 |= I2C_CR1_ACK;
    }

    // Wait until the byte is received
    timeout = FLAG_TIMEOUT;
    while (__HAL_I2C_GET_FLAG(&I2cHandle, I2C_FLAG_RXNE) == RESET) {
        if ((timeout--) == 0) {
            return -1;
        }
    }

    *value = (int)i2c->DR;

    return 0;
}

int TwoWire::i2c_master_byte_write(int data)
{
  I2C_TypeDef *i2c = (I2C_TypeDef *)I2cHandle.Instance;
    int timeout;

    i2c->DR = (uint8_t)data;

    // Wait until the byte is transmitted
    timeout = FLAG_TIMEOUT;
    while ((__HAL_I2C_GET_FLAG(&I2cHandle, I2C_FLAG_TXE) == RESET) &&
            (__HAL_I2C_GET_FLAG(&I2cHandle, I2C_FLAG_BTF) == RESET)) {
        if ((timeout--) == 0) {
            return 0;
        }
    }

    return 1;
}

int TwoWire::i2c_slave_write(const char *data, int length)
{
    uint32_t Timeout;
    int size = 0;

    I2C_TypeDef *i2c = (I2C_TypeDef *)I2cHandle.Instance;

    while (length > 0) {
        /* Wait until TXE flag is set */
        Timeout = FLAG_TIMEOUT;
        while (__HAL_I2C_GET_FLAG(&I2cHandle, I2C_FLAG_TXE) == RESET) {
            Timeout--;
            if (Timeout == 0) {
                return -1;
            }
        }

        /* Write data to DR */
        i2c->DR = (*data++);
        length--;
        size++;

        if ((__HAL_I2C_GET_FLAG(&I2cHandle, I2C_FLAG_BTF) == SET) && (length != 0)) {
            /* Write data to DR */
            i2c->DR = (*data++);
            length--;
            size++;
        }
    }

    /* Wait until AF flag is set */
    Timeout = FLAG_TIMEOUT;
    while (__HAL_I2C_GET_FLAG(&I2cHandle, I2C_FLAG_AF) == RESET) {
        Timeout--;
        if (Timeout == 0) {
            return -1;
        }
    }

    /* Clear AF flag */
    __HAL_I2C_CLEAR_FLAG(&I2cHandle, I2C_FLAG_AF);

    /* Wait until BUSY flag is reset */
    Timeout = FLAG_TIMEOUT;
    while (__HAL_I2C_GET_FLAG(&I2cHandle, I2C_FLAG_BUSY) == SET) {
        Timeout--;
        if (Timeout == 0) {
            return -1;
        }
    }

    I2cHandle.State = HAL_I2C_STATE_READY;

    /* Process Unlocked */
    __HAL_UNLOCK(&I2cHandle);

    return size;
}

void TwoWire::handleInterrupt(uint8_t TransferDirection, uint16_t AddrMatchCode)
{
    if(AddrMatchCode == defaultAddress)
    {
      /* First of all, check the transfer direction to call the correct Slave Interface */
      if(TransferDirection == I2C_DIRECTION_TRANSMIT)
      {
        // don't bother if user hasn't registered a callback
        if(!user_onReceive){
          return;
        }

        HAL_I2C_Slave_Sequential_Receive_IT(&I2cHandle, &(rxBuffer[rxBufferLength]), 1, I2C_FIRST_FRAME);
      }
      else
      {
        // don't bother if user hasn't registered a callback
        if(!user_onRequest){
          return;
        }
        // reset tx buffer iterator vars
        // !!! this will kill any pending pre-master sendTo() activity
        txBufferIndex = 0;
        txBufferLength = 0;

        // alert user program
        user_onRequest();
      }
    }
}

void TwoWire::enableInterrupt(void)
{
    if(I2cHandle.Instance == HAL_I2C3)
    {
      HAL_NVIC_EnableIRQ(I2C3_ER_IRQn);
      HAL_NVIC_EnableIRQ(I2C3_EV_IRQn);
    }
    else if(I2cHandle.Instance == HAL_I2C2)
    {
      HAL_NVIC_EnableIRQ(I2C2_ER_IRQn);
      HAL_NVIC_EnableIRQ(I2C2_EV_IRQn);
    }
    else if (I2cHandle.Instance == HAL_I2C1)
    {
      HAL_NVIC_EnableIRQ(I2C1_ER_IRQn);
      HAL_NVIC_EnableIRQ(I2C1_EV_IRQn);
    } else
    {
      // Do Nothing
    }
}

void TwoWire::disableInterrupt(void)
{
    if(I2cHandle.Instance == HAL_I2C3)
    {
      HAL_NVIC_DisableIRQ(I2C3_ER_IRQn);
      HAL_NVIC_DisableIRQ(I2C3_EV_IRQn);
    }
    else if(I2cHandle.Instance == HAL_I2C2)
    {
      HAL_NVIC_DisableIRQ(I2C2_ER_IRQn);
      HAL_NVIC_DisableIRQ(I2C2_EV_IRQn);
    }
    else if (I2cHandle.Instance == HAL_I2C1)
    {
      HAL_NVIC_DisableIRQ(I2C1_ER_IRQn);
      HAL_NVIC_DisableIRQ(I2C1_EV_IRQn);
    } else
    {
      // Do Nothing
    }
}

#ifdef __cplusplus
extern "C" {
#endif

void __irq_i2c1_ev(void)
{
  //while(1)
  //{
  //}
  HAL_I2C_EV_IRQHandler(&(Wire.I2cHandle));
}

void __irq_i2c1_er(void)
{
  HAL_I2C_ER_IRQHandler(&(Wire.I2cHandle));
}

void __irq_i2c2_ev(void)
{
  HAL_I2C_EV_IRQHandler(&(Wire1.I2cHandle));
}

void __irq_i2c2_er(void)
{
  HAL_I2C_ER_IRQHandler(&(Wire1.I2cHandle));
}

void __irq_I2C3_EV_IRQHandler(void)
{
  HAL_I2C_EV_IRQHandler(&(Wire2.I2cHandle));
}

void __irq_I2C3_ER_IRQHandler(void)
{
  HAL_I2C_ER_IRQHandler(&(Wire2.I2cHandle));
}

void HAL_I2C_AddrCallback(I2C_HandleTypeDef *hi2c, uint8_t TransferDirection, uint16_t AddrMatchCode)
{
  if(hi2c->Instance == HAL_I2C1)
  {
    Wire.handleInterrupt(TransferDirection, AddrMatchCode);
  } else if (hi2c->Instance == HAL_I2C2)
  {
    Wire1.handleInterrupt(TransferDirection, AddrMatchCode);
  } else if (hi2c->Instance == HAL_I2C3)
  {
    Wire2.handleInterrupt(TransferDirection, AddrMatchCode);
  } else
  {
    // Do nothing, but it is strange if you enter here
  }
}


void HAL_I2C_SlaveRxCpltCallback(I2C_HandleTypeDef *hi2c)
{
  if(hi2c->Instance == HAL_I2C3)
  {
    Wire2.rxBufferLength++;
    HAL_I2C_Slave_Sequential_Receive_IT(&(Wire2.I2cHandle), &(Wire2.rxBuffer[Wire2.rxBufferLength]), 1, I2C_FIRST_FRAME);
  }
  else if(hi2c->Instance == HAL_I2C2)
  {
    Wire1.rxBufferLength++;
    HAL_I2C_Slave_Sequential_Receive_IT(&(Wire1.I2cHandle), &(Wire1.rxBuffer[Wire1.rxBufferLength]), 1, I2C_FIRST_FRAME);
  }
  else if (hi2c->Instance == HAL_I2C1)
  {
    Wire.rxBufferLength++;
    HAL_I2C_Slave_Sequential_Receive_IT(&(Wire.I2cHandle), &(Wire.rxBuffer[Wire.rxBufferLength]), 1, I2C_FIRST_FRAME);
  } else
  {
    // Do Nothing
  }
}

void HAL_I2C_ListenCpltCallback(I2C_HandleTypeDef *hi2c)
{
  if(hi2c->Instance == HAL_I2C3)
  {
    Wire2.rxBufferIndex = 0;
    Wire2.user_onReceive(Wire2.rxBufferLength);
    Wire2.rxBufferIndex = 0;
    Wire2.rxBufferLength = 0;
    HAL_I2C_EnableListen_IT(&(Wire2.I2cHandle));
  }
  else if(hi2c->Instance == HAL_I2C2)
  {
    Wire1.rxBufferIndex = 0;
    Wire1.user_onReceive(Wire1.rxBufferLength);
    Wire1.rxBufferIndex = 0;
    Wire1.rxBufferLength = 0;
  HAL_I2C_EnableListen_IT(&(Wire1.I2cHandle));
  }
  else if (hi2c->Instance == HAL_I2C1)
  {
    Wire.rxBufferIndex = 0;
    Wire.user_onReceive(Wire.rxBufferLength);
    Wire.rxBufferIndex = 0;
    Wire.rxBufferLength = 0;
  HAL_I2C_EnableListen_IT(&(Wire.I2cHandle));
  } else
  {
      // Do Nothing
  }
}


#ifdef __cplusplus
}
#endif

// Preinstantiate Objects //////////////////////////////////////////////////////

TwoWire Wire  = TwoWire(HAL_I2C1);
TwoWire Wire1 = TwoWire(HAL_I2C2);
TwoWire Wire2 = TwoWire(HAL_I2C3);
