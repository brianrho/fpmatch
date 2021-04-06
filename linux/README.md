## Build steps

* Clone `loadlibrary` from [here](https://github.com/taviso/loadlibrary) -- perhaps into a directory right next to your clone of `fpmatch`.
* Install (with `apt` or whatever) the dependencies listed in the `loadlibrary` README, for your particular flavour of Linux. 
You **don't** need to download the antimalware engine mpam stuff, only concern yourself with the libraries in the table (and some of those may not even be necessary).
* Now returning to *this* directory, in the Makefile, supply the path to your `loadlibrary` clone in the `LOADLIBRARY_DIR` variable.
* Run `make` from here.
* If your build is successful, an executable `fpmatch` should've now be available here, which you can run with `./fpmatch` to get the default matching results and confirm your setup works.