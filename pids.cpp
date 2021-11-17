/*
   pids
   Paramater ID (PID) Structures
*/

#include "pids.h"

// Push the PID Data to extended RAM
// This keeps regular ram for the Teensy device open.

EXTMEM TPID PIDS[NUM_PIDS] = {
  {
    ._name = "ENGINE SPEED", 
    ._shortname = "RPM", 
    ._formula = "((N1 << 8) +N2) *0.25", 
    ._unit = "RPM", 
    ._len = 2, 
    ._PID = "000C", 
    ._format = "", 
    ._mci = "%RPM%", 
    ._selected = false, 
    ._value = "", 
    ._fake = false, 
    ._duplicate = false, 
    ._dupeIndex = -1, 
    ._CMD = "", 
    ._guid = "8aab80aa-86bc-4845-a093-78ffb2ad16c6"
  }, {
    ._name = "Injector PW",
    ._shortname = "Injector PW",
    ._formula = "(((N1<<8)+N2)/65.535)",
    ._unit = "ms",
    ._len = 2,
    ._PID = "1193",
    ._format = "%f",
    ._mci = "%IPW%",
    ._selected = false,
    ._value = "",
    ._fake = false,
    ._duplicate = false,
    ._dupeIndex = -1,
    ._CMD = "",
    ._guid = "bf2a5b80-9a55-4583-80a5-9342683fc1da"
  }, {
    ._name = "ECT (ENGINE COOLANT TEMPERATURE)",
    ._shortname = "ECT",
    ._formula = "N0-40",
    ._unit = "ºC",
    ._len = 1,
    ._PID = "0005",
    ._format = "",
    ._mci = "%ECT%",
    ._selected = false,
    ._value = "",
    ._fake = false,
    ._duplicate = false,
    ._dupeIndex = -1,
    ._CMD = "",
    ._guid = "8c34e085-9aa5-4b2e-a1c1-b905c2a962d4"
  }, {
    ._name = "MASS AIR FLOW RAW INPUT FREQUENCY",
    ._shortname = "MAF",
    ._formula = "((N1 << 8) + N2) / 2.048",
    ._unit = "Hz",
    ._len = 2,
    ._PID = "1250",
    ._format = "%f",
    ._mci = "%MAF%",
    ._selected = false,
    ._value = "",
    ._fake = false,
    ._duplicate = false,
    ._dupeIndex = -1,
    ._CMD = "",
    ._guid = "ffbb3e60-5694-497a-8e76-3c97993b2f9d"
  }, {
    ._name = "SHORT TERM FUEL TRIM BANK 1",
    ._shortname = "STFT",
    ._formula = "(N0-128)/1.28",
    ._unit = "%",
    ._len = 1,
    ._PID = "0006",
    ._format = "%f",
    ._mci = "%STF%",
    ._selected = false,
    ._value = "",
    ._fake = false,
    ._duplicate = false,
    ._dupeIndex = -1,
    ._CMD = "",
    ._guid = "a7ae6e3e-34ed-48da-8031-38686d3bb2ed"
  }, {
    ._name = "LONG TERM FUEL TRIM BANK 1",
    ._shortname = "LTFT",
    ._formula = "(N0-128)/1.28",
    ._unit = "%",
    ._len = 1,
    ._PID = "0007",
    ._format = "%f",
    ._mci = "%LTF%",
    ._selected = false,
    ._value = "",
    ._fake = false,
    ._duplicate = false,
    ._dupeIndex = -1,
    ._CMD = "",
    ._guid = "8f28352c-6902-4520-a2b0-c6094977543d"
  }, {
    ._name = "MAP (kPa)",
    ._shortname = "MAP(kPa)",
    ._formula = "N0",
    ._unit = "kPa",
    ._len = 1,
    ._PID = "000B",
    ._format = "",
    ._mci = "%MAP%",
    ._selected = false,
    ._value = "",
    ._fake = false,
    ._duplicate = false,
    ._dupeIndex = -1,
    ._CMD = "",
    ._guid = "e15cc0ae-f8e3-44b9-9546-dd93bbdb9d7e"
  }, {
    ._name = "VEHICLE SPEED",
    ._shortname = "MPH",
    ._formula = "N0/1.609",
    ._unit = "MPH",
    ._len = 1,
    ._PID = "000D",
    ._format = "%f",
    ._mci = "%MPH%",
    ._selected = false,
    ._value = "",
    ._fake = false,
    ._duplicate = false,
    ._dupeIndex = -1,
    ._CMD = "",
    ._guid = "2eb011bb-2e13-475c-8ba4-e1aa632cb602"
  }, {
    ._name = "SPARK ADVANCE",
    ._shortname = "Spark",
    ._formula = "((N0/2) - 64) *",
    ._unit = "Degrees",
    ._len = 1,
    ._PID = "000E",
    ._format = "",
    ._mci = "%SPK%",
    ._selected = false,
    ._value = "",
    ._fake = false,
    ._duplicate = false,
    ._dupeIndex = -1,
    ._CMD = "",
    ._guid = "c3cb7b54-b469-4a91-8108-75ea36793ca4"
  }, {
    ._name = "INTAKE AIR TEMPERATURE",
    ._shortname = "IAT",
    ._formula = "N0-40",
    ._unit = "ºC",
    ._len = 1,
    ._PID = "000F",
    ._format = "",
    ._mci = "%IAT%",
    ._selected = false,
    ._value = "",
    ._fake = false,
    ._duplicate = false,
    ._dupeIndex = -1,
    ._CMD = "",
    ._guid = "01fa99de-b9b9-4d3e-9917-84b33eeb9f52"
  }, {
    ._name = "TP Angle %",
    ._shortname = "TP %",
    ._formula = "N0/2.55",
    ._unit = "%",
    ._len = 1,
    ._PID = "0011",
    ._format = "",
    ._mci = "%TPS%",
    ._selected = false,
    ._value = "",
    ._fake = false,
    ._duplicate = false,
    ._dupeIndex = -1,
    ._CMD = "",
    ._guid = "59d2572d-deca-4ef9-8cc5-ba4e86084eb8"
  }, {
    ._name = "Ignition 1 Voltage",
    ._shortname = "IGN V",
    ._formula = "N0/10",
    ._unit = "V",
    ._len = 1,
    ._PID = "1141",
    ._format = "",
    ._mci = "%IGV%",
    ._selected = false,
    ._value = "",
    ._fake = false,
    ._duplicate = false,
    ._dupeIndex = -1,
    ._CMD = "",
    ._guid = "c014ff51-cd13-4f8b-8649-5a3fff42967b"
  }, {
    ._name = "H02S Sensor 1",
    ._shortname = "O2",
    ._formula = "0.434*N0*10",
    ._unit = "mV",
    ._len = 1,
    ._PID = "1145",
    ._format = "",
    ._mci = "%HO1%",
    ._selected = false,
    ._value = "",
    ._fake = false,
    ._duplicate = false,
    ._dupeIndex = -1,
    ._CMD = "",
    ._guid = "adcaf210-fa13-484a-b75d-ea23fc5384db"
  }, {
    ._name = "Knock Retard",
    ._shortname = "KR",
    ._formula = "22.5*N0/256",
    ._unit = "Degrees",
    ._len = 1,
    ._PID = "11A6",
    ._format = "",
    ._mci = "%KRS%",
    ._selected = false,
    ._value = "",
    ._fake = false,
    ._duplicate = false,
    ._dupeIndex = -1,
    ._CMD = "",
    ._guid = "9fc93aab-6728-436c-bf86-21b67bbaa280"
  }, {
    ._name = "Current Gear",
    ._shortname = "Gear",
    ._formula = "N0",
    ._unit = "",
    ._len = 1,
    ._PID = "199A",
    ._format = "",
    ._mci = "%CGS%",
    ._selected = false,
    ._value = "",
    ._fake = false,
    ._duplicate = false,
    ._dupeIndex = -1,
    ._CMD = "",
    ._guid = "f332b968-6e48-45ae-8ddb-42a980937476"
  }, {
    ._name = "Misfire Cyl. 6 History",
    ._shortname = "Misfire Cyl. 6 History",
    ._formula = "(N1 << 8) + N2",
    ._unit = "Count",
    ._len = 2,
    ._PID = "11F9",
    ._format = "",
    ._mci = "%MH6%",
    ._selected = false,
    ._value = "",
    ._fake = false,
    ._duplicate = false,
    ._dupeIndex = -1,
    ._CMD = "",
    ._guid = "fc690c1a-bf1c-4257-b1fe-7ff84ae634c4"
  }, {
    ._name = "Misfire Cyl. 6 Current",
    ._shortname = "Misfire Cyl. 6 Current",
    ._formula = "N0",
    ._unit = "Count",
    ._len = 1,
    ._PID = "11EB",
    ._format = "",
    ._mci = "%MC6%",
    ._selected = false,
    ._value = "",
    ._fake = false,
    ._duplicate = false,
    ._dupeIndex = -1,
    ._CMD = "",
    ._guid = "c4883231-98ce-48d4-9b5c-ef7c7f5d8f2f"
  }, {
    ._name = "Misfire Cyl. 5 History",
    ._shortname = "Misfire Cyl. 5 History",
    ._formula = "(N1 << 8) + N2",
    ._unit = "Count",
    ._len = 2,
    ._PID = "11F8",
    ._format = "",
    ._mci = "%MH5%",
    ._selected = false,
    ._value = "",
    ._fake = false,
    ._duplicate = false,
    ._dupeIndex = -1,
    ._CMD = "",
    ._guid = "daebe262-e160-47b3-a701-50508c714e73"
  }, {
    ._name = "Misfire Cyl. 5 Current",
    ._shortname = "Misfire Cyl. 5 Current",
    ._formula = "N0",
    ._unit = "Count",
    ._len = 1,
    ._PID = "11EA",
    ._format = "",
    ._mci = "%MC5%",
    ._selected = false,
    ._value = "",
    ._fake = false,
    ._duplicate = false,
    ._dupeIndex = -1,
    ._CMD = "",
    ._guid = "c031f279-9da7-4127-a91b-5f7676b79ef5"
  }, {
    ._name = "Misfire Cyl. 4 History",
    ._shortname = "Misfire Cyl. 4 History",
    ._formula = "(N1 << 8) + N2",
    ._unit = "Count",
    ._len = 2,
    ._PID = "1204",
    ._format = "",
    ._mci = "%MH4%",
    ._selected = false,
    ._value = "",
    ._fake = false,
    ._duplicate = false,
    ._dupeIndex = -1,
    ._CMD = "",
    ._guid = "2652dceb-f799-4f23-96a6-372a63a523c0"
  }, {
    ._name = "Misfire Cyl. 4 Current",
    ._shortname = "Misfire Cyl. 4 Current",
    ._formula = "N0",
    ._unit = "Count",
    ._len = 1,
    ._PID = "1208",
    ._format = "",
    ._mci = "%MC4%",
    ._selected = false,
    ._value = "",
    ._fake = false,
    ._duplicate = false,
    ._dupeIndex = -1,
    ._CMD = "",
    ._guid = "a55067cc-279a-4537-a911-2178a88dff6c"
  }, {
    ._name = "Misfire Cyl. 3 History",
    ._shortname = "Misfire Cyl. 3 History",
    ._formula = "(N1 << 8) + N2",
    ._unit = "Count",
    ._len = 2,
    ._PID = "1203",
    ._format = "",
    ._mci = "%MH3%",
    ._selected = false,
    ._value = "",
    ._fake = false,
    ._duplicate = false,
    ._dupeIndex = -1,
    ._CMD = "",
    ._guid = "7b4b138c-6c24-4bde-9b55-06f686cd111e"
  }, {
    ._name = "Misfire Cyl. 3 Current",
    ._shortname = "Misfire Cyl. 3 Current",
    ._formula = "N0",
    ._unit = "Count",
    ._len = 1,
    ._PID = "1207",
    ._format = "",
    ._mci = "%MC3%",
    ._selected = false,
    ._value = "",
    ._fake = false,
    ._duplicate = false,
    ._dupeIndex = -1,
    ._CMD = "",
    ._guid = "061a4d5d-89d1-4d46-8c58-b2cc704a5ba0"
  }, {
    ._name = "Misfire Cyl. 2 History",
    ._shortname = "Misfire Cyl. 2 History",
    ._formula = "(N1 << 8) + N2",
    ._unit = "Count",
    ._len = 2,
    ._PID = "1202",
    ._format = "",
    ._mci = "%MH2%",
    ._selected = false,
    ._value = "",
    ._fake = false,
    ._duplicate = false,
    ._dupeIndex = -1,
    ._CMD = "",
    ._guid = "ac38524e-ecb8-467e-a44d-f98fc5b90549"
  }, {
    ._name = "Misfire Cyl. 2 Current",
    ._shortname = "Misfire Cyl. 2 Current",
    ._formula = "N0",
    ._unit = "Count",
    ._len = 1,
    ._PID = "1205",
    ._format = "",
    ._mci = "%MC2%",
    ._selected = false,
    ._value = "",
    ._fake = false,
    ._duplicate = false,
    ._dupeIndex = -1,
    ._CMD = "",
    ._guid = "32184d23-901b-41b6-950b-023a2ec83cab"
  }, {
    ._name = "Misfire Cyl. 1 History",
    ._shortname = "Misfire Cyl. 1 History",
    ._formula = "(N1 << 8) + N2",
    ._unit = "Count",
    ._len = 2,
    ._PID = "1201",
    ._format = "",
    ._mci = "%MH1%",
    ._selected = false,
    ._value = "",
    ._fake = false,
    ._duplicate = false,
    ._dupeIndex = -1,
    ._CMD = "",
    ._guid = "170196a6-467f-4dca-bd64-d2930b6d2f47"
  }, {
    ._name = "Misfire Cyl. 1 Current",
    ._shortname = "Misfire Cyl. 1 Current",
    ._formula = "N0",
    ._unit = "Count",
    ._len = 1,
    ._PID = "1206",
    ._format = "",
    ._mci = "%MC1%",
    ._selected = false,
    ._value = "",
    ._fake = false,
    ._duplicate = false,
    ._dupeIndex = -1,
    ._CMD = "",
    ._guid = "ca73abd9-5f13-4302-8323-693444374900"
  }, {
    ._name = "Fuel Trim Cell",
    ._shortname = "FT Cell",
    ._formula = "N0",
    ._unit = "",
    ._len = 1,
    ._PID = "1190",
    ._format = "",
    ._mci = "%FTC%",
    ._selected = false,
    ._value = "",
    ._fake = false,
    ._duplicate = false,
    ._dupeIndex = -1,
    ._CMD = "",
    ._guid = "46fb70be-acda-432a-972f-b025e88215d6"
  }, {
    ._name = "MAF Flow Rate",
    ._shortname = "MAF(g/s)",
    ._formula = "((N1 << 8) + N2)  / 100",
    ._unit = "g/s",
    ._len = 2,
    ._PID = "0010",
    ._format = "",
    ._mci = "%MAFGmPerSec%",
    ._selected = false,
    ._value = "",
    ._fake = false,
    ._duplicate = false,
    ._dupeIndex = -1,
    ._CMD = "",
    ._guid = "70f4a51d-2a15-4304-8b77-24f88d0a5c02"
  }, {
    ._name = "AFR (Commanded)",
    ._shortname = "AFR",
    ._formula = "N0 / 10",
    ._unit = ":1",
    ._len = 1,
    ._PID = "119E",
    ._format = "",
    ._mci = "%AFRCommanded%",
    ._selected = false,
    ._value = "",
    ._fake = false,
    ._duplicate = false,
    ._dupeIndex = -1,
    ._CMD = "",
    ._guid = "9434baad-40f3-4065-ba1f-1c18f22d5868"
  }, {
    ._name = "Last Shift Time",
    ._shortname = "Shift Time",
    ._formula = "N0 / 40",
    ._unit = "Seconds",
    ._len = 1,
    ._PID = "1992",
    ._format = "",
    ._mci = "%LST%",
    ._selected = false,
    ._value = "",
    ._fake = false,
    ._duplicate = false,
    ._dupeIndex = -1,
    ._CMD = "",
    ._guid = "ba26df82-1b29-4e90-9d1e-031624790c4e"
  }, {
    ._name = "1-2 Shift Time",
    ._shortname = "1-2 Time",
    ._formula = "N0 / 40",
    ._unit = "Seconds",
    ._len = 1,
    ._PID = "1993",
    ._format = "",
    ._mci = "%ST12%",
    ._selected = false,
    ._value = "",
    ._fake = false,
    ._duplicate = false,
    ._dupeIndex = -1,
    ._CMD = "",
    ._guid = "def6d735-28a9-4a08-8f88-8fd0f8a3aa16"
  }, {
    ._name = "2-3 Shift Time",
    ._shortname = "2-3 Time",
    ._formula = "N0 / 40",
    ._unit = "Seconds",
    ._len = 1,
    ._PID = "1994",
    ._format = "",
    ._mci = "%ST23%",
    ._selected = false,
    ._value = "",
    ._fake = false,
    ._duplicate = false,
    ._dupeIndex = -1,
    ._CMD = "",
    ._guid = "7efc4f28-90e7-4681-adbb-261554fe5ff7"
  }, {
    ._name = "3-4 Shift Time",
    ._shortname = "3-4 Time",
    ._formula = "N0 / 40",
    ._unit = "Seconds",
    ._len = 1,
    ._PID = "1995",
    ._format = "",
    ._mci = "%ST34%",
    ._selected = false,
    ._value = "",
    ._fake = false,
    ._duplicate = false,
    ._dupeIndex = -1,
    ._CMD = "",
    ._guid = "6e72a4d6-c54d-46cb-9b5c-7b9f4ca65edd"
  }, {
    ._name = "1-2 Shift Error",
    ._shortname = "1-2 Error",
    ._formula = "N0 / 40",
    ._unit = "Seconds",
    ._len = 1,
    ._PID = "1997",
    ._format = "",
    ._mci = "%SE12%",
    ._selected = false,
    ._value = "",
    ._fake = false,
    ._duplicate = false,
    ._dupeIndex = -1,
    ._CMD = "",
    ._guid = "ebce1f27-e727-495f-8244-ee9a00d89aef"
  }, {
    ._name = "2-3 Shift Error",
    ._shortname = "2-3 Error",
    ._formula = "N0 / 40",
    ._unit = "Seconds",
    ._len = 1,
    ._PID = "1998",
    ._format = "",
    ._mci = "%SE23%",
    ._selected = false,
    ._value = "",
    ._fake = false,
    ._duplicate = false,
    ._dupeIndex = -1,
    ._CMD = "",
    ._guid = "848956fb-d823-421b-8293-3489ef9e1c3e"
  }, {
    ._name = "3-4 Shift Error",
    ._shortname = "3-4 Error",
    ._formula = "N0 / 40",
    ._unit = "Seconds",
    ._len = 1,
    ._PID = "1999",
    ._format = "",
    ._mci = "%SE34%",
    ._selected = false,
    ._value = "",
    ._fake = false,
    ._duplicate = false,
    ._dupeIndex = -1,
    ._CMD = "",
    ._guid = "042e1930-52c3-429a-a591-0de561fb045d"
  }, {
    ._name = "Fuel Loop Status",
    ._shortname = "Loop",
    ._formula = "((N0 >> 3) & 1)",
    ._unit = "",
    ._len = 1,
    ._PID = "1105",
    ._format = "",
    ._mci = "%FuelLoopStatus%",
    ._selected = false,
    ._value = "",
    ._fake = false,
    ._duplicate = false,
    ._dupeIndex = -1,
    ._CMD = "",
    ._guid = "3306c7f1-0764-472e-b4dc-e4c5308c919a"
  }, {
    ._name = "Perf Shift Mode",
    ._shortname = "Perf Shift",
    ._formula = "((N0 >> 2) & 1)",
    ._unit = "",
    ._len = 1,
    ._PID = "110C",
    ._format = "%o",
    ._mci = "%BitShiftMode%",
    ._selected = false,
    ._value = "",
    ._fake = false,
    ._duplicate = false,
    ._dupeIndex = -1,
    ._CMD = "",
    ._guid = "f8132555-7f06-4592-8f80-db3e3db11ceb"
  }, {
    ._name = "Desired Idle Speed",
    ._shortname = "Desired Idle",
    ._formula = "N0 * 12.5",
    ._unit = "RPM",
    ._len = 1,
    ._PID = "1192",
    ._format = "",
    ._mci = "%DesiredIdle%",
    ._selected = false,
    ._value = "",
    ._fake = false,
    ._duplicate = false,
    ._dupeIndex = -1,
    ._CMD = "",
    ._guid = "adc672e0-0c84-45d6-8d3c-f7da6e137529"
  }, {
    ._name = "IAC Position",
    ._shortname = "IAC Position",
    ._formula = "N0",
    ._unit = "",
    ._len = 1,
    ._PID = "1172",
    ._format = "",
    ._mci = "%IACCounts%",
    ._selected = false,
    ._value = "",
    ._fake = false,
    ._duplicate = false,
    ._dupeIndex = -1,
    ._CMD = "",
    ._guid = "442e8f0b-3070-4ca4-983b-e1219078ec55"
  }, {
    ._name = "Power Enrichment Mode",
    ._shortname = "PE Mode",
    ._formula = "((N0 >> 2) & 1)",
    ._unit = "",
    ._len = 1,
    ._PID = "1106",
    ._format = "%o",
    ._mci = "%BitPEMode%",
    ._selected = false,
    ._value = "",
    ._fake = false,
    ._duplicate = false,
    ._dupeIndex = -1,
    ._CMD = "",
    ._guid = "0d17a501-6034-4948-ac8a-d10ec889b4a1"
  }, {
    ._name = "Decel Fuel Mode",
    ._shortname = "DFCO Mode",
    ._formula = "((N0 >> 3) & 1)",
    ._unit = "",
    ._len = 1,
    ._PID = "1106",
    ._format = "%o",
    ._mci = "%BitDFCOMode%",
    ._selected = false,
    ._value = "",
    ._fake = false,
    ._duplicate = false,
    ._dupeIndex = -1,
    ._CMD = "",
    ._guid = "aff05d96-9f95-45db-ab3b-0c9071b71561"
  }, {
    ._name = "Transmission ISS",
    ._shortname = "ISS Speed",
    ._formula = "((N1 << 8) + N2) * 0.125",
    ._unit = "RPM",
    ._len = 2,
    ._PID = "1941",
    ._format = "",
    ._mci = "",
    ._selected = false,
    ._value = "",
    ._fake = false,
    ._duplicate = false,
    ._dupeIndex = -1,
    ._CMD = "",
    ._guid = "c88d4440-1868-4ed6-8f93-33d5f414d0e1"
  }, {
    ._name = "Transmission OSS",
    ._shortname = "OSS Speed",
    ._formula = "((N1 << 8) + N2) * 0.125",
    ._unit = "RPM",
    ._len = 2,
    ._PID = "1942",
    ._format = "",
    ._mci = "",
    ._selected = false,
    ._value = "",
    ._fake = false,
    ._duplicate = false,
    ._dupeIndex = -1,
    ._CMD = "",
    ._guid = "fd324323-84f7-485a-842d-bcb7965a64e0"
  }, {
    ._name = "TCC Slip Speed",
    ._shortname = "TCC Slip RPM",
    ._formula = "((N1 << 8) + N2) * 0.125",
    ._unit = "RPM",
    ._len = 2,
    ._PID = "1991",
    ._format = "",
    ._mci = "",
    ._selected = false,
    ._value = "",
    ._fake = false,
    ._duplicate = false,
    ._dupeIndex = -1,
    ._CMD = "",
    ._guid = "e7c620e8-7248-4c42-a63b-f87428e9bf89"
  }, {
    ._name = "Transmission Fluid Temp",
    ._shortname = "Trans Temp",
    ._formula = "N0 - 40",
    ._unit = "ºC",
    ._len = 1,
    ._PID = "1940",
    ._format = "",
    ._mci = "",
    ._selected = false,
    ._value = "",
    ._fake = false,
    ._duplicate = false,
    ._dupeIndex = -1,
    ._CMD = "",
    ._guid = "cfac07e0-f4ee-4df7-ae28-98098c86b71b"
  }, {
    ._name = "TCC Duty Cycle",
    ._shortname = "TCC %",
    ._formula = "N0 / 2.55",
    ._unit = "%",
    ._len = 1,
    ._PID = "1970",
    ._format = "",
    ._mci = "",
    ._selected = false,
    ._value = "",
    ._fake = false,
    ._duplicate = false,
    ._dupeIndex = -1,
    ._CMD = "",
    ._guid = "c5adba8c-9aec-48ff-9485-73892774731e"
  }, {
    ._name = "PC Solenoid Duty Cycle",
    ._shortname = "PC %",
    ._formula = "N0 / 2.55",
    ._unit = "%",
    ._len = 1,
    ._PID = "1972",
    ._format = "",
    ._mci = "",
    ._selected = false,
    ._value = "",
    ._fake = false,
    ._duplicate = false,
    ._dupeIndex = -1,
    ._CMD = "",
    ._guid = "52f59431-067e-48b0-9fe9-c9e6070e1e14"
  }, {
    ._name = "PC Solenoid Actual Current",
    ._shortname = "PC Sol Amp",
    ._formula = "N0 * 0.0195",
    ._unit = "Amps",
    ._len = 1,
    ._PID = "199E",
    ._format = "",
    ._mci = "",
    ._selected = false,
    ._value = "",
    ._fake = false,
    ._duplicate = false,
    ._dupeIndex = -1,
    ._CMD = "",
    ._guid = "84bd58d7-b5f6-42ed-804f-cd8c1d61e861"
  }, {
    ._name = "PC Solenoid Reference Current",
    ._shortname = "PC Sol Ref Amp",
    ._formula = "N0 * 0.0195",
    ._unit = "Amps",
    ._len = 1,
    ._PID = "199F",
    ._format = "",
    ._mci = "",
    ._selected = false,
    ._value = "",
    ._fake = false,
    ._duplicate = false,
    ._dupeIndex = -1,
    ._CMD = "",
    ._guid = "83a85b6a-0781-439d-9a0a-0d0f4c316c30"
  }, {
    ._name = "18X Crank Sensor",
    ._shortname = "18X Crank",
    ._formula = "1310720 / (((N1 << 8) + N2) * 6)",
    ._unit = "Pulses",
    ._len = 2,
    ._PID = "1256",
    ._format = "",
    ._mci = "",
    ._selected = false,
    ._value = "",
    ._fake = false,
    ._duplicate = false,
    ._dupeIndex = -1,
    ._CMD = "",
    ._guid = "8cad9bce-34a8-46c8-83f2-47b2be96d65b"
  }, {
    ._name = "3X Crank Sensor",
    ._shortname = "3X Crank",
    ._formula = "1310720 / ((N1 << 8) + N2)",
    ._unit = "Pulses",
    ._len = 2,
    ._PID = "124F",
    ._format = "",
    ._mci = "",
    ._selected = false,
    ._value = "",
    ._fake = false,
    ._duplicate = false,
    ._dupeIndex = -1,
    ._CMD = "",
    ._guid = "0d9981d0-caee-4687-a26c-1fb7833892f6"
  }, {
    ._name = "Fans Low Speed",
    ._shortname = "Fans Low",
    ._formula = "((N0 >> 6) & 1)",
    ._unit = "",
    ._len = 1,
    ._PID = "1103",
    ._format = "%o",
    ._mci = "",
    ._selected = false,
    ._value = "",
    ._fake = false,
    ._duplicate = false,
    ._dupeIndex = -1,
    ._CMD = "",
    ._guid = "8bc78dde-9082-419e-a4d0-9b6049c7fc6a"
  }, {
    ._name = "Fans High Speed",
    ._shortname = "Fans High",
    ._formula = "((N0 >> 7) & 1)",
    ._unit = "",
    ._len = 1,
    ._PID = "1103",
    ._format = "%o",
    ._mci = "",
    ._selected = false,
    ._value = "",
    ._fake = false,
    ._duplicate = false,
    ._dupeIndex = -1,
    ._CMD = "",
    ._guid = "d8c0f558-10d8-47cb-ade4-17cf74560b2a"
  }, {
    ._name = "Gear Ratio",
    ._shortname = "Gear Ratio",
    ._formula = "N0 * 0.01563",
    ._unit = ":1",
    ._len = 1,
    ._PID = "19A1",
    ._format = "",
    ._mci = "",
    ._selected = false,
    ._value = "",
    ._fake = false,
    ._duplicate = false,
    ._dupeIndex = -1,
    ._CMD = "",
    ._guid = "7d32d171-4445-4512-8668-319fe6bdada1"
  }, {
    ._name = "SPARK ADVANCE (Alt)",
    ._shortname = "Spark",
    ._formula = "((-1 * N0 / 2) + 64) * -1",
    ._unit = "Degrees",
    ._len = 1,
    ._PID = "000E",
    ._format = "",
    ._mci = "%SPK%",
    ._selected = false,
    ._value = "",
    ._fake = false,
    ._duplicate = false,
    ._dupeIndex = -1,
    ._CMD = "",
    ._guid = "ce51ecd9-8f59-4851-a3e7-65d3fb2f0e0e"
  }, {
    ._name = "HO2 Bank 1 Sensor 2",
    ._shortname = "HO2 B1S2",
    ._formula = "0.434 * N0 * 10",
    ._unit = "mV",
    ._len = 1,
    ._PID = "1146",
    ._format = "",
    ._mci = "",
    ._selected = false,
    ._value = "",
    ._fake = false,
    ._duplicate = false,
    ._dupeIndex = -1,
    ._CMD = "",
    ._guid = "e76c4258-c72f-473f-83c8-99c8e38beebe"
  }, {
    ._name = "Traction Control Desired Torque",
    ._shortname = "Traction CTRL Torque",
    ._formula = "((N1 << 8) + N2) * 5 / 256",
    ._unit = "%",
    ._len = 2,
    ._PID = "160C",
    ._format = "%f",
    ._mci = "",
    ._selected = false,
    ._value = "",
    ._fake = false,
    ._duplicate = false,
    ._dupeIndex = -1,
    ._CMD = "",
    ._guid = "01594c60-2504-409c-aca9-cc7212381004"
  }, {
    ._name = "Fuel Level",
    ._shortname = "Fuel Level",
    ._formula = "((N1 << 8) + N2) * 0.01953125",
    ._unit = "%",
    ._len = 2,
    ._PID = "12C5",
    ._format = "",
    ._mci = "",
    ._selected = false,
    ._value = "",
    ._fake = false,
    ._duplicate = false,
    ._dupeIndex = -1,
    ._CMD = "",
    ._guid = "35663a1f-5a55-43bf-aed9-167151b0d59c"
  }, {
    ._name = "Transmission Range Switch A",
    ._shortname = "TR A",
    ._formula = "N0 & 1",
    ._unit = "",
    ._len = 1,
    ._PID = "1100",
    ._format = "",
    ._mci = "",
    ._selected = false,
    ._value = "",
    ._fake = false,
    ._duplicate = false,
    ._dupeIndex = -1,
    ._CMD = "",
    ._guid = "7eaea396-26f5-4ada-932a-6bd638cb9f77"
  }, {
    ._name = "Transmission Range Switch B",
    ._shortname = "TR B",
    ._formula = "((N0 >> 1) & 1)",
    ._unit = "",
    ._len = 1,
    ._PID = "1100",
    ._format = "",
    ._mci = "",
    ._selected = false,
    ._value = "",
    ._fake = false,
    ._duplicate = false,
    ._dupeIndex = -1,
    ._CMD = "",
    ._guid = "572dd54c-0699-4f02-bad7-e9110b392c29"
  }, {
    ._name = "Transmission Range Switch C",
    ._shortname = "TR C",
    ._formula = "((N0 >> 2) & 1)",
    ._unit = "",
    ._len = 1,
    ._PID = "1100",
    ._format = "",
    ._mci = "",
    ._selected = false,
    ._value = "",
    ._fake = false,
    ._duplicate = false,
    ._dupeIndex = -1,
    ._CMD = "",
    ._guid = "021a982a-c79f-478b-83cc-b72840f3affa"
  }, {
    ._name = "Transmission Range Switch P",
    ._shortname = "TR P",
    ._formula = "((N0 >> 3) & 1)",
    ._unit = "",
    ._len = 1,
    ._PID = "1100",
    ._format = "",
    ._mci = "",
    ._selected = false,
    ._value = "",
    ._fake = false,
    ._duplicate = false,
    ._dupeIndex = -1,
    ._CMD = "",
    ._guid = "ded10be8-25ce-479f-b320-37cc26f4d47f"
  }, {
    ._name = "Transmission Range",
    ._shortname = "TR",
    ._formula = "N0 & 15",
    ._unit = "",
    ._len = 1,
    ._PID = "1100",
    ._format = "",
    ._mci = "",
    ._selected = false,
    ._value = "",
    ._fake = false,
    ._duplicate = false,
    ._dupeIndex = -1,
    ._CMD = "",
    ._guid = "8e9c0fee-d630-4933-ac2d-b64c63ec648a"
  }, {
    ._name = "Boost Solenoid PWM",
    ._shortname = "Boost Solenoid",
    ._formula = "((N1 > 4) & 2) + ((N2 > 5) & 3)",
    ._unit = "",
    ._len = 2,
    ._PID = "1108",
    ._format = "",
    ._mci = "%BoostPWM%",
    ._selected = false,
    ._value = "",
    ._fake = false,
    ._duplicate = false,
    ._dupeIndex = -1,
    ._CMD = "",
    ._guid = "cd6e8e77-c23a-4dd9-8058-62899c6e9adb"
  }, {
    ._name = "Engine Torque",
    ._shortname = "Engine Torque",
    ._formula = "((N1 << 8) + N2) * 0.33895",
    ._unit = "N-m",
    ._len = 2,
    ._PID = "19DE",
    ._format = "",
    ._mci = "",
    ._selected = false,
    ._value = "",
    ._fake = false,
    ._duplicate = false,
    ._dupeIndex = -1,
    ._CMD = "",
    ._guid = "c824f1dd-6dea-4747-bbc3-6cf3d62116a7"
  }, {
    ._name = "EGR %",
    ._shortname = "EGR %",
    ._formula = "N0 / 2.55",
    ._unit = "%",
    ._len = 1,
    ._PID = "1152",
    ._format = "",
    ._mci = "",
    ._selected = false,
    ._value = "",
    ._fake = false,
    ._duplicate = false,
    ._dupeIndex = -1,
    ._CMD = "",
    ._guid = "e8deae0f-0d3f-4166-a0e6-4422b3041360"
  }, {
    ._name = "EGR Duty Cycle",
    ._shortname = "EGR %",
    ._formula = "N0 / 2.55",
    ._unit = "%",
    ._len = 1,
    ._PID = "1171",
    ._format = "",
    ._mci = "",
    ._selected = false,
    ._value = "",
    ._fake = false,
    ._duplicate = false,
    ._dupeIndex = -1,
    ._CMD = "",
    ._guid = "f619397b-f61d-4db5-b946-cd08cbc243e7"
  }, {
    ._name = "Desired EGR %",
    ._shortname = "Desired EGR %",
    ._formula = "N0 / 2.55",
    ._unit = "%",
    ._len = 1,
    ._PID = "119B",
    ._format = "",
    ._mci = "",
    ._selected = false,
    ._value = "",
    ._fake = false,
    ._duplicate = false,
    ._dupeIndex = -1,
    ._CMD = "",
    ._guid = "939cc26a-2a48-4184-811b-954d13edef39"
  }, {
    ._name = "EGR Closed Valve Pintle Position",
    ._shortname = "EGR Pintle V",
    ._formula = "N0 / 51",
    ._unit = "V",
    ._len = 1,
    ._PID = "11BB",
    ._format = "",
    ._mci = "",
    ._selected = false,
    ._value = "",
    ._fake = false,
    ._duplicate = false,
    ._dupeIndex = -1,
    ._CMD = "",
    ._guid = "9443a8c6-e12c-4b65-9b38-c818783c96be"
  }, {
    ._name = "EGR Flow Test Count",
    ._shortname = "EGR Flow Count",
    ._formula = "N0",
    ._unit = "",
    ._len = 1,
    ._PID = "11BD",
    ._format = "",
    ._mci = "",
    ._selected = false,
    ._value = "",
    ._fake = false,
    ._duplicate = false,
    ._dupeIndex = -1,
    ._CMD = "",
    ._guid = "bdd1520b-15fe-4d44-8e03-4c37a0ecc55e"
  }, {
    ._name = "EGR Position Error",
    ._shortname = "EGR Error V",
    ._formula = "(N0 - 128) / 1.28",
    ._unit = "V",
    ._len = 1,
    ._PID = "11C1",
    ._format = "",
    ._mci = "",
    ._selected = false,
    ._value = "",
    ._fake = false,
    ._duplicate = false,
    ._dupeIndex = -1,
    ._CMD = "",
    ._guid = "f21234d1-99f1-4a36-bac9-31be48814af1"
  }, {
    ._name = "Commanded EGR",
    ._shortname = "Commanded EGR",
    ._formula = "N0 / 2.55",
    ._unit = "%",
    ._len = 1,
    ._PID = "002C",
    ._format = "",
    ._mci = "",
    ._selected = false,
    ._value = "",
    ._fake = false,
    ._duplicate = false,
    ._dupeIndex = -1,
    ._CMD = "",
    ._guid = "50de21a7-9dde-4a66-ad52-20b179b9cee0"
  }, {
    ._name = "EGR Error %",
    ._shortname = "EGR Error",
    ._formula = "N0 * 0.78125 - 100",
    ._unit = "%",
    ._len = 1,
    ._PID = "002D",
    ._format = "",
    ._mci = "",
    ._selected = false,
    ._value = "",
    ._fake = false,
    ._duplicate = false,
    ._dupeIndex = -1,
    ._CMD = "",
    ._guid = "af21e635-3870-4c3e-8ba0-852d0fb48786"
  }, {
    ._name = "TP Sensor Voltage",
    ._shortname = "TP V",
    ._formula = "N0 / 51",
    ._unit = "V",
    ._len = 1,
    ._PID = "1143",
    ._format = "",
    ._mci = "",
    ._selected = false,
    ._value = "",
    ._fake = false,
    ._duplicate = false,
    ._dupeIndex = -1,
    ._CMD = "",
    ._guid = "300db759-4f46-488d-a447-db5109ab7cfc"
  }, {
    ._name = "CMP Sensor Signal Present",
    ._shortname = "CMP Present",
    ._formula = "((N0 >> 1) & 1)",
    ._unit = "",
    ._len = 1,
    ._PID = "1107",
    ._format = "",
    ._mci = "",
    ._selected = false,
    ._value = "",
    ._fake = false,
    ._duplicate = false,
    ._dupeIndex = -1,
    ._CMD = "",
    ._guid = "7c694ddc-4d01-4e11-b2f1-882caa8df1ed"
  }
};


