

#include "irmplog.h"

/*---------------------------------------------------------------------------------------------------------------------------------------------------
 *  Logging
 *---------------------------------------------------------------------------------------------------------------------------------------------------
 */
#if IRMP_LOGGING == 1                                                   // logging via UART

 /*---------------------------------------------------------------------------------------------------------------------------------------------------
  *  Initialize  UART
  *  @details  Initializes UART
  *---------------------------------------------------------------------------------------------------------------------------------------------------
  */
void
irmp_uart_init(void)
{
#ifndef UNIX_OR_WINDOWS
#if defined(ARM_STM32F4XX)
  GPIO_InitTypeDef GPIO_InitStructure;
  USART_InitTypeDef USART_InitStructure;

  // Clock enable vom TX Pin
  RCC_AHB1PeriphClockCmd(STM32_GPIO_CLOCK, ENABLE);

  // Clock enable der UART
  RCC_APB1PeriphClockCmd(STM32_UART_CLOCK, ENABLE);

  // UART Alternative-Funktion mit dem IO-Pin verbinden
  GPIO_PinAFConfig(STM32_GPIO_PORT, STM32_GPIO_SOURCE, STM32_UART_AF);

  // UART als Alternative-Funktion mit PushPull
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;

  // TX-Pin
  GPIO_InitStructure.GPIO_Pin = STM32_GPIO_PIN;
  GPIO_Init(STM32_GPIO_PORT, &GPIO_InitStructure);

  // Oversampling
  USART_OverSampling8Cmd(STM32_UART_COM, ENABLE);

  // init baud rate, 8 data bits, 1 stop bit, no parity, no RTS+CTS
  USART_InitStructure.USART_BaudRate = STM32_UART_BAUD;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Tx;
  USART_Init(STM32_UART_COM, &USART_InitStructure);

  // UART enable
  USART_Cmd(STM32_UART_COM, ENABLE);

#elif defined(ARM_STM32F10X)
  GPIO_InitTypeDef GPIO_InitStructure;
  USART_InitTypeDef USART_InitStructure;

  // Clock enable vom TX Pin
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); // UART3 an PB10

  // Clock enable der UART
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);

  // UART als Alternative-Funktion mit PushPull
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

  // TX-Pin
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
  GPIO_Init(GPIOB, &GPIO_InitStructure);

  // Oversampling
  USART_OverSampling8Cmd(STM32_UART_COM, ENABLE);

  // init baud rate, 8 data bits, 1 stop bit, no parity, no RTS+CTS
  USART_InitStructure.USART_BaudRate = 115200;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Tx;
  USART_Init(STM32_UART_COM, &USART_InitStructure);

  // UART enable
  USART_Cmd(STM32_UART_COM, ENABLE);

#elif defined(ARDUINO)
  // we use the Arduino Serial Imlementation
  // you have to call Serial.begin(SER_BAUD); in Arduino setup() function

#elif defined (__AVR_XMEGA__)

  PMIC.CTRL |= PMIC_HILVLEN_bm;

  USARTC1.BAUDCTRLB = 0;
  USARTC1.BAUDCTRLA = F_CPU / 153600 - 1;
  USARTC1.CTRLA = USART_RXCINTLVL_HI_gc;                                                          // high INT level (receive)
  USARTC1.CTRLB = USART_TXEN_bm | USART_RXEN_bm;                                                  // activated RX and TX
  USARTC1.CTRLC = USART_CHSIZE_8BIT_gc;                                                           // 8 Bit
  PORTC.DIR |= (1 << 7);                                                                            // TXD is output
  PORTC.DIR &= ~(1 << 6);

#elif defined (_CHIBIOS_HAL_)
  // we use the SD interface for logging, no need to init that here

#else

#if (IRMP_EXT_LOGGING == 0)                                                                         // use UART
  UART0_UBRRH = UBRRH_VALUE;                                                                      // set baud rate
  UART0_UBRRL = UBRRL_VALUE;

#if USE_2X
  UART0_UCSRA |= (1 << UART0_U2X);
#else
  UART0_UCSRA &= ~(1 << UART0_U2X);
#endif

  UART0_UCSRC = UART0_UCSZ1_BIT_VALUE | UART0_UCSZ0_BIT_VALUE | UART0_URSEL_BIT_VALUE;
  UART0_UCSRB |= UART0_TXEN_BIT_VALUE;                                                            // enable UART TX
#else                                                                                               // other log method
  initextlog();
