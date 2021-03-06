.MODEL	SMALL
.286
.STACK	100H
COD	SEGMENT PARA	PUBLIC	'CODE'
ASSUME	CS:COD,SS:STACK,DS:DAT,ES:DAT

DATS	EQU	CS:[DATSEG]
BUFS	EQU	CS:[BUFSEG]
BUF	EQU	DAT+(DAT:ED-DAT:STA+15)/16

CRLY	EQU	2;CREDITTS WIN
WWLY	EQU	9;WORK WIN
DWLY	EQU	3;DUMP WIN
RWLY	EQU	1;REPORT WIN
FWLX	EQU	29;FIRST WIN
SWLX	EQU	15;SECOND WIN

WINLY	EQU	1+1+CRLY+1+WWLY+1+DWLY+1+RWLY+1+1
WINLX	EQU	2+1+FWLX+1+SWLX+1+2
LOADWLY EQU	5
LOADWLX EQU	34

WINATY	EQU	(25-WINLY)/2-1
WINATX	EQU	(80-WINLX)/2
LOADWATY	EQU	(25-LOADWLY)/2-1
LOADWATX	EQU	(80-LOADWLX)/2

F3	EQU	3DH
F5	EQU	3EH
F6	EQU	3FH

EMUL8086	PROC
	PUSH	DS
	POP	SS
	MOV	DS,DATS
	PUSH	DS
	PUSH	DS
	POP	ES
	MOV	AX,0FFFFH
	LEA	SI,FNAME
	XOR	DX,DX
	MOV	DS,BUFS
	CALL	LOAD_FILE
	POP	DS
	JC	EMUL_ERR
	CALL	SETUP
	PUSH	DS
	POP	ES
	CALL	VIEW_WIN
AGAIN:
	CALL	PRINT_DUMP
	CALL	PRINT_STACK
AGAIN_1:
	CALL	PRINT_REGS
KEYPAUSE_1:
	CALL	VERIFY_COMMAND
	PUSHF
	CALL	PRINT_COMMAND
KEYPAUSE_11:
	CALL	KEYPAUSE
	CMP	AL,1
	JZ	EMUL_EXIT
	CMP	AL,F3
	JZ	LOAD_COM_FILE
	CMP	AL,F5
	JZ	GET_DATA_ADRESS
	CMP	AL,F6
	JZ	GET_CODE_ADRESS
	POPF
	JC	COMMAND_ERROR
	CALL	EXECUTE_COMMAND
	JMP	SHORT	AGAIN
COMMAND_ERROR:
	CALL	PRINT_COMMAND_ERROR
	CALL	PASS_ERROR
	CALL	KEYPAUSE
	CMP	AL,1
	JZ	EMUL_EXIT
	CALL	CLRSTR
	JMP	SHORT	AGAIN_1
EMUL_EXIT:
	CALL	VIEW_WIN
EMUL_ERR:
	CALL	POPUP
	MOV	AX,4C00H
	INT	21H
LOAD_COM_FILE:
	CALL	INP_FILE_NAME
	JC	KEYPAUSE_11
	CALL	CLWW
	MOV	DS,DATS
	MOV	BYTE PTR DS:[CUR_Y_COMMAND],0
	POPF
	JMP	SHORT	AGAIN
GET_DATA_ADRESS:
	CALL	INP_DATA_ADRESS
	JC	SHORT	KEYPAUSE_11
	CALL	PRINT_DUMP
	JMP	SHORT	KEYPAUSE_11
GET_CODE_ADRESS:
	CALL	INP_CODE_ADRESS
	JC	SHORT	KEYPAUSE_11
	CALL	CLWW
	MOV	DS,DATS
	MOV	BYTE PTR DS:[CUR_Y_COMMAND],0
	POPF
	JMP	SHORT	AGAIN_1