struct TBlockID {
  int value; // -1 for empty
  String PID; // PID stored
};

// 8 rows $FE to $F7
// 6 bytes per row
TBlockID Blocks[8][6];

EXTMEM QList < struct TPID > sPIDS; // linked list of selected to keep track of what user wants.

byte currentBlock;

void ClearBlocks() {
  for (int y = 0; y < 8; y++) {
    for (int x = 0; x < 6; x++) {
      Blocks[y][x].value = -1;
      Blocks[y][x].PID = "";
    }
  }
}

// Generates A simple grid layout to be able to see what PIDS are where in the blocks to send to the PCM

void PopulateGrid() {
  Serial.println("");
  Serial.println("----------------------------------------------------------------------------");
  for (int y = 0; y < 8; y++) {
    switch (y) {
      case 0:
        Serial.print("$FE | ");
        break;
      case 1:
        Serial.print("$FD | ");
        break;
      case 2:
        Serial.print("$FC | ");
        break;
      case 3:
        Serial.print("$FB | ");
        break;
      case 4:
        Serial.print("$FA | ");
        break;
      case 5:
        Serial.print("$F9 | ");
        break;
      case 6:
        Serial.print("$F8 | ");
        break;
      case 7:
        Serial.print("$F7 | ");
        break;
    }
    for (int x = 0; x < 6; x++) {
      Serial.print(" ");
      if (Blocks[y][x].value > -1) {
        Serial.print(" ");
      }
      Serial.print(Blocks[y][x].value);
      Serial.print("(");
      if (Blocks[y][x].PID == "") {
        Serial.print("----");
      } else {
        Serial.print(Blocks[y][x].PID);
      }
      Serial.print(")");
      Serial.print(" |");
    }
    Serial.println("");
  }
  Serial.println("----------------------------------------------------------------------------");
  Serial.println("");
}

