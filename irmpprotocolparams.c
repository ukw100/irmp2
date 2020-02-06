


#include "irmpprotocolparams.h"
#include "irmpcalculatedconstants.h"


/*---------------------------------------------------------------------------------------------------------------------------------------------------
 *  Protocol names
 *---------------------------------------------------------------------------------------------------------------------------------------------------
 */
#if defined(UNIX_OR_WINDOWS) || IRMP_PROTOCOL_NAMES == 1
static const char proto_unknown[]       PROGMEM = "UNKNOWN";
static const char proto_sircs[]         PROGMEM = "SIRCS";
static const char proto_nec[]           PROGMEM = "NEC";
static const char proto_samsung[]       PROGMEM = "SAMSUNG";
static const char proto_matsushita[]    PROGMEM = "MATSUSH";
static const char proto_kaseikyo[]      PROGMEM = "KASEIKYO";
static const char proto_recs80[]        PROGMEM = "RECS80";
static const char proto_rc5[]           PROGMEM = "RC5";
static const char proto_denon[]         PROGMEM = "DENON";
static const char proto_rc6[]           PROGMEM = "RC6";
static const char proto_samsung32[]     PROGMEM = "SAMSG32";
static const char proto_apple[]         PROGMEM = "APPLE";
static const char proto_recs80ext[]     PROGMEM = "RECS80EX";
static const char proto_nubert[]        PROGMEM = "NUBERT";
static const char proto_bang_olufsen[]  PROGMEM = "BANG OLU";
static const char proto_grundig[]       PROGMEM = "GRUNDIG";
static const char proto_nokia[]         PROGMEM = "NOKIA";
static const char proto_siemens[]       PROGMEM = "SIEMENS";
static const char proto_fdc[]           PROGMEM = "FDC";
static const char proto_rccar[]         PROGMEM = "RCCAR";
static const char proto_jvc[]           PROGMEM = "JVC";
static const char proto_rc6a[]          PROGMEM = "RC6A";
static const char proto_nikon[]         PROGMEM = "NIKON";
static const char proto_ruwido[]        PROGMEM = "RUWIDO";
static const char proto_ir60[]          PROGMEM = "IR60";
static const char proto_kathrein[]      PROGMEM = "KATHREIN";
static const char proto_netbox[]        PROGMEM = "NETBOX";
static const char proto_nec16[]         PROGMEM = "NEC16";
static const char proto_nec42[]         PROGMEM = "NEC42";
static const char proto_lego[]          PROGMEM = "LEGO";
static const char proto_thomson[]       PROGMEM = "THOMSON";
static const char proto_bose[]          PROGMEM = "BOSE";
static const char proto_a1tvbox[]       PROGMEM = "A1TVBOX";
static const char proto_ortek[]         PROGMEM = "ORTEK";
static const char proto_telefunken[]    PROGMEM = "TELEFUNKEN";
static const char proto_roomba[]        PROGMEM = "ROOMBA";
static const char proto_rcmm32[]        PROGMEM = "RCMM32";
static const char proto_rcmm24[]        PROGMEM = "RCMM24";
static const char proto_rcmm12[]        PROGMEM = "RCMM12";
static const char proto_speaker[]       PROGMEM = "SPEAKER";
static const char proto_lgair[]         PROGMEM = "LGAIR";
static const char proto_samsung48[]     PROGMEM = "SAMSG48";
static const char proto_merlin[]        PROGMEM = "MERLIN";
static const char proto_pentax[]        PROGMEM = "PENTAX";
static const char proto_fan[]           PROGMEM = "FAN";
static const char proto_s100[]          PROGMEM = "S100";
static const char proto_acp24[]         PROGMEM = "ACP24";
static const char proto_technics[]      PROGMEM = "TECHNICS";
static const char proto_panasonic[]     PROGMEM = "PANASONIC";
static const char proto_mitsu_heavy[]   PROGMEM = "MITSU_HEAVY";
static const char proto_vincent[]       PROGMEM = "VINCENT";
static const char proto_samsungah[]     PROGMEM = "SAMSUNGAH";
static const char proto_irmp16[]        PROGMEM = "IRMP16";
static const char proto_gree[]          PROGMEM = "GREE";
static const char proto_rcii[]          PROGMEM = "RCII";
static const char proto_metz[]          PROGMEM = "METZ";
static const char proto_onkyo[]         PROGMEM = "ONKYO";

static const char proto_radio1[]        PROGMEM = "RADIO1";

const char* const
irmp_protocol_names[IRMP_N_PROTOCOLS + 1] PROGMEM =
{
    proto_unknown,
    proto_sircs,
    proto_nec,
    proto_samsung,
    proto_matsushita,
    proto_kaseikyo,
    proto_recs80,
    proto_rc5,
    proto_denon,
    proto_rc6,
    proto_samsung32,
    proto_apple,
    proto_recs80ext,
    proto_nubert,
    proto_bang_olufsen,
    proto_grundig,
    proto_nokia,
    proto_siemens,
    proto_fdc,
    proto_rccar,
    proto_jvc,
    proto_rc6a,
    proto_nikon,
    proto_ruwido,
    proto_ir60,
    proto_kathrein,
    proto_netbox,
    proto_nec16,
    proto_nec42,
    proto_lego,
    proto_thomson,
    proto_bose,
    proto_a1tvbox,
    proto_ortek,
    proto_telefunken,
    proto_roomba,
    proto_rcmm32,
    proto_rcmm24,
    proto_rcmm12,
    proto_speaker,
    proto_lgair,
    proto_samsung48,
    proto_merlin,
    proto_pentax,
    proto_fan,
    proto_s100,
    proto_acp24,
    proto_technics,
    proto_panasonic,
    proto_mitsu_heavy,
    proto_vincent,
    proto_samsungah,
    proto_irmp16,
    proto_gree,
    proto_rcii,
    proto_metz,
    proto_onkyo,

    proto_radio1
};

#endif


#if IRMP_SUPPORT_SIRCS_PROTOCOL == 1

   const PROGMEM IRMP_PARAMETER sircs_param =
  {
      IRMP_SIRCS_PROTOCOL,                                                // protocol:        ir protocol
      SIRCS_1_PULSE_LEN_MIN,                                              // pulse_1_len_min: minimum length of pulse with bit value 1
      SIRCS_1_PULSE_LEN_MAX,                                              // pulse_1_len_max: maximum length of pulse with bit value 1
      SIRCS_PAUSE_LEN_MIN,                                                // pause_1_len_min: minimum length of pause with bit value 1
      SIRCS_PAUSE_LEN_MAX,                                                // pause_1_len_max: maximum length of pause with bit value 1
      SIRCS_0_PULSE_LEN_MIN,                                              // pulse_0_len_min: minimum length of pulse with bit value 0
      SIRCS_0_PULSE_LEN_MAX,                                              // pulse_0_len_max: maximum length of pulse with bit value 0
      SIRCS_PAUSE_LEN_MIN,                                                // pause_0_len_min: minimum length of pause with bit value 0
      SIRCS_PAUSE_LEN_MAX,                                                // pause_0_len_max: maximum length of pause with bit value 0
      SIRCS_ADDRESS_OFFSET,                                               // address_offset:  address offset
      SIRCS_ADDRESS_OFFSET + SIRCS_ADDRESS_LEN,                           // address_end:     end of address
      SIRCS_COMMAND_OFFSET,                                               // command_offset:  command offset
      SIRCS_COMMAND_OFFSET + SIRCS_COMMAND_LEN,                           // command_end:     end of command
      SIRCS_COMPLETE_DATA_LEN,                                            // complete_len:    complete length of frame
      SIRCS_STOP_BIT,                                                     // stop_bit:        flag: frame has stop bit
      SIRCS_LSB,                                                          // lsb_first:       flag: LSB first
      SIRCS_FLAGS                                                         // flags:           some flags
  };

#endif

#if IRMP_SUPPORT_NEC_PROTOCOL == 1

   const PROGMEM IRMP_PARAMETER nec_param =
  {
      IRMP_NEC_PROTOCOL,                                                  // protocol:        ir protocol
      NEC_PULSE_LEN_MIN,                                                  // pulse_1_len_min: minimum length of pulse with bit value 1
      NEC_PULSE_LEN_MAX,                                                  // pulse_1_len_max: maximum length of pulse with bit value 1
      NEC_1_PAUSE_LEN_MIN,                                                // pause_1_len_min: minimum length of pause with bit value 1
      NEC_1_PAUSE_LEN_MAX,                                                // pause_1_len_max: maximum length of pause with bit value 1
      NEC_PULSE_LEN_MIN,                                                  // pulse_0_len_min: minimum length of pulse with bit value 0
      NEC_PULSE_LEN_MAX,                                                  // pulse_0_len_max: maximum length of pulse with bit value 0
      NEC_0_PAUSE_LEN_MIN,                                                // pause_0_len_min: minimum length of pause with bit value 0
      NEC_0_PAUSE_LEN_MAX,                                                // pause_0_len_max: maximum length of pause with bit value 0
      NEC_ADDRESS_OFFSET,                                                 // address_offset:  address offset
      NEC_ADDRESS_OFFSET + NEC_ADDRESS_LEN,                               // address_end:     end of address
      NEC_COMMAND_OFFSET,                                                 // command_offset:  command offset
      NEC_COMMAND_OFFSET + NEC_COMMAND_LEN,                               // command_end:     end of command
      NEC_COMPLETE_DATA_LEN,                                              // complete_len:    complete length of frame
      NEC_STOP_BIT,                                                       // stop_bit:        flag: frame has stop bit
      NEC_LSB,                                                            // lsb_first:       flag: LSB first
      NEC_FLAGS                                                           // flags:           some flags
  };

   const PROGMEM IRMP_PARAMETER nec_rep_param =
  {
      IRMP_NEC_PROTOCOL,                                                  // protocol:        ir protocol
      NEC_PULSE_LEN_MIN,                                                  // pulse_1_len_min: minimum length of pulse with bit value 1
      NEC_PULSE_LEN_MAX,                                                  // pulse_1_len_max: maximum length of pulse with bit value 1
      NEC_1_PAUSE_LEN_MIN,                                                // pause_1_len_min: minimum length of pause with bit value 1
      NEC_1_PAUSE_LEN_MAX,                                                // pause_1_len_max: maximum length of pause with bit value 1
      NEC_PULSE_LEN_MIN,                                                  // pulse_0_len_min: minimum length of pulse with bit value 0
      NEC_PULSE_LEN_MAX,                                                  // pulse_0_len_max: maximum length of pulse with bit value 0
      NEC_0_PAUSE_LEN_MIN,                                                // pause_0_len_min: minimum length of pause with bit value 0
      NEC_0_PAUSE_LEN_MAX,                                                // pause_0_len_max: maximum length of pause with bit value 0
      0,                                                                  // address_offset:  address offset
      0,                                                                  // address_end:     end of address
      0,                                                                  // command_offset:  command offset
      0,                                                                  // command_end:     end of command
      0,                                                                  // complete_len:    complete length of frame
      NEC_STOP_BIT,                                                       // stop_bit:        flag: frame has stop bit
      NEC_LSB,                                                            // lsb_first:       flag: LSB first
      NEC_FLAGS                                                           // flags:           some flags
  };

#endif

