/**
  ******************************************************************************
  * @file    main.c
  * @author  Ac6
  * @version V1.0
  * @date    01-December-2013
  * @brief   Default main function.
  ******************************************************************************
*/


#include "stm32f4xx.h"
#include "stm32f4_discovery.h"
#include "defines.h"
#include "tm_stm32f4_delay.h"
#include "tm_stm32f4_hd44780.h"
#include <ctype.h>


/* czesc od blutuf */

char a;
void USART3_IRQHandler(void)
{
	// sprawdzenie flagi zwiazanej z odebraniem danych przez USART
	if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)
	{
		USART3->DR;

		if(USART3->DR=='1'){
			GPIO_ToggleBits(GPIOD, GPIO_Pin_12);
			TM_HD44780_Clear();
			TM_HD44780_Puts(0, 0, "Bambosz to pedal");
		}
		if(USART3->DR=='2'){
			TM_HD44780_Clear();
			TM_HD44780_Puts(0, 0, "Hehehehe");
			GPIO_ToggleBits(GPIOD, GPIO_Pin_13);

		}
		if(USART3->DR=='3'){
			TM_HD44780_Clear();
			TM_HD44780_Puts(0, 0, "Zarcik :)");
			GPIO_ToggleBits(GPIOD, GPIO_Pin_14);

		}

		if(USART3->DR=='4'){
			GPIO_ToggleBits(GPIOD, GPIO_Pin_15);
			TM_HD44780_Clear();
			TM_HD44780_Puts(0, 0, "Artur to najle");
			TM_HD44780_Puts(0, 1, "pszy programista");

		}
	}
}

/*blutuf*/
int main(void) {



	/* czesc od blutuf */
	// wlaczenie taktowania wybranego portu
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
		// wlaczenie taktowania wybranego uk豉du USART
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);

		TIM_ClearITPendingBit(TIM5, TIM_IT_Update);
		// zezwolenie na przerwania od przepe軟ienia dla timera 3
		TIM_ITConfig(TIM5, TIM_IT_Update, ENABLE);
		TIM_Cmd(TIM5, ENABLE);

		GPIO_InitTypeDef  GPIO_InitStructure;
		/* Configure PD12, PD13, PD14 and PD15 in output pushpull mode */
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13| GPIO_Pin_14| GPIO_Pin_15;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOD, &GPIO_InitStructure);
		// konfiguracja linii Rx i Tx
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;

		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOC, &GPIO_InitStructure);

		/* przyciski */
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2| GPIO_Pin_3;
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN; //wejscie
			GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
			GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
		GPIO_Init(GPIOA, &GPIO_InitStructure);
		/*przyciski */
		// ustawienie funkcji alternatywnej dla pin闚 (USART)
		GPIO_PinAFConfig(GPIOC, GPIO_PinSource10, GPIO_AF_USART3);
		GPIO_PinAFConfig(GPIOC, GPIO_PinSource11, GPIO_AF_USART3);

		USART_InitTypeDef USART_InitStructure;
		// predkosc transmisji (mozliwe standardowe opcje: 9600, 19200, 38400, 57600, 115200, ...)
		USART_InitStructure.USART_BaudRate = 9600;
		// d逝go s這wa (USART_WordLength_8b lub USART_WordLength_9b)
		USART_InitStructure.USART_WordLength = USART_WordLength_8b;
		// liczba bit闚 stopu (USART_StopBits_1, USART_StopBits_0_5, USART_StopBits_2, USART_StopBits_1_5)
		USART_InitStructure.USART_StopBits = USART_StopBits_1;
		// sprawdzanie parzystoi (USART_Parity_No, USART_Parity_Even, USART_Parity_Odd)
		USART_InitStructure.USART_Parity = USART_Parity_No;
		// sprz皻owa kontrola przep造wu (USART_HardwareFlowControl_None, USART_HardwareFlowControl_RTS, USART_HardwareFlowControl_CTS, USART_HardwareFlowControl_RTS_CTS)
		USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
		// tryb nadawania/odbierania (USART_Mode_Rx, USART_Mode_Rx )
		USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

		// konfiguracja
		USART_Init(USART3, &USART_InitStructure);

		// wlaczenie ukladu USART
		USART_Cmd(USART3, ENABLE);


		//struktura do konfiguracji kontrolera NVIC
		NVIC_InitTypeDef NVIC_InitStructure;
		// wlaczenie przerwania zwi頊anego z odebraniem danych (pozostale zrodla przerwan zdefiniowane sa w pliku stm32f4xx_usart.h)
		USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);
		NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;

		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		// konfiguracja kontrolera przerwan
		NVIC_Init(&NVIC_InitStructure);
		// wlaczenie przerwan od ukladu USART
		NVIC_EnableIRQ(USART3_IRQn);

		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);

	/*blutuf*/


    //Rectangle for custom character
    //xxx means doesn't care, lower 5 bits are important for LCD
    uint8_t customChar[] = {
        0x1F,    // xxx 11111
        0x11,    // xxx 10001
        0x11,    // xxx 10001
        0x11,    // xxx 10001
        0x11,    // xxx 10001
        0x11,    // xxx 10001
        0x11,    // xxx 10001
        0x1F    // xxx 11111
    };
    //Initialize system
    SystemInit();

    //Initialize LCD 20 cols x 4 rows
    TM_HD44780_Init(20, 4);

    //Save custom character on location 0 in LCD
    TM_HD44780_CreateChar(0, &customChar[0]);

    //Put string to LCD
    TM_HD44780_Puts(0, 0, "STM32F4/29 Discovery");
    TM_HD44780_Puts(2, 1, "20x4 HD44780 LCD");
    TM_HD44780_Puts(0, 2, "stm32f429-\n\r       discovery.com");

    //Wait a little
    Delayms(3000);

    //Clear LCD
    //TM_HD44780_Clear();

    //Show cursor
    TM_HD44780_CursorOn();

    //Write new text
    TM_HD44780_Puts(6, 2, "CLEARED!");

    //Wait a little
    Delayms(1000);

    //Enable cursor blinking
    TM_HD44780_BlinkOn();

    //Show custom character at x = 1, y = 2 from RAM location 0
    TM_HD44780_PutCustom(1, 2, 0);



    while(1) {
    	if(!GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_1))
    			{
    				GPIO_SetBits(GPIOD, GPIO_Pin_12);
    			}
    			else
    			{
    				GPIO_ResetBits(GPIOD, GPIO_Pin_12);
    			}
    			if(!GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_2))
    			{
    				GPIO_SetBits(GPIOD, GPIO_Pin_13);
    			}
    			else
    			{
    				GPIO_ResetBits(GPIOD, GPIO_Pin_13);
    	}

    }
}