int findspot(byte len, String PID) {
  bool found;
  int PID_Position = -1; // will return this at the end

  for (int by = 0; by < 8; by++) {
    for (int bx = 0; bx < 6; bx++) {
      found = false;

      if (Blocks[by][bx].value == -1) {
        switch (len) {
          case 1: {
              found = true;
              break;
            }
          case 2: {
              if (bx < 5) { // fits 0,1,2,3,4,x
                if (Blocks[by][bx + 1].value == -1) {
                  found = true;
                }
              }
              break;
            }
          case 4: {
              if (bx < 3) { // fits 0,1,2,x,x,x
                if (Blocks[by][bx + 1].value == -1 &&
                    Blocks[by][bx + 2].value == -1 &&
                    Blocks[by][bx + 3].value == -1) {
                  found = true;
                }
              }
              break;
            }
        }

        if (found == true) {
          PID_Position = bx; // 0 based array
          switch (by) {
            case 0: {
                currentBlock = 254;
                break;
              }
            case 1: {
                currentBlock = 253;
                break;
              }
            case 2: {
                currentBlock = 252;
                break;
              }
            case 3: {
                currentBlock = 251;
                break;
              }
            case 4: {
                currentBlock = 250;
                break;
              }
            case 5: {
                currentBlock = 249;
                break;
              }
            case 6: {
                currentBlock = 248;
                break;
              }
            case 7: {
                currentBlock = 247;
                break;
              }
          }

          switch (len) {
            case 1: {
                Blocks[by][bx].value = len;
                Blocks[by][bx].PID = PID;
                break;
              }
            case 2: {
                Blocks[by][bx].value = len;
                Blocks[by][bx].PID = PID;
                Blocks[by][bx + 1].value = len;
                Blocks[by][bx + 1].PID = PID;
                break;
              }
            case 4: {
                Blocks[by][bx].value = len;
                Blocks[by][bx + 1].value = len;
                Blocks[by][bx + 2].value = len;
                Blocks[by][bx + 3].value = len;
                Blocks[by][bx].PID = PID;
                Blocks[by][bx + 1].PID = PID;
                Blocks[by][bx + 2].PID = PID;
                Blocks[by][bx + 3].PID = PID;
                break;
              }
          }
          return PID_Position; // get out of here, we found a spot!
        }
      }
    }
  }

  Serial.print("PID_Position(b) = ");
  Serial.println(PID_Position);

  return PID_Position;
}