ENDP
CLWW	PROC
	PUSH	AX
	PUSH	BX
	PUSH	CX
	PUSH	DX
	MOV	AX,600H
	MOV	BH,78H
	MOV	CX,(WINATX+2+1)+(WINATY+1+1+CRLY+1)*256
	MOV	DX,(WINATX+2+1+FWLX-1)+(WINATY+1+1+CRLY+1+WWLY-1)*256
	INT	10H
	POP	DX
	POP	CX
	POP	BX
	POP	AX
	RET
ENDP
INP_FILE_NAME	PROC
	PUSHA
	PUSH	DS
	PUSH	ES
	MOV	DS,DATS
	PUSH	DS
	POP	ES
	LEA	SI,LOADSPR
	LEA	DI,LOADSCR
	CALL	SPR2SCR
	MOV	AX,26+256*11
	CALL	AT
	LEA	SI,FILENA_
	CALL	WW
	LEA	DI,FNAME_
	MOV	CX,12
	PUSH	DI
	CALL	IW
	POP	SI
	JC	INP_FILE_NAME_EXIT
	PUSH	SI
	MOV	AX,DAT
	ADD	AX,1000H
	MOV	DX,100H
	PUSH	AX
	PUSH	DX
	MOV	DS,AX
	CALL	LOAD_FILE
	POP	DX
	POP	BP
	POP	SI
	JC	INP_FILE_NAME_ERROR
	MOV	DS,DATS
	MOV	WORD PTR DS:[CS_IP_],DX
	SUB	DX,100H
	MOV	WORD PTR DS:[DUMP_ADDR],DX
	MOV	WORD PTR DS:[CS_IP_+2],BP
	MOV	WORD PTR DS:[DUMP_ADDR+2],BP
	CLC
INP_FILE_NAME_EXIT:
	PUSHF
	CALL	CLRLOADSTR
	LEA	SI,LOADSPR
	LEA	DI,LOADSCR
	CALL	SPR2SCR
	POPF
	POP	ES
	POP	DS
	POPA
	RET
INP_FILE_NAME_ERROR:
	PUSH	SI
	MOV	DS,DATS
	MOV	AX,26+256*11
	CALL	AT
	LEA	SI,FILE_
	CALL	WW
	POP	SI
	CALL	WW
	LEA	SI,NOTF_
	CALL	WW
	CALL	KEYPAUSE
	STC
	JMP	SHORT	INP_FILE_NAME_EXIT
ENDP
CLRLOADSTR	PROC
	MOV	AX,600H
	MOV	BH,78H
	MOV	CX,26+256*11
	MOV	DX,26+256*11+27
	INT	10H
	RET
ENDP
CLRSTR	PROC
	MOV	AX,600H
	MOV	BH,78H
	MOV	CX,(WINATY+1+1+CRLY+1+WWLY+1+DWLY+1)*256+WINATX+2+1
	MOV	DX,(WINATY+1+1+CRLY+1+WWLY+1+DWLY+1)*256+WINATX+2+1+FWLX+1+SWLX-1
	INT	10H
	RET
ENDP
IW	PROC
	;IN CX-LEN
	;ES:DI -BUF
	PUSHA
	MOV	BP,CX
IW_1:
	CALL	INKEY
	XCHG	AL,AH
	CMP	AL,0DH
	JE	IW_ENT
	CMP	AL,08
	JE	IW_BACK
	CMP	AL,27
	JE	IW_ESC
	OR	CX,CX
	JZ	IW_1
	STOSB
	CALL	WS
	DEC	CX
	JMP	SHORT	IW_1
IW_ENT:
	XOR	AL,AL
	STOSB
	POPA
	RET
IW_BACK:
	CMP	CX,BP
	JZ	IW_1
	DEC	DI
	INC	CX
	CALL	WS
	MOV	AL,' '
	CALL	WS
	MOV	AL,08
	CALL	WS
	JMP	SHORT	IW_1
IW_ESC:
	STC
	POPA
	RET
