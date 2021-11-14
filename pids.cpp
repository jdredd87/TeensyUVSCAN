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
      ._shortname = "",
      ._formula = "((N1 << 8) +N2) *0.25",
      ._unit = "RPM",
      ._len = 2,
      ._PID = "000C",
      ._format = "",
      ._selected = false,
      ._MCI = "%RPM%",
      ._value = "", 
      ._fake = false, 
      ._duplicate = false, 
      ._dupeIndex = -1, ._CMD = "",
      ._guid = "6cd30bb0-77e1-4c2a-a780-02a9124b296e"
  },
  {
    ._name = "Injector PW",
    ._shortname = "",
    ._formula = "(((N1<<8)+N2)/65.535)",
    ._unit = "ms",
    ._len = 2,
    ._PID = "1193",
    ._format = "%f",
    ._selected = false,
    ._MCI = "%IPW%",
    ._value = "",
    ._fake = false,
    ._duplicate = false,
    ._dupeIndex = -1,
    ._CMD = "",
    ._guid = "430031d4-2dec-4d22-ba12-fc6ec231e375"
  },
  {
    ._name = "ECT (ENGINE COOLANT TEMPERATURE)",
    ._shortname = "",
    ._formula = "N0-40",
    ._unit = "ºC",
    ._len = 1,
    ._PID = "5",
    ._format = "",
    ._selected = false,
    ._MCI = "%ECT%",
    ._value = "",
    ._fake = false,
    ._duplicate = false,
    ._dupeIndex = -1,
    ._CMD = "",
    ._guid = "88a9038f-296d-4917-896e-257bcd4cef0f"
  },
  {
    ._name = "MASS AIR FLOW RAW INPUT FREQUENCY",
    ._shortname = "",
    ._formula = "((N1 << 8) + N2) / 2.048",
    ._unit = "Hz",
    ._len = 2,
    ._PID = "1250",
    ._format = "%f",
    ._selected = false,
    ._MCI = "%MAF%",
    ._value = "",
    ._fake = false,
    ._duplicate = false,
    ._dupeIndex = -1,
    ._CMD = "",
    ._guid = "a7718867-0233-47fd-99c6-fac5e53ba34e"
  },
  {
    ._name = "SHORT TERM FUEL TRIM BANK 1",
    ._shortname = "",
    ._formula = "(N0-128)/1.28",
    ._unit = "%",
    ._len = 1,
    ._PID = "6",
    ._format = "%f",
    ._selected = false,
    ._MCI = "%STF%",
    ._value = "",
    ._fake = false,
    ._duplicate = false,
    ._dupeIndex = -1,
    ._CMD = "",
    ._guid = "545d3417-6572-469e-8dfc-db96c23d2b19"
  },
  {
    ._name = "LONG TERM FUEL TRIM BANK 1",
    ._shortname = "",
    ._formula = "(N0-128)/1.28",
    ._unit = "%",
    ._len = 1,
    ._PID = "7",
    ._format = "%f",
    ._selected = false,
    ._MCI = "%LTF%",
    ._value = "",
    ._fake = false,
    ._duplicate = false,
    ._dupeIndex = -1,
    ._CMD = "",
    ._guid = "bb6dbdeb-170d-49f0-bc11-a7f3fe7a6f85"
  },
  {
    ._name = "MAP (kPa)",
    ._shortname = "",
    ._formula = "N0",
    ._unit = "kPa",
    ._len = 1,
    ._PID = "000B",
    ._format = "",
    ._selected = false,
    ._MCI = "%MAP%",
    ._value = "",
    ._fake = false,
    ._duplicate = false,
    ._dupeIndex = -1,
    ._CMD = "",
    ._guid = "4001f575-ae3a-4f7f-a89d-6854a7a55e3b"
  },
  {
    ._name = "VEHICLE SPEED",
    ._shortname = "",
    ._formula = "N0/1.609",
    ._unit = "MPH",
    ._len = 1,
    ._PID = "000D",
    ._format = "%f",
    ._selected = false,
    ._MCI = "%MPH%",
    ._value = "",
    ._fake = false,
    ._duplicate = false,
    ._dupeIndex = -1,
    ._CMD = "",
    ._guid = "269caec3-da38-4061-9c35-c55a1b89a759"
  },
  {
    ._name = "SPARK ADVANCE",
    ._shortname = "",
    ._formula = "((N0/2) - 64) *",
    ._unit = "Degrees",
    ._len = 1,
    ._PID = "000E",
    ._format = "",
    ._selected = false,
    ._MCI = "%SPK%",
    ._value = "",
    ._fake = false,
    ._duplicate = false,
    ._dupeIndex = -1,
    ._CMD = "",
    ._guid = "85d3bd93-9ac2-4b30-8f4c-da3cde126843"
  },
  {
    ._name = "INTAKE AIR TEMPERATURE",
    ._shortname = "",
    ._formula = "N0-40",
    ._unit = "ºC",
    ._len = 1,
    ._PID = "000F",
    ._format = "",
    ._selected = false,
    ._MCI = "%IAT%",
    ._value = "",
    ._fake = false,
    ._duplicate = false,
    ._dupeIndex = -1,
    ._CMD = "",
    ._guid = "3574e1c3-5e32-422f-b1b7-dd9d8f0c2538"
  },
  {
    ._name = "TP Angle %",
    ._shortname = "",
    ._formula = "N0/2.55",
    ._unit = "%",
    ._len = 1,
    ._PID = "11",
    ._format = "",
    ._selected = false,
    ._MCI = "%TPS%",
    ._value = "",
    ._fake = false,
    ._duplicate = false,
    ._dupeIndex = -1,
    ._CMD = "",
    ._guid = "f6bcc554-150a-4e4d-b6ad-893820b09161"
  },
  {
    ._name = "Ignition 1 Voltage",
    ._shortname = "",
    ._formula = "N0/10",
    ._unit = "V",
    ._len = 1,
    ._PID = "1141",
    ._format = "",
    ._selected = false,
    ._MCI = "%IGV%",
    ._value = "",
    ._fake = false,
    ._duplicate = false,
    ._dupeIndex = -1,
    ._CMD = "",
    ._guid = "67632335-302c-4bf5-8c9b-9ed9dd6c5a6e"
  },
  {
    ._name = "H02S Sensor 1",
    ._shortname = "",
    ._formula = "0.434*N0*10",
    ._unit = "mV",
    ._len = 1,
    ._PID = "1145",
    ._format = "",
    ._selected = false,
    ._MCI = "%HO1%",
    ._value = "",
    ._fake = false,
    ._duplicate = false,
    ._dupeIndex = -1,
    ._CMD = "",
    ._guid = "e30f8822-eec5-4b72-8409-cc78bebb3403"
  },
  {
    ._name = "Knock Retard",
    ._shortname = "",
    ._formula = "22.5*N0/256",
    ._unit = "Degrees",
    ._len = 1,
    ._PID = "11A6",
    ._format = "",
    ._selected = false,
    ._MCI = "%KRS%",
    ._value = "",
    ._fake = false,
    ._duplicate = false,
    ._dupeIndex = -1,
    ._CMD = "",
    ._guid = "4b48859c-8d60-4bd8-a0ee-c0ae830f3dd3"
  },
  {
    ._name = "Current Gear",
    ._shortname = "",
    ._formula = "N0",
    ._unit = "",
    ._len = 1,
    ._PID = "199A",
    ._format = "",
    ._selected = false,
    ._MCI = "%CGS%",
    ._value = "",
    ._fake = false,
    ._duplicate = false,
    ._dupeIndex = -1,
    ._CMD = "",
    ._guid = "32b12a0f-f991-406d-8c53-64af9ad0bfd6"
  },
  {
    ._name = "Misfire Cyl. 1 History",
    ._shortname = "",
    ._formula = "(N1 << 8) + N2",
    ._unit = "Count",
    ._len = 2,
    ._PID = "1201",
    ._format = "",
    ._selected = false,
    ._MCI = "%MH1%",
    ._value = "",
    ._fake = false,
    ._duplicate = false,
    ._dupeIndex = -1,
    ._CMD = "",
    ._guid = "48bae48d-96e4-42a1-96a1-83be0e06face"
  },
  {
    ._name = "Misfire Cyl. 1 Current",
    ._shortname = "",
    ._formula = "N0",
    ._unit = "Count",
    ._len = 1,
    ._PID = "1206",
    ._format = "",
    ._selected = false,
    ._MCI = "%MC1%",
    ._value = "",
    ._fake = false,
    ._duplicate = false,
    ._dupeIndex = -1,
    ._CMD = "",
    ._guid = "652ce231-cb8b-46b1-9fe9-26a121cc898b"
  },
  {
    ._name = "Misfire Cyl. 2 History",
    ._shortname = "",
    ._formula = "(N1 << 8) + N2",
    ._unit = "Count",
    ._len = 2,
    ._PID = "1202",
    ._format = "",
    ._selected = false,
    ._MCI = "%MH2%",
    ._value = "",
    ._fake = false,
    ._duplicate = false,
    ._dupeIndex = -1,
    ._CMD = "",
    ._guid = "e7856918-dd4f-49c7-b35f-7952edd23a69"
  },
  {
    ._name = "Misfire Cyl. 2 Current",
    ._shortname = "",
    ._formula = "N0",
    ._unit = "Count",
    ._len = 1,
    ._PID = "1205",
    ._format = "",
    ._selected = false,
    ._MCI = "%MC2%",
    ._value = "",
    ._fake = false,
    ._duplicate = false,
    ._dupeIndex = -1,
    ._CMD = "",
    ._guid = "2c99f5e7-e6c2-4289-8328-5ef370df7c56"
  },
  {
    ._name = "Misfire Cyl. 3 History",
    ._shortname = "",
    ._formula = "(N1 << 8) + N2",
    ._unit = "Count",
    ._len = 2,
    ._PID = "1203",
    ._format = "",
    ._selected = false,
    ._MCI = "%MH3%",
    ._value = "",
    ._fake = false,
    ._duplicate = false,
    ._dupeIndex = -1,
    ._CMD = "",
    ._guid = "5d99c356-cace-4be9-abfc-93c9de41cf62"
  },
  {
    ._name = "Misfire Cyl. 3 Current",
    ._shortname = "",
    ._formula = "N0",
    ._unit = "Count",
    ._len = 1,
    ._PID = "1207",
    ._format = "",
    ._selected = false,
    ._MCI = "%MC3%",
    ._value = "",
    ._fake = false,
    ._duplicate = false,
    ._dupeIndex = -1,
    ._CMD = "",
    ._guid = "ca5dacdb-aa48-4877-9ae0-0d2171e16c27"
  },
  {
    ._name = "Misfire Cyl. 4 History",
    ._shortname = "",
    ._formula = "(N1 << 8) + N2",
    ._unit = "Count",
    ._len = 2,
    ._PID = "1204",
    ._format = "",
    ._selected = false,
    ._MCI = "%MH4%",
    ._value = "",
    ._fake = false,
    ._duplicate = false,
    ._dupeIndex = -1,
    ._CMD = "",
    ._guid = "dbdc8daa-1d05-478c-88fb-3a89d7f91ce2"
  },
  {
    ._name = "Misfire Cyl. 4 Current",
    ._shortname = "",
    ._formula = "N0",
    ._unit = "Count",
    ._len = 1,
    ._PID = "1208",
    ._format = "",
    ._selected = false,
    ._MCI = "%MC4%",
    ._value = "",
    ._fake = false,
    ._duplicate = false,
    ._dupeIndex = -1,
    ._CMD = "",
    ._guid = "f238bb19-433a-4eb4-8841-6f68bcd0af1a"
  },
  {
    ._name = "Misfire Cyl. 5 History",
    ._shortname = "",
    ._formula = "(N1 << 8) + N2",
    ._unit = "Count",
    ._len = 2,
    ._PID = "11F8",
    ._format = "",
    ._selected = false,
    ._MCI = "%MH5%",
    ._value = "",
    ._fake = false,
    ._duplicate = false,
    ._dupeIndex = -1,
    ._CMD = "",
    ._guid = "fc128da0-643f-474e-a0ac-b79089e5f70c"
  },
  {
    ._name = "Misfire Cyl. 5 Current",
    ._shortname = "",
    ._formula = "N0",
    ._unit = "Count",
    ._len = 1,
    ._PID = "11EA",
    ._format = "",
    ._selected = false,
    ._MCI = "%MC5%",
    ._value = "",
    ._fake = false,
    ._duplicate = false,
    ._dupeIndex = -1,
    ._CMD = "",
    ._guid = "e8bee228-0da5-4a78-978a-587cd82c1ccc"
  },
  {
    ._name = "Misfire Cyl. 6 History",
    ._shortname = "",
    ._formula = "(N1 << 8) + N2",
    ._unit = "Count",
    ._len = 2,
    ._PID = "11F9",
    ._format = "",
    ._selected = false,
    ._MCI = "%MH6%",
    ._value = "",
    ._fake = false,
    ._duplicate = false,
    ._dupeIndex = -1,
    ._CMD = "",
    ._guid = "a93ab092-f380-4b17-b810-49cd4fc0d503"
  },
  {
    ._name = "Misfire Cyl. 6 Current",
    ._shortname = "",
    ._formula = "N0",
    ._unit = "Count",
    ._len = 1,
    ._PID = "11EB",
    ._format = "",
    ._selected = false,
    ._MCI = "%MC6%",
    ._value = "",
    ._fake = false,
    ._duplicate = false,
    ._dupeIndex = -1,
    ._CMD = "",
    ._guid = "cc8128de-d5dc-4f90-ad73-6f1da6fc7bbc"
  },
  {
    ._name = "Fuel Trim Cell",
    ._shortname = "",
    ._formula = "N0",
    ._unit = "",
    ._len = 1,
    ._PID = "1190",
    ._format = "",
    ._selected = false,
    ._MCI = "%FTC%",
    ._value = "",
    ._fake = false,
    ._duplicate = false,
    ._dupeIndex = -1,
    ._CMD = "",
    ._guid = "95b29e26-ac6d-43a5-a18d-4a635cc6ccc4"
  },
  {
    ._name = "MAF Flow Rate",
    ._shortname = "",
    ._formula = "((N1 << 8) + N2)  / 100",
    ._unit = "g/s",
    ._len = 2,
    ._PID = "10",
    ._format = "",
    ._selected = false,
    ._MCI = "%MAFGmPerSec%",
    ._value = "",
    ._fake = false,
    ._duplicate = false,
    ._dupeIndex = -1,
    ._CMD = "",
    ._guid = "1d4502e9-1ba7-4436-8cb2-58f1ac52e809"
  },
  {
    ._name = "AFR (Commanded)",
    ._shortname = "",
    ._formula = "N0 / 10",
    ._unit = ":1",
    ._len = 1,
    ._PID = "119E",
    ._format = "",
    ._selected = false,
    ._MCI = "%AFRCommanded%",
    ._value = "",
    ._fake = false,
    ._duplicate = false,
    ._dupeIndex = -1,
    ._CMD = "",
    ._guid = "5de2cedc-0a3e-4f09-8033-b9d0c6645996"
  },
  {
    ._name = "Last Shift Time",
    ._shortname = "",
    ._formula = "N0 / 40",
    ._unit = "Seconds",
    ._len = 1,
    ._PID = "1992",
    ._format = "",
    ._selected = false,
    ._MCI = "%LST%",
    ._value = "",
    ._fake = false,
    ._duplicate = false,
    ._dupeIndex = -1,
    ._CMD = "",
    ._guid = "6029ee1f-cbbd-419e-a069-3102cc766592"
  },
  {
    ._name = "1-2 Shift Time",
    ._shortname = "",
    ._formula = "N0 / 40",
    ._unit = "Seconds",
    ._len = 1,
    ._PID = "1993",
    ._format = "",
    ._selected = false,
    ._MCI = "%ST12%",
    ._value = "",
    ._fake = false,
    ._duplicate = false,
    ._dupeIndex = -1,
    ._CMD = "",
    ._guid = "f1849cf4-3196-4104-9aba-b44983175e7f"
  },
  {
    ._name = "2-3 Shift Time",
    ._shortname = "",
    ._formula = "N0 / 40",
    ._unit = "Seconds",
    ._len = 1,
    ._PID = "1994",
    ._format = "",
    ._selected = false,
    ._MCI = "%ST23%",
    ._value = "",
    ._fake = false,
    ._duplicate = false,
    ._dupeIndex = -1,
    ._CMD = "",
    ._guid = "2f8c4332-31a3-4f76-8fb3-17805a15be65"
  },
  {
    ._name = "3-4 Shift Time",
    ._shortname = "",
    ._formula = "N0 / 40",
    ._unit = "Seconds",
    ._len = 1,
    ._PID = "1995",
    ._format = "",
    ._selected = false,
    ._MCI = "%ST34%",
    ._value = "",
    ._fake = false,
    ._duplicate = false,
    ._dupeIndex = -1,
    ._CMD = "",
    ._guid = "041d4198-d914-484c-8f74-6ec75cae056b"
  },
  {
    ._name = "1-2 Shift Error",
    ._shortname = "",
    ._formula = "N0 / 40",
    ._unit = "Seconds",
    ._len = 1,
    ._PID = "1997",
    ._format = "",
    ._selected = false,
    ._MCI = "%SE12%",
    ._value = "",
    ._fake = false,
    ._duplicate = false,
    ._dupeIndex = -1,
    ._CMD = "",
    ._guid = "211e5bb4-9f15-47cc-86df-4744808fdc70"
  },
  {
    ._name = "2-3 Shift Error",
    ._shortname = "",
    ._formula = "N0 / 40",
    ._unit = "Seconds",
    ._len = 1,
    ._PID = "1998",
    ._format = "",
    ._selected = false,
    ._MCI = "%SE23%",
    ._value = "",
    ._fake = false,
    ._duplicate = false,
    ._dupeIndex = -1,
    ._CMD = "",
    ._guid = "82a854bd-178c-4a42-b737-3d423eea1015"
  },
  {
    ._name = "3-4 Shift Error",
    ._shortname = "",
    ._formula = "N0 / 40",
    ._unit = "Seconds",
    ._len = 1,
    ._PID = "1999",
    ._format = "",
    ._selected = false,
    ._MCI = "%SE34%",
    ._value = "",
    ._fake = false,
    ._duplicate = false,
    ._dupeIndex = -1,
    ._CMD = "",
    ._guid = "4f6ab6e7-96e6-4f9d-8a20-033cd9ca0bdb"
  },
  {
    ._name = "Fuel Loop Status",
    ._shortname = "",
    ._formula = "((N0 >> 3) & 1)",
    ._unit = "",
    ._len = 1,
    ._PID = "1105",
    ._format = "",
    ._selected = false,
    ._MCI = "%FuelLoopStatus%",
    ._value = "",
    ._fake = false,
    ._duplicate = false,
    ._dupeIndex = -1,
    ._CMD = "",
    ._guid = "13c80a52-f261-45a5-b9d6-c3ac6b9478fc"
  },
  {
    ._name = "Perf Shift Mode",
    ._shortname = "",
    ._formula = "((N0 >> 2) & 1)",
    ._unit = "",
    ._len = 1,
    ._PID = "110C",
    ._format = "%o",
    ._selected = false,
    ._MCI = "%BitShiftMode%",
    ._value = "",
    ._fake = false,
    ._duplicate = false,
    ._dupeIndex = -1,
    ._CMD = "",
    ._guid = "2f6297b0-2895-46b1-8609-fa944ac3be47"
  },
  {
    ._name = "Desired Idle Speed",
    ._shortname = "",
    ._formula = "N0 * 12.5",
    ._unit = "RPM",
    ._len = 1,
    ._PID = "1192",
    ._format = "",
    ._selected = false,
    ._MCI = "%DesiredIdle%",
    ._value = "",
    ._fake = false,
    ._duplicate = false,
    ._dupeIndex = -1,
    ._CMD = "",
    ._guid = "1bfdb874-d94e-4a14-af1e-7c18f5a34500"
  },
  {
    ._name = "IAC Position",
    ._shortname = "",
    ._formula = "N0",
    ._unit = "",
    ._len = 1,
    ._PID = "1172",
    ._format = "",
    ._selected = false,
    ._MCI = "%IACCounts%",
    ._value = "",
    ._fake = false,
    ._duplicate = false,
    ._dupeIndex = -1,
    ._CMD = "",
    ._guid = "044f6c87-e960-429e-9738-80d3f68b6a8a"
  },
  {
    ._name = "Power Enrichment Mode",
    ._shortname = "",
    ._formula = "((N0 >> 2) & 1)",
    ._unit = "",
    ._len = 1,
    ._PID = "1106",
    ._format = "%o",
    ._selected = false,
    ._MCI = "%BitPEMode%",
    ._value = "",
    ._fake = false,
    ._duplicate = false,
    ._dupeIndex = -1,
    ._CMD = "",
    ._guid = "14a38025-8799-48dc-b81a-b78b192d709b"
  },
  {
    ._name = "Decel Fuel Mode",
    ._shortname = "",
    ._formula = "((N0 >> 3) & 1)",
    ._unit = "",
    ._len = 1,
    ._PID = "1106",
    ._format = "%o",
    ._selected = false,
    ._MCI = "%BitDFCOMode%",
    ._value = "",
    ._fake = false,
    ._duplicate = false,
    ._dupeIndex = -1,
    ._CMD = "",
    ._guid = "4fe076fa-7480-4f7a-884b-716742a0ce40"
  },
  {
    ._name = "Transmission ISS",
    ._shortname = "",
    ._formula = "((N1 << 8) + N2) * 0.125",
    ._unit = "RPM",
    ._len = 2,
    ._PID = "1941",
    ._format = "",
    ._selected = false,
    ._MCI = "",
    ._value = "",
    ._fake = false,
    ._duplicate = false,
    ._dupeIndex = -1,
    ._CMD = "",
    ._guid = "b8eb4c58-6b1e-4fa3-aed9-a47352d27c92"
  },
  {
    ._name = "Transmission OSS",
    ._shortname = "",
    ._formula = "((N1 << 8) + N2) * 0.125",
    ._unit = "RPM",
    ._len = 2,
    ._PID = "1942",
    ._format = "",
    ._selected = false,
    ._MCI = "",
    ._value = "",
    ._fake = false,
    ._duplicate = false,
    ._dupeIndex = -1,
    ._CMD = "",
    ._guid = "2b2a28fd-1f96-46db-804d-50038a8d4fb5"
  },
  {
    ._name = "TCC Slip Speed",
    ._shortname = "",
    ._formula = "((N1 << 8) + N2) * 0.125",
    ._unit = "RPM",
    ._len = 2,
    ._PID = "1991",
    ._format = "",
    ._selected = false,
    ._MCI = "",
    ._value = "",
    ._fake = false,
    ._duplicate = false,
    ._dupeIndex = -1,
    ._CMD = "",
    ._guid = "b565949a-e000-4615-a466-e54cdc216549"
  },
  {
    ._name = "Transmission Fluid Temp",
    ._shortname = "",
    ._formula = "N0 - 40",
    ._unit = "ºC",
    ._len = 1,
    ._PID = "1940",
    ._format = "",
    ._selected = false,
    ._MCI = "",
    ._value = "",
    ._fake = false,
    ._duplicate = false,
    ._dupeIndex = -1,
    ._CMD = "",
    ._guid = "1d9b17ab-b121-4c38-94a1-8b35f73c637d"
  },
  {
    ._name = "TCC Duty Cycle",
    ._shortname = "",
    ._formula = "N0 / 2.55",
    ._unit = "%",
    ._len = 1,
    ._PID = "1970",
    ._format = "",
    ._selected = false,
    ._MCI = "",
    ._value = "",
    ._fake = false,
    ._duplicate = false,
    ._dupeIndex = -1,
    ._CMD = "",
    ._guid = "3a20c02a-19a4-4599-abde-50625302b052"
  },
  {
    ._name = "PC Solenoid Duty Cycle",
    ._shortname = "",
    ._formula = "N0 / 2.55",
    ._unit = "%",
    ._len = 1,
    ._PID = "1972",
    ._format = "",
    ._selected = false,
    ._MCI = "",
    ._value = "",
    ._fake = false,
    ._duplicate = false,
    ._dupeIndex = -1,
    ._CMD = "",
    ._guid = "bcdcaecd-ad87-45da-b159-605573e31d02"
  },
  {
    ._name = "PC Solenoid Actual Current",
    ._shortname = "",
    ._formula = "N0 * 0.0195",
    ._unit = "Amps",
    ._len = 1,
    ._PID = "199E",
    ._format = "",
    ._selected = false,
    ._MCI = "",
    ._value = "",
    ._fake = false,
    ._duplicate = false,
    ._dupeIndex = -1,
    ._CMD = "",
    ._guid = "b937ae48-e93b-4585-9f3d-3d8842c6e21b"
  },
  {
    ._name = "PC Solenoid Reference Current",
    ._shortname = "",
    ._formula = "N0 * 0.0195",
    ._unit = "Amps",
    ._len = 1,
    ._PID = "199F",
    ._format = "",
    ._selected = false,
    ._MCI = "",
    ._value = "",
    ._fake = false,
    ._duplicate = false,
    ._dupeIndex = -1,
    ._CMD = "",
    ._guid = "1e195b94-4401-4e81-b597-471e4ec16da9"
  },
  {
    ._name = "18X Crank Sensor",
    ._shortname = "",
    ._formula = "1310720 / (((N1 << 8) + N2) * 6)",
    ._unit = "Pulses",
    ._len = 2,
    ._PID = "1256",
    ._format = "",
    ._selected = false,
    ._MCI = "",
    ._value = "",
    ._fake = false,
    ._duplicate = false,
    ._dupeIndex = -1,
    ._CMD = "",
    ._guid = "826ed4dc-3f2f-4294-abb8-4cd3a2e84d75"
  },
  {
    ._name = "3X Crank Sensor",
    ._shortname = "",
    ._formula = "1310720 / ((N1 << 8) + N2)",
    ._unit = "Pulses",
    ._len = 2,
    ._PID = "124F",
    ._format = "",
    ._selected = false,
    ._MCI = "",
    ._value = "",
    ._fake = false,
    ._duplicate = false,
    ._dupeIndex = -1,
    ._CMD = "",
    ._guid = "a3f8090c-f273-47e0-b908-18bf71b8570e"
  },
  {
    ._name = "Fans Low Speed",
    ._shortname = "",
    ._formula = "((N0 >> 6) & 1)",
    ._unit = "",
    ._len = 1,
    ._PID = "1103",
    ._format = "%o",
    ._selected = false,
    ._MCI = "",
    ._value = "",
    ._fake = false,
    ._duplicate = false,
    ._dupeIndex = -1,
    ._CMD = "",
    ._guid = "583ed8b3-486d-4dc8-aa80-7e560b30ae1a"
  },
  {
    ._name = "Fans High Speed",
    ._shortname = "",
    ._formula = "((N0 >> 7) & 1)",
    ._unit = "",
    ._len = 1,
    ._PID = "1103",
    ._format = "%o",
    ._selected = false,
    ._MCI = "",
    ._value = "",
    ._fake = false,
    ._duplicate = false,
    ._dupeIndex = -1,
    ._CMD = "",
    ._guid = "92fb99ca-8514-436e-b157-b13965918741"
  },
  {
    ._name = "Gear Ratio",
    ._shortname = "",
    ._formula = "N0 * 0.01563",
    ._unit = ":1",
    ._len = 1,
    ._PID = "19A1",
    ._format = "",
    ._selected = false,
    ._MCI = "",
    ._value = "",
    ._fake = false,
    ._duplicate = false,
    ._dupeIndex = -1,
    ._CMD = "",
    ._guid = "b756af9b-4af9-4880-861f-fa9c109ec140"
  },
  {
    ._name = "SPARK ADVANCE (Alt)",
    ._shortname = "",
    ._formula = "((-1 * N0 / 2) + 64) * -1",
    ._unit = "Degrees",
    ._len = 1,
    ._PID = "000E",
    ._format = "",
    ._selected = false,
    ._MCI = "%SPK%",
    ._value = "",
    ._fake = false,
    ._duplicate = false,
    ._dupeIndex = -1,
    ._CMD = "",
    ._guid = "8cfee309-d1e2-4887-98af-560f6394c957"
  },
  {
    ._name = "HO2 Bank 1 Sensor 2",
    ._shortname = "",
    ._formula = "0.434 * N0 * 10",
    ._unit = "mV",
    ._len = 1,
    ._PID = "1146",
    ._format = "",
    ._selected = false,
    ._MCI = "",
    ._value = "",
    ._fake = false,
    ._duplicate = false,
    ._dupeIndex = -1,
    ._CMD = "",
    ._guid = "e063c23a-c6e9-472f-92d6-9098b74fd5f4"
  },
  {
    ._name = "Traction Control Desired Torque",
    ._shortname = "",
    ._formula = "((N1 << 8) + N2) * 5 / 256",
    ._unit = "%",
    ._len = 2,
    ._PID = "160C",
    ._format = "%f",
    ._selected = false,
    ._MCI = "",
    ._value = "",
    ._fake = false,
    ._duplicate = false,
    ._dupeIndex = -1,
    ._CMD = "",
    ._guid = "7a454f72-eae6-41c7-839c-48b9a9269fa2"
  },
  {
    ._name = "Fuel Level",
    ._shortname = "",
    ._formula = "((N1 << 8) + N2) * 0.01953125",
    ._unit = "%",
    ._len = 2,
    ._PID = "12C5",
    ._format = "",
    ._selected = false,
    ._MCI = "",
    ._value = "",
    ._fake = false,
    ._duplicate = false,
    ._dupeIndex = -1,
    ._CMD = "",
    ._guid = "ebbebed5-4576-4d25-a89c-daad768775a0"
  },
  {
    ._name = "Transmission Range Switch A",
    ._shortname = "",
    ._formula = "N0 & 1",
    ._unit = "",
    ._len = 1,
    ._PID = "1100",
    ._format = "",
    ._selected = false,
    ._MCI = "",
    ._value = "",
    ._fake = false,
    ._duplicate = false,
    ._dupeIndex = -1,
    ._CMD = "",
    ._guid = "99919b0a-7730-435c-baae-442c8dcbbf41"
  },
  {
    ._name = "Transmission Range Switch B",
    ._shortname = "",
    ._formula = "((N0 >> 1) & 1)",
    ._unit = "",
    ._len = 1,
    ._PID = "1100",
    ._format = "",
    ._selected = false,
    ._MCI = "",
    ._value = "",
    ._fake = false,
    ._duplicate = false,
    ._dupeIndex = -1,
    ._CMD = "",
    ._guid = "6b07d123-546a-4866-b62b-c2318c74aea4"
  },
  {
    ._name = "Transmission Range Switch C",
    ._shortname = "",
    ._formula = "((N0 >> 2) & 1)",
    ._unit = "",
    ._len = 1,
    ._PID = "1100",
    ._format = "",
    ._selected = false,
    ._MCI = "",
    ._value = "",
    ._fake = false,
    ._duplicate = false,
    ._dupeIndex = -1,
    ._CMD = "",
    ._guid = "ccb12603-0419-4eaa-87d5-81558c6b0196"
  },
  {
    ._name = "Transmission Range Switch P",
    ._shortname = "",
    ._formula = "((N0 >> 3) & 1)",
    ._unit = "",
    ._len = 1,
    ._PID = "1100",
    ._format = "",
    ._selected = false,
    ._MCI = "",
    ._value = "",
    ._fake = false,
    ._duplicate = false,
    ._dupeIndex = -1,
    ._CMD = "",
    ._guid = "7de59e57-767e-49a3-a579-ba98c13522e1"
  },
  {
    ._name = "Transmission Range",
    ._shortname = "",
    ._formula = "N0 & 15",
    ._unit = "",
    ._len = 1,
    ._PID = "1100",
    ._format = "",
    ._selected = false,
    ._MCI = "",
    ._value = "",
    ._fake = false,
    ._duplicate = false,
    ._dupeIndex = -1,
    ._CMD = "",
    ._guid = "1e0fe36a-bfe0-490b-ac5e-832ac0227afb"
  },
  {
    ._name = "Boost Solenoid PWM",
    ._shortname = "",
    ._formula = "((N1 > 4) & 2) + ((N2 > 5) & 3)",
    ._unit = "",
    ._len = 2,
    ._PID = "1108",
    ._format = "",
    ._selected = false,
    ._MCI = "%BoostPWM%",
    ._value = "",
    ._fake = false,
    ._duplicate = false,
    ._dupeIndex = -1,
    ._CMD = "",
    ._guid = "b8c82080-b528-493a-b842-82d9655b0171"
  },
  {
    ._name = "Engine Torque",
    ._shortname = "",
    ._formula = "((N1 << 8) + N2) * 0.33895",
    ._unit = "N-m",
    ._len = 2,
    ._PID = "19DE",
    ._format = "",
    ._selected = false,
    ._MCI = "",
    ._value = "",
    ._fake = false,
    ._duplicate = false,
    ._dupeIndex = -1,
    ._CMD = "",
    ._guid = "a9842755-2e47-41ee-9e0e-408d89ac2269"
  },
  {
    ._name = "EGR %",
    ._shortname = "",
    ._formula = "N0 / 2.55",
    ._unit = "%",
    ._len = 1,
    ._PID = "1152",
    ._format = "",
    ._selected = false,
    ._MCI = "",
    ._value = "",
    ._fake = false,
    ._duplicate = false,
    ._dupeIndex = -1,
    ._CMD = "",
    ._guid = "dfd29ecf-4b78-469d-90ec-9a9db2de5c17"
  },
  {
    ._name = "EGR Duty Cycle",
    ._shortname = "",
    ._formula = "N0 / 2.55",
    ._unit = "%",
    ._len = 1,
    ._PID = "1171",
    ._format = "",
    ._selected = false,
    ._MCI = "",
    ._value = "",
    ._fake = false,
    ._duplicate = false,
    ._dupeIndex = -1,
    ._CMD = "",
    ._guid = "215db1d7-11d0-4895-9a01-616704f8a80a"
  },
  {
    ._name = "Desired EGR %",
    ._shortname = "",
    ._formula = "N0 / 2.55",
    ._unit = "%",
    ._len = 1,
    ._PID = "119B",
    ._format = "",
    ._selected = false,
    ._MCI = "",
    ._value = "",
    ._fake = false,
    ._duplicate = false,
    ._dupeIndex = -1,
    ._CMD = "",
    ._guid = "66f17db9-5109-426c-b05d-b2900a585f57"
  },
  {
    ._name = "EGR Closed Valve Pintle Position",
    ._shortname = "",
    ._formula = "N0 / 51",
    ._unit = "V",
    ._len = 1,
    ._PID = "11BB",
    ._format = "",
    ._selected = false,
    ._MCI = "",
    ._value = "",
    ._fake = false,
    ._duplicate = false,
    ._dupeIndex = -1,
    ._CMD = "",
    ._guid = "8473f86e-0389-4b4d-a3bf-9ae4f52ab962"
  },
  {
    ._name = "EGR Flow Test Count",
    ._shortname = "",
    ._formula = "N0",
    ._unit = "",
    ._len = 1,
    ._PID = "11BD",
    ._format = "",
    ._selected = false,
    ._MCI = "",
    ._value = "",
    ._fake = false,
    ._duplicate = false,
    ._dupeIndex = -1,
    ._CMD = "",
    ._guid = "179345b8-c162-4939-9000-99574522f84e"
  },
  {
    ._name = "EGR Position Error",
    ._shortname = "",
    ._formula = "(N0 - 128) / 1.28",
    ._unit = "V",
    ._len = 1,
    ._PID = "11C1",
    ._format = "",
    ._selected = false,
    ._MCI = "",
    ._value = "",
    ._fake = false,
    ._duplicate = false,
    ._dupeIndex = -1,
    ._CMD = "",
    ._guid = "7bac5fbc-5a3d-45e4-9997-e20c2aaa3135"
  },
  {
    ._name = "Commanded EGR",
    ._shortname = "",
    ._formula = "N0 / 2.55",
    ._unit = "%",
    ._len = 1,
    ._PID = "002C",
    ._format = "",
    ._selected = false,
    ._MCI = "",
    ._value = "",
    ._fake = false,
    ._duplicate = false,
    ._dupeIndex = -1,
    ._CMD = "",
    ._guid = "5f26fd9a-97a2-4fdb-bfee-f188ba5b96aa"
  },
  {
    ._name = "EGR Error %",
    ._shortname = "",
    ._formula = "N0 * 0.78125 - 100",
    ._unit = "%",
    ._len = 1,
    ._PID = "002D",
    ._format = "",
    ._selected = false,
    ._MCI = "",
    ._value = "",
    ._fake = false,
    ._duplicate = false,
    ._dupeIndex = -1,
    ._CMD = "",
    ._guid = "f305b648-84f3-4f3f-ad39-4d1e66cd75a0"
  },
  {
    ._name = "TP Sensor Voltage",
    ._shortname = "",
    ._formula = "N0 / 51",
    ._unit = "V",
    ._len = 1,
    ._PID = "1143",
    ._format = "",
    ._selected = false,
    ._MCI = "",
    ._value = "",
    ._fake = false,
    ._duplicate = false,
    ._dupeIndex = -1,
    ._CMD = "",
    ._guid = "14f91426-b203-4464-9fc0-1e2c620aef0e"
  },
  {
    ._name = "CMP Sensor Signal Present",
    ._shortname = "",
    ._formula = "((N0 >> 1) & 1)",
    ._unit = "",
    ._len = 1,
    ._PID = "1107",
    ._format = "",
    ._selected = false,
    ._MCI = "",
    ._value = "",
    ._fake = false,
    ._duplicate = false,
    ._dupeIndex = -1,
    ._CMD = "",
    ._guid = "2af52c25-16e7-4665-848c-344e894fb4c5"
  }
};
