;ziada2, yahme6, aliia2
;
;This program is a stack calculator which has different parts 
;EVALUATE: This subroutine for each input value (echo to screen), calls the push, pop, add, subtract, ;multiply, divide and power after evaluating if the value read from the memory is an operator or operand ;and if it is an operator, which kind. If the stack underflows or if after evaluating the whole expression the ;stack has more than one value, print "Invalid Expression" to the screen and halt.
;PUSH: This subroutine has been given to you.
;POP: This subroutine has been given to you.
;ADD: Adds the two operands.
;SUBTRACT: Performs subtraction.
;MULTIPLY: Performs multiplication.
;DIVIDE: Performs division. In case the division results in a remainder, just return the integer quotient. ;The input values will always be positive integers.
;POWER: Performs power operation. You may assume that the register storing the result will not overflow. The input values will always be positive integers.
;PRINT_HEX: This subroutine prints the output of the input expression in its hexadecimal representation, which was taken from mp1 and adapted to fit the code by changing the values of R3


; the registers changed a lot throughout the program, but in the end:
; R3: value found in the stack
; R5: also value found in the stack, requested by you guys 
; 
;
.ORIG x3000
	
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

	
	







;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;R0 - character input from keyboard
;R6 - current numerical output
;R2 TEMP REGISTER 
; R1 REGISTER TO STORE ' ' & ' = ' & '0'& '9' TO CHECK VALUE

EVALUATE

;your code goes here



;your code goes here

READ_NEXT

	GETC 		; GET INPUT FROM USER
	OUT			; OUTPUT SO USER CAN SEE WHAT WE OUTPUT


;CHECK EQUALS
	AND R2,R2,#0		; CLEAR R2 AS TEMP REG
	LD R1, EQUALS_SIGN 
	NOT R1,R1 
	ADD R1,R1,#1		;TWOS COMPLEMENT R1, TO SEE IF EQUALS
	ADD R2,R0,R1 		; ADD R0 AND R1 AND PLACE INTO R2
	BRz CHECK_STACK	; IF ZERO THEN IT’S EQUALS
	
;CHECK SPACE 
	AND R2,R2, #0 		;CLEAR R0 AGAIN 
	LD R1, SPACE_SIGN	; LOAD [SPACE] INTO R1
	NOT R1,R1		
	ADD R1,R1,#1		;TWOS COMPLEMENT  R1 
	ADD R2, R0,R1 	; CHECK IF R0 IS SPACE (R0 +R1)
	
	BRz READ_NEXT	; IF IT IS SPACE, CHECK NEXT  VALUE
	; check 0-9 
	LD R1, NINE 
	NOT R1,R1
	ADD R1,R1,#1		;TWOS COMPLEMENT
		
	AND R2,R2,#0
	ADD R2,R1,R0 		; SUBTRACT -R1+R0 (CHECK R2)
	BRp CHECK_OPERATOR
	
	LD R1, ZERO
	NOT R1,R1
	ADD R1,R1, #1	
	ADD R2, R0, R1	;R0-R1  CHECK IF R0 IS 0
	BRn CHECK_OPERATOR


;------ sub zero 
	LD R1, ZERO
	NOT R1,R1
	ADD R1,R1,#1 	;twos complement zero
	ADD R0, R0,R1 ; SUBTRACT ‘0’
	JSR PUSH	;IS THIS GOOD!?

	BRnzp READ_NEXT
	
; check operator checks if the entered value is the same through twos complementing and adding it to eachother and respectively going to whichever sign it found, 
; for example: if * then go to at_least_two_multiply
CHECK_OPERATOR 

;MULTIPLY SIGN
	LD R2, MULTIPLY_SIGN 
	NOT R2,R2
	ADD R2,R2,#1 
	ADD R2, R0, R2	
	BRz AT_LEAST_TWO_MULTIPLY
;PLUS SIGN 
	LD R2, PLUS_SIGN
	NOT R2,R2
	ADD R2,R2,#1 
	ADD R2, R0, R2	
	BRz AT_LEAST_TWO_PLUS
;MINUS SIGN 
	LD R2, MINUS_SIGN 
	NOT R2,R2
	ADD R2,R2,#1 
	ADD R2, R0, R2	
	BRz AT_LEAST_TWO_MINUS
