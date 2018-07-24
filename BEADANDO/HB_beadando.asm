INCLUDE Irvine32.inc

; Harmat Bálint
; DX3MYV
; L. Assembly Programozás lab. gyak
;
; 30. Labirintus feladat
;
; Input:	a labirintus egy tömbben, az adatszegmensben.
;			a labirintus szélessége (tömb oszlopainak száma) és a labirintus teljes területe (tömb elemeinek száma)
; Output: az ágens minden lépése után kirajzolódik a konzolra az aktuális labirintus állapot.
;	Output értelmezése: fehér tömör téglalap	= fal
;						a						= ágens
;						e						= a labirintus kijárata ("end")
;						1						= olyan mezõ, melyen az ágens már járt egyszer
;						2						= olyan mezõ, melyen az ágens másodszor lép át, vagy
;												melyen visszafordult egy zsákutcából.
;
; Ha az inputban nincs ágens, hiba üzenetet dob.
; Ha az inputban nincs exit mezõ, akkor az ágens vissza talál a kiindulási pontba.
;
; A végsõ állapotban az 1-esekkel jelölt mezõk sorozata egy egyértelmû korrket utat mutat.

.data
	
	agentErrorString	BYTE	'Error, no agent start position specified in input ("a").', 0ah, 0
	newStepString		BYTE	' step', 0

	agentX	WORD	0
	agentY	WORD	0

	north	BYTE	"w"
	east	BYTE	"w"
	south	BYTE	"w"
	west	BYTE	"w"

	NORTHPOSITION	BYTE	0
	EASTPOSITION	BYTE	0
	SOUTHPOSITION	BYTE	0
	WESTPOSITION	BYTE	0


	color			BYTE	white
	backgroundColor	BYTE black

	wall	BYTE	"w"
	floor	BYTE	" "
	GOAL	BYTE	"e"		; SUPPOSED TO BE END, BUT IT IS A USED KEYWORD BY THE LANGUAGE....
	agent	BYTE	"a"
	first	BYTE	"1"
	second	BYTE	"2"

	direction		SBYTE	0 ; SIGNED -MAZEHEIGHT=NORTH 1=EAST MAZEHEIGHT=SOUTH -1=WEST
	currentPosition	BYTE	0 ; UNSIGNED
	plannedPosition BYTE	0 ; UNSIGNED
	lastPositIon	BYTE	0 ; UNSIGNED
	currentMark		BYTE	0 ; THE MARK UNDER OUR CURRENT POSITION
	FIRSTPATHS		BYTE	0 ; UNSIGNED, THE NUMBER OF POSSIBLE FIRSTPATHS (1 MEANS IT IS A HALLWAY...)
	MARKLEVEL		BYTE	1 ; TO KEEP TRACK IF WE SHOULD USE FIRST, OR SECOND MARK..
	GAMEOVER		BYTE	0 ; IF THIS IS SET TO 1, WE REACHED THE END OR A DEADLOCK.

	mazeWidth	WORD	11
	mazeSize	WORD	121
	MAZEHEIGHT	WORD	? ; CALCULATED AT INIT...
	
	maze	BYTE "w", "w", "w", "w", "w", "w", "w", "w", "w", "w", "w"
			BYTE "w", " ", " ", " ", "w", " ", " ", " ", " ", " ", "w"
			BYTE "w", " ", "w", "w", "w", " ", "w", "w", "w", " ", "w"
			BYTE "w", " ", " ", " ", "w", " ", " ", " ", " ", " ", "w"
			BYTE "w", " ", "w", " ", "w", "w", "w", " ", "w", "w", "w"
			BYTE "w", " ", "w", " ", " ", " ", " ", " ", "w", " ", "w"
			BYTE "w", " ", "w", " ", "w", "w", "w", " ", "w", " ", "e"
			BYTE "w", " ", " ", " ", " ", " ", " ", " ", " ", " ", "w"
			BYTE "w", " ", "w", "w", "w", " ", "w", "w", "w", "w", "w"
			BYTE "w", " ", " ", " ", " ", " ", " ", " ", " ", " ", "w"
			BYTE "w", "w", "w", "w", "w", "w", "w", "w", "a", "w", "w"


