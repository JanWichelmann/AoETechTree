#pragma once
/*
--- AOE TECH TREE REPLACEMENT :: CODECAVE FUNCTIONS :: DEFINITIONS ---
*/

/* INCLUDES */

// Windows definitions
#ifndef NOMINMAX
#define NOMINMAX
#endif
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>

// C standard I/O functions
#include <cstdio>

/* ASSERTIONS */

// Assert that base types have the correct size (else very funny things will happen)
static_assert(sizeof(bool) == 1, "bool type has not 8 bit size");
static_assert(sizeof(char) == 1, "char type has not 8 bit size");
static_assert(sizeof(short) == 2, "short type has not 16 bit size");
static_assert(sizeof(int) == 4, "int type has not 32 bit size");

/* DEFINITIONS */

// Copies the given data to a given address.
// Parameters:
// -> destAddr: The address where the data should be copied to.
// -> data: The pointer to the data.
// -> byteCount: The length of the data to be copied (byte count).
void CopyBytesToAddr(DWORD destAddr, void *data, size_t byteCount);

// Replaces the virtual function table entry at the specified location by a pointer to the given wrapper function.
// Parameters:
// -> destAddr: The address where the entry should by replaced.
// -> func: The address of the replacement wrapper function.
void CreateVTableEntry(DWORD destAddr, void(*func)(void));

// Reads the virtual function table entry at the specified address.
// Parameters:
// -> addr: The address of the entry to be read.
DWORD ReadVTableEntry(DWORD addr);

// Creates a call for the given codecave function at the given destination address.
// Optionally after the call several NOPs can be inserted to overwrite damaged opcodes / functions.
// Parameters:
// -> destAddr: The address where the codecave call should be performed.
// -> func: The codecave function to be called.
// -> nopCount: The count of the NOPs to be inserted after the 5 CALL bytes.
void CreateCodecave(DWORD destAddr, void(*func)(void), size_t nopCount = 0);
