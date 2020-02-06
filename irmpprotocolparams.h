

#ifndef IRMPPROTOPARAMS_H
#define IRMPPROTOPARAMS_H

#include "irmp.h"

#ifdef __cplusplus
extern "C"
{
#endif

  const char* const
  irmp_protocol_names[IRMP_N_PROTOCOLS + 1] PROGMEM;

  typedef struct
  {
    uint_fast8_t    protocol;                                                // ir protocol
    uint_fast8_t    pulse_1_len_min;                                         // minimum length of pulse with bit value 1
    uint_fast8_t    pulse_1_len_max;                                         // maximum length of pulse with bit value 1
    uint_fast8_t    pause_1_len_min;                                         // minimum length of pause with bit value 1
    uint_fast8_t    pause_1_len_max;                                         // maximum length of pause with bit value 1
    uint_fast8_t    pulse_0_len_min;                                         // minimum length of pulse with bit value 0
    uint_fast8_t    pulse_0_len_max;                                         // maximum length of pulse with bit value 0
    uint_fast8_t    pause_0_len_min;                                         // minimum length of pause with bit value 0
    uint_fast8_t    pause_0_len_max;                                         // maximum length of pause with bit value 0
    uint_fast8_t    address_offset;                                          // address offset
    uint_fast8_t    address_end;                                             // end of address
    uint_fast8_t    command_offset;                                          // command offset
    uint_fast8_t    command_end;                                             // end of command
    uint_fast8_t    complete_len;                                            // complete length of frame
    uint_fast8_t    stop_bit;                                                // flag: frame has stop bit
    uint_fast8_t    lsb_first;                                               // flag: LSB first
    uint_fast8_t    flags;                                                   // some flags
  } IRMP_PARAMETER;

#if IRMP_SUPPORT_SIRCS_PROTOCOL == 1
  extern const PROGMEM IRMP_PARAMETER sircs_param;
#endif

#if IRMP_SUPPORT_NEC_PROTOCOL == 1
  extern const PROGMEM IRMP_PARAMETER nec_param;
  extern const PROGMEM IRMP_PARAMETER nec_rep_param;
#endif

#if IRMP_SUPPORT_NEC42_PROTOCOL == 1
  extern const PROGMEM IRMP_PARAMETER nec42_param;
#endif

#if IRMP_SUPPORT_LGAIR_PROTOCOL == 1
  extern const PROGMEM IRMP_PARAMETER lgair_param;
#endif

#if IRMP_SUPPORT_SAMSUNG_PROTOCOL == 1
  extern const PROGMEM IRMP_PARAMETER samsung_param;
#endif

#if IRMP_SUPPORT_SAMSUNGAH_PROTOCOL == 1
  extern const PROGMEM IRMP_PARAMETER samsungah_param;
#endif

#if IRMP_SUPPORT_TELEFUNKEN_PROTOCOL == 1
  extern const PROGMEM IRMP_PARAMETER telefunken_param;
#endif

#if IRMP_SUPPORT_MATSUSHITA_PROTOCOL == 1
  extern const PROGMEM IRMP_PARAMETER matsushita_param;
#endif

#if IRMP_SUPPORT_KASEIKYO_PROTOCOL == 1
  extern const PROGMEM IRMP_PARAMETER kaseikyo_param;
#endif

#if IRMP_SUPPORT_PANASONIC_PROTOCOL == 1
  extern const PROGMEM IRMP_PARAMETER panasonic_param;
#endif

#if IRMP_SUPPORT_MITSU_HEAVY_PROTOCOL == 1
  extern const PROGMEM IRMP_PARAMETER mitsu_heavy_param;
#endif

#if IRMP_SUPPORT_VINCENT_PROTOCOL == 1
  extern const PROGMEM IRMP_PARAMETER vincent_param;
#endif

#if IRMP_SUPPORT_RECS80_PROTOCOL == 1
  extern const PROGMEM IRMP_PARAMETER recs80_param;
#endif

#if IRMP_SUPPORT_RC5_PROTOCOL == 1
  extern const PROGMEM IRMP_PARAMETER rc5_param;
#endif

#if IRMP_SUPPORT_RCII_PROTOCOL == 1
  extern const PROGMEM IRMP_PARAMETER rcii_param;
#endif

#if IRMP_SUPPORT_S100_PROTOCOL == 1
  extern const PROGMEM IRMP_PARAMETER s100_param;
#endif

#if IRMP_SUPPORT_DENON_PROTOCOL == 1
  extern const PROGMEM IRMP_PARAMETER denon_param;
#endif

#if IRMP_SUPPORT_RC6_PROTOCOL == 1
  extern const PROGMEM IRMP_PARAMETER rc6_param;
#endif

#if IRMP_SUPPORT_RECS80EXT_PROTOCOL == 1
  extern const PROGMEM IRMP_PARAMETER recs80ext_param;
#endif

#if IRMP_SUPPORT_NUBERT_PROTOCOL == 1
  extern const PROGMEM IRMP_PARAMETER nubert_param;
#endif

#if IRMP_SUPPORT_FAN_PROTOCOL == 1
  extern const PROGMEM IRMP_PARAMETER fan_param;
#endif

#if IRMP_SUPPORT_SPEAKER_PROTOCOL == 1
  extern const PROGMEM IRMP_PARAMETER speaker_param;
#endif

#if IRMP_SUPPORT_BANG_OLUFSEN_PROTOCOL == 1
  extern const PROGMEM IRMP_PARAMETER bang_olufsen_param;
#endif

#if IRMP_SUPPORT_GRUNDIG_NOKIA_IR60_PROTOCOL == 1

  uint_fast8_t first_bit;
  extern const PROGMEM IRMP_PARAMETER grundig_param;
#endif

#if IRMP_SUPPORT_SIEMENS_OR_RUWIDO_PROTOCOL == 1
  extern const PROGMEM IRMP_PARAMETER ruwido_param;
#endif

#if IRMP_SUPPORT_FDC_PROTOCOL == 1
  extern const PROGMEM IRMP_PARAMETER fdc_param;
#endif

#if IRMP_SUPPORT_RCCAR_PROTOCOL == 1
  extern const PROGMEM IRMP_PARAMETER rccar_param;
#endif

#if IRMP_SUPPORT_NIKON_PROTOCOL == 1
  extern const PROGMEM IRMP_PARAMETER nikon_param;
#endif

#if IRMP_SUPPORT_KATHREIN_PROTOCOL == 1
  extern const PROGMEM IRMP_PARAMETER kathrein_param;
#endif

#if IRMP_SUPPORT_NETBOX_PROTOCOL == 1
  extern const PROGMEM IRMP_PARAMETER netbox_param;
#endif

#if IRMP_SUPPORT_LEGO_PROTOCOL == 1
  extern const PROGMEM IRMP_PARAMETER lego_param;
#endif

#if IRMP_SUPPORT_IRMP16_PROTOCOL == 1
  extern const PROGMEM IRMP_PARAMETER irmp16_param;
#endif

#if IRMP_SUPPORT_GREE_PROTOCOL == 1
  extern const PROGMEM IRMP_PARAMETER gree_param;
#endif

#if IRMP_SUPPORT_THOMSON_PROTOCOL == 1
  extern const PROGMEM IRMP_PARAMETER thomson_param;
#endif

#if IRMP_SUPPORT_BOSE_PROTOCOL == 1
  extern const PROGMEM IRMP_PARAMETER bose_param;
#endif

#if IRMP_SUPPORT_A1TVBOX_PROTOCOL == 1
  extern const PROGMEM IRMP_PARAMETER a1tvbox_param;
#endif

#if IRMP_SUPPORT_MERLIN_PROTOCOL == 1
  extern const PROGMEM IRMP_PARAMETER merlin_param;
#endif

#if IRMP_SUPPORT_ORTEK_PROTOCOL == 1
  extern const PROGMEM IRMP_PARAMETER ortek_param;
#endif

#if IRMP_SUPPORT_ROOMBA_PROTOCOL == 1
  extern const PROGMEM IRMP_PARAMETER roomba_param;
#endif

#if IRMP_SUPPORT_RCMM_PROTOCOL == 1
  extern const PROGMEM IRMP_PARAMETER rcmm_param;
#endif

#if IRMP_SUPPORT_PENTAX_PROTOCOL == 1
  extern const PROGMEM IRMP_PARAMETER pentax_param;
#endif

#if IRMP_SUPPORT_ACP24_PROTOCOL == 1
  extern const PROGMEM IRMP_PARAMETER acp24_param;
#endif

#if IRMP_SUPPORT_METZ_PROTOCOL == 1
  extern const PROGMEM IRMP_PARAMETER metz_param;
#endif

#if IRMP_SUPPORT_RADIO1_PROTOCOL == 1
  extern const PROGMEM IRMP_PARAMETER radio1_param;
#endif

#ifdef __cplusplus
}
#endif

#endif

