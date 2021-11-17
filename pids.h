/*
 * pids
 * Paramater ID (PID) Structures
 */ 
 
#ifndef pids_h
#define pids_h
#include "Arduino.h"
#include "QList.h"
#include "io.h"


#define NUM_PIDS 77

struct TPID {
 String _name; // Long name
 String _shortname; // Short name
 String _formula; // formula
 String _unit; // unit type, RPM, V, MPH, ect
 byte   _len; // byte length, 0,1,2,4
 String _PID; // PID code to send to PCM, FFFF = FAKE PID
 String _format; // format/manipulate final output
 String _mci; // %varname% for this PID
 bool   _selected; // is this pid selected
 String _value; // value stored when scanned
 bool   _fake; // is this a fake pid
 bool   _duplicate; // is this a duplicate
 int    _dupeIndex; // if duplicate, what index to point to.
 String _CMD; // CMD to send to PCM when ready to scan
 String _guid; // Unique ID for this PID

 byte _blockID; // which block ID.. $fe, $fd, ect
 byte _blockPOS; // 0,1,2,3,4,5
 
};

extern TPID PIDS[NUM_PIDS];
extern QList<struct TPID> sPIDS;
extern byte currentBlock;

void printPIDS();
bool BuildPIDS();
String addpid(String PID, byte len, byte PID_Position);
int findspot(byte len, String PID);
void PopulateGrid();
void ClearBlocks();


#endif
