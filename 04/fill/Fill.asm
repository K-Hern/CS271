// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/04/Fill.asm

// Runs an infinite loop that listens to the keyboard input.
// When a key is pressed (any key), the program blackens the screen,
// i.e. writes "black" in every pixel;
// the screen should remain fully black as long as the key is pressed. 
// When no key is pressed, the program clears the screen, i.e. writes
// "white" in every pixel;
// the screen should remain fully clear as long as no key is pressed.

// Put your code here.

(LOOP)

@24575
D=A
@screen_block 		//Initializing screen_block to contain 24,575 (Last Screen Pixel)
M=D

@8192
D=A
@i_remain		//Initializing i_remain to contain 8192 (number of pixels (-1's) within screen)
M=D



@KBD
D=M

@SET_D_BLACK
D;JNE		//Checking to see if KBD Input is still 0; and checking again


@input
M=0

@FILL_LOOP
D;JEQ


(SET_D_BLACK)

@input
M=-1		//Setting D to -1 if key pressed, or 0 if not




(FILL_LOOP)	//Start of Screen Fill Loop

@input
D=M

@screen_block
A=M

//@A - Setting A to Contents of screen_block
M=D


@screen_block
D=M
@1
D=D-A
@screen_block		//Decrementing screen_block by 1
M=D


@i_remain
D=M
@1
D=D-A
@i_remain		//Decrementing i_remain by 1
M=D


@FILL_LOOP		//Checking to see if screen is filled & exiting if true
D;JNE


@LOOP
0;JMP