#if IRMP_SUPPORT_NEC42_PROTOCOL == 1

   const PROGMEM IRMP_PARAMETER nec42_param =
  {
      IRMP_NEC42_PROTOCOL,                                                // protocol:        ir protocol
      NEC_PULSE_LEN_MIN,                                                  // pulse_1_len_min: minimum length of pulse with bit value 1
      NEC_PULSE_LEN_MAX,                                                  // pulse_1_len_max: maximum length of pulse with bit value 1
      NEC_1_PAUSE_LEN_MIN,                                                // pause_1_len_min: minimum length of pause with bit value 1
      NEC_1_PAUSE_LEN_MAX,                                                // pause_1_len_max: maximum length of pause with bit value 1
      NEC_PULSE_LEN_MIN,                                                  // pulse_0_len_min: minimum length of pulse with bit value 0
      NEC_PULSE_LEN_MAX,                                                  // pulse_0_len_max: maximum length of pulse with bit value 0
      NEC_0_PAUSE_LEN_MIN,                                                // pause_0_len_min: minimum length of pause with bit value 0
      NEC_0_PAUSE_LEN_MAX,                                                // pause_0_len_max: maximum length of pause with bit value 0
      NEC42_ADDRESS_OFFSET,                                               // address_offset:  address offset
      NEC42_ADDRESS_OFFSET + NEC42_ADDRESS_LEN,                           // address_end:     end of address
      NEC42_COMMAND_OFFSET,                                               // command_offset:  command offset
      NEC42_COMMAND_OFFSET + NEC42_COMMAND_LEN,                           // command_end:     end of command
      NEC42_COMPLETE_DATA_LEN,                                            // complete_len:    complete length of frame
      NEC_STOP_BIT,                                                       // stop_bit:        flag: frame has stop bit
      NEC_LSB,                                                            // lsb_first:       flag: LSB first
      NEC_FLAGS                                                           // flags:           some flags
  };

#endif

#if IRMP_SUPPORT_LGAIR_PROTOCOL == 1

   const PROGMEM IRMP_PARAMETER lgair_param =
  {
      IRMP_LGAIR_PROTOCOL,                                                // protocol:        ir protocol
      NEC_PULSE_LEN_MIN,                                                  // pulse_1_len_min: minimum length of pulse with bit value 1
      NEC_PULSE_LEN_MAX,                                                  // pulse_1_len_max: maximum length of pulse with bit value 1
      NEC_1_PAUSE_LEN_MIN,                                                // pause_1_len_min: minimum length of pause with bit value 1
      NEC_1_PAUSE_LEN_MAX,                                                // pause_1_len_max: maximum length of pause with bit value 1
      NEC_PULSE_LEN_MIN,                                                  // pulse_0_len_min: minimum length of pulse with bit value 0
      NEC_PULSE_LEN_MAX,                                                  // pulse_0_len_max: maximum length of pulse with bit value 0
      NEC_0_PAUSE_LEN_MIN,                                                // pause_0_len_min: minimum length of pause with bit value 0
      NEC_0_PAUSE_LEN_MAX,                                                // pause_0_len_max: maximum length of pause with bit value 0
      LGAIR_ADDRESS_OFFSET,                                               // address_offset:  address offset
      LGAIR_ADDRESS_OFFSET + LGAIR_ADDRESS_LEN,                           // address_end:     end of address
      LGAIR_COMMAND_OFFSET,                                               // command_offset:  command offset
      LGAIR_COMMAND_OFFSET + LGAIR_COMMAND_LEN,                           // command_end:     end of command
      LGAIR_COMPLETE_DATA_LEN,                                            // complete_len:    complete length of frame
      NEC_STOP_BIT,                                                       // stop_bit:        flag: frame has stop bit
      NEC_LSB,                                                            // lsb_first:       flag: LSB first
      NEC_FLAGS                                                           // flags:           some flags
  };

#endif

#if IRMP_SUPPORT_SAMSUNG_PROTOCOL == 1

   const PROGMEM IRMP_PARAMETER samsung_param =
  {
      IRMP_SAMSUNG_PROTOCOL,                                              // protocol:        ir protocol
      SAMSUNG_PULSE_LEN_MIN,                                              // pulse_1_len_min: minimum length of pulse with bit value 1
      SAMSUNG_PULSE_LEN_MAX,                                              // pulse_1_len_max: maximum length of pulse with bit value 1
      SAMSUNG_1_PAUSE_LEN_MIN,                                            // pause_1_len_min: minimum length of pause with bit value 1
      SAMSUNG_1_PAUSE_LEN_MAX,                                            // pause_1_len_max: maximum length of pause with bit value 1
      SAMSUNG_PULSE_LEN_MIN,                                              // pulse_0_len_min: minimum length of pulse with bit value 0
      SAMSUNG_PULSE_LEN_MAX,                                              // pulse_0_len_max: maximum length of pulse with bit value 0
      SAMSUNG_0_PAUSE_LEN_MIN,                                            // pause_0_len_min: minimum length of pause with bit value 0
      SAMSUNG_0_PAUSE_LEN_MAX,                                            // pause_0_len_max: maximum length of pause with bit value 0
      SAMSUNG_ADDRESS_OFFSET,                                             // address_offset:  address offset
      SAMSUNG_ADDRESS_OFFSET + SAMSUNG_ADDRESS_LEN,                       // address_end:     end of address
      SAMSUNG_COMMAND_OFFSET,                                             // command_offset:  command offset
      SAMSUNG_COMMAND_OFFSET + SAMSUNG_COMMAND_LEN,                       // command_end:     end of command
      SAMSUNG_COMPLETE_DATA_LEN,                                          // complete_len:    complete length of frame
      SAMSUNG_STOP_BIT,                                                   // stop_bit:        flag: frame has stop bit
      SAMSUNG_LSB,                                                        // lsb_first:       flag: LSB first
      SAMSUNG_FLAGS                                                       // flags:           some flags
  };

#endif

#if IRMP_SUPPORT_SAMSUNGAH_PROTOCOL == 1

   const PROGMEM IRMP_PARAMETER samsungah_param =
  {
      IRMP_SAMSUNGAH_PROTOCOL,                                            // protocol:        ir protocol
      SAMSUNGAH_PULSE_LEN_MIN,                                            // pulse_1_len_min: minimum length of pulse with bit value 1
      SAMSUNGAH_PULSE_LEN_MAX,                                            // pulse_1_len_max: maximum length of pulse with bit value 1
      SAMSUNGAH_1_PAUSE_LEN_MIN,                                          // pause_1_len_min: minimum length of pause with bit value 1
      SAMSUNGAH_1_PAUSE_LEN_MAX,                                          // pause_1_len_max: maximum length of pause with bit value 1
      SAMSUNGAH_PULSE_LEN_MIN,                                            // pulse_0_len_min: minimum length of pulse with bit value 0
      SAMSUNGAH_PULSE_LEN_MAX,                                            // pulse_0_len_max: maximum length of pulse with bit value 0
      SAMSUNGAH_0_PAUSE_LEN_MIN,                                          // pause_0_len_min: minimum length of pause with bit value 0
      SAMSUNGAH_0_PAUSE_LEN_MAX,                                          // pause_0_len_max: maximum length of pause with bit value 0
      SAMSUNGAH_ADDRESS_OFFSET,                                           // address_offset:  address offset
      SAMSUNGAH_ADDRESS_OFFSET + SAMSUNGAH_ADDRESS_LEN,                   // address_end:     end of address
      SAMSUNGAH_COMMAND_OFFSET,                                           // command_offset:  command offset
      SAMSUNGAH_COMMAND_OFFSET + SAMSUNGAH_COMMAND_LEN,                   // command_end:     end of command
      SAMSUNGAH_COMPLETE_DATA_LEN,                                        // complete_len:    complete length of frame
      SAMSUNGAH_STOP_BIT,                                                 // stop_bit:        flag: frame has stop bit
      SAMSUNGAH_LSB,                                                      // lsb_first:       flag: LSB first
      SAMSUNGAH_FLAGS                                                     // flags:           some flags
  };

#endif

#if IRMP_SUPPORT_TELEFUNKEN_PROTOCOL == 1

   const PROGMEM IRMP_PARAMETER telefunken_param =
  {
      IRMP_TELEFUNKEN_PROTOCOL,                                           // protocol:        ir protocol
      TELEFUNKEN_PULSE_LEN_MIN,                                           // pulse_1_len_min: minimum length of pulse with bit value 1
      TELEFUNKEN_PULSE_LEN_MAX,                                           // pulse_1_len_max: maximum length of pulse with bit value 1
      TELEFUNKEN_1_PAUSE_LEN_MIN,                                         // pause_1_len_min: minimum length of pause with bit value 1
      TELEFUNKEN_1_PAUSE_LEN_MAX,                                         // pause_1_len_max: maximum length of pause with bit value 1
      TELEFUNKEN_PULSE_LEN_MIN,                                           // pulse_0_len_min: minimum length of pulse with bit value 0
      TELEFUNKEN_PULSE_LEN_MAX,                                           // pulse_0_len_max: maximum length of pulse with bit value 0
      TELEFUNKEN_0_PAUSE_LEN_MIN,                                         // pause_0_len_min: minimum length of pause with bit value 0
      TELEFUNKEN_0_PAUSE_LEN_MAX,                                         // pause_0_len_max: maximum length of pause with bit value 0
      TELEFUNKEN_ADDRESS_OFFSET,                                          // address_offset:  address offset
      TELEFUNKEN_ADDRESS_OFFSET + TELEFUNKEN_ADDRESS_LEN,                 // address_end:     end of address
      TELEFUNKEN_COMMAND_OFFSET,                                          // command_offset:  command offset
      TELEFUNKEN_COMMAND_OFFSET + TELEFUNKEN_COMMAND_LEN,                 // command_end:     end of command
      TELEFUNKEN_COMPLETE_DATA_LEN,                                       // complete_len:    complete length of frame
      TELEFUNKEN_STOP_BIT,                                                // stop_bit:        flag: frame has stop bit
      TELEFUNKEN_LSB,                                                     // lsb_first:       flag: LSB first
      TELEFUNKEN_FLAGS                                                    // flags:           some flags
  };

#endif

#if IRMP_SUPPORT_MATSUSHITA_PROTOCOL == 1

   const PROGMEM IRMP_PARAMETER matsushita_param =
  {
      IRMP_MATSUSHITA_PROTOCOL,                                           // protocol:        ir protocol
      MATSUSHITA_PULSE_LEN_MIN,                                           // pulse_1_len_min: minimum length of pulse with bit value 1
      MATSUSHITA_PULSE_LEN_MAX,                                           // pulse_1_len_max: maximum length of pulse with bit value 1
      MATSUSHITA_1_PAUSE_LEN_MIN,                                         // pause_1_len_min: minimum length of pause with bit value 1
      MATSUSHITA_1_PAUSE_LEN_MAX,                                         // pause_1_len_max: maximum length of pause with bit value 1
      MATSUSHITA_PULSE_LEN_MIN,                                           // pulse_0_len_min: minimum length of pulse with bit value 0
      MATSUSHITA_PULSE_LEN_MAX,                                           // pulse_0_len_max: maximum length of pulse with bit value 0
      MATSUSHITA_0_PAUSE_LEN_MIN,                                         // pause_0_len_min: minimum length of pause with bit value 0
      MATSUSHITA_0_PAUSE_LEN_MAX,                                         // pause_0_len_max: maximum length of pause with bit value 0
      MATSUSHITA_ADDRESS_OFFSET,                                          // address_offset:  address offset
      MATSUSHITA_ADDRESS_OFFSET + MATSUSHITA_ADDRESS_LEN,                 // address_end:     end of address
      MATSUSHITA_COMMAND_OFFSET,                                          // command_offset:  command offset
      MATSUSHITA_COMMAND_OFFSET + MATSUSHITA_COMMAND_LEN,                 // command_end:     end of command
      MATSUSHITA_COMPLETE_DATA_LEN,                                       // complete_len:    complete length of frame
      MATSUSHITA_STOP_BIT,                                                // stop_bit:        flag: frame has stop bit
      MATSUSHITA_LSB,                                                     // lsb_first:       flag: LSB first
      MATSUSHITA_FLAGS                                                    // flags:           some flags
  };

