gforth_translate
================
To run:
	./translator < proftest.in > proftest.out

If it it successful it will output the gforth code into proftest.out
and no messages will be generated. If it does not parse correctly,
then there will be error messages and the program will terminate.

The *.out file may then be loaded and run in gforth with something like:
gforth < proftest.out
