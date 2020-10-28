.section .data
lista:		.int 0x5,0x5,0x5,0x5
			.int 0x5,0x5,0x5,0x5
			.int 0x5ffff,0x5,0x5,0x5
			.int 0x5,0x5,0x5,0x5

longlista:	.int   (.-lista)/4			# asi sabemos cuantos elementos hay en la lista
media:	.int   0
resto:	.int   0
formato:	.ascii 	"Media = %d = 0x%x hex\n" 
			.ascii  "Resto = %d = 0x%x hex\n"
			

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