#endif

#if IRMP_SUPPORT_KASEIKYO_PROTOCOL == 1

   const PROGMEM IRMP_PARAMETER kaseikyo_param =
  {
      IRMP_KASEIKYO_PROTOCOL,                                             // protocol:        ir protocol
      KASEIKYO_PULSE_LEN_MIN,                                             // pulse_1_len_min: minimum length of pulse with bit value 1
      KASEIKYO_PULSE_LEN_MAX,                                             // pulse_1_len_max: maximum length of pulse with bit value 1
      KASEIKYO_1_PAUSE_LEN_MIN,                                           // pause_1_len_min: minimum length of pause with bit value 1
      KASEIKYO_1_PAUSE_LEN_MAX,                                           // pause_1_len_max: maximum length of pause with bit value 1
      KASEIKYO_PULSE_LEN_MIN,                                             // pulse_0_len_min: minimum length of pulse with bit value 0
      KASEIKYO_PULSE_LEN_MAX,                                             // pulse_0_len_max: maximum length of pulse with bit value 0
      KASEIKYO_0_PAUSE_LEN_MIN,                                           // pause_0_len_min: minimum length of pause with bit value 0
      KASEIKYO_0_PAUSE_LEN_MAX,                                           // pause_0_len_max: maximum length of pause with bit value 0
      KASEIKYO_ADDRESS_OFFSET,                                            // address_offset:  address offset
      KASEIKYO_ADDRESS_OFFSET + KASEIKYO_ADDRESS_LEN,                     // address_end:     end of address
      KASEIKYO_COMMAND_OFFSET,                                            // command_offset:  command offset
      KASEIKYO_COMMAND_OFFSET + KASEIKYO_COMMAND_LEN,                     // command_end:     end of command
      KASEIKYO_COMPLETE_DATA_LEN,                                         // complete_len:    complete length of frame
      KASEIKYO_STOP_BIT,                                                  // stop_bit:        flag: frame has stop bit
      KASEIKYO_LSB,                                                       // lsb_first:       flag: LSB first
      KASEIKYO_FLAGS                                                      // flags:           some flags
  };

#endif

#if IRMP_SUPPORT_PANASONIC_PROTOCOL == 1

   const PROGMEM IRMP_PARAMETER panasonic_param =
  {
      IRMP_PANASONIC_PROTOCOL,                                            // protocol:        ir protocol
      PANASONIC_PULSE_LEN_MIN,                                            // pulse_1_len_min: minimum length of pulse with bit value 1
      PANASONIC_PULSE_LEN_MAX,                                            // pulse_1_len_max: maximum length of pulse with bit value 1
      PANASONIC_1_PAUSE_LEN_MIN,                                          // pause_1_len_min: minimum length of pause with bit value 1
      PANASONIC_1_PAUSE_LEN_MAX,                                          // pause_1_len_max: maximum length of pause with bit value 1
      PANASONIC_PULSE_LEN_MIN,                                            // pulse_0_len_min: minimum length of pulse with bit value 0
      PANASONIC_PULSE_LEN_MAX,                                            // pulse_0_len_max: maximum length of pulse with bit value 0
      PANASONIC_0_PAUSE_LEN_MIN,                                          // pause_0_len_min: minimum length of pause with bit value 0
      PANASONIC_0_PAUSE_LEN_MAX,                                          // pause_0_len_max: maximum length of pause with bit value 0
      PANASONIC_ADDRESS_OFFSET,                                           // address_offset:  address offset
      PANASONIC_ADDRESS_OFFSET + PANASONIC_ADDRESS_LEN,                   // address_end:     end of address
      PANASONIC_COMMAND_OFFSET,                                           // command_offset:  command offset
      PANASONIC_COMMAND_OFFSET + PANASONIC_COMMAND_LEN,                   // command_end:     end of command
      PANASONIC_COMPLETE_DATA_LEN,                                        // complete_len:    complete length of frame
      PANASONIC_STOP_BIT,                                                 // stop_bit:        flag: frame has stop bit
      PANASONIC_LSB,                                                      // lsb_first:       flag: LSB first
      PANASONIC_FLAGS                                                     // flags:           some flags
  };

#endif

#if IRMP_SUPPORT_MITSU_HEAVY_PROTOCOL == 1

   const PROGMEM IRMP_PARAMETER mitsu_heavy_param =
  {
      IRMP_MITSU_HEAVY_PROTOCOL,                                          // protocol:        ir protocol
      MITSU_HEAVY_PULSE_LEN_MIN,                                          // pulse_1_len_min: minimum length of pulse with bit value 1
      MITSU_HEAVY_PULSE_LEN_MAX,                                          // pulse_1_len_max: maximum length of pulse with bit value 1
      MITSU_HEAVY_1_PAUSE_LEN_MIN,                                        // pause_1_len_min: minimum length of pause with bit value 1
      MITSU_HEAVY_1_PAUSE_LEN_MAX,                                        // pause_1_len_max: maximum length of pause with bit value 1
      MITSU_HEAVY_PULSE_LEN_MIN,                                          // pulse_0_len_min: minimum length of pulse with bit value 0
      MITSU_HEAVY_PULSE_LEN_MAX,                                          // pulse_0_len_max: maximum length of pulse with bit value 0
      MITSU_HEAVY_0_PAUSE_LEN_MIN,                                        // pause_0_len_min: minimum length of pause with bit value 0
      MITSU_HEAVY_0_PAUSE_LEN_MAX,                                        // pause_0_len_max: maximum length of pause with bit value 0
      MITSU_HEAVY_ADDRESS_OFFSET,                                         // address_offset:  address offset
      MITSU_HEAVY_ADDRESS_OFFSET + MITSU_HEAVY_ADDRESS_LEN,               // address_end:     end of address
      MITSU_HEAVY_COMMAND_OFFSET,                                         // command_offset:  command offset
      MITSU_HEAVY_COMMAND_OFFSET + MITSU_HEAVY_COMMAND_LEN,               // command_end:     end of command
      MITSU_HEAVY_COMPLETE_DATA_LEN,                                      // complete_len:    complete length of frame
      MITSU_HEAVY_STOP_BIT,                                               // stop_bit:        flag: frame has stop bit
      MITSU_HEAVY_LSB,                                                    // lsb_first:       flag: LSB first
      MITSU_HEAVY_FLAGS                                                   // flags:           some flags
  };

#endif

#if IRMP_SUPPORT_VINCENT_PROTOCOL == 1

   const PROGMEM IRMP_PARAMETER vincent_param =
  {
      IRMP_VINCENT_PROTOCOL,                                              // protocol:        ir protocol
      VINCENT_PULSE_LEN_MIN,                                              // pulse_1_len_min: minimum length of pulse with bit value 1
      VINCENT_PULSE_LEN_MAX,                                              // pulse_1_len_max: maximum length of pulse with bit value 1
      VINCENT_1_PAUSE_LEN_MIN,                                            // pause_1_len_min: minimum length of pause with bit value 1
      VINCENT_1_PAUSE_LEN_MAX,                                            // pause_1_len_max: maximum length of pause with bit value 1
      VINCENT_PULSE_LEN_MIN,                                              // pulse_0_len_min: minimum length of pulse with bit value 0
      VINCENT_PULSE_LEN_MAX,                                              // pulse_0_len_max: maximum length of pulse with bit value 0
      VINCENT_0_PAUSE_LEN_MIN,                                            // pause_0_len_min: minimum length of pause with bit value 0
      VINCENT_0_PAUSE_LEN_MAX,                                            // pause_0_len_max: maximum length of pause with bit value 0
      VINCENT_ADDRESS_OFFSET,                                             // address_offset:  address offset
      VINCENT_ADDRESS_OFFSET + VINCENT_ADDRESS_LEN,                       // address_end:     end of address
      VINCENT_COMMAND_OFFSET,                                             // command_offset:  command offset
      VINCENT_COMMAND_OFFSET + VINCENT_COMMAND_LEN,                       // command_end:     end of command
      VINCENT_COMPLETE_DATA_LEN,                                          // complete_len:    complete length of frame
      VINCENT_STOP_BIT,                                                   // stop_bit:        flag: frame has stop bit
      VINCENT_LSB,                                                        // lsb_first:       flag: LSB first
      VINCENT_FLAGS                                                       // flags:           some flags
  };

#endif

#if IRMP_SUPPORT_RECS80_PROTOCOL == 1

   const PROGMEM IRMP_PARAMETER recs80_param =
  {
      IRMP_RECS80_PROTOCOL,                                               // protocol:        ir protocol
      RECS80_PULSE_LEN_MIN,                                               // pulse_1_len_min: minimum length of pulse with bit value 1
      RECS80_PULSE_LEN_MAX,                                               // pulse_1_len_max: maximum length of pulse with bit value 1
      RECS80_1_PAUSE_LEN_MIN,                                             // pause_1_len_min: minimum length of pause with bit value 1
      RECS80_1_PAUSE_LEN_MAX,                                             // pause_1_len_max: maximum length of pause with bit value 1
      RECS80_PULSE_LEN_MIN,                                               // pulse_0_len_min: minimum length of pulse with bit value 0
      RECS80_PULSE_LEN_MAX,                                               // pulse_0_len_max: maximum length of pulse with bit value 0
      RECS80_0_PAUSE_LEN_MIN,                                             // pause_0_len_min: minimum length of pause with bit value 0
      RECS80_0_PAUSE_LEN_MAX,                                             // pause_0_len_max: maximum length of pause with bit value 0
      RECS80_ADDRESS_OFFSET,                                              // address_offset:  address offset
      RECS80_ADDRESS_OFFSET + RECS80_ADDRESS_LEN,                         // address_end:     end of address
      RECS80_COMMAND_OFFSET,                                              // command_offset:  command offset
      RECS80_COMMAND_OFFSET + RECS80_COMMAND_LEN,                         // command_end:     end of command
      RECS80_COMPLETE_DATA_LEN,                                           // complete_len:    complete length of frame
      RECS80_STOP_BIT,                                                    // stop_bit:        flag: frame has stop bit
      RECS80_LSB,                                                         // lsb_first:       flag: LSB first
      RECS80_FLAGS                                                        // flags:           some flags
  };

#endif

#if IRMP_SUPPORT_RC5_PROTOCOL == 1

   const PROGMEM IRMP_PARAMETER rc5_param =
  {
      IRMP_RC5_PROTOCOL,                                                  // protocol:        ir protocol
      RC5_BIT_LEN_MIN,                                                    // pulse_1_len_min: here: minimum length of short pulse
      RC5_BIT_LEN_MAX,                                                    // pulse_1_len_max: here: maximum length of short pulse
      RC5_BIT_LEN_MIN,                                                    // pause_1_len_min: here: minimum length of short pause
      RC5_BIT_LEN_MAX,                                                    // pause_1_len_max: here: maximum length of short pause
      0,                                                                  // pulse_0_len_min: here: not used
      0,                                                                  // pulse_0_len_max: here: not used
      0,                                                                  // pause_0_len_min: here: not used
      0,                                                                  // pause_0_len_max: here: not used
      RC5_ADDRESS_OFFSET,                                                 // address_offset:  address offset
      RC5_ADDRESS_OFFSET + RC5_ADDRESS_LEN,                               // address_end:     end of address
      RC5_COMMAND_OFFSET,                                                 // command_offset:  command offset
      RC5_COMMAND_OFFSET + RC5_COMMAND_LEN,                               // command_end:     end of command
      RC5_COMPLETE_DATA_LEN,                                              // complete_len:    complete length of frame
      RC5_STOP_BIT,                                                       // stop_bit:        flag: frame has stop bit
      RC5_LSB,                                                            // lsb_first:       flag: LSB first
      RC5_FLAGS                                                           // flags:           some flags
  };

