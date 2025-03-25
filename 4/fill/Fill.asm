// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.

// Runs an infinite loop that listens to the keyboard input. 
// When a key is pressed (any key), the program blackens the screen,
// i.e. writes "black" in every pixel. When no key is pressed, 
// the screen should be cleared.

//while (true){
//	if (keyboard){
//		screen = black;
//	}else{
//		screen = white;
//	}
//}

	@0
	D=M
	@pressed
	M=D				//pressed = 0
	@SCREEN
	D=M
	@addr
	M=D				//addr = &screen
	
(LOOP)
	@KBD			
	D=M
	@BLKSCRN			
	D;JGT			//if key_is_pressed goto BLKSCRN
	@pressed
	D=M
	@CLRSCRN
	D;JLT			//if key_is_NOT-Pressed & pressed flag goto CLRSCRN
	@LOOP
	0;JMP
	
(BLKSCRN)
	@pressed
	D=M
	@LOOP
	D;JLT
	@pressed
	M=-1			//pressed = -1
	@IMAGE
	0;JMP
	
(CLRSCRN)
	@0
	D=M
	@pressed
	M=D				//pressed = 0
	
(IMAGE)
	@0
	D=A
	@word
	M=D				//word=0
	@8192
	D=A
	@n
	M=D				//n = 256 * 32 = 8192 (number of 16bit numbers for the whole screen)

(BLACK)
	@word
	D=M
	@n
	D=M-D			//n - word
	@LOOP
	D;JEQ			//if n == word goto LOOP
	@word
	D=M				
	M=D+1			//word = word + 1
	@SCREEN
	D=D+A			//A = &screen + word
	@addr
	M=D				//addr = next Pixel address
	@pressed
	D=M
	@addr
	A=M
	M=D			//Screen[A] = -1 = all 1's = all black
	@BLACK
	0;JMP			//goto BLACK

