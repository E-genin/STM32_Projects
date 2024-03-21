

#include "main.h"
#include "Timer.h"

int main(void)
{

  McuInit();

  LED1_Configure();

  Init_Timer6();


  while (1)
  {

	  for(uint16_t i=0; i<1000; i++)

	  delay_1ms();

	  LED1_Toggle();

  }
  /* USER CODE END 3 */
}
