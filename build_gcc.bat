setlocal
SET outDir=./gccOut
mkdir %outDir%

gcc --static -Wall -DF_INTERRUPTS=10000 irmp-main-analyze.c -o %outDir%/irmp-10kHz.exe
gcc -Wall -DF_INTERRUPTS=11718 irmp-main-analyze.c -o %outDir%/irmp-11718Hz
gcc -Wall -DF_INTERRUPTS=15000 irmp-main-analyze.c -o %outDir%/irmp-15kHz
gcc -Wall -DF_INTERRUPTS=20000 irmp-main-analyze.c -o %outDir%/irmp-20kHz