#endif

#if IRMP_SUPPORT_RCII_PROTOCOL == 1

   const PROGMEM IRMP_PARAMETER rcii_param =
  {
      IRMP_RCII_PROTOCOL,                                                 // protocol:        ir protocol
      RCII_BIT_LEN_MIN,                                                   // pulse_1_len_min: here: minimum length of short pulse
      RCII_BIT_LEN_MAX,                                                   // pulse_1_len_max: here: maximum length of short pulse
      RCII_BIT_LEN_MIN,                                                   // pause_1_len_min: here: minimum length of short pause
      RCII_BIT_LEN_MAX,                                                   // pause_1_len_max: here: maximum length of short pause
      RCII_BIT_LEN_MIN,                                                                  // pulse_0_len_min: here: not used
      RCII_BIT_LEN_MAX,                                                                  // pulse_0_len_max: here: not used
      RCII_BIT_LEN_MIN,                                                                  // pause_0_len_min: here: not used
      RCII_BIT_LEN_MAX,                                                                  // pause_0_len_max: here: not used
      RCII_ADDRESS_OFFSET,                                                // address_offset:  address offset
      RCII_ADDRESS_OFFSET + RCII_ADDRESS_LEN,                             // address_end:     end of address
      RCII_COMMAND_OFFSET,                                                // command_offset:  command offset
      RCII_COMMAND_OFFSET + RCII_COMMAND_LEN,                             // command_end:     end of command
      RCII_COMPLETE_DATA_LEN,                                             // complete_len:    complete length of frame
      RCII_STOP_BIT,                                                      // stop_bit:        flag: frame has stop bit
      RCII_LSB,                                                           // lsb_first:       flag: LSB first
      RCII_FLAGS                                                          // flags:           some flags
  };

#endif

#if IRMP_SUPPORT_S100_PROTOCOL == 1

   const PROGMEM IRMP_PARAMETER s100_param =
  {
      IRMP_S100_PROTOCOL,                                                 // protocol:        ir protocol
      S100_BIT_LEN_MIN,                                                   // pulse_1_len_min: here: minimum length of short pulse
      S100_BIT_LEN_MAX,                                                   // pulse_1_len_max: here: maximum length of short pulse
      S100_BIT_LEN_MIN,                                                   // pause_1_len_min: here: minimum length of short pause
      S100_BIT_LEN_MAX,                                                   // pause_1_len_max: here: maximum length of short pause
      0,                                                                  // pulse_0_len_min: here: not used
      0,                                                                  // pulse_0_len_max: here: not used
      0,                                                                  // pause_0_len_min: here: not used
      0,                                                                  // pause_0_len_max: here: not used
      S100_ADDRESS_OFFSET,                                                // address_offset:  address offset
      S100_ADDRESS_OFFSET + S100_ADDRESS_LEN,                             // address_end:     end of address
      S100_COMMAND_OFFSET,                                                // command_offset:  command offset
      S100_COMMAND_OFFSET + S100_COMMAND_LEN,                             // command_end:     end of command
      S100_COMPLETE_DATA_LEN,                                             // complete_len:    complete length of frame
      S100_STOP_BIT,                                                      // stop_bit:        flag: frame has stop bit
      S100_LSB,                                                           // lsb_first:       flag: LSB first
      S100_FLAGS                                                          // flags:           some flags
  };

#endif

#if IRMP_SUPPORT_DENON_PROTOCOL == 1

   const PROGMEM IRMP_PARAMETER denon_param =
  {
      IRMP_DENON_PROTOCOL,                                                // protocol:        ir protocol
      DENON_PULSE_LEN_MIN,                                                // pulse_1_len_min: minimum length of pulse with bit value 1
      DENON_PULSE_LEN_MAX,                                                // pulse_1_len_max: maximum length of pulse with bit value 1
      DENON_1_PAUSE_LEN_MIN,                                              // pause_1_len_min: minimum length of pause with bit value 1
      DENON_1_PAUSE_LEN_MAX,                                              // pause_1_len_max: maximum length of pause with bit value 1
      DENON_PULSE_LEN_MIN,                                                // pulse_0_len_min: minimum length of pulse with bit value 0
      DENON_PULSE_LEN_MAX,                                                // pulse_0_len_max: maximum length of pulse with bit value 0
      DENON_0_PAUSE_LEN_MIN,                                              // pause_0_len_min: minimum length of pause with bit value 0
      DENON_0_PAUSE_LEN_MAX,                                              // pause_0_len_max: maximum length of pause with bit value 0
      DENON_ADDRESS_OFFSET,                                               // address_offset:  address offset
      DENON_ADDRESS_OFFSET + DENON_ADDRESS_LEN,                           // address_end:     end of address
      DENON_COMMAND_OFFSET,                                               // command_offset:  command offset
      DENON_COMMAND_OFFSET + DENON_COMMAND_LEN,                           // command_end:     end of command
      DENON_COMPLETE_DATA_LEN,                                            // complete_len:    complete length of frame
      DENON_STOP_BIT,                                                     // stop_bit:        flag: frame has stop bit
      DENON_LSB,                                                          // lsb_first:       flag: LSB first
      DENON_FLAGS                                                         // flags:           some flags
  };

#endif

#if IRMP_SUPPORT_RC6_PROTOCOL == 1

   const PROGMEM IRMP_PARAMETER rc6_param =
  {
      IRMP_RC6_PROTOCOL,                                                  // protocol:        ir protocol

      RC6_BIT_PULSE_LEN_MIN,                                              // pulse_1_len_min: here: minimum length of short pulse
      RC6_BIT_PULSE_LEN_MAX,                                              // pulse_1_len_max: here: maximum length of short pulse
      RC6_BIT_PAUSE_LEN_MIN,                                              // pause_1_len_min: here: minimum length of short pause
      RC6_BIT_PAUSE_LEN_MAX,                                              // pause_1_len_max: here: maximum length of short pause
      0,                                                                  // pulse_0_len_min: here: not used
      0,                                                                  // pulse_0_len_max: here: not used
      0,                                                                  // pause_0_len_min: here: not used
      0,                                                                  // pause_0_len_max: here: not used
      RC6_ADDRESS_OFFSET,                                                 // address_offset:  address offset
      RC6_ADDRESS_OFFSET + RC6_ADDRESS_LEN,                               // address_end:     end of address
      RC6_COMMAND_OFFSET,                                                 // command_offset:  command offset
      RC6_COMMAND_OFFSET + RC6_COMMAND_LEN,                               // command_end:     end of command
      RC6_COMPLETE_DATA_LEN_SHORT,                                        // complete_len:    complete length of frame
      RC6_STOP_BIT,                                                       // stop_bit:        flag: frame has stop bit
      RC6_LSB,                                                            // lsb_first:       flag: LSB first
      RC6_FLAGS                                                           // flags:           some flags
  };

#endif

#if IRMP_SUPPORT_RECS80EXT_PROTOCOL == 1

   const PROGMEM IRMP_PARAMETER recs80ext_param =
  {
      IRMP_RECS80EXT_PROTOCOL,                                            // protocol:        ir protocol
      RECS80EXT_PULSE_LEN_MIN,                                            // pulse_1_len_min: minimum length of pulse with bit value 1
      RECS80EXT_PULSE_LEN_MAX,                                            // pulse_1_len_max: maximum length of pulse with bit value 1
      RECS80EXT_1_PAUSE_LEN_MIN,                                          // pause_1_len_min: minimum length of pause with bit value 1
      RECS80EXT_1_PAUSE_LEN_MAX,                                          // pause_1_len_max: maximum length of pause with bit value 1
      RECS80EXT_PULSE_LEN_MIN,                                            // pulse_0_len_min: minimum length of pulse with bit value 0
      RECS80EXT_PULSE_LEN_MAX,                                            // pulse_0_len_max: maximum length of pulse with bit value 0
      RECS80EXT_0_PAUSE_LEN_MIN,                                          // pause_0_len_min: minimum length of pause with bit value 0
      RECS80EXT_0_PAUSE_LEN_MAX,                                          // pause_0_len_max: maximum length of pause with bit value 0
      RECS80EXT_ADDRESS_OFFSET,                                           // address_offset:  address offset
      RECS80EXT_ADDRESS_OFFSET + RECS80EXT_ADDRESS_LEN,                   // address_end:     end of address
      RECS80EXT_COMMAND_OFFSET,                                           // command_offset:  command offset
      RECS80EXT_COMMAND_OFFSET + RECS80EXT_COMMAND_LEN,                   // command_end:     end of command
      RECS80EXT_COMPLETE_DATA_LEN,                                        // complete_len:    complete length of frame
      RECS80EXT_STOP_BIT,                                                 // stop_bit:        flag: frame has stop bit
      RECS80EXT_LSB,                                                      // lsb_first:       flag: LSB first
      RECS80EXT_FLAGS                                                     // flags:           some flags
  };

#endif

#if IRMP_SUPPORT_NUBERT_PROTOCOL == 1

   const PROGMEM IRMP_PARAMETER nubert_param =
  {
      IRMP_NUBERT_PROTOCOL,                                               // protocol:        ir protocol
      NUBERT_1_PULSE_LEN_MIN,                                             // pulse_1_len_min: minimum length of pulse with bit value 1
      NUBERT_1_PULSE_LEN_MAX,                                             // pulse_1_len_max: maximum length of pulse with bit value 1
      NUBERT_1_PAUSE_LEN_MIN,                                             // pause_1_len_min: minimum length of pause with bit value 1
      NUBERT_1_PAUSE_LEN_MAX,                                             // pause_1_len_max: maximum length of pause with bit value 1
      NUBERT_0_PULSE_LEN_MIN,                                             // pulse_0_len_min: minimum length of pulse with bit value 0
      NUBERT_0_PULSE_LEN_MAX,                                             // pulse_0_len_max: maximum length of pulse with bit value 0
      NUBERT_0_PAUSE_LEN_MIN,                                             // pause_0_len_min: minimum length of pause with bit value 0
      NUBERT_0_PAUSE_LEN_MAX,                                             // pause_0_len_max: maximum length of pause with bit value 0
      NUBERT_ADDRESS_OFFSET,                                              // address_offset:  address offset
      NUBERT_ADDRESS_OFFSET + NUBERT_ADDRESS_LEN,                         // address_end:     end of address
      NUBERT_COMMAND_OFFSET,                                              // command_offset:  command offset
      NUBERT_COMMAND_OFFSET + NUBERT_COMMAND_LEN,                         // command_end:     end of command
      NUBERT_COMPLETE_DATA_LEN,                                           // complete_len:    complete length of frame
      NUBERT_STOP_BIT,                                                    // stop_bit:        flag: frame has stop bit
      NUBERT_LSB,                                                         // lsb_first:       flag: LSB first
      NUBERT_FLAGS                                                        // flags:           some flags
  };

#endif

