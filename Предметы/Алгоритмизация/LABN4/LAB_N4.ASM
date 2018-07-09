ASSUME  CS:COD,DS:COD
COD     SEGMENT
ORG     100H
START:
LABN1   PROC
        MOV     AL,1
        CALL    RANDOMIZE
        CALL    CHECK_N_L
        MOV     DS:[N],AX
        MOV     DS:[L],BX
        CALL    CLS
        LEA     SI,CREDITS
        CALL    WW
        CALL    VERIFY_XC
        LEA     SI,STR_SOURSE
        CALL    WW
        MOV     CX,DS:[N]
        MOV     AX,1
        SHL     AX,CL
        DEC     AX
        MOV     BX,AX
        CALL    RND
        MOV     BP,AX
        PUSH    BP
        CALL    PRINTBIN
        CALL    ENTERF
        LEA     SI,MATRIX
        CALL    WW
        CALL    CODER;(IN AX,OUT DX)
        CALL    ENTERF
        LEA     SI,CODED_WORD
        CALL    WW
        MOV     CX,DS:[L]
        MOV     AX,DX
        CALL    PRINTBIN
        LEA     SI,PLUS
        CALL    WW
        LEA     SI,HINDRANCE
        CALL    WW
        CALL    ADD_HINDRANCE;(IN DX,OUT DX)
        LEA     SI,EQUAL
        CALL    WW
        LEA     SI,GOTTEN_WORD
        CALL    WW
        MOV     AX,DX
        CALL    PRINTBIN
        CALL    ENTERF
        MOV     AX,DX
        CALL    DECODER;(IN AX,OUT AX)
        LEA     SI,OUT_DECODER
        CALL    WW
        MOV     CX,DS:[N]
        CALL    PRINTBIN
        CALL    ENTERF
        POP     BP
        CMP     AX,BP
        JNE     SHUM_ERROR
        MOV     AX,4C00H
        INT     21H
SHUM_ERROR:
        MOV     AX,4CFFH
        INT     21H
EXIT:
        MOV     AX,4CFEH
        INT     21H
ENDP
ADD_HINDRANCE   PROC
        PUSH    AX
        PUSH    CX
        MOV     AX,DS:[L]
        MOV     BX,AX
        CALL    RND
        MOV     CX,AX
        XOR     AX,AX
        STC
        RCL     AX,CL
        MOV     CX,DS:[L]
        CALL    PRINTBIN
        XOR     DX,AX
        POP     CX
        POP     AX
        RET
ENDP
CODER   PROC
        PUSH    AX
        PUSH    CX
        PUSH    SI
        PUSH    BP
        MOV     BP,AX
        XOR     AX,AX
        MOV     DX,AX
        MOV     AX,DS:[XC]
        MOV     CX,DS:[N]
CODER_2:
        SHR     BP,1
        JNC     CODER_1
        XOR     DX,AX
        STC
CODER_1:
        CALL    LINE_MATRIX
        SHL     AX,1
        LOOP    CODER_2
        MOV     AL,' '
        CALL    WS
        MOV     AX,DX
        MOV     CX,DS:[L]
        CALL    PRINTBIN
        POP     BP
        POP     SI
        POP     CX
        POP     AX
        RET
ENDP
LINE_MATRIX     PROC
        PUSH    AX
        PUSH    CX
        PUSHF
        PUSH    AX
        MOV     AL,0B3H
        CALL    WS
        POP     AX
        MOV     CX,DS:[L]
        CALL    PRINTBIN
        MOV     AL,0B3H
        CALL    WS
        POPF
        CALL    PRINTCARRY
        CALL    ENTERF
        POP     CX
        POP     AX
        RET
ENDP
PRINTCARRY      PROC
        PUSHF
        MOV     AL,0
        ADC     AL,30H
        CALL    WS
        POPF
        RET
ENDP
DECODER PROC
        PUSH    BX
        PUSH    CX
        PUSH    DX
        PUSH    DI
        PUSH    BP
        MOV     DI,AX
        MOV     BX,DS:[XC]
DECODER_2:
        MOV     AX,DI
        CALL    DIVIDEXOR
        CALL    PRINT_DIV
        OR      DX,DX
        JZ      DECODER_EXIT
        XOR     CX,CX
DECODER_1:
        CMP     BP,1
        JNA     DECODER_NA
        INC     CX
        CALL    ROLLER;(IN,OUT DI)
        MOV     AX,DI
        CALL    DIVIDEXOR
        CALL    PRINT_DIV
        JMP     SHORT   DECODER_1
DECODER_NA:
        CALL    PRINT_OVER_HINDRANCE
        JCXZ    DECODER_2
        NEG     CX
        ADD     CX,DS:[L]
DECODER_NA1:
        CALL    ROLLER
        LOOP    DECODER_NA1
        JMP     SHORT   DECODER_2
DECODER_EXIT:
        POP     BP
        POP     DI
        POP     DX
        POP     CX
        POP     BX
        RET
ENDP
CLS     PROC
        PUSH     AX
        PUSH     BX
        PUSH     CX
        PUSH     DX
        MOV      AX,700H
        MOV      BX,AX
        XOR      CX,CX
        MOV      DX,79+24*256
        INT      10H
        MOV      AX,200H
        XOR      BX,BX
        MOV      DX,BX
        INT      10H
        POP      DX
        POP      CX
        POP      BX
        POP      AX
        RET