ENDP
INP_DATA_ADRESS PROC
	PUSHA
	PUSH	DS
	PUSH	ES
	MOV	DS,DATS
	PUSH	DS
	POP	ES
	LEA	SI,LOADSPR
	LEA	DI,LOADSCR
	CALL	SPR2SCR
	MOV	AX,26+256*11
	CALL	AT
	LEA	SI,ENTDATA
	CALL	WW
	CALL	IH
	;C=1 ERROR,AX:DX-ADRESS,FOR BX=2;DX,FOR BX=1
	JC	INP_DATA_ADRESS_1
	DEC	BX
	JC	INP_DATA_ADRESS_ESC
	MOV	WORD PTR DS:[DUMP_ADDR],DX
	DEC	BX
	JC	INP_DATA_ADRESS_OFF
	MOV	WORD PTR DS:[DUMP_ADDR+2],AX
INP_DATA_ADRESS_OFF:
	CLC
INP_DATA_ADRESS_ESC:
	PUSHF
	CALL	CLRLOADSTR
	LEA	SI,LOADSPR
	LEA	DI,LOADSCR
	CALL	SPR2SCR
	POPF
	POP	ES
	POP	DS
	POPA
	RET
INP_DATA_ADRESS_1:
	CMP	AX,0FFFFH
	STC
	JMP	SHORT	INP_DATA_ADRESS_ESC
	MOV	AX,26+256*11
	CALL	AT
	LEA	SI,ERROR_CODE
	CALL	WW
	CALL	KEYPAUSE
	STC
	JMP	SHORT	INP_DATA_ADRESS_ESC
ENDP
INP_CODE_ADRESS PROC
	PUSHA
	PUSH	DS
	PUSH	ES
	MOV	DS,DATS
	PUSH	DS
	POP	ES
	LEA	SI,LOADSPR
	LEA	DI,LOADSCR
	CALL	SPR2SCR
	MOV	AX,26+256*11
	CALL	AT
	LEA	SI,ENTCODE
	CALL	WW
	CALL	IH
	;C=1 ERROR,AX:DX-ADRESS,FOR BX=2;DX,FOR BX=1
	JC	INP_CODE_ADRESS_1
	DEC	BX
	JC	INP_CODE_ADRESS_ESC
	MOV	WORD PTR DS:[CS_IP_],DX
	DEC	BX
	JC	INP_CODE_ADRESS_OFF
	MOV	WORD PTR DS:[CS_IP_+2],AX
INP_CODE_ADRESS_OFF:
	CLC
INP_CODE_ADRESS_ESC:
	PUSHF
	CALL	CLRLOADSTR
	LEA	SI,LOADSPR
	LEA	DI,LOADSCR
	CALL	SPR2SCR
	POPF
	POP	ES
	POP	DS
	POPA
	RET
INP_CODE_ADRESS_1:
	CMP	AX,0FFFFH
	STC
	JMP	SHORT	INP_CODE_ADRESS_ESC
	MOV	AX,26+256*11
	CALL	AT
	LEA	SI,ERROR_CODE
	CALL	WW
	CALL	KEYPAUSE
	STC
	JMP	SHORT	INP_CODE_ADRESS_ESC
ENDP
IH	PROC
	PUSH	BX
	PUSH	CX
	PUSH	SI
	PUSH	DI
	PUSH	BP
	PUSH	DS
	PUSH	ES
	MOV	ES,DATS
	PUSH	ES
	POP	DS
	MOV	CX,9
	LEA	DI,FREE
	CALL	IW
	JC	IH_E
	MOV	SI,DI
	MOV	CX,4
	XOR	DX,DX
IH_1:
	LODSB
	CMP	AL,':'
	JZ	IH_4
	OR	AL,AL
	JZ	IH_3
	CALL	S2H;OUT AL-NUM,C=1 ERROR CODE
	JC	IH_ERROR
	CALL	OVERDX
	LOOP	IH_1
	LODSB
	OR	AL,AL
	JZ	IH_3
	CMP	AL,':'
	STC
	JNZ	IH_ERROR
IH_4:
	MOV	BP,DX
	XOR	DX,DX
	MOV	CX,4
IH_2:
	LODSB
	OR	AL,AL
	JZ	IH_5
	CALL	S2H;OUT AL-NUM,C=1 ERROR CODE
	JC	IH_ERROR
	CALL	OVERDX
	LOOP	IH_2
