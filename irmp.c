/*---------------------------------------------------------------------------------------------------------------------------------------------------
 * irmp.c - infrared multi-protocol decoder, supports several remote control protocols
 *
 * Copyright (c) 2009-2019 Frank Meyer - frank(at)fli4l.de
 *
 * Supported AVR mikrocontrollers:
 *
 * ATtiny87,  ATtiny167
 * ATtiny45,  ATtiny85
 * ATtiny44,  ATtiny84
 * ATmega8,   ATmega16,  ATmega32
 * ATmega162
 * ATmega164, ATmega324, ATmega644,  ATmega644P, ATmega1284, ATmega1284P
 * ATmega88,  ATmega88P, ATmega168,  ATmega168P, ATmega328P
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *---------------------------------------------------------------------------------------------------------------------------------------------------
 */

#include "irmp.h"
#include "irmpcalculatedconstants.h"
#include "irmplog.h"
#include "irmpprotocolparams.h"


#ifdef ANALYZE
/*    not every PIC compiler knows variadic macros :-( */
#  define ANALYZE_PUTCHAR(a)                         { if (! silent)             { putchar (a);          } }
#  define ANALYZE_ONLY_NORMAL_PUTCHAR(a)             { if (! silent && !verbose) { putchar (a);          } }
#  define ANALYZE_PRINT(text)                        { if (verbose)              { printf (text);        } }
#  define ANALYZE_PRINTF_1(text, a1)                              { if (verbose)               { printf (text, (a1));  } }
#  define ANALYZE_PRINTF_2(text, a1, a2)                          { if (verbose)               { printf (text, (a1), (a2));  } }
#  define ANALYZE_PRINTF_3(text, a1, a2, a3)                      { if (verbose)               { printf (text, (a1), (a2), (a3));  } }
#  define ANALYZE_PRINTF_4(text, a1, a2, a3, a4)                  { if (verbose)               { printf (text, (a1), (a2), (a3), (a4));  } }
#  define ANALYZE_ONLY_NORMAL_PRINT(text)                         { if (! silent && !verbose)  { printf (text);        } }
#  define ANALYZE_ONLY_NORMAL_PRINTF_1(text, a1)                  { if (! silent && !verbose)  { printf (text, (a1));  } }
#  define ANALYZE_ONLY_NORMAL_PRINTF_2(text, a1, a2)              { if (! silent && !verbose)  { printf (text, (a1), (a2));  } }
#  define ANALYZE_ONLY_NORMAL_PRINTF_3(text, a1, a2, a3)          { if (! silent && !verbose)  { printf (text, (a1), (a2), (a3));  } }
#  define ANALYZE_ONLY_NORMAL_PRINTF_4(text, a1, a2, a3, a4)      { if (! silent && !verbose)  { printf (text, (a1), (a2), (a3), (a4));  } }
#  define ANALYZE_NEWLINE()                          { if (verbose)              { putchar ('\n');       } }
static int                                           silent;
static int                                           time_counter;
static int                                           verbose;

#else
#  define ANALYZE_PUTCHAR(a)                         
#  define ANALYZE_ONLY_NORMAL_PUTCHAR(a)             
#  define ANALYZE_PRINT(text)                        
#  define ANALYZE_PRINTF_1(text, a1)                              
#  define ANALYZE_PRINTF_2(text, a1, a2)                          
#  define ANALYZE_PRINTF_3(text, a1, a2, a3)                      
#  define ANALYZE_PRINTF_4(text, a1, a2, a3, a4)                  
#  define ANALYZE_ONLY_NORMAL_PRINT(text)                         
#  define ANALYZE_ONLY_NORMAL_PRINTF_1(text, a1)                  
#  define ANALYZE_ONLY_NORMAL_PRINTF_2(text, a1, a2)              
#  define ANALYZE_ONLY_NORMAL_PRINTF_3(text, a1, a2, a3)          
#  define ANALYZE_ONLY_NORMAL_PRINTF_4(text, a1, a2, a3, a4)      
#  define ANALYZE_NEWLINE()

#endif

#if IRMP_USE_CALLBACK == 1
static void                                     (*irmp_callback_ptr) (uint_fast8_t);
#endif // IRMP_USE_CALLBACK == 1

#define PARITY_CHECK_OK                         1
#define PARITY_CHECK_FAILED                     0


static uint_fast8_t                             irmp_bit;                   // current bit position
static IRMP_PARAMETER                           irmp_param;

#if IRMP_SUPPORT_RC5_PROTOCOL == 1 && (IRMP_SUPPORT_FDC_PROTOCOL == 1 || IRMP_SUPPORT_RCCAR_PROTOCOL == 1)
static IRMP_PARAMETER                           irmp_param2;
#endif

static volatile uint_fast8_t                    irmp_ir_detected = FALSE;
static volatile uint_fast8_t                    irmp_protocol;
static volatile uint_fast16_t                   irmp_address;
#if IRMP_32_BIT == 1
static volatile uint_fast32_t                   irmp_command;
#else
static volatile uint_fast16_t                   irmp_command;
#endif
static volatile uint_fast16_t                   irmp_id;                // only used for SAMSUNG protocol
static volatile uint_fast8_t                    irmp_flags;
// static volatile uint_fast8_t                 irmp_busy_flag;

#if defined(__MBED__)
// DigitalIn inputPin(IRMP_PIN, PullUp);                                // this requires mbed.h and source to be compiled as cpp
gpio_t                                          gpioIRin;               // use low level c function instead
#endif


#ifdef ANALYZE
#define input(x)                                (x)
static uint_fast8_t                             IRMP_PIN;
static uint_fast8_t                             radio;
#endif

/*---------------------------------------------------------------------------------------------------------------------------------------------------
 *  Initialize IRMP decoder
 *  @details  Configures IRMP input pin
 *---------------------------------------------------------------------------------------------------------------------------------------------------
 */
#ifndef ANALYZE
void
irmp_init (void)
{
#if defined(PIC_CCS) || defined(PIC_C18)                                // PIC: do nothing
#elif defined (ARM_STM32_HAL)                                           // STM32 with Hal Library: do nothing
#elif defined (ARM_STM32)                                               // STM32
    GPIO_InitTypeDef     GPIO_InitStructure;

    /* GPIOx clock enable */
#  if defined (ARM_STM32L1XX)
    RCC_AHBPeriphClockCmd(IRMP_PORT_RCC, ENABLE);
#  elif defined (ARM_STM32F10X)
    RCC_APB2PeriphClockCmd(IRMP_PORT_RCC, ENABLE);
#  elif defined (ARM_STM32F30X)
    RCC_AHBPeriphClockCmd(IRMP_PORT_RCC, ENABLE);
#  elif defined (ARM_STM32F4XX)
    RCC_AHB1PeriphClockCmd(IRMP_PORT_RCC, ENABLE);
#  endif

    /* GPIO Configuration */
    GPIO_InitStructure.GPIO_Pin = IRMP_BIT;
#  if defined (ARM_STM32L1XX) || defined (ARM_STM32F4XX)
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
#  elif defined (ARM_STM32F10X)
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
#  elif defined (ARM_STM32F30X)
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
#  endif
    GPIO_Init(IRMP_PORT, &GPIO_InitStructure);

#elif defined(STELLARIS_ARM_CORTEX_M4)
    // Enable the GPIO port
    ROM_SysCtlPeripheralEnable(IRMP_PORT_PERIPH);

    // Set as an input
    ROM_GPIODirModeSet(IRMP_PORT_BASE, IRMP_PORT_PIN, GPIO_DIR_MODE_IN);
    ROM_GPIOPadConfigSet(IRMP_PORT_BASE, IRMP_PORT_PIN, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);

#elif defined(__SDCC_stm8)                                              // STM8
    IRMP_GPIO_STRUCT->DDR &= ~(1<<IRMP_BIT);                            // pin is input
    IRMP_GPIO_STRUCT->CR1 |= (1<<IRMP_BIT);                             // activate pullup

#elif defined (TEENSY_ARM_CORTEX_M4)                                    // TEENSY
    pinMode(IRMP_PIN, INPUT);

#elif defined(__xtensa__)                                               // ESP8266
    pinMode(IRMP_BIT_NUMBER, INPUT);
                                                                        // select pin function
#  if (IRMP_BIT_NUMBER == 12)
    PIN_FUNC_SELECT(PERIPHS_IO_MUX_MTDI_U, FUNC_GPIO12);
//  doesn't work for me:
//  # elif (IRMP_BIT_NUMBER == 13)
//  PIN_FUNC_SELECT(PERIPHS_IO_MUX_MTCK_U , FUNC_GPIO13);
#  else
#   warning Please add PIN_FUNC_SELECT when necessary.
#  endif
    GPIO_DIS_OUTPUT(IRMP_BIT_NUMBER);

#elif defined(__MBED__)
    gpio_init_in_ex(&gpioIRin, IRMP_PIN, IRMP_PINMODE);                 // initialize input for IR diode

#elif defined(_CHIBIOS_HAL_)
    // ChibiOS HAL automatically initializes all pins according to the board config file, no need to repeat here

#else                                                                   // AVR
    IRMP_PORT &= ~(1<<IRMP_BIT);                                        // deactivate pullup
    IRMP_DDR &= ~(1<<IRMP_BIT);                                         // set pin to input
#endif

#if IRMP_LOGGING == 1
    irmp_uart_init ();
#endif
}
#endif


/*---------------------------------------------------------------------------------------------------------------------------------------------------
 *  Get IRMP data
 *  @details  gets decoded IRMP data
 *  @param    pointer in order to store IRMP data
 *  @return    TRUE: successful, FALSE: failed
 *---------------------------------------------------------------------------------------------------------------------------------------------------
 */
uint_fast8_t
irmp_get_data (IRMP_DATA * irmp_data_p)
{
    uint_fast8_t   rtc = FALSE;
#if IRMP_SUPPORT_MERLIN_PROTOCOL == 1
    uint_fast8_t   cmd_len = 0;
#endif

    if (irmp_ir_detected)
    {
        switch (irmp_protocol)
        {
#if IRMP_SUPPORT_SAMSUNG_PROTOCOL == 1
            case IRMP_SAMSUNG_PROTOCOL:
                if ((irmp_command >> 8) == (~irmp_command & 0x00FF))
                {
                    irmp_command &= 0xff;
                    irmp_command |= irmp_id << 8;
                    rtc = TRUE;
                }
                break;

#if IRMP_SUPPORT_SAMSUNG48_PROTOCOL == 1
            case IRMP_SAMSUNG48_PROTOCOL:
                irmp_command = (irmp_command & 0x00FF) | ((irmp_id & 0x00FF) << 8);
                rtc = TRUE;
                break;
#endif
#endif

#if IRMP_SUPPORT_NEC_PROTOCOL == 1
            case IRMP_NEC_PROTOCOL:
                if ((irmp_command >> 8) == (~irmp_command & 0x00FF))
                {
                    irmp_command &= 0xff;
                    rtc = TRUE;
                }
                else if (irmp_address == 0x87EE)
                {
                    ANALYZE_PRINT ("Switching to APPLE protocol\n");
                    irmp_protocol = IRMP_APPLE_PROTOCOL;
                    irmp_address = (irmp_command & 0xFF00) >> 8;
                    irmp_command &= 0x00FF;
                    rtc = TRUE;
                }
                else
                {
                    ANALYZE_PRINT ("Switching to ONKYO protocol\n");
                    irmp_protocol = IRMP_ONKYO_PROTOCOL;
                    rtc = TRUE;
                }
                break;
#endif


#if IRMP_SUPPORT_NEC_PROTOCOL == 1
            case IRMP_VINCENT_PROTOCOL:
                if ((irmp_command >> 8) == (irmp_command & 0x00FF))
                {
                    irmp_command &= 0xff;
                    rtc = TRUE;
                }
                break;
#endif

#if IRMP_SUPPORT_BOSE_PROTOCOL == 1
            case IRMP_BOSE_PROTOCOL:
                if ((irmp_command >> 8) == (~irmp_command & 0x00FF))
                {
                    irmp_command &= 0xff;
                    rtc = TRUE;
                }
                break;
#endif

#if IRMP_SUPPORT_MERLIN_PROTOCOL == 1
            case IRMP_MERLIN_PROTOCOL:
                if (irmp_bit == 10)
                {
                    rtc = TRUE;
                }
                else if (irmp_bit >= 19 && ((irmp_bit - 3) % 8 == 0))
                {
                    if (((irmp_command >> 1) & 1) != (irmp_command & 1))
                    {
                        irmp_command >>= 1;
                        irmp_command |= ((irmp_address & 1) << (irmp_bit - 12));
                        irmp_address >>= 1;
                        cmd_len = (irmp_bit - 11) >> 3;
                        rtc = TRUE;
                    }
                }
                break;
#endif

#if IRMP_SUPPORT_SIEMENS_OR_RUWIDO_PROTOCOL == 1
            case IRMP_SIEMENS_PROTOCOL:
            case IRMP_RUWIDO_PROTOCOL:
                if (((irmp_command >> 1) & 0x0001) == (~irmp_command & 0x0001))
                {
                    irmp_command >>= 1;
                    rtc = TRUE;
                }
                break;
#endif
#if IRMP_SUPPORT_KATHREIN_PROTOCOL == 1
            case IRMP_KATHREIN_PROTOCOL:
                if (irmp_command != 0x0000)
                {
                    rtc = TRUE;
                }
                break;
#endif
#if IRMP_SUPPORT_RC5_PROTOCOL == 1
            case IRMP_RC5_PROTOCOL:
                irmp_address &= ~0x20;                              // clear toggle bit
                rtc = TRUE;
                break;
#endif
#if IRMP_SUPPORT_S100_PROTOCOL == 1
            case IRMP_S100_PROTOCOL:
                irmp_address &= ~0x20;                              // clear toggle bit
                rtc = TRUE;
                break;
#endif
#if IRMP_SUPPORT_IR60_PROTOCOL == 1
            case IRMP_IR60_PROTOCOL:
                if (irmp_command != 0x007d)                         // 0x007d (== 62<<1 + 1) is start instruction frame
                {
                    rtc = TRUE;
                }
                else
                {
                    ANALYZE_PRINT("Info IR60: got start instruction frame\n");
                }
                break;
#endif
#if IRMP_SUPPORT_RCCAR_PROTOCOL == 1
            case IRMP_RCCAR_PROTOCOL:
                // frame in irmp_data:
                // Bit 12 11 10 9  8  7  6  5  4  3  2  1  0
                //     V  D7 D6 D5 D4 D3 D2 D1 D0 A1 A0 C1 C0   //         10 9  8  7  6  5  4  3  2  1  0
                irmp_address = (irmp_command & 0x000C) >> 2;    // addr:   0  0  0  0  0  0  0  0  0  A1 A0
                irmp_command = ((irmp_command & 0x1000) >> 2) | // V-Bit:  V  0  0  0  0  0  0  0  0  0  0
                               ((irmp_command & 0x0003) << 8) | // C-Bits: 0  C1 C0 0  0  0  0  0  0  0  0
                               ((irmp_command & 0x0FF0) >> 4);  // D-Bits:          D7 D6 D5 D4 D3 D2 D1 D0
                rtc = TRUE;                                     // Summe:  V  C1 C0 D7 D6 D5 D4 D3 D2 D1 D0
                break;
#endif

#if IRMP_SUPPORT_NETBOX_PROTOCOL == 1                           // squeeze code to 8 bit, upper bit indicates release-key
            case IRMP_NETBOX_PROTOCOL:
                if (irmp_command & 0x1000)                      // last bit set?
                {
                    if ((irmp_command & 0x1f) == 0x15)          // key pressed: 101 01 (LSB)
                    {
                        irmp_command >>= 5;
                        irmp_command &= 0x7F;
                        rtc = TRUE;
                    }
                    else if ((irmp_command & 0x1f) == 0x10)     // key released: 000 01 (LSB)
                    {
                        irmp_command >>= 5;
                        irmp_command |= 0x80;
                        rtc = TRUE;
                    }
                    else
                    {
                        ANALYZE_PRINT("error NETBOX: bit6/7 must be 0/1\n");
                    }
                }
                else
                {
                    ANALYZE_PRINT("error NETBOX: last bit not set\n");
                }
                break;
#endif
#if IRMP_SUPPORT_LEGO_PROTOCOL == 1
            case IRMP_LEGO_PROTOCOL:
            {
                uint_fast8_t crc = 0x0F ^ ((irmp_command & 0xF000) >> 12) ^ ((irmp_command & 0x0F00) >> 8) ^ ((irmp_command & 0x00F0) >> 4);

                if ((irmp_command & 0x000F) == crc)
                {
                    irmp_command >>= 4;
                    rtc = TRUE;
                }
                else
                {
                    ANALYZE_PRINT ("CRC error in LEGO protocol\n");
                    // rtc = TRUE;                              // don't accept codes with CRC errors
                }
                break;
            }
#endif

#if IRMP_SUPPORT_METZ_PROTOCOL == 1
            case IRMP_METZ_PROTOCOL:
                irmp_address &= ~0x40;                              // clear toggle bit
                if (((~irmp_address) & 0x07) == (irmp_address >> 3) && ((~irmp_command) & 0x3f) == (irmp_command >> 6))
                {
                    irmp_address >>= 3;
                    irmp_command >>= 6;
                    rtc = TRUE;
                }
                break;
#endif
            default:
            {
                rtc = TRUE;
                break;
            }
        }

        if (rtc)
        {
            irmp_data_p->protocol = irmp_protocol;
            irmp_data_p->address  = irmp_address;
            irmp_data_p->command  = irmp_command;
            irmp_data_p->flags    = irmp_flags;
#if IRMP_SUPPORT_MERLIN_PROTOCOL == 1
            irmp_data_p->flags   |= cmd_len;
#endif
        }
        else
        {
            irmp_protocol = IRMP_UNKNOWN_PROTOCOL;
        }

        irmp_command  = 0;                                      // don't reset irmp_protocol here, needed for detection of NEC & JVC repetition frames!
        irmp_address  = 0;
        irmp_flags    = 0;

        irmp_ir_detected = FALSE;
    }

    return rtc;
}

#if IRMP_USE_CALLBACK == 1
void
irmp_set_callback_ptr (void (*cb)(uint_fast8_t))
{
    irmp_callback_ptr = cb;
}
#endif // IRMP_USE_CALLBACK == 1

// these statics must not be volatile, because they are only used by irmp_store_bit(), which is called by irmp_ISR()
static uint_fast16_t irmp_tmp_address;                                      // ir address
#if IRMP_32_BIT == 1
static uint_fast32_t irmp_tmp_command;                                      // ir command
#else
static uint_fast16_t irmp_tmp_command;                                      // ir command
#endif

#if (IRMP_SUPPORT_RC5_PROTOCOL == 1 && (IRMP_SUPPORT_FDC_PROTOCOL == 1 || IRMP_SUPPORT_RCCAR_PROTOCOL == 1)) || IRMP_SUPPORT_NEC42_PROTOCOL == 1
static uint_fast16_t irmp_tmp_address2;                                     // ir address
static uint_fast16_t irmp_tmp_command2;                                     // ir command
#endif

#if IRMP_SUPPORT_LGAIR_PROTOCOL == 1
static uint_fast16_t irmp_lgair_address;                                    // ir address
static uint_fast16_t irmp_lgair_command;                                    // ir command
#endif

#if IRMP_SUPPORT_SAMSUNG_PROTOCOL == 1
static uint_fast16_t irmp_tmp_id;                                           // ir id (only SAMSUNG)
#endif
#if IRMP_SUPPORT_KASEIKYO_PROTOCOL == 1
static uint8_t      xor_check[6];                                           // check kaseikyo "parity" bits
static uint_fast8_t genre2;                                                 // save genre2 bits here, later copied to MSB in flags
#endif

#if IRMP_SUPPORT_ORTEK_PROTOCOL == 1
static uint_fast8_t  parity;                                                // number of '1' of the first 14 bits, check if even.
#endif

#if IRMP_SUPPORT_MITSU_HEAVY_PROTOCOL == 1
static uint_fast8_t  check;                                                 // number of '1' of the first 14 bits, check if even.
static uint_fast8_t  mitsu_parity;                                          // number of '1' of the first 14 bits, check if even.
#endif

/*---------------------------------------------------------------------------------------------------------------------------------------------------
 *  store bit
 *  @details  store bit in temp address or temp command
 *  @param    value to store: 0 or 1
 *---------------------------------------------------------------------------------------------------------------------------------------------------
 */
// verhindert, dass irmp_store_bit() inline compiliert wird:
// static void irmp_store_bit (uint_fast8_t) __attribute__ ((noinline));

