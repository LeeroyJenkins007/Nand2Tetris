// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.

// Multiplies R0 and R1 and stores the result in R2.
// (R0, R1, R2 refer to RAM[0], RAM[1], and RAM[2], respectively.)
// The algorithm is based on repetitive addition.

//pseudo
//int n = 0;
//int adder = 0;
//if (R0 > R1){
//	n = R1;
//	adder = R0;
//}else{
//	n = R0;
//	adder = R1;
//}
//int sum = 0;
//for (int i = 1; i <= n,; i++){
//	sum = sum + adder;
//}

	@0
	D=A
	@R2
	M=D
	@i
	M=D			//i = 0
	@R0
	D=M			//D = R0
	@R1
	D=D-M		//D = R0 - R1
	@BIGGER
	D;JGT			//if R0 > R1 goto BIGGER
	
	@R0
	D=M
	@n
	M=D			//n = R0
	@R1
	D=M
	@adder
	M=D			//adder = R1
	@LOOP
	0;JMP			//goto LOOP
	
(BIGGER)
	@R1
	D=M
	@n
	M=D			//n = R1
	@R0
	D=M
	@adder
	M=D			//adder = R0
	
(LOOP)
	@i
	D=M
	@n
	D=D-M
	@END
	D;JEQ			//if i == n goto END
	@adder
	D=M			//D = adder
	@R2
	M=D+M		//R2 = R2 + adder
	@i
	M=M+1		//i++
	@LOOP
	0;JMP			//return to top of LOOP
	
(END)
	@END
	0;JMP
	
	