IH_5:
	MOV	AX,BP
IH_3:
IH_ERROR:
	POP	ES
	POP	DS
	POP	BP
	POP	DI
	POP	SI
	POP	CX
	POP	BX
	RET
IH_E:
	MOV	AX,0FFFFH
	JMP	SHORT	IH_3
ENDP
S2H	PROC
	CMP	AL,'0'
	JB	S2H_EX
	CMP	AL,'9'
	JBE	S2H_OK
	CMP	AL,'A'
	JB	S2H_EX
	CMP	AL,'F'
	JBE	S2H_OK1
	CMP	AL,'a'
	JB	S2H_EX
	CMP	AL,'f'
	JBE	S2H_OK2
	STC
	JMP	SHORT	S2H_EX
S2H_OK2:
	SUB	AL,20H
S2H_OK1:
	SUB	AL,'A'-'9'-1
S2H_OK:
	SUB	AL,'0'
S2H_EX:
	RET
ENDP
OVERDX	PROC
	PUSH	CX
	MOV	CX,4
	SHL	AL,CL
OVERDX1:
	SHL	AL,1
	RCL	DX,1
	LOOP	OVERDX1
	POP	CX
	RET
ENDP
PASS_ERROR	PROC
	PUSH	DS
	MOV	DS,DATS
	MOV	AX,DS:[LEN_CUR_COMMAND]
	ADD	WORD PTR DS:[CS_IP_],AX
	POP	DS
	RET
ENDP
SETUP	PROC
	PUSH	DS
	MOV	AX,3501H
	INT	21H
	MOV	DS:[OLD_1H_OFF],BX
	MOV	WORD PTR DS:[OLD_1H_SEG],ES
	MOV	AX,COD
	MOV	DS,AX
	MOV	AX,2501H
	LEA	DX,NEW_1H
	INT	21H
	MOV	AX,300H
	XOR	BH,BH
	INT	10H
	MOV	DS,DATS
	MOV	DS:[OLD_CURSOR_AT],DX
	MOV	DS:[OLD_CURSOR_LEN],CX
	MOV	AX,100H
	MOV	CX,0010000000000000B
	INT	10H
	POP	DS
	RET
ENDP
PRINT_REGS	PROC
	MOV	DX,(WINATX+2+1+FWLX+1+3)+256*(WINATY+1+1+CRLY+1)
	MOV	CX,3
	LEA	SI,AX_
PRINT_REGS_1:
	MOV	AX,DX
	CALL	AT
	LODSW
	CALL	PRINT_HEXW
	INC	DH
	LOOP	PRINT_REGS_1
	MOV	CX,3
	MOV	DX,(WINATX+2+1+FWLX+1+3+5+3)+256*(WINATY+1+1+CRLY+1)
PRINT_REGS_3:
	MOV	AX,DX
	CALL	AT
	LODSW
	CALL	PRINT_HEXW
	INC	DH
	LOOP	PRINT_REGS_3
	MOV	CX,4
	MOV	BX,(WINATX+2+1+FWLX+1+6)+256*(WINATY+1+1+CRLY+1+3)
PRINT_REGS_2:
	MOV	AX,BX
	CALL	AT
	LODSW
	PUSH	AX
	LODSW
	CALL	PRINT_HEXW
	MOV	AL,':'
	CALL	WS
	POP	AX
	CALL	PRINT_HEXW
	INC	BH
	LOOP	PRINT_REGS_2
	MOV	AX,(WINATX+2+1+FWLX+1+6)+256*(WINATY+1+1+CRLY+1+3+4+1)
	CALL	AT
	CALL	CREATE_FLAGS
	MOV	CX,8
	CALL	PRINTBIN
	RET
