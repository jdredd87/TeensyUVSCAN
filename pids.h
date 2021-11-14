/*
 * pids
 * Paramater ID (PID) Structures
 */ 
 
#ifndef pids_h
#define pids_h
#include "Arduino.h"

#define NUM_PIDS 78

struct TPID {
 String _name; // Long name
 String _shortname; // Short name
 String _formula; // formula
 String _unit; // unit type, RPM, V, MPH, ect
 byte   _len; // byte length, 0,1,2,4
 String _PID; // PID code to send to PCM, FFFF = FAKE PID
 String _format; // format/manipulate final output
 bool   _selected; // is this pid selected
 String _MCI; // %varname% for this PID
 String _value; // value stored when scanned
 bool   _fake; // is this a fake pid
 bool   _duplicate; // is this a duplicate
 int    _dupeIndex; // if duplicate, what index to point to.
 String _CMD; // CMD to send to PCM when ready to scan
 String _guid; // Unique ID for this PID
};

extern TPID PIDS[NUM_PIDS];

#endif
