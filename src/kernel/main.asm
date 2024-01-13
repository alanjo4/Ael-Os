org 0x7C00
bits 16

%define ENDL 0x0D, 0x0A


start:
	jmp main

puts:
	; Guarda los registros que vamos a modificar
	push si
	push ax

.loop:
	; Cargamos el caracter que vamos a imprimir
	lodsb
	; Si es 0 terminamos
	or al, al
	jz .done
	; Si no, lo imprimimos
	mov ah, 0x0E
	mov bh, 0x00
	int 0x10

	jmp .loop

.done:
	; Restauramos los registros
	pop ax
	pop si
	ret

main:
	; Creamos los segmentos de datos y de codigo
	mov ax, 0
	mov ds, ax
	mov es, ax

	; Creamos el stack
	mov ss, ax
	mov sp, 0x7C00 ; El stack crece hacia abajo desde donde fue cargado en la memoria 
	; En esencia el stack es un pedacito de memoria al cual podemos acceder
	; con el puntero de stack (sp) y que se va a ir llenando con los datos que
	; nosotros le vayamos metiendo.
	; también es importante decir que usa una arquitectura FIFO (First In First Out)
	; es decir que el primer dato que metamos va a ser el último en salir y viceversa
	; también el stack es usado para guardar los return address de las funciones
	; cuando se está llamando una función. Es decir que cuando se llama una función
	; el return address de la función que la llamó se guarda en el stack y cuando
	; la función termina se saca ese return address del stack y se salta a esa dirección

	; print
	mov si, msg
	call puts

	hlt

.halt:
	jmp .halt

msg: db "Hello world!", ENDL, 0

times 510-($-$$) db 0
dw 0AA55h