ENDP
PRINT_DUMP	PROC
	PUSHA
	PUSH	DS
	MOV	DS,DATS
	XOR	AX,AX
	CALL	PRINT_DUMP_ADRESS
	MOV	AX,100H
	CALL	PRINT_DUMP_ADRESS
	MOV	BX,(WINATX+2+1+11)+256*(WINATY+1+1+CRLY+1+WWLY+1+1)
	MOV	AX,BX
	CALL	AT
	MOV	CX,4
	LDS	SI,DS:[DUMP_ADDR]
PRINT_DUMP_1:
	LODSB
	CALL	PRINT_HEXB
	MOV	AL,' '
	CALL	WS
	LOOP	PRINT_DUMP_1
	INC	BH
	MOV	AX,BX
	CALL	AT
	MOV	CX,4
PRINT_DUMP_2:
	LODSB
	CALL	PRINT_HEXB
	MOV	AL,' '
	CALL	WS
	LOOP	PRINT_DUMP_2
	POP	DS
	POPA
	RET
ENDP
PRINT_DUMP_ADRESS	PROC
	;IN AH 0 OR 1
	PUSH	BX
	PUSH	DX
	PUSH	BP
	XOR	DX,DX
	MOV	DL,AH
	SHL	DX,2
	MOV	BP,DX
	MOV	BX,(WINATX+2+1)+256*(WINATY+1+1+CRLY+1+WWLY+1+1)
	XOR	AL,AL
	ADD	AX,BX
	CALL	AT
	MOV	AX,WORD PTR DS:[DUMP_ADDR+2]
	CALL	PRINT_HEXW
	MOV	AL,':'
	CALL	WS
	MOV	AX,WORD PTR DS:[DUMP_ADDR]
	ADD	AX,BP
	CALL	PRINT_HEXW
	POP	BP
	POP	DX
	POP	BX
	RET
ENDP
PRINT_STACK	PROC
	PUSHA
	PUSH	DS
	MOV	DS,DATS
	MOV	BX,(WINATX+2+1+FWLX+1+3)+256*(WINATY+1+1+CRLY+1+WWLY+1+1)
	LDS	SI,DS:[SS_SP_]
	MOV	CX,2
	MOV	DL,'0'
PRINT_STACK_1:
	MOV	AX,BX
	CALL	AT
	MOV	AL,'+'
	CALL	WS
	MOV	AL,DL
	CALL	WS
	MOV	AL,' '
	CALL	WS
	CALL	WS
	LODSW
	CALL	PRINT_HEXW
	INC	BH
	INC	DL
	INC	DL
	LOOP	PRINT_STACK_1
	POP	DS
	POPA
	RET
ENDP
CREATE_FLAGS	PROC
	XOR	AX,AX
	MOV	DX,DS:[F_]
	SHR	DX,1
	RCL	AX,1
	MOV	CX,3
CREATE_FLAGS_1:
	SHR	DX,2
	RCL	AX,1
	LOOP	CREATE_FLAGS_1
	SHR	DX,1
	RCL	AX,1
	SHR	DX,2
	RCL	AX,1
	SHR	DX,1
	RCL	AX,1
	SHR	DX,1
	RCL	AX,1
	RET
ENDP
EXECUTE_COMMAND PROC
	MOV	DS:[OLD_SS],SS
	MOV	DS:[OLD_SP],SP
	MOV	AX,DS:[F_]
	OR	AX,100000000B
	PUSH	AX
	MOV	AX,WORD PTR DS:[CS_IP_+2]
	PUSH	AX
	MOV	AX,WORD PTR DS:[CS_IP_]
	PUSH	AX
	MOV	AX,DS:[AX_]
	MOV	BX,DS:[BX_]
	MOV	CX,DS:[CX_]
	MOV	DX,DS:[DX_]
	MOV	BP,DS:[BP_]
	LES	DI,DS:[ES_DI_]
	LDS	SI,DS:[DS_SI_]
	IRET