String addpid(String PID, byte len, byte PID_Position) {

  /*
    Serial.print(pItem.PID);
    Serial.print("-");
    Serial.print(pItem.len);
    Serial.print("-");
    Serial.println(PID_Position);
  */

  byte count;
  String pidcmd;
  count = 64; // start position in the GM memory for a block
  pidcmd = "";

  if ((1 & len) > 0) {
    count = count + 1;
  }

  if ((2 & len) > 0) {
    count = count + 2;
  }

  if ((4 & len) > 0) {
    count = count + 4;
  }

  if ((1 & (PID_Position + 1)) > 0) {
    count = count + 8;
  }

  if ((2 & (PID_Position + 1)) > 0) {
    count = count + 16;
  }

  if ((4 & (PID_Position + 1)) > 0) {
    count = count + 32;
  }

  //Serial.println(pItem.name); // left side memo, show name
  //                   6C10F1
  //  pidcmd.concat("0A6C10F12C");
  pidcmd.concat("2C");
  pidcmd.concat(ByteToHex(currentBlock));
  pidcmd.concat(ByteToHex(count));
  pidcmd.concat(PID);
  pidcmd.concat("FFFF");

  return pidcmd;
}

bool BuildPIDS() {
  ClearBlocks();
  //currentBlock = 254; // $FE
  int PID_Position = -1;
  Serial.println("");

  for (int idx = 0; idx < sPIDS.size(); idx++) {
    PID_Position = -1;

    if (sPIDS.at(idx)._duplicate == true) {
      Serial.print("Dupe at ");
      Serial.print(idx);
      Serial.print(" PID = ");
      Serial.println(sPIDS.at(idx)._PID);
    } else if (sPIDS.at(idx)._fake == true) {
      Serial.print("Fake at ");
      Serial.print(idx);
      Serial.print(" PID = ");
      Serial.println(sPIDS.at(idx)._PID);
    } else {
      PID_Position = findspot(sPIDS.at(idx)._len, sPIDS.at(idx)._PID);
      Serial.print(idx);
      Serial.print(" - ");
      Serial.print(sPIDS.at(idx)._PID);
      Serial.print(" - ");
      Serial.println(PID_Position);

      if (PID_Position > -1) {
        String CMD = addpid(sPIDS.at(idx)._PID, sPIDS.at(idx)._len, PID_Position);
        sPIDS.at(idx)._CMD = CMD;
        sPIDS.at(idx)._blockID = currentBlock;
        sPIDS.at(idx)._blockPOS = PID_Position;
      } else {
        Serial.print("Removed ");
        Serial.print(idx);
        Serial.print(" ");
        Serial.print(sPIDS.at(idx)._PID);
        return false; // should be only the last item
      }
    }
  }

  return true; // ok it worked it added
  Serial.println("");
  Serial.println("-----------------------------------------------");
}

// Generates the list of selected PIDS and their position / states
void printPIDS() {
  Serial.println("");
  Serial.println("");
  Serial.print("Select PID Count #");
  Serial.println(sPIDS.size());
  Serial.println("");
  Serial.println("-----------------------------------------------");

  for (int x = 0; x < sPIDS.size(); x++) {
    Serial.print(x);
    Serial.print(" - ");
    Serial.print(sPIDS.at(x)._PID);
    Serial.print(" - ");
    Serial.print(sPIDS.at(x)._len);
    Serial.print(" - ");

    if (sPIDS.at(x)._fake == true) {
      Serial.print("Fake User PID ");
      Serial.print(sPIDS.at(x)._PID);
      Serial.print("    ");
    } else

      if (sPIDS.at(x)._duplicate == true) {
        Serial.print("duplicate to index ");
        Serial.print(sPIDS.at(x)._dupeIndex);
        Serial.print("  ");
      } else {
        Serial.print(sPIDS.at(x)._CMD);
      }
    Serial.print("  -  ");
    Serial.println(sPIDS.at(x)._name);
  }
}
