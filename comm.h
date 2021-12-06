/*
 * comm
 * Communications for the STN1110 Serial interface to the GM OBD2 PCM
 */
 
#ifndef comm_h
#define comm_h

#include "Arduino.h"
#include "io.h"
#include "screen.h"

const char * const DISP_DEVICE_DESCRIPT       = "AT @1";       // General
const char * const DISP_DEVICE_ID             = "AT @2";       // General
const char * const STORE_DEVICE_ID            = "AT @3 %s";    // General
const char * const REPEAT_LAST_COMMAND        = "AT \r";       // General
const char * const ALLOW_LONG_MESSAGES        = "AT AL";       // General
const char * const LINEFEEDS_OFF              = "AT L0";       // General
const char * const LINEFEEDS_ON               = "AT L1";       // General
const char * const LOW_POWER_MODE             = "AT LP";       // General
const char * const MEMORY_OFF                 = "AT M0";       // General
const char * const MEMORY_ON                  = "AT M1";       // General
const char * const READ_STORED_DATA           = "AT RD";       // General
const char * const STORE_DATA_BYTE            = "AT SD ";      // General
const char * const WARM_START                 = "AT WS";       // General
const char * const RESET_ALL                  = "AT Z";        // General
const char * const TRY_BAUD_DIVISOR           = "AT BRD %02d"; // General
const char * const SET_HANDSHAKE_TIMEOUT      = "AT BRT %02d"; // General
const char * const SET_ALL_TO_DEFAULTS        = "AT D";        // General
const char * const ECHO_OFF                   = "AT E0";       // General
const char * const ECHO_ON                    = "AT E1";       // General
const char * const FORGE_EVENTS               = "AT FE";       // General
const char * const DISP_ID                    = "AT I";        // General
const char * const AUTOMATIC_RECEIVE          = "AT AR";       // OBD
const char * const ADAPTIVE_TIMING_OFF        = "AT AT0";      // OBD
const char * const ADAPTIVE_TIMING_AUTO_1     = "AT AT1";      // OBD
const char * const ADAPTIVE_TIMING_AUTO_2     = "AT AT2";      // OBD
const char * const DUMP_BUFFER                = "AT BD";       // OBD
const char * const BYPASS_INIT_SEQUENCE       = "AT BI";       // OBD
const char * const DISP_CURRENT_PROTOCOL      = "AT DP";       // OBD
const char * const DISP_CURRENT_PROTOCOL_NUM  = "AT DPN";      // OBD
const char * const HEADERS_OFF                = "AT H0";       // OBD
const char * const HEADERS_ON                 = "AT H1";       // OBD
const char * const MONITOR_ALL                = "AT MA";       // OBD
const char * const MONITOR_FOR_RECEIVER       = "AT MR %02d";  // OBD
const char * const MONITOR_FOR_TRANSMITTER    = "AT MT %02d";  // OBD
const char * const NORMAL_LENGTH_MESSAGES     = "AT NL";       // OBD
const char * const SET_PROTO_OPTIONS_AND_BAUD = "AT PB %s";    // OBD
const char * const PROTOCOL_CLOSE             = "AT PC";       // OBD
const char * const RESPONSES_OFF              = "AT R0";       // OBD
const char * const RESPONSES_ON               = "AT R1";       // OBD
const char * const SET_RECEIVE_ADDRESS_TO     = "AT RA %02d";  // OBD
const char * const PRINTING_SPACES_OFF        = "AT S0";       // OBD
const char * const PRINTING_SPACES_ON         = "AT S1";       // OBD
const char * const SET_HEADER                 = "AT SH %s";    // OBD
const char * const SET_PROTOCOL_TO_AUTO_H_SAVE = "AT SP A%c";  // OBD
const char * const SET_PROTOCOL_TO_H_SAVE     = "AT SP %c";    // OBD
const char * const SET_PROTOCOL_TO_AUTO_SAVE  = "AT SP 00";    // OBD
const char * const SET_REC_ADDRESS            = "AT SR %02d";  // OBD
const char * const SET_STANDARD_SEARCH_ORDER  = "AT SS";       // OBD
const char * const SET_TIMEOUT_TO_H_X_4MS     = "AT ST %02d";  // OBD
const char * const SET_TESTER_ADDRESS_TO      = "AT TA %02d";  // OBD
const char * const TRY_PROT_H_AUTO_SEARCH     = "AT TP A%c";   // OBD
const char * const TRY_PROT_H                 = "AT TP %c";    // OBD
const char * const ALL_PROG_PARAMS_OFF        = "AT PP FF OFF";// PPs
const char * const ALL_PROG_PARAMS_ON         = "AT PP FF ON"; // PPs
const char * const SET_PROG_PARAM_OFF         = "AT PP %s OFF";// PPs
const char * const SET_PROG_PARAM_ON          = "AT PP %s ON"; // PPs
const char * const SET_PROG_PARAM_VAL         = "AT PP %s SV %s"; // PPs
const char * const DISP_PP_SUMMARY            = "AT PPS";      // PPs
const char * const READ_VOLTAGE               = "AT RV";       // Volts
const char * const CALIBRATE_VOLTAGE_CUSTOM   = "AT CV %04d";  // Volts
const char * const RESTORE_CV_TO_FACTORY      = "AT CV 0000";  // Volts
const char * const REQUEST_HEADER     = "ATSH6C10F1";   // Stage header for PIDs
const char * const GET_VIN1           = "3C01";         // VIN Part 1
const char * const GET_VIN2           = "3C02";         // VIN Part 2
const char * const GET_VIN3           = "3C03";         // VIN Part 3
const char * const REQUEST_KEEPALIVE  = "3F";           // Tell PCM to keep report data
const char * const GET_OSID           = "3C0A";         // PCM OSID #
const char * const SET_VIN1           = "3B0100";       // VIN Part 1 + VIN 1 HEX DATA
const char * const SET_VIN2           = "3B02";         // VIN Part 2 + VIN 2 HEX DATA
const char * const SET_VIN3           = "3B03";         // VIN Part 3 + VIN 3 HEX DATA
const char * const GET_HW             = "3C04";         // Get PCM HW ID
const char * const LASTBLOCK_FE       = "2A14FE000000"; // FE
const char * const LASTBLOCK_FEFD     = "2A14FEFD0000"; // FE FD
const char * const LASTBLOCK_FEFDFC   = "2A14FEFDFC00"; // FE FD FC
const char * const LASTBLOCK_FEFDFCFB = "2A14FEFDFCFB"; // FE FD FC FB
const char * const LASTBLOCK_FA       = "2A14FA000000"; // FA
const char * const LASTBLOCK_FAF9     = "2A14FAF90000"; // FE F9
const char * const LASTBLOCK_FAF9F8   = "2A14FAF9F800"; // FE F9 F8
const char * const LASTBLOCK_FAF9F8F7 = "2A14FAF9F8F7"; // FE F9 F8 F7
const char * const REQUEST_PID        = "2C %s %s %s FF FF"; // PID request - LastBlock ID / Position / PID
const char * const REQUEST_TEST_PID   = "01 00";

struct Tdeviceinfo {
  String STDI; // Device hardware ID
  String STDICES; // Engine start count
  String STDICPO; // Power on Reset count
  String STI; // Firmware ID
  String STIX; // Extended firmware ID
  String STMFR; // device mfg id 
  String STSN; // device serial #
  String STPRS; // current protocol
};

void serial_flush(void);
void initSTNScanner();
bool isOK(String value);
bool isSTOPPED(String value);
bool isGOOD(String value, String checkstr, int len);
bool initSTN(bool withHeader);
String getVIN();
String getOSID();
String getVOLTS();
String getPCMHW();

String send(String cmd, int D);
String send2(String cmd, bool ignore);
void send3(String cmd);
void send4(String cmd, int D);

struct Tdeviceinfo getDeviceInfo();

#endif