NEW_1H:
	MOV	WORD PTR CS:[OLD_DS],DS
	MOV	DS,CS:[DATS]
	MOV	DS:[BP_],BP
	MOV	DS:[DX_],DX
	MOV	DS:[CX_],CX
	MOV	DS:[BX_],BX
	MOV	DS:[AX_],AX
	MOV	AX,CS:[OLD_DS]
	MOV	WORD PTR DS:[DS_SI_],SI
	MOV	WORD PTR DS:[DS_SI_+2],AX
	MOV	WORD PTR DS:[ES_DI_],DI
	MOV	WORD PTR DS:[ES_DI_+2],ES
	POP	AX
	MOV	WORD PTR DS:[CS_IP_],AX
	POP	AX
	MOV	WORD PTR DS:[CS_IP_+2],AX
	POP	AX
	MOV	DS:[F_],AX
	MOV	BX,DS:[OLD_SS]
	MOV	AX,SS
	SUB	AX,BX
	ADD	AX,WORD PTR DS:[SS_SP_+2]
	MOV	WORD PTR DS:[SS_SP_+2],AX
	MOV	BX,DS:[OLD_SP]
	MOV	AX,SP
	SUB	AX,BX
	ADD	AX,WORD PTR DS:[SS_SP_]
	MOV	WORD PTR DS:[SS_SP_],AX
	RET
OLD_DS	DW  0
ENDP
PRINT_COMMAND	PROC
	MOV	BH,DS:[CUR_Y_COMMAND]
	CMP	BH,WWLY
	JB	PRINT_COMMAND_2
	PUSH	BX
	MOV	AX,601H
	MOV	BH,78H
	MOV	CX,(WINATX+2+1)+(WINATY+1+1+CRLY+1)*256
	MOV	DX,(WINATX+2+1+FWLX-1)+(WINATY+1+1+CRLY+1+WWLY-1)*256
	INT	10H
	POP	BX
	DEC	BYTE PTR DS:[CUR_Y_COMMAND]
	MOV	BH,DS:[CUR_Y_COMMAND]
PRINT_COMMAND_2:
	OR	BH,BH
	JZ	PRINT_COMMAND_3
	CALL	OVER_OLD_CURSOR
PRINT_COMMAND_3:
	CALL	PRINT_ADRESS
	ADD	BH,WINATY+1+1+CRLY+1
	MOV	BL,WINATX+2+1+1+10
	MOV	CX,DS:[LEN_CUR_COMMAND]
	PUSH	DS
	LDS	SI,DS:[CS_IP_]
PRINT_COMMAND_1:
	MOV	AX,BX
	CALL	AT
	LODSB
	CALL	PRINT_HEXB
	ADD	BL,3
	LOOP	PRINT_COMMAND_1
	POP	DS
	CALL	OVER_CURSOR
	INC	BYTE PTR DS:[CUR_Y_COMMAND]
	RET
ENDP
PRINT_ADRESS	PROC
	PUSH	BX
	MOV	BX,(WINATX+2+1)+256*(WINATY+1+1+CRLY+1)
	XOR	AL,AL
	MOV	AH,DS:[CUR_Y_COMMAND]
	ADD	AX,BX
	CALL	AT
	MOV	AX,WORD PTR DS:[CS_IP_+2]
	CALL	PRINT_HEXW
	MOV	AL,':'
	CALL	WS
	MOV	AX,WORD PTR DS:[CS_IP_]
	CALL	PRINT_HEXW
	POP	BX
	RET
ENDP
OVER_OLD_CURSOR PROC
	PUSH	AX
	MOV	AL,DS:[CUR_Y_COMMAND]
	DEC	AL
	CALL	OVER1
	POP	AX
	RET
ENDP
OVER_CURSOR	PROC
	PUSH	AX
	MOV	AL,DS:[CUR_Y_COMMAND]
	CALL	OVER1
	POP	AX
	RET
ENDP
OVER1	PROC
	PUSH	BX
	PUSH	CX
	PUSH	DX
	MOV	DX,(WINATX+2+1+9)+256*(WINATY+1+1+CRLY+1)
	XOR	AH,AH
	XCHG	AL,AH
	ADD	AX,DX
	CALL	AT
	MOV	AX,800H
	MOV	BH,AL
	INT	10H
	CMP	AL,' '
	JNZ	OVER11
	XOR	AL,AL
