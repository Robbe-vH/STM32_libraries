int main(void){ 

TM1638_Handler_t tm1638Handler;
  TM1638_Platform_Init(&tm1638Handler);

  TM1638_Init(&tm1638Handler, TM1638DisplayTypeComCathode);
  TM1638_ConfigDisplay(&tm1638Handler, 3, TM1638DisplayStateON);

  uint8_t const _digits[10] = {
    0b00111111,  // Digit 0
    0b00000110,  // Digit 1
    0b01011011,  // Digit 2
    0b01001111,  // Digit 3
    0b01100110,  // Digit 4
    0b01101101,  // Digit 5
    0b01111101,  // Digit 6
    0b00000111,  // Digit 7
    0b01111111,  // Digit 8
    0b01101111   // Digit 9
  };
  
  while (1)
  {
    // Displays 2 on the first segment
	  TM1638_SetMultipleDigit(&tm1638Handler, &_digits[2], 0, 1);

  }
}
