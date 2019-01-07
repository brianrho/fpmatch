## Server/PC-side matching for R3xx/FPMxx/ZFMxx fingerprint sensors

This is written in C and is based on a poorly documented DLL I found in the SDK which performs the actual matching.
It's been tested only on Windows but not thoroughly, though results are promising and almost
the same (in terms of fingerprint match scores) as those from the sensor itself. 

The DLL matching function seems to expect 256-byte arrays, and not the entire 512 bytes of a typical template,
as might be expected. But upon examining a regular 512-byte template from the sensor, it looks 
it's simply two 256-byte templates concatenated, each of them possibly from each stage of the enrollment.
So the inputs of the matching function seem consistent with this assumption.
This means that for matching, only the first 256 bytes of a template are actually needed. This may
halve transfer times if you're sending templates over a network.

Use at your own risk.
