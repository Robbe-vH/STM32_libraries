#ifndef _TM1638_H
#define _TM1638_H

#include "stm32l4xx_hal.h"

typedef enum {
  PULSE1_16,
  PULSE2_16,
  PULSE4_16,
  PULSE10_16,
  PULSE11_16,
  PULSE12_16,
  PULSE13_16,
  PULSE14_16
} pulse_t;

typedef enum {
  S1, S2, S3, S4,
  S5, S6, S7, S8
} button_t;

class TM1638 {
private:
  #define INSTRUCTION_WRITE_DATA 0x40
  #define INSTRUCTION_READ_KEY 0x42
  #define INSTRUCTION_ADDRESS_AUTO 0x40
  #define INSTRUCTION_ADDRESS_FIXED 0x44
  #define INSTRUCTION_NORMAL_MODE 0x40
  #define INSTRUCTION_TEST_MODE 0x48

  #define FIRST_DISPLAY_ADDRESS 0xC0

  #define DISPLAY_TURN_OFF 0x80
  #define DISPLAY_TURN_ON 0x88

  uint8_t _digits[16] = {
    0b00111111, 0b00000110, 0b01011011, 0b01001111,
    0b01100110, 0b01101101, 0b01111101, 0b00000111,
    0b01111111, 0b01101111, 0b01110111, 0b01111100,
    0b00111001, 0b01011110, 0b01111001, 0b01110001
  };

  GPIO_TypeDef* _clk_port;
  uint16_t _clk_pin;
  GPIO_TypeDef* _stb_port;
  uint16_t _stb_pin;
  GPIO_TypeDef* _dio_port;
  uint16_t _dio_pin;
  uint8_t _buttons;
  pulse_t _pulse;
  bool _isOn;

public:
  TM1638(GPIO_TypeDef* clk_port, uint16_t clk_pin, GPIO_TypeDef* dio_port, uint16_t dio_pin, GPIO_TypeDef* stb_port, uint16_t stb_pin) {
    _clk_port = clk_port;
    _clk_pin = clk_pin;
    _stb_port = stb_port;
    _stb_pin = stb_pin;
    _dio_port = dio_port;
    _dio_pin = dio_pin;
    _pulse = PULSE1_16;
    _isOn = false;

    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;

    GPIO_InitStruct.Pin = _clk_pin;
    HAL_GPIO_Init(_clk_port, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = _stb_pin;
    HAL_GPIO_Init(_stb_port, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = _dio_pin;
    HAL_GPIO_Init(_dio_port, &GPIO_InitStruct);

    HAL_GPIO_WritePin(_stb_port, _stb_pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(_clk_port, _clk_pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(_dio_port, _dio_pin, GPIO_PIN_SET);
  }

  bool getButton(button_t s);
  uint8_t getButtons();
  void writeLed(uint8_t num, bool state);
  void writeLeds(uint8_t val);
  void displayVal(uint8_t digitId, uint8_t val);
  void displayDig(uint8_t digitId, uint8_t pgfedcba);
  void displayClear();
  void displayTurnOff();
  void displayTurnOn();
  void displaySetBrightness(pulse_t pulse);
  void reset();
  void test();

private:
  void writeData(uint8_t data);
  void writeDataAt(uint8_t displayAddress, uint8_t data);
  void setDisplayMode(uint8_t displayMode);
  void setDataInstruction(uint8_t dataInstruction);
};

#endif