static void
irmp_store_bit (uint_fast8_t value)
{
#if IRMP_SUPPORT_ACP24_PROTOCOL == 1
    if (irmp_param.protocol == IRMP_ACP24_PROTOCOL)                                                 // squeeze 64 bits into 16 bits:
    {
        if (value)
        {
            // ACP24-Frame:
            //           1         2         3         4         5         6
            // 0123456789012345678901234567890123456789012345678901234567890123456789
            // N VVMMM    ? ???    t vmA x                 y                     TTTT
            //
            // irmp_data_p->command:
            //
            //         5432109876543210
            //         NAVVvMMMmtxyTTTT

            switch (irmp_bit)
            {
                case  0: irmp_tmp_command |= (1<<15); break;                                        // N
                case  2: irmp_tmp_command |= (1<<13); break;                                        // V
                case  3: irmp_tmp_command |= (1<<12); break;                                        // V
                case  4: irmp_tmp_command |= (1<<10); break;                                        // M
                case  5: irmp_tmp_command |= (1<< 9); break;                                        // M
                case  6: irmp_tmp_command |= (1<< 8); break;                                        // M
                case 20: irmp_tmp_command |= (1<< 6); break;                                        // t
                case 22: irmp_tmp_command |= (1<<11); break;                                        // v
                case 23: irmp_tmp_command |= (1<< 7); break;                                        // m
                case 24: irmp_tmp_command |= (1<<14); break;                                        // A
                case 26: irmp_tmp_command |= (1<< 5); break;                                        // x
                case 44: irmp_tmp_command |= (1<< 4); break;                                        // y
                case 66: irmp_tmp_command |= (1<< 3); break;                                        // T
                case 67: irmp_tmp_command |= (1<< 2); break;                                        // T
                case 68: irmp_tmp_command |= (1<< 1); break;                                        // T
                case 69: irmp_tmp_command |= (1<< 0); break;                                        // T
            }
        }
    }
    else
#endif // IRMP_SUPPORT_ACP24_PROTOCOL

#if IRMP_SUPPORT_ORTEK_PROTOCOL == 1
    if (irmp_param.protocol == IRMP_ORTEK_PROTOCOL)
    {
        if (irmp_bit < 14)
        {
            if (value)
            {
                parity++;
            }
        }
        else if (irmp_bit == 14)
        {
            if (value)                                                                                      // value == 1: even parity
            {
                if (parity & 0x01)
                {
                    parity = PARITY_CHECK_FAILED;
                }
                else
                {
                    parity = PARITY_CHECK_OK;
                }
            }
            else
            {
                if (parity & 0x01)                                                                          // value == 0: odd parity
                {
                    parity = PARITY_CHECK_OK;
                }
                else
                {
                    parity = PARITY_CHECK_FAILED;
                }
            }
        }
    }
    else
#endif
    {
        ;
    }

#if IRMP_SUPPORT_GRUNDIG_NOKIA_IR60_PROTOCOL == 1
    if (irmp_bit == 0 && irmp_param.protocol == IRMP_GRUNDIG_PROTOCOL)
    {
        first_bit = value;
    }
    else
#endif

    if (irmp_bit >= irmp_param.address_offset && irmp_bit < irmp_param.address_end)
    {
        if (irmp_param.lsb_first)
        {
            irmp_tmp_address |= (((uint_fast16_t) (value)) << (irmp_bit - irmp_param.address_offset));   // CV wants cast
        }
        else
        {
            irmp_tmp_address <<= 1;
            irmp_tmp_address |= value;
        }
    }
    else if (irmp_bit >= irmp_param.command_offset && irmp_bit < irmp_param.command_end)
    {
        if (irmp_param.lsb_first)
        {
#if IRMP_SUPPORT_SAMSUNG48_PROTOCOL == 1
            if (irmp_param.protocol == IRMP_SAMSUNG48_PROTOCOL && irmp_bit >= 32)
            {
                irmp_tmp_id |= (((uint_fast16_t) (value)) << (irmp_bit - 32));   // CV wants cast
            }
            else
#endif
            {
                irmp_tmp_command |= (((uint_fast16_t) (value)) << (irmp_bit - irmp_param.command_offset));   // CV wants cast
            }
        }
        else
        {
            irmp_tmp_command <<= 1;
            irmp_tmp_command |= value;
        }
    }

#if IRMP_SUPPORT_LGAIR_PROTOCOL == 1
    if (irmp_param.protocol == IRMP_NEC_PROTOCOL || irmp_param.protocol == IRMP_NEC42_PROTOCOL)
    {
        if (irmp_bit < 8)
        {
            irmp_lgair_address <<= 1;                                                               // LGAIR uses MSB
            irmp_lgair_address |= value;
        }
        else if (irmp_bit < 24)
        {
            irmp_lgair_command <<= 1;                                                               // LGAIR uses MSB
            irmp_lgair_command |= value;
        }
    }
    // NO else!
#endif

#if IRMP_SUPPORT_NEC42_PROTOCOL == 1
    if (irmp_param.protocol == IRMP_NEC42_PROTOCOL && irmp_bit >= 13 && irmp_bit < 26)
    {
        irmp_tmp_address2 |= (((uint_fast16_t) (value)) << (irmp_bit - 13));                             // CV wants cast
    }
    else
#endif

#if IRMP_SUPPORT_SAMSUNG_PROTOCOL == 1
    if (irmp_param.protocol == IRMP_SAMSUNG_PROTOCOL && irmp_bit >= SAMSUNG_ID_OFFSET && irmp_bit < SAMSUNG_ID_OFFSET + SAMSUNG_ID_LEN)
    {
        irmp_tmp_id |= (((uint_fast16_t) (value)) << (irmp_bit - SAMSUNG_ID_OFFSET));                    // store with LSB first
    }
    else
#endif

#if IRMP_SUPPORT_KASEIKYO_PROTOCOL == 1
    if (irmp_param.protocol == IRMP_KASEIKYO_PROTOCOL)
    {
        if (irmp_bit >= 20 && irmp_bit < 24)
        {
            irmp_tmp_command |= (((uint_fast16_t) (value)) << (irmp_bit - 8));      // store 4 system bits (genre 1) in upper nibble with LSB first
        }
        else if (irmp_bit >= 24 && irmp_bit < 28)
        {
            genre2 |= (((uint_fast8_t) (value)) << (irmp_bit - 20));                // store 4 system bits (genre 2) in upper nibble with LSB first
        }

        if (irmp_bit < KASEIKYO_COMPLETE_DATA_LEN)
        {
            if (value)
            {
                xor_check[irmp_bit / 8] |= 1 << (irmp_bit % 8);
            }
            else
            {
                xor_check[irmp_bit / 8] &= ~(1 << (irmp_bit % 8));
            }
        }
    }
    else
#endif

#if IRMP_SUPPORT_MITSU_HEAVY_PROTOCOL == 1
    if (irmp_param.protocol == IRMP_MITSU_HEAVY_PROTOCOL)                           // squeeze 64 bits into 16 bits:
    {
        if (irmp_bit == 72 )
        {                                                                           // irmp_tmp_address, irmp_tmp_command received: check parity & compress
            mitsu_parity = PARITY_CHECK_OK;

            check = irmp_tmp_address >> 8;                                          // inverted upper byte == lower byte?
            check = ~ check;

            if (check == (irmp_tmp_address & 0xFF))
            {                                                                       // ok:
                irmp_tmp_address <<= 8;                                             // throw away upper byte
            }
            else
            {
                mitsu_parity = PARITY_CHECK_FAILED;
            }

            check = irmp_tmp_command >> 8;                                          // inverted upper byte == lower byte?
            check = ~ check;
            if (check == (irmp_tmp_command & 0xFF))
            {                                                                       // ok:  pack together
                irmp_tmp_address |= irmp_tmp_command & 0xFF;                        // byte 1, byte2 in irmp_tmp_address, irmp_tmp_command can be used for byte 3
            }
            else
            {
                mitsu_parity = PARITY_CHECK_FAILED;
            }
            irmp_tmp_command = 0;
        }

        if (irmp_bit >= 72 )
        {                                                                           // receive 3. word in irmp_tmp_command
            irmp_tmp_command <<= 1;
            irmp_tmp_command |= value;
        }
    }
    else
#endif // IRMP_SUPPORT_MITSU_HEAVY_PROTOCOL
    {
        ;
    }

    irmp_bit++;
}

/*---------------------------------------------------------------------------------------------------------------------------------------------------
 *  store bit
 *  @details  store bit in temp address or temp command
 *  @param    value to store: 0 or 1
 *---------------------------------------------------------------------------------------------------------------------------------------------------
 */
#if IRMP_SUPPORT_RC5_PROTOCOL == 1 && (IRMP_SUPPORT_FDC_PROTOCOL == 1 || IRMP_SUPPORT_RCCAR_PROTOCOL == 1)
static void
irmp_store_bit2 (uint_fast8_t value)
{
    uint_fast8_t irmp_bit2;

    if (irmp_param.protocol)
    {
        irmp_bit2 = irmp_bit - 2;
    }
    else
    {
        irmp_bit2 = irmp_bit - 1;
    }

    if (irmp_bit2 >= irmp_param2.address_offset && irmp_bit2 < irmp_param2.address_end)
    {
        irmp_tmp_address2 |= (((uint_fast16_t) (value)) << (irmp_bit2 - irmp_param2.address_offset));   // CV wants cast
    }
    else if (irmp_bit2 >= irmp_param2.command_offset && irmp_bit2 < irmp_param2.command_end)
    {
        irmp_tmp_command2 |= (((uint_fast16_t) (value)) << (irmp_bit2 - irmp_param2.command_offset));   // CV wants cast
    }
}
#endif // IRMP_SUPPORT_RC5_PROTOCOL == 1 && (IRMP_SUPPORT_FDC_PROTOCOL == 1 || IRMP_SUPPORT_RCCAR_PROTOCOL == 1)

#ifdef ANALYZE
static uint32_t s_curSample = 0;
static uint32_t s_startBitSample = 0;
#endif

/*---------------------------------------------------------------------------------------------------------------------------------------------------
 *  ISR routine
 *  @details  ISR routine, called 10000 times per second
 *---------------------------------------------------------------------------------------------------------------------------------------------------
 */
