## Server/PC-side matching for R3xx/FPMxx/ZFMxx fingerprint sensors

This is written in C and is based on a poorly documented DLL I found in the SDK which performs the actual matching.
It's been tested only on Windows but not thoroughly, though results are promising and almost
the same (in terms of fingerprint match scores) as those from the sensor itself. 

The DLL matching function seems to expect 256-byte arrays, and not the entire 512 bytes of a typical template,
as would be expected. But upon examining a regular 512-byte template from the sensor, it looks like
it's simply two 256-byte templates concatenated, each "sub-template" possibly from each stage of the enrollment.
If this is the case, then the arguments of the matching function make sense.
This means that for matching, only the first 256 bytes of a template are actually needed. This may
halve transfer times if you're sending templates over a network.

Use at your own risk.