#if IRMP_SUPPORT_FAN_PROTOCOL == 1

   const PROGMEM IRMP_PARAMETER fan_param =
  {
      IRMP_FAN_PROTOCOL,                                                  // protocol:        ir protocol
      FAN_1_PULSE_LEN_MIN,                                                // pulse_1_len_min: minimum length of pulse with bit value 1
      FAN_1_PULSE_LEN_MAX,                                                // pulse_1_len_max: maximum length of pulse with bit value 1
      FAN_1_PAUSE_LEN_MIN,                                                // pause_1_len_min: minimum length of pause with bit value 1
      FAN_1_PAUSE_LEN_MAX,                                                // pause_1_len_max: maximum length of pause with bit value 1
      FAN_0_PULSE_LEN_MIN,                                                // pulse_0_len_min: minimum length of pulse with bit value 0
      FAN_0_PULSE_LEN_MAX,                                                // pulse_0_len_max: maximum length of pulse with bit value 0
      FAN_0_PAUSE_LEN_MIN,                                                // pause_0_len_min: minimum length of pause with bit value 0
      FAN_0_PAUSE_LEN_MAX,                                                // pause_0_len_max: maximum length of pause with bit value 0
      FAN_ADDRESS_OFFSET,                                                 // address_offset:  address offset
      FAN_ADDRESS_OFFSET + FAN_ADDRESS_LEN,                               // address_end:     end of address
      FAN_COMMAND_OFFSET,                                                 // command_offset:  command offset
      FAN_COMMAND_OFFSET + FAN_COMMAND_LEN,                               // command_end:     end of command
      FAN_COMPLETE_DATA_LEN,                                              // complete_len:    complete length of frame
      FAN_STOP_BIT,                                                       // stop_bit:        flag: frame has NO stop bit
      FAN_LSB,                                                            // lsb_first:       flag: LSB first
      FAN_FLAGS                                                           // flags:           some flags
  };

#endif

#if IRMP_SUPPORT_SPEAKER_PROTOCOL == 1

   const PROGMEM IRMP_PARAMETER speaker_param =
  {
      IRMP_SPEAKER_PROTOCOL,                                              // protocol:        ir protocol
      SPEAKER_1_PULSE_LEN_MIN,                                            // pulse_1_len_min: minimum length of pulse with bit value 1
      SPEAKER_1_PULSE_LEN_MAX,                                            // pulse_1_len_max: maximum length of pulse with bit value 1
      SPEAKER_1_PAUSE_LEN_MIN,                                            // pause_1_len_min: minimum length of pause with bit value 1
      SPEAKER_1_PAUSE_LEN_MAX,                                            // pause_1_len_max: maximum length of pause with bit value 1
      SPEAKER_0_PULSE_LEN_MIN,                                            // pulse_0_len_min: minimum length of pulse with bit value 0
      SPEAKER_0_PULSE_LEN_MAX,                                            // pulse_0_len_max: maximum length of pulse with bit value 0
      SPEAKER_0_PAUSE_LEN_MIN,                                            // pause_0_len_min: minimum length of pause with bit value 0
      SPEAKER_0_PAUSE_LEN_MAX,                                            // pause_0_len_max: maximum length of pause with bit value 0
      SPEAKER_ADDRESS_OFFSET,                                             // address_offset:  address offset
      SPEAKER_ADDRESS_OFFSET + SPEAKER_ADDRESS_LEN,                       // address_end:     end of address
      SPEAKER_COMMAND_OFFSET,                                             // command_offset:  command offset
      SPEAKER_COMMAND_OFFSET + SPEAKER_COMMAND_LEN,                       // command_end:     end of command
      SPEAKER_COMPLETE_DATA_LEN,                                          // complete_len:    complete length of frame
      SPEAKER_STOP_BIT,                                                   // stop_bit:        flag: frame has stop bit
      SPEAKER_LSB,                                                        // lsb_first:       flag: LSB first
      SPEAKER_FLAGS                                                       // flags:           some flags
  };

#endif

#if IRMP_SUPPORT_BANG_OLUFSEN_PROTOCOL == 1

   const PROGMEM IRMP_PARAMETER bang_olufsen_param =
  {
      IRMP_BANG_OLUFSEN_PROTOCOL,                                         // protocol:        ir protocol
      BANG_OLUFSEN_PULSE_LEN_MIN,                                         // pulse_1_len_min: minimum length of pulse with bit value 1
      BANG_OLUFSEN_PULSE_LEN_MAX,                                         // pulse_1_len_max: maximum length of pulse with bit value 1
      BANG_OLUFSEN_1_PAUSE_LEN_MIN,                                       // pause_1_len_min: minimum length of pause with bit value 1
      BANG_OLUFSEN_1_PAUSE_LEN_MAX,                                       // pause_1_len_max: maximum length of pause with bit value 1
      BANG_OLUFSEN_PULSE_LEN_MIN,                                         // pulse_0_len_min: minimum length of pulse with bit value 0
      BANG_OLUFSEN_PULSE_LEN_MAX,                                         // pulse_0_len_max: maximum length of pulse with bit value 0
      BANG_OLUFSEN_0_PAUSE_LEN_MIN,                                       // pause_0_len_min: minimum length of pause with bit value 0
      BANG_OLUFSEN_0_PAUSE_LEN_MAX,                                       // pause_0_len_max: maximum length of pause with bit value 0
      BANG_OLUFSEN_ADDRESS_OFFSET,                                        // address_offset:  address offset
      BANG_OLUFSEN_ADDRESS_OFFSET + BANG_OLUFSEN_ADDRESS_LEN,             // address_end:     end of address
      BANG_OLUFSEN_COMMAND_OFFSET,                                        // command_offset:  command offset
      BANG_OLUFSEN_COMMAND_OFFSET + BANG_OLUFSEN_COMMAND_LEN,             // command_end:     end of command
      BANG_OLUFSEN_COMPLETE_DATA_LEN,                                     // complete_len:    complete length of frame
      BANG_OLUFSEN_STOP_BIT,                                              // stop_bit:        flag: frame has stop bit
      BANG_OLUFSEN_LSB,                                                   // lsb_first:       flag: LSB first
      BANG_OLUFSEN_FLAGS                                                  // flags:           some flags
  };

#endif

#if IRMP_SUPPORT_GRUNDIG_NOKIA_IR60_PROTOCOL == 1

   uint_fast8_t first_bit;

   const PROGMEM IRMP_PARAMETER grundig_param =
  {
      IRMP_GRUNDIG_PROTOCOL,                                              // protocol:        ir protocol

      GRUNDIG_NOKIA_IR60_BIT_LEN_MIN,                                     // pulse_1_len_min: here: minimum length of short pulse
      GRUNDIG_NOKIA_IR60_BIT_LEN_MAX,                                     // pulse_1_len_max: here: maximum length of short pulse
      GRUNDIG_NOKIA_IR60_BIT_LEN_MIN,                                     // pause_1_len_min: here: minimum length of short pause
      GRUNDIG_NOKIA_IR60_BIT_LEN_MAX,                                     // pause_1_len_max: here: maximum length of short pause
      0,                                                                  // pulse_0_len_min: here: not used
      0,                                                                  // pulse_0_len_max: here: not used
      0,                                                                  // pause_0_len_min: here: not used
      0,                                                                  // pause_0_len_max: here: not used
      GRUNDIG_ADDRESS_OFFSET,                                             // address_offset:  address offset
      GRUNDIG_ADDRESS_OFFSET + GRUNDIG_ADDRESS_LEN,                       // address_end:     end of address
      GRUNDIG_COMMAND_OFFSET,                                             // command_offset:  command offset
      GRUNDIG_COMMAND_OFFSET + GRUNDIG_COMMAND_LEN + 1,                   // command_end:     end of command (USE 1 bit MORE to STORE NOKIA DATA!)
      NOKIA_COMPLETE_DATA_LEN,                                            // complete_len:    complete length of frame, here: NOKIA instead of GRUNDIG!
      GRUNDIG_NOKIA_IR60_STOP_BIT,                                        // stop_bit:        flag: frame has stop bit
      GRUNDIG_NOKIA_IR60_LSB,                                             // lsb_first:       flag: LSB first
      GRUNDIG_NOKIA_IR60_FLAGS                                            // flags:           some flags
  };

#endif

#if IRMP_SUPPORT_SIEMENS_OR_RUWIDO_PROTOCOL == 1

   const PROGMEM IRMP_PARAMETER ruwido_param =
  {
      IRMP_RUWIDO_PROTOCOL,                                               // protocol:        ir protocol
      SIEMENS_OR_RUWIDO_BIT_PULSE_LEN_MIN,                                // pulse_1_len_min: here: minimum length of short pulse
      SIEMENS_OR_RUWIDO_BIT_PULSE_LEN_MAX,                                // pulse_1_len_max: here: maximum length of short pulse
      SIEMENS_OR_RUWIDO_BIT_PAUSE_LEN_MIN,                                // pause_1_len_min: here: minimum length of short pause
      SIEMENS_OR_RUWIDO_BIT_PAUSE_LEN_MAX,                                // pause_1_len_max: here: maximum length of short pause
      0,                                                                  // pulse_0_len_min: here: not used
      0,                                                                  // pulse_0_len_max: here: not used
      0,                                                                  // pause_0_len_min: here: not used
      0,                                                                  // pause_0_len_max: here: not used
      RUWIDO_ADDRESS_OFFSET,                                              // address_offset:  address offset
      RUWIDO_ADDRESS_OFFSET + RUWIDO_ADDRESS_LEN,                         // address_end:     end of address
      RUWIDO_COMMAND_OFFSET,                                              // command_offset:  command offset
      RUWIDO_COMMAND_OFFSET + RUWIDO_COMMAND_LEN,                         // command_end:     end of command
      SIEMENS_COMPLETE_DATA_LEN,                                          // complete_len:    complete length of frame, here: SIEMENS instead of RUWIDO!
      SIEMENS_OR_RUWIDO_STOP_BIT,                                         // stop_bit:        flag: frame has stop bit
      SIEMENS_OR_RUWIDO_LSB,                                              // lsb_first:       flag: LSB first
      SIEMENS_OR_RUWIDO_FLAGS                                             // flags:           some flags
  };

#endif

#if IRMP_SUPPORT_FDC_PROTOCOL == 1

   const PROGMEM IRMP_PARAMETER fdc_param =
  {
      IRMP_FDC_PROTOCOL,                                                  // protocol:        ir protocol
      FDC_PULSE_LEN_MIN,                                                  // pulse_1_len_min: minimum length of pulse with bit value 1
      FDC_PULSE_LEN_MAX,                                                  // pulse_1_len_max: maximum length of pulse with bit value 1
      FDC_1_PAUSE_LEN_MIN,                                                // pause_1_len_min: minimum length of pause with bit value 1
      FDC_1_PAUSE_LEN_MAX,                                                // pause_1_len_max: maximum length of pause with bit value 1
      FDC_PULSE_LEN_MIN,                                                  // pulse_0_len_min: minimum length of pulse with bit value 0
      FDC_PULSE_LEN_MAX,                                                  // pulse_0_len_max: maximum length of pulse with bit value 0
      FDC_0_PAUSE_LEN_MIN,                                                // pause_0_len_min: minimum length of pause with bit value 0
      FDC_0_PAUSE_LEN_MAX,                                                // pause_0_len_max: maximum length of pause with bit value 0
      FDC_ADDRESS_OFFSET,                                                 // address_offset:  address offset
      FDC_ADDRESS_OFFSET + FDC_ADDRESS_LEN,                               // address_end:     end of address
      FDC_COMMAND_OFFSET,                                                 // command_offset:  command offset
      FDC_COMMAND_OFFSET + FDC_COMMAND_LEN,                               // command_end:     end of command
      FDC_COMPLETE_DATA_LEN,                                              // complete_len:    complete length of frame
      FDC_STOP_BIT,                                                       // stop_bit:        flag: frame has stop bit
      FDC_LSB,                                                            // lsb_first:       flag: LSB first
      FDC_FLAGS                                                           // flags:           some flags
  };