uint_fast8_t
irmp_ISR (void)
{
    static uint_fast8_t     irmp_start_bit_detected;                                // flag: start bit detected
    static uint_fast8_t     wait_for_space;                                         // flag: wait for data bit space
    static uint_fast8_t     wait_for_start_space;                                   // flag: wait for start bit space
    static uint_fast8_t     irmp_pulse_time;                                        // count bit time for pulse
    static PAUSE_LEN        irmp_pause_time;                                        // count bit time for pause
    static uint_fast16_t    last_irmp_address = 0xFFFF;                             // save last irmp address to recognize key repetition
#if IRMP_32_BIT == 1
    static uint_fast32_t    last_irmp_command = 0xFFFFFFFF;                         // save last irmp command to recognize key repetition
#else
    static uint_fast16_t    last_irmp_command = 0xFFFF;                             // save last irmp command to recognize key repetition
#endif
    static uint_fast16_t    key_repetition_len;                                     // SIRCS repeats frame 2-5 times with 45 ms pause
    static uint_fast8_t     repetition_frame_number;
#if IRMP_SUPPORT_DENON_PROTOCOL == 1
    static uint_fast16_t    last_irmp_denon_command;                                // save last irmp command to recognize DENON frame repetition
    static uint_fast16_t    denon_repetition_len = 0xFFFF;                          // denon repetition len of 2nd auto generated frame
#endif
#if IRMP_SUPPORT_RC5_PROTOCOL == 1 || IRMP_SUPPORT_S100_PROTOCOL == 1
    static uint_fast8_t     rc5_cmd_bit6;                                           // bit 6 of RC5 command is the inverted 2nd start bit
#endif
#if IRMP_SUPPORT_MANCHESTER == 1
    static PAUSE_LEN        last_pause;                                             // last pause value
#endif
#if IRMP_SUPPORT_MANCHESTER == 1 || IRMP_SUPPORT_BANG_OLUFSEN_PROTOCOL == 1
    static uint_fast8_t     last_value;                                             // last bit value
#endif
#if IRMP_SUPPORT_RCII_PROTOCOL == 1
    static uint_fast8_t     waiting_for_2nd_pulse = 0;
#endif
    uint_fast8_t            irmp_input;                                             // input value

#ifdef ANALYZE

#if 0 // only for test
    static uint_fast8_t     last_irmp_start_bit_detected = 0xFF;
    static uint_fast8_t     last_irmp_pulse_time = 0xFF;

    if (last_irmp_start_bit_detected != irmp_start_bit_detected || last_irmp_pulse_time != irmp_pulse_time)
    {
        last_irmp_start_bit_detected    = irmp_start_bit_detected;
        last_irmp_pulse_time            = irmp_pulse_time;

        printf ("%d %d %d\n", time_counter, irmp_start_bit_detected, irmp_pulse_time);
    }
#endif // 0

    time_counter++;

    printf("%d: %i - %d %d %d %d %d %d %d %d %d %d %d %d %d %d\n"
          , (int)time_counter
          , (int)IRMP_PIN
          , (int)irmp_start_bit_detected
          , (int)wait_for_space
          , (int)wait_for_start_space
          , (int)irmp_pulse_time
          , (int)irmp_pause_time
          , (int)last_irmp_address
          , (int)last_irmp_command
          , (int)key_repetition_len
          , (int)repetition_frame_number
          , (int)last_irmp_denon_command
          , (int)last_pause
          , (int)last_value
          , (int)denon_repetition_len
          , (int)rc5_cmd_bit6
      );

#endif // ANALYZE

#if defined(__SDCC_stm8)
    irmp_input = input(IRMP_GPIO_STRUCT->IDR)
#elif defined(__MBED__)
    //irmp_input = inputPin;
    irmp_input = gpio_read (&gpioIRin);
#else
    irmp_input = input(IRMP_PIN);
#endif

#if IRMP_USE_CALLBACK == 1
    if (irmp_callback_ptr)
    {
        static uint_fast8_t last_inverted_input;

        if (last_inverted_input != !irmp_input)
        {
            (*irmp_callback_ptr) (! irmp_input);
            last_inverted_input = !irmp_input;
        }
    }
#endif // IRMP_USE_CALLBACK == 1

    irmp_log(irmp_input);                                                       // log ir signal, if IRMP_LOGGING defined

    if (! irmp_ir_detected)                                                     // ir code already detected?
    {                                                                           // no...
        if (! irmp_start_bit_detected)                                          // start bit detected?
        {                                                                       // no...
            if (! irmp_input)                                                   // receiving burst?
            {                                                                   // yes...
//              irmp_busy_flag = TRUE;
#ifdef ANALYZE
                if (! irmp_pulse_time)
                {
                    s_startBitSample = s_curSample;
                    ANALYZE_PRINTF_1("%8.3fms [starting pulse]\n", (float) (time_counter * 1000) / F_INTERRUPTS);
                }
#endif // ANALYZE
                irmp_pulse_time++;                                              // increment counter
            }
            else
            {                                                                   // no...
                if (irmp_pulse_time)                                            // it's dark....
                {                                                               // set flags for counting the time of darkness...
                    irmp_start_bit_detected = 1;
                    wait_for_start_space    = 1;
                    wait_for_space          = 0;
                    irmp_tmp_command        = 0;
                    irmp_tmp_address        = 0;
#if IRMP_SUPPORT_KASEIKYO_PROTOCOL == 1
                    genre2                  = 0;
#endif
#if IRMP_SUPPORT_SAMSUNG_PROTOCOL == 1
                    irmp_tmp_id = 0;
#endif

#if IRMP_SUPPORT_RC5_PROTOCOL == 1 && (IRMP_SUPPORT_FDC_PROTOCOL == 1 || IRMP_SUPPORT_RCCAR_PROTOCOL == 1) || IRMP_SUPPORT_NEC42_PROTOCOL == 1
                    irmp_tmp_command2       = 0;
                    irmp_tmp_address2       = 0;
#endif
#if IRMP_SUPPORT_LGAIR_PROTOCOL == 1
                    irmp_lgair_command      = 0;
                    irmp_lgair_address      = 0;
#endif
                    irmp_bit                = 0xff;
                    irmp_pause_time         = 1;                                // 1st pause: set to 1, not to 0!
#if IRMP_SUPPORT_RC5_PROTOCOL == 1 || IRMP_SUPPORT_S100_PROTOCOL == 1
                    rc5_cmd_bit6            = 0;                                // fm 2010-03-07: bugfix: reset it after incomplete RC5 frame!
#endif
                }
                else
                {
                    if (key_repetition_len < 0xFFFF)                            // avoid overflow of counter
                    {
                        key_repetition_len++;

#if IRMP_SUPPORT_DENON_PROTOCOL == 1
                        if (denon_repetition_len < 0xFFFF)                      // avoid overflow of counter
                        {
                            denon_repetition_len++;

                            if (denon_repetition_len >= DENON_AUTO_REPETITION_PAUSE_LEN && last_irmp_denon_command != 0)
                            {
                                ANALYZE_PRINTF_1 ("%8.3fms warning: did not receive inverted command repetition\n",
                                                (float) (time_counter * 1000) / F_INTERRUPTS);
                                last_irmp_denon_command = 0;
                                denon_repetition_len = 0xFFFF;
                            }
                        }
#endif // IRMP_SUPPORT_DENON_PROTOCOL == 1
                    }
                }
            }
        }
        else
        {
            if (wait_for_start_space)                                           // we have received start bit...
            {                                                                   // ...and are counting the time of darkness
                if (irmp_input)                                                 // still dark?
                {                                                               // yes
                    irmp_pause_time++;                                          // increment counter

#if IRMP_SUPPORT_NIKON_PROTOCOL == 1
                    if (((irmp_pulse_time < NIKON_START_BIT_PULSE_LEN_MIN || irmp_pulse_time > NIKON_START_BIT_PULSE_LEN_MAX) && irmp_pause_time > IRMP_TIMEOUT_LEN) ||
                         irmp_pause_time > IRMP_TIMEOUT_NIKON_LEN)
#else
                    if (irmp_pause_time > IRMP_TIMEOUT_LEN)                     // timeout?
#endif
                    {                                                           // yes...
#if IRMP_SUPPORT_JVC_PROTOCOL == 1
                        if (irmp_protocol == IRMP_JVC_PROTOCOL)                 // don't show eror if JVC protocol, irmp_pulse_time has been set below!
                        {
                            ;
                        }
                        else
#endif // IRMP_SUPPORT_JVC_PROTOCOL == 1
                        {
                            ANALYZE_PRINTF_3 ("%8.3fms error 1: pause after start bit pulse %d too long: %d\n", (float) (time_counter * 1000) / F_INTERRUPTS, irmp_pulse_time, irmp_pause_time);
                            ANALYZE_ONLY_NORMAL_PUTCHAR ('\n');
                        }

                        irmp_start_bit_detected = 0;                            // reset flags, let's wait for another start bit
                        irmp_pulse_time         = 0;
                        irmp_pause_time         = 0;
                    }
                }
                else
                {                                                               // receiving first data pulse!
                    IRMP_PARAMETER * irmp_param_p;
                    irmp_param_p = (IRMP_PARAMETER *) 0;

#if IRMP_SUPPORT_RC5_PROTOCOL == 1 && (IRMP_SUPPORT_FDC_PROTOCOL == 1 || IRMP_SUPPORT_RCCAR_PROTOCOL == 1)
                    irmp_param2.protocol = 0;
#endif

                    ANALYZE_PRINTF_3 ("%8.3fms [start-bit: pulse = %2d, pause = %2d]\n", (float) (time_counter * 1000) / F_INTERRUPTS, irmp_pulse_time, irmp_pause_time);

#if IRMP_SUPPORT_SIRCS_PROTOCOL == 1
                    if (irmp_pulse_time >= SIRCS_START_BIT_PULSE_LEN_MIN && irmp_pulse_time <= SIRCS_START_BIT_PULSE_LEN_MAX &&
                        irmp_pause_time >= SIRCS_START_BIT_PAUSE_LEN_MIN && irmp_pause_time <= SIRCS_START_BIT_PAUSE_LEN_MAX)
                    {                                                           // it's SIRCS
                        ANALYZE_PRINTF_4 ("protocol = SIRCS, start bit timings: pulse: %3d - %3d, pause: %3d - %3d\n",
                                        SIRCS_START_BIT_PULSE_LEN_MIN, SIRCS_START_BIT_PULSE_LEN_MAX,
                                        SIRCS_START_BIT_PAUSE_LEN_MIN, SIRCS_START_BIT_PAUSE_LEN_MAX);
                        irmp_param_p = (IRMP_PARAMETER *) &sircs_param;
                    }
                    else
#endif // IRMP_SUPPORT_SIRCS_PROTOCOL == 1

#if IRMP_SUPPORT_JVC_PROTOCOL == 1
                    if (irmp_protocol == IRMP_JVC_PROTOCOL &&                                                       // last protocol was JVC, awaiting repeat frame
                        irmp_pulse_time >= JVC_START_BIT_PULSE_LEN_MIN && irmp_pulse_time <= JVC_START_BIT_PULSE_LEN_MAX &&
                        irmp_pause_time >= JVC_REPEAT_START_BIT_PAUSE_LEN_MIN && irmp_pause_time <= JVC_REPEAT_START_BIT_PAUSE_LEN_MAX)
                    {
                        ANALYZE_PRINTF_4 ("protocol = NEC or JVC (type 1) repeat frame, start bit timings: pulse: %3d - %3d, pause: %3d - %3d\n",
                                        JVC_START_BIT_PULSE_LEN_MIN, JVC_START_BIT_PULSE_LEN_MAX,
                                        JVC_REPEAT_START_BIT_PAUSE_LEN_MIN, JVC_REPEAT_START_BIT_PAUSE_LEN_MAX);
                        irmp_param_p = (IRMP_PARAMETER *) &nec_param;
                    }
                    else
#endif // IRMP_SUPPORT_JVC_PROTOCOL == 1

#if IRMP_SUPPORT_NEC_PROTOCOL == 1
                    if (irmp_pulse_time >= NEC_START_BIT_PULSE_LEN_MIN && irmp_pulse_time <= NEC_START_BIT_PULSE_LEN_MAX &&
                        irmp_pause_time >= NEC_START_BIT_PAUSE_LEN_MIN && irmp_pause_time <= NEC_START_BIT_PAUSE_LEN_MAX)
                    {
#if IRMP_SUPPORT_NEC42_PROTOCOL == 1
                        ANALYZE_PRINTF_4 ("protocol = NEC42, start bit timings: pulse: %3d - %3d, pause: %3d - %3d\n",
                                        NEC_START_BIT_PULSE_LEN_MIN, NEC_START_BIT_PULSE_LEN_MAX,
                                        NEC_START_BIT_PAUSE_LEN_MIN, NEC_START_BIT_PAUSE_LEN_MAX);
                        irmp_param_p = (IRMP_PARAMETER *) &nec42_param;
#else
                        ANALYZE_PRINTF_4 ("protocol = NEC, start bit timings: pulse: %3d - %3d, pause: %3d - %3d\n",
                                        NEC_START_BIT_PULSE_LEN_MIN, NEC_START_BIT_PULSE_LEN_MAX,
                                        NEC_START_BIT_PAUSE_LEN_MIN, NEC_START_BIT_PAUSE_LEN_MAX);
                        irmp_param_p = (IRMP_PARAMETER *) &nec_param;
#endif
                    }
                    else if (irmp_pulse_time >= NEC_START_BIT_PULSE_LEN_MIN        && irmp_pulse_time <= NEC_START_BIT_PULSE_LEN_MAX &&
                             irmp_pause_time >= NEC_REPEAT_START_BIT_PAUSE_LEN_MIN && irmp_pause_time <= NEC_REPEAT_START_BIT_PAUSE_LEN_MAX)
                    {                                                           // it's NEC
#if IRMP_SUPPORT_JVC_PROTOCOL == 1
                        if (irmp_protocol == IRMP_JVC_PROTOCOL)                 // last protocol was JVC, awaiting repeat frame
                        {                                                       // some jvc remote controls use nec repetition frame for jvc repetition frame
                            ANALYZE_PRINTF_4 ("protocol = JVC repeat frame type 2, start bit timings: pulse: %3d - %3d, pause: %3d - %3d\n",
                                            NEC_START_BIT_PULSE_LEN_MIN, NEC_START_BIT_PULSE_LEN_MAX,
                                            NEC_REPEAT_START_BIT_PAUSE_LEN_MIN, NEC_REPEAT_START_BIT_PAUSE_LEN_MAX);
                            irmp_param_p = (IRMP_PARAMETER *) &nec_param;
                        }
                        else
#endif // IRMP_SUPPORT_JVC_PROTOCOL == 1
                        {
                            ANALYZE_PRINTF_4 ("protocol = NEC (repetition frame), start bit timings: pulse: %3d - %3d, pause: %3d - %3d\n",
                                            NEC_START_BIT_PULSE_LEN_MIN, NEC_START_BIT_PULSE_LEN_MAX,
                                            NEC_REPEAT_START_BIT_PAUSE_LEN_MIN, NEC_REPEAT_START_BIT_PAUSE_LEN_MAX);

                            irmp_param_p = (IRMP_PARAMETER *) &nec_rep_param;
                        }
                    }
                    else

#if IRMP_SUPPORT_JVC_PROTOCOL == 1
                    if (irmp_protocol == IRMP_JVC_PROTOCOL &&                   // last protocol was JVC, awaiting repeat frame
                        irmp_pulse_time >= NEC_START_BIT_PULSE_LEN_MIN && irmp_pulse_time <= NEC_START_BIT_PULSE_LEN_MAX &&
                        irmp_pause_time >= NEC_0_PAUSE_LEN_MIN         && irmp_pause_time <= NEC_0_PAUSE_LEN_MAX)
                    {                                                           // it's JVC repetition type 3
                        ANALYZE_PRINTF_4 ("protocol = JVC repeat frame type 3, start bit timings: pulse: %3d - %3d, pause: %3d - %3d\n",
                                        NEC_START_BIT_PULSE_LEN_MIN, NEC_START_BIT_PULSE_LEN_MAX,
                                        NEC_0_PAUSE_LEN_MIN, NEC_0_PAUSE_LEN_MAX);
                        irmp_param_p = (IRMP_PARAMETER *) &nec_param;
                    }
                    else
#endif // IRMP_SUPPORT_JVC_PROTOCOL == 1

#endif // IRMP_SUPPORT_NEC_PROTOCOL == 1

#if IRMP_SUPPORT_TELEFUNKEN_PROTOCOL == 1
                    if (irmp_pulse_time >= TELEFUNKEN_START_BIT_PULSE_LEN_MIN && irmp_pulse_time <= TELEFUNKEN_START_BIT_PULSE_LEN_MAX &&
                        irmp_pause_time >= TELEFUNKEN_START_BIT_PAUSE_LEN_MIN && irmp_pause_time <= TELEFUNKEN_START_BIT_PAUSE_LEN_MAX)
                    {
                        ANALYZE_PRINTF_4 ("protocol = TELEFUNKEN, start bit timings: pulse: %3d - %3d, pause: %3d - %3d\n",
                                        TELEFUNKEN_START_BIT_PULSE_LEN_MIN, TELEFUNKEN_START_BIT_PULSE_LEN_MAX,
                                        TELEFUNKEN_START_BIT_PAUSE_LEN_MIN, TELEFUNKEN_START_BIT_PAUSE_LEN_MAX);
                        irmp_param_p = (IRMP_PARAMETER *) &telefunken_param;
                    }
                    else
#endif // IRMP_SUPPORT_TELEFUNKEN_PROTOCOL == 1

#if IRMP_SUPPORT_ROOMBA_PROTOCOL == 1
                    if (irmp_pulse_time >= ROOMBA_START_BIT_PULSE_LEN_MIN && irmp_pulse_time <= ROOMBA_START_BIT_PULSE_LEN_MAX &&
                        irmp_pause_time >= ROOMBA_START_BIT_PAUSE_LEN_MIN && irmp_pause_time <= ROOMBA_START_BIT_PAUSE_LEN_MAX)
                    {
                        ANALYZE_PRINTF_4 ("protocol = ROOMBA, start bit timings: pulse: %3d - %3d, pause: %3d - %3d\n",
                                        ROOMBA_START_BIT_PULSE_LEN_MIN, ROOMBA_START_BIT_PULSE_LEN_MAX,
                                        ROOMBA_START_BIT_PAUSE_LEN_MIN, ROOMBA_START_BIT_PAUSE_LEN_MAX);
                        irmp_param_p = (IRMP_PARAMETER *) &roomba_param;
                    }
                    else
#endif // IRMP_SUPPORT_ROOMBA_PROTOCOL == 1

#if IRMP_SUPPORT_ACP24_PROTOCOL == 1
                    if (irmp_pulse_time >= ACP24_START_BIT_PULSE_LEN_MIN && irmp_pulse_time <= ACP24_START_BIT_PULSE_LEN_MAX &&
                        irmp_pause_time >= ACP24_START_BIT_PAUSE_LEN_MIN && irmp_pause_time <= ACP24_START_BIT_PAUSE_LEN_MAX)
                    {
                        ANALYZE_PRINTF_4 ("protocol = ACP24, start bit timings: pulse: %3d - %3d, pause: %3d - %3d\n",
                                        ACP24_START_BIT_PULSE_LEN_MIN, ACP24_START_BIT_PULSE_LEN_MAX,
                                        ACP24_START_BIT_PAUSE_LEN_MIN, ACP24_START_BIT_PAUSE_LEN_MAX);
                        irmp_param_p = (IRMP_PARAMETER *) &acp24_param;
                    }
                    else
#endif // IRMP_SUPPORT_ROOMBA_PROTOCOL == 1

#if IRMP_SUPPORT_PENTAX_PROTOCOL == 1
                    if (irmp_pulse_time >= PENTAX_START_BIT_PULSE_LEN_MIN && irmp_pulse_time <= PENTAX_START_BIT_PULSE_LEN_MAX &&
                        irmp_pause_time >= PENTAX_START_BIT_PAUSE_LEN_MIN && irmp_pause_time <= PENTAX_START_BIT_PAUSE_LEN_MAX)
                    {
                        ANALYZE_PRINTF_4 ("protocol = PENTAX, start bit timings: pulse: %3d - %3d, pause: %3d - %3d\n",
                                        PENTAX_START_BIT_PULSE_LEN_MIN, PENTAX_START_BIT_PULSE_LEN_MAX,
                                        PENTAX_START_BIT_PAUSE_LEN_MIN, PENTAX_START_BIT_PAUSE_LEN_MAX);
                        irmp_param_p = (IRMP_PARAMETER *) &pentax_param;
                    }
                    else
#endif // IRMP_SUPPORT_PENTAX_PROTOCOL == 1

#if IRMP_SUPPORT_NIKON_PROTOCOL == 1
                    if (irmp_pulse_time >= NIKON_START_BIT_PULSE_LEN_MIN && irmp_pulse_time <= NIKON_START_BIT_PULSE_LEN_MAX &&
                        irmp_pause_time >= NIKON_START_BIT_PAUSE_LEN_MIN && irmp_pause_time <= NIKON_START_BIT_PAUSE_LEN_MAX)
                    {
                        ANALYZE_PRINTF_4 ("protocol = NIKON, start bit timings: pulse: %3d - %3d, pause: %3d - %3d\n",
                                        NIKON_START_BIT_PULSE_LEN_MIN, NIKON_START_BIT_PULSE_LEN_MAX,
                                        NIKON_START_BIT_PAUSE_LEN_MIN, NIKON_START_BIT_PAUSE_LEN_MAX);
                        irmp_param_p = (IRMP_PARAMETER *) &nikon_param;
                    }
                    else
#endif // IRMP_SUPPORT_NIKON_PROTOCOL == 1

#if IRMP_SUPPORT_SAMSUNG_PROTOCOL == 1
                    if (irmp_pulse_time >= SAMSUNG_START_BIT_PULSE_LEN_MIN && irmp_pulse_time <= SAMSUNG_START_BIT_PULSE_LEN_MAX &&
                        irmp_pause_time >= SAMSUNG_START_BIT_PAUSE_LEN_MIN && irmp_pause_time <= SAMSUNG_START_BIT_PAUSE_LEN_MAX)
                    {                                                           // it's SAMSUNG
                        ANALYZE_PRINTF_4 ("protocol = SAMSUNG, start bit timings: pulse: %3d - %3d, pause: %3d - %3d\n",
                                        SAMSUNG_START_BIT_PULSE_LEN_MIN, SAMSUNG_START_BIT_PULSE_LEN_MAX,
                                        SAMSUNG_START_BIT_PAUSE_LEN_MIN, SAMSUNG_START_BIT_PAUSE_LEN_MAX);
                        irmp_param_p = (IRMP_PARAMETER *) &samsung_param;
                    }
                    else
#endif // IRMP_SUPPORT_SAMSUNG_PROTOCOL == 1

#if IRMP_SUPPORT_SAMSUNGAH_PROTOCOL == 1
                    if (irmp_pulse_time >= SAMSUNGAH_START_BIT_PULSE_LEN_MIN && irmp_pulse_time <= SAMSUNGAH_START_BIT_PULSE_LEN_MAX &&
                        irmp_pause_time >= SAMSUNGAH_START_BIT_PAUSE_LEN_MIN && irmp_pause_time <= SAMSUNGAH_START_BIT_PAUSE_LEN_MAX)
                    {                                                           // it's SAMSUNGAH
                        ANALYZE_PRINTF_4 ("protocol = SAMSUNGAH, start bit timings: pulse: %3d - %3d, pause: %3d - %3d\n",
                                        SAMSUNGAH_START_BIT_PULSE_LEN_MIN, SAMSUNGAH_START_BIT_PULSE_LEN_MAX,
                                        SAMSUNGAH_START_BIT_PAUSE_LEN_MIN, SAMSUNGAH_START_BIT_PAUSE_LEN_MAX);
                        irmp_param_p = (IRMP_PARAMETER *) &samsungah_param;
                    }
                    else
#endif // IRMP_SUPPORT_SAMSUNGAH_PROTOCOL == 1

#if IRMP_SUPPORT_MATSUSHITA_PROTOCOL == 1
                    if (irmp_pulse_time >= MATSUSHITA_START_BIT_PULSE_LEN_MIN && irmp_pulse_time <= MATSUSHITA_START_BIT_PULSE_LEN_MAX &&
                        irmp_pause_time >= MATSUSHITA_START_BIT_PAUSE_LEN_MIN && irmp_pause_time <= MATSUSHITA_START_BIT_PAUSE_LEN_MAX)
                    {                                                           // it's MATSUSHITA
                        ANALYZE_PRINTF_4 ("protocol = MATSUSHITA, start bit timings: pulse: %3d - %3d, pause: %3d - %3d\n",
                                        MATSUSHITA_START_BIT_PULSE_LEN_MIN, MATSUSHITA_START_BIT_PULSE_LEN_MAX,
                                        MATSUSHITA_START_BIT_PAUSE_LEN_MIN, MATSUSHITA_START_BIT_PAUSE_LEN_MAX);
                        irmp_param_p = (IRMP_PARAMETER *) &matsushita_param;
                    }
                    else
#endif // IRMP_SUPPORT_MATSUSHITA_PROTOCOL == 1

#if IRMP_SUPPORT_KASEIKYO_PROTOCOL == 1
                    if (irmp_pulse_time >= KASEIKYO_START_BIT_PULSE_LEN_MIN && irmp_pulse_time <= KASEIKYO_START_BIT_PULSE_LEN_MAX &&
                        irmp_pause_time >= KASEIKYO_START_BIT_PAUSE_LEN_MIN && irmp_pause_time <= KASEIKYO_START_BIT_PAUSE_LEN_MAX)
                    {                                                           // it's KASEIKYO
                        ANALYZE_PRINTF_4 ("protocol = KASEIKYO, start bit timings: pulse: %3d - %3d, pause: %3d - %3d\n",
                                        KASEIKYO_START_BIT_PULSE_LEN_MIN, KASEIKYO_START_BIT_PULSE_LEN_MAX,
                                        KASEIKYO_START_BIT_PAUSE_LEN_MIN, KASEIKYO_START_BIT_PAUSE_LEN_MAX);
                        irmp_param_p = (IRMP_PARAMETER *) &kaseikyo_param;
                    }
                    else
#endif // IRMP_SUPPORT_KASEIKYO_PROTOCOL == 1

#if IRMP_SUPPORT_PANASONIC_PROTOCOL == 1
                    if (irmp_pulse_time >= PANASONIC_START_BIT_PULSE_LEN_MIN && irmp_pulse_time <= PANASONIC_START_BIT_PULSE_LEN_MAX &&
                        irmp_pause_time >= PANASONIC_START_BIT_PAUSE_LEN_MIN && irmp_pause_time <= PANASONIC_START_BIT_PAUSE_LEN_MAX)
                    {                                                           // it's PANASONIC
                        ANALYZE_PRINTF_4 ("protocol = PANASONIC, start bit timings: pulse: %3d - %3d, pause: %3d - %3d\n",
                                        PANASONIC_START_BIT_PULSE_LEN_MIN, PANASONIC_START_BIT_PULSE_LEN_MAX,
                                        PANASONIC_START_BIT_PAUSE_LEN_MIN, PANASONIC_START_BIT_PAUSE_LEN_MAX);
                        irmp_param_p = (IRMP_PARAMETER *) &panasonic_param;
                    }
                    else
#endif // IRMP_SUPPORT_PANASONIC_PROTOCOL == 1

#if IRMP_SUPPORT_MITSU_HEAVY_PROTOCOL == 1
                    if (irmp_pulse_time >= MITSU_HEAVY_START_BIT_PULSE_LEN_MIN && irmp_pulse_time <= MITSU_HEAVY_START_BIT_PULSE_LEN_MAX &&
                        irmp_pause_time >= MITSU_HEAVY_START_BIT_PAUSE_LEN_MIN && irmp_pause_time <= MITSU_HEAVY_START_BIT_PAUSE_LEN_MAX)
                    {                                                           // it's MITSU_HEAVY
                        ANALYZE_PRINTF_4 ("protocol = MITSU_HEAVY, start bit timings: pulse: %3d - %3d, pause: %3d - %3d\n",
                                        MITSU_HEAVY_START_BIT_PULSE_LEN_MIN, MITSU_HEAVY_START_BIT_PULSE_LEN_MAX,
                                        MITSU_HEAVY_START_BIT_PAUSE_LEN_MIN, MITSU_HEAVY_START_BIT_PAUSE_LEN_MAX);
                        irmp_param_p = (IRMP_PARAMETER *) &mitsu_heavy_param;
                    }
                    else
#endif // IRMP_SUPPORT_MITSU_HEAVY_PROTOCOL == 1

#if IRMP_SUPPORT_VINCENT_PROTOCOL == 1
                    if (irmp_pulse_time >= VINCENT_START_BIT_PULSE_LEN_MIN && irmp_pulse_time <= VINCENT_START_BIT_PULSE_LEN_MAX &&
                        irmp_pause_time >= VINCENT_START_BIT_PAUSE_LEN_MIN && irmp_pause_time <= VINCENT_START_BIT_PAUSE_LEN_MAX)
                    {                                                           // it's VINCENT
                        ANALYZE_PRINTF_4 ("protocol = VINCENT, start bit timings: pulse: %3d - %3d, pause: %3d - %3d\n",
                                        VINCENT_START_BIT_PULSE_LEN_MIN, VINCENT_START_BIT_PULSE_LEN_MAX,
                                        VINCENT_START_BIT_PAUSE_LEN_MIN, VINCENT_START_BIT_PAUSE_LEN_MAX);
                        irmp_param_p = (IRMP_PARAMETER *) &vincent_param;
                    }
                    else
#endif // IRMP_SUPPORT_VINCENT_PROTOCOL == 1

#if IRMP_SUPPORT_METZ_PROTOCOL == 1
                    if (irmp_pulse_time >= METZ_START_BIT_PULSE_LEN_MIN && irmp_pulse_time <= METZ_START_BIT_PULSE_LEN_MAX &&
                        irmp_pause_time >= METZ_START_BIT_PAUSE_LEN_MIN && irmp_pause_time <= METZ_START_BIT_PAUSE_LEN_MAX)
                    {
                        ANALYZE_PRINTF_4 ("protocol = METZ, start bit timings: pulse: %3d - %3d, pause: %3d - %3d\n",
                                        METZ_START_BIT_PULSE_LEN_MIN, METZ_START_BIT_PULSE_LEN_MAX,
                                        METZ_START_BIT_PAUSE_LEN_MIN, METZ_START_BIT_PAUSE_LEN_MAX);
                        irmp_param_p = (IRMP_PARAMETER *) &metz_param;
                    }
                    else
#endif // IRMP_SUPPORT_METZ_PROTOCOL == 1

#if IRMP_SUPPORT_RADIO1_PROTOCOL == 1
                    if (irmp_pulse_time >= RADIO1_START_BIT_PULSE_LEN_MIN && irmp_pulse_time <= RADIO1_START_BIT_PULSE_LEN_MAX &&
                        irmp_pause_time >= RADIO1_START_BIT_PAUSE_LEN_MIN && irmp_pause_time <= RADIO1_START_BIT_PAUSE_LEN_MAX)
                    {
                        ANALYZE_PRINTF_4 ("protocol = RADIO1, start bit timings: pulse: %3d - %3d, pause: %3d - %3d\n",
                                        RADIO1_START_BIT_PULSE_LEN_MIN, RADIO1_START_BIT_PULSE_LEN_MAX,
                                        RADIO1_START_BIT_PAUSE_LEN_MIN, RADIO1_START_BIT_PAUSE_LEN_MAX);
                        irmp_param_p = (IRMP_PARAMETER *) &radio1_param;
                    }
                    else
#endif // IRMP_SUPPORT_RRADIO1_PROTOCOL == 1

#if IRMP_SUPPORT_RECS80_PROTOCOL == 1
                    if (irmp_pulse_time >= RECS80_START_BIT_PULSE_LEN_MIN && irmp_pulse_time <= RECS80_START_BIT_PULSE_LEN_MAX &&
                        irmp_pause_time >= RECS80_START_BIT_PAUSE_LEN_MIN && irmp_pause_time <= RECS80_START_BIT_PAUSE_LEN_MAX)
                    {                                                           // it's RECS80
                        ANALYZE_PRINTF_4 ("protocol = RECS80, start bit timings: pulse: %3d - %3d, pause: %3d - %3d\n",
                                        RECS80_START_BIT_PULSE_LEN_MIN, RECS80_START_BIT_PULSE_LEN_MAX,
                                        RECS80_START_BIT_PAUSE_LEN_MIN, RECS80_START_BIT_PAUSE_LEN_MAX);
                        irmp_param_p = (IRMP_PARAMETER *) &recs80_param;
                    }
                    else
#endif // IRMP_SUPPORT_RECS80_PROTOCOL == 1

#if IRMP_SUPPORT_S100_PROTOCOL == 1
                    if (((irmp_pulse_time >= S100_START_BIT_LEN_MIN     && irmp_pulse_time <= S100_START_BIT_LEN_MAX) ||
                         (irmp_pulse_time >= 2 * S100_START_BIT_LEN_MIN && irmp_pulse_time <= 2 * S100_START_BIT_LEN_MAX)) &&
                        ((irmp_pause_time >= S100_START_BIT_LEN_MIN     && irmp_pause_time <= S100_START_BIT_LEN_MAX) ||
                         (irmp_pause_time >= 2 * S100_START_BIT_LEN_MIN && irmp_pause_time <= 2 * S100_START_BIT_LEN_MAX)))
                    {                                                           // it's S100
                        ANALYZE_PRINTF_4("protocol = S100, start bit timings: pulse: %3d - %3d, pause: %3d - %3d ",
                                        S100_START_BIT_LEN_MIN, S100_START_BIT_LEN_MAX,
                                        2 * S100_START_BIT_LEN_MIN, 2 * S100_START_BIT_LEN_MAX);
                        ANALYZE_PRINTF_4("or pulse: %3d - %3d, pause: %3d - %3d\n",
                                        S100_START_BIT_LEN_MIN, S100_START_BIT_LEN_MAX,
                                        2 * S100_START_BIT_LEN_MIN, 2 * S100_START_BIT_LEN_MAX);

                        irmp_param_p = (IRMP_PARAMETER *) &s100_param;
                        last_pause = irmp_pause_time;

                        if ((irmp_pulse_time > S100_START_BIT_LEN_MAX && irmp_pulse_time <= 2 * S100_START_BIT_LEN_MAX) ||
                            (irmp_pause_time > S100_START_BIT_LEN_MAX && irmp_pause_time <= 2 * S100_START_BIT_LEN_MAX))
                        {
                          last_value  = 0;
                          rc5_cmd_bit6 = 1<<6;
                        }
                        else
                        {
                          last_value  = 1;
                        }
                    }
                    else
#endif // IRMP_SUPPORT_S100_PROTOCOL == 1

#if IRMP_SUPPORT_RC5_PROTOCOL == 1
                    if (((irmp_pulse_time >= RC5_START_BIT_LEN_MIN     && irmp_pulse_time <= RC5_START_BIT_LEN_MAX) ||
                         (irmp_pulse_time >= 2 * RC5_START_BIT_LEN_MIN && irmp_pulse_time <= 2 * RC5_START_BIT_LEN_MAX)) &&
                        ((irmp_pause_time >= RC5_START_BIT_LEN_MIN     && irmp_pause_time <= RC5_START_BIT_LEN_MAX) ||
                         (irmp_pause_time >= 2 * RC5_START_BIT_LEN_MIN && irmp_pause_time <= 2 * RC5_START_BIT_LEN_MAX)))
                    {                                                           // it's RC5
#if IRMP_SUPPORT_FDC_PROTOCOL == 1
                        if (irmp_pulse_time >= FDC_START_BIT_PULSE_LEN_MIN && irmp_pulse_time <= FDC_START_BIT_PULSE_LEN_MAX &&
                            irmp_pause_time >= FDC_START_BIT_PAUSE_LEN_MIN && irmp_pause_time <= FDC_START_BIT_PAUSE_LEN_MAX)
                        {
                            ANALYZE_PRINT ("protocol = RC5 or FDC\n");
                            ANALYZE_PRINTF_4 ("FDC start bit timings: pulse: %3d - %3d, pause: %3d - %3d\n",
                                            FDC_START_BIT_PULSE_LEN_MIN, FDC_START_BIT_PULSE_LEN_MAX,
                                            FDC_START_BIT_PAUSE_LEN_MIN, FDC_START_BIT_PAUSE_LEN_MAX);
                            ANALYZE_PRINTF_4 ("RC5 start bit timings: pulse: %3d - %3d, pause: %3d - %3d\n",
                                            RC5_START_BIT_LEN_MIN, RC5_START_BIT_LEN_MAX,
                                            RC5_START_BIT_LEN_MIN, RC5_START_BIT_LEN_MAX);
                            memcpy_P (&irmp_param2, &fdc_param, sizeof (IRMP_PARAMETER));
                        }
                        else
#endif // IRMP_SUPPORT_FDC_PROTOCOL == 1

#if IRMP_SUPPORT_RCCAR_PROTOCOL == 1
                        if (irmp_pulse_time >= RCCAR_START_BIT_PULSE_LEN_MIN && irmp_pulse_time <= RCCAR_START_BIT_PULSE_LEN_MAX &&
                            irmp_pause_time >= RCCAR_START_BIT_PAUSE_LEN_MIN && irmp_pause_time <= RCCAR_START_BIT_PAUSE_LEN_MAX)
                        {
                            ANALYZE_PRINT ("protocol = RC5 or RCCAR\n");
                            ANALYZE_PRINTF_4 ("RCCAR start bit timings: pulse: %3d - %3d, pause: %3d - %3d\n",
                                            RCCAR_START_BIT_PULSE_LEN_MIN, RCCAR_START_BIT_PULSE_LEN_MAX,
                                            RCCAR_START_BIT_PAUSE_LEN_MIN, RCCAR_START_BIT_PAUSE_LEN_MAX);
                            ANALYZE_PRINTF_4 ("RC5 start bit timings: pulse: %3d - %3d, pause: %3d - %3d\n",
                                            RC5_START_BIT_LEN_MIN, RC5_START_BIT_LEN_MAX,
                                            RC5_START_BIT_LEN_MIN, RC5_START_BIT_LEN_MAX);
                            memcpy_P (&irmp_param2, &rccar_param, sizeof (IRMP_PARAMETER));
                        }
                        else
#endif // IRMP_SUPPORT_RCCAR_PROTOCOL == 1
                        {
                            ANALYZE_PRINTF_4 ("protocol = RC5, start bit timings: pulse: %3d - %3d, pause: %3d - %3d",
                                            RC5_START_BIT_LEN_MIN, RC5_START_BIT_LEN_MAX,
                                            2 * RC5_START_BIT_LEN_MIN, 2 * RC5_START_BIT_LEN_MAX);
                            ANALYZE_PRINTF_4("or pulse: % 3d - % 3d, pause : % 3d - % 3d\n",
                                            RC5_START_BIT_LEN_MIN, RC5_START_BIT_LEN_MAX,
                                            2 * RC5_START_BIT_LEN_MIN, 2 * RC5_START_BIT_LEN_MAX);
                        }

                        irmp_param_p = (IRMP_PARAMETER *) &rc5_param;
                        last_pause = irmp_pause_time;

                        if ((irmp_pulse_time > RC5_START_BIT_LEN_MAX && irmp_pulse_time <= 2 * RC5_START_BIT_LEN_MAX) ||
                            (irmp_pause_time > RC5_START_BIT_LEN_MAX && irmp_pause_time <= 2 * RC5_START_BIT_LEN_MAX))
                        {
                            last_value  = 0;
                            rc5_cmd_bit6 = 1<<6;
                        }
                        else
                        {
                            last_value  = 1;
                        }
                    }
                    else
#endif // IRMP_SUPPORT_RC5_PROTOCOL == 1

#if IRMP_SUPPORT_RCII_PROTOCOL == 1
                    if ((irmp_pulse_time >= RCII_START_BIT_PULSE_LEN_MIN && irmp_pulse_time <= RCII_START_BIT_PULSE_LEN_MAX) &&
                        (irmp_pause_time >= RCII_START_BIT_PAUSE_LEN_MIN && irmp_pause_time <= RCII_START_BIT_PAUSE_LEN_MAX))
                    {                                                           // it's RCII
                        ANALYZE_PRINTF_4 ("protocol = RCII, start bit timings: pulse: %3d - %3d, pause: %3d - %3d\n",
                                        RCII_START_BIT_PULSE_LEN_MIN, RCII_START_BIT_PULSE_LEN_MAX,
                                        RCII_START_BIT_PAUSE_LEN_MIN, RCII_START_BIT_PAUSE_LEN_MAX);
                        irmp_param_p = (IRMP_PARAMETER *) &rcii_param;
                        last_pause = irmp_pause_time;
                        waiting_for_2nd_pulse = 1;
                        last_value  = 1;
                    }
                    else
#endif // IRMP_SUPPORT_RCII_PROTOCOL == 1

#if IRMP_SUPPORT_DENON_PROTOCOL == 1
                    if ( (irmp_pulse_time >= DENON_PULSE_LEN_MIN && irmp_pulse_time <= DENON_PULSE_LEN_MAX) &&
                        ((irmp_pause_time >= DENON_1_PAUSE_LEN_MIN && irmp_pause_time <= DENON_1_PAUSE_LEN_MAX) ||
                         (irmp_pause_time >= DENON_0_PAUSE_LEN_MIN && irmp_pause_time <= DENON_0_PAUSE_LEN_MAX)))
                    {                                                           // it's DENON
                        ANALYZE_PRINTF_2("protocol = DENON, start bit timings: pulse: %3d - %3d, ",
                                        DENON_PULSE_LEN_MIN, DENON_PULSE_LEN_MAX);
                        ANALYZE_PRINTF_4("pause: %3d - %3d or %3d - %3d\n",
                                        DENON_1_PAUSE_LEN_MIN, DENON_1_PAUSE_LEN_MAX,
                                        DENON_0_PAUSE_LEN_MIN, DENON_0_PAUSE_LEN_MAX);
                        irmp_param_p = (IRMP_PARAMETER *) &denon_param;
                    }
                    else
#endif // IRMP_SUPPORT_DENON_PROTOCOL == 1

#if IRMP_SUPPORT_THOMSON_PROTOCOL == 1
                    if ( (irmp_pulse_time >= THOMSON_PULSE_LEN_MIN && irmp_pulse_time <= THOMSON_PULSE_LEN_MAX) &&
                        ((irmp_pause_time >= THOMSON_1_PAUSE_LEN_MIN && irmp_pause_time <= THOMSON_1_PAUSE_LEN_MAX) ||
                         (irmp_pause_time >= THOMSON_0_PAUSE_LEN_MIN && irmp_pause_time <= THOMSON_0_PAUSE_LEN_MAX)))
                    {                                                           // it's THOMSON
                        ANALYZE_PRINTF_2("protocol = THOMSON, start bit timings: pulse: %3d - %3d",
                                        THOMSON_PULSE_LEN_MIN, THOMSON_PULSE_LEN_MAX);
                        ANALYZE_PRINTF_4("pause: %3d - %3d or %3d - %3d\n",
                                        THOMSON_1_PAUSE_LEN_MIN, THOMSON_1_PAUSE_LEN_MAX,
                                        THOMSON_0_PAUSE_LEN_MIN, THOMSON_0_PAUSE_LEN_MAX);
                        irmp_param_p = (IRMP_PARAMETER *) &thomson_param;
                    }
                    else
#endif // IRMP_SUPPORT_THOMSON_PROTOCOL == 1

#if IRMP_SUPPORT_BOSE_PROTOCOL == 1
                    if (irmp_pulse_time >= BOSE_START_BIT_PULSE_LEN_MIN && irmp_pulse_time <= BOSE_START_BIT_PULSE_LEN_MAX &&
                        irmp_pause_time >= BOSE_START_BIT_PAUSE_LEN_MIN && irmp_pause_time <= BOSE_START_BIT_PAUSE_LEN_MAX)
                    {
                        ANALYZE_PRINTF_4 ("protocol = BOSE, start bit timings: pulse: %3d - %3d, pause: %3d - %3d\n",
                                        BOSE_START_BIT_PULSE_LEN_MIN, BOSE_START_BIT_PULSE_LEN_MAX,
                                        BOSE_START_BIT_PAUSE_LEN_MIN, BOSE_START_BIT_PAUSE_LEN_MAX);
                        irmp_param_p = (IRMP_PARAMETER *) &bose_param;
                    }
                    else
#endif // IRMP_SUPPORT_BOSE_PROTOCOL == 1

#if IRMP_SUPPORT_RC6_PROTOCOL == 1
                    if (irmp_pulse_time >= RC6_START_BIT_PULSE_LEN_MIN && irmp_pulse_time <= RC6_START_BIT_PULSE_LEN_MAX &&
                        irmp_pause_time >= RC6_START_BIT_PAUSE_LEN_MIN && irmp_pause_time <= RC6_START_BIT_PAUSE_LEN_MAX)
                    {                                                           // it's RC6
                        ANALYZE_PRINTF_4 ("protocol = RC6, start bit timings: pulse: %3d - %3d, pause: %3d - %3d\n",
                                        RC6_START_BIT_PULSE_LEN_MIN, RC6_START_BIT_PULSE_LEN_MAX,
                                        RC6_START_BIT_PAUSE_LEN_MIN, RC6_START_BIT_PAUSE_LEN_MAX);
                        irmp_param_p = (IRMP_PARAMETER *) &rc6_param;
                        last_pause = 0;
                        last_value = 1;
                    }
                    else
#endif // IRMP_SUPPORT_RC6_PROTOCOL == 1

#if IRMP_SUPPORT_RECS80EXT_PROTOCOL == 1
                    if (irmp_pulse_time >= RECS80EXT_START_BIT_PULSE_LEN_MIN && irmp_pulse_time <= RECS80EXT_START_BIT_PULSE_LEN_MAX &&
                        irmp_pause_time >= RECS80EXT_START_BIT_PAUSE_LEN_MIN && irmp_pause_time <= RECS80EXT_START_BIT_PAUSE_LEN_MAX)
                    {                                                           // it's RECS80EXT
                        ANALYZE_PRINTF_4 ("protocol = RECS80EXT, start bit timings: pulse: %3d - %3d, pause: %3d - %3d\n",
                                        RECS80EXT_START_BIT_PULSE_LEN_MIN, RECS80EXT_START_BIT_PULSE_LEN_MAX,
                                        RECS80EXT_START_BIT_PAUSE_LEN_MIN, RECS80EXT_START_BIT_PAUSE_LEN_MAX);
                        irmp_param_p = (IRMP_PARAMETER *) &recs80ext_param;
                    }
                    else
#endif // IRMP_SUPPORT_RECS80EXT_PROTOCOL == 1

#if IRMP_SUPPORT_NUBERT_PROTOCOL == 1
                    if (irmp_pulse_time >= NUBERT_START_BIT_PULSE_LEN_MIN && irmp_pulse_time <= NUBERT_START_BIT_PULSE_LEN_MAX &&
                        irmp_pause_time >= NUBERT_START_BIT_PAUSE_LEN_MIN && irmp_pause_time <= NUBERT_START_BIT_PAUSE_LEN_MAX)
                    {                                                           // it's NUBERT
                        ANALYZE_PRINTF_4 ("protocol = NUBERT, start bit timings: pulse: %3d - %3d, pause: %3d - %3d\n",
                                        NUBERT_START_BIT_PULSE_LEN_MIN, NUBERT_START_BIT_PULSE_LEN_MAX,
                                        NUBERT_START_BIT_PAUSE_LEN_MIN, NUBERT_START_BIT_PAUSE_LEN_MAX);
                        irmp_param_p = (IRMP_PARAMETER *) &nubert_param;
                    }
                    else
#endif // IRMP_SUPPORT_NUBERT_PROTOCOL == 1

#if IRMP_SUPPORT_FAN_PROTOCOL == 1
                    if (irmp_pulse_time >= FAN_START_BIT_PULSE_LEN_MIN && irmp_pulse_time <= FAN_START_BIT_PULSE_LEN_MAX &&
                        irmp_pause_time >= FAN_START_BIT_PAUSE_LEN_MIN && irmp_pause_time <= FAN_START_BIT_PAUSE_LEN_MAX)
                    {                                                           // it's FAN
                        ANALYZE_PRINTF_4 ("protocol = FAN, start bit timings: pulse: %3d - %3d, pause: %3d - %3d\n",
                                        FAN_START_BIT_PULSE_LEN_MIN, FAN_START_BIT_PULSE_LEN_MAX,
                                        FAN_START_BIT_PAUSE_LEN_MIN, FAN_START_BIT_PAUSE_LEN_MAX);
                        irmp_param_p = (IRMP_PARAMETER *) &fan_param;
                    }
                    else
#endif // IRMP_SUPPORT_FAN_PROTOCOL == 1

#if IRMP_SUPPORT_SPEAKER_PROTOCOL == 1
                    if (irmp_pulse_time >= SPEAKER_START_BIT_PULSE_LEN_MIN && irmp_pulse_time <= SPEAKER_START_BIT_PULSE_LEN_MAX &&
                        irmp_pause_time >= SPEAKER_START_BIT_PAUSE_LEN_MIN && irmp_pause_time <= SPEAKER_START_BIT_PAUSE_LEN_MAX)
                    {                                                           // it's SPEAKER
                        ANALYZE_PRINTF_4 ("protocol = SPEAKER, start bit timings: pulse: %3d - %3d, pause: %3d - %3d\n",
                                        SPEAKER_START_BIT_PULSE_LEN_MIN, SPEAKER_START_BIT_PULSE_LEN_MAX,
                                        SPEAKER_START_BIT_PAUSE_LEN_MIN, SPEAKER_START_BIT_PAUSE_LEN_MAX);
                        irmp_param_p = (IRMP_PARAMETER *) &speaker_param;
                    }
                    else
#endif // IRMP_SUPPORT_SPEAKER_PROTOCOL == 1

#if IRMP_SUPPORT_BANG_OLUFSEN_PROTOCOL == 1
                    if (irmp_pulse_time >= BANG_OLUFSEN_START_BIT1_PULSE_LEN_MIN && irmp_pulse_time <= BANG_OLUFSEN_START_BIT1_PULSE_LEN_MAX &&
                        irmp_pause_time >= BANG_OLUFSEN_START_BIT1_PAUSE_LEN_MIN && irmp_pause_time <= BANG_OLUFSEN_START_BIT1_PAUSE_LEN_MAX)
                    {                                                           // it's BANG_OLUFSEN
                        ANALYZE_PRINT ("protocol = BANG_OLUFSEN\n");
                        ANALYZE_PRINTF_4 ("start bit 1 timings: pulse: %3d - %3d, pause: %3d - %3d\n",
                                        BANG_OLUFSEN_START_BIT1_PULSE_LEN_MIN, BANG_OLUFSEN_START_BIT1_PULSE_LEN_MAX,
                                        BANG_OLUFSEN_START_BIT1_PAUSE_LEN_MIN, BANG_OLUFSEN_START_BIT1_PAUSE_LEN_MAX);
                        ANALYZE_PRINTF_4 ("start bit 2 timings: pulse: %3d - %3d, pause: %3d - %3d\n",
                                        BANG_OLUFSEN_START_BIT2_PULSE_LEN_MIN, BANG_OLUFSEN_START_BIT2_PULSE_LEN_MAX,
                                        BANG_OLUFSEN_START_BIT2_PAUSE_LEN_MIN, BANG_OLUFSEN_START_BIT2_PAUSE_LEN_MAX);
                        ANALYZE_PRINTF_4 ("start bit 3 timings: pulse: %3d - %3d, pause: %3d - %3d\n",
                                        BANG_OLUFSEN_START_BIT3_PULSE_LEN_MIN, BANG_OLUFSEN_START_BIT3_PULSE_LEN_MAX,
                                        BANG_OLUFSEN_START_BIT3_PAUSE_LEN_MIN, BANG_OLUFSEN_START_BIT3_PAUSE_LEN_MAX);
                        ANALYZE_PRINTF_4 ("start bit 4 timings: pulse: %3d - %3d, pause: %3d - %3d\n",
                                        BANG_OLUFSEN_START_BIT4_PULSE_LEN_MIN, BANG_OLUFSEN_START_BIT4_PULSE_LEN_MAX,
                                        BANG_OLUFSEN_START_BIT4_PAUSE_LEN_MIN, BANG_OLUFSEN_START_BIT4_PAUSE_LEN_MAX);
                        irmp_param_p = (IRMP_PARAMETER *) &bang_olufsen_param;
                        last_value = 0;
                    }
                    else
#endif // IRMP_SUPPORT_BANG_OLUFSEN_PROTOCOL == 1

#if IRMP_SUPPORT_GRUNDIG_NOKIA_IR60_PROTOCOL == 1
                    if (irmp_pulse_time >= GRUNDIG_NOKIA_IR60_START_BIT_LEN_MIN && irmp_pulse_time <= GRUNDIG_NOKIA_IR60_START_BIT_LEN_MAX &&
                        irmp_pause_time >= GRUNDIG_NOKIA_IR60_PRE_PAUSE_LEN_MIN && irmp_pause_time <= GRUNDIG_NOKIA_IR60_PRE_PAUSE_LEN_MAX)
                    {                                                           // it's GRUNDIG
                        ANALYZE_PRINTF_4 ("protocol = GRUNDIG, pre bit timings: pulse: %3d - %3d, pause: %3d - %3d\n",
                                        GRUNDIG_NOKIA_IR60_START_BIT_LEN_MIN, GRUNDIG_NOKIA_IR60_START_BIT_LEN_MAX,
                                        GRUNDIG_NOKIA_IR60_PRE_PAUSE_LEN_MIN, GRUNDIG_NOKIA_IR60_PRE_PAUSE_LEN_MAX);
                        irmp_param_p = (IRMP_PARAMETER *) &grundig_param;
                        last_pause = irmp_pause_time;
                        last_value  = 1;
                    }
                    else
#endif // IRMP_SUPPORT_GRUNDIG_NOKIA_IR60_PROTOCOL == 1

#if IRMP_SUPPORT_MERLIN_PROTOCOL == 1 // check MERLIN before RUWIDO!
                    if (irmp_pulse_time >= MERLIN_START_BIT_PULSE_LEN_MIN && irmp_pulse_time <= MERLIN_START_BIT_PULSE_LEN_MAX &&
                        irmp_pause_time >= MERLIN_START_BIT_PAUSE_LEN_MIN && irmp_pause_time <= MERLIN_START_BIT_PAUSE_LEN_MAX)
                    {                                                           // it's MERLIN
                        ANALYZE_PRINTF_4 ("protocol = MERLIN, start bit timings: pulse: %3d - %3d, pause: %3d - %3d\n",
                                        MERLIN_START_BIT_PULSE_LEN_MIN, MERLIN_START_BIT_PULSE_LEN_MAX,
                                        MERLIN_START_BIT_PAUSE_LEN_MIN, MERLIN_START_BIT_PAUSE_LEN_MAX);
                        irmp_param_p = (IRMP_PARAMETER *) &merlin_param;
                        last_pause = irmp_pause_time;
                        last_value = 1;
                    }
                    else
#endif // IRMP_SUPPORT_MERLIN_PROTOCOL == 1

#if IRMP_SUPPORT_SIEMENS_OR_RUWIDO_PROTOCOL == 1
                    if (((irmp_pulse_time >= SIEMENS_OR_RUWIDO_START_BIT_PULSE_LEN_MIN && irmp_pulse_time <= SIEMENS_OR_RUWIDO_START_BIT_PULSE_LEN_MAX) ||
                         (irmp_pulse_time >= 2 * SIEMENS_OR_RUWIDO_START_BIT_PULSE_LEN_MIN && irmp_pulse_time <= 2 * SIEMENS_OR_RUWIDO_START_BIT_PULSE_LEN_MAX)) &&
                        ((irmp_pause_time >= SIEMENS_OR_RUWIDO_START_BIT_PAUSE_LEN_MIN && irmp_pause_time <= SIEMENS_OR_RUWIDO_START_BIT_PAUSE_LEN_MAX) ||
                         (irmp_pause_time >= 2 * SIEMENS_OR_RUWIDO_START_BIT_PAUSE_LEN_MIN && irmp_pause_time <= 2 * SIEMENS_OR_RUWIDO_START_BIT_PAUSE_LEN_MAX)))
                    {                                                           // it's RUWIDO or SIEMENS
                        ANALYZE_PRINTF_4 ("protocol = RUWIDO, start bit timings: pulse: %3d - %3d or %3d - %3d, ",
                                          SIEMENS_OR_RUWIDO_START_BIT_PULSE_LEN_MIN,   SIEMENS_OR_RUWIDO_START_BIT_PULSE_LEN_MAX,
                                          2 * SIEMENS_OR_RUWIDO_START_BIT_PULSE_LEN_MIN, 2 * SIEMENS_OR_RUWIDO_START_BIT_PULSE_LEN_MAX);
                        ANALYZE_PRINTF_4 ("pause: %3d - %3d or %3d - %3d\n",
                                          SIEMENS_OR_RUWIDO_START_BIT_PAUSE_LEN_MIN,   SIEMENS_OR_RUWIDO_START_BIT_PAUSE_LEN_MAX,
                                          2 * SIEMENS_OR_RUWIDO_START_BIT_PAUSE_LEN_MIN, 2 * SIEMENS_OR_RUWIDO_START_BIT_PAUSE_LEN_MAX);
                        irmp_param_p = (IRMP_PARAMETER *) &ruwido_param;
                        last_pause = irmp_pause_time;
                        last_value  = 1;
                    }
                    else
#endif // IRMP_SUPPORT_SIEMENS_OR_RUWIDO_PROTOCOL == 1

#if IRMP_SUPPORT_FDC_PROTOCOL == 1
                    if (irmp_pulse_time >= FDC_START_BIT_PULSE_LEN_MIN && irmp_pulse_time <= FDC_START_BIT_PULSE_LEN_MAX &&
                        irmp_pause_time >= FDC_START_BIT_PAUSE_LEN_MIN && irmp_pause_time <= FDC_START_BIT_PAUSE_LEN_MAX)
                    {
                        ANALYZE_PRINTF_4 ("protocol = FDC, start bit timings: pulse: %3d - %3d, pause: %3d - %3d\n",
                                        FDC_START_BIT_PULSE_LEN_MIN, FDC_START_BIT_PULSE_LEN_MAX,
                                        FDC_START_BIT_PAUSE_LEN_MIN, FDC_START_BIT_PAUSE_LEN_MAX);
                        irmp_param_p = (IRMP_PARAMETER *) &fdc_param;
                    }
                    else
#endif // IRMP_SUPPORT_FDC_PROTOCOL == 1

#if IRMP_SUPPORT_RCCAR_PROTOCOL == 1
                    if (irmp_pulse_time >= RCCAR_START_BIT_PULSE_LEN_MIN && irmp_pulse_time <= RCCAR_START_BIT_PULSE_LEN_MAX &&
                        irmp_pause_time >= RCCAR_START_BIT_PAUSE_LEN_MIN && irmp_pause_time <= RCCAR_START_BIT_PAUSE_LEN_MAX)
                    {
                        ANALYZE_PRINTF_4 ("protocol = RCCAR, start bit timings: pulse: %3d - %3d, pause: %3d - %3d\n",
                                        RCCAR_START_BIT_PULSE_LEN_MIN, RCCAR_START_BIT_PULSE_LEN_MAX,
                                        RCCAR_START_BIT_PAUSE_LEN_MIN, RCCAR_START_BIT_PAUSE_LEN_MAX);
                        irmp_param_p = (IRMP_PARAMETER *) &rccar_param;
                    }
                    else
#endif // IRMP_SUPPORT_RCCAR_PROTOCOL == 1

#if IRMP_SUPPORT_KATHREIN_PROTOCOL == 1
                    if (irmp_pulse_time >= KATHREIN_START_BIT_PULSE_LEN_MIN && irmp_pulse_time <= KATHREIN_START_BIT_PULSE_LEN_MAX &&
                        irmp_pause_time >= KATHREIN_START_BIT_PAUSE_LEN_MIN && irmp_pause_time <= KATHREIN_START_BIT_PAUSE_LEN_MAX)
                    {                                                           // it's KATHREIN
                        ANALYZE_PRINTF_4 ("protocol = KATHREIN, start bit timings: pulse: %3d - %3d, pause: %3d - %3d\n",
                                        KATHREIN_START_BIT_PULSE_LEN_MIN, KATHREIN_START_BIT_PULSE_LEN_MAX,
                                        KATHREIN_START_BIT_PAUSE_LEN_MIN, KATHREIN_START_BIT_PAUSE_LEN_MAX);
                        irmp_param_p = (IRMP_PARAMETER *) &kathrein_param;
                    }
                    else
#endif // IRMP_SUPPORT_KATHREIN_PROTOCOL == 1

#if IRMP_SUPPORT_NETBOX_PROTOCOL == 1
                    if (irmp_pulse_time >= NETBOX_START_BIT_PULSE_LEN_MIN && irmp_pulse_time <= NETBOX_START_BIT_PULSE_LEN_MAX &&
                        irmp_pause_time >= NETBOX_START_BIT_PAUSE_LEN_MIN && irmp_pause_time <= NETBOX_START_BIT_PAUSE_LEN_MAX)
                    {                                                           // it's NETBOX
                        ANALYZE_PRINTF_4 ("protocol = NETBOX, start bit timings: pulse: %3d - %3d, pause: %3d - %3d\n",
                                        NETBOX_START_BIT_PULSE_LEN_MIN, NETBOX_START_BIT_PULSE_LEN_MAX,
                                        NETBOX_START_BIT_PAUSE_LEN_MIN, NETBOX_START_BIT_PAUSE_LEN_MAX);
                        irmp_param_p = (IRMP_PARAMETER *) &netbox_param;
                    }
                    else
#endif // IRMP_SUPPORT_NETBOX_PROTOCOL == 1

#if IRMP_SUPPORT_LEGO_PROTOCOL == 1
                    if (irmp_pulse_time >= LEGO_START_BIT_PULSE_LEN_MIN && irmp_pulse_time <= LEGO_START_BIT_PULSE_LEN_MAX &&
                        irmp_pause_time >= LEGO_START_BIT_PAUSE_LEN_MIN && irmp_pause_time <= LEGO_START_BIT_PAUSE_LEN_MAX)
                    {
                        ANALYZE_PRINTF_4 ("protocol = LEGO, start bit timings: pulse: %3d - %3d, pause: %3d - %3d\n",
                                        LEGO_START_BIT_PULSE_LEN_MIN, LEGO_START_BIT_PULSE_LEN_MAX,
                                        LEGO_START_BIT_PAUSE_LEN_MIN, LEGO_START_BIT_PAUSE_LEN_MAX);
                        irmp_param_p = (IRMP_PARAMETER *) &lego_param;
                    }
                    else
#endif // IRMP_SUPPORT_LEGO_PROTOCOL == 1

#if IRMP_SUPPORT_IRMP16_PROTOCOL == 1
                    if (irmp_pulse_time >= IRMP16_START_BIT_PULSE_LEN_MIN && irmp_pulse_time <= IRMP16_START_BIT_PULSE_LEN_MAX &&
                        irmp_pause_time >= IRMP16_START_BIT_PAUSE_LEN_MIN && irmp_pause_time <= IRMP16_START_BIT_PAUSE_LEN_MAX)
                    {
                        ANALYZE_PRINTF_4 ("protocol = IRMP16, start bit timings: pulse: %3d - %3d, pause: %3d - %3d\n",
                                        IRMP16_START_BIT_PULSE_LEN_MIN, IRMP16_START_BIT_PULSE_LEN_MAX,
                                        IRMP16_START_BIT_PAUSE_LEN_MIN, IRMP16_START_BIT_PAUSE_LEN_MAX);
                        irmp_param_p = (IRMP_PARAMETER *) &irmp16_param;
                    }
                    else
#endif // IRMP_SUPPORT_IRMP16_PROTOCOL == 1

#if IRMP_SUPPORT_GREE_PROTOCOL == 1
                    if (irmp_pulse_time >= GREE_START_BIT_PULSE_LEN_MIN && irmp_pulse_time <= GREE_START_BIT_PULSE_LEN_MAX &&
                        irmp_pause_time >= GREE_START_BIT_PAUSE_LEN_MIN && irmp_pause_time <= GREE_START_BIT_PAUSE_LEN_MAX)
                    {
                        ANALYZE_PRINTF_4 ("protocol = GREE, start bit timings: pulse: %3d - %3d, pause: %3d - %3d\n",
                                        GREE_START_BIT_PULSE_LEN_MIN, GREE_START_BIT_PULSE_LEN_MAX,
                                        GREE_START_BIT_PAUSE_LEN_MIN, GREE_START_BIT_PAUSE_LEN_MAX);
                        irmp_param_p = (IRMP_PARAMETER *) &gree_param;
                    }
                    else
#endif // IRMP_SUPPORT_GREE_PROTOCOL == 1

#if IRMP_SUPPORT_A1TVBOX_PROTOCOL == 1
                    if (irmp_pulse_time >= A1TVBOX_START_BIT_PULSE_LEN_MIN && irmp_pulse_time <= A1TVBOX_START_BIT_PULSE_LEN_MAX &&
                        irmp_pause_time >= A1TVBOX_START_BIT_PAUSE_LEN_MIN && irmp_pause_time <= A1TVBOX_START_BIT_PAUSE_LEN_MAX)
                    {                                                           // it's A1TVBOX
                        ANALYZE_PRINTF_4 ("protocol = A1TVBOX, start bit timings: pulse: %3d - %3d, pause: %3d - %3d\n",
                                        A1TVBOX_START_BIT_PULSE_LEN_MIN, A1TVBOX_START_BIT_PULSE_LEN_MAX,
                                        A1TVBOX_START_BIT_PAUSE_LEN_MIN, A1TVBOX_START_BIT_PAUSE_LEN_MAX);
                        irmp_param_p = (IRMP_PARAMETER *) &a1tvbox_param;
                        last_pause = 0;
                        last_value = 1;
                    }
                    else
#endif // IRMP_SUPPORT_A1TVBOX_PROTOCOL == 1

#if IRMP_SUPPORT_ORTEK_PROTOCOL == 1
                    if (irmp_pulse_time >= ORTEK_START_BIT_PULSE_LEN_MIN && irmp_pulse_time <= ORTEK_START_BIT_PULSE_LEN_MAX &&
                        irmp_pause_time >= ORTEK_START_BIT_PAUSE_LEN_MIN && irmp_pause_time <= ORTEK_START_BIT_PAUSE_LEN_MAX)
                    {                                                           // it's ORTEK (Hama)
                        ANALYZE_PRINTF_4 ("protocol = ORTEK, start bit timings: pulse: %3d - %3d, pause: %3d - %3d\n",
                                        ORTEK_START_BIT_PULSE_LEN_MIN, ORTEK_START_BIT_PULSE_LEN_MAX,
                                        ORTEK_START_BIT_PAUSE_LEN_MIN, ORTEK_START_BIT_PAUSE_LEN_MAX);
                        irmp_param_p = (IRMP_PARAMETER *) &ortek_param;
                        last_pause  = 0;
                        last_value  = 1;
                        parity      = 0;
                    }
                    else
#endif // IRMP_SUPPORT_ORTEK_PROTOCOL == 1

#if IRMP_SUPPORT_RCMM_PROTOCOL == 1
                    if (irmp_pulse_time >= RCMM32_START_BIT_PULSE_LEN_MIN && irmp_pulse_time <= RCMM32_START_BIT_PULSE_LEN_MAX &&
                        irmp_pause_time >= RCMM32_START_BIT_PAUSE_LEN_MIN && irmp_pause_time <= RCMM32_START_BIT_PAUSE_LEN_MAX)
                    {                                                           // it's RCMM
                        ANALYZE_PRINTF_4 ("protocol = RCMM, start bit timings: pulse: %3d - %3d, pause: %3d - %3d\n",
                                        RCMM32_START_BIT_PULSE_LEN_MIN, RCMM32_START_BIT_PULSE_LEN_MAX,
                                        RCMM32_START_BIT_PAUSE_LEN_MIN, RCMM32_START_BIT_PAUSE_LEN_MAX);
                        irmp_param_p = (IRMP_PARAMETER *) &rcmm_param;
                    }
                    else
#endif // IRMP_SUPPORT_RCMM_PROTOCOL == 1
                    {
                        ANALYZE_PRINT ("protocol = UNKNOWN\n");
                        irmp_start_bit_detected = 0;                            // wait for another start bit...
                    }

                    if (irmp_start_bit_detected)
                    {
                        memcpy_P (&irmp_param, irmp_param_p, sizeof (IRMP_PARAMETER));

                        if (! (irmp_param.flags & IRMP_PARAM_FLAG_IS_MANCHESTER))
                        {
                            ANALYZE_PRINTF_2 ("pulse_1: %3d - %3d\n", irmp_param.pulse_1_len_min, irmp_param.pulse_1_len_max);
                            ANALYZE_PRINTF_2 ("pause_1: %3d - %3d\n", irmp_param.pause_1_len_min, irmp_param.pause_1_len_max);
                        }
                        else
                        {
                            ANALYZE_PRINTF_4 ("pulse: %3d - %3d or %3d - %3d\n", irmp_param.pulse_1_len_min, irmp_param.pulse_1_len_max,
                                            2 * irmp_param.pulse_1_len_min, 2 * irmp_param.pulse_1_len_max);
                            ANALYZE_PRINTF_4 ("pause: %3d - %3d or %3d - %3d\n", irmp_param.pause_1_len_min, irmp_param.pause_1_len_max,
                                            2 * irmp_param.pause_1_len_min, 2 * irmp_param.pause_1_len_max);
                        }

#if IRMP_SUPPORT_RC5_PROTOCOL == 1 && (IRMP_SUPPORT_FDC_PROTOCOL == 1 || IRMP_SUPPORT_RCCAR_PROTOCOL == 1)
                        if (irmp_param2.protocol)
                        {
                            ANALYZE_PRINTF_2 ("pulse_0: %3d - %3d\n", irmp_param2.pulse_0_len_min, irmp_param2.pulse_0_len_max);
                            ANALYZE_PRINTF_2 ("pause_0: %3d - %3d\n", irmp_param2.pause_0_len_min, irmp_param2.pause_0_len_max);
                            ANALYZE_PRINTF_2 ("pulse_1: %3d - %3d\n", irmp_param2.pulse_1_len_min, irmp_param2.pulse_1_len_max);
                            ANALYZE_PRINTF_2 ("pause_1: %3d - %3d\n", irmp_param2.pause_1_len_min, irmp_param2.pause_1_len_max);
                        }
#endif


#if IRMP_SUPPORT_RC6_PROTOCOL == 1
                        if (irmp_param.protocol == IRMP_RC6_PROTOCOL)
                        {
                            ANALYZE_PRINTF_2 ("pulse_toggle: %3d - %3d\n", RC6_TOGGLE_BIT_LEN_MIN, RC6_TOGGLE_BIT_LEN_MAX);
                        }
#endif

                        if (! (irmp_param.flags & IRMP_PARAM_FLAG_IS_MANCHESTER))
                        {
                            ANALYZE_PRINTF_2 ("pulse_0: %3d - %3d\n", irmp_param.pulse_0_len_min, irmp_param.pulse_0_len_max);
                            ANALYZE_PRINTF_2 ("pause_0: %3d - %3d\n", irmp_param.pause_0_len_min, irmp_param.pause_0_len_max);
                        }
                        else
                        {
                            ANALYZE_PRINTF_4 ("pulse: %3d - %3d or %3d - %3d\n", irmp_param.pulse_0_len_min, irmp_param.pulse_0_len_max,
                                            2 * irmp_param.pulse_0_len_min, 2 * irmp_param.pulse_0_len_max);
                            ANALYZE_PRINTF_4 ("pause: %3d - %3d or %3d - %3d\n", irmp_param.pause_0_len_min, irmp_param.pause_0_len_max,
                                            2 * irmp_param.pause_0_len_min, 2 * irmp_param.pause_0_len_max);
                        }

#ifdef ANALYZE
#if IRMP_SUPPORT_BANG_OLUFSEN_PROTOCOL == 1
                        if (irmp_param.protocol == IRMP_BANG_OLUFSEN_PROTOCOL)
                        {
                            ANALYZE_PRINTF_2 ("pulse_r: %3d - %3d\n", irmp_param.pulse_0_len_min, irmp_param.pulse_0_len_max);
                            ANALYZE_PRINTF_2 ("pause_r: %3d - %3d\n", BANG_OLUFSEN_R_PAUSE_LEN_MIN, BANG_OLUFSEN_R_PAUSE_LEN_MAX);
                        }
#endif

                        ANALYZE_PRINTF_1 ("command_offset: %2d\n", irmp_param.command_offset);
                        ANALYZE_PRINTF_1 ("command_len:    %3d\n", irmp_param.command_end - irmp_param.command_offset);
                        ANALYZE_PRINTF_1 ("complete_len:   %3d\n", irmp_param.complete_len);
                        ANALYZE_PRINTF_1 ("stop_bit:       %3d\n", irmp_param.stop_bit);
#endif // ANALYZE
                    }

                    irmp_bit = 0;

#if IRMP_SUPPORT_MANCHESTER == 1
                    if ((irmp_param.flags & IRMP_PARAM_FLAG_IS_MANCHESTER) &&
                         irmp_param.protocol != IRMP_RUWIDO_PROTOCOL && // Manchester, but not RUWIDO
                         irmp_param.protocol != IRMP_RC6_PROTOCOL /*** &&    // Manchester, but not RC6
                         irmp_param.protocol != IRMP_RCII_PROTOCOL ****/)     // Manchester, but not RCII
                    {
                        if (irmp_pause_time > irmp_param.pulse_1_len_max && irmp_pause_time <= 2 * irmp_param.pulse_1_len_max)
                        {
                            ANALYZE_PRINTF_4 ("%8.3fms [bit %2d: pulse = %3d, pause = %3d] ", (float) (time_counter * 1000) / F_INTERRUPTS, irmp_bit, irmp_pulse_time, irmp_pause_time);
                            ANALYZE_PUTCHAR ((irmp_param.flags & IRMP_PARAM_FLAG_1ST_PULSE_IS_1) ? '0' : '1');
                            ANALYZE_NEWLINE ();
                            irmp_store_bit ((irmp_param.flags & IRMP_PARAM_FLAG_1ST_PULSE_IS_1) ? 0 : 1);
                        }
                        else if (! last_value)  // && irmp_pause_time >= irmp_param.pause_1_len_min && irmp_pause_time <= irmp_param.pause_1_len_max)
                        {
                            ANALYZE_PRINTF_4 ("%8.3fms [bit %2d: pulse = %3d, pause = %3d] ", (float) (time_counter * 1000) / F_INTERRUPTS, irmp_bit, irmp_pulse_time, irmp_pause_time);
                            ANALYZE_PUTCHAR ((irmp_param.flags & IRMP_PARAM_FLAG_1ST_PULSE_IS_1) ? '1' : '0');
                            ANALYZE_NEWLINE ();
                            irmp_store_bit ((irmp_param.flags & IRMP_PARAM_FLAG_1ST_PULSE_IS_1) ? 1 : 0);
                        }
                    }
                    else
#endif // IRMP_SUPPORT_MANCHESTER == 1

#if IRMP_SUPPORT_SERIAL == 1
                    if (irmp_param.flags & IRMP_PARAM_FLAG_IS_SERIAL)
                    {
                        ; // do nothing
                    }
                    else
#endif // IRMP_SUPPORT_SERIAL == 1


#if IRMP_SUPPORT_DENON_PROTOCOL == 1
                    if (irmp_param.protocol == IRMP_DENON_PROTOCOL)
                    {
                        ANALYZE_PRINTF_4 ("%8.3fms [bit %2d: pulse = %3d, pause = %3d] ", (float) (time_counter * 1000) / F_INTERRUPTS, irmp_bit, irmp_pulse_time, irmp_pause_time);

                        if (irmp_pause_time >= DENON_1_PAUSE_LEN_MIN && irmp_pause_time <= DENON_1_PAUSE_LEN_MAX)
                        {                                                       // pause timings correct for "1"?
                            ANALYZE_PRINT ("1\n");                              // yes, store 1
                            irmp_store_bit (1);
                        }
                        else // if (irmp_pause_time >= DENON_0_PAUSE_LEN_MIN && irmp_pause_time <= DENON_0_PAUSE_LEN_MAX)
                        {                                                       // pause timings correct for "0"?
                            ANALYZE_PRINT("0\n")                                // yes, store 0
                            irmp_store_bit (0);
                        }
                    }
                    else
#endif // IRMP_SUPPORT_DENON_PROTOCOL == 1
#if IRMP_SUPPORT_THOMSON_PROTOCOL == 1
                    if (irmp_param.protocol == IRMP_THOMSON_PROTOCOL)
                    {
                        ANALYZE_PRINTF_4 ("%8.3fms [bit %2d: pulse = %3d, pause = %3d] ", (float) (time_counter * 1000) / F_INTERRUPTS, irmp_bit, irmp_pulse_time, irmp_pause_time);

                        if (irmp_pause_time >= THOMSON_1_PAUSE_LEN_MIN && irmp_pause_time <= THOMSON_1_PAUSE_LEN_MAX)
                        {                                                       // pause timings correct for "1"?
                            ANALYZE_PRINT ("1\n");                              // yes, store 1
                            irmp_store_bit (1);
                        }
                        else // if (irmp_pause_time >= THOMSON_0_PAUSE_LEN_MIN && irmp_pause_time <= THOMSON_0_PAUSE_LEN_MAX)
                        {                                                       // pause timings correct for "0"?
                            ANALYZE_PRINT("0\n")                                // yes, store 0
                            irmp_store_bit (0);
                        }
                    }
                    else
#endif // IRMP_SUPPORT_THOMSON_PROTOCOL == 1
                    {
                        ;                                                       // else do nothing
                    }

                    irmp_pulse_time = 1;                                        // set counter to 1, not 0
                    irmp_pause_time = 0;
                    wait_for_start_space = 0;
                }
            }
            else if (wait_for_space)                                            // the data section....
            {                                                                   // counting the time of darkness....
                uint_fast8_t got_light = FALSE;

                if (irmp_input)                                                 // still dark?
                {                                                               // yes...
                    if (irmp_bit == irmp_param.complete_len && irmp_param.stop_bit == 1)
                    {
                        if (
#if IRMP_SUPPORT_MANCHESTER == 1
                            (irmp_param.flags & IRMP_PARAM_FLAG_IS_MANCHESTER) ||
#endif
#if IRMP_SUPPORT_SERIAL == 1
                            (irmp_param.flags & IRMP_PARAM_FLAG_IS_SERIAL) ||
#endif
                            (irmp_pulse_time >= irmp_param.pulse_0_len_min && irmp_pulse_time <= irmp_param.pulse_0_len_max))
                        {
#ifdef ANALYZE
                            if (! (irmp_param.flags & IRMP_PARAM_FLAG_IS_MANCHESTER))
                            {
                                ANALYZE_PRINT ("stop bit detected\n");
                            }
#endif // ANALYZE
                            irmp_param.stop_bit = 0;
                        }
                        else
                        {
                            ANALYZE_PRINTF_4 ("error: stop bit timing wrong, irmp_bit = %d, irmp_pulse_time = %d, pulse_0_len_min = %d, pulse_0_len_max = %d\n",
                                            irmp_bit, irmp_pulse_time, irmp_param.pulse_0_len_min, irmp_param.pulse_0_len_max);
                            irmp_start_bit_detected = 0;                        // wait for another start bit...
                            irmp_pulse_time         = 0;
                            irmp_pause_time         = 0;
                        }
                    }
                    else
                    {
                        irmp_pause_time++;                                                          // increment counter

#if IRMP_SUPPORT_SIRCS_PROTOCOL == 1
                        if (irmp_param.protocol == IRMP_SIRCS_PROTOCOL &&                           // Sony has a variable number of bits:
                            irmp_pause_time > SIRCS_PAUSE_LEN_MAX &&                                // minimum is 12
                            irmp_bit >= 12 - 1)                                                     // pause too long?
                        {                                                                           // yes, break and close this frame
                            irmp_param.complete_len = irmp_bit + 1;                                 // set new complete length
                            got_light = TRUE;                                                       // this is a lie, but helps (generates stop bit)
                            irmp_tmp_address |= (irmp_bit - SIRCS_MINIMUM_DATA_LEN + 1) << 8;       // new: store number of additional bits in upper byte of address!
                            irmp_param.command_end = irmp_param.command_offset + irmp_bit + 1;      // correct command length
                            irmp_pause_time = SIRCS_PAUSE_LEN_MAX - 1;                              // correct pause length
                        }
                        else
#endif
#if IRMP_SUPPORT_MERLIN_PROTOCOL == 1
                        if (irmp_param.protocol == IRMP_MERLIN_PROTOCOL &&                          // Merlin has a variable number of bits:
                            irmp_pause_time > MERLIN_START_BIT_PAUSE_LEN_MAX &&                     // minimum is 8
                            irmp_bit >= 8 - 1)                                                      // pause too long?
                        {                                                                           // yes, break and close this frame
                            irmp_param.complete_len = irmp_bit;                                     // set new complete length
                            got_light = TRUE;                                                       // this is a lie, but helps (generates stop bit)
                            irmp_pause_time = MERLIN_BIT_PAUSE_LEN_MAX - 1;                         // correct pause length
                        }
                        else
#endif
#if IRMP_SUPPORT_FAN_PROTOCOL == 1
                        if (irmp_param.protocol == IRMP_FAN_PROTOCOL &&                             // FAN has no stop bit.
                            irmp_bit >= FAN_COMPLETE_DATA_LEN - 1)                                  // last bit in frame
                        {                                                                           // yes, break and close this frame
                            if (irmp_pulse_time <= FAN_0_PULSE_LEN_MAX && irmp_pause_time >= FAN_0_PAUSE_LEN_MIN)
                            {
                                ANALYZE_PRINT ("Generating virtual stop bit\n");
                                got_light = TRUE;                                                   // this is a lie, but helps (generates stop bit)
                            }
                            else if (irmp_pulse_time >= FAN_1_PULSE_LEN_MIN && irmp_pause_time >= FAN_1_PAUSE_LEN_MIN)
                            {
                                ANALYZE_PRINT ("Generating virtual stop bit\n");
                                got_light = TRUE;                                                   // this is a lie, but helps (generates stop bit)
                            }
                        }
                        else
#endif
#if IRMP_SUPPORT_SERIAL == 1
                        // NETBOX generates no stop bit, here is the timeout condition:
                        if ((irmp_param.flags & IRMP_PARAM_FLAG_IS_SERIAL) && irmp_param.protocol == IRMP_NETBOX_PROTOCOL &&
                            irmp_pause_time >= NETBOX_PULSE_LEN * (NETBOX_COMPLETE_DATA_LEN - irmp_bit))
                        {
                            got_light = TRUE;                                                       // this is a lie, but helps (generates stop bit)
                        }
                        else
#endif
#if IRMP_SUPPORT_GRUNDIG_NOKIA_IR60_PROTOCOL == 1
                        if (irmp_param.protocol == IRMP_GRUNDIG_PROTOCOL && !irmp_param.stop_bit)
                        {
                            if (irmp_pause_time > IR60_TIMEOUT_LEN && (irmp_bit == 5 || irmp_bit == 6))
                            {
                                ANALYZE_PRINT ("Switching to IR60 protocol\n");
                                got_light = TRUE;                                       // this is a lie, but generates a stop bit ;-)
                                irmp_param.stop_bit = TRUE;                             // set flag

                                irmp_param.protocol         = IRMP_IR60_PROTOCOL;       // change protocol
                                irmp_param.complete_len     = IR60_COMPLETE_DATA_LEN;   // correct complete len
                                irmp_param.address_offset   = IR60_ADDRESS_OFFSET;
                                irmp_param.address_end      = IR60_ADDRESS_OFFSET + IR60_ADDRESS_LEN;
                                irmp_param.command_offset   = IR60_COMMAND_OFFSET;
                                irmp_param.command_end      = IR60_COMMAND_OFFSET + IR60_COMMAND_LEN;

                                irmp_tmp_command <<= 1;
                                irmp_tmp_command |= first_bit;
                            }
                            else if (irmp_pause_time >= 2 * irmp_param.pause_1_len_max && irmp_bit >= GRUNDIG_COMPLETE_DATA_LEN - 2)
                            {                                                           // special manchester decoder
                                irmp_param.complete_len = GRUNDIG_COMPLETE_DATA_LEN;    // correct complete len
                                got_light = TRUE;                                       // this is a lie, but generates a stop bit ;-)
                                irmp_param.stop_bit = TRUE;                             // set flag
                            }
                            else if (irmp_bit >= GRUNDIG_COMPLETE_DATA_LEN)
                            {
                                ANALYZE_PRINTF_1 ("Switching to NOKIA protocol, irmp_bit = %d\n", irmp_bit);
                                irmp_param.protocol         = IRMP_NOKIA_PROTOCOL;      // change protocol
                                irmp_param.address_offset   = NOKIA_ADDRESS_OFFSET;
                                irmp_param.address_end      = NOKIA_ADDRESS_OFFSET + NOKIA_ADDRESS_LEN;
                                irmp_param.command_offset   = NOKIA_COMMAND_OFFSET;
                                irmp_param.command_end      = NOKIA_COMMAND_OFFSET + NOKIA_COMMAND_LEN;

                                if (irmp_tmp_command & 0x300)
                                {
                                    irmp_tmp_address = (irmp_tmp_command >> 8);
                                    irmp_tmp_command &= 0xFF;
                                }
                            }
                        }
                        else
#endif
#if IRMP_SUPPORT_SIEMENS_OR_RUWIDO_PROTOCOL == 1
                        if (irmp_param.protocol == IRMP_RUWIDO_PROTOCOL && !irmp_param.stop_bit)
                        {
                            if (irmp_pause_time >= 2 * irmp_param.pause_1_len_max && irmp_bit >= RUWIDO_COMPLETE_DATA_LEN - 2)
                            {                                                           // special manchester decoder
                                irmp_param.complete_len = RUWIDO_COMPLETE_DATA_LEN;     // correct complete len
                                got_light = TRUE;                                       // this is a lie, but generates a stop bit ;-)
                                irmp_param.stop_bit = TRUE;                             // set flag
                            }
                            else if (irmp_bit >= RUWIDO_COMPLETE_DATA_LEN)
                            {
                                ANALYZE_PRINT ("Switching to SIEMENS protocol\n");
                                irmp_param.protocol         = IRMP_SIEMENS_PROTOCOL;    // change protocol
                                irmp_param.address_offset   = SIEMENS_ADDRESS_OFFSET;
                                irmp_param.address_end      = SIEMENS_ADDRESS_OFFSET + SIEMENS_ADDRESS_LEN;
                                irmp_param.command_offset   = SIEMENS_COMMAND_OFFSET;
                                irmp_param.command_end      = SIEMENS_COMMAND_OFFSET + SIEMENS_COMMAND_LEN;

                                //                   76543210
                                // RUWIDO:  AAAAAAAAACCCCCCCp
                                // SIEMENS: AAAAAAAAAAACCCCCCCCCCp
                                irmp_tmp_address <<= 2;
                                irmp_tmp_address |= (irmp_tmp_command >> 6);
                                irmp_tmp_command &= 0x003F;
//                              irmp_tmp_command <<= 4;
                                irmp_tmp_command |= last_value;
                            }
                        }
                        else
#endif
#if IRMP_SUPPORT_ROOMBA_PROTOCOL == 1
                        if (irmp_param.protocol == IRMP_ROOMBA_PROTOCOL &&                          // Roomba has no stop bit
                            irmp_bit >= ROOMBA_COMPLETE_DATA_LEN - 1)                               // it's the last data bit...
                        {                                                                           // break and close this frame
                            if (irmp_pulse_time >= ROOMBA_1_PULSE_LEN_MIN && irmp_pulse_time <= ROOMBA_1_PULSE_LEN_MAX)
                            {
                                irmp_pause_time = ROOMBA_1_PAUSE_LEN_EXACT;
                            }
                            else if (irmp_pulse_time >= ROOMBA_0_PULSE_LEN_MIN && irmp_pulse_time <= ROOMBA_0_PULSE_LEN_MAX)
                            {
                                irmp_pause_time = ROOMBA_0_PAUSE_LEN;
                            }

                            got_light = TRUE;                                                       // this is a lie, but helps (generates stop bit)
                        }
                        else
#endif
#if IRMP_SUPPORT_MANCHESTER == 1
                        if ((irmp_param.flags & IRMP_PARAM_FLAG_IS_MANCHESTER) &&
                            irmp_pause_time >= 2 * irmp_param.pause_1_len_max && irmp_bit >= irmp_param.complete_len - 2 && !irmp_param.stop_bit)
                        {                                                       // special manchester decoder
                            got_light = TRUE;                                   // this is a lie, but generates a stop bit ;-)
                            irmp_param.stop_bit = TRUE;                         // set flag
                        }
                        else
#endif // IRMP_SUPPORT_MANCHESTER == 1
                        if (irmp_pause_time > IRMP_TIMEOUT_LEN)                 // timeout?
                        {                                                       // yes...
                            if (irmp_bit == irmp_param.complete_len - 1 && irmp_param.stop_bit == 0)
                            {
                                irmp_bit++;
                            }
#if IRMP_SUPPORT_NEC_PROTOCOL == 1
                            else if ((irmp_param.protocol == IRMP_NEC_PROTOCOL || irmp_param.protocol == IRMP_NEC42_PROTOCOL) && irmp_bit == 0)
                            {                                                               // it was a non-standard repetition frame
#ifdef ANALYZE                                                                              // with 4500us pause instead of 2250us
                                ANALYZE_PRINT ("Detected non-standard repetition frame, switching to NEC repetition\n");
#endif // ANALYZE
                                if (key_repetition_len < NEC_FRAME_REPEAT_PAUSE_LEN_MAX)
                                {
                                    irmp_param.stop_bit     = TRUE;                         // set flag
                                    irmp_param.protocol     = IRMP_NEC_PROTOCOL;            // switch protocol
                                    irmp_param.complete_len = irmp_bit;                     // patch length: 16 or 17
                                    irmp_tmp_address = last_irmp_address;                   // address is last address
                                    irmp_tmp_command = last_irmp_command;                   // command is last command
                                    irmp_flags |= IRMP_FLAG_REPETITION;
                                    key_repetition_len = 0;
                                }
                                else
                                {
                                    ANALYZE_PRINTF_2 ("ignoring NEC repetition frame: timeout occured, key_repetition_len = %d > %d\n",
                                                    key_repetition_len, NEC_FRAME_REPEAT_PAUSE_LEN_MAX);
                                    irmp_ir_detected = FALSE;
                                }
                            }
#endif // IRMP_SUPPORT_NEC_PROTOCOL == 1
#if IRMP_SUPPORT_JVC_PROTOCOL == 1
                            else if (irmp_param.protocol == IRMP_NEC_PROTOCOL && (irmp_bit == 16 || irmp_bit == 17))      // it was a JVC stop bit
                            {
                                ANALYZE_PRINTF_1 ("Switching to JVC protocol, irmp_bit = %d\n", irmp_bit);
                                irmp_param.stop_bit     = TRUE;                                     // set flag
                                irmp_param.protocol     = IRMP_JVC_PROTOCOL;                        // switch protocol
                                irmp_param.complete_len = irmp_bit;                                 // patch length: 16 or 17
                                irmp_tmp_command        = (irmp_tmp_address >> 4);                  // set command: upper 12 bits are command bits
                                irmp_tmp_address        = irmp_tmp_address & 0x000F;                // lower 4 bits are address bits
                                irmp_start_bit_detected = 1;                                        // tricky: don't wait for another start bit...
                            }
#endif // IRMP_SUPPORT_JVC_PROTOCOL == 1
#if IRMP_SUPPORT_LGAIR_PROTOCOL == 1
                            else if (irmp_param.protocol == IRMP_NEC_PROTOCOL && (irmp_bit == 28 || irmp_bit == 29))      // it was a LGAIR stop bit
                            {
                                ANALYZE_PRINTF_1 ("Switching to LGAIR protocol, irmp_bit = %d\n", irmp_bit);
                                irmp_param.stop_bit     = TRUE;                                     // set flag
                                irmp_param.protocol     = IRMP_LGAIR_PROTOCOL;                      // switch protocol
                                irmp_param.complete_len = irmp_bit;                                 // patch length: 16 or 17
                                irmp_tmp_command        = irmp_lgair_command;                       // set command: upper 8 bits are command bits
                                irmp_tmp_address        = irmp_lgair_address;                       // lower 4 bits are address bits
                                irmp_start_bit_detected = 1;                                        // tricky: don't wait for another start bit...
                            }
#endif // IRMP_SUPPORT_LGAIR_PROTOCOL == 1

#if IRMP_SUPPORT_NEC42_PROTOCOL == 1
#if IRMP_SUPPORT_NEC_PROTOCOL == 1
                            else if (irmp_param.protocol == IRMP_NEC42_PROTOCOL && irmp_bit == 32)      // it was a NEC stop bit
                            {
                                ANALYZE_PRINT ("Switching to NEC protocol\n");
                                irmp_param.stop_bit     = TRUE;                                     // set flag
                                irmp_param.protocol     = IRMP_NEC_PROTOCOL;                        // switch protocol
                                irmp_param.complete_len = irmp_bit;                                 // patch length: 16 or 17

                                //        0123456789ABC0123456789ABC0123456701234567
                                // NEC42: AAAAAAAAAAAAAaaaaaaaaaaaaaCCCCCCCCcccccccc
                                // NEC:   AAAAAAAAaaaaaaaaCCCCCCCCcccccccc
                                irmp_tmp_address        |= (irmp_tmp_address2 & 0x0007) << 13;      // fm 2012-02-13: 12 -> 13
                                irmp_tmp_command        = (irmp_tmp_address2 >> 3) | (irmp_tmp_command << 10);
                            }
#endif // IRMP_SUPPORT_NEC_PROTOCOL == 1
#if IRMP_SUPPORT_LGAIR_PROTOCOL == 1
                            else if (irmp_param.protocol == IRMP_NEC42_PROTOCOL && irmp_bit == 28)      // it was a NEC stop bit
                            {
                                ANALYZE_PRINT ("Switching to LGAIR protocol\n");
                                irmp_param.stop_bit     = TRUE;                                     // set flag
                                irmp_param.protocol     = IRMP_LGAIR_PROTOCOL;                      // switch protocol
                                irmp_param.complete_len = irmp_bit;                                 // patch length: 16 or 17
                                irmp_tmp_address        = irmp_lgair_address;
                                irmp_tmp_command        = irmp_lgair_command;
                            }
#endif // IRMP_SUPPORT_LGAIR_PROTOCOL == 1
#if IRMP_SUPPORT_JVC_PROTOCOL == 1
                            else if (irmp_param.protocol == IRMP_NEC42_PROTOCOL && (irmp_bit == 16 || irmp_bit == 17))  // it was a JVC stop bit
                            {
                                ANALYZE_PRINTF_1 ("Switching to JVC protocol, irmp_bit = %d\n", irmp_bit);
                                irmp_param.stop_bit     = TRUE;                                     // set flag
                                irmp_param.protocol     = IRMP_JVC_PROTOCOL;                        // switch protocol
                                irmp_param.complete_len = irmp_bit;                                 // patch length: 16 or 17

                                //        0123456789ABC0123456789ABC0123456701234567
                                // NEC42: AAAAAAAAAAAAAaaaaaaaaaaaaaCCCCCCCCcccccccc
                                // JVC:   AAAACCCCCCCCCCCC
                                irmp_tmp_command        = (irmp_tmp_address >> 4) | (irmp_tmp_address2 << 9);   // set command: upper 12 bits are command bits
                                irmp_tmp_address        = irmp_tmp_address & 0x000F;                            // lower 4 bits are address bits
                            }
#endif // IRMP_SUPPORT_JVC_PROTOCOL == 1
#endif // IRMP_SUPPORT_NEC42_PROTOCOL == 1

#if IRMP_SUPPORT_SAMSUNG48_PROTOCOL == 1
                            else if (irmp_param.protocol == IRMP_SAMSUNG48_PROTOCOL && irmp_bit == 32)          // it was a SAMSUNG32 stop bit
                            {
                                ANALYZE_PRINT ("Switching to SAMSUNG32 protocol\n");
                                irmp_param.protocol         = IRMP_SAMSUNG32_PROTOCOL;
                                irmp_param.command_offset   = SAMSUNG32_COMMAND_OFFSET;
                                irmp_param.command_end      = SAMSUNG32_COMMAND_OFFSET + SAMSUNG32_COMMAND_LEN;
                                irmp_param.complete_len     = SAMSUNG32_COMPLETE_DATA_LEN;
                            }
#endif // IRMP_SUPPORT_SAMSUNG_PROTOCOL == 1

#if IRMP_SUPPORT_RCMM_PROTOCOL == 1
                            else if (irmp_param.protocol == IRMP_RCMM32_PROTOCOL && (irmp_bit == 12 || irmp_bit == 24))  // it was a RCMM stop bit
                            {
                                if (irmp_bit == 12)
                                {
                                    irmp_tmp_command = (irmp_tmp_address & 0xFF);                   // set command: lower 8 bits are command bits
                                    irmp_tmp_address >>= 8;                                         // upper 4 bits are address bits

                                    ANALYZE_PRINTF_1 ("Switching to RCMM12 protocol, irmp_bit = %d\n", irmp_bit);
                                    irmp_param.protocol     = IRMP_RCMM12_PROTOCOL;                 // switch protocol
                                }
                                else // if ((irmp_bit == 24)
                                {
                                    ANALYZE_PRINTF_1 ("Switching to RCMM24 protocol, irmp_bit = %d\n", irmp_bit);
                                    irmp_param.protocol     = IRMP_RCMM24_PROTOCOL;                 // switch protocol
                                }
                                irmp_param.stop_bit     = TRUE;                                     // set flag
                                irmp_param.complete_len = irmp_bit;                                 // patch length
                            }
#endif // IRMP_SUPPORT_RCMM_PROTOCOL == 1

#if IRMP_SUPPORT_TECHNICS_PROTOCOL == 1
                            else if (irmp_param.protocol == IRMP_MATSUSHITA_PROTOCOL && irmp_bit == 22)  // it was a TECHNICS stop bit
                            {
                                ANALYZE_PRINTF_1 ("Switching to TECHNICS protocol, irmp_bit = %d\n", irmp_bit);
                                // Situation:
                                // The first 12 bits have been stored in irmp_tmp_command (LSB first)
                                // The following 10 bits have been stored in irmp_tmp_address (LSB first)
                                // The code of TECHNICS is:
                                //   cccccccccccCCCCCCCCCCC (11 times c and 11 times C)
                                //   ccccccccccccaaaaaaaaaa
                                // where C is inverted value of c

                                irmp_tmp_address <<= 1;
                                if (irmp_tmp_command & (1<<11))
                                {
                                    irmp_tmp_address |= 1;
                                    irmp_tmp_command &= ~(1<<11);
                                }

                                if (irmp_tmp_command == ((~irmp_tmp_address) & 0x07FF))
                                {
                                    irmp_tmp_address = 0;

                                    irmp_param.protocol     = IRMP_TECHNICS_PROTOCOL;                   // switch protocol
                                    irmp_param.complete_len = irmp_bit;                                 // patch length
                                }
                                else
                                {
                                    ANALYZE_PRINT ("error 8: TECHNICS frame error\n");
                                    ANALYZE_ONLY_NORMAL_PUTCHAR ('\n');
                                    irmp_start_bit_detected = 0;                    // wait for another start bit...
                                    irmp_pulse_time         = 0;
                                    irmp_pause_time         = 0;
                                }
                            }
#endif // IRMP_SUPPORT_TECHNICS_PROTOCOL == 1
                            else
                            {
                                ANALYZE_PRINTF_2 ("error 2: pause %d after data bit %d too long\n", irmp_pause_time, irmp_bit);
                                ANALYZE_ONLY_NORMAL_PUTCHAR ('\n');
                                irmp_start_bit_detected = 0;                    // wait for another start bit...
                                irmp_pulse_time         = 0;
                                irmp_pause_time         = 0;
                            }
                        }
                    }
                }
                else
                {                                                               // got light now!
                    got_light = TRUE;
                }

                if (got_light)
                {
                    ANALYZE_PRINTF_4 ("%8.3fms [bit %2d: pulse = %3d, pause = %3d] ", (float) (time_counter * 1000) / F_INTERRUPTS, irmp_bit, irmp_pulse_time, irmp_pause_time);

#if IRMP_SUPPORT_MANCHESTER == 1
                    if ((irmp_param.flags & IRMP_PARAM_FLAG_IS_MANCHESTER))                                     // Manchester
                    {
#if IRMP_SUPPORT_MERLIN_PROTOCOL == 1
                        if (irmp_param.complete_len == irmp_bit && irmp_param.protocol == IRMP_MERLIN_PROTOCOL)
                        {
                            if (last_value == 0)
                            {
                                if (irmp_pulse_time >= 2 * irmp_param.pulse_1_len_min && irmp_pulse_time <= 2 * irmp_param.pulse_1_len_max &&
                                    last_pause >= irmp_param.pause_1_len_min && last_pause <= irmp_param.pulse_1_len_max)
                                {
                                    irmp_param.complete_len += 2;
                                    irmp_store_bit(0);
                                    irmp_store_bit(1);
                                }
                            }
                            else
                            {
                                if (last_pause >= 2 * irmp_param.pause_1_len_min && last_pause <= 2 * irmp_param.pulse_1_len_max)
                                {
                                    if (irmp_pulse_time >= irmp_param.pulse_1_len_min && irmp_pulse_time <= irmp_param.pulse_1_len_max)
                                    {
                                        irmp_param.complete_len++;
                                        irmp_store_bit(0);
                                    }
                                    else if (irmp_pulse_time >= 2 * irmp_param.pulse_1_len_min && irmp_pulse_time <= 2 * irmp_param.pulse_1_len_max)
                                    {
                                        irmp_param.complete_len += 2;
                                        irmp_store_bit(0);
                                        irmp_store_bit(1);
                                    }
                                }
                            }
                        }
                        else
#endif
#if 1
                        if (irmp_pulse_time > irmp_param.pulse_1_len_max /* && irmp_pulse_time <= 2 * irmp_param.pulse_1_len_max */)
#else // better, but some IR-RCs use asymmetric timings :-/
                        if (irmp_pulse_time > irmp_param.pulse_1_len_max && irmp_pulse_time <= 2 * irmp_param.pulse_1_len_max &&
                            irmp_pause_time <= 2 * irmp_param.pause_1_len_max)
#endif
                        {
#if IRMP_SUPPORT_RC6_PROTOCOL == 1
                            if (irmp_param.protocol == IRMP_RC6_PROTOCOL && irmp_bit == 4 && irmp_pulse_time > RC6_TOGGLE_BIT_LEN_MIN)         // RC6 toggle bit
                            {
                                ANALYZE_PUTCHAR ('T');
                                if (irmp_param.complete_len == RC6_COMPLETE_DATA_LEN_LONG)                      // RC6 mode 6A
                                {
                                    irmp_store_bit (1);
                                    last_value = 1;
                                }
                                else                                                                            // RC6 mode 0
                                {
                                    irmp_store_bit (0);
                                    last_value = 0;
                                }
                                ANALYZE_NEWLINE ();
                            }
                            else
#endif // IRMP_SUPPORT_RC6_PROTOCOL == 1
                            {
                                ANALYZE_PUTCHAR ((irmp_param.flags & IRMP_PARAM_FLAG_1ST_PULSE_IS_1) ? '0' : '1');
                                irmp_store_bit ((irmp_param.flags & IRMP_PARAM_FLAG_1ST_PULSE_IS_1) ? 0  :  1 );

#if IRMP_SUPPORT_RC6_PROTOCOL == 1
                                if (irmp_param.protocol == IRMP_RC6_PROTOCOL && irmp_bit == 4 && irmp_pulse_time > RC6_TOGGLE_BIT_LEN_MIN)      // RC6 toggle bit
                                {
                                    ANALYZE_PUTCHAR ('T');
                                    irmp_store_bit (1);

                                    if (irmp_pause_time > 2 * irmp_param.pause_1_len_max)
                                    {
                                        last_value = 0;
                                    }
                                    else
                                    {
                                        last_value = 1;
                                    }
                                    ANALYZE_NEWLINE ();
                                }
                                else
#endif // IRMP_SUPPORT_RC6_PROTOCOL == 1
                                {
                                    ANALYZE_PUTCHAR ((irmp_param.flags & IRMP_PARAM_FLAG_1ST_PULSE_IS_1) ? '1' : '0');
                                    irmp_store_bit ((irmp_param.flags & IRMP_PARAM_FLAG_1ST_PULSE_IS_1) ? 1 :   0 );

#if IRMP_SUPPORT_RC5_PROTOCOL == 1 && IRMP_SUPPORT_RCII_PROTOCOL == 1 && (IRMP_SUPPORT_FDC_PROTOCOL == 1 || IRMP_SUPPORT_RCCAR_PROTOCOL == 1)
                                    if (! irmp_param2.protocol)
#endif
                                    {
#ifdef ANALYZE
                                        ANALYZE_NEWLINE ();
#endif // ANALYZE
                                    }
                                    last_value = (irmp_param.flags & IRMP_PARAM_FLAG_1ST_PULSE_IS_1) ? 1 : 0;
                                }
                            }
                        }
                        else if (irmp_pulse_time >= irmp_param.pulse_1_len_min && irmp_pulse_time <= irmp_param.pulse_1_len_max
                                 /* && irmp_pause_time <= 2 * irmp_param.pause_1_len_max */)
                        {
                            uint_fast8_t manchester_value;

                            if (last_pause > irmp_param.pause_1_len_max && last_pause <= 2 * irmp_param.pause_1_len_max)
                            {
                                manchester_value = last_value ? 0 : 1;
                                last_value  = manchester_value;
                            }
                            else
                            {
                                manchester_value = last_value;
                            }

                            ANALYZE_PUTCHAR (manchester_value + '0');

#if IRMP_SUPPORT_RC5_PROTOCOL == 1 && (IRMP_SUPPORT_FDC_PROTOCOL == 1 || IRMP_SUPPORT_RCCAR_PROTOCOL == 1)
                            if (! irmp_param2.protocol)
#endif
                            {
                                ANALYZE_NEWLINE ();
                            }

#if IRMP_SUPPORT_RC6_PROTOCOL == 1
                            if (irmp_param.protocol == IRMP_RC6_PROTOCOL && irmp_bit == 1 && manchester_value == 1)     // RC6 mode != 0 ???
                            {
                                ANALYZE_PRINT ("Switching to RC6A protocol\n");
                                irmp_param.complete_len = RC6_COMPLETE_DATA_LEN_LONG;
                                irmp_param.address_offset = 5;
                                irmp_param.address_end = irmp_param.address_offset + 15;
                                irmp_param.command_offset = irmp_param.address_end + 1;                                 // skip 1 system bit, changes like a toggle bit
                                irmp_param.command_end = irmp_param.command_offset + 16 - 1;
                                irmp_tmp_address = 0;
                            }
#endif // IRMP_SUPPORT_RC6_PROTOCOL == 1

                            irmp_store_bit (manchester_value);
                        }
                        else
                        {
#if IRMP_SUPPORT_RC5_PROTOCOL == 1 && IRMP_SUPPORT_FDC_PROTOCOL == 1
                            if (irmp_param2.protocol == IRMP_FDC_PROTOCOL &&
                                irmp_pulse_time >= FDC_PULSE_LEN_MIN && irmp_pulse_time <= FDC_PULSE_LEN_MAX &&
                                ((irmp_pause_time >= FDC_1_PAUSE_LEN_MIN && irmp_pause_time <= FDC_1_PAUSE_LEN_MAX) ||
                                 (irmp_pause_time >= FDC_0_PAUSE_LEN_MIN && irmp_pause_time <= FDC_0_PAUSE_LEN_MAX)))
                            {
                                ANALYZE_PUTCHAR ('?');
                                irmp_param.protocol = 0;                // switch to FDC, see below
                            }
                            else
#endif // IRMP_SUPPORT_FDC_PROTOCOL == 1
#if IRMP_SUPPORT_RC5_PROTOCOL == 1 && IRMP_SUPPORT_RCCAR_PROTOCOL == 1
                            if (irmp_param2.protocol == IRMP_RCCAR_PROTOCOL &&
                                irmp_pulse_time >= RCCAR_PULSE_LEN_MIN && irmp_pulse_time <= RCCAR_PULSE_LEN_MAX &&
                                ((irmp_pause_time >= RCCAR_1_PAUSE_LEN_MIN && irmp_pause_time <= RCCAR_1_PAUSE_LEN_MAX) ||
                                 (irmp_pause_time >= RCCAR_0_PAUSE_LEN_MIN && irmp_pause_time <= RCCAR_0_PAUSE_LEN_MAX)))
                            {
                                ANALYZE_PUTCHAR ('?');
                                irmp_param.protocol = 0;                // switch to RCCAR, see below
                            }
                            else
#endif // IRMP_SUPPORT_RCCAR_PROTOCOL == 1
                            {
                                ANALYZE_PUTCHAR ('?');
                                ANALYZE_NEWLINE ();
                                ANALYZE_PRINTF_3 ("error 3 manchester: timing not correct: data bit %d,  pulse: %d, pause: %d\n", irmp_bit, irmp_pulse_time, irmp_pause_time);
                                ANALYZE_ONLY_NORMAL_PUTCHAR ('\n');
                                irmp_start_bit_detected = 0;                            // reset flags and wait for next start bit
                                irmp_pause_time         = 0;
                            }
                        }

#if IRMP_SUPPORT_RC5_PROTOCOL == 1 && IRMP_SUPPORT_FDC_PROTOCOL == 1
                        if (irmp_param2.protocol == IRMP_FDC_PROTOCOL && irmp_pulse_time >= FDC_PULSE_LEN_MIN && irmp_pulse_time <= FDC_PULSE_LEN_MAX)
                        {
                            if (irmp_pause_time >= FDC_1_PAUSE_LEN_MIN && irmp_pause_time <= FDC_1_PAUSE_LEN_MAX)
                            {
                                ANALYZE_PRINT ("   1 (FDC)\n");
                                irmp_store_bit2 (1);
                            }
                            else if (irmp_pause_time >= FDC_0_PAUSE_LEN_MIN && irmp_pause_time <= FDC_0_PAUSE_LEN_MAX)
                            {
                                ANALYZE_PRINT ("   0 (FDC)\n");
                                irmp_store_bit2 (0);
                            }

                            if (! irmp_param.protocol)
                            {
                                ANALYZE_PRINT ("Switching to FDC protocol\n");
                                memcpy (&irmp_param, &irmp_param2, sizeof (IRMP_PARAMETER));
                                irmp_param2.protocol = 0;
                                irmp_tmp_address = irmp_tmp_address2;
                                irmp_tmp_command = irmp_tmp_command2;
                            }
                        }
#endif // IRMP_SUPPORT_FDC_PROTOCOL == 1
#if IRMP_SUPPORT_RC5_PROTOCOL == 1 && IRMP_SUPPORT_RCCAR_PROTOCOL == 1
                        if (irmp_param2.protocol == IRMP_RCCAR_PROTOCOL && irmp_pulse_time >= RCCAR_PULSE_LEN_MIN && irmp_pulse_time <= RCCAR_PULSE_LEN_MAX)
                        {
                            if (irmp_pause_time >= RCCAR_1_PAUSE_LEN_MIN && irmp_pause_time <= RCCAR_1_PAUSE_LEN_MAX)
                            {
                                ANALYZE_PRINT ("   1 (RCCAR)\n");
                                irmp_store_bit2 (1);
                            }
                            else if (irmp_pause_time >= RCCAR_0_PAUSE_LEN_MIN && irmp_pause_time <= RCCAR_0_PAUSE_LEN_MAX)
                            {
                                ANALYZE_PRINT ("   0 (RCCAR)\n");
                                irmp_store_bit2 (0);
                            }

                            if (! irmp_param.protocol)
                            {
                                ANALYZE_PRINT ("Switching to RCCAR protocol\n");
                                memcpy (&irmp_param, &irmp_param2, sizeof (IRMP_PARAMETER));
                                irmp_param2.protocol = 0;
                                irmp_tmp_address = irmp_tmp_address2;
                                irmp_tmp_command = irmp_tmp_command2;
                            }
                        }
#endif // IRMP_SUPPORT_RCCAR_PROTOCOL == 1

                        last_pause      = irmp_pause_time;
                        wait_for_space  = 0;
                    }
                    else
#endif // IRMP_SUPPORT_MANCHESTER == 1

#if IRMP_SUPPORT_SERIAL == 1
                    if (irmp_param.flags & IRMP_PARAM_FLAG_IS_SERIAL)
                    {
                        while (irmp_bit < irmp_param.complete_len && irmp_pulse_time > irmp_param.pulse_1_len_max)
                        {
                            ANALYZE_PUTCHAR ('1');
                            irmp_store_bit (1);

                            if (irmp_pulse_time >= irmp_param.pulse_1_len_min)
                            {
                                irmp_pulse_time -= irmp_param.pulse_1_len_min;
                            }
                            else
                            {
                                irmp_pulse_time = 0;
                            }
                        }

                        while (irmp_bit < irmp_param.complete_len && irmp_pause_time > irmp_param.pause_1_len_max)
                        {
                            ANALYZE_PUTCHAR ('0');
                            irmp_store_bit (0);

                            if (irmp_pause_time >= irmp_param.pause_1_len_min)
                            {
                                irmp_pause_time -= irmp_param.pause_1_len_min;
                            }
                            else
                            {
                                irmp_pause_time = 0;
                            }
                        }
                        ANALYZE_NEWLINE ();
                        wait_for_space = 0;
                    }
                    else
#endif // IRMP_SUPPORT_SERIAL == 1

#if IRMP_SUPPORT_SAMSUNG_PROTOCOL == 1
                    if (irmp_param.protocol == IRMP_SAMSUNG_PROTOCOL && irmp_bit == 16)       // Samsung: 16th bit
                    {
                        if (irmp_pulse_time >= SAMSUNG_PULSE_LEN_MIN && irmp_pulse_time <= SAMSUNG_PULSE_LEN_MAX &&
                            irmp_pause_time >= SAMSUNG_START_BIT_PAUSE_LEN_MIN && irmp_pause_time <= SAMSUNG_START_BIT_PAUSE_LEN_MAX)
                        {
                            ANALYZE_PRINT ("SYNC\n");
                            wait_for_space = 0;
                            irmp_bit++;
                        }
                        else  if (irmp_pulse_time >= SAMSUNG_PULSE_LEN_MIN && irmp_pulse_time <= SAMSUNG_PULSE_LEN_MAX)
                        {
#if IRMP_SUPPORT_SAMSUNG48_PROTOCOL == 1
                            ANALYZE_PRINT ("Switching to SAMSUNG48 protocol ");
                            irmp_param.protocol         = IRMP_SAMSUNG48_PROTOCOL;
                            irmp_param.command_offset   = SAMSUNG48_COMMAND_OFFSET;
                            irmp_param.command_end      = SAMSUNG48_COMMAND_OFFSET + SAMSUNG48_COMMAND_LEN;
                            irmp_param.complete_len     = SAMSUNG48_COMPLETE_DATA_LEN;
#else
                            ANALYZE_PRINT ("Switching to SAMSUNG32 protocol ");
                            irmp_param.protocol         = IRMP_SAMSUNG32_PROTOCOL;
                            irmp_param.command_offset   = SAMSUNG32_COMMAND_OFFSET;
                            irmp_param.command_end      = SAMSUNG32_COMMAND_OFFSET + SAMSUNG32_COMMAND_LEN;
                            irmp_param.complete_len     = SAMSUNG32_COMPLETE_DATA_LEN;
#endif
                            if (irmp_pause_time >= SAMSUNG_1_PAUSE_LEN_MIN && irmp_pause_time <= SAMSUNG_1_PAUSE_LEN_MAX)
                            {
                                ANALYZE_PRINT("1\n");
                                irmp_store_bit(1);
                                wait_for_space = 0;
                            }
                            else
                            {
                                ANALYZE_PRINT("0\n");
                                irmp_store_bit (0);
                                wait_for_space = 0;
                            }
                        }
                        else
                        {                                                           // timing incorrect!
                            ANALYZE_PRINTF_3 ("error 3 Samsung: timing not correct: data bit %d,  pulse: %d, pause: %d\n", irmp_bit, irmp_pulse_time, irmp_pause_time);
                            ANALYZE_ONLY_NORMAL_PUTCHAR ('\n');
                            irmp_start_bit_detected = 0;                            // reset flags and wait for next start bit
                            irmp_pause_time         = 0;
                        }
                    }
                    else
#endif // IRMP_SUPPORT_SAMSUNG_PROTOCOL

#if IRMP_SUPPORT_NEC16_PROTOCOL
#if IRMP_SUPPORT_NEC42_PROTOCOL == 1
                    if (irmp_param.protocol == IRMP_NEC42_PROTOCOL &&
#else // IRMP_SUPPORT_NEC_PROTOCOL instead
                    if (irmp_param.protocol == IRMP_NEC_PROTOCOL &&
#endif // IRMP_SUPPORT_NEC42_PROTOCOL == 1
                        irmp_bit == 8 && irmp_pause_time >= NEC_START_BIT_PAUSE_LEN_MIN && irmp_pause_time <= NEC_START_BIT_PAUSE_LEN_MAX)
                    {
                        ANALYZE_PRINT ("Switching to NEC16 protocol\n");
                        irmp_param.protocol         = IRMP_NEC16_PROTOCOL;
                        irmp_param.address_offset   = NEC16_ADDRESS_OFFSET;
                        irmp_param.address_end      = NEC16_ADDRESS_OFFSET + NEC16_ADDRESS_LEN;
                        irmp_param.command_offset   = NEC16_COMMAND_OFFSET;
                        irmp_param.command_end      = NEC16_COMMAND_OFFSET + NEC16_COMMAND_LEN;
                        irmp_param.complete_len     = NEC16_COMPLETE_DATA_LEN;
                        wait_for_space = 0;
                    }
                    else
#endif // IRMP_SUPPORT_NEC16_PROTOCOL

#if IRMP_SUPPORT_BANG_OLUFSEN_PROTOCOL == 1
                    if (irmp_param.protocol == IRMP_BANG_OLUFSEN_PROTOCOL)
                    {
                        if (irmp_pulse_time >= BANG_OLUFSEN_PULSE_LEN_MIN && irmp_pulse_time <= BANG_OLUFSEN_PULSE_LEN_MAX)
                        {
                            if (irmp_bit == 1)                                      // Bang & Olufsen: 3rd bit
                            {
                                if (irmp_pause_time >= BANG_OLUFSEN_START_BIT3_PAUSE_LEN_MIN && irmp_pause_time <= BANG_OLUFSEN_START_BIT3_PAUSE_LEN_MAX)
                                {
                                    ANALYZE_PRINT ("3rd start bit\n");
                                    wait_for_space = 0;
                                    irmp_bit++;
                                }
                                else
                                {                                                   // timing incorrect!
                                    ANALYZE_PRINTF_3 ("error 3a B&O: timing not correct: data bit %d,  pulse: %d, pause: %d\n", irmp_bit, irmp_pulse_time, irmp_pause_time);
                                    ANALYZE_ONLY_NORMAL_PUTCHAR ('\n');
                                    irmp_start_bit_detected = 0;                    // reset flags and wait for next start bit
                                    irmp_pause_time         = 0;
                                }
                            }
                            else if (irmp_bit == 19)                                // Bang & Olufsen: trailer bit
                            {
                                if (irmp_pause_time >= BANG_OLUFSEN_TRAILER_BIT_PAUSE_LEN_MIN && irmp_pause_time <= BANG_OLUFSEN_TRAILER_BIT_PAUSE_LEN_MAX)
                                {
                                    ANALYZE_PRINT ("trailer bit\n");
                                    wait_for_space = 0;
                                    irmp_bit++;
                                }
                                else
                                {                                                   // timing incorrect!
                                    ANALYZE_PRINTF_3 ("error 3b B&O: timing not correct: data bit %d,  pulse: %d, pause: %d\n", irmp_bit, irmp_pulse_time, irmp_pause_time);
                                    ANALYZE_ONLY_NORMAL_PUTCHAR ('\n');
                                    irmp_start_bit_detected = 0;                    // reset flags and wait for next start bit
                                    irmp_pause_time         = 0;
                                }
                            }
                            else
                            {
                                if (irmp_pause_time >= BANG_OLUFSEN_1_PAUSE_LEN_MIN && irmp_pause_time <= BANG_OLUFSEN_1_PAUSE_LEN_MAX)
                                {                                                   // pulse & pause timings correct for "1"?
                                    ANALYZE_PRINT("1\n");
                                    irmp_store_bit (1);
                                    last_value = 1;
                                    wait_for_space = 0;
                                }
                                else if (irmp_pause_time >= BANG_OLUFSEN_0_PAUSE_LEN_MIN && irmp_pause_time <= BANG_OLUFSEN_0_PAUSE_LEN_MAX)
                                {                                                   // pulse & pause timings correct for "0"?
                                    ANALYZE_PRINT("0\n");
                                    irmp_store_bit (0);
                                    last_value = 0;
                                    wait_for_space = 0;
                                }
                                else if (irmp_pause_time >= BANG_OLUFSEN_R_PAUSE_LEN_MIN && irmp_pause_time <= BANG_OLUFSEN_R_PAUSE_LEN_MAX)
                                {
                                    ANALYZE_PUTCHAR (last_value + '0');
                                    ANALYZE_NEWLINE ();
                                    irmp_store_bit (last_value);
                                    wait_for_space = 0;
                                }
                                else
                                {                                                   // timing incorrect!
                                    ANALYZE_PRINTF_3 ("error 3c B&O: timing not correct: data bit %d,  pulse: %d, pause: %d\n", irmp_bit, irmp_pulse_time, irmp_pause_time);
                                    ANALYZE_ONLY_NORMAL_PUTCHAR ('\n');
                                    irmp_start_bit_detected = 0;                    // reset flags and wait for next start bit
                                    irmp_pause_time         = 0;
                                }
                            }
                        }
                        else
                        {                                                           // timing incorrect!
                            ANALYZE_PRINTF_3 ("error 3d B&O: timing not correct: data bit %d,  pulse: %d, pause: %d\n", irmp_bit, irmp_pulse_time, irmp_pause_time);
                            ANALYZE_ONLY_NORMAL_PUTCHAR ('\n');
                            irmp_start_bit_detected = 0;                            // reset flags and wait for next start bit
                            irmp_pause_time         = 0;
                        }
                    }
                    else
#endif // IRMP_SUPPORT_BANG_OLUFSEN_PROTOCOL

#if IRMP_SUPPORT_RCMM_PROTOCOL == 1
                    if (irmp_param.protocol == IRMP_RCMM32_PROTOCOL)
                    {
                        if (irmp_pause_time >= RCMM32_BIT_00_PAUSE_LEN_MIN && irmp_pause_time <= RCMM32_BIT_00_PAUSE_LEN_MAX)
                        {
                          ANALYZE_PUTCHAR('0');
                          ANALYZE_PUTCHAR('0');
                          irmp_store_bit (0);
                            irmp_store_bit (0);
                        }
                        else if (irmp_pause_time >= RCMM32_BIT_01_PAUSE_LEN_MIN && irmp_pause_time <= RCMM32_BIT_01_PAUSE_LEN_MAX)
                        {
                            ANALYZE_PUTCHAR ('0');
                            ANALYZE_PUTCHAR ('1');
                            irmp_store_bit (0);
                            irmp_store_bit (1);
                        }
                        else if (irmp_pause_time >= RCMM32_BIT_10_PAUSE_LEN_MIN && irmp_pause_time <= RCMM32_BIT_10_PAUSE_LEN_MAX)
                        {
                            ANALYZE_PUTCHAR ('1');
                            ANALYZE_PUTCHAR ('0');
                            irmp_store_bit (1);
                            irmp_store_bit (0);
                        }
                        else if (irmp_pause_time >= RCMM32_BIT_11_PAUSE_LEN_MIN && irmp_pause_time <= RCMM32_BIT_11_PAUSE_LEN_MAX)
                        {
                            ANALYZE_PUTCHAR ('1');
                            ANALYZE_PUTCHAR ('1');
                            irmp_store_bit (1);
                            irmp_store_bit (1);
                        }
                        ANALYZE_PRINT ("\n");
                        wait_for_space = 0;
                    }
                    else
#endif

                    if (irmp_pulse_time >= irmp_param.pulse_1_len_min && irmp_pulse_time <= irmp_param.pulse_1_len_max &&
                        irmp_pause_time >= irmp_param.pause_1_len_min && irmp_pause_time <= irmp_param.pause_1_len_max)
                    {                                                               // pulse & pause timings correct for "1"?
                        ANALYZE_PUTCHAR ('1');
                        ANALYZE_NEWLINE ();
                        irmp_store_bit (1);
                        wait_for_space = 0;
                    }
                    else if (irmp_pulse_time >= irmp_param.pulse_0_len_min && irmp_pulse_time <= irmp_param.pulse_0_len_max &&
                             irmp_pause_time >= irmp_param.pause_0_len_min && irmp_pause_time <= irmp_param.pause_0_len_max)
                    {                                                               // pulse & pause timings correct for "0"?
                        ANALYZE_PUTCHAR ('0');
                        ANALYZE_NEWLINE ();
                        irmp_store_bit (0);
                        wait_for_space = 0;
                    }
                    else
#if IRMP_SUPPORT_KATHREIN_PROTOCOL

                    if (irmp_param.protocol == IRMP_KATHREIN_PROTOCOL &&
                        irmp_pulse_time >= KATHREIN_1_PULSE_LEN_MIN && irmp_pulse_time <= KATHREIN_1_PULSE_LEN_MAX &&
                        (((irmp_bit == 8 || irmp_bit == 6) &&
                                irmp_pause_time >= KATHREIN_SYNC_BIT_PAUSE_LEN_MIN && irmp_pause_time <= KATHREIN_SYNC_BIT_PAUSE_LEN_MAX) ||
                         (irmp_bit == 12 &&
                                irmp_pause_time >= KATHREIN_START_BIT_PAUSE_LEN_MIN && irmp_pause_time <= KATHREIN_START_BIT_PAUSE_LEN_MAX)))

                    {
                        if (irmp_bit == 8)
                        {
                            irmp_bit++;
                            ANALYZE_PUTCHAR ('S');
                            ANALYZE_NEWLINE ();
                            irmp_tmp_command <<= 1;
                        }
                        else
                        {
                            ANALYZE_PUTCHAR ('S');
                            ANALYZE_NEWLINE ();
                            irmp_store_bit (1);
                        }
                        wait_for_space = 0;
                    }
                    else
#endif // IRMP_SUPPORT_KATHREIN_PROTOCOL
                    {                                                               // timing incorrect!
                        ANALYZE_PRINTF_3 ("error 3: timing not correct: data bit %d,  pulse: %d, pause: %d\n", irmp_bit, irmp_pulse_time, irmp_pause_time);
                        ANALYZE_ONLY_NORMAL_PUTCHAR ('\n');
                        irmp_start_bit_detected = 0;                                // reset flags and wait for next start bit
                        irmp_pause_time         = 0;
                    }

                    irmp_pulse_time = 1;                                            // set counter to 1, not 0
                }
            }
            else
            {                                                                       // counting the pulse length ...
                if (! irmp_input)                                                   // still light?
                {                                                                   // yes...
                    irmp_pulse_time++;                                              // increment counter
                }
                else
                {                                                                   // now it's dark!
                    wait_for_space  = 1;                                            // let's count the time (see above)
                    irmp_pause_time = 1;                                            // set pause counter to 1, not 0

#if IRMP_SUPPORT_RCII_PROTOCOL == 1
                    if (irmp_param.protocol == IRMP_RCII_PROTOCOL && waiting_for_2nd_pulse)
                    {
                        // fm: output is "1000 466" or "1533 466"
                        // printf ("fm: %d %d\n", irmp_pulse_time * 1000000 / F_INTERRUPTS, RCII_BIT_LEN * 1000000 / F_INTERRUPTS);
                        irmp_pulse_time -= RCII_BIT_LEN;
                        last_value = 0;

                        ANALYZE_PRINTF_1 ("RCII: got 2nd pulse, irmp_pulse_time = %d\n", irmp_pulse_time);
                        waiting_for_2nd_pulse = 0;
                    }
#endif
                }
            }

            if (irmp_start_bit_detected && irmp_bit == irmp_param.complete_len && irmp_param.stop_bit == 0)    // enough bits received?
            {
                if (last_irmp_command == irmp_tmp_command && key_repetition_len < AUTO_FRAME_REPETITION_LEN)
                {
                    repetition_frame_number++;
                }
                else
                {
                    repetition_frame_number = 0;
                }

#if IRMP_SUPPORT_SIRCS_PROTOCOL == 1
                // if SIRCS protocol and the code will be repeated within 50 ms, we will ignore 2nd and 3rd repetition frame
                if (irmp_param.protocol == IRMP_SIRCS_PROTOCOL && (repetition_frame_number == 1 || repetition_frame_number == 2))
                {
                    ANALYZE_PRINTF_3 ("code skipped: SIRCS auto repetition frame #%d, counter = %d, auto repetition len = %d\n",
                                    repetition_frame_number + 1, key_repetition_len, AUTO_FRAME_REPETITION_LEN);
                    key_repetition_len = 0;
                }
                else
#endif

#if IRMP_SUPPORT_ORTEK_PROTOCOL == 1
                // if ORTEK protocol and the code will be repeated within 50 ms, we will ignore 2nd repetition frame
                if (irmp_param.protocol == IRMP_ORTEK_PROTOCOL && repetition_frame_number == 1)
                {
                    ANALYZE_PRINTF_3 ("code skipped: ORTEK auto repetition frame #%d, counter = %d, auto repetition len = %d\n",
                                    repetition_frame_number + 1, key_repetition_len, AUTO_FRAME_REPETITION_LEN);
                    key_repetition_len = 0;
                }
                else
#endif

#if 0 && IRMP_SUPPORT_KASEIKYO_PROTOCOL == 1    // fm 2015-12-02: don't ignore every 2nd frame
                // if KASEIKYO protocol and the code will be repeated within 50 ms, we will ignore 2nd repetition frame
                if (irmp_param.protocol == IRMP_KASEIKYO_PROTOCOL && repetition_frame_number == 1)
                {
                    ANALYZE_PRINTF_3 ("code skipped: KASEIKYO auto repetition frame #%d, counter = %d, auto repetition len = %d\n",
                                    repetition_frame_number + 1, key_repetition_len, AUTO_FRAME_REPETITION_LEN);
                    key_repetition_len = 0;
                }
                else
#endif

#if 0 && IRMP_SUPPORT_SAMSUNG_PROTOCOL == 1     // fm 2015-12-02: don't ignore every 2nd frame
                // if SAMSUNG32 or SAMSUNG48 protocol and the code will be repeated within 50 ms, we will ignore every 2nd frame
                if ((irmp_param.protocol == IRMP_SAMSUNG32_PROTOCOL || irmp_param.protocol == IRMP_SAMSUNG48_PROTOCOL) && (repetition_frame_number & 0x01))
                {
                    ANALYZE_PRINTF_3 ("code skipped: SAMSUNG32/SAMSUNG48 auto repetition frame #%d, counter = %d, auto repetition len = %d\n",
                                    repetition_frame_number + 1, key_repetition_len, AUTO_FRAME_REPETITION_LEN);
                    key_repetition_len = 0;
                }
                else
#endif

#if IRMP_SUPPORT_NUBERT_PROTOCOL == 1
                // if NUBERT protocol and the code will be repeated within 50 ms, we will ignore every 2nd frame
                if (irmp_param.protocol == IRMP_NUBERT_PROTOCOL && (repetition_frame_number & 0x01))
                {
                    ANALYZE_PRINTF_3 ("code skipped: NUBERT auto repetition frame #%d, counter = %d, auto repetition len = %d\n",
                                    repetition_frame_number + 1, key_repetition_len, AUTO_FRAME_REPETITION_LEN);
                    key_repetition_len = 0;
                }
                else
#endif

#if IRMP_SUPPORT_SPEAKER_PROTOCOL == 1
                // if SPEAKER protocol and the code will be repeated within 50 ms, we will ignore every 2nd frame
                if (irmp_param.protocol == IRMP_SPEAKER_PROTOCOL && (repetition_frame_number & 0x01))
                {
                    ANALYZE_PRINTF_3 ("code skipped: SPEAKER auto repetition frame #%d, counter = %d, auto repetition len = %d\n",
                                    repetition_frame_number + 1, key_repetition_len, AUTO_FRAME_REPETITION_LEN);
                    key_repetition_len = 0;
                }
                else
#endif

                {
                    ANALYZE_PRINTF_2 ("%8.3fms code detected, length = %d\n", (float) (time_counter * 1000) / F_INTERRUPTS, irmp_bit);
                    irmp_ir_detected = TRUE;

#if IRMP_SUPPORT_DENON_PROTOCOL == 1
                    if (irmp_param.protocol == IRMP_DENON_PROTOCOL)
                    {                                                               // check for repetition frame
                        if ((~irmp_tmp_command & 0x3FF) == last_irmp_denon_command) // command bits must be inverted
                        {
                            irmp_tmp_command = last_irmp_denon_command;             // use command received before!
                            last_irmp_denon_command = 0;

                            irmp_protocol = irmp_param.protocol;                    // store protocol
                            irmp_address = irmp_tmp_address;                        // store address
                            irmp_command = irmp_tmp_command;                        // store command
                        }
                        else
                        {
                            if ((irmp_tmp_command & 0x01) == 0x00)
                            {
                                ANALYZE_PRINTF_1 ("%8.3fms info Denon: waiting for inverted command repetition\n", (float) (time_counter * 1000) / F_INTERRUPTS);
                                last_irmp_denon_command = irmp_tmp_command;
                                denon_repetition_len = 0;
                                irmp_ir_detected = FALSE;
                            }
                            else
                            {
                                ANALYZE_PRINTF_1 ("%8.3fms warning Denon: got unexpected inverted command, ignoring it\n", (float) (time_counter * 1000) / F_INTERRUPTS);
                                last_irmp_denon_command = 0;
                                irmp_ir_detected = FALSE;
                            }
                        }
                    }
                    else
#endif // IRMP_SUPPORT_DENON_PROTOCOL

#if IRMP_SUPPORT_GRUNDIG_PROTOCOL == 1
                    if (irmp_param.protocol == IRMP_GRUNDIG_PROTOCOL && irmp_tmp_command == 0x01ff)
                    {                                                               // Grundig start frame?
                        ANALYZE_PRINT ("Detected GRUNDIG start frame, ignoring it\n");
                        irmp_ir_detected = FALSE;
                    }
                    else
#endif // IRMP_SUPPORT_GRUNDIG_PROTOCOL

#if IRMP_SUPPORT_NOKIA_PROTOCOL == 1
                    if (irmp_param.protocol == IRMP_NOKIA_PROTOCOL && irmp_tmp_address == 0x00ff && irmp_tmp_command == 0x00fe)
                    {                                                               // Nokia start frame?
                        ANALYZE_PRINT ("Detected NOKIA start frame, ignoring it\n");
                        irmp_ir_detected = FALSE;
                    }
                    else
#endif // IRMP_SUPPORT_NOKIA_PROTOCOL
                    {
#if IRMP_SUPPORT_NEC_PROTOCOL == 1
                        if (irmp_param.protocol == IRMP_NEC_PROTOCOL && irmp_bit == 0)  // repetition frame
                        {
                            if (key_repetition_len < NEC_FRAME_REPEAT_PAUSE_LEN_MAX)
                            {
                                ANALYZE_PRINTF_1 ("Detected NEC repetition frame, key_repetition_len = %d\n", key_repetition_len);
                                ANALYZE_ONLY_NORMAL_PRINT("REPETETION FRAME                ");
                                irmp_tmp_address = last_irmp_address;                   // address is last address
                                irmp_tmp_command = last_irmp_command;                   // command is last command
                                irmp_flags |= IRMP_FLAG_REPETITION;
                                key_repetition_len = 0;
                            }
                            else
                            {
                                ANALYZE_PRINTF_2 ("Detected NEC repetition frame, ignoring it: timeout occured, key_repetition_len = %d > %d\n",
                                                key_repetition_len, NEC_FRAME_REPEAT_PAUSE_LEN_MAX);
                                irmp_ir_detected = FALSE;
                            }
                        }
#endif // IRMP_SUPPORT_NEC_PROTOCOL

#if IRMP_SUPPORT_KASEIKYO_PROTOCOL == 1
                        if (irmp_param.protocol == IRMP_KASEIKYO_PROTOCOL)
                        {
                            uint_fast8_t xor_value;

                            xor_value = (xor_check[0] & 0x0F) ^ ((xor_check[0] & 0xF0) >> 4) ^ (xor_check[1] & 0x0F) ^ ((xor_check[1] & 0xF0) >> 4);

                            if (xor_value != (xor_check[2] & 0x0F))
                            {
                                ANALYZE_PRINTF_2 ("error 4: wrong XOR check for customer id: 0x%1x 0x%1x\n", xor_value, xor_check[2] & 0x0F);
                                irmp_ir_detected = FALSE;
                            }

                            xor_value = xor_check[2] ^ xor_check[3] ^ xor_check[4];

                            if (xor_value != xor_check[5])
                            {
                                ANALYZE_PRINTF_2 ("error 5: wrong XOR check for data bits: 0x%02x 0x%02x\n", xor_value, xor_check[5]);
                                irmp_ir_detected = FALSE;
                            }

                            irmp_flags |= genre2;       // write the genre2 bits into MSB of the flag byte
                        }
#endif // IRMP_SUPPORT_KASEIKYO_PROTOCOL == 1

#if IRMP_SUPPORT_ORTEK_PROTOCOL == 1
                        if (irmp_param.protocol == IRMP_ORTEK_PROTOCOL)
                        {
                            if (parity == PARITY_CHECK_FAILED)
                            {
                                ANALYZE_PRINT ("error 6: parity check failed\n");
                                irmp_ir_detected = FALSE;
                            }

                            if ((irmp_tmp_address & 0x03) == 0x02)
                            {
                                ANALYZE_PRINT ("code skipped: ORTEK end of transmission frame (key release)\n");
                                irmp_ir_detected = FALSE;
                            }
                            irmp_tmp_address >>= 2;
                        }
#endif // IRMP_SUPPORT_ORTEK_PROTOCOL == 1

#if IRMP_SUPPORT_MITSU_HEAVY_PROTOCOL == 1
                        if (irmp_param.protocol == IRMP_MITSU_HEAVY_PROTOCOL)
                        {
                            check = irmp_tmp_command >> 8;                    // inverted upper byte == lower byte?
                            check = ~ check;
                            if (check == (irmp_tmp_command & 0xFF)) {         //ok:
                              irmp_tmp_command &= 0xFF;
                            }
                            else  mitsu_parity = PARITY_CHECK_FAILED;
                            if (mitsu_parity == PARITY_CHECK_FAILED)
                            {
                                ANALYZE_PRINT ("error 7: parity check failed\n");
                                irmp_ir_detected = FALSE;
                            }
                        }
#endif // IRMP_SUPPORT_MITSU_HEAVY_PROTOCOL

#if IRMP_SUPPORT_RC6_PROTOCOL == 1
                        if (irmp_param.protocol == IRMP_RC6_PROTOCOL && irmp_param.complete_len == RC6_COMPLETE_DATA_LEN_LONG)     // RC6 mode = 6?
                        {
                            irmp_protocol = IRMP_RC6A_PROTOCOL;
                        }
                        else
#endif // IRMP_SUPPORT_RC6_PROTOCOL == 1
                        {
                            irmp_protocol = irmp_param.protocol;
                        }

#if IRMP_SUPPORT_FDC_PROTOCOL == 1
                        if (irmp_param.protocol == IRMP_FDC_PROTOCOL)
                        {
                            if (irmp_tmp_command & 0x000F)                          // released key?
                            {
                                irmp_tmp_command = (irmp_tmp_command >> 4) | 0x80;  // yes, set bit 7
                            }
                            else
                            {
                                irmp_tmp_command >>= 4;                             // no, it's a pressed key
                            }
                            irmp_tmp_command |= (irmp_tmp_address << 2) & 0x0F00;   // 000000CCCCAAAAAA -> 0000CCCC00000000
                            irmp_tmp_address &= 0x003F;
                        }
#endif

                        irmp_address = irmp_tmp_address;                            // store address
#if IRMP_SUPPORT_NEC_PROTOCOL == 1
                        if (irmp_param.protocol == IRMP_NEC_PROTOCOL)
                        {
                            last_irmp_address = irmp_tmp_address;                   // store as last address, too
                        }
#endif

#if IRMP_SUPPORT_RC5_PROTOCOL == 1
                        if (irmp_param.protocol == IRMP_RC5_PROTOCOL)
                        {
                            irmp_tmp_command |= rc5_cmd_bit6;                       // store bit 6
                        }
#endif
#if IRMP_SUPPORT_S100_PROTOCOL == 1
                        if (irmp_param.protocol == IRMP_S100_PROTOCOL)
                        {
                            irmp_tmp_command |= rc5_cmd_bit6;                       // store bit 6
                        }
#endif
                        irmp_command = irmp_tmp_command;                            // store command

#if IRMP_SUPPORT_SAMSUNG_PROTOCOL == 1
                        irmp_id = irmp_tmp_id;
#endif
                    }
                }

                if (irmp_ir_detected)
                {
                    if (last_irmp_command == irmp_tmp_command &&
                        last_irmp_address == irmp_tmp_address &&
                        key_repetition_len < IRMP_KEY_REPETITION_LEN)
                    {
                        irmp_flags |= IRMP_FLAG_REPETITION;
                    }

                    last_irmp_address = irmp_tmp_address;                           // store as last address, too
                    last_irmp_command = irmp_tmp_command;                           // store as last command, too

                    key_repetition_len = 0;
                }
                else
                {
                    ANALYZE_ONLY_NORMAL_PUTCHAR ('\n');
                }

                irmp_start_bit_detected = 0;                                        // and wait for next start bit
                irmp_tmp_command        = 0;
                irmp_pulse_time         = 0;
                irmp_pause_time         = 0;

#if IRMP_SUPPORT_JVC_PROTOCOL == 1
                if (irmp_protocol == IRMP_JVC_PROTOCOL)                             // the stop bit of JVC frame is also start bit of next frame
                {                                                                   // set pulse time here!
                    irmp_pulse_time = ((uint_fast8_t)(F_INTERRUPTS * JVC_START_BIT_PULSE_TIME));
                }
#endif // IRMP_SUPPORT_JVC_PROTOCOL == 1
            }
        }
    }

#if defined(STELLARIS_ARM_CORTEX_M4)
    // Clear the timer interrupt
    TimerIntClear(TIMER1_BASE, TIMER_TIMA_TIMEOUT);
#endif

#if (defined(_CHIBIOS_RT_) || defined(_CHIBIOS_NIL_)) && IRMP_USE_EVENT == 1
    if (IRMP_EVENT_THREAD_PTR != NULL && irmp_ir_detected)
        chEvtSignalI(IRMP_EVENT_THREAD_PTR,IRMP_EVENT_BIT);
#endif

#if IRMP_USE_IDLE_CALL == 1
    // check if there is no ongoing transmission or repetition
    if (!irmp_start_bit_detected && !irmp_pulse_time
        && key_repetition_len > IRMP_KEY_REPETITION_LEN)
    {
        // no ongoing transmission
        // enough time passed since last decoded signal that a repetition won't affect our output

        irmp_idle();
    }
#endif // IRMP_USE_IDLE_CALL

    return (irmp_ir_detected);
}