; DIVIDE SIGN
	LD R2, DIVIDE_SIGN 
	NOT R2,R2
	ADD R2,R2,#1 
	ADD R2, R0, R2	
	BRz AT_LEAST_TWO_DIVIDE
;EXPONENT_SIGN
	LD R2, EXPONENT_SIGN 
	NOT R2,R2
	ADD R2,R2,#1 
	ADD R2, R0, R2	

BRz AT_LEAST_TWO_EXPONENT
	

PRINT_INVALID	

	LEA R0, INVALID	; PUT STRINGZ INTO R0
	PUTS 		; PRINT OUT USING PUTS INSTEAD OF OUT BECAUSE ITS A STRING
	BRnzp DONE	; HALT PROGRAM

INVALID .STRINGZ "Invalid Expression"

PRINT_HEX	

; you will need to insert your code to print the histogram here

; do not forget to write a brief description of the approach/algorithm
; for your implementation, list registers used in this part of the code,
; and provide sufficient comments
;R1 DIGIT COUNTER
;R2 DIGIT
;R3 HISTOGRAM POINTER
;R4 BIT COUNTER
;R5 TEMP REGISTER TO STORE LETTERS LIKE @, AND A AND Z
;MP1
	

	
	

	

	AND R0,R0,#0		; CLEAR R0
	LD R0, SPACE		;LOAD SPACE WHICH IS FILLED	
	OUT			;PRINT SPACE
;—---- 

	ADD R2,R3, #0		; MAKE R2 HOLD THE VALUE OF THE HISTOGRAM POINTER
	AND R4,R4,#0 		; INIT BIT COUNTER 
	ADD R4,R4,#-4		; MAKE BIT COUNTER -4
	
	AND R6,R6,#0 		; CHAR COUNTER 
	ADD R6,R6,#-4		;SET TO -4
	;AND R0,R0,#0 		; clear R0

CHAR_LOOP

	AND R4,R4,#0 		; INIT BIT COUNTER 
	ADD R4,R4,#-4		; MAKE BIT COUNTER -4
	AND R0, R0, #0		; CLEAR R0	
	

BIT_LOOP
	ADD R0, R0, R0
	ADD R2,R2,#0		;UPDATE R2 TO CHECK MSB
	BRzp SKIP1		;CHECK IF MSB IS -1
	
MSB	
	ADD R0,R0,#1		;ADD 1 TO R0 
	

SKIP1
	ADD R4,R4,#1 		; INCREMENT BIT COUNTER
	
	ADD R2,R2,R2 		; LEFT SHIFT
	
	ADD R4,R4,#0		; CHECK R4
	BRn BIT_LOOP 		; CHECK IF BIT LOOP DONE?
	
	ADD R0,R0,#-9		; CHECK IF LESS THAN 
	
	BRp LETTER		;BRANCH TO LETTER
	LD R1, ZERO		; LOAD ZERO TO R1
	
	ADD R0,R0,#9 		; ADD 9 BACK
	ADD R0,R0,R1 		; R0 + ZERO IN ASCII FOR OFFSET
	 
	BRnzp SKIP2 		; SKIP LETTER 

LETTER
	LD R1, A		; LOAD A TO R1
	ADD R1,R1,#-10		; SUBTRACT 10 FOR THE OFFSET
	ADD R0,R0,#9		;ADD THE 9 BACK 
	ADD R0,R0,R1		; ADD R1 TO R0 -> LETTER + (A-10)
SKIP2
	OUT 			;PRINT OUT 
	ADD R6,R6,#1		 ; INCREMENT CHAR COUNTER 	

	BRn CHAR_LOOP 		; check this positive or negative
	

;------
			;
	
	;LD R5, SOMETHING_ELSE ; WAS SUPPOSED TO BE TEMP REGISTER BUT DID NOT WORK
	BRnzp DONE		; DONE 
	
DONE 	HALT ; END PROGRAM

;;;;;;;;;;;;;;;;;;;;
	
;ALL THE AT_LEAST_TWO_X DOES THE SAME THING, SUBTRACT STACK TOP FRROM STACK START AND CHECK IF ITS 2 OR MORE USING TWOS COMPLEMENT THEN IF IT HAS TWO GO TO  
;HAS_TWO_X IF NOT PRINT INVALID.

