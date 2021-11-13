/*
 * pids
 * Paramater ID (PID) Structures
 */ 
 
#ifndef pids_h
#define pids_h
#include "Arduino.h"

#define NUM_PIDS 78

struct TPID {
 String _name;
 String _formula; 
 String _unit;
 byte _len;
 String _PID;
 String _format;
 bool _selected;
 String _MCI;  
 String _value;
 String _guid;
};

extern TPID PIDS[NUM_PIDS];

#endif
