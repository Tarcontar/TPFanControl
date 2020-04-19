
// --------------------------------------------------------------
//
//  Thinkpad Fan Control
//
// --------------------------------------------------------------
//
// The original TPFanControl code is in public domain. See this fork for public domain code:
// https://github.com/cjbdev/TPFanControl
// All my own patches are licensed under GNU GPL v3 license. See notice below and LICENSE file for details.
//
// Copyright (c) Stanislav Vinokurov, 2020
//
// This program is free software : you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program.If not, see < https://www.gnu.org/licenses/>.// 
//
// --------------------------------------------------------------

#include "_prec.h"
#include "fancontrol.h"
#include "winio.h"


// Registers of the embedded controller
#define EC_DATAPORT		0x62	// EC data io-port
#define EC_CTRLPORT		0x66	// EC control io-port


// Embedded controller status register bits
#define EC_STAT_OBF		0x01    // Output buffer full 
#define EC_STAT_IBF		0x02    // Input buffer full 
#define EC_STAT_CMD		0x08    // Last write was a command write (0=data) 


// Embedded controller commands
// (write to EC_CTRLPORT to initiate read/write operation)
#define EC_CTRLPORT_READ		(char)0x80	
#define EC_CTRLPORT_WRITE		(char)0x81
#define EC_CTRLPORT_QUERY		(char)0x84





int verbosity= 0;	// verbosity for the logbuf (0= nothing)
const size_t logbuf_n = 8192;
char lasterrorstring[256]= "",
	 logbuf[logbuf_n]= "";


