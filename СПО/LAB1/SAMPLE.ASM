ASSUME	CS:CGR,DS:CGR
CGR	GROUP	COD,DAT
COD	SEGMENT
ORG	100H
a5:
	add  dx,1f04h
	add  [bx+si],dx
	add  dx,20
	sub  [bx+si],dx
	add  ax,0fed3h
	or   [bx+si],ax
	or   cx,[bx+si]
	add  ax,0ffffh
	adc  cx,8000h
	xor  dx,dx
	mul  cx
	add  bx,cx
	div  bx
	inc  ax
	dec  cx
	jnz  a1
	ja   a2
	call a3
	jmp  short a4
a1:
	sub  cx,10h
	inc  si
	jmp  a4
a2:
	sub  ax,10h
	dec  si
a4:
	xor  bx,bx
	jz   a5
a3:
	add  cx,10h
	ret
ENDS
DAT	SEGMENT
ENDS
END a5