.code

;-------------------------------------------------------------------------------
;	Main function, initializes the game, and contains the main gameloop

main proc

	; initialize the board
	CALL		DrawMaze
	CALL		CRLF

	; calculate mazeheight
	MOVZX EAX, MAZESIZE
	CDQ
	DIV MAZEWIDTH
	XCHG AX, MAZEHEIGHT

	; find the agent starting position
	MOVZX ECX, mazeSize
	L3:		
		MOV		EDX, ECX
		MOVZX	EBX, mazeSize
		SUB		EBX, EDX
		MOVZX	EAX,  [maze + EBX]
		MOVZX	EDX,	agent
		CMP		EAX, EDX
		JE agentFound		
	LOOP L3
		MOV EDX, OFFSET AGENTERRORSTRING
		CALL CRLF
		CALL WRITESTRING
		JMP ENDSTATE
	; set staring agent coordinates
	agentFound:
		MOV EAX, EBX ; itt EBX = hanyadik mezoben vagyunk...
		XCHG AL, CURRENTPOSITION

	; main loop
	MOVZX EAX, MAZESIZE
	MOVZX EDX, MAZESIZE
	ADD EDX, EAX
	MOV ECX, EDX ; THE ALGORITHM SHOULD NEVER TAKE MORE STEPS THAN THE SQUARE OF A 2D MAZE SIZE
	ADD EDX, 1
	mainLoop:
		PUSH EDX
		PUSH ECX
		CALL CHECKSURROUNDINGS
		CALL DRAWMAZE
		POP ECX
		POP EDX
		XCHG EAX, EDX
		MOV EDX, OFFSET NEWSTEPSTRING
		CALL CRLF
		CALL WRITESTRING
		XCHG EAX, EDX
		MOV EAX, EDX
		SUB EAX, ECX
		CALL WRITEINT
		CALL CRLF
		CMP GAMEOVER, 1
			JE ENDSTATE
	LOOP mainLoop
	; end of main loop

	ENDSTATE:
	INVOKE	ExitProcess,0
main endp

;!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
;	Function to execute MOVE 
;	
MOVE	PROC

	MOV AL, CURRENTPOSITION
	MOV LASTPOSITION, AL
	MOVZX EAX, PLANNEDPOSITION
	MOV BL, AGENT
	XCHG BL, [MAZE + EAX]
	XCHG AL, CURRENTPOSITION
	RET

MOVE	ENDP

;!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
;	Function to MARK THE CURRENT POSITION
;	
MARK	PROC

	MOVZX EAX, CURRENTPOSITION
	CMP MARKLEVEL, 1
	JNE MARKLEVEL2
		MOV BL, FIRST
		JMP	SETMARK
	MARKLEVEL2:
		MOV BL, SECOND
	SETMARK:
	XCHG BL, [MAZE + EAX]
	MOV MARKLEVEL, 1
	RET

MARK ENDP

;!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
;	Function to CALCULATE 2D ARRAY INDEX 
;	
GETINDEX	PROC

	MOV EAX, 0
	MOV AX, AGENTY
	MUL MAZEWIDTH
	ADD AX, AGENTX

	RET

GETINDEX ENDP

;!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
;	Function to CALCULATE agentX and agentY values from EAX 
;	
GETXY	PROC

		MOV EDX, 0
		DIV mazeWidth	; ezutan AX-ben hogy hanyadik sor, DX-ben hogy hanyadik oszlop
		MOV agentX, DX
		MOV agentY, AX
	
		RET
GETXY ENDP