AT_LEAST_TWO_MULTIPLY



	LD R1,STACK_TOP	; LD STACK_TOP R1
	LD R6, STACK_START ; LD STACK_START

	NOT R1,R1	
	ADD R1,R1,#1	;TWOS COMPLEMENT STACK TOP
	ADD R6,R6,R1 	; R6 - R1 SUB STACK TOP FROM STACK START
	AND R1,R1,#0	; CLEAR R1
	ADD R1,R1, #-2	; SET R1 TO -2
	ADD R6,R6,R1	; R6 -2 
	BRzp HAS_TWO_MULT ; IF ZERO OR POSITIVE THEN THE STACK HAS TWO OR MORE
	BRnzp PRINT_INVALID


	AT_LEAST_TWO_PLUS
	LD R1,STACK_TOP
	LD R6, STACK_START

	NOT R1,R1	
	ADD R1,R1,#1	;TWOS COMPLEMENT
	ADD R6,R6,R1 ; R6 - R1
	AND R1,R1,#0	; CLEAR R1
	ADD R1,R1, #-2	; SET R1 TO -2
	ADD R6,R6,R1	; R6 -2 
	BRzp HAS_TWO_PLUS ; IF ZERO OR POSITIVE THEN THE STACK HAS TWO OR MORE
	BRnzp PRINT_INVALID

	AT_LEAST_TWO_MINUS
	LD R1,STACK_TOP
	LD R6, STACK_START

	NOT R1,R1	
	ADD R1,R1,#1	;TWOS COMPLEMENT
	ADD R6,R6,R1 ; R6 - R1
	AND R1,R1,#0	; CLEAR R1
	ADD R1,R1,#-2	; SET R1 TO -2
	ADD R6,R6,R1	; R6 -2 
	BRzp HAS_TWO_MINUS ; IF ZERO OR POSITIVE THEN THE STACK HAS TWO OR MORE
	BRnzp PRINT_INVALID

	AT_LEAST_TWO_DIVIDE
	LD R1,STACK_TOP
	LD R6, STACK_START

	NOT R1,R1	
	ADD R1,R1,#1	;TWOS COMPLEMENT
	ADD R6,R6,R1 ; R6 - R1
	AND R1,R1,#0	; CLEAR R1
	ADD R1,R1, #-2	; SET R1 TO -2
	ADD R6,R6,R1	; R6 -2 
	BRzp HAS_TWO_DIVIDE ; IF ZERO OR POSITIVE THEN THE STACK HAS TWO OR MORE
	BRnzp PRINT_INVALID

AT_LEAST_TWO_EXPONENT

	LD R1,STACK_TOP
	LD R6, STACK_START
	NOT R1,R1	
	ADD R1,R1,#1	;TWOS COMPLEMENT
	ADD R6,R6,R1 ; R6 - R1
	AND R1,R1,#0	; CLEAR R1
	ADD R1,R1, #-2	; SET R1 TO -2
	ADD R6,R6,R1	; R6 -2 
	BRzp HAS_TWO_EXPONENT ; IF ZERO OR POSITIVE THEN THE STACK HAS TWO OR MORE
	BRnzp PRINT_INVALID

;ALL THE .FILLS ARE HERE SINCE WE GOT AN ERROR THAT IT WAS OUT OF RANGE
POP_SaveR3		.BLKW #1	;
POP_SaveR4		.BLKW #1	;
STACK_END		.FILL x3FF0	;
STACK_START		.FILL x4000	;
STACK_TOP		.FILL x4000	;
SAVE_R7			.FILL x5000
SAVE_R4			.FILL x5001
SAVE_R3			.FILL x5002

EXPONENT_SIGN	 .FILL #94
PLUS_SIGN 		 .FILL #43
DIVIDE_SIGN		 .FILL #47
MINUS_SIGN		.FILL #45
MULTIPLY_SIGN 	.FILL #42 	; FILL MULTIPLY SIGN WITH “  *  ”
EQUALS_SIGN 	.FILL #61 ; FILL EQUALS SIGN WITH ‘=’
SPACE_SIGN 		.FILL #32 ; FILL SPACE_SIGN WITH ‘[SPACE] ‘
;SOMETHING_ELSE 	.BLKW #1

