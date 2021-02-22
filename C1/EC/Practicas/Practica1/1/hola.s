.data
msg:    .string "¡hola, mundo!\n"
tam:    .quad . - msg	# calcula el tamaño de msg. tam esta en pos14. . indica la posicion actual(14). por tanto el tamaño de msg = 14 - 0 (donde empieza el string)

.text
        .global _start

write:  mov   $1,   %rax  # write
        mov   $1,   %rdi  # stdout
        mov   $msg, %rsi  # texto
        mov   tam,  %rdx  # tamaño
        syscall           # llamada a write
        ret

exit:   mov   $60,  %rax  # exit
        xor   %rdi, %rdi  # 0
        syscall           # llamada a exit
        ret

_start: call  write       # llamada a función
        call  exit        # llamada a función

