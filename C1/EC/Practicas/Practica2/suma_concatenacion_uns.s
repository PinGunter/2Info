.section .data
lista:		.int 0xffffffff,0xffffffff,0xffffffff,0xffffffff
			.int 0xffffffff,0xffffffff,0xffffffff,0xffffffff
			.int 0xffffffff,0xffffffff,0xffffffff,0xffffffff
			.int 0xffffffff,0xffffffff,0xffffffff,0xffffffff

longlista:	.int   (.-lista)/4			# asi sabemos cuantos elementos hay en la lista
resultado:	.quad   0
formato:	.ascii 	"resultado \t = %18lu (uns)\n"
			.ascii	"\t\t = 0x%18lx (hex)\n"
			.ascii	"\t\t = 0x %08x %08x \n"

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
	mov  %eax, resultado
	mov  %edx, resultado+4	# añadimos la parte mas significativa 4 bytes detras (concatenamos)
#	ret


# imprimir:
	mov	  %edx, %ecx	# parte mas significativa | penultimo argumento
	mov   %eax, %r8d	# parte menos significativa	| ultimo argumento
	mov   $formato, %rdi	# guardamos el formato
	mov   resultado,%rsi	# y el resultado en los registros de 64bits
	mov   resultado,%rdx
	# para imprimir la parte mas significativa y la menos por separadao
	mov          $0,%eax	# varargin sin xmm
	call  printf		# == printf(formato, res, res,MSB,LSB);

	mov  $0, %edi
	call _exit		# ==  exit(resultado)

suma:
	mov $0, %eax 	# la suma es la concatenacion de EDX:EAX # parte menos significativa
	mov $0, %edx	# parte mas significativa
	mov $0, %rsi

bucle:
	add  (%rbx,%rsi,4), %eax  # el nuevo indice es RSI
	adc $0, %edx	# acumulamos el acarreo en edx. edx = 0 + acarreo
	# jnc noacarreo
	# inc %edx

noacarreo:
	inc   %rsi 	# incrementa indice
	cmp   %rsi,%rcx	# compara longitud
	jne    bucle
	ret