AT				.FILL #64 
SPACE			.FILL #32
NEW_LINE		.FILL #10
ZERO			.FILL x30 ; 48 in dec
A				.FILL x41 ; 58
Z				.FILL #91 
NINE 			.FILL x39 	
; ALL THE HAS TWO DOES THE SAME THING, POP AND PLACE INTO R4 THEN POP AGAIN AND PLACE INTO R3 
; AFTER THAT GO TO THE RESPECTIVE OPERATION, e.g. MULT 
HAS_TWO_MULT

	JSR POP 		; POP, GET VALUE IN R0
	AND R4,R4,#0	;CLEAR R4
	ADD R4,R0,#0	; PLACE R0 INTO R4
	JSR POP			; POP AGAIN
	AND R3,R3,#0	; CLEAR R3
	ADD R3,R0,#0 	;PLACE R0 INTO R3
	JSR MUL

; RET FROM JSR PLUS THEN PUSH
	JSR PUSH		; AFTER RET PUSH RESULT INTO STACK

	BRnzp READ_NEXT	; READ NEXT VALUE 

HAS_TWO_PLUS

	JSR POP 
	AND R4,R4,#0
	ADD R4,R0,#0	
	JSR POP
	AND R3,R3,#0
	ADD R3,R0,#0 	
	JSR PLUS

; RET FROM JSR PLUS THEN PUSH
	JSR PUSH

	BRnzp READ_NEXT

	HAS_TWO_MINUS
	JSR POP 
	AND R4,R4,#0
	ADD R4,R0,#0	
	JSR POP
	AND R3,R3,#0
	ADD R3,R0,#0 	
	JSR MIN

; RET FROM JSR PLUS THEN PUSH
	JSR PUSH

	BRnzp READ_NEXT

	HAS_TWO_DIVIDE

	JSR POP 
	AND R4,R4,#0
	ADD R4,R0,#0	
	JSR POP
	AND R3,R3,#0
	ADD R3,R0,#0 	
	JSR DIV

; RET FROM JSR PLUS THEN PUSH
	JSR PUSH

	BRnzp READ_NEXT

	HAS_TWO_EXPONENT
	JSR POP 
	AND R4,R4,#0
	ADD R4,R0,#0	
	JSR POP
	AND R3,R3,#0
	ADD R3,R0,#0 	
	JSR EXP 

; RET FROM JSR PLUS THEN PUSH
	JSR PUSH

	BRnzp READ_NEXT

	CHECK_STACK
; CHECK STACK CHECKS IF THERE IS ONE VALUE IN STACK TO SEE IF WE ARE DONE AFTER = SIGN IS FOUND
	LD R1,STACK_TOP		
	LD R6, STACK_START
	NOT R1,R1	
	ADD R1,R1,#1	;TWOS COMPLELEMNT
	ADD R6,R6,R1 ; R6 - R1 STACK TOP - STACK START TO SEE HOW MANY VALUES ARE IN STACK
	AND R1,R1,#0	; CLEAR R1
	ADD R1,R1, #-1	; SET R1 TO -1	
	ADD R6,R6,R1	; R6 -1 TO SEE IF ITS -1
	BRnp PRINT_INVALID

	JSR POP 	; POP
	ADD R3,R0,#0	; PLACE RESULT IN R3
	ADD R5, R0, #0	; PLACE RESULT IN R5


	;ST R5, SOMETHING_ELSE
	BRnzp PRINT_HEX ; should it be jsr?


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
	PLUS	
	ADD R0, R3, R4	;adds the values stored in r3 and r4 and stores in r0
	RET	
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
MIN	
	AND R0,R0,#0 ; INIT R0
	NOT R4,R4 ; NOT R4
	ADD R4,R4, #1 ; TWO'S COMPLEMENT OF R4
	ADD R3, R3, R4 ; SUBTRACT R3 AND R4
	ADD R0, R3, #0 ; LOAD R3 INTO R0, does this work!? Should it be add!?
	RET

;your code goes here
	
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0