;!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
;	Function to check surroundings
;	
CheckSurroundings	PROC

	MOV FIRSTPATHS, 0

	MOVZX EAX, CURRENTPOSITION
	CALL GETXY

	;check north
	MOV AL, wall
	XCHG AL, north ; base assumption, there is a wall to the north...
	MOVZX EAX, agentY
	CMP EAX, 0
	JE northBorder ; if the north side is the maze border, jump over setting it, and leave it as a wall..
	SUB EAX, 1
	MUL mazeWidth
	ADD AX, agentX
	MOV PLANNEDPOSITION, AL
	MOV NORTHPOSITION, AL
	MOV AL, [maze + EAX]
	XCHG AL, north
	northBorder:

	;check east
	MOV AL, wall
	XCHG AL, east ; base assumption, there is a wall to the east...
	MOVZX EAX, agentX
	MOVZX EDX, mazeWidth
	SUB EDX, 1
	CMP EAX, EDX
	JE eastBorder ; if the east side is the maze border, jump over setting it, and leave it as a wall..
	ADD EAX, 1
	MOV EBX, EAX
	MOVZX EAX, agentY
	MUL mazeWidth
	ADD EAX, EBX
	MOV PLANNEDPOSITION, AL
	MOV EASTPOSITION, AL
	MOV AL, [maze + EAX]
	XCHG AL, EAST
	eastBorder:

	;CHECK SOUTH
	MOV AL, wall
	XCHG AL, SOUTH ; base assumption, there is a wall to the SOUTH...
	MOVZX EAX, agentY
	MOVZX EDX, mazeWidth
	SUB EDX, 1
	CMP EAX, EDX
	JE southBorder ; if the SOUTH side is the maze border, jump over setting it, and leave it as a wall..
	ADD EAX, 1
	MUL mazeWidth
	ADD AX, agentX	
	MOV PLANNEDPOSITION, AL
	MOV SOUTHPOSITION, AL
	MOV AL, [maze + EAX]
	XCHG AL, SOUTH
	southBorder:

	;check WEST
	MOV AL, wall
	XCHG AL, WEST ; base assumption, there is a wall to the WEST...
	MOVZX EAX, agentX
	CMP EAX, 0
	JE westBorder ; if the WEST side is the maze border, jump over setting it, and leave it as a wall..
	SUB EAX, 1
	MOV EBX, EAX
	MOVZX EAX, agentY
	MUL mazeWidth
	ADD EAX, EBX
	MOV PLANNEDPOSITION, AL
	MOV WESTPOSITION, AL
	MOV AL, [maze + EAX]
	XCHG AL, WEST
	westBorder:
	
	;CHECK IF NORTH IS EMPTY PATH
	MOV AL, NORTHPOSITION
	XCHG AL, PLANNEDPOSITION
	MOV AL, NORTH
	CMP AL, FLOOR
	JE NORTHISFLOOR
	CMP AL, GOAL
	JE NORTHISEND
	JMP NORTHISNOTFLOOR
		NORTHISEND:
		MOV GAMEOVER, 1
		NORTHISFLOOR:
		JMP FINALLY
	NORTHISNOTFLOOR:

	;CHECK IF EAST IS EMPTY PATH
	MOV AL, EASTPOSITION
	XCHG AL, PLANNEDPOSITION
	MOV AL, EAST
	CMP AL, FLOOR
	JE EASTISFLOOR
	CMP AL, GOAL
	JE EASTISEND
	JMP EASTISNOTFLOOR
		EASTISEND:
		MOV GAMEOVER, 1
		EASTISFLOOR:
		JMP FINALLY
	EASTISNOTFLOOR:
	
	;CHECK IF SOUTH IS EMPTY PATH
	MOV AL, SOUTHPOSITION
	XCHG AL, PLANNEDPOSITION
	MOV AL, SOUTH
	CMP AL, FLOOR
	JE SOUTHISFLOOR
	CMP AL, GOAL
	JE SOUTHISEND
	JMP SOUTHISNOTFLOOR
		SOUTHISEND:
		MOV GAMEOVER, 1
		SOUTHISFLOOR:
		JMP FINALLY
	SOUTHISNOTFLOOR:

	;CHECK IF WEST IS EMPTY PATH
	MOV AL, WESTPOSITION
	XCHG AL, PLANNEDPOSITION
	MOV AL, WEST
	CMP AL, FLOOR
	JE WESTISFLOOR
	CMP AL, GOAL
	JE WESTISEND
	JMP WESTISNOTFLOOR
		WESTISEND:
		MOV GAMEOVER, 1
		WESTISFLOOR:
		JMP FINALLY
	WESTISNOTFLOOR:

	; IF WE ARE HERE, NO EMPTY FLOORS WERE FOUND...
	MOV MARKLEVEL, 2
	;CHECK IF NORTH IS FIRST PATH
	MOV AL, NORTH
	CMP AL, FIRST
	JNE NORTHISNOTFIRST
		XCHG AL, NORTHPOSITION
		MOV PLANNEDPOSITION, AL
		ADD FIRSTPATHS, 1
	NORTHISNOTFIRST:

	;CHECK IF EAST IS FIRST PATH
	MOV AL, EAST
	CMP AL, FIRST
	JNE EASTISNOTFIRST
		XCHG AL, EASTPOSITION
		MOV PLANNEDPOSITION, AL
		ADD FIRSTPATHS, 1
	EASTISNOTFIRST:

	;CHECK IF SOUTH IS FIRST PATH
	MOV AL, SOUTH
	CMP AL, FIRST
	JNE SOUTHISNOTFIRST
		XCHG AL, SOUTHPOSITION
		MOV PLANNEDPOSITION, AL
		ADD FIRSTPATHS, 1
	SOUTHISNOTFIRST:

	;CHECK IF WEST IS FIRST PATH
	MOV AL, WEST
	CMP AL, FIRST
	JNE WESTISNOTFIRST
		XCHG AL, WESTPOSITION
		MOV PLANNEDPOSITION, AL
		ADD FIRSTPATHS, 1
	WESTISNOTFIRST:

	CMP FIRSTPATHS, 0
	JNE FINALLY
		MOV GAMEOVER, 1
		RET



	FINALLY:
	CMP FIRSTPATHS, 2
	JNE	CORRIDOR
		MOV AL, LASTPOSITION
		MOV PLANNEDPOSITION, AL
	CORRIDOR:
		CALL MARK
		CALL MOVE
	RET

