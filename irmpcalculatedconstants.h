/*---------------------------------------------------------------------------------------------------------------------------------------------------
 * irmpcalculatedconstants.h - 
 *
 * Copyright (c) 2009-2019 Frank Meyer - frank(at)fli4l.de
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *---------------------------------------------------------------------------------------------------------------------------------------------------
 */


#ifndef IRMPCALCCONSTANTS_H
#define IRMPCALCCONSTANTS_H

#ifdef __cplusplus
extern "C"
{
#endif

#if IRMP_SUPPORT_GRUNDIG_PROTOCOL == 1 || IRMP_SUPPORT_NOKIA_PROTOCOL == 1 || IRMP_SUPPORT_IR60_PROTOCOL == 1
#  define IRMP_SUPPORT_GRUNDIG_NOKIA_IR60_PROTOCOL  1
#else
#  define IRMP_SUPPORT_GRUNDIG_NOKIA_IR60_PROTOCOL  0
#endif

#if IRMP_SUPPORT_SIEMENS_PROTOCOL == 1 || IRMP_SUPPORT_RUWIDO_PROTOCOL == 1
#  define IRMP_SUPPORT_SIEMENS_OR_RUWIDO_PROTOCOL   1
#else
#  define IRMP_SUPPORT_SIEMENS_OR_RUWIDO_PROTOCOL   0
#endif

#if IRMP_SUPPORT_RC5_PROTOCOL == 1 ||                   \
    IRMP_SUPPORT_RCII_PROTOCOL == 1 ||                  \
    IRMP_SUPPORT_S100_PROTOCOL == 1 ||                  \
    IRMP_SUPPORT_RC6_PROTOCOL == 1 ||                   \
    IRMP_SUPPORT_GRUNDIG_NOKIA_IR60_PROTOCOL == 1 ||    \
    IRMP_SUPPORT_SIEMENS_OR_RUWIDO_PROTOCOL == 1 ||     \
    IRMP_SUPPORT_IR60_PROTOCOL == 1 ||                  \
    IRMP_SUPPORT_A1TVBOX_PROTOCOL == 1 ||               \
    IRMP_SUPPORT_MERLIN_PROTOCOL == 1 ||                \
    IRMP_SUPPORT_ORTEK_PROTOCOL == 1
#  define IRMP_SUPPORT_MANCHESTER                   1
#else
#  define IRMP_SUPPORT_MANCHESTER                   0
#endif

#if IRMP_SUPPORT_NETBOX_PROTOCOL == 1
#  define IRMP_SUPPORT_SERIAL                       1
#else
#  define IRMP_SUPPORT_SERIAL                       0
#endif



#define IRMP_KEY_REPETITION_LEN                 (uint_fast16_t)(F_INTERRUPTS * 150.0e-3 + 0.5)           // autodetect key repetition within 150 msec

#define MIN_TOLERANCE_00                        1.0                           // -0%
#define MAX_TOLERANCE_00                        1.0                           // +0%

#define MIN_TOLERANCE_02                        0.98                          // -2%
#define MAX_TOLERANCE_02                        1.02                          // +2%

#define MIN_TOLERANCE_03                        0.97                          // -3%
#define MAX_TOLERANCE_03                        1.03                          // +3%

#define MIN_TOLERANCE_05                        0.95                          // -5%
#define MAX_TOLERANCE_05                        1.05                          // +5%

#define MIN_TOLERANCE_10                        0.9                           // -10%
#define MAX_TOLERANCE_10                        1.1                           // +10%

#define MIN_TOLERANCE_15                        0.85                          // -15%
#define MAX_TOLERANCE_15                        1.15                          // +15%

#define MIN_TOLERANCE_20                        0.8                           // -20%
#define MAX_TOLERANCE_20                        1.2                           // +20%

#define MIN_TOLERANCE_30                        0.7                           // -30%
#define MAX_TOLERANCE_30                        1.3                           // +30%

#define MIN_TOLERANCE_40                        0.6                           // -40%
#define MAX_TOLERANCE_40                        1.4                           // +40%

#define MIN_TOLERANCE_50                        0.5                           // -50%
#define MAX_TOLERANCE_50                        1.5                           // +50%

#define MIN_TOLERANCE_60                        0.4                           // -60%
#define MAX_TOLERANCE_60                        1.6                           // +60%

#define MIN_TOLERANCE_70                        0.3                           // -70%
#define MAX_TOLERANCE_70                        1.7                           // +70%

#define SIRCS_START_BIT_PULSE_LEN_MIN           ((uint_fast8_t)(F_INTERRUPTS * SIRCS_START_BIT_PULSE_TIME * MIN_TOLERANCE_10 + 0.5) - 1)
#define SIRCS_START_BIT_PULSE_LEN_MAX           ((uint_fast8_t)(F_INTERRUPTS * SIRCS_START_BIT_PULSE_TIME * MAX_TOLERANCE_10 + 0.5) + 1)
#define SIRCS_START_BIT_PAUSE_LEN_MIN           ((uint_fast8_t)(F_INTERRUPTS * SIRCS_START_BIT_PAUSE_TIME * MIN_TOLERANCE_20 + 0.5) - 1)
#if IRMP_SUPPORT_NETBOX_PROTOCOL                // only 5% to avoid conflict with NETBOX:
#  define SIRCS_START_BIT_PAUSE_LEN_MAX         ((uint_fast8_t)(F_INTERRUPTS * SIRCS_START_BIT_PAUSE_TIME * MAX_TOLERANCE_05 + 0.5))
#else                                           // only 5% + 1 to avoid conflict with RC6:
#  define SIRCS_START_BIT_PAUSE_LEN_MAX         ((uint_fast8_t)(F_INTERRUPTS * SIRCS_START_BIT_PAUSE_TIME * MAX_TOLERANCE_05 + 0.5) + 1)
#endif
#define SIRCS_1_PULSE_LEN_MIN                   ((uint_fast8_t)(F_INTERRUPTS * SIRCS_1_PULSE_TIME * MIN_TOLERANCE_10 + 0.5) - 1)
#define SIRCS_1_PULSE_LEN_MAX                   ((uint_fast8_t)(F_INTERRUPTS * SIRCS_1_PULSE_TIME * MAX_TOLERANCE_10 + 0.5) + 1)
#define SIRCS_0_PULSE_LEN_MIN                   ((uint_fast8_t)(F_INTERRUPTS * SIRCS_0_PULSE_TIME * MIN_TOLERANCE_10 + 0.5) - 1)
#define SIRCS_0_PULSE_LEN_MAX                   ((uint_fast8_t)(F_INTERRUPTS * SIRCS_0_PULSE_TIME * MAX_TOLERANCE_10 + 0.5) + 1)
#define SIRCS_PAUSE_LEN_MIN                     ((uint_fast8_t)(F_INTERRUPTS * SIRCS_PAUSE_TIME * MIN_TOLERANCE_10 + 0.5) - 1)
#define SIRCS_PAUSE_LEN_MAX                     ((uint_fast8_t)(F_INTERRUPTS * SIRCS_PAUSE_TIME * MAX_TOLERANCE_10 + 0.5) + 1)

#define NEC_START_BIT_PULSE_LEN_MIN             ((uint_fast8_t)(F_INTERRUPTS * NEC_START_BIT_PULSE_TIME * MIN_TOLERANCE_30 + 0.5) - 1)
#define NEC_START_BIT_PULSE_LEN_MAX             ((uint_fast8_t)(F_INTERRUPTS * NEC_START_BIT_PULSE_TIME * MAX_TOLERANCE_30 + 0.5) + 1)
#define NEC_START_BIT_PAUSE_LEN_MIN             ((uint_fast8_t)(F_INTERRUPTS * NEC_START_BIT_PAUSE_TIME * MIN_TOLERANCE_30 + 0.5) - 1)
#define NEC_START_BIT_PAUSE_LEN_MAX             ((uint_fast8_t)(F_INTERRUPTS * NEC_START_BIT_PAUSE_TIME * MAX_TOLERANCE_30 + 0.5) + 1)
#define NEC_REPEAT_START_BIT_PAUSE_LEN_MIN      ((uint_fast8_t)(F_INTERRUPTS * NEC_REPEAT_START_BIT_PAUSE_TIME * MIN_TOLERANCE_30 + 0.5) - 1)
#define NEC_REPEAT_START_BIT_PAUSE_LEN_MAX      ((uint_fast8_t)(F_INTERRUPTS * NEC_REPEAT_START_BIT_PAUSE_TIME * MAX_TOLERANCE_30 + 0.5) + 1)
#define NEC_PULSE_LEN_MIN                       ((uint_fast8_t)(F_INTERRUPTS * NEC_PULSE_TIME * MIN_TOLERANCE_30 + 0.5) - 1)
#define NEC_PULSE_LEN_MAX                       ((uint_fast8_t)(F_INTERRUPTS * NEC_PULSE_TIME * MAX_TOLERANCE_30 + 0.5) + 1)
#define NEC_1_PAUSE_LEN_MIN                     ((uint_fast8_t)(F_INTERRUPTS * NEC_1_PAUSE_TIME * MIN_TOLERANCE_30 + 0.5) - 1)
#define NEC_1_PAUSE_LEN_MAX                     ((uint_fast8_t)(F_INTERRUPTS * NEC_1_PAUSE_TIME * MAX_TOLERANCE_30 + 0.5) + 1)
#define NEC_0_PAUSE_LEN_MIN                     ((uint_fast8_t)(F_INTERRUPTS * NEC_0_PAUSE_TIME * MIN_TOLERANCE_30 + 0.5) - 1)
#define NEC_0_PAUSE_LEN_MAX                     ((uint_fast8_t)(F_INTERRUPTS * NEC_0_PAUSE_TIME * MAX_TOLERANCE_30 + 0.5) + 1)
// autodetect nec repetition frame within 50 msec:
// NEC seems to send the first repetition frame after 40ms, further repetition frames after 100 ms
#if 0
#define NEC_FRAME_REPEAT_PAUSE_LEN_MAX          (uint_fast16_t)(F_INTERRUPTS * NEC_FRAME_REPEAT_PAUSE_TIME * MAX_TOLERANCE_20 + 0.5)
#else
#define NEC_FRAME_REPEAT_PAUSE_LEN_MAX          (uint_fast16_t)(F_INTERRUPTS * 100.0e-3 * MAX_TOLERANCE_20 + 0.5)
#endif

#define SAMSUNG_START_BIT_PULSE_LEN_MIN         ((uint_fast8_t)(F_INTERRUPTS * SAMSUNG_START_BIT_PULSE_TIME * MIN_TOLERANCE_10 + 0.5) - 1)
#define SAMSUNG_START_BIT_PULSE_LEN_MAX         ((uint_fast8_t)(F_INTERRUPTS * SAMSUNG_START_BIT_PULSE_TIME * MAX_TOLERANCE_10 + 0.5) + 1)
#define SAMSUNG_START_BIT_PAUSE_LEN_MIN         ((uint_fast8_t)(F_INTERRUPTS * SAMSUNG_START_BIT_PAUSE_TIME * MIN_TOLERANCE_10 + 0.5) - 1)
#define SAMSUNG_START_BIT_PAUSE_LEN_MAX         ((uint_fast8_t)(F_INTERRUPTS * SAMSUNG_START_BIT_PAUSE_TIME * MAX_TOLERANCE_10 + 0.5) + 1)
#define SAMSUNG_PULSE_LEN_MIN                   ((uint_fast8_t)(F_INTERRUPTS * SAMSUNG_PULSE_TIME * MIN_TOLERANCE_30 + 0.5) - 1)
#define SAMSUNG_PULSE_LEN_MAX                   ((uint_fast8_t)(F_INTERRUPTS * SAMSUNG_PULSE_TIME * MAX_TOLERANCE_30 + 0.5) + 1)
#define SAMSUNG_1_PAUSE_LEN_MIN                 ((uint_fast8_t)(F_INTERRUPTS * SAMSUNG_1_PAUSE_TIME * MIN_TOLERANCE_30 + 0.5) - 1)
#define SAMSUNG_1_PAUSE_LEN_MAX                 ((uint_fast8_t)(F_INTERRUPTS * SAMSUNG_1_PAUSE_TIME * MAX_TOLERANCE_30 + 0.5) + 1)
#define SAMSUNG_0_PAUSE_LEN_MIN                 ((uint_fast8_t)(F_INTERRUPTS * SAMSUNG_0_PAUSE_TIME * MIN_TOLERANCE_30 + 0.5) - 1)
#define SAMSUNG_0_PAUSE_LEN_MAX                 ((uint_fast8_t)(F_INTERRUPTS * SAMSUNG_0_PAUSE_TIME * MAX_TOLERANCE_30 + 0.5) + 1)

#define SAMSUNGAH_START_BIT_PULSE_LEN_MIN       ((uint_fast8_t)(F_INTERRUPTS * SAMSUNGAH_START_BIT_PULSE_TIME * MIN_TOLERANCE_10 + 0.5) - 1)
#define SAMSUNGAH_START_BIT_PULSE_LEN_MAX       ((uint_fast8_t)(F_INTERRUPTS * SAMSUNGAH_START_BIT_PULSE_TIME * MAX_TOLERANCE_10 + 0.5) + 1)
#define SAMSUNGAH_START_BIT_PAUSE_LEN_MIN       ((uint_fast8_t)(F_INTERRUPTS * SAMSUNGAH_START_BIT_PAUSE_TIME * MIN_TOLERANCE_10 + 0.5) - 1)
#define SAMSUNGAH_START_BIT_PAUSE_LEN_MAX       ((uint_fast8_t)(F_INTERRUPTS * SAMSUNGAH_START_BIT_PAUSE_TIME * MAX_TOLERANCE_10 + 0.5) + 1)
#define SAMSUNGAH_PULSE_LEN_MIN                 ((uint_fast8_t)(F_INTERRUPTS * SAMSUNGAH_PULSE_TIME * MIN_TOLERANCE_30 + 0.5) - 1)
#define SAMSUNGAH_PULSE_LEN_MAX                 ((uint_fast8_t)(F_INTERRUPTS * SAMSUNGAH_PULSE_TIME * MAX_TOLERANCE_30 + 0.5) + 1)
#define SAMSUNGAH_1_PAUSE_LEN_MIN               ((uint_fast8_t)(F_INTERRUPTS * SAMSUNGAH_1_PAUSE_TIME * MIN_TOLERANCE_30 + 0.5) - 1)
#define SAMSUNGAH_1_PAUSE_LEN_MAX               ((uint_fast8_t)(F_INTERRUPTS * SAMSUNGAH_1_PAUSE_TIME * MAX_TOLERANCE_30 + 0.5) + 1)
#define SAMSUNGAH_0_PAUSE_LEN_MIN               ((uint_fast8_t)(F_INTERRUPTS * SAMSUNGAH_0_PAUSE_TIME * MIN_TOLERANCE_30 + 0.5) - 1)
#define SAMSUNGAH_0_PAUSE_LEN_MAX               ((uint_fast8_t)(F_INTERRUPTS * SAMSUNGAH_0_PAUSE_TIME * MAX_TOLERANCE_30 + 0.5) + 1)

#define MATSUSHITA_START_BIT_PULSE_LEN_MIN      ((uint_fast8_t)(F_INTERRUPTS * MATSUSHITA_START_BIT_PULSE_TIME * MIN_TOLERANCE_20 + 0.5) - 1)
#define MATSUSHITA_START_BIT_PULSE_LEN_MAX      ((uint_fast8_t)(F_INTERRUPTS * MATSUSHITA_START_BIT_PULSE_TIME * MAX_TOLERANCE_20 + 0.5) + 1)
#define MATSUSHITA_START_BIT_PAUSE_LEN_MIN      ((uint_fast8_t)(F_INTERRUPTS * MATSUSHITA_START_BIT_PAUSE_TIME * MIN_TOLERANCE_20 + 0.5) - 1)
#define MATSUSHITA_START_BIT_PAUSE_LEN_MAX      ((uint_fast8_t)(F_INTERRUPTS * MATSUSHITA_START_BIT_PAUSE_TIME * MAX_TOLERANCE_20 + 0.5) + 1)
#define MATSUSHITA_PULSE_LEN_MIN                ((uint_fast8_t)(F_INTERRUPTS * MATSUSHITA_PULSE_TIME * MIN_TOLERANCE_40 + 0.5) - 1)
#define MATSUSHITA_PULSE_LEN_MAX                ((uint_fast8_t)(F_INTERRUPTS * MATSUSHITA_PULSE_TIME * MAX_TOLERANCE_40 + 0.5) + 1)
#define MATSUSHITA_1_PAUSE_LEN_MIN              ((uint_fast8_t)(F_INTERRUPTS * MATSUSHITA_1_PAUSE_TIME * MIN_TOLERANCE_40 + 0.5) - 1)
#define MATSUSHITA_1_PAUSE_LEN_MAX              ((uint_fast8_t)(F_INTERRUPTS * MATSUSHITA_1_PAUSE_TIME * MAX_TOLERANCE_40 + 0.5) + 1)
#define MATSUSHITA_0_PAUSE_LEN_MIN              ((uint_fast8_t)(F_INTERRUPTS * MATSUSHITA_0_PAUSE_TIME * MIN_TOLERANCE_40 + 0.5) - 1)
#define MATSUSHITA_0_PAUSE_LEN_MAX              ((uint_fast8_t)(F_INTERRUPTS * MATSUSHITA_0_PAUSE_TIME * MAX_TOLERANCE_40 + 0.5) + 1)

#define KASEIKYO_START_BIT_PULSE_LEN_MIN        ((uint_fast8_t)(F_INTERRUPTS * KASEIKYO_START_BIT_PULSE_TIME * MIN_TOLERANCE_20 + 0.5) - 1)
#define KASEIKYO_START_BIT_PULSE_LEN_MAX        ((uint_fast8_t)(F_INTERRUPTS * KASEIKYO_START_BIT_PULSE_TIME * MAX_TOLERANCE_20 + 0.5) + 1)
#define KASEIKYO_START_BIT_PAUSE_LEN_MIN        ((uint_fast8_t)(F_INTERRUPTS * KASEIKYO_START_BIT_PAUSE_TIME * MIN_TOLERANCE_20 + 0.5) - 1)
#define KASEIKYO_START_BIT_PAUSE_LEN_MAX        ((uint_fast8_t)(F_INTERRUPTS * KASEIKYO_START_BIT_PAUSE_TIME * MAX_TOLERANCE_20 + 0.5) + 1)
#define KASEIKYO_PULSE_LEN_MIN                  ((uint_fast8_t)(F_INTERRUPTS * KASEIKYO_PULSE_TIME * MIN_TOLERANCE_40 + 0.5) - 1)
#define KASEIKYO_PULSE_LEN_MAX                  ((uint_fast8_t)(F_INTERRUPTS * KASEIKYO_PULSE_TIME * MAX_TOLERANCE_40 + 0.5) + 1)
#define KASEIKYO_1_PAUSE_LEN_MIN                ((uint_fast8_t)(F_INTERRUPTS * KASEIKYO_1_PAUSE_TIME * MIN_TOLERANCE_20 + 0.5) - 1)
#define KASEIKYO_1_PAUSE_LEN_MAX                ((uint_fast8_t)(F_INTERRUPTS * KASEIKYO_1_PAUSE_TIME * MAX_TOLERANCE_20 + 0.5) + 1)
#define KASEIKYO_0_PAUSE_LEN_MIN                ((uint_fast8_t)(F_INTERRUPTS * KASEIKYO_0_PAUSE_TIME * MIN_TOLERANCE_20 + 0.5) - 1)
#define KASEIKYO_0_PAUSE_LEN_MAX                ((uint_fast8_t)(F_INTERRUPTS * KASEIKYO_0_PAUSE_TIME * MAX_TOLERANCE_20 + 0.5) + 1)

#define MITSU_HEAVY_START_BIT_PULSE_LEN_MIN     ((uint_fast8_t)(F_INTERRUPTS * MITSU_HEAVY_START_BIT_PULSE_TIME * MIN_TOLERANCE_10 + 0.5) - 1)
#define MITSU_HEAVY_START_BIT_PULSE_LEN_MAX     ((uint_fast8_t)(F_INTERRUPTS * MITSU_HEAVY_START_BIT_PULSE_TIME * MAX_TOLERANCE_10 + 0.5) + 1)
#define MITSU_HEAVY_START_BIT_PAUSE_LEN_MIN     ((uint_fast8_t)(F_INTERRUPTS * MITSU_HEAVY_START_BIT_PAUSE_TIME * MIN_TOLERANCE_10 + 0.5) - 1)
#define MITSU_HEAVY_START_BIT_PAUSE_LEN_MAX     ((uint_fast8_t)(F_INTERRUPTS * MITSU_HEAVY_START_BIT_PAUSE_TIME * MAX_TOLERANCE_10 + 0.5) + 1)
#define MITSU_HEAVY_PULSE_LEN_MIN               ((uint_fast8_t)(F_INTERRUPTS * MITSU_HEAVY_PULSE_TIME * MIN_TOLERANCE_40 + 0.5) - 1)
#define MITSU_HEAVY_PULSE_LEN_MAX               ((uint_fast8_t)(F_INTERRUPTS * MITSU_HEAVY_PULSE_TIME * MAX_TOLERANCE_40 + 0.5) + 1)
#define MITSU_HEAVY_1_PAUSE_LEN_MIN             ((uint_fast8_t)(F_INTERRUPTS * MITSU_HEAVY_1_PAUSE_TIME * MIN_TOLERANCE_20 + 0.5) - 1)
#define MITSU_HEAVY_1_PAUSE_LEN_MAX             ((uint_fast8_t)(F_INTERRUPTS * MITSU_HEAVY_1_PAUSE_TIME * MAX_TOLERANCE_20 + 0.5) + 1)
#define MITSU_HEAVY_0_PAUSE_LEN_MIN             ((uint_fast8_t)(F_INTERRUPTS * MITSU_HEAVY_0_PAUSE_TIME * MIN_TOLERANCE_20 + 0.5) - 1)
#define MITSU_HEAVY_0_PAUSE_LEN_MAX             ((uint_fast8_t)(F_INTERRUPTS * MITSU_HEAVY_0_PAUSE_TIME * MAX_TOLERANCE_20 + 0.5) + 1)

#define VINCENT_START_BIT_PULSE_LEN_MIN         ((uint_fast8_t)(F_INTERRUPTS * VINCENT_START_BIT_PULSE_TIME * MIN_TOLERANCE_10 + 0.5) - 1)
#define VINCENT_START_BIT_PULSE_LEN_MAX         ((uint_fast8_t)(F_INTERRUPTS * VINCENT_START_BIT_PULSE_TIME * MAX_TOLERANCE_10 + 0.5) + 1)
#define VINCENT_START_BIT_PAUSE_LEN_MIN         ((uint_fast8_t)(F_INTERRUPTS * VINCENT_START_BIT_PAUSE_TIME * MIN_TOLERANCE_10 + 0.5) - 1)
#define VINCENT_START_BIT_PAUSE_LEN_MAX         ((uint_fast8_t)(F_INTERRUPTS * VINCENT_START_BIT_PAUSE_TIME * MAX_TOLERANCE_10 + 0.5) + 1)
#define VINCENT_PULSE_LEN_MIN                   ((uint_fast8_t)(F_INTERRUPTS * VINCENT_PULSE_TIME * MIN_TOLERANCE_40 + 0.5) - 1)
#define VINCENT_PULSE_LEN_MAX                   ((uint_fast8_t)(F_INTERRUPTS * VINCENT_PULSE_TIME * MAX_TOLERANCE_40 + 0.5) + 1)
#define VINCENT_1_PAUSE_LEN_MIN                 ((uint_fast8_t)(F_INTERRUPTS * VINCENT_1_PAUSE_TIME * MIN_TOLERANCE_20 + 0.5) - 1)
#define VINCENT_1_PAUSE_LEN_MAX                 ((uint_fast8_t)(F_INTERRUPTS * VINCENT_1_PAUSE_TIME * MAX_TOLERANCE_20 + 0.5) + 1)
#define VINCENT_0_PAUSE_LEN_MIN                 ((uint_fast8_t)(F_INTERRUPTS * VINCENT_0_PAUSE_TIME * MIN_TOLERANCE_20 + 0.5) - 1)
#define VINCENT_0_PAUSE_LEN_MAX                 ((uint_fast8_t)(F_INTERRUPTS * VINCENT_0_PAUSE_TIME * MAX_TOLERANCE_20 + 0.5) + 1)

#define PANASONIC_START_BIT_PULSE_LEN_MIN       ((uint_fast8_t)(F_INTERRUPTS * PANASONIC_START_BIT_PULSE_TIME * MIN_TOLERANCE_10 + 0.5) - 1)
#define PANASONIC_START_BIT_PULSE_LEN_MAX       ((uint_fast8_t)(F_INTERRUPTS * PANASONIC_START_BIT_PULSE_TIME * MAX_TOLERANCE_10 + 0.5) + 1)
#define PANASONIC_START_BIT_PAUSE_LEN_MIN       ((uint_fast8_t)(F_INTERRUPTS * PANASONIC_START_BIT_PAUSE_TIME * MIN_TOLERANCE_10 + 0.5) - 1)
#define PANASONIC_START_BIT_PAUSE_LEN_MAX       ((uint_fast8_t)(F_INTERRUPTS * PANASONIC_START_BIT_PAUSE_TIME * MAX_TOLERANCE_10 + 0.5) + 1)
#define PANASONIC_PULSE_LEN_MIN                 ((uint_fast8_t)(F_INTERRUPTS * PANASONIC_PULSE_TIME * MIN_TOLERANCE_40 + 0.5) - 1)
#define PANASONIC_PULSE_LEN_MAX                 ((uint_fast8_t)(F_INTERRUPTS * PANASONIC_PULSE_TIME * MAX_TOLERANCE_40 + 0.5) + 1)
#define PANASONIC_1_PAUSE_LEN_MIN               ((uint_fast8_t)(F_INTERRUPTS * PANASONIC_1_PAUSE_TIME * MIN_TOLERANCE_20 + 0.5) - 1)
#define PANASONIC_1_PAUSE_LEN_MAX               ((uint_fast8_t)(F_INTERRUPTS * PANASONIC_1_PAUSE_TIME * MAX_TOLERANCE_20 + 0.5) + 1)
#define PANASONIC_0_PAUSE_LEN_MIN               ((uint_fast8_t)(F_INTERRUPTS * PANASONIC_0_PAUSE_TIME * MIN_TOLERANCE_20 + 0.5) - 1)
#define PANASONIC_0_PAUSE_LEN_MAX               ((uint_fast8_t)(F_INTERRUPTS * PANASONIC_0_PAUSE_TIME * MAX_TOLERANCE_20 + 0.5) + 1)

#define RECS80_START_BIT_PULSE_LEN_MIN          ((uint_fast8_t)(F_INTERRUPTS * RECS80_START_BIT_PULSE_TIME * MIN_TOLERANCE_20 + 0.5) - 1)
#define RECS80_START_BIT_PULSE_LEN_MAX          ((uint_fast8_t)(F_INTERRUPTS * RECS80_START_BIT_PULSE_TIME * MAX_TOLERANCE_20 + 0.5) + 1)
#define RECS80_START_BIT_PAUSE_LEN_MIN          ((uint_fast8_t)(F_INTERRUPTS * RECS80_START_BIT_PAUSE_TIME * MIN_TOLERANCE_10 + 0.5) - 1)
#define RECS80_START_BIT_PAUSE_LEN_MAX          ((uint_fast8_t)(F_INTERRUPTS * RECS80_START_BIT_PAUSE_TIME * MAX_TOLERANCE_10 + 0.5) + 1)
#define RECS80_PULSE_LEN_MIN                    ((uint_fast8_t)(F_INTERRUPTS * RECS80_PULSE_TIME * MIN_TOLERANCE_20 + 0.5) - 1)
#define RECS80_PULSE_LEN_MAX                    ((uint_fast8_t)(F_INTERRUPTS * RECS80_PULSE_TIME * MAX_TOLERANCE_20 + 0.5) + 1)
#define RECS80_1_PAUSE_LEN_MIN                  ((uint_fast8_t)(F_INTERRUPTS * RECS80_1_PAUSE_TIME * MIN_TOLERANCE_10 + 0.5) - 1)
#define RECS80_1_PAUSE_LEN_MAX                  ((uint_fast8_t)(F_INTERRUPTS * RECS80_1_PAUSE_TIME * MAX_TOLERANCE_10 + 0.5) + 1)
#define RECS80_0_PAUSE_LEN_MIN                  ((uint_fast8_t)(F_INTERRUPTS * RECS80_0_PAUSE_TIME * MIN_TOLERANCE_10 + 0.5) - 1)
#define RECS80_0_PAUSE_LEN_MAX                  ((uint_fast8_t)(F_INTERRUPTS * RECS80_0_PAUSE_TIME * MAX_TOLERANCE_10 + 0.5) + 1)

#if IRMP_SUPPORT_BOSE_PROTOCOL == 1 // BOSE conflicts with RC5, so keep tolerance for RC5 minimal here:
#define RC5_START_BIT_LEN_MIN                   ((uint_fast8_t)(F_INTERRUPTS * RC5_BIT_TIME * MIN_TOLERANCE_05 + 0.5) - 1)
#define RC5_START_BIT_LEN_MAX                   ((uint_fast8_t)(F_INTERRUPTS * RC5_BIT_TIME * MAX_TOLERANCE_05 + 0.5) + 1)
#else
#define RC5_START_BIT_LEN_MIN                   ((uint_fast8_t)(F_INTERRUPTS * RC5_BIT_TIME * MIN_TOLERANCE_10 + 0.5) - 1)
#define RC5_START_BIT_LEN_MAX                   ((uint_fast8_t)(F_INTERRUPTS * RC5_BIT_TIME * MAX_TOLERANCE_10 + 0.5) + 1)
#endif

#define RC5_BIT_LEN_MIN                         ((uint_fast8_t)(F_INTERRUPTS * RC5_BIT_TIME * MIN_TOLERANCE_10 + 0.5) - 1)
#define RC5_BIT_LEN_MAX                         ((uint_fast8_t)(F_INTERRUPTS * RC5_BIT_TIME * MAX_TOLERANCE_10 + 0.5) + 1)

#define RCII_START_BIT_PULSE_LEN_MIN            ((uint_fast8_t)(F_INTERRUPTS * RCII_START_BIT_PULSE_TIME * MIN_TOLERANCE_05 + 0.5) - 1)
#define RCII_START_BIT_PULSE_LEN_MAX            ((uint_fast8_t)(F_INTERRUPTS * RCII_START_BIT_PULSE_TIME * MAX_TOLERANCE_05 + 0.5) + 1)
#define RCII_START_BIT_PAUSE_LEN_MIN            ((uint_fast8_t)(F_INTERRUPTS * RCII_START_BIT_PAUSE_TIME * MIN_TOLERANCE_05 + 0.5) - 1)
#define RCII_START_BIT_PAUSE_LEN_MAX            ((uint_fast8_t)(F_INTERRUPTS * RCII_START_BIT_PAUSE_TIME * MAX_TOLERANCE_05 + 0.5) + 1)
#define RCII_START_BIT2_PULSE_LEN_MIN           ((uint_fast8_t)(F_INTERRUPTS * RCII_START_BIT2_PULSE_TIME * MIN_TOLERANCE_05 + 0.5) - 1)
#define RCII_START_BIT2_PULSE_LEN_MAX           ((uint_fast8_t)(F_INTERRUPTS * RCII_START_BIT2_PULSE_TIME * MAX_TOLERANCE_05 + 0.5) + 1)

#define RCII_BIT_LEN_MIN                        ((uint_fast8_t)(F_INTERRUPTS * RCII_BIT_TIME * MIN_TOLERANCE_30 + 0.5) - 1)
#define RCII_BIT_LEN                            ((uint_fast8_t)(F_INTERRUPTS * RCII_BIT_TIME))
#define RCII_BIT_LEN_MAX                        ((uint_fast8_t)(F_INTERRUPTS * RCII_BIT_TIME * MAX_TOLERANCE_30 + 0.5) + 1)

#if IRMP_SUPPORT_BOSE_PROTOCOL == 1 // BOSE conflicts with S100, so keep tolerance for S100 minimal here:
#define S100_START_BIT_LEN_MIN                   ((uint_fast8_t)(F_INTERRUPTS * S100_BIT_TIME * MIN_TOLERANCE_05 + 0.5) - 1)
#define S100_START_BIT_LEN_MAX                   ((uint_fast8_t)(F_INTERRUPTS * S100_BIT_TIME * MAX_TOLERANCE_05 + 0.5) + 1)
#else
#define S100_START_BIT_LEN_MIN                   ((uint_fast8_t)(F_INTERRUPTS * S100_BIT_TIME * MIN_TOLERANCE_10 + 0.5) - 1)
#define S100_START_BIT_LEN_MAX                   ((uint_fast8_t)(F_INTERRUPTS * S100_BIT_TIME * MAX_TOLERANCE_10 + 0.5) + 1)
#endif

#define S100_BIT_LEN_MIN                         ((uint_fast8_t)(F_INTERRUPTS * S100_BIT_TIME * MIN_TOLERANCE_10 + 0.5) - 1)
#define S100_BIT_LEN_MAX                         ((uint_fast8_t)(F_INTERRUPTS * S100_BIT_TIME * MAX_TOLERANCE_10 + 0.5) + 1)

#define DENON_PULSE_LEN_MIN                     ((uint_fast8_t)(F_INTERRUPTS * DENON_PULSE_TIME * MIN_TOLERANCE_10 + 0.5) - 1)
#define DENON_PULSE_LEN_MAX                     ((uint_fast8_t)(F_INTERRUPTS * DENON_PULSE_TIME * MAX_TOLERANCE_20 + 0.5) + 1)
#define DENON_1_PAUSE_LEN_MIN                   ((uint_fast8_t)(F_INTERRUPTS * DENON_1_PAUSE_TIME * MIN_TOLERANCE_10 + 0.5) - 1)
#define DENON_1_PAUSE_LEN_MAX                   ((uint_fast8_t)(F_INTERRUPTS * DENON_1_PAUSE_TIME * MAX_TOLERANCE_10 + 0.5) + 1)
// RUWIDO (see t-home-mediareceiver-15kHz.txt) conflicts here with DENON
#define DENON_0_PAUSE_LEN_MIN                   ((uint_fast8_t)(F_INTERRUPTS * DENON_0_PAUSE_TIME * MIN_TOLERANCE_10 + 0.5) - 1)
#define DENON_0_PAUSE_LEN_MAX                   ((uint_fast8_t)(F_INTERRUPTS * DENON_0_PAUSE_TIME * MAX_TOLERANCE_10 + 0.5) + 1)
#define DENON_AUTO_REPETITION_PAUSE_LEN         ((uint_fast16_t)(F_INTERRUPTS * DENON_AUTO_REPETITION_PAUSE_TIME * MAX_TOLERANCE_10 + 0.5) + 1)

#define THOMSON_PULSE_LEN_MIN                   ((uint_fast8_t)(F_INTERRUPTS * THOMSON_PULSE_TIME * MIN_TOLERANCE_10 + 0.5) - 1)
#define THOMSON_PULSE_LEN_MAX                   ((uint_fast8_t)(F_INTERRUPTS * THOMSON_PULSE_TIME * MAX_TOLERANCE_10 + 0.5) + 1)
#define THOMSON_1_PAUSE_LEN_MIN                 ((uint_fast8_t)(F_INTERRUPTS * THOMSON_1_PAUSE_TIME * MIN_TOLERANCE_10 + 0.5) - 1)
#define THOMSON_1_PAUSE_LEN_MAX                 ((uint_fast8_t)(F_INTERRUPTS * THOMSON_1_PAUSE_TIME * MAX_TOLERANCE_10 + 0.5) + 1)
#define THOMSON_0_PAUSE_LEN_MIN                 ((uint_fast8_t)(F_INTERRUPTS * THOMSON_0_PAUSE_TIME * MIN_TOLERANCE_10 + 0.5) - 1)
#define THOMSON_0_PAUSE_LEN_MAX                 ((uint_fast8_t)(F_INTERRUPTS * THOMSON_0_PAUSE_TIME * MAX_TOLERANCE_10 + 0.5) + 1)

#define RC6_START_BIT_PULSE_LEN_MIN             ((uint_fast8_t)(F_INTERRUPTS * RC6_START_BIT_PULSE_TIME * MIN_TOLERANCE_10 + 0.5) - 1)
#define RC6_START_BIT_PULSE_LEN_MAX             ((uint_fast8_t)(F_INTERRUPTS * RC6_START_BIT_PULSE_TIME * MAX_TOLERANCE_10 + 0.5) + 1)
#define RC6_START_BIT_PAUSE_LEN_MIN             ((uint_fast8_t)(F_INTERRUPTS * RC6_START_BIT_PAUSE_TIME * MIN_TOLERANCE_10 + 0.5) - 1)
#define RC6_START_BIT_PAUSE_LEN_MAX             ((uint_fast8_t)(F_INTERRUPTS * RC6_START_BIT_PAUSE_TIME * MAX_TOLERANCE_10 + 0.5) + 1)
#define RC6_TOGGLE_BIT_LEN_MIN                  ((uint_fast8_t)(F_INTERRUPTS * RC6_TOGGLE_BIT_TIME * MIN_TOLERANCE_10 + 0.5) - 1)
#define RC6_TOGGLE_BIT_LEN_MAX                  ((uint_fast8_t)(F_INTERRUPTS * RC6_TOGGLE_BIT_TIME * MAX_TOLERANCE_10 + 0.5) + 1)
#define RC6_BIT_PULSE_LEN_MIN                   ((uint_fast8_t)(F_INTERRUPTS * RC6_BIT_TIME * MIN_TOLERANCE_10 + 0.5) - 1)
#define RC6_BIT_PULSE_LEN_MAX                   ((uint_fast8_t)(F_INTERRUPTS * RC6_BIT_TIME * MAX_TOLERANCE_60 + 0.5) + 1)       // pulses: 300 - 800
#define RC6_BIT_PAUSE_LEN_MIN                   ((uint_fast8_t)(F_INTERRUPTS * RC6_BIT_TIME * MIN_TOLERANCE_10 + 0.5) - 1)
#define RC6_BIT_PAUSE_LEN_MAX                   ((uint_fast8_t)(F_INTERRUPTS * RC6_BIT_TIME * MAX_TOLERANCE_20 + 0.5) + 1)       // pauses: 300 - 600

#define RECS80EXT_START_BIT_PULSE_LEN_MIN       ((uint_fast8_t)(F_INTERRUPTS * RECS80EXT_START_BIT_PULSE_TIME * MIN_TOLERANCE_20 + 0.5) - 1)
#define RECS80EXT_START_BIT_PULSE_LEN_MAX       ((uint_fast8_t)(F_INTERRUPTS * RECS80EXT_START_BIT_PULSE_TIME * MAX_TOLERANCE_20 + 0.5) + 1)
#define RECS80EXT_START_BIT_PAUSE_LEN_MIN       ((uint_fast8_t)(F_INTERRUPTS * RECS80EXT_START_BIT_PAUSE_TIME * MIN_TOLERANCE_10 + 0.5) - 1)
#define RECS80EXT_START_BIT_PAUSE_LEN_MAX       ((uint_fast8_t)(F_INTERRUPTS * RECS80EXT_START_BIT_PAUSE_TIME * MAX_TOLERANCE_10 + 0.5) + 1)
#define RECS80EXT_PULSE_LEN_MIN                 ((uint_fast8_t)(F_INTERRUPTS * RECS80EXT_PULSE_TIME * MIN_TOLERANCE_20 + 0.5) - 1)
#define RECS80EXT_PULSE_LEN_MAX                 ((uint_fast8_t)(F_INTERRUPTS * RECS80EXT_PULSE_TIME * MAX_TOLERANCE_20 + 0.5) + 1)
#define RECS80EXT_1_PAUSE_LEN_MIN               ((uint_fast8_t)(F_INTERRUPTS * RECS80EXT_1_PAUSE_TIME * MIN_TOLERANCE_10 + 0.5) - 1)
#define RECS80EXT_1_PAUSE_LEN_MAX               ((uint_fast8_t)(F_INTERRUPTS * RECS80EXT_1_PAUSE_TIME * MAX_TOLERANCE_10 + 0.5) + 1)
#define RECS80EXT_0_PAUSE_LEN_MIN               ((uint_fast8_t)(F_INTERRUPTS * RECS80EXT_0_PAUSE_TIME * MIN_TOLERANCE_10 + 0.5) - 1)
#define RECS80EXT_0_PAUSE_LEN_MAX               ((uint_fast8_t)(F_INTERRUPTS * RECS80EXT_0_PAUSE_TIME * MAX_TOLERANCE_10 + 0.5) + 1)

#define NUBERT_START_BIT_PULSE_LEN_MIN          ((uint_fast8_t)(F_INTERRUPTS * NUBERT_START_BIT_PULSE_TIME * MIN_TOLERANCE_20 + 0.5) - 1)
#define NUBERT_START_BIT_PULSE_LEN_MAX          ((uint_fast8_t)(F_INTERRUPTS * NUBERT_START_BIT_PULSE_TIME * MAX_TOLERANCE_20 + 0.5) + 1)
#define NUBERT_START_BIT_PAUSE_LEN_MIN          ((uint_fast8_t)(F_INTERRUPTS * NUBERT_START_BIT_PAUSE_TIME * MIN_TOLERANCE_20 + 0.5) - 1)
#define NUBERT_START_BIT_PAUSE_LEN_MAX          ((uint_fast8_t)(F_INTERRUPTS * NUBERT_START_BIT_PAUSE_TIME * MAX_TOLERANCE_20 + 0.5) + 1)
#define NUBERT_1_PULSE_LEN_MIN                  ((uint_fast8_t)(F_INTERRUPTS * NUBERT_1_PULSE_TIME * MIN_TOLERANCE_20 + 0.5) - 1)
#define NUBERT_1_PULSE_LEN_MAX                  ((uint_fast8_t)(F_INTERRUPTS * NUBERT_1_PULSE_TIME * MAX_TOLERANCE_20 + 0.5) + 1)
#define NUBERT_1_PAUSE_LEN_MIN                  ((uint_fast8_t)(F_INTERRUPTS * NUBERT_1_PAUSE_TIME * MIN_TOLERANCE_20 + 0.5) - 1)
#define NUBERT_1_PAUSE_LEN_MAX                  ((uint_fast8_t)(F_INTERRUPTS * NUBERT_1_PAUSE_TIME * MAX_TOLERANCE_20 + 0.5) + 1)
#define NUBERT_0_PULSE_LEN_MIN                  ((uint_fast8_t)(F_INTERRUPTS * NUBERT_0_PULSE_TIME * MIN_TOLERANCE_20 + 0.5) - 1)
#define NUBERT_0_PULSE_LEN_MAX                  ((uint_fast8_t)(F_INTERRUPTS * NUBERT_0_PULSE_TIME * MAX_TOLERANCE_20 + 0.5) + 1)
#define NUBERT_0_PAUSE_LEN_MIN                  ((uint_fast8_t)(F_INTERRUPTS * NUBERT_0_PAUSE_TIME * MIN_TOLERANCE_20 + 0.5) - 1)
#define NUBERT_0_PAUSE_LEN_MAX                  ((uint_fast8_t)(F_INTERRUPTS * NUBERT_0_PAUSE_TIME * MAX_TOLERANCE_20 + 0.5) + 1)

#define FAN_START_BIT_PULSE_LEN_MIN             ((uint_fast8_t)(F_INTERRUPTS * FAN_START_BIT_PULSE_TIME * MIN_TOLERANCE_20 + 0.5) - 1)
#define FAN_START_BIT_PULSE_LEN_MAX             ((uint_fast8_t)(F_INTERRUPTS * FAN_START_BIT_PULSE_TIME * MAX_TOLERANCE_20 + 0.5) + 1)
#define FAN_START_BIT_PAUSE_LEN_MIN             ((uint_fast8_t)(F_INTERRUPTS * FAN_START_BIT_PAUSE_TIME * MIN_TOLERANCE_20 + 0.5) - 1)
#define FAN_START_BIT_PAUSE_LEN_MAX             ((uint_fast8_t)(F_INTERRUPTS * FAN_START_BIT_PAUSE_TIME * MAX_TOLERANCE_20 + 0.5) + 1)
#define FAN_1_PULSE_LEN_MIN                     ((uint_fast8_t)(F_INTERRUPTS * FAN_1_PULSE_TIME * MIN_TOLERANCE_20 + 0.5) - 1)
#define FAN_1_PULSE_LEN_MAX                     ((uint_fast8_t)(F_INTERRUPTS * FAN_1_PULSE_TIME * MAX_TOLERANCE_20 + 0.5) + 1)
#define FAN_1_PAUSE_LEN_MIN                     ((uint_fast8_t)(F_INTERRUPTS * FAN_1_PAUSE_TIME * MIN_TOLERANCE_20 + 0.5) - 1)
#define FAN_1_PAUSE_LEN_MAX                     ((uint_fast8_t)(F_INTERRUPTS * FAN_1_PAUSE_TIME * MAX_TOLERANCE_20 + 0.5) + 1)
#define FAN_0_PULSE_LEN_MIN                     ((uint_fast8_t)(F_INTERRUPTS * FAN_0_PULSE_TIME * MIN_TOLERANCE_20 + 0.5) - 1)
#define FAN_0_PULSE_LEN_MAX                     ((uint_fast8_t)(F_INTERRUPTS * FAN_0_PULSE_TIME * MAX_TOLERANCE_20 + 0.5) + 1)
#define FAN_0_PAUSE_LEN_MIN                     ((uint_fast8_t)(F_INTERRUPTS * FAN_0_PAUSE_TIME * MIN_TOLERANCE_20 + 0.5) - 1)
#define FAN_0_PAUSE_LEN_MAX                     ((uint_fast8_t)(F_INTERRUPTS * FAN_0_PAUSE_TIME * MAX_TOLERANCE_20 + 0.5) + 1)

#define SPEAKER_START_BIT_PULSE_LEN_MIN          ((uint_fast8_t)(F_INTERRUPTS * SPEAKER_START_BIT_PULSE_TIME * MIN_TOLERANCE_20 + 0.5) - 1)
#define SPEAKER_START_BIT_PULSE_LEN_MAX          ((uint_fast8_t)(F_INTERRUPTS * SPEAKER_START_BIT_PULSE_TIME * MAX_TOLERANCE_20 + 0.5) + 1)
#define SPEAKER_START_BIT_PAUSE_LEN_MIN          ((uint_fast8_t)(F_INTERRUPTS * SPEAKER_START_BIT_PAUSE_TIME * MIN_TOLERANCE_20 + 0.5) - 1)
#define SPEAKER_START_BIT_PAUSE_LEN_MAX          ((uint_fast8_t)(F_INTERRUPTS * SPEAKER_START_BIT_PAUSE_TIME * MAX_TOLERANCE_20 + 0.5) + 1)
#define SPEAKER_1_PULSE_LEN_MIN                  ((uint_fast8_t)(F_INTERRUPTS * SPEAKER_1_PULSE_TIME * MIN_TOLERANCE_20 + 0.5) - 1)
#define SPEAKER_1_PULSE_LEN_MAX                  ((uint_fast8_t)(F_INTERRUPTS * SPEAKER_1_PULSE_TIME * MAX_TOLERANCE_20 + 0.5) + 1)
#define SPEAKER_1_PAUSE_LEN_MIN                  ((uint_fast8_t)(F_INTERRUPTS * SPEAKER_1_PAUSE_TIME * MIN_TOLERANCE_20 + 0.5) - 1)
#define SPEAKER_1_PAUSE_LEN_MAX                  ((uint_fast8_t)(F_INTERRUPTS * SPEAKER_1_PAUSE_TIME * MAX_TOLERANCE_20 + 0.5) + 1)
#define SPEAKER_0_PULSE_LEN_MIN                  ((uint_fast8_t)(F_INTERRUPTS * SPEAKER_0_PULSE_TIME * MIN_TOLERANCE_20 + 0.5) - 1)
#define SPEAKER_0_PULSE_LEN_MAX                  ((uint_fast8_t)(F_INTERRUPTS * SPEAKER_0_PULSE_TIME * MAX_TOLERANCE_20 + 0.5) + 1)
#define SPEAKER_0_PAUSE_LEN_MIN                  ((uint_fast8_t)(F_INTERRUPTS * SPEAKER_0_PAUSE_TIME * MIN_TOLERANCE_20 + 0.5) - 1)
#define SPEAKER_0_PAUSE_LEN_MAX                  ((uint_fast8_t)(F_INTERRUPTS * SPEAKER_0_PAUSE_TIME * MAX_TOLERANCE_20 + 0.5) + 1)

#define BANG_OLUFSEN_START_BIT1_PULSE_LEN_MIN   ((uint_fast8_t)(F_INTERRUPTS * BANG_OLUFSEN_START_BIT1_PULSE_TIME * MIN_TOLERANCE_10 + 0.5) - 1)
#define BANG_OLUFSEN_START_BIT1_PULSE_LEN_MAX   ((uint_fast8_t)(F_INTERRUPTS * BANG_OLUFSEN_START_BIT1_PULSE_TIME * MAX_TOLERANCE_10 + 0.5) + 1)
#define BANG_OLUFSEN_START_BIT1_PAUSE_LEN_MIN   ((uint_fast8_t)(F_INTERRUPTS * BANG_OLUFSEN_START_BIT1_PAUSE_TIME * MIN_TOLERANCE_10 + 0.5) - 1)
#define BANG_OLUFSEN_START_BIT1_PAUSE_LEN_MAX   ((uint_fast8_t)(F_INTERRUPTS * BANG_OLUFSEN_START_BIT1_PAUSE_TIME * MAX_TOLERANCE_10 + 0.5) + 1)
#define BANG_OLUFSEN_START_BIT2_PULSE_LEN_MIN   ((uint_fast8_t)(F_INTERRUPTS * BANG_OLUFSEN_START_BIT2_PULSE_TIME * MIN_TOLERANCE_10 + 0.5) - 1)
#define BANG_OLUFSEN_START_BIT2_PULSE_LEN_MAX   ((uint_fast8_t)(F_INTERRUPTS * BANG_OLUFSEN_START_BIT2_PULSE_TIME * MAX_TOLERANCE_10 + 0.5) + 1)
#define BANG_OLUFSEN_START_BIT2_PAUSE_LEN_MIN   ((uint_fast8_t)(F_INTERRUPTS * BANG_OLUFSEN_START_BIT2_PAUSE_TIME * MIN_TOLERANCE_10 + 0.5) - 1)
#define BANG_OLUFSEN_START_BIT2_PAUSE_LEN_MAX   ((uint_fast8_t)(F_INTERRUPTS * BANG_OLUFSEN_START_BIT2_PAUSE_TIME * MAX_TOLERANCE_10 + 0.5) + 1)
#define BANG_OLUFSEN_START_BIT3_PULSE_LEN_MIN   ((uint_fast8_t)(F_INTERRUPTS * BANG_OLUFSEN_START_BIT3_PULSE_TIME * MIN_TOLERANCE_10 + 0.5) - 1)
#define BANG_OLUFSEN_START_BIT3_PULSE_LEN_MAX   ((uint_fast8_t)(F_INTERRUPTS * BANG_OLUFSEN_START_BIT3_PULSE_TIME * MAX_TOLERANCE_10 + 0.5) + 1)
#define BANG_OLUFSEN_START_BIT3_PAUSE_LEN_MIN   ((uint_fast8_t)(F_INTERRUPTS * BANG_OLUFSEN_START_BIT3_PAUSE_TIME * MIN_TOLERANCE_10 + 0.5) - 1)
#define BANG_OLUFSEN_START_BIT3_PAUSE_LEN_MAX   ((PAUSE_LEN)(F_INTERRUPTS * BANG_OLUFSEN_START_BIT3_PAUSE_TIME * MAX_TOLERANCE_05 + 0.5) + 1) // value must be below IRMP_TIMEOUT
#define BANG_OLUFSEN_START_BIT4_PULSE_LEN_MIN   ((uint_fast8_t)(F_INTERRUPTS * BANG_OLUFSEN_START_BIT4_PULSE_TIME * MIN_TOLERANCE_10 + 0.5) - 1)
#define BANG_OLUFSEN_START_BIT4_PULSE_LEN_MAX   ((uint_fast8_t)(F_INTERRUPTS * BANG_OLUFSEN_START_BIT4_PULSE_TIME * MAX_TOLERANCE_10 + 0.5) + 1)
#define BANG_OLUFSEN_START_BIT4_PAUSE_LEN_MIN   ((uint_fast8_t)(F_INTERRUPTS * BANG_OLUFSEN_START_BIT4_PAUSE_TIME * MIN_TOLERANCE_10 + 0.5) - 1)
#define BANG_OLUFSEN_START_BIT4_PAUSE_LEN_MAX   ((uint_fast8_t)(F_INTERRUPTS * BANG_OLUFSEN_START_BIT4_PAUSE_TIME * MAX_TOLERANCE_10 + 0.5) + 1)
#define BANG_OLUFSEN_PULSE_LEN_MIN              ((uint_fast8_t)(F_INTERRUPTS * BANG_OLUFSEN_PULSE_TIME * MIN_TOLERANCE_10 + 0.5) - 1)
#define BANG_OLUFSEN_PULSE_LEN_MAX              ((uint_fast8_t)(F_INTERRUPTS * BANG_OLUFSEN_PULSE_TIME * MAX_TOLERANCE_10 + 0.5) + 1)
#define BANG_OLUFSEN_1_PAUSE_LEN_MIN            ((uint_fast8_t)(F_INTERRUPTS * BANG_OLUFSEN_1_PAUSE_TIME * MIN_TOLERANCE_10 + 0.5) - 1)
#define BANG_OLUFSEN_1_PAUSE_LEN_MAX            ((uint_fast8_t)(F_INTERRUPTS * BANG_OLUFSEN_1_PAUSE_TIME * MAX_TOLERANCE_10 + 0.5) + 1)
#define BANG_OLUFSEN_0_PAUSE_LEN_MIN            ((uint_fast8_t)(F_INTERRUPTS * BANG_OLUFSEN_0_PAUSE_TIME * MIN_TOLERANCE_10 + 0.5) - 1)
#define BANG_OLUFSEN_0_PAUSE_LEN_MAX            ((uint_fast8_t)(F_INTERRUPTS * BANG_OLUFSEN_0_PAUSE_TIME * MAX_TOLERANCE_10 + 0.5) + 1)
#define BANG_OLUFSEN_R_PAUSE_LEN_MIN            ((uint_fast8_t)(F_INTERRUPTS * BANG_OLUFSEN_R_PAUSE_TIME * MIN_TOLERANCE_10 + 0.5) - 1)
#define BANG_OLUFSEN_R_PAUSE_LEN_MAX            ((uint_fast8_t)(F_INTERRUPTS * BANG_OLUFSEN_R_PAUSE_TIME * MAX_TOLERANCE_10 + 0.5) + 1)
#define BANG_OLUFSEN_TRAILER_BIT_PAUSE_LEN_MIN  ((uint_fast8_t)(F_INTERRUPTS * BANG_OLUFSEN_TRAILER_BIT_PAUSE_TIME * MIN_TOLERANCE_10 + 0.5) - 1)
#define BANG_OLUFSEN_TRAILER_BIT_PAUSE_LEN_MAX  ((uint_fast8_t)(F_INTERRUPTS * BANG_OLUFSEN_TRAILER_BIT_PAUSE_TIME * MAX_TOLERANCE_10 + 0.5) + 1)

#define IR60_TIMEOUT_LEN                        ((uint_fast8_t)(F_INTERRUPTS * IR60_TIMEOUT_TIME * 0.5))
#define GRUNDIG_NOKIA_IR60_START_BIT_LEN_MIN    ((uint_fast8_t)(F_INTERRUPTS * GRUNDIG_NOKIA_IR60_BIT_TIME * MIN_TOLERANCE_10 + 0.5) - 1)
#define GRUNDIG_NOKIA_IR60_START_BIT_LEN_MAX    ((uint_fast8_t)(F_INTERRUPTS * GRUNDIG_NOKIA_IR60_BIT_TIME * MAX_TOLERANCE_10 + 0.5) + 1)
#define GRUNDIG_NOKIA_IR60_BIT_LEN_MIN          ((uint_fast8_t)(F_INTERRUPTS * GRUNDIG_NOKIA_IR60_BIT_TIME * MIN_TOLERANCE_10 + 0.5) - 1)
#define GRUNDIG_NOKIA_IR60_BIT_LEN_MAX          ((uint_fast8_t)(F_INTERRUPTS * GRUNDIG_NOKIA_IR60_BIT_TIME * MAX_TOLERANCE_10 + 0.5) + 1)
#define GRUNDIG_NOKIA_IR60_PRE_PAUSE_LEN_MIN    ((uint_fast8_t)(F_INTERRUPTS * GRUNDIG_NOKIA_IR60_PRE_PAUSE_TIME * MIN_TOLERANCE_20 + 0.5) + 1)
#define GRUNDIG_NOKIA_IR60_PRE_PAUSE_LEN_MAX    ((uint_fast8_t)(F_INTERRUPTS * GRUNDIG_NOKIA_IR60_PRE_PAUSE_TIME * MAX_TOLERANCE_20 + 0.5) + 1)

#define SIEMENS_OR_RUWIDO_START_BIT_PULSE_LEN_MIN       ((uint_fast8_t)(F_INTERRUPTS * SIEMENS_OR_RUWIDO_START_BIT_PULSE_TIME * MIN_TOLERANCE_10 + 0.5) - 1)
#define SIEMENS_OR_RUWIDO_START_BIT_PULSE_LEN_MAX       ((uint_fast8_t)(F_INTERRUPTS * SIEMENS_OR_RUWIDO_START_BIT_PULSE_TIME * MAX_TOLERANCE_10 + 0.5) + 1)
#define SIEMENS_OR_RUWIDO_START_BIT_PAUSE_LEN_MIN       ((uint_fast8_t)(F_INTERRUPTS * SIEMENS_OR_RUWIDO_START_BIT_PAUSE_TIME * MIN_TOLERANCE_10 + 0.5) - 1)
#define SIEMENS_OR_RUWIDO_START_BIT_PAUSE_LEN_MAX       ((uint_fast8_t)(F_INTERRUPTS * SIEMENS_OR_RUWIDO_START_BIT_PAUSE_TIME * MAX_TOLERANCE_10 + 0.5) + 1)
#define SIEMENS_OR_RUWIDO_BIT_PULSE_LEN_MIN             ((uint_fast8_t)(F_INTERRUPTS * SIEMENS_OR_RUWIDO_BIT_PULSE_TIME * MIN_TOLERANCE_10 + 0.5) - 1)
#define SIEMENS_OR_RUWIDO_BIT_PULSE_LEN_MAX             ((uint_fast8_t)(F_INTERRUPTS * SIEMENS_OR_RUWIDO_BIT_PULSE_TIME * MAX_TOLERANCE_10 + 0.5) + 1)
#define SIEMENS_OR_RUWIDO_BIT_PAUSE_LEN_MIN             ((uint_fast8_t)(F_INTERRUPTS * SIEMENS_OR_RUWIDO_BIT_PAUSE_TIME * MIN_TOLERANCE_10 + 0.5) - 1)
#define SIEMENS_OR_RUWIDO_BIT_PAUSE_LEN_MAX             ((uint_fast8_t)(F_INTERRUPTS * SIEMENS_OR_RUWIDO_BIT_PAUSE_TIME * MAX_TOLERANCE_10 + 0.5) + 1)

#define FDC_START_BIT_PULSE_LEN_MIN             ((uint_fast8_t)(F_INTERRUPTS * FDC_START_BIT_PULSE_TIME * MIN_TOLERANCE_05 + 0.5) - 1)   // 5%: avoid conflict with NETBOX
#define FDC_START_BIT_PULSE_LEN_MAX             ((uint_fast8_t)(F_INTERRUPTS * FDC_START_BIT_PULSE_TIME * MAX_TOLERANCE_05 + 0.5))
#define FDC_START_BIT_PAUSE_LEN_MIN             ((uint_fast8_t)(F_INTERRUPTS * FDC_START_BIT_PAUSE_TIME * MIN_TOLERANCE_05 + 0.5) - 1)
#define FDC_START_BIT_PAUSE_LEN_MAX             ((uint_fast8_t)(F_INTERRUPTS * FDC_START_BIT_PAUSE_TIME * MAX_TOLERANCE_05 + 0.5))
#define FDC_PULSE_LEN_MIN                       ((uint_fast8_t)(F_INTERRUPTS * FDC_PULSE_TIME * MIN_TOLERANCE_40 + 0.5) - 1)
#define FDC_PULSE_LEN_MAX                       ((uint_fast8_t)(F_INTERRUPTS * FDC_PULSE_TIME * MAX_TOLERANCE_50 + 0.5) + 1)
#define FDC_1_PAUSE_LEN_MIN                     ((uint_fast8_t)(F_INTERRUPTS * FDC_1_PAUSE_TIME * MIN_TOLERANCE_20 + 0.5) - 1)
#define FDC_1_PAUSE_LEN_MAX                     ((uint_fast8_t)(F_INTERRUPTS * FDC_1_PAUSE_TIME * MAX_TOLERANCE_20 + 0.5) + 1)
#if 0
#define FDC_0_PAUSE_LEN_MIN                     ((uint_fast8_t)(F_INTERRUPTS * FDC_0_PAUSE_TIME * MIN_TOLERANCE_40 + 0.5) - 1)   // could be negative: 255
#else
#define FDC_0_PAUSE_LEN_MIN                     (1)                                                                         // simply use 1
#endif
#define FDC_0_PAUSE_LEN_MAX                     ((uint_fast8_t)(F_INTERRUPTS * FDC_0_PAUSE_TIME * MAX_TOLERANCE_10 + 0.5) + 1)

#define RCCAR_START_BIT_PULSE_LEN_MIN           ((uint_fast8_t)(F_INTERRUPTS * RCCAR_START_BIT_PULSE_TIME * MIN_TOLERANCE_10 + 0.5) - 1)
#define RCCAR_START_BIT_PULSE_LEN_MAX           ((uint_fast8_t)(F_INTERRUPTS * RCCAR_START_BIT_PULSE_TIME * MAX_TOLERANCE_10 + 0.5) + 1)
#define RCCAR_START_BIT_PAUSE_LEN_MIN           ((uint_fast8_t)(F_INTERRUPTS * RCCAR_START_BIT_PAUSE_TIME * MIN_TOLERANCE_10 + 0.5) - 1)
#define RCCAR_START_BIT_PAUSE_LEN_MAX           ((uint_fast8_t)(F_INTERRUPTS * RCCAR_START_BIT_PAUSE_TIME * MAX_TOLERANCE_10 + 0.5) + 1)
#define RCCAR_PULSE_LEN_MIN                     ((uint_fast8_t)(F_INTERRUPTS * RCCAR_PULSE_TIME * MIN_TOLERANCE_20 + 0.5) - 1)
#define RCCAR_PULSE_LEN_MAX                     ((uint_fast8_t)(F_INTERRUPTS * RCCAR_PULSE_TIME * MAX_TOLERANCE_20 + 0.5) + 1)
#define RCCAR_1_PAUSE_LEN_MIN                   ((uint_fast8_t)(F_INTERRUPTS * RCCAR_1_PAUSE_TIME * MIN_TOLERANCE_30 + 0.5) - 1)
#define RCCAR_1_PAUSE_LEN_MAX                   ((uint_fast8_t)(F_INTERRUPTS * RCCAR_1_PAUSE_TIME * MAX_TOLERANCE_30 + 0.5) + 1)
#define RCCAR_0_PAUSE_LEN_MIN                   ((uint_fast8_t)(F_INTERRUPTS * RCCAR_0_PAUSE_TIME * MIN_TOLERANCE_30 + 0.5) - 1)
#define RCCAR_0_PAUSE_LEN_MAX                   ((uint_fast8_t)(F_INTERRUPTS * RCCAR_0_PAUSE_TIME * MAX_TOLERANCE_30 + 0.5) + 1)

#define JVC_START_BIT_PULSE_LEN_MIN             ((uint_fast8_t)(F_INTERRUPTS * JVC_START_BIT_PULSE_TIME * MIN_TOLERANCE_40 + 0.5) - 1)
#define JVC_START_BIT_PULSE_LEN_MAX             ((uint_fast8_t)(F_INTERRUPTS * JVC_START_BIT_PULSE_TIME * MAX_TOLERANCE_40 + 0.5) + 1)
#define JVC_REPEAT_START_BIT_PAUSE_LEN_MIN      ((uint_fast8_t)(F_INTERRUPTS * (JVC_FRAME_REPEAT_PAUSE_TIME - IRMP_TIMEOUT_TIME) * MIN_TOLERANCE_40 + 0.5) - 1)  // HACK!
#define JVC_REPEAT_START_BIT_PAUSE_LEN_MAX      ((uint_fast8_t)(F_INTERRUPTS * (JVC_FRAME_REPEAT_PAUSE_TIME - IRMP_TIMEOUT_TIME) * MAX_TOLERANCE_70 + 0.5) - 1)  // HACK!
#define JVC_PULSE_LEN_MIN                       ((uint_fast8_t)(F_INTERRUPTS * JVC_PULSE_TIME * MIN_TOLERANCE_40 + 0.5) - 1)
#define JVC_PULSE_LEN_MAX                       ((uint_fast8_t)(F_INTERRUPTS * JVC_PULSE_TIME * MAX_TOLERANCE_40 + 0.5) + 1)
#define JVC_1_PAUSE_LEN_MIN                     ((uint_fast8_t)(F_INTERRUPTS * JVC_1_PAUSE_TIME * MIN_TOLERANCE_40 + 0.5) - 1)
#define JVC_1_PAUSE_LEN_MAX                     ((uint_fast8_t)(F_INTERRUPTS * JVC_1_PAUSE_TIME * MAX_TOLERANCE_40 + 0.5) + 1)
#define JVC_0_PAUSE_LEN_MIN                     ((uint_fast8_t)(F_INTERRUPTS * JVC_0_PAUSE_TIME * MIN_TOLERANCE_40 + 0.5) - 1)
#define JVC_0_PAUSE_LEN_MAX                     ((uint_fast8_t)(F_INTERRUPTS * JVC_0_PAUSE_TIME * MAX_TOLERANCE_40 + 0.5) + 1)
// autodetect JVC repetition frame within 50 msec:
#define JVC_FRAME_REPEAT_PAUSE_LEN_MAX          (uint_fast16_t)(F_INTERRUPTS * JVC_FRAME_REPEAT_PAUSE_TIME * MAX_TOLERANCE_20 + 0.5)

#define NIKON_START_BIT_PULSE_LEN_MIN           ((uint_fast8_t)(F_INTERRUPTS * NIKON_START_BIT_PULSE_TIME * MIN_TOLERANCE_20 + 0.5) - 1)
#define NIKON_START_BIT_PULSE_LEN_MAX           ((uint_fast8_t)(F_INTERRUPTS * NIKON_START_BIT_PULSE_TIME * MAX_TOLERANCE_20 + 0.5) + 1)
#define NIKON_START_BIT_PAUSE_LEN_MIN           ((uint_fast16_t)(F_INTERRUPTS * NIKON_START_BIT_PAUSE_TIME * MIN_TOLERANCE_20 + 0.5) - 1)
#define NIKON_START_BIT_PAUSE_LEN_MAX           ((uint_fast16_t)(F_INTERRUPTS * NIKON_START_BIT_PAUSE_TIME * MAX_TOLERANCE_20 + 0.5) + 1)
#define NIKON_REPEAT_START_BIT_PAUSE_LEN_MIN    ((uint_fast8_t)(F_INTERRUPTS * NIKON_REPEAT_START_BIT_PAUSE_TIME * MIN_TOLERANCE_20 + 0.5) - 1)
#define NIKON_REPEAT_START_BIT_PAUSE_LEN_MAX    ((uint_fast8_t)(F_INTERRUPTS * NIKON_REPEAT_START_BIT_PAUSE_TIME * MAX_TOLERANCE_20 + 0.5) + 1)
#define NIKON_PULSE_LEN_MIN                     ((uint_fast8_t)(F_INTERRUPTS * NIKON_PULSE_TIME * MIN_TOLERANCE_20 + 0.5) - 1)
#define NIKON_PULSE_LEN_MAX                     ((uint_fast8_t)(F_INTERRUPTS * NIKON_PULSE_TIME * MAX_TOLERANCE_20 + 0.5) + 1)
#define NIKON_1_PAUSE_LEN_MIN                   ((uint_fast8_t)(F_INTERRUPTS * NIKON_1_PAUSE_TIME * MIN_TOLERANCE_20 + 0.5) - 1)
#define NIKON_1_PAUSE_LEN_MAX                   ((uint_fast8_t)(F_INTERRUPTS * NIKON_1_PAUSE_TIME * MAX_TOLERANCE_20 + 0.5) + 1)
#define NIKON_0_PAUSE_LEN_MIN                   ((uint_fast8_t)(F_INTERRUPTS * NIKON_0_PAUSE_TIME * MIN_TOLERANCE_20 + 0.5) - 1)
#define NIKON_0_PAUSE_LEN_MAX                   ((uint_fast8_t)(F_INTERRUPTS * NIKON_0_PAUSE_TIME * MAX_TOLERANCE_20 + 0.5) + 1)
#define NIKON_FRAME_REPEAT_PAUSE_LEN_MAX        (uint_fast16_t)(F_INTERRUPTS * NIKON_FRAME_REPEAT_PAUSE_TIME * MAX_TOLERANCE_20 + 0.5)

#define KATHREIN_START_BIT_PULSE_LEN_MIN        ((uint_fast8_t)(F_INTERRUPTS * KATHREIN_START_BIT_PULSE_TIME * MIN_TOLERANCE_10 + 0.5) - 1)
#define KATHREIN_START_BIT_PULSE_LEN_MAX        ((uint_fast8_t)(F_INTERRUPTS * KATHREIN_START_BIT_PULSE_TIME * MAX_TOLERANCE_10 + 0.5) + 1)
#define KATHREIN_START_BIT_PAUSE_LEN_MIN        ((uint_fast8_t)(F_INTERRUPTS * KATHREIN_START_BIT_PAUSE_TIME * MIN_TOLERANCE_10 + 0.5) - 1)
#define KATHREIN_START_BIT_PAUSE_LEN_MAX        ((uint_fast8_t)(F_INTERRUPTS * KATHREIN_START_BIT_PAUSE_TIME * MAX_TOLERANCE_10 + 0.5) + 1)
#define KATHREIN_1_PULSE_LEN_MIN                ((uint_fast8_t)(F_INTERRUPTS * KATHREIN_1_PULSE_TIME * MIN_TOLERANCE_10 + 0.5) - 1)
#define KATHREIN_1_PULSE_LEN_MAX                ((uint_fast8_t)(F_INTERRUPTS * KATHREIN_1_PULSE_TIME * MAX_TOLERANCE_10 + 0.5) + 1)
#define KATHREIN_1_PAUSE_LEN_MIN                ((uint_fast8_t)(F_INTERRUPTS * KATHREIN_1_PAUSE_TIME * MIN_TOLERANCE_10 + 0.5) - 1)
#define KATHREIN_1_PAUSE_LEN_MAX                ((uint_fast8_t)(F_INTERRUPTS * KATHREIN_1_PAUSE_TIME * MAX_TOLERANCE_10 + 0.5) + 1)
#define KATHREIN_0_PULSE_LEN_MIN                ((uint_fast8_t)(F_INTERRUPTS * KATHREIN_0_PULSE_TIME * MIN_TOLERANCE_10 + 0.5) - 1)
#define KATHREIN_0_PULSE_LEN_MAX                ((uint_fast8_t)(F_INTERRUPTS * KATHREIN_0_PULSE_TIME * MAX_TOLERANCE_10 + 0.5) + 1)
#define KATHREIN_0_PAUSE_LEN_MIN                ((uint_fast8_t)(F_INTERRUPTS * KATHREIN_0_PAUSE_TIME * MIN_TOLERANCE_10 + 0.5) - 1)
#define KATHREIN_0_PAUSE_LEN_MAX                ((uint_fast8_t)(F_INTERRUPTS * KATHREIN_0_PAUSE_TIME * MAX_TOLERANCE_10 + 0.5) + 1)
#define KATHREIN_SYNC_BIT_PAUSE_LEN_MIN         ((uint_fast8_t)(F_INTERRUPTS * KATHREIN_SYNC_BIT_PAUSE_LEN_TIME * MIN_TOLERANCE_10 + 0.5) - 1)
#define KATHREIN_SYNC_BIT_PAUSE_LEN_MAX         ((uint_fast8_t)(F_INTERRUPTS * KATHREIN_SYNC_BIT_PAUSE_LEN_TIME * MAX_TOLERANCE_10 + 0.5) + 1)

#define NETBOX_START_BIT_PULSE_LEN_MIN          ((uint_fast8_t)(F_INTERRUPTS * NETBOX_START_BIT_PULSE_TIME * MIN_TOLERANCE_10 + 0.5) - 1)
#define NETBOX_START_BIT_PULSE_LEN_MAX          ((uint_fast8_t)(F_INTERRUPTS * NETBOX_START_BIT_PULSE_TIME * MAX_TOLERANCE_10 + 0.5) + 1)
#define NETBOX_START_BIT_PAUSE_LEN_MIN          ((uint_fast8_t)(F_INTERRUPTS * NETBOX_START_BIT_PAUSE_TIME * MIN_TOLERANCE_10 + 0.5) - 1)
#define NETBOX_START_BIT_PAUSE_LEN_MAX          ((uint_fast8_t)(F_INTERRUPTS * NETBOX_START_BIT_PAUSE_TIME * MAX_TOLERANCE_10 + 0.5) + 1)
#define NETBOX_PULSE_LEN                        ((uint_fast8_t)(F_INTERRUPTS * NETBOX_PULSE_TIME))
#define NETBOX_PAUSE_LEN                        ((uint_fast8_t)(F_INTERRUPTS * NETBOX_PAUSE_TIME))
#define NETBOX_PULSE_REST_LEN                   ((uint_fast8_t)(F_INTERRUPTS * NETBOX_PULSE_TIME / 4))
#define NETBOX_PAUSE_REST_LEN                   ((uint_fast8_t)(F_INTERRUPTS * NETBOX_PAUSE_TIME / 4))

#define LEGO_START_BIT_PULSE_LEN_MIN            ((uint_fast8_t)(F_INTERRUPTS * LEGO_START_BIT_PULSE_TIME * MIN_TOLERANCE_40 + 0.5) - 1)
#define LEGO_START_BIT_PULSE_LEN_MAX            ((uint_fast8_t)(F_INTERRUPTS * LEGO_START_BIT_PULSE_TIME * MAX_TOLERANCE_40 + 0.5) + 1)
#define LEGO_START_BIT_PAUSE_LEN_MIN            ((uint_fast8_t)(F_INTERRUPTS * LEGO_START_BIT_PAUSE_TIME * MIN_TOLERANCE_40 + 0.5) - 1)
#define LEGO_START_BIT_PAUSE_LEN_MAX            ((uint_fast8_t)(F_INTERRUPTS * LEGO_START_BIT_PAUSE_TIME * MAX_TOLERANCE_40 + 0.5) + 1)
#define LEGO_PULSE_LEN_MIN                      ((uint_fast8_t)(F_INTERRUPTS * LEGO_PULSE_TIME * MIN_TOLERANCE_40 + 0.5) - 1)
#define LEGO_PULSE_LEN_MAX                      ((uint_fast8_t)(F_INTERRUPTS * LEGO_PULSE_TIME * MAX_TOLERANCE_40 + 0.5) + 1)
#define LEGO_1_PAUSE_LEN_MIN                    ((uint_fast8_t)(F_INTERRUPTS * LEGO_1_PAUSE_TIME * MIN_TOLERANCE_40 + 0.5) - 1)
#define LEGO_1_PAUSE_LEN_MAX                    ((uint_fast8_t)(F_INTERRUPTS * LEGO_1_PAUSE_TIME * MAX_TOLERANCE_40 + 0.5) + 1)
#define LEGO_0_PAUSE_LEN_MIN                    ((uint_fast8_t)(F_INTERRUPTS * LEGO_0_PAUSE_TIME * MIN_TOLERANCE_40 + 0.5) - 1)
#define LEGO_0_PAUSE_LEN_MAX                    ((uint_fast8_t)(F_INTERRUPTS * LEGO_0_PAUSE_TIME * MAX_TOLERANCE_40 + 0.5) + 1)

#define IRMP16_START_BIT_PULSE_LEN_MIN          ((uint_fast8_t)(F_INTERRUPTS * IRMP16_START_BIT_PULSE_TIME * MIN_TOLERANCE_20 + 0.5) - 1)
#define IRMP16_START_BIT_PULSE_LEN_MAX          ((uint_fast8_t)(F_INTERRUPTS * IRMP16_START_BIT_PULSE_TIME * MAX_TOLERANCE_20 + 0.5) + 1)
#define IRMP16_START_BIT_PAUSE_LEN_MIN          ((uint_fast8_t)(F_INTERRUPTS * IRMP16_START_BIT_PAUSE_TIME * MIN_TOLERANCE_20 + 0.5) - 1)
#define IRMP16_START_BIT_PAUSE_LEN_MAX          ((uint_fast8_t)(F_INTERRUPTS * IRMP16_START_BIT_PAUSE_TIME * MAX_TOLERANCE_20 + 0.5) + 1)
#define IRMP16_PULSE_LEN_MIN                    ((uint_fast8_t)(F_INTERRUPTS * IRMP16_PULSE_TIME * MIN_TOLERANCE_20 + 0.5) - 1)
#define IRMP16_PULSE_LEN_MAX                    ((uint_fast8_t)(F_INTERRUPTS * IRMP16_PULSE_TIME * MAX_TOLERANCE_20 + 0.5) + 1)
#define IRMP16_1_PAUSE_LEN_MIN                  ((uint_fast8_t)(F_INTERRUPTS * IRMP16_1_PAUSE_TIME * MIN_TOLERANCE_20 + 0.5) - 1)
#define IRMP16_1_PAUSE_LEN_MAX                  ((uint_fast8_t)(F_INTERRUPTS * IRMP16_1_PAUSE_TIME * MAX_TOLERANCE_20 + 0.5) + 1)
#define IRMP16_0_PAUSE_LEN_MIN                  ((uint_fast8_t)(F_INTERRUPTS * IRMP16_0_PAUSE_TIME * MIN_TOLERANCE_20 + 0.5) - 1)
#define IRMP16_0_PAUSE_LEN_MAX                  ((uint_fast8_t)(F_INTERRUPTS * IRMP16_0_PAUSE_TIME * MAX_TOLERANCE_20 + 0.5) + 1)

#define GREE_START_BIT_PULSE_LEN_MIN            ((uint_fast8_t)(F_INTERRUPTS * GREE_START_BIT_PULSE_TIME * MIN_TOLERANCE_20 + 0.5) - 1)
#define GREE_START_BIT_PULSE_LEN_MAX            ((uint_fast8_t)(F_INTERRUPTS * GREE_START_BIT_PULSE_TIME * MAX_TOLERANCE_20 + 0.5) + 1)
#define GREE_START_BIT_PAUSE_LEN_MIN            ((uint_fast8_t)(F_INTERRUPTS * GREE_START_BIT_PAUSE_TIME * MIN_TOLERANCE_20 + 0.5) - 1)
#define GREE_START_BIT_PAUSE_LEN_MAX            ((uint_fast8_t)(F_INTERRUPTS * GREE_START_BIT_PAUSE_TIME * MAX_TOLERANCE_20 + 0.5) + 1)
#define GREE_PULSE_LEN_MIN                      ((uint_fast8_t)(F_INTERRUPTS * GREE_PULSE_TIME * MIN_TOLERANCE_20 + 0.5) - 1)
#define GREE_PULSE_LEN_MAX                      ((uint_fast8_t)(F_INTERRUPTS * GREE_PULSE_TIME * MAX_TOLERANCE_20 + 0.5) + 1)
#define GREE_1_PAUSE_LEN_MIN                    ((uint_fast8_t)(F_INTERRUPTS * GREE_1_PAUSE_TIME * MIN_TOLERANCE_20 + 0.5) - 1)
#define GREE_1_PAUSE_LEN_MAX                    ((uint_fast8_t)(F_INTERRUPTS * GREE_1_PAUSE_TIME * MAX_TOLERANCE_20 + 0.5) + 1)
#define GREE_0_PAUSE_LEN_MIN                    ((uint_fast8_t)(F_INTERRUPTS * GREE_0_PAUSE_TIME * MIN_TOLERANCE_20 + 0.5) - 1)
#define GREE_0_PAUSE_LEN_MAX                    ((uint_fast8_t)(F_INTERRUPTS * GREE_0_PAUSE_TIME * MAX_TOLERANCE_20 + 0.5) + 1)

#define BOSE_START_BIT_PULSE_LEN_MIN             ((uint_fast8_t)(F_INTERRUPTS * BOSE_START_BIT_PULSE_TIME * MIN_TOLERANCE_30 + 0.5) - 1)
#define BOSE_START_BIT_PULSE_LEN_MAX             ((uint_fast8_t)(F_INTERRUPTS * BOSE_START_BIT_PULSE_TIME * MAX_TOLERANCE_30 + 0.5) + 1)
#define BOSE_START_BIT_PAUSE_LEN_MIN             ((uint_fast8_t)(F_INTERRUPTS * BOSE_START_BIT_PAUSE_TIME * MIN_TOLERANCE_30 + 0.5) - 1)
#define BOSE_START_BIT_PAUSE_LEN_MAX             ((uint_fast8_t)(F_INTERRUPTS * BOSE_START_BIT_PAUSE_TIME * MAX_TOLERANCE_30 + 0.5) + 1)
#define BOSE_PULSE_LEN_MIN                       ((uint_fast8_t)(F_INTERRUPTS * BOSE_PULSE_TIME * MIN_TOLERANCE_30 + 0.5) - 1)
#define BOSE_PULSE_LEN_MAX                       ((uint_fast8_t)(F_INTERRUPTS * BOSE_PULSE_TIME * MAX_TOLERANCE_30 + 0.5) + 1)
#define BOSE_1_PAUSE_LEN_MIN                     ((uint_fast8_t)(F_INTERRUPTS * BOSE_1_PAUSE_TIME * MIN_TOLERANCE_30 + 0.5) - 1)
#define BOSE_1_PAUSE_LEN_MAX                     ((uint_fast8_t)(F_INTERRUPTS * BOSE_1_PAUSE_TIME * MAX_TOLERANCE_30 + 0.5) + 1)
#define BOSE_0_PAUSE_LEN_MIN                     ((uint_fast8_t)(F_INTERRUPTS * BOSE_0_PAUSE_TIME * MIN_TOLERANCE_30 + 0.5) - 1)
#define BOSE_0_PAUSE_LEN_MAX                     ((uint_fast8_t)(F_INTERRUPTS * BOSE_0_PAUSE_TIME * MAX_TOLERANCE_30 + 0.5) + 1)
#define BOSE_FRAME_REPEAT_PAUSE_LEN_MAX          (uint_fast16_t)(F_INTERRUPTS * 100.0e-3 * MAX_TOLERANCE_20 + 0.5)

#define A1TVBOX_START_BIT_PULSE_LEN_MIN         ((uint_fast8_t)(F_INTERRUPTS * A1TVBOX_START_BIT_PULSE_TIME * MIN_TOLERANCE_10 + 0.5) - 1)
#define A1TVBOX_START_BIT_PULSE_LEN_MAX         ((uint_fast8_t)(F_INTERRUPTS * A1TVBOX_START_BIT_PULSE_TIME * MAX_TOLERANCE_10 + 0.5) + 1)
#define A1TVBOX_START_BIT_PAUSE_LEN_MIN         ((uint_fast8_t)(F_INTERRUPTS * A1TVBOX_START_BIT_PAUSE_TIME * MIN_TOLERANCE_10 + 0.5) - 1)
#define A1TVBOX_START_BIT_PAUSE_LEN_MAX         ((uint_fast8_t)(F_INTERRUPTS * A1TVBOX_START_BIT_PAUSE_TIME * MAX_TOLERANCE_10 + 0.5) + 1)
#define A1TVBOX_BIT_PULSE_LEN_MIN               ((uint_fast8_t)(F_INTERRUPTS * A1TVBOX_BIT_PULSE_TIME * MIN_TOLERANCE_30 + 0.5) - 1)
#define A1TVBOX_BIT_PULSE_LEN_MAX               ((uint_fast8_t)(F_INTERRUPTS * A1TVBOX_BIT_PULSE_TIME * MAX_TOLERANCE_30 + 0.5) + 1)
#define A1TVBOX_BIT_PAUSE_LEN_MIN               ((uint_fast8_t)(F_INTERRUPTS * A1TVBOX_BIT_PAUSE_TIME * MIN_TOLERANCE_30 + 0.5) - 1)
#define A1TVBOX_BIT_PAUSE_LEN_MAX               ((uint_fast8_t)(F_INTERRUPTS * A1TVBOX_BIT_PAUSE_TIME * MAX_TOLERANCE_30 + 0.5) + 1)

#define MERLIN_START_BIT_PULSE_LEN_MIN          ((uint_fast8_t)(F_INTERRUPTS * MERLIN_START_BIT_PULSE_TIME * MIN_TOLERANCE_10 + 0.5) - 1)
#define MERLIN_START_BIT_PULSE_LEN_MAX          ((uint_fast8_t)(F_INTERRUPTS * MERLIN_START_BIT_PULSE_TIME * MAX_TOLERANCE_10 + 0.5) + 1)
#define MERLIN_START_BIT_PAUSE_LEN_MIN          ((uint_fast8_t)(F_INTERRUPTS * MERLIN_START_BIT_PAUSE_TIME * MIN_TOLERANCE_10 + 0.5) - 1)
#define MERLIN_START_BIT_PAUSE_LEN_MAX          ((uint_fast8_t)(F_INTERRUPTS * MERLIN_START_BIT_PAUSE_TIME * MAX_TOLERANCE_10 + 0.5) + 1)
#define MERLIN_BIT_PULSE_LEN_MIN                ((uint_fast8_t)(F_INTERRUPTS * MERLIN_BIT_PULSE_TIME * MIN_TOLERANCE_30 + 0.5) - 1)
#define MERLIN_BIT_PULSE_LEN_MAX                ((uint_fast8_t)(F_INTERRUPTS * MERLIN_BIT_PULSE_TIME * MAX_TOLERANCE_30 + 0.5) + 1)
#define MERLIN_BIT_PAUSE_LEN_MIN                ((uint_fast8_t)(F_INTERRUPTS * MERLIN_BIT_PAUSE_TIME * MIN_TOLERANCE_30 + 0.5) - 1)
#define MERLIN_BIT_PAUSE_LEN_MAX                ((uint_fast8_t)(F_INTERRUPTS * MERLIN_BIT_PAUSE_TIME * MAX_TOLERANCE_30 + 0.5) + 1)

#define ORTEK_START_BIT_PULSE_LEN_MIN           ((uint_fast8_t)(F_INTERRUPTS * ORTEK_START_BIT_PULSE_TIME * MIN_TOLERANCE_10 + 0.5) - 1)
#define ORTEK_START_BIT_PULSE_LEN_MAX           ((uint_fast8_t)(F_INTERRUPTS * ORTEK_START_BIT_PULSE_TIME * MAX_TOLERANCE_10 + 0.5) + 1)
#define ORTEK_START_BIT_PAUSE_LEN_MIN           ((uint_fast8_t)(F_INTERRUPTS * ORTEK_START_BIT_PAUSE_TIME * MIN_TOLERANCE_10 + 0.5) - 1)
#define ORTEK_START_BIT_PAUSE_LEN_MAX           ((uint_fast8_t)(F_INTERRUPTS * ORTEK_START_BIT_PAUSE_TIME * MAX_TOLERANCE_10 + 0.5) + 1)
#define ORTEK_BIT_PULSE_LEN_MIN                 ((uint_fast8_t)(F_INTERRUPTS * ORTEK_BIT_TIME * MIN_TOLERANCE_10 + 0.5) - 1)
#define ORTEK_BIT_PULSE_LEN_MAX                 ((uint_fast8_t)(F_INTERRUPTS * ORTEK_BIT_TIME * MAX_TOLERANCE_10 + 0.5) + 1)
#define ORTEK_BIT_PAUSE_LEN_MIN                 ((uint_fast8_t)(F_INTERRUPTS * ORTEK_BIT_TIME * MIN_TOLERANCE_10 + 0.5) - 1)
#define ORTEK_BIT_PAUSE_LEN_MAX                 ((uint_fast8_t)(F_INTERRUPTS * ORTEK_BIT_TIME * MAX_TOLERANCE_10 + 0.5) + 1)

#define TELEFUNKEN_START_BIT_PULSE_LEN_MIN      ((uint_fast8_t)(F_INTERRUPTS * TELEFUNKEN_START_BIT_PULSE_TIME * MIN_TOLERANCE_10 + 0.5) - 1)
#define TELEFUNKEN_START_BIT_PULSE_LEN_MAX      ((uint_fast8_t)(F_INTERRUPTS * TELEFUNKEN_START_BIT_PULSE_TIME * MAX_TOLERANCE_10 + 0.5) + 1)
#define TELEFUNKEN_START_BIT_PAUSE_LEN_MIN      ((uint_fast8_t)(F_INTERRUPTS * (TELEFUNKEN_START_BIT_PAUSE_TIME) * MIN_TOLERANCE_10 + 0.5) - 1)
#define TELEFUNKEN_START_BIT_PAUSE_LEN_MAX      ((uint_fast8_t)(F_INTERRUPTS * (TELEFUNKEN_START_BIT_PAUSE_TIME) * MAX_TOLERANCE_10 + 0.5) - 1)
#define TELEFUNKEN_PULSE_LEN_MIN                ((uint_fast8_t)(F_INTERRUPTS * TELEFUNKEN_PULSE_TIME * MIN_TOLERANCE_30 + 0.5) - 1)
#define TELEFUNKEN_PULSE_LEN_MAX                ((uint_fast8_t)(F_INTERRUPTS * TELEFUNKEN_PULSE_TIME * MAX_TOLERANCE_30 + 0.5) + 1)
#define TELEFUNKEN_1_PAUSE_LEN_MIN              ((uint_fast8_t)(F_INTERRUPTS * TELEFUNKEN_1_PAUSE_TIME * MIN_TOLERANCE_30 + 0.5) - 1)
#define TELEFUNKEN_1_PAUSE_LEN_MAX              ((uint_fast8_t)(F_INTERRUPTS * TELEFUNKEN_1_PAUSE_TIME * MAX_TOLERANCE_30 + 0.5) + 1)
#define TELEFUNKEN_0_PAUSE_LEN_MIN              ((uint_fast8_t)(F_INTERRUPTS * TELEFUNKEN_0_PAUSE_TIME * MIN_TOLERANCE_30 + 0.5) - 1)
#define TELEFUNKEN_0_PAUSE_LEN_MAX              ((uint_fast8_t)(F_INTERRUPTS * TELEFUNKEN_0_PAUSE_TIME * MAX_TOLERANCE_30 + 0.5) + 1)
// autodetect TELEFUNKEN repetition frame within 50 msec:
// #define TELEFUNKEN_FRAME_REPEAT_PAUSE_LEN_MAX   (uint_fast16_t)(F_INTERRUPTS * TELEFUNKEN_FRAME_REPEAT_PAUSE_TIME * MAX_TOLERANCE_20 + 0.5)

#define ROOMBA_START_BIT_PULSE_LEN_MIN          ((uint_fast8_t)(F_INTERRUPTS * ROOMBA_START_BIT_PULSE_TIME * MIN_TOLERANCE_10 + 0.5) - 1)
#define ROOMBA_START_BIT_PULSE_LEN_MAX          ((uint_fast8_t)(F_INTERRUPTS * ROOMBA_START_BIT_PULSE_TIME * MAX_TOLERANCE_10 + 0.5) + 1)
#define ROOMBA_START_BIT_PAUSE_LEN_MIN          ((uint_fast8_t)(F_INTERRUPTS * ROOMBA_START_BIT_PAUSE_TIME * MIN_TOLERANCE_10 + 0.5) - 1)
#define ROOMBA_START_BIT_PAUSE_LEN_MAX          ((uint_fast8_t)(F_INTERRUPTS * ROOMBA_START_BIT_PAUSE_TIME * MAX_TOLERANCE_10 + 0.5) + 1)
#define ROOMBA_1_PAUSE_LEN_EXACT                ((uint_fast8_t)(F_INTERRUPTS * ROOMBA_1_PAUSE_TIME + 0.5))
#define ROOMBA_1_PULSE_LEN_MIN                  ((uint_fast8_t)(F_INTERRUPTS * ROOMBA_1_PULSE_TIME * MIN_TOLERANCE_20 + 0.5) - 1)
#define ROOMBA_1_PULSE_LEN_MAX                  ((uint_fast8_t)(F_INTERRUPTS * ROOMBA_1_PULSE_TIME * MAX_TOLERANCE_20 + 0.5) + 1)
#define ROOMBA_1_PAUSE_LEN_MIN                  ((uint_fast8_t)(F_INTERRUPTS * ROOMBA_1_PAUSE_TIME * MIN_TOLERANCE_20 + 0.5) - 1)
#define ROOMBA_1_PAUSE_LEN_MAX                  ((uint_fast8_t)(F_INTERRUPTS * ROOMBA_1_PAUSE_TIME * MAX_TOLERANCE_20 + 0.5) + 1)
#define ROOMBA_0_PAUSE_LEN                      ((uint_fast8_t)(F_INTERRUPTS * ROOMBA_0_PAUSE_TIME))
#define ROOMBA_0_PULSE_LEN_MIN                  ((uint_fast8_t)(F_INTERRUPTS * ROOMBA_0_PULSE_TIME * MIN_TOLERANCE_20 + 0.5) - 1)
#define ROOMBA_0_PULSE_LEN_MAX                  ((uint_fast8_t)(F_INTERRUPTS * ROOMBA_0_PULSE_TIME * MAX_TOLERANCE_20 + 0.5) + 1)
#define ROOMBA_0_PAUSE_LEN_MIN                  ((uint_fast8_t)(F_INTERRUPTS * ROOMBA_0_PAUSE_TIME * MIN_TOLERANCE_20 + 0.5) - 1)
#define ROOMBA_0_PAUSE_LEN_MAX                  ((uint_fast8_t)(F_INTERRUPTS * ROOMBA_0_PAUSE_TIME * MAX_TOLERANCE_20 + 0.5) + 1)

#define RCMM32_START_BIT_PULSE_LEN_MIN          ((uint_fast8_t)(F_INTERRUPTS * RCMM32_START_BIT_PULSE_TIME * MIN_TOLERANCE_05 + 0.5) - 1)
#define RCMM32_START_BIT_PULSE_LEN_MAX          ((uint_fast8_t)(F_INTERRUPTS * RCMM32_START_BIT_PULSE_TIME * MAX_TOLERANCE_05 + 0.5) + 1)
#define RCMM32_START_BIT_PAUSE_LEN_MIN          ((uint_fast8_t)(F_INTERRUPTS * RCMM32_START_BIT_PAUSE_TIME * MIN_TOLERANCE_05 + 0.5) - 1)
#define RCMM32_START_BIT_PAUSE_LEN_MAX          ((uint_fast8_t)(F_INTERRUPTS * RCMM32_START_BIT_PAUSE_TIME * MAX_TOLERANCE_05 + 0.5) + 1)
#define RCMM32_BIT_PULSE_LEN_MIN                ((uint_fast8_t)(F_INTERRUPTS * RCMM32_PULSE_TIME * MIN_TOLERANCE_05 + 0.5) - 1)
#define RCMM32_BIT_PULSE_LEN_MAX                ((uint_fast8_t)(F_INTERRUPTS * RCMM32_PULSE_TIME * MAX_TOLERANCE_05 + 0.5) + 1)
#define RCMM32_BIT_00_PAUSE_LEN_MIN             ((uint_fast8_t)(F_INTERRUPTS * RCMM32_00_PAUSE_TIME * MIN_TOLERANCE_05 + 0.5) - 1)
#define RCMM32_BIT_00_PAUSE_LEN_MAX             ((uint_fast8_t)(F_INTERRUPTS * RCMM32_00_PAUSE_TIME * MAX_TOLERANCE_05 + 0.5) + 1)
#define RCMM32_BIT_01_PAUSE_LEN_MIN             ((uint_fast8_t)(F_INTERRUPTS * RCMM32_01_PAUSE_TIME * MIN_TOLERANCE_05 + 0.5) - 1)
#define RCMM32_BIT_01_PAUSE_LEN_MAX             ((uint_fast8_t)(F_INTERRUPTS * RCMM32_01_PAUSE_TIME * MAX_TOLERANCE_05 + 0.5) + 1)
#define RCMM32_BIT_10_PAUSE_LEN_MIN             ((uint_fast8_t)(F_INTERRUPTS * RCMM32_10_PAUSE_TIME * MIN_TOLERANCE_05 + 0.5) - 1)
#define RCMM32_BIT_10_PAUSE_LEN_MAX             ((uint_fast8_t)(F_INTERRUPTS * RCMM32_10_PAUSE_TIME * MAX_TOLERANCE_05 + 0.5) + 1)
#define RCMM32_BIT_11_PAUSE_LEN_MIN             ((uint_fast8_t)(F_INTERRUPTS * RCMM32_11_PAUSE_TIME * MIN_TOLERANCE_05 + 0.5) - 1)
#define RCMM32_BIT_11_PAUSE_LEN_MAX             ((uint_fast8_t)(F_INTERRUPTS * RCMM32_11_PAUSE_TIME * MAX_TOLERANCE_05 + 0.5) + 1)

#define PENTAX_START_BIT_PULSE_LEN_MIN          ((uint_fast8_t)(F_INTERRUPTS * PENTAX_START_BIT_PULSE_TIME * MIN_TOLERANCE_10 + 0.5) - 1)
#define PENTAX_START_BIT_PULSE_LEN_MAX          ((uint_fast8_t)(F_INTERRUPTS * PENTAX_START_BIT_PULSE_TIME * MAX_TOLERANCE_10 + 0.5) + 1)
#define PENTAX_START_BIT_PAUSE_LEN_MIN          ((uint_fast8_t)(F_INTERRUPTS * PENTAX_START_BIT_PAUSE_TIME * MIN_TOLERANCE_10 + 0.5) - 1)
#define PENTAX_START_BIT_PAUSE_LEN_MAX          ((uint_fast8_t)(F_INTERRUPTS * PENTAX_START_BIT_PAUSE_TIME * MAX_TOLERANCE_10 + 0.5) + 1)
#define PENTAX_1_PAUSE_LEN_EXACT                ((uint_fast8_t)(F_INTERRUPTS * PENTAX_1_PAUSE_TIME + 0.5))
#define PENTAX_PULSE_LEN_MIN                    ((uint_fast8_t)(F_INTERRUPTS * PENTAX_PULSE_TIME * MIN_TOLERANCE_20 + 0.5) - 1)
#define PENTAX_PULSE_LEN_MAX                    ((uint_fast8_t)(F_INTERRUPTS * PENTAX_PULSE_TIME * MAX_TOLERANCE_20 + 0.5) + 1)
#define PENTAX_1_PAUSE_LEN_MIN                  ((uint_fast8_t)(F_INTERRUPTS * PENTAX_1_PAUSE_TIME * MIN_TOLERANCE_20 + 0.5) - 1)
#define PENTAX_1_PAUSE_LEN_MAX                  ((uint_fast8_t)(F_INTERRUPTS * PENTAX_1_PAUSE_TIME * MAX_TOLERANCE_20 + 0.5) + 1)
#define PENTAX_0_PAUSE_LEN                      ((uint_fast8_t)(F_INTERRUPTS * PENTAX_0_PAUSE_TIME))
#define PENTAX_PULSE_LEN_MIN                    ((uint_fast8_t)(F_INTERRUPTS * PENTAX_PULSE_TIME * MIN_TOLERANCE_20 + 0.5) - 1)
#define PENTAX_PULSE_LEN_MAX                    ((uint_fast8_t)(F_INTERRUPTS * PENTAX_PULSE_TIME * MAX_TOLERANCE_20 + 0.5) + 1)
#define PENTAX_0_PAUSE_LEN_MIN                  ((uint_fast8_t)(F_INTERRUPTS * PENTAX_0_PAUSE_TIME * MIN_TOLERANCE_20 + 0.5) - 1)
#define PENTAX_0_PAUSE_LEN_MAX                  ((uint_fast8_t)(F_INTERRUPTS * PENTAX_0_PAUSE_TIME * MAX_TOLERANCE_20 + 0.5) + 1)

#define ACP24_START_BIT_PULSE_LEN_MIN           ((uint_fast8_t)(F_INTERRUPTS * ACP24_START_BIT_PULSE_TIME * MIN_TOLERANCE_15 + 0.5) - 1)
#define ACP24_START_BIT_PULSE_LEN_MAX           ((uint_fast8_t)(F_INTERRUPTS * ACP24_START_BIT_PULSE_TIME * MAX_TOLERANCE_15 + 0.5) + 1)
#define ACP24_START_BIT_PAUSE_LEN_MIN           ((uint_fast8_t)(F_INTERRUPTS * ACP24_START_BIT_PAUSE_TIME * MIN_TOLERANCE_15 + 0.5) - 1)
#define ACP24_START_BIT_PAUSE_LEN_MAX           ((uint_fast8_t)(F_INTERRUPTS * ACP24_START_BIT_PAUSE_TIME * MAX_TOLERANCE_15 + 0.5) + 1)
#define ACP24_PULSE_LEN_MIN                     ((uint_fast8_t)(F_INTERRUPTS * ACP24_PULSE_TIME * MIN_TOLERANCE_15 + 0.5) - 1)
#define ACP24_PULSE_LEN_MAX                     ((uint_fast8_t)(F_INTERRUPTS * ACP24_PULSE_TIME * MAX_TOLERANCE_15 + 0.5) + 1)
#define ACP24_1_PAUSE_LEN_MIN                   ((uint_fast8_t)(F_INTERRUPTS * ACP24_1_PAUSE_TIME * MIN_TOLERANCE_15 + 0.5) - 1)
#define ACP24_1_PAUSE_LEN_MAX                   ((uint_fast8_t)(F_INTERRUPTS * ACP24_1_PAUSE_TIME * MAX_TOLERANCE_15 + 0.5) + 1)
#define ACP24_0_PAUSE_LEN_MIN                   ((uint_fast8_t)(F_INTERRUPTS * ACP24_0_PAUSE_TIME * MIN_TOLERANCE_15 + 0.5) - 1)
#define ACP24_0_PAUSE_LEN_MAX                   ((uint_fast8_t)(F_INTERRUPTS * ACP24_0_PAUSE_TIME * MAX_TOLERANCE_15 + 0.5) + 1)

#define METZ_START_BIT_PULSE_LEN_MIN            ((uint_fast8_t)(F_INTERRUPTS * METZ_START_BIT_PULSE_TIME * MIN_TOLERANCE_05 + 0.5) - 1)
#define METZ_START_BIT_PULSE_LEN_MAX            ((uint_fast8_t)(F_INTERRUPTS * METZ_START_BIT_PULSE_TIME * MAX_TOLERANCE_05 + 0.5) + 1)
#define METZ_START_BIT_PAUSE_LEN_MIN            ((uint_fast8_t)(F_INTERRUPTS * METZ_START_BIT_PAUSE_TIME * MIN_TOLERANCE_05 + 0.5) - 1)
#define METZ_START_BIT_PAUSE_LEN_MAX            ((uint_fast8_t)(F_INTERRUPTS * METZ_START_BIT_PAUSE_TIME * MAX_TOLERANCE_05 + 0.5) + 1)
#define METZ_PULSE_LEN_MIN                      ((uint_fast8_t)(F_INTERRUPTS * METZ_PULSE_TIME * MIN_TOLERANCE_20 + 0.5) - 1)
#define METZ_PULSE_LEN_MAX                      ((uint_fast8_t)(F_INTERRUPTS * METZ_PULSE_TIME * MAX_TOLERANCE_20 + 0.5) + 1)
#define METZ_1_PAUSE_LEN_MIN                    ((uint_fast8_t)(F_INTERRUPTS * METZ_1_PAUSE_TIME * MIN_TOLERANCE_20 + 0.5) - 1)
#define METZ_1_PAUSE_LEN_MAX                    ((uint_fast8_t)(F_INTERRUPTS * METZ_1_PAUSE_TIME * MAX_TOLERANCE_20 + 0.5) + 1)
#define METZ_0_PAUSE_LEN_MIN                    ((uint_fast8_t)(F_INTERRUPTS * METZ_0_PAUSE_TIME * MIN_TOLERANCE_20 + 0.5) - 1)
#define METZ_0_PAUSE_LEN_MAX                    ((uint_fast8_t)(F_INTERRUPTS * METZ_0_PAUSE_TIME * MAX_TOLERANCE_20 + 0.5) + 1)
#define METZ_FRAME_REPEAT_PAUSE_LEN_MAX         (uint_fast16_t)(F_INTERRUPTS * METZ_FRAME_REPEAT_PAUSE_TIME * MAX_TOLERANCE_20 + 0.5)

#define RADIO1_START_BIT_PULSE_LEN_MIN          ((uint_fast8_t)(F_INTERRUPTS * RADIO1_START_BIT_PULSE_TIME * MIN_TOLERANCE_10 + 0.5) - 1)
#define RADIO1_START_BIT_PULSE_LEN_MAX          ((uint_fast8_t)(F_INTERRUPTS * RADIO1_START_BIT_PULSE_TIME * MAX_TOLERANCE_10 + 0.5) + 1)
#define RADIO1_START_BIT_PAUSE_LEN_MIN          ((uint_fast8_t)(F_INTERRUPTS * RADIO1_START_BIT_PAUSE_TIME * MIN_TOLERANCE_10 + 0.5) - 1)
#define RADIO1_START_BIT_PAUSE_LEN_MAX          ((uint_fast8_t)(F_INTERRUPTS * RADIO1_START_BIT_PAUSE_TIME * MAX_TOLERANCE_10 + 0.5) + 1)
#define RADIO1_1_PAUSE_LEN_EXACT                ((uint_fast8_t)(F_INTERRUPTS * RADIO1_1_PAUSE_TIME + 0.5))
#define RADIO1_1_PULSE_LEN_MIN                  ((uint_fast8_t)(F_INTERRUPTS * RADIO1_1_PULSE_TIME * MIN_TOLERANCE_20 + 0.5) - 1)
#define RADIO1_1_PULSE_LEN_MAX                  ((uint_fast8_t)(F_INTERRUPTS * RADIO1_1_PULSE_TIME * MAX_TOLERANCE_20 + 0.5) + 1)
#define RADIO1_1_PAUSE_LEN_MIN                  ((uint_fast8_t)(F_INTERRUPTS * RADIO1_1_PAUSE_TIME * MIN_TOLERANCE_20 + 0.5) - 1)
#define RADIO1_1_PAUSE_LEN_MAX                  ((uint_fast8_t)(F_INTERRUPTS * RADIO1_1_PAUSE_TIME * MAX_TOLERANCE_20 + 0.5) + 1)
#define RADIO1_0_PAUSE_LEN                      ((uint_fast8_t)(F_INTERRUPTS * RADIO1_0_PAUSE_TIME))
#define RADIO1_0_PULSE_LEN_MIN                  ((uint_fast8_t)(F_INTERRUPTS * RADIO1_0_PULSE_TIME * MIN_TOLERANCE_20 + 0.5) - 1)
#define RADIO1_0_PULSE_LEN_MAX                  ((uint_fast8_t)(F_INTERRUPTS * RADIO1_0_PULSE_TIME * MAX_TOLERANCE_20 + 0.5) + 1)
#define RADIO1_0_PAUSE_LEN_MIN                  ((uint_fast8_t)(F_INTERRUPTS * RADIO1_0_PAUSE_TIME * MIN_TOLERANCE_20 + 0.5) - 1)
#define RADIO1_0_PAUSE_LEN_MAX                  ((uint_fast8_t)(F_INTERRUPTS * RADIO1_0_PAUSE_TIME * MAX_TOLERANCE_20 + 0.5) + 1)

#define AUTO_FRAME_REPETITION_LEN               (uint_fast16_t)(F_INTERRUPTS * AUTO_FRAME_REPETITION_TIME + 0.5)       // use uint_fast16_t!

#ifdef __cplusplus
}
#endif

#endif