#endif

#if IRMP_SUPPORT_RCCAR_PROTOCOL == 1

   const PROGMEM IRMP_PARAMETER rccar_param =
  {
      IRMP_RCCAR_PROTOCOL,                                                // protocol:        ir protocol
      RCCAR_PULSE_LEN_MIN,                                                // pulse_1_len_min: minimum length of pulse with bit value 1
      RCCAR_PULSE_LEN_MAX,                                                // pulse_1_len_max: maximum length of pulse with bit value 1
      RCCAR_1_PAUSE_LEN_MIN,                                              // pause_1_len_min: minimum length of pause with bit value 1
      RCCAR_1_PAUSE_LEN_MAX,                                              // pause_1_len_max: maximum length of pause with bit value 1
      RCCAR_PULSE_LEN_MIN,                                                // pulse_0_len_min: minimum length of pulse with bit value 0
      RCCAR_PULSE_LEN_MAX,                                                // pulse_0_len_max: maximum length of pulse with bit value 0
      RCCAR_0_PAUSE_LEN_MIN,                                              // pause_0_len_min: minimum length of pause with bit value 0
      RCCAR_0_PAUSE_LEN_MAX,                                              // pause_0_len_max: maximum length of pause with bit value 0
      RCCAR_ADDRESS_OFFSET,                                               // address_offset:  address offset
      RCCAR_ADDRESS_OFFSET + RCCAR_ADDRESS_LEN,                           // address_end:     end of address
      RCCAR_COMMAND_OFFSET,                                               // command_offset:  command offset
      RCCAR_COMMAND_OFFSET + RCCAR_COMMAND_LEN,                           // command_end:     end of command
      RCCAR_COMPLETE_DATA_LEN,                                            // complete_len:    complete length of frame
      RCCAR_STOP_BIT,                                                     // stop_bit:        flag: frame has stop bit
      RCCAR_LSB,                                                          // lsb_first:       flag: LSB first
      RCCAR_FLAGS                                                         // flags:           some flags
  };

#endif

#if IRMP_SUPPORT_NIKON_PROTOCOL == 1

   const PROGMEM IRMP_PARAMETER nikon_param =
  {
      IRMP_NIKON_PROTOCOL,                                                // protocol:        ir protocol
      NIKON_PULSE_LEN_MIN,                                                // pulse_1_len_min: minimum length of pulse with bit value 1
      NIKON_PULSE_LEN_MAX,                                                // pulse_1_len_max: maximum length of pulse with bit value 1
      NIKON_1_PAUSE_LEN_MIN,                                              // pause_1_len_min: minimum length of pause with bit value 1
      NIKON_1_PAUSE_LEN_MAX,                                              // pause_1_len_max: maximum length of pause with bit value 1
      NIKON_PULSE_LEN_MIN,                                                // pulse_0_len_min: minimum length of pulse with bit value 0
      NIKON_PULSE_LEN_MAX,                                                // pulse_0_len_max: maximum length of pulse with bit value 0
      NIKON_0_PAUSE_LEN_MIN,                                              // pause_0_len_min: minimum length of pause with bit value 0
      NIKON_0_PAUSE_LEN_MAX,                                              // pause_0_len_max: maximum length of pause with bit value 0
      NIKON_ADDRESS_OFFSET,                                               // address_offset:  address offset
      NIKON_ADDRESS_OFFSET + NIKON_ADDRESS_LEN,                           // address_end:     end of address
      NIKON_COMMAND_OFFSET,                                               // command_offset:  command offset
      NIKON_COMMAND_OFFSET + NIKON_COMMAND_LEN,                           // command_end:     end of command
      NIKON_COMPLETE_DATA_LEN,                                            // complete_len:    complete length of frame
      NIKON_STOP_BIT,                                                     // stop_bit:        flag: frame has stop bit
      NIKON_LSB,                                                          // lsb_first:       flag: LSB first
      NIKON_FLAGS                                                         // flags:           some flags
  };

#endif

#if IRMP_SUPPORT_KATHREIN_PROTOCOL == 1

   const PROGMEM IRMP_PARAMETER kathrein_param =
  {
      IRMP_KATHREIN_PROTOCOL,                                             // protocol:        ir protocol
      KATHREIN_1_PULSE_LEN_MIN,                                           // pulse_1_len_min: minimum length of pulse with bit value 1
      KATHREIN_1_PULSE_LEN_MAX,                                           // pulse_1_len_max: maximum length of pulse with bit value 1
      KATHREIN_1_PAUSE_LEN_MIN,                                           // pause_1_len_min: minimum length of pause with bit value 1
      KATHREIN_1_PAUSE_LEN_MAX,                                           // pause_1_len_max: maximum length of pause with bit value 1
      KATHREIN_0_PULSE_LEN_MIN,                                           // pulse_0_len_min: minimum length of pulse with bit value 0
      KATHREIN_0_PULSE_LEN_MAX,                                           // pulse_0_len_max: maximum length of pulse with bit value 0
      KATHREIN_0_PAUSE_LEN_MIN,                                           // pause_0_len_min: minimum length of pause with bit value 0
      KATHREIN_0_PAUSE_LEN_MAX,                                           // pause_0_len_max: maximum length of pause with bit value 0
      KATHREIN_ADDRESS_OFFSET,                                            // address_offset:  address offset
      KATHREIN_ADDRESS_OFFSET + KATHREIN_ADDRESS_LEN,                     // address_end:     end of address
      KATHREIN_COMMAND_OFFSET,                                            // command_offset:  command offset
      KATHREIN_COMMAND_OFFSET + KATHREIN_COMMAND_LEN,                     // command_end:     end of command
      KATHREIN_COMPLETE_DATA_LEN,                                         // complete_len:    complete length of frame
      KATHREIN_STOP_BIT,                                                  // stop_bit:        flag: frame has stop bit
      KATHREIN_LSB,                                                       // lsb_first:       flag: LSB first
      KATHREIN_FLAGS                                                      // flags:           some flags
  };

#endif

#if IRMP_SUPPORT_NETBOX_PROTOCOL == 1

   const PROGMEM IRMP_PARAMETER netbox_param =
  {
      IRMP_NETBOX_PROTOCOL,                                               // protocol:        ir protocol
      NETBOX_PULSE_LEN,                                                   // pulse_1_len_min: minimum length of pulse with bit value 1, here: exact value
      NETBOX_PULSE_REST_LEN,                                              // pulse_1_len_max: maximum length of pulse with bit value 1, here: rest value
      NETBOX_PAUSE_LEN,                                                   // pause_1_len_min: minimum length of pause with bit value 1, here: exact value
      NETBOX_PAUSE_REST_LEN,                                              // pause_1_len_max: maximum length of pause with bit value 1, here: rest value
      NETBOX_PULSE_LEN,                                                   // pulse_0_len_min: minimum length of pulse with bit value 0, here: exact value
      NETBOX_PULSE_REST_LEN,                                              // pulse_0_len_max: maximum length of pulse with bit value 0, here: rest value
      NETBOX_PAUSE_LEN,                                                   // pause_0_len_min: minimum length of pause with bit value 0, here: exact value
      NETBOX_PAUSE_REST_LEN,                                              // pause_0_len_max: maximum length of pause with bit value 0, here: rest value
      NETBOX_ADDRESS_OFFSET,                                              // address_offset:  address offset
      NETBOX_ADDRESS_OFFSET + NETBOX_ADDRESS_LEN,                         // address_end:     end of address
      NETBOX_COMMAND_OFFSET,                                              // command_offset:  command offset
      NETBOX_COMMAND_OFFSET + NETBOX_COMMAND_LEN,                         // command_end:     end of command
      NETBOX_COMPLETE_DATA_LEN,                                           // complete_len:    complete length of frame
      NETBOX_STOP_BIT,                                                    // stop_bit:        flag: frame has stop bit
      NETBOX_LSB,                                                         // lsb_first:       flag: LSB first
      NETBOX_FLAGS                                                        // flags:           some flags
  };

#endif

#if IRMP_SUPPORT_LEGO_PROTOCOL == 1

   const PROGMEM IRMP_PARAMETER lego_param =
  {
      IRMP_LEGO_PROTOCOL,                                                 // protocol:        ir protocol
      LEGO_PULSE_LEN_MIN,                                                 // pulse_1_len_min: minimum length of pulse with bit value 1
      LEGO_PULSE_LEN_MAX,                                                 // pulse_1_len_max: maximum length of pulse with bit value 1
      LEGO_1_PAUSE_LEN_MIN,                                               // pause_1_len_min: minimum length of pause with bit value 1
      LEGO_1_PAUSE_LEN_MAX,                                               // pause_1_len_max: maximum length of pause with bit value 1
      LEGO_PULSE_LEN_MIN,                                                 // pulse_0_len_min: minimum length of pulse with bit value 0
      LEGO_PULSE_LEN_MAX,                                                 // pulse_0_len_max: maximum length of pulse with bit value 0
      LEGO_0_PAUSE_LEN_MIN,                                               // pause_0_len_min: minimum length of pause with bit value 0
      LEGO_0_PAUSE_LEN_MAX,                                               // pause_0_len_max: maximum length of pause with bit value 0
      LEGO_ADDRESS_OFFSET,                                                // address_offset:  address offset
      LEGO_ADDRESS_OFFSET + LEGO_ADDRESS_LEN,                             // address_end:     end of address
      LEGO_COMMAND_OFFSET,                                                // command_offset:  command offset
      LEGO_COMMAND_OFFSET + LEGO_COMMAND_LEN,                             // command_end:     end of command
      LEGO_COMPLETE_DATA_LEN,                                             // complete_len:    complete length of frame
      LEGO_STOP_BIT,                                                      // stop_bit:        flag: frame has stop bit
      LEGO_LSB,                                                           // lsb_first:       flag: LSB first
      LEGO_FLAGS                                                          // flags:           some flags
  };

#endif

#if IRMP_SUPPORT_IRMP16_PROTOCOL == 1

   const PROGMEM IRMP_PARAMETER irmp16_param =
  {
      IRMP_IRMP16_PROTOCOL,                                               // protocol:        ir protocol
      IRMP16_PULSE_LEN_MIN,                                               // pulse_1_len_min: minimum length of pulse with bit value 1
      IRMP16_PULSE_LEN_MAX,                                               // pulse_1_len_max: maximum length of pulse with bit value 1
      IRMP16_1_PAUSE_LEN_MIN,                                             // pause_1_len_min: minimum length of pause with bit value 1
      IRMP16_1_PAUSE_LEN_MAX,                                             // pause_1_len_max: maximum length of pause with bit value 1
      IRMP16_PULSE_LEN_MIN,                                               // pulse_0_len_min: minimum length of pulse with bit value 0
      IRMP16_PULSE_LEN_MAX,                                               // pulse_0_len_max: maximum length of pulse with bit value 0
      IRMP16_0_PAUSE_LEN_MIN,                                             // pause_0_len_min: minimum length of pause with bit value 0
      IRMP16_0_PAUSE_LEN_MAX,                                             // pause_0_len_max: maximum length of pause with bit value 0
      IRMP16_ADDRESS_OFFSET,                                              // address_offset:  address offset
      IRMP16_ADDRESS_OFFSET + IRMP16_ADDRESS_LEN,                         // address_end:     end of address
      IRMP16_COMMAND_OFFSET,                                              // command_offset:  command offset
      IRMP16_COMMAND_OFFSET + IRMP16_COMMAND_LEN,                         // command_end:     end of command
      IRMP16_COMPLETE_DATA_LEN,                                           // complete_len:    complete length of frame
      IRMP16_STOP_BIT,                                                    // stop_bit:        flag: frame has stop bit
      IRMP16_LSB,                                                         // lsb_first:       flag: LSB first
      IRMP16_FLAGS                                                        // flags:           some flags
  };