#endif //IRMP_EXT_LOGGING
#endif //ARM_STM32F4XX
#endif // UNIX_OR_WINDOWS
}

/*---------------------------------------------------------------------------------------------------------------------------------------------------
 *  Send character
 *  @details  Sends character
 *  @param    ch character to be transmitted
 *---------------------------------------------------------------------------------------------------------------------------------------------------
 */
void
irmp_uart_putc(unsigned char ch)
{
#ifndef UNIX_OR_WINDOWS
#if defined(ARM_STM32F4XX) || defined(ARM_STM32F10X)
  // warten bis altes Byte gesendet wurde
  while (USART_GetFlagStatus(STM32_UART_COM, USART_FLAG_TXE) == RESET)
  {
    ;
  }

  USART_SendData(STM32_UART_COM, ch);

  if (ch == '\n')
  {
    while (USART_GetFlagStatus(STM32_UART_COM, USART_FLAG_TXE) == RESET);
    USART_SendData(STM32_UART_COM, '\r');
  }

#elif defined(ARDUINO)
  // we use the Arduino Serial Imlementation
  usb_serial_putchar(ch);

#elif defined(_CHIBIOS_HAL_)
  // use the SD interface from HAL, log to IRMP_LOGGING_SD which is defined in irmpconfig.h
  sdWriteI(&IRMP_LOGGING_SD, &ch, 1);      // we are called from interrupt context, so use the ...I version of the function

#else
#if (IRMP_EXT_LOGGING == 0)

#  if defined (__AVR_XMEGA__)
  while (!(USARTC1.STATUS & USART_DREIF_bm))
  {
    ;
  }

  USARTC1.DATA = ch;

#  else // AVR_MEGA
  while (!(UART0_UCSRA & UART0_UDRE_BIT_VALUE))
  {
    ;
  }

  UART0_UDR = ch;

#  endif // __AVR_XMEGA__

#else

  sendextlog(ch);                                                         // use external log

#endif // IRMP_EXT_LOGGING
#endif // ARM_STM32F4XX
#else
  fputc(ch, stderr);
#endif // UNIX_OR_WINDOWS
}

/*---------------------------------------------------------------------------------------------------------------------------------------------------
 *  Log IR signal
 *---------------------------------------------------------------------------------------------------------------------------------------------------
 */

void irmp_log(uint_fast8_t val)
{
  static uint8_t          buf[DATALEN];                                   // logging buffer
  static uint_fast16_t    buf_idx;                                        // index
  static uint_fast8_t     startcycles;                                    // current number of start-zeros
  static uint_fast16_t    cnt;                                            // counts sequenced highbits - to detect end
  static uint_fast8_t     last_val = 1;

  if (!val && (startcycles < STARTCYCLES) && !buf_idx)                   // prevent that single random zeros init logging
  {
    startcycles++;
  }
  else
  {
    startcycles = 0;

    if (!val || buf_idx != 0)                                          // start or continue logging on "0", "1" cannot init logging
    {
      if (last_val == val)
      {
        cnt++;

        if (val && cnt > ENDBITS)                                   // if high received then look at log-stop condition
        {                                                           // if stop condition is true, output on uart
          uint_fast8_t     i8;
          uint_fast16_t    i;
          uint_fast16_t    j;
          uint_fast8_t     v = '1';
          uint_fast16_t    d;

          for (i8 = 0; i8 < STARTCYCLES; i8++)
          {
            irmp_uart_putc('0');                               // the ignored starting zeros
          }

          for (i = 0; i < buf_idx; i++)
          {
            d = buf[i];

            if (d == 0xff)
            {
              i++;
              d = buf[i];
              i++;
              d |= ((uint_fast16_t)buf[i] << 8);
            }

            for (j = 0; j < d; j++)
            {
              irmp_uart_putc(v);
            }

            v = (v == '1') ? '0' : '1';
          }

          for (i8 = 0; i8 < 20; i8++)
          {
            irmp_uart_putc('1');
          }

          irmp_uart_putc('\n');
          buf_idx = 0;
          last_val = 1;
          cnt = 0;
        }
      }
      else if (buf_idx < DATALEN - 3)
      {
        if (cnt >= 0xff)
        {
          buf[buf_idx++] = 0xff;
          buf[buf_idx++] = (cnt & 0xff);
          buf[buf_idx] = (cnt >> 8);
        }
        else
        {
          buf[buf_idx] = cnt;
        }

        buf_idx++;
        cnt = 1;
        last_val = val;
      }
    }
  }
}

#endif //IRMP_LOGGING


