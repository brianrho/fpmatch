## Server/PC-side matching for R3xx/FPMxx/ZFMxx fingerprint sensors

There are C files (tested with TDM-GCC) and a Python 3 script. 
You can use the latter if you want to test quickly or don't mind that Python will be slower.
Just make sure the DLL is in the same directory as the Python script.

This project is based on a poorly documented DLL I found in the SDK which performs the actual matching.
It's been tested only on Windows but not thoroughly, though results are promising and nearly
the same (in terms of fingerprint match scores) as those from the sensor itself. 

The DLL matching function seems to expect 256-byte arrays, and not the entire 512 bytes of a typical template,
as would be expected. But upon examining a regular 512-byte template from the sensor, it looks like
it's simply two 256-byte templates concatenated, each "sub-template" likely from each stage of the enrollment.
If this is the case, then the arguments of the matching function make sense.
This means that for matching, only the first 256 bytes of a template are actually needed. This may
halve transfer times if you're sending templates over a network.

For questions regarding availability on Linux, check [here](https://github.com/brianrho/fpmatch/issues/1).

Use at your own risk.
