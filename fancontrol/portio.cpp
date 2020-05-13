// --------------------------------------------------------------
//
//  Thinkpad Fan Control
//
// --------------------------------------------------------------
//
//  This program and source code is in the public domain.
//
//  The author claims no copyright, copyleft, license or
//  whatsoever for the program itself (with exception of
//  WinIO driver).  You may use, reuse or distribute it's 
//  binaries or source code in any desired way or form,  
//  Useage of binaries or source shall be entirely and 
//  without exception at your own risk. 
// 
// --------------------------------------------------------------

#include "_prec.h"
#include "fancontrol.h"
#include "TVicPort.h"

// Registers of the embedded controller
constexpr auto EC_DATAPORT = 0x1600; // EC data io-port 0x62
constexpr auto EC_CTRLPORT = 0x1604; // EC control io-port 0x66

// Embedded controller status register bits
constexpr auto EC_OUTPUT_BUFF_FULL = 0x01;
constexpr auto EC_INPUT_BUFF_FULL = 0x02;
constexpr auto EC_STAT_CMD = 0x08; // Last write was a command write (0=data)

// Embedded controller commands
// (write to EC_CTRLPORT to initiate read/write operation)
constexpr auto EC_CTRLPORT_READ = (char)0x80;
constexpr auto EC_CTRLPORT_WRITE = (char)0x81;
constexpr auto EC_CTRLPORT_QUERY = (char)0x84;


const int trys = 100;
const int iTick = 10;
int logbuf_verbosity = 1;
char lasterrorstring[256] = "",
logbuf[8192] = "";


int WaitForEmptyBuffers()
{
    int i = 0;
    char data = -1;

    do
    {
        data = (char)ReadPort(EC_CTRLPORT) & 0xff;
        if (i++ >= trys) return 0;
        ::Sleep(iTick);
    } while (data & (EC_INPUT_BUFF_FULL | EC_OUTPUT_BUFF_FULL));

    return data;
}

int WaitForEmptyOutputBuffer()
{
    int data = -1;
    int i = 0;

    do
    {
        data = (char)ReadPort(EC_CTRLPORT) & 0xff;
        if (i++ == trys) return 0;
        ::Sleep(iTick);
    } while (data & EC_OUTPUT_BUFF_FULL);

    return 1;
}

void SetReadPosition(int port, int position = EC_CTRLPORT_READ)
{
    WritePort(port, position);
}

void SetWritePosition(int port, int position)
{
    WritePort(port, position);
}

int PortReady()
{
    SetReadPosition(EC_CTRLPORT);
    int data = WaitForEmptyBuffers();
    if (data & EC_OUTPUT_BUFF_FULL) ReadPort(EC_DATAPORT);
    return WaitForEmptyBuffers();
}

int WaitForFullOutputBuffer()
{
    int data = -1;
    int i = 0;

    do
    {
        data = (char)ReadPort(EC_CTRLPORT) & 0xff;
        if (i++ == trys * 10) return 0;
        ::Sleep(iTick);
    } while (!(data & EC_OUTPUT_BUFF_FULL));

    return 1;
}

int FANCONTROL::ReadByteFromEC(int offset, char* pdata)
{
    int data = PortReady();
    if (!data) return 0;

    SetReadPosition(EC_DATAPORT, offset);

    if (!(data & EC_OUTPUT_BUFF_FULL) && !WaitForFullOutputBuffer()) return -1;

    *pdata = ReadPort(EC_DATAPORT);

    //if (logbuf_verbosity > 0) sprintf(logbuf + strlen(logbuf), "readec: offset= %x, data= %02x\n", offset, *pdata);
    return 1;
}

int FANCONTROL::WriteByteToEC(int offset, char NewData)
{
    WaitForEmptyBuffers();
    if (!WaitForEmptyOutputBuffer())
    {
        return 0;
    }
    //if (!PortReady()) return 0;

    WritePort(EC_CTRLPORT, EC_CTRLPORT_WRITE);
    WaitForEmptyBuffers();

    SetWritePosition(EC_DATAPORT, offset);

    /*if (!WaitForEmptyBuffers())
    {
        return 0;
    }*/

    WritePort(EC_DATAPORT, NewData);

    return 1;
}