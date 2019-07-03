	.text
	.global	add_bignum
	.type	add_bignum, @function

    # Wyznaczajac sume a oraz b iteruje po ich tablicach
    # digits od najmniej znaczacego bajtu. Dodaje liczbe zapisana
    # w a na danym bajcie do liczby zapisanej w b na odpowiadajacym bajcie.
    # Jesli liczba mozliwa do zapisania na jednym bajcie wyjdzie poza zakres
    # to w kolejnej iteracji dodaje 1 do wyniku dodawania. 

add_bignum:
    movq (%rdi), %rax              # porownuje liczbe bajtow a oraz b. Wieksza z nich
    movq (%rsi), %rbx              # bedzie iloscia iteracji.
    cmpl %eax, %ebx
    ja T1
    movl %eax, %ecx
    jmp T2
T1:
    movl %ebx, %ecx
T2:
    movq $0, %r10
    movq $0, %rbx
    movq (%rsi), %r8               # W rejestrach r8 oraz r9 zapamietuje liczbe bajtow
    movq (%rdi), %r9               # tablicy digits w b oraz a

AddLoop:
    leaq 4(%rdx, %r10, 1), %r15   # adres pierwszego elementu digits struktury r
    cmpl %r10d, %r8d              # sprawdzam czy nie wychodze poza zakres tablicy b
    ja S1a
    movq $0, %r11                 # w przypadku wyjscia poza zakres zapisuje w r11 liczbe 0
    jmp S1
S1a:
    movq 4(%rsi, %r10, 1), %r11   # jesli zakres jest poprawny zapisuje w r11 wartosc tablicy
S1:
    movb %r11b, (%r15)            # przenosze wartos r11 do nowej struktury r pod odpowiedni adres (tablica digits)
    cmpl %r10d, %r9d              # dla struktury a wykonuje analogiczny proces
    ja S2a
    movq $0, %r11
    jmp S2
S2a:
    movq 4(%rdi, %r10, 1), %r11
S2:
    addb %r11b, (%r15)            # dodaje wartosc do poprzednio przeniesonej liczby z b
    jb L1                         # sprawdzam czy nie wyszedlem poza zakres
    addb %bl, (%r15)              # dodaje bit z poprzedniej iteracji
    jb L2                         # jesli zapalila sie flaga CF to w nastepej iteracji musze dodac 1 do wyniku (skoro flaga sie zapalila to bl = 1)
    movq $0, %rbx                 # jesli nie wyszedlem poza zakres to w nastepnej iteracji dodaje 0
    jmp L2
L1:
    addb %bl, (%r15)              # dodaje bit z poprzedniej iteracji
    movq $1, %rbx                 # jesli wyszedlem poza zakres to w nastepnej iteracji dodaje 1
L2:
    addq $1, %r10                 # iterator++
    cmpl %ecx, %r10d              # sprawdzam czy koniec
    jne AddLoop

    leaq 4(%rdx, %r10, 1), %r15   # jesli na koniec rbx = 1 to trzeba przeniesc 1 na kolejny bit (bardziej znaczacy)
    addq %rbx, (%r15)
    ret

	.size	add_bignum, . - add_bignum
