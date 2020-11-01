.section .data
#ifndef TEST
#define TEST 20
#endif
	.macro linea
#if TEST==1	
	.int 1,2,1,2
#elif TEST==2
	.int -1,-2,-1,-2
#elif TEST==3
	.int 0x7fffffff,0x7fffffff,0x7fffffff,0x7fffffff
#elif TEST==4
	.int 0x80000000,0x80000000,0x80000000,0x80000000
#elif TEST==5	
	.int 0xffffffff,0xffffffff,0xffffffff,0xffffffff
#elif TEST==6
	.int 2000000000,2000000000,2000000000,2000000000
#elif TEST==7
	.int 3000000000,3000000000,3000000000,3000000000
#elif TEST==8
	.int -2000000000,-2000000000,-2000000000,-2000000000
#elif TEST==9	
	.int -3000000000,-3000000000,-3000000000,-3000000000
#elif TEST >= 10 && TEST <= 14
	.int 1,1,1,1
#elif TEST >= 15 && TEST <= 19
	.int -1,-1,-1,-1
#else
	.error "Definir TEST entre 1..19"
#endif
	.endm

	.macro linea0
#if TEST >= 1 && TEST<=9
	linea
#elif TEST==10
	.int 0,2,1,1
#elif TEST==11
	.int 1,2,1,1
#elif TEST==12
	.int 8,2,1,1
#elif TEST==13
	.int 15,2,1,1
#elif TEST==14
	.int 16,2,1,1
#elif TEST==15
	.int 0,-2,-1,-1
#elif TEST==16
	.int -1,-2,-1,-1
#elif TEST==17
	.int -8,-2,-1,-1
#elif TEST==18
	.int -15,-2,-1,-1
#elif TEST==19
	.int -16,-2,-1,-1
#else
	.error "Definir TEST entre 1..19"
#endif
	.endm
lista:	linea0
	.irpc i,123
		linea
	.endr

longlista:	.int   (.-lista)/4			# asi sabemos cuantos elementos hay en la lista
media:		.int   0
resto:		.int   0
formato:	.ascii 	"Media 32 = %11d = 0x%x hex\n" 
			.asciz  "Resto 32 = %11d = 0x%x hex\n"
formatoq:	.ascii  "Media 64 = %11ld = 0x%lx hex\n"
			.asciz  "Resto 64 = %11ld = 0x%lx hex\n"
mediaq: 	.quad 0
restoq: 	.quad 0

# opción: 1) no usar printf, 2)3) usar printf/fmt/exit, 4) usar tb main
# 1) as  suma.s -o suma.o
#    ld  suma.o -o suma					1232 B
# 2) as  suma.s -o suma.o				6520 B
#    ld  suma.o -o suma -lc -dynamic-linker /lib64/ld-linux-x86-64.so.2
# 3) gcc suma.s -o suma -no-pie –nostartfiles		6544 B
# 4) gcc suma.s -o suma	-no-pie				8664 B

.section .text
# _start: .global _start
main: .global  main
# trabajar:
	mov     $lista, %rbx
	mov  longlista, %ecx
	call suma		# == suma(&lista, longlista);
	mov  %eax, media
	mov  %edx, resto

	mov     $lista, %rbx
	mov  longlista, %ecx
	call sumaq
	mov %rax, mediaq
	mov %rdx, restoq


	# mov  %edx, resultado+4	# añadimos la parte mas significativa 4 bytes detras (concatenamos)
#	ret


# imprimir:
	# mov	  %edx, %ecx	# parte mas significativa | penultimo argumento
	# mov   %eax, %r8d	# parte menos significativa	| ultimo argumento
	mov   $formato, %rdi	# guardamos el formato
	mov   media,%esi	# y el resultado en los registros de 64bits
	mov   media,%edx
	mov   resto, %ecx
	mov   resto, %r8
	# para imprimir la parte mas significativa y la menos por separadao
	mov          $0,%eax	# varargin sin xmm
 	call  printf		# == printf(formato, media, resto,media,resto);


	# imprimir 64 bits
	mov $formatoq, %rdi
	mov mediaq, %rsi
	mov mediaq, %rdx
	mov restoq, %rcx
	mov restoq, %r8
	mov $0, %eax
	call printf


	mov  $0, %edi
	call _exit		# ==  exit(resultado)

suma:
	mov $0, %ebp 	# parte menos significativa
	mov $0, %edi	# parte mas significativa
	mov $0, %rsi	# indice

bucle:
	mov  (%rbx,%rsi,4), %eax  # el nuevo indice es RSI
	cltd 	  # extendemos el signo
	add %eax, %edi	# sumamos LSB
	adc %edx, %ebp	# sumamos MSB y el acarreo

	inc %rsi
	cmp %rsi, %rcx
	jne bucle

	mov %edi, %eax	# movemos a los registros necesarios para la funcion
	mov %ebp, %edx	# suma esta en edx:eax

	idiv %ecx # dividimos edx:eax entre ecx (numero de elementos de la lista, tambien se puede usar longlista)
	

	ret

noacarreo:
	inc   %rsi 	# incrementa indice
	cmp   %rsi,%rcx	# compara longitud
	jne    bucle
	ret

# 64 bits
sumaq:
	mov $0, %rdi	
	mov $0, %rsi	# indice

bucleq:
	mov  (%rbx,%rsi,4), %eax  # el nuevo indice es RSI
	cltq 	  # extendemos el signo EAX -> RAX
	cqto
	add %rax, %rdi	# sumamos LSB
	inc %rsi
	cmp %rsi, %rcx
	jne bucleq

	mov %rdi, %rax
	idiv %ecx # dividimos rdx:rax entre ecx (numero de elementos de la lista, tambien se puede usar longlista)
	

	ret

noacarreoq:
	inc   %rsi 	# incrementa indice
	cmp   %rsi,%rcx	# compara longitud
	jne    bucleq
	ret