OVER11:
	XOR	AL,10H
	MOV	BL,AH
	XOR	BH,BH
	MOV	AH,09H
	MOV	CX,1
	INT	10H
	POP	DX
	POP	CX
	POP	BX
	RET
ENDP
KEYPAUSE	PROC
	XOR	AX,AX
	INT	16H
	XCHG	AL,AH
	RET
ENDP
INKEY	EQU	KEYPAUSE
VERIFY_COMMAND	PROC
	PUSHA
	PUSH	DS
	MOV	DS,DATS
	LDS	SI,DS:[CS_IP_]
	LODSW
	MOV	BX,AX
	LODSW
	MOV	DX,AX
	MOV	DS,DATS
	MOV	BYTE PTR DS:[LEN_CUR_COMMAND],0
	MOV	AX,BX
	XOR	AH,AH
PREFIX_A:
	LEA	SI,COMMAND_TABLE
	ADD	SI,AX
	LODSB
	CMP	AL,80H
	JNZ	NO_PREFIX
	INC	BYTE PTR DS:[LEN_CUR_COMMAND]
	CALL	SHIFTING
	MOV	AL,BL
	OR	BX,DX
	JZ	NO_COMMAND_1
	JMP	SHORT	PREFIX_A
NO_PREFIX:
	OR	AL,AL
	JZ	NO_COMMAND
	TEST	AL,40H
	JNZ	MOD_REG_RM
	CMP	AL,8
	JB	SHORT	VERIFY_COMMAND_EXIT_1
	LEA	SI,NEXT_TABLES
	SUB	AL,8
	XOR	AH,AH
	SHL	AL,3
	ADD	SI,AX
	MOV	AL,BH
	AND	AL,00111000B
	SHR	AL,3
	ADD	SI,AX
	LODSB
	JMP	SHORT	NO_PREFIX
NO_COMMAND:
	INC	BYTE PTR DS:[LEN_CUR_COMMAND]
NO_COMMAND_1:
	STC
	JMP	SHORT	VERIFY_COMMAND_EXIT
MOD_REG_RM:
	AND	AL,111B
	XCHG	AL,BH
	AND	AL,11000111B
	CMP	AL,00000110B
	JNZ	MOD_REG_RM_2
	ADD	BYTE PTR DS:[LEN_CUR_COMMAND],2
MOD_REG_RM_2:
	SHR	AL,6
	CMP	AL,3
	JNZ	MOD_REG_RM_1
	XOR	AL,AL
MOD_REG_RM_1:
	ADD	AL,BH
VERIFY_COMMAND_EXIT_1:
	ADD	BYTE PTR DS:[LEN_CUR_COMMAND],AL
VERIFY_COMMAND_EXIT:
	POP	DS
	POPA
	RET
ENDP
SHIFTING	PROC
	MOV	BL,BH
	MOV	BH,DL
	MOV	DL,DH
	XOR	DH,DH
	RET
ENDP
PRINT_COMMAND_ERROR	PROC
	PUSH	DS
	MOV	DS,DATS
	MOV	AX,(WINATY+1+1+CRLY+1+WWLY+1+DWLY+1)*256+(WINATX+2+1)
	CALL	AT
	LEA	SI,COMMM_ERR
	CALL	WW
	POP	DS
	RET
ENDP
VIEW_WIN	PROC
	LEA	SI,SPRTBL
	LEA	DI,SCRTBL
	JMP	SPR2SCR
ENDP
POPUP	PROC
	PUSH	DS
	MOV	AX,2501H
	MOV	DX,DS:[OLD_1H_OFF]
	MOV	DS,DS:[OLD_1H_SEG]
	INT	21H
	MOV	AX,100H
	MOV	DS,DATS
	MOV	CX,DS:[OLD_CURSOR_LEN]
	INT	10H
	MOV	AX,200H
	XOR	BH,BH
	MOV	DX,DS:[OLD_CURSOR_AT]
	INT	10H
	POP	DS
	RET
