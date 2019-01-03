## Server/PC-side matching (in C) for R3xx/FPMxx/ZFMxx fingerprint sensors

This is based on a poorly documented DLL I found in the SDK which performs the actual matching.
Tested only on Windows but not thoroughly, though results are promising and almost
the same (in terms of fingerprint match scores) as those from the sensor itself. 

The DLL matching functions seem to accept only 256-byte arrays, which is consistent
with the typical 512-byte template that looks like it's simply two 256-byte templates concatenated.
This means that for matching, only first 256 bytes of a template are actually needed.

Use at your own risk and please let me know if you discover anything.