CheckSurroundings	ENDP


;!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
;	Function to draw the actual maze onto the console
;	
DrawMaze	PROC

	; Loop through the maze array
	MOVZX ECX, mazeSize
	L1:
		; if end of the line, insert linefeed
		MOV EBX, ECX
		MOVZX EAX, mazeSize
		SUB EAX, EBX
		CDQ
		DIV mazeWidth
		CMP DX, 0
		JNE else2
		CALL Crlf

		else2:
		MOV EDX, ECX
		MOVZX EBX, mazeSize
		SUB EBX, EDX
		MOVZX EAX,  [maze + EBX]
		MOVZX EBX,	wall
		; if current position is wall, drawWall
		CMP EBX, EAX
		JNE else1
		CALL DrawWall
		JMP continue
		; else if floor..
		else1:
		;MOV AL, floor
		CALL WriteChar
		continue:
	LOOP L1

		
	
	RET
DrawMaze ENDP

DrawWall PROC USES EAX 

	; this part makes the char a block of solid color...
	MOVZX EAX, color
	SHL EAX, 4
	OR AL, color
	CALL SetTextColor 

	MOV AL, wall
	call WriteChar

	; this part changes back the background to black, for further prints
	MOVZX EAX, backgroundColor
	SHL EAX, 4
	OR AL, color
	CALL SetTextColor


	RET
DrawWall ENDP

;===============================================================================
.stack
			dw		1000	dup	(?)

end main
