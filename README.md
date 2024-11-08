## Server/PC-side matching for R3xx/FPMxx/ZFMxx fingerprint sensors

### Windows
- C source file (tested previously with TDM-GCC)
- Equivalent Python 3 script (**32-bit interpreter required**)

### Linux
- C source file (tested on Ubuntu, gcc v9.30), dependent on [loadlibrary](https://github.com/taviso/loadlibrary).

This project is based on a poorly [documented](common/demo-board-api-manual-v23-2.pdf) DLL I found in some SDK which performs the actual matching.
There's been some basic testing on Windows (a while back anyways) and on Linux. The DLL's match results do reflect sensor results, though not identical scores.
Perhaps the algorithms are different, to better take advantage of a PC's power.

Use at your own risk.