ENDP
PRINT_DIV       PROC
        PUSH    AX
        PUSH    CX
        PUSH    SI
        PUSH    AX
        MOV     AX,DI
        MOV     CX,DS:[L]
        CALL    PRINTBIN
        MOV     AL,'/'
        CALL    WS
        CALL    WRITE_POLINOM
        MOV     AL,'='
        CALL    WS
        POP     AX
        MOV     CX,DS:[N]
        CALL    PRINTBIN
        LEA     SI,DIVI
        CALL    WW
        MOV     AX,DX
        MOV     CX,DS:[L]
        SUB     CX,DS:[N]
        CALL    PRINTBIN
        LEA     SI,WEIGHT_
        CALL    WW
        MOV     AX,BP
        ADD     AL,30H
        CALL    WS
        CALL    ENTERF
        POP     SI
        POP     CX
        POP     AX
        RET
ENDP
PRINT_OVER_HINDRANCE    PROC
        PUSH    AX
        PUSH    CX
        LEA     SI,DELETE_HINDRANCE
        CALL    WW
        MOV     AX,DI
        MOV     CX,DS:[L]
        CALL    PRINTBIN
        MOV     AL,'+'
        CALL    WS
        MOV     AX,DX
        CALL    PRINTBIN
        MOV     AL,'='
        CALL    WS
        XOR     DI,DX
        MOV     AX,DI
        CALL    PRINTBIN
        CALL    ENTERF
        POP     CX
        POP     AX
        RET
ENDP
ROLLER  PROC
        PUSH    AX
        PUSH    CX
        MOV     CX,DS:[L]
        XOR     AX,AX
        STC
        RCL     AX,CL
        TEST    DI,AX
        JZ      ROLLER_1
        XOR     DI,AX
        STC
ROLLER_1:
        RCL     DI,1
        POP     CX
        POP     AX
        RET
ENDP
CHECK_N_L       PROC
        PUSH    CX
        MOV     AX,DS:[XC]
        MOV     CX,16
CHECK_N_L_1:
        SHL     AX,1
        JC      CHECK_N_L_2
        LOOP    CHECK_N_L_1
CHECK_N_L_2:
        DEC     CX
        PUSH    CX
        MOV     AX,1
        SHL     AX,CL
        DEC     AX
        MOV     BX,AX
        POP     CX
        SUB     AX,CX
        MOV     DS:[N],AX
        POP     CX
        RET
ENDP
VERIFY_XC       PROC
        PUSH    AX
        PUSH    BX
        PUSH    CX
        PUSH    DX
        PUSH    BP
        MOV     CX,DS:[L]
        INC     CX
        XOR     AX,AX
        STC
        RCL     AX,CL
        INC     AX
        MOV     BX,DS:[XC]
        CALL    DIVIDEXOR
        OR      DX,DX
        JNZ     VERIFY_ERROR
        LEA     SI,POLINOM
        CALL    WW
        MOV     AX,DS:[L]
        CALL    WRITE_POLINOM
        CALL    ENTERF
        POP     BP
        POP     DX
        POP     CX
        POP     BX
        POP     AX
        RET
VERIFY_ERROR:
        LEA     SI,POLINOM_ERR
        CALL    WW
        CALL    WRITE_POLINOM
        CALL    ENTERF
        JMP     EXIT
ENDP
WRITE_POLINOM   PROC
        MOV     AX,DS:[L]
        SUB     AX,DS:[N]
        INC     AX
        MOV     CX,AX
        MOV     AX,DS:[XC]
        JMP     PRINTBIN
ENDP
ENTERF  PROC
        PUSH    SI
        LEA     SI,ENTR
        CALL    WW
        POP     SI
        RET
ENDP
INCLUDE DIV.LIB
INCLUDE PRINTBIN.LIB
INCLUDE WW.LIB
INCLUDE RND.LIB
CREDITS         DB      'Лабораторная работа по алгоритмизации Скрылева Павла (C)1996',0dh,0ah,0ah,0
POLINOM         DB      'Порождающий полином:',0
POLINOM_ERR     DB      'Неверный порождающий полином:',0
STR_SOURSE      DB      'Информационное слово Un=',0
CODER_          DB      '[CODER]',0DH,0AH,0
MATRIX          DB      'Порождающая матрица:',0DH,0AH,0
CODED_WORD      DB      'Кодовое слово X=',0
PLUS            DB      ' + ',0
HINDRANCE       DB      'Помеха Z=',0
EQUAL           DB      ' => ',0
GOTTEN_WORD     DB      'Слово с помехой Y=',0
DECODER_        DB      '[DECODER]',0DH,0AH,0
OUT_DECODER     DB      'Слово на выходе из DECODERа:',0
DIVI            DB      ',Остаток=',0
WEIGHT_         DB      ',Вес остатка=',0
DELETE_HINDRANCE        DB      'Удаление помехи:',0
ENTR            DB      0DH,0AH,0
XC      DW      1101B
N       DW      ?
L       DW      ?
ENDS
END  START
