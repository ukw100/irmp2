

#ifndef IRMPLOG_H
#define IRMPLOG_H


#ifdef __cplusplus
extern "C"
{
#endif



/*---------------------------------------------------------------------------------------------------------------------------------------------------
 *  Logging
 *---------------------------------------------------------------------------------------------------------------------------------------------------
 */
#if IRMP_LOGGING == 1                                                   // logging via UART

#if defined(ARM_STM32F4XX)
#  define  STM32_GPIO_CLOCK   RCC_AHB1Periph_GPIOA                      // UART2 on PA2
#  define  STM32_UART_CLOCK   RCC_APB1Periph_USART2
#  define  STM32_GPIO_PORT    GPIOA
#  define  STM32_GPIO_PIN     GPIO_Pin_2
#  define  STM32_GPIO_SOURCE  GPIO_PinSource2
#  define  STM32_UART_AF      GPIO_AF_USART2
#  define  STM32_UART_COM     USART2
#  define  STM32_UART_BAUD    115200                                    // 115200 Baud
#  include "stm32f4xx_usart.h"
#elif defined(ARM_STM32F10X)
#  define  STM32_UART_COM     USART3                                    // UART3 on PB10
#elif defined(ARDUINO)                                                  // Arduino Serial implementation
#  if defined(USB_SERIAL)
#    include "usb_serial.h"
#  else
#    error USB_SERIAL not defined in ARDUINO Environment
#  endif
#elif defined(_CHIBIOS_HAL_)                                            // ChibiOS HAL
#  if IRMP_EXT_LOGGING == 1
#    error IRMP_EXT_LOGGING not implemented for ChibiOS HAL, use regular logging instead
#  endif
#else
#  if IRMP_EXT_LOGGING == 1                                             // use external logging
#    include "irmpextlog.h"
#  else                                                                 // normal UART log (IRMP_EXT_LOGGING == 0)
#    define BAUD                                    9600L
#  ifndef UNIX_OR_WINDOWS
#    include <util/setbaud.h>
#  endif

#ifdef UBRR0H

#define UART0_UBRRH                             UBRR0H
#define UART0_UBRRL                             UBRR0L
#define UART0_UCSRA                             UCSR0A
#define UART0_UCSRB                             UCSR0B
#define UART0_UCSRC                             UCSR0C
#define UART0_UDRE_BIT_VALUE                    (1<<UDRE0)
#define UART0_UCSZ1_BIT_VALUE                   (1<<UCSZ01)
#define UART0_UCSZ0_BIT_VALUE                   (1<<UCSZ00)
#ifdef URSEL0
#define UART0_URSEL_BIT_VALUE                   (1<<URSEL0)
#else
#define UART0_URSEL_BIT_VALUE                   (0)
#endif
#define UART0_TXEN_BIT_VALUE                    (1<<TXEN0)
#define UART0_UDR                               UDR0
#define UART0_U2X                               U2X0

#else

#define UART0_UBRRH                             UBRRH
#define UART0_UBRRL                             UBRRL
#define UART0_UCSRA                             UCSRA
#define UART0_UCSRB                             UCSRB
#define UART0_UCSRC                             UCSRC
#define UART0_UDRE_BIT_VALUE                    (1<<UDRE)
#define UART0_UCSZ1_BIT_VALUE                   (1<<UCSZ1)
#define UART0_UCSZ0_BIT_VALUE                   (1<<UCSZ0)
#ifdef URSEL
#define UART0_URSEL_BIT_VALUE                   (1<<URSEL)
#else
#define UART0_URSEL_BIT_VALUE                   (0)
#endif
#define UART0_TXEN_BIT_VALUE                    (1<<TXEN)
#define UART0_UDR                               UDR
#define UART0_U2X                               U2X

#endif //UBRR0H
#endif //IRMP_EXT_LOGGING
#endif //ARM_STM32F4XX

 /*---------------------------------------------------------------------------------------------------------------------------------------------------
  *  Initialize  UART
  *  @details  Initializes UART
  *---------------------------------------------------------------------------------------------------------------------------------------------------
  */
void
irmp_uart_init(void);


/*---------------------------------------------------------------------------------------------------------------------------------------------------
 *  Log IR signal
 *---------------------------------------------------------------------------------------------------------------------------------------------------
 */

#define STARTCYCLES                       2                                 // min count of zeros before start of logging
#define ENDBITS                        1000                                 // number of sequenced highbits to detect end
#define DATALEN                         700                                 // log buffer size

void
irmp_log(uint_fast8_t val);

#else
#define irmp_log(val)
#endif //IRMP_LOGGING

#ifdef __cplusplus
}
#endif

#endif


