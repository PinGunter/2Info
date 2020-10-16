.section .data
lista:		.int 0xFFFF,0xFFFF,0xFFFF,0xFFFF
			.int 0xFFFF,0xFFFF,0xFFFF,0xFFFF
			.int 0xFFFF,0xFFFF,0xFFFF,0xFFFF
			.int 0xFFFF,0xFFFF,0xFFFF,0xFFFF

longlista:	.int   (.-lista)/4			# asi sabemos cuantos elementos hay en la lista
resultado:	.quad   0
formato: 	.asciz	"suma = %lu = 0x%lx hex\n"

# opción: 1) no usar printf, 2)3) usar printf/fmt/exit, 4) usar tb main
# 1) as  suma.s -o suma.o
#    ld  suma.o -o suma					1232 B
# 2) as  suma.s -o suma.o				6520 B
#    ld  suma.o -o suma -lc -dynamic-linker /lib64/ld-linux-x86-64.so.2
# 3) gcc suma.s -o suma -no-pie –nostartfiles		6544 B
# 4) gcc suma.s -o suma	-no-pie				8664 B

.section .text
 _start: .global _start
# main: .global  main

# 	call trabajar	# subrutina de usuario
# #	call imprim_C	# printf()  de libC
# 	call acabar_L	# exit()   del kernel Linux
# #	call acabar_C	# exit()    de libC
# 	ret

# trabajar:
	mov     $lista, %rbx
	mov  longlista, %ecx
	call suma		# == suma(&lista, longlista);
	mov  %eax, resultado
#	ret
	mov   $formato, %rdi
	mov   resultado,%rsi
	mov   resultado,%rdx
	mov          $0,%eax	# varargin sin xmm
	call  printf		# == printf(formato, res, res);

	mov  $0, %edi
	call _exit		# ==  exit(resultado)

suma:
	mov $0, %eax 	# la suma es la concatenacion de EDX:EAX # parte menos significativa
	mov $0, %edx	# parte mas significativa
	mov $0, %rsi
bucle:
	add  (%rbx,%rsi,4), %eax  # el nuevo indice es RSI
	jnc noacarreo
	inc %edx
noacarreo:
	inc   %rsi 	# incrementa indice
	cmp   %rsi,%rcx	# compara longitud
	jne    bucle
	ret
# imprim_C:			# requiere libC
#	
#	ret

# acabar_L:
#	mov        $60, %rax
#	mov  resultado, %edi
#	syscall			# == _exit(resultado)
#	ret

# acabar_C:			# requiere libC
#	mov  resultado, %edi
#	call _exit		# ==  exit(resultado)
#	ret
