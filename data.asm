;----------------------------------------------;
; nasm -f bin data.asm -o data.bin
;
; Athenian
;
;----------------------------------------------;
 
BITS 16
ORG     0x7c00                  ;ORIGIN ADDRESS when loaded
 
jmp start
 
start:
        mov ax,cs
        mov ds,ax
        mov si,msg          ;SI now holds the message we wanna print
        call print
        mov ax,13h        
        int 10h             
        mov ax,0A000h        
        mov es,ax             
        mov ax,32010          
        mov di,ax             
        mov dl,4             
        mov [es:di],dx        
        int 10h
 
print:
        push ax
        cld
next:
        mov al,[si]
        cmp al,0            ;is the end of the string ?
        je done             ;if so,jump to done
        call printchar
        inc si              ;move to the next position in the string
        jmp next            ;repeat
done:
        jmp $               ;infinite loop
 
printchar:
        mov ah,0x0e         ;print char service
        int 0x10            ;print char
        ret
  
msg:            db        "Like like like.", 0
;----------------------------------------------;
; Bootloader signature must be located
; at bytes #511 and #512.
; Fill with 0 in between.
; $  = address of the current line
; $$ = address of the 1st instruction
;----------------------------------------------;
  
times 510 - ($-$$) db 0
dw        0xaa55