ENDP
AT	PROC
	PUSH	AX
	PUSH	BX
	PUSH	DX
	MOV	DX,AX
	MOV	AX,200H
	MOV	BH,0
	INT	10H
	POP	DX
	POP	BX
	POP	AX
	RET
ENDP
PRINT_HEXW	PROC
	PUSH	CX
	MOV	CX,4
	CALL	PRINT_HEX
	POP	CX
	RET
ENDP
PRINT_HEXB	PROC
	PUSH	CX
	MOV	CX,2
	CALL	PRINT_HEX
	POP	CX
	RET
ENDP
PRINT_HEX	PROC
	;IN - CX -QUANTITY
	;     AX -NUMBER
	PUSHA
	MOV	DX,AX
	MOV	BX,CX
PRINT_HEX_1:
	MOV	AX,DX
	AND	AX,1111B
	ADD	AL,30H
	CMP	AL,3AH
	JB	PRINT_HEX_2
	ADD	AL,7
PRINT_HEX_2:
	PUSH	AX
	SHR	DX,4
	LOOP	PRINT_HEX_1
	MOV	CX,BX
PRINT_HEX_3:
	POP	AX
	CALL	WS
	LOOP	PRINT_HEX_3
	POPA
	RET
ENDP
INCLUDE ..\..\LIBRARY\TEXT\SPR2SCR.LIB
INCLUDE ..\..\LIBRARY\FILE\IO.LIB
INCLUDE ..\..\LIBRARY\TEXT\WW.LIB
INCLUDE ..\..\LIBRARY\TEXT\PRINTBIN.LIB
INCLUDE ..\..\LIBRARY\TEXT\VIDEO.TBL
DATSEG	DW	DAT
BUFSEG	DW	BUF
ENDS
DAT	SEGMENT PARA	PUBLIC	'DATA'
STA	DB	10H	DUP	(0)
ASSUME	CS:DAT
CODB:
	db	00,01
	db	01,00
	ADD	AX,10
	SUB	BX,AX
	INC	CX
	ROR	AL,1
	JZ	CODB1
	ADD	CL,1
	REP	CMPSB
	ADD	DL,CS:[15]
CODB1:
	ADC	CH,ES:[SI+BP]
	STC
JMP	SHORT	CODB
LEN_CUR_COMMAND 	DW	0
CUR_Y_COMMAND		DB	0
CUR_CODE		DB	0
AX_	DW	0
BX_	DW	0
CX_	DW	0
DX_	DW	0
BP_	DW	0
F_	DW	3202H
DS_SI_	DD	DAT:0
ES_DI_	DD	DAT:0
SS_SP_	DD	DAT:10H
CS_IP_	DD	DAT:CODB
OLD_SP	DW	0
OLD_SS	DW	0
OLD_1H_OFF	DW	0
OLD_1H_SEG	DW	0
OLD_CURSOR_AT	DW	0
OLD_CURSOR_LEN	DW	0
DUMP_ADDR	DD	DAT:0
SPRTBL	DD	BUF:0
	DW	WINLY
	DW	WINLX
	DW	WINATY
	DW	WINATX
	DB	0,0,0,0
SCRTBL	DW	0,0,0,0
	DB	8	DUP	(0)
LOADSPR DD	BUF:(WINLY*WINLX*2)
	DW	LOADWLY
	DW	LOADWLX
	DW	LOADWATY
	DW	LOADWATX
	DB	0,0,0,0
LOADSCR DW	0,0,0,0
	DB	8	DUP	(0)
INCLUDE COMMAND.TBL
FNAME	DB	'EMUL8086.WIN',0
FNAME_	DB	13	DUP	(0)
FREE	DB	10	DUP	(0)
COMMM_ERR	DB	'Illegal command code <Exception #6>',0
FILENA_ 	DB	'Enter filename:',0
FILE_		DB	'File ',0
NOTF_		DB	' not found',0
ENTDATA 	DB	'Enter data adress:',0
ENTCODE 	DB	'Enter code adress:',0
ERROR_CODE	DB	' Error in writing of adress ',0

ED:
ENDS
END	EMUL8086
