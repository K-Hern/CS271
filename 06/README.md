This is an assembler for Nand2tetris assembly code. These files end in the .asm extension. The assembler will translate these files into executable computer binary instructions. All tools required are included in this directory.


Notes:
The assembler follows many of the standards of the industry. Header files include definitions and other supplementary information, while .c, C, files contain the functions and “guts” of the systems.
The main.c file executes all commands and as the name suggests, is the main file, and is where the driver program is housed.


Instructions for use:


1) In your terminal open the directory and either compile with your preferred method, or simply type "make", and the included Makefile will execute its commands.
2) Once the program has compiled enter an assembly file to translate. This file should be of extension ".asm". The assembler will immediately create a file in the same directory, of the same name as the input, with the addition of a ".hack" extension. This is the program output and where you will find your translated code.
3) You may continue to enter as many files as you would like. Input repetition will continue to produce results, but will overwrite previously created output files of the same name and location.