#endif

#if IRMP_SUPPORT_GREE_PROTOCOL == 1

   const PROGMEM IRMP_PARAMETER gree_param =
  {
      IRMP_GREE_PROTOCOL,                                               // protocol:        ir protocol
      GREE_PULSE_LEN_MIN,                                               // pulse_1_len_min: minimum length of pulse with bit value 1
      GREE_PULSE_LEN_MAX,                                               // pulse_1_len_max: maximum length of pulse with bit value 1
      GREE_1_PAUSE_LEN_MIN,                                             // pause_1_len_min: minimum length of pause with bit value 1
      GREE_1_PAUSE_LEN_MAX,                                             // pause_1_len_max: maximum length of pause with bit value 1
      GREE_PULSE_LEN_MIN,                                               // pulse_0_len_min: minimum length of pulse with bit value 0
      GREE_PULSE_LEN_MAX,                                               // pulse_0_len_max: maximum length of pulse with bit value 0
      GREE_0_PAUSE_LEN_MIN,                                             // pause_0_len_min: minimum length of pause with bit value 0
      GREE_0_PAUSE_LEN_MAX,                                             // pause_0_len_max: maximum length of pause with bit value 0
      GREE_ADDRESS_OFFSET,                                              // address_offset:  address offset
      GREE_ADDRESS_OFFSET + GREE_ADDRESS_LEN,                         // address_end:     end of address
      GREE_COMMAND_OFFSET,                                              // command_offset:  command offset
      GREE_COMMAND_OFFSET + GREE_COMMAND_LEN,                         // command_end:     end of command
      GREE_COMPLETE_DATA_LEN,                                           // complete_len:    complete length of frame
      GREE_STOP_BIT,                                                    // stop_bit:        flag: frame has stop bit
      GREE_LSB,                                                         // lsb_first:       flag: LSB first
      GREE_FLAGS                                                        // flags:           some flags
  };

#endif

#if IRMP_SUPPORT_THOMSON_PROTOCOL == 1

   const PROGMEM IRMP_PARAMETER thomson_param =
  {
      IRMP_THOMSON_PROTOCOL,                                              // protocol:        ir protocol
      THOMSON_PULSE_LEN_MIN,                                              // pulse_1_len_min: minimum length of pulse with bit value 1
      THOMSON_PULSE_LEN_MAX,                                              // pulse_1_len_max: maximum length of pulse with bit value 1
      THOMSON_1_PAUSE_LEN_MIN,                                            // pause_1_len_min: minimum length of pause with bit value 1
      THOMSON_1_PAUSE_LEN_MAX,                                            // pause_1_len_max: maximum length of pause with bit value 1
      THOMSON_PULSE_LEN_MIN,                                              // pulse_0_len_min: minimum length of pulse with bit value 0
      THOMSON_PULSE_LEN_MAX,                                              // pulse_0_len_max: maximum length of pulse with bit value 0
      THOMSON_0_PAUSE_LEN_MIN,                                            // pause_0_len_min: minimum length of pause with bit value 0
      THOMSON_0_PAUSE_LEN_MAX,                                            // pause_0_len_max: maximum length of pause with bit value 0
      THOMSON_ADDRESS_OFFSET,                                             // address_offset:  address offset
      THOMSON_ADDRESS_OFFSET + THOMSON_ADDRESS_LEN,                       // address_end:     end of address
      THOMSON_COMMAND_OFFSET,                                             // command_offset:  command offset
      THOMSON_COMMAND_OFFSET + THOMSON_COMMAND_LEN,                       // command_end:     end of command
      THOMSON_COMPLETE_DATA_LEN,                                          // complete_len:    complete length of frame
      THOMSON_STOP_BIT,                                                   // stop_bit:        flag: frame has stop bit
      THOMSON_LSB,                                                        // lsb_first:       flag: LSB first
      THOMSON_FLAGS                                                       // flags:           some flags
  };

#endif

#if IRMP_SUPPORT_BOSE_PROTOCOL == 1

   const PROGMEM IRMP_PARAMETER bose_param =
  {
      IRMP_BOSE_PROTOCOL,                                                 // protocol:        ir protocol
      BOSE_PULSE_LEN_MIN,                                                 // pulse_1_len_min: minimum length of pulse with bit value 1
      BOSE_PULSE_LEN_MAX,                                                 // pulse_1_len_max: maximum length of pulse with bit value 1
      BOSE_1_PAUSE_LEN_MIN,                                               // pause_1_len_min: minimum length of pause with bit value 1
      BOSE_1_PAUSE_LEN_MAX,                                               // pause_1_len_max: maximum length of pause with bit value 1
      BOSE_PULSE_LEN_MIN,                                                 // pulse_0_len_min: minimum length of pulse with bit value 0
      BOSE_PULSE_LEN_MAX,                                                 // pulse_0_len_max: maximum length of pulse with bit value 0
      BOSE_0_PAUSE_LEN_MIN,                                               // pause_0_len_min: minimum length of pause with bit value 0
      BOSE_0_PAUSE_LEN_MAX,                                               // pause_0_len_max: maximum length of pause with bit value 0
      BOSE_ADDRESS_OFFSET,                                                // address_offset:  address offset
      BOSE_ADDRESS_OFFSET + BOSE_ADDRESS_LEN,                             // address_end:     end of address
      BOSE_COMMAND_OFFSET,                                                // command_offset:  command offset
      BOSE_COMMAND_OFFSET + BOSE_COMMAND_LEN,                             // command_end:     end of command
      BOSE_COMPLETE_DATA_LEN,                                             // complete_len:    complete length of frame
      BOSE_STOP_BIT,                                                      // stop_bit:        flag: frame has stop bit
      BOSE_LSB,                                                           // lsb_first:       flag: LSB first
      BOSE_FLAGS                                                          // flags:           some flags
  };

#endif

#if IRMP_SUPPORT_A1TVBOX_PROTOCOL == 1

   const PROGMEM IRMP_PARAMETER a1tvbox_param =
  {
      IRMP_A1TVBOX_PROTOCOL,                                              // protocol:        ir protocol

      A1TVBOX_BIT_PULSE_LEN_MIN,                                          // pulse_1_len_min: here: minimum length of short pulse
      A1TVBOX_BIT_PULSE_LEN_MAX,                                          // pulse_1_len_max: here: maximum length of short pulse
      A1TVBOX_BIT_PAUSE_LEN_MIN,                                          // pause_1_len_min: here: minimum length of short pause
      A1TVBOX_BIT_PAUSE_LEN_MAX,                                          // pause_1_len_max: here: maximum length of short pause
      0,                                                                  // pulse_0_len_min: here: not used
      0,                                                                  // pulse_0_len_max: here: not used
      0,                                                                  // pause_0_len_min: here: not used
      0,                                                                  // pause_0_len_max: here: not used
      A1TVBOX_ADDRESS_OFFSET,                                             // address_offset:  address offset
      A1TVBOX_ADDRESS_OFFSET + A1TVBOX_ADDRESS_LEN,                       // address_end:     end of address
      A1TVBOX_COMMAND_OFFSET,                                             // command_offset:  command offset
      A1TVBOX_COMMAND_OFFSET + A1TVBOX_COMMAND_LEN,                       // command_end:     end of command
      A1TVBOX_COMPLETE_DATA_LEN,                                          // complete_len:    complete length of frame
      A1TVBOX_STOP_BIT,                                                   // stop_bit:        flag: frame has stop bit
      A1TVBOX_LSB,                                                        // lsb_first:       flag: LSB first
      A1TVBOX_FLAGS                                                       // flags:           some flags
  };

#endif

#if IRMP_SUPPORT_MERLIN_PROTOCOL == 1

   const PROGMEM IRMP_PARAMETER merlin_param =
  {
      IRMP_MERLIN_PROTOCOL,                                               // protocol:        ir protocol

      MERLIN_BIT_PULSE_LEN_MIN,                                           // pulse_1_len_min: here: minimum length of short pulse
      MERLIN_BIT_PULSE_LEN_MAX,                                           // pulse_1_len_max: here: maximum length of short pulse
      MERLIN_BIT_PAUSE_LEN_MIN,                                           // pause_1_len_min: here: minimum length of short pause
      MERLIN_BIT_PAUSE_LEN_MAX,                                           // pause_1_len_max: here: maximum length of short pause
      0,                                                                  // pulse_0_len_min: here: not used
      0,                                                                  // pulse_0_len_max: here: not used
      0,                                                                  // pause_0_len_min: here: not used
      0,                                                                  // pause_0_len_max: here: not used
      MERLIN_ADDRESS_OFFSET,                                              // address_offset:  address offset
      MERLIN_ADDRESS_OFFSET + MERLIN_ADDRESS_LEN,                         // address_end:     end of address
      MERLIN_COMMAND_OFFSET,                                              // command_offset:  command offset
      MERLIN_COMMAND_OFFSET + MERLIN_COMMAND_LEN,                         // command_end:     end of command
      MERLIN_COMPLETE_DATA_LEN,                                           // complete_len:    complete length of frame
      MERLIN_STOP_BIT,                                                    // stop_bit:        flag: frame has stop bit
      MERLIN_LSB,                                                         // lsb_first:       flag: LSB first
      MERLIN_FLAGS                                                        // flags:           some flags
  };

#endif

#if IRMP_SUPPORT_ORTEK_PROTOCOL == 1

   const PROGMEM IRMP_PARAMETER ortek_param =
  {
      IRMP_ORTEK_PROTOCOL,                                                // protocol:        ir protocol

      ORTEK_BIT_PULSE_LEN_MIN,                                            // pulse_1_len_min: here: minimum length of short pulse
      ORTEK_BIT_PULSE_LEN_MAX,                                            // pulse_1_len_max: here: maximum length of short pulse
      ORTEK_BIT_PAUSE_LEN_MIN,                                            // pause_1_len_min: here: minimum length of short pause
      ORTEK_BIT_PAUSE_LEN_MAX,                                            // pause_1_len_max: here: maximum length of short pause
      0,                                                                  // pulse_0_len_min: here: not used
      0,                                                                  // pulse_0_len_max: here: not used
      0,                                                                  // pause_0_len_min: here: not used
      0,                                                                  // pause_0_len_max: here: not used
      ORTEK_ADDRESS_OFFSET,                                               // address_offset:  address offset
      ORTEK_ADDRESS_OFFSET + ORTEK_ADDRESS_LEN,                           // address_end:     end of address
      ORTEK_COMMAND_OFFSET,                                               // command_offset:  command offset
      ORTEK_COMMAND_OFFSET + ORTEK_COMMAND_LEN,                           // command_end:     end of command
      ORTEK_COMPLETE_DATA_LEN,                                            // complete_len:    complete length of frame
      ORTEK_STOP_BIT,                                                     // stop_bit:        flag: frame has stop bit
      ORTEK_LSB,                                                          // lsb_first:       flag: LSB first
      ORTEK_FLAGS                                                         // flags:           some flags
  };

