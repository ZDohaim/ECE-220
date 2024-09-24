;ziada2, yahme6, aliia2
;This program takes a string and counts how many times a character (non alphabet or alphabet) has been in the 
;string and adds it to a histogram which was given in 
;the code from the git hub, then we created a way to print out the histogram
; by first printing @ and then SPACE then converting the hex digit to decimal to print out properly
; The code given to you here implements the histogram calculation that 
; we developed in class.  In programming lab, we will add code that
; prints a number in hexadecimal to the monitor.
;
; Your assignment for this program is to combine these two pieces of 
; code to print the histogram to the monitor.
;
; If you finish your program, 
;    ** commit a working version to your repository  **
;    ** (and make a note of the repository version)! **


	.ORIG	x3000		; starting address is x3000


;
; Count the occurrences of each letter (A to Z) in an ASCII string 
; terminated by a NUL character.  Lower case and upper case should 
; be counted together, and a count also kept of all non-alphabetic 
; characters (not counting the terminal NUL).
;
; The string starts at x4000.
;
; The resulting histogram (which will NOT be initialized in advance) 
; should be stored starting at x3F00, with the non-alphabetic count 
; at x3F00, and the count for each letter in x3F01 (A) through x3F1A (Z).
;
; table of register use in this part of the code
;    R0 holds a pointer to the histogram (x3F00)
;    R1 holds a pointer to the current position in the string
;       and as the loop count during histogram initialization
;    R2 holds the current character being counted
;       and is also used to point to the histogram entry
;    R3 holds the additive inverse of ASCII '@' (xFFC0)
;    R4 holds the difference between ASCII '@' and 'Z' (xFFE6)
;    R5 holds the difference between ASCII '@' and '`' (xFFE0)
;    R6 is used as a temporary register
;

	LD R0,HIST_ADDR      	; point R0 to the start of the histogram
	
	; fill the histogram with zeroes 
	AND R6,R6,#0		; put a zero into R6
	LD R1,NUM_BINS		; initialize loop count to 27
	ADD R2,R0,#0		; copy start of histogram into R2

	; loop to fill histogram starts here
HFLOOP	STR R6,R2,#0		; write a zero into histogram
	ADD R2,R2,#1		; point to next histogram entry
	ADD R1,R1,#-1		; decrement loop count
	BRp HFLOOP		; continue until loop count reaches zero

	; initialize R1, R3, R4, and R5 from memory
	LD R3,NEG_AT		; set R3 to additive inverse of ASCII '@'
	LD R4,AT_MIN_Z		; set R4 to difference between ASCII '@' and 'Z'
	LD R5,AT_MIN_BQ		; set R5 to difference between ASCII '@' and '`'
	LD R1,STR_START		; point R1 to start of string

	; the counting loop starts here
COUNTLOOP
	LDR R2,R1,#0		; read the next character from the string
	BRz PRINT_HIST		; found the end of the string

	ADD R2,R2,R3		; subtract '@' from the character
	BRp AT_LEAST_A		; branch if > '@', i.e., >= 'A'
NON_ALPHA
	LDR R6,R0,#0		; load the non-alpha count
	ADD R6,R6,#1		; add one to it
	STR R6,R0,#0		; store the new non-alpha count
	BRnzp GET_NEXT		; branch to end of conditional structure
AT_LEAST_A
	ADD R6,R2,R4		; compare with 'Z'
	BRp MORE_THAN_Z         ; branch if > 'Z'

; note that we no longer need the current character
; so we can reuse R2 for the pointer to the correct
; histogram entry for incrementing
ALPHA	ADD R2,R2,R0		; point to correct histogram entry
	LDR R6,R2,#0		; load the count
	ADD R6,R6,#1		; add one to it
	STR R6,R2,#0		; store the new count
	BRnzp GET_NEXT		; branch to end of conditional structure

; subtracting as below yields the original character minus '`'
MORE_THAN_Z
	ADD R2,R2,R5		; subtract '`' - '@' from the character
	BRnz NON_ALPHA		; if <= '`', i.e., < 'a', go increment non-alpha
	ADD R6,R2,R4		; compare with 'z'
	BRnz ALPHA		; if <= 'z', go increment alpha count
	BRnzp NON_ALPHA		; otherwise, go increment non-alpha

GET_NEXT
	ADD R1,R1,#1		; point to next character in string
	BRnzp COUNTLOOP		; go to start of counting loop



PRINT_HIST

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
	

	LD R3, HIST_ADDR 	;STORE R0 (HISTOGRAM POINTER) IN R3 IN CASE R0 DOESNT HOLD HIST POINTER
	

	AND R5, R5, #0		;INIT REGISTER TO STORE CHARACTERS
	LD R5, AT 		; LOAD ‘@’ FILLED

	
PRINT	AND R0,R0,#0		;CLEAR R0
	ADD R0,R5,#0		; ADD R5 INTO R0

	OUT 			;PRINT

	;AND R0,R0,#0		; CLEAR R0
	LD R0, SPACE		;LOAD SPACE WHICH IS FILLED	
	OUT			;PRINT SPACE
;—---- 
	LD R3, HIST_ADDR	; LOAD PISTROGRAM POINTER
	LDR R2,R3, #0		; MAKE R2 HOLD THE VALUE OF THE HISTOGRAM POINTER
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
	BRzp SKIP1			;CHECK IF MSB IS -1
	
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

	BRn CHAR_LOOP 		; check this positivie or negative
	

;------
	
DONE1 	
	ADD R3,R3,#1		; INCREMENT HISTOGRAM POINTER
	ST R3,HIST_ADDR		; STORE HIST_ADDR TO 
	
	LD R0, NEW_LINE		;LOAD NEW_LINE
	OUT			;PRINT NEW_LINE
	ADD R5, R5, #1		; INCREMENTING @->A…
	LD R6, Z		; LOAD Z INTO R6
	NOT R6,R6 
	ADD R6,R6, #1  		; TWOS COMPLETENT 
	ADD R6, R5, R6		; CHECK IF AT Z
	BRz DONE		; DONE 

	BRnzp PRINT		;LOOP BACK TO PRINT TO PRINT OUT OTHER ALPHABETS


	AT		.FILL #64 
	SPACE		.FILL #32
	NEW_LINE	.FILL #10
	ZERO		.FILL x30 ; 48 in dec
	A		.FILL x41 ; 58
	Z		.FILL #91  





DONE	HALT			; done


; the data needed by the program
NUM_BINS	.FILL #27	; 27 loop iterations
NEG_AT		.FILL xFFC0	; the additive inverse of ASCII '@'
AT_MIN_Z	.FILL xFFE6	; the difference between ASCII '@' and 'Z'
AT_MIN_BQ	.FILL xFFE0	; the difference between ASCII '@' and '`'
HIST_ADDR	.FILL x3F00     ; histogram starting address
STR_START	.FILL x4000	; string starting address

; for testing, you can use the lines below to include the string in this
; program...
; STR_START	.FILL STRING	; string starting address
; STRING		.STRINGZ "This is a test of the counting frequency code.  AbCd...WxYz."



	; the directive below tells the assembler that the program is done
	; (so do not write any code below it!)

	.END