MUL	
	AND R0, R0, #0			; INITIALIZING REGISTER
	MULT_LOOP
	ADD R0, R0, R3		;adding r3 to r0, r0 is the summation register
	ADD R4, R4,#-1		;r4 is the counting register, it is being decremented.
	BRz	MULT_DONE		;when r4 is 0, the number has been multiplied
	ADD R4,R4,#0 			; TO BE SAFE, UPDATE
	BRnp 	MULT_LOOP		;if r4 is positive, more summations are to be carried out

	MULT_DONE 			
	RET
	

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
DIV	

	AND R0,R0,#0 ;  INIT R0
	NOT R4,R4     ; NOT R4
	ADD R4,R4, #1 ; TWO’S COMPLEMENT OF R4
	DIVIDE 
	ADD R3,R3,R4 ; ADD NEGATIVE R4 TO R3
	BRn DIVIDE_DONE
	ADD R0,R0,#1 ; COUNT HOW LONG IT TAKES TO DIVIDE R3 BY R4
	BRp DIVIDE

	DIVIDE_DONE
	RET		; RETURN

;your code goes here
	
	
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0


;2^3 = 8


EXP 

	ST R7, SAVE_R7
	ST R3, SAVE_R3	; HOW TO DO THIS!?
	ST R4, SAVE_R4	;Storing r4 because it will be changed

	ADD R4, R3, #0		;storing r3 in r4 so that r3 can be mult. By itself 
	AND R0, R0, #0 	
	AND R1, R1, #0		;R1 is the register that contains the summation for EXP
	LD R6, SAVE_R4 	; R6 HOLDS EXPONENT VALUE (3 IN THIS CASE)  

EXP_LOOP 	
	ADD R6, R6, #-1 	;0
	BRz 	EXP_DONE	;FIGURE OUT WHAT TO DO HERE

	BRn 	EXP_ZERO	; R6 -1 = -1 
	JSR MUL 		;8
	ADD R1, R1, R0 	;R0 summation register for MULT, add it to register FOR EXP
	ADD R6,R6,#0		;

	BRp 	EXP_LOOP


EXP_DONE	 
		ADD R0,R1,#0 		;STORE R0 IN R1 
		LD R7, SAVE_R7
RET



EXP_ZERO	;CHECK IF THIS X^0, IF 0 THEN PRINT 1
	AND R1,R1,#0
	ADD R1, R1,#1		; SET R1 TO 1
	BRnzp EXP_DONE

	
;IN:R0, OUT:R5 (0-success, 1-fail/overflow)
;R3: STACK_END R4: STACK_TOP
;
PUSH	
	ST R3, PUSH_SaveR3	;save R3
	ST R4, PUSH_SaveR4		;save R4
	AND R5, R5, #0			;
	LD R3, STACK_END	 	;
	LD R4, STACk_TOP		;
	ADD R3, R3, #-1		;
	NOT R3, R3			;
	ADD R3, R3, #1			;
	ADD R3, R3, R4		;
	BRz OVERFLOW		;stack is full
	STR R0, R4, #0			;no overflow, store value in the stack
	ADD R4, R4, #-1		;move top of the stack
	ST R4, STACK_TOP		;store top of stack pointer
	BRnzp DONE_PUSH		;
OVERFLOW
	ADD R5, R5, #1			;
DONE_PUSH
	LD R3, PUSH_SaveR3		;
	LD R4, PUSH_SaveR4		;
	RET


PUSH_SaveR3	.BLKW #1		;
PUSH_SaveR4	.BLKW #1 		;


;OUT: R0, OUT R5 (0-success, 1-fail/underflow)
;R3 STACK_START R4 STACK_TOP
;
POP	
	ST R3, POP_SaveR3		;save R3
	ST R4, POP_SaveR4		;save R3
	AND R5, R5, #0			;clear R5
	LD R3, STACK_START		;
	LD R4, STACK_TOP		;
	NOT R3, R3			;
	ADD R3, R3, #1			;
	ADD R3, R3, R4		;
	BRz UNDERFLOW		;
	ADD R4, R4, #1			;
	LDR R0, R4, #0			;
	ST R4, STACK_TOP		;
	BRnzp DONE_POP		;
UNDERFLOW
	ADD R5, R5, #1			;
DONE_POP
	LD R3, POP_SaveR3		;
	LD R4, POP_SaveR4		;
	RET	




.END