#endif

#if IRMP_SUPPORT_ROOMBA_PROTOCOL == 1

   const PROGMEM IRMP_PARAMETER roomba_param =
  {
      IRMP_ROOMBA_PROTOCOL,                                               // protocol:        ir protocol
      ROOMBA_1_PULSE_LEN_MIN,                                             // pulse_1_len_min: minimum length of pulse with bit value 1
      ROOMBA_1_PULSE_LEN_MAX,                                             // pulse_1_len_max: maximum length of pulse with bit value 1
      ROOMBA_1_PAUSE_LEN_MIN,                                             // pause_1_len_min: minimum length of pause with bit value 1
      ROOMBA_1_PAUSE_LEN_MAX,                                             // pause_1_len_max: maximum length of pause with bit value 1
      ROOMBA_0_PULSE_LEN_MIN,                                             // pulse_0_len_min: minimum length of pulse with bit value 0
      ROOMBA_0_PULSE_LEN_MAX,                                             // pulse_0_len_max: maximum length of pulse with bit value 0
      ROOMBA_0_PAUSE_LEN_MIN,                                             // pause_0_len_min: minimum length of pause with bit value 0
      ROOMBA_0_PAUSE_LEN_MAX,                                             // pause_0_len_max: maximum length of pause with bit value 0
      ROOMBA_ADDRESS_OFFSET,                                              // address_offset:  address offset
      ROOMBA_ADDRESS_OFFSET + ROOMBA_ADDRESS_LEN,                         // address_end:     end of address
      ROOMBA_COMMAND_OFFSET,                                              // command_offset:  command offset
      ROOMBA_COMMAND_OFFSET + ROOMBA_COMMAND_LEN,                         // command_end:     end of command
      ROOMBA_COMPLETE_DATA_LEN,                                           // complete_len:    complete length of frame
      ROOMBA_STOP_BIT,                                                    // stop_bit:        flag: frame has stop bit
      ROOMBA_LSB,                                                         // lsb_first:       flag: LSB first
      ROOMBA_FLAGS                                                        // flags:           some flags
  };

#endif

#if IRMP_SUPPORT_RCMM_PROTOCOL == 1

   const PROGMEM IRMP_PARAMETER rcmm_param =
  {
      IRMP_RCMM32_PROTOCOL,                                               // protocol:        ir protocol

      RCMM32_BIT_PULSE_LEN_MIN,                                           // pulse_1_len_min: here: minimum length of short pulse
      RCMM32_BIT_PULSE_LEN_MAX,                                           // pulse_1_len_max: here: maximum length of short pulse
      0,                                                                  // pause_1_len_min: here: minimum length of short pause
      0,                                                                  // pause_1_len_max: here: maximum length of short pause
      RCMM32_BIT_PULSE_LEN_MIN,                                           // pulse_0_len_min: here: not used
      RCMM32_BIT_PULSE_LEN_MAX,                                           // pulse_0_len_max: here: not used
      0,                                                                  // pause_0_len_min: here: not used
      0,                                                                  // pause_0_len_max: here: not used
      RCMM32_ADDRESS_OFFSET,                                              // address_offset:  address offset
      RCMM32_ADDRESS_OFFSET + RCMM32_ADDRESS_LEN,                         // address_end:     end of address
      RCMM32_COMMAND_OFFSET,                                              // command_offset:  command offset
      RCMM32_COMMAND_OFFSET + RCMM32_COMMAND_LEN,                         // command_end:     end of command
      RCMM32_COMPLETE_DATA_LEN,                                           // complete_len:    complete length of frame
      RCMM32_STOP_BIT,                                                    // stop_bit:        flag: frame has stop bit
      RCMM32_LSB,                                                         // lsb_first:       flag: LSB first
      RCMM32_FLAGS                                                        // flags:           some flags
  };

#endif

#if IRMP_SUPPORT_PENTAX_PROTOCOL == 1

   const PROGMEM IRMP_PARAMETER pentax_param =
  {
      IRMP_PENTAX_PROTOCOL,                                               // protocol:        ir protocol
      PENTAX_PULSE_LEN_MIN,                                               // pulse_1_len_min: minimum length of pulse with bit value 1
      PENTAX_PULSE_LEN_MAX,                                               // pulse_1_len_max: maximum length of pulse with bit value 1
      PENTAX_1_PAUSE_LEN_MIN,                                             // pause_1_len_min: minimum length of pause with bit value 1
      PENTAX_1_PAUSE_LEN_MAX,                                             // pause_1_len_max: maximum length of pause with bit value 1
      PENTAX_PULSE_LEN_MIN,                                               // pulse_0_len_min: minimum length of pulse with bit value 0
      PENTAX_PULSE_LEN_MAX,                                               // pulse_0_len_max: maximum length of pulse with bit value 0
      PENTAX_0_PAUSE_LEN_MIN,                                             // pause_0_len_min: minimum length of pause with bit value 0
      PENTAX_0_PAUSE_LEN_MAX,                                             // pause_0_len_max: maximum length of pause with bit value 0
      PENTAX_ADDRESS_OFFSET,                                              // address_offset:  address offset
      PENTAX_ADDRESS_OFFSET + PENTAX_ADDRESS_LEN,                         // address_end:     end of address
      PENTAX_COMMAND_OFFSET,                                              // command_offset:  command offset
      PENTAX_COMMAND_OFFSET + PENTAX_COMMAND_LEN,                         // command_end:     end of command
      PENTAX_COMPLETE_DATA_LEN,                                           // complete_len:    complete length of frame
      PENTAX_STOP_BIT,                                                    // stop_bit:        flag: frame has stop bit
      PENTAX_LSB,                                                         // lsb_first:       flag: LSB first
      PENTAX_FLAGS                                                        // flags:           some flags
  };

#endif

#if IRMP_SUPPORT_ACP24_PROTOCOL == 1

   const PROGMEM IRMP_PARAMETER acp24_param =
  {
      IRMP_ACP24_PROTOCOL,                                                // protocol:        ir protocol
      ACP24_PULSE_LEN_MIN,                                                // pulse_1_len_min: minimum length of pulse with bit value 1
      ACP24_PULSE_LEN_MAX,                                                // pulse_1_len_max: maximum length of pulse with bit value 1
      ACP24_1_PAUSE_LEN_MIN,                                              // pause_1_len_min: minimum length of pause with bit value 1
      ACP24_1_PAUSE_LEN_MAX,                                              // pause_1_len_max: maximum length of pause with bit value 1
      ACP24_PULSE_LEN_MIN,                                                // pulse_0_len_min: minimum length of pulse with bit value 0
      ACP24_PULSE_LEN_MAX,                                                // pulse_0_len_max: maximum length of pulse with bit value 0
      ACP24_0_PAUSE_LEN_MIN,                                              // pause_0_len_min: minimum length of pause with bit value 0
      ACP24_0_PAUSE_LEN_MAX,                                              // pause_0_len_max: maximum length of pause with bit value 0
      ACP24_ADDRESS_OFFSET,                                               // address_offset:  address offset
      ACP24_ADDRESS_OFFSET + ACP24_ADDRESS_LEN,                           // address_end:     end of address
      ACP24_COMMAND_OFFSET,                                               // command_offset:  command offset
      ACP24_COMMAND_OFFSET + ACP24_COMMAND_LEN,                           // command_end:     end of command
      ACP24_COMPLETE_DATA_LEN,                                            // complete_len:    complete length of frame
      ACP24_STOP_BIT,                                                     // stop_bit:        flag: frame has stop bit
      ACP24_LSB,                                                          // lsb_first:       flag: LSB first
      ACP24_FLAGS                                                         // flags:           some flags
  };

#endif

#if IRMP_SUPPORT_METZ_PROTOCOL == 1

   const PROGMEM IRMP_PARAMETER metz_param =
  {
      IRMP_METZ_PROTOCOL,                                                 // protocol:        ir protocol
      METZ_PULSE_LEN_MIN,                                                 // pulse_1_len_min: minimum length of pulse with bit value 1
      METZ_PULSE_LEN_MAX,                                                 // pulse_1_len_max: maximum length of pulse with bit value 1
      METZ_1_PAUSE_LEN_MIN,                                               // pause_1_len_min: minimum length of pause with bit value 1
      METZ_1_PAUSE_LEN_MAX,                                               // pause_1_len_max: maximum length of pause with bit value 1
      METZ_PULSE_LEN_MIN,                                                 // pulse_0_len_min: minimum length of pulse with bit value 0
      METZ_PULSE_LEN_MAX,                                                 // pulse_0_len_max: maximum length of pulse with bit value 0
      METZ_0_PAUSE_LEN_MIN,                                               // pause_0_len_min: minimum length of pause with bit value 0
      METZ_0_PAUSE_LEN_MAX,                                               // pause_0_len_max: maximum length of pause with bit value 0
      METZ_ADDRESS_OFFSET,                                                // address_offset:  address offset
      METZ_ADDRESS_OFFSET + METZ_ADDRESS_LEN,                             // address_end:     end of address
      METZ_COMMAND_OFFSET,                                                // command_offset:  command offset
      METZ_COMMAND_OFFSET + METZ_COMMAND_LEN,                             // command_end:     end of command
      METZ_COMPLETE_DATA_LEN,                                             // complete_len:    complete length of frame
      METZ_STOP_BIT,                                                      // stop_bit:        flag: frame has stop bit
      METZ_LSB,                                                           // lsb_first:       flag: LSB first
      METZ_FLAGS                                                          // flags:           some flags
  };

#endif

#if IRMP_SUPPORT_RADIO1_PROTOCOL == 1

   const PROGMEM IRMP_PARAMETER radio1_param =
  {
      IRMP_RADIO1_PROTOCOL,                                               // protocol:        ir protocol

      RADIO1_1_PULSE_LEN_MIN,                                             // pulse_1_len_min: minimum length of pulse with bit value 1
      RADIO1_1_PULSE_LEN_MAX,                                             // pulse_1_len_max: maximum length of pulse with bit value 1
      RADIO1_1_PAUSE_LEN_MIN,                                             // pause_1_len_min: minimum length of pause with bit value 1
      RADIO1_1_PAUSE_LEN_MAX,                                             // pause_1_len_max: maximum length of pause with bit value 1
      RADIO1_0_PULSE_LEN_MIN,                                             // pulse_0_len_min: minimum length of pulse with bit value 0
      RADIO1_0_PULSE_LEN_MAX,                                             // pulse_0_len_max: maximum length of pulse with bit value 0
      RADIO1_0_PAUSE_LEN_MIN,                                             // pause_0_len_min: minimum length of pause with bit value 0
      RADIO1_0_PAUSE_LEN_MAX,                                             // pause_0_len_max: maximum length of pause with bit value 0
      RADIO1_ADDRESS_OFFSET,                                              // address_offset:  address offset
      RADIO1_ADDRESS_OFFSET + RADIO1_ADDRESS_LEN,                         // address_end:     end of address
      RADIO1_COMMAND_OFFSET,                                              // command_offset:  command offset
      RADIO1_COMMAND_OFFSET + RADIO1_COMMAND_LEN,                         // command_end:     end of command
      RADIO1_COMPLETE_DATA_LEN,                                           // complete_len:    complete length of frame
      RADIO1_STOP_BIT,                                                    // stop_bit:        flag: frame has stop bit
      RADIO1_LSB,                                                         // lsb_first:       flag: LSB first
      RADIO1_FLAGS                                                        // flags:           some flags
  };

#endif


