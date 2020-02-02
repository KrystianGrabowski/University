	.text
	.global	clz
	.type	clz, @function
    
    # Mam wyznaczyc dlugosc prefixu skladajacego sie z zer.
    # W pierwszej kolejnosci sprawdzam czy nasza liczba jest mniejsza lub rowna 
    # polowie maksymalnej liczby mozliwej do zapisania na 64 bitach.
    # Jesli jest mniejsza lub rowna od 0x00000000ffffffff to znaczy,
    # ze ostatnie 32 bity to 0. Usuwam policzone juz zera przesuwajac liczbe w 
    # lewo o 32 bity. Nastepnie sprawdzam czy nowo powstala liczba jest mniejsza lub rowna
    # masce przesunietej o 32/2 = 16 bitow w lewo. Jezeli tak, to znaczy ze ze kolejne 16 ostatnich
    # bitow liczby jest 0, dodaje wiec 16 do wyniku. Powtarzam proces az do sprawdzenia jednego bitu.
    # W przypadku, gdy liczba jest wieksza od maski to jedynie zwiekszam maske.
    # Piszac maska mam na mysli stala ktora co krok przesuwamy o n/2 zerowych bitow w jej prefiksie (0x00000000ffffffff, 0x0000ffffffffffff ..)

clz:
    mov $0, %rax 
    mov $0x00000000ffffffff, %r8
    cmp %r8, %rdi                   # porownanie rdi - r8 (liczba - maska)
    ja L1                           # jesli wynik > 0 to liczba wieksza od maski, wiec wykonuje skok i sprawdzam liczbe z wieksza maska
    add $32, %rax                   # jesli wynik <= 0 dodaje liczbe zer do wyniku
    sal $32, %rdi                   # usuwam zera ktore juz policzylem
L1:                                 # dalsze kroki to zamiana powyzszych szesciu instrukcji na sprawdzanie dla 16, 8, 4, 2, 1 bitow
    mov $0x0000ffffffffffff, %r8
    cmp %r8, %rdi
    ja L2
    add $16, %rax
    sal $16, %rdi
L2:
    mov $0x00ffffffffffffff, %r8
    cmp %r8, %rdi
    ja L3
    add $8, %rax
    sal $8, %rdi
L3:
    mov $0x0fffffffffffffff, %r8
    cmp %r8, %rdi
    ja L4
    add $4, %rax
    sal $4, %rdi
L4:
    mov $0x3fffffffffffffff, %r8
    cmp %r8, %rdi
    ja L5
    add $2, %rax
    sal $2, %rdi
L5:
    mov $0x7fffffffffffffff, %r8
    cmp %r8, %rdi # (*)
    ja L6
    add $1, %rax
    sal $1, %rdi
L6:
    mov $0x7fffffffffffffff, %r8    # Warunek specjalny dla 0 jesli wyzej(*) x <= masce (0x7fffffffffffffff)
    cmp %r8, %rdi                   # to moglo jeszcze zachodzic x = 0.
    ja L7
    add $1, %rax
L7:
    ret
	.size	clz, .-clz
