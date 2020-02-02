	.text
	.global	sqrf
	.type	sqrf, @function

    # Chce obliczyc kwadrat liczby zmiennopozycyjnej reprezentowanej 
    # przez 32-bitowe slowo. Liczba ta ma postac [s eeeeeeee mmmmmmmmmmmmmmmmmmmmmmm] (1)(8)(23).
    # S to znak liczby e to wykladnik a m to mantysa. Jako ze licze kwadrat liczby to znak 
    # zawsze bedzie rowny 0. Aby pomnozyc liczby moge skorzystac ze wzoru
    # (2^e1*m1) * (2^e2*m2) = 2^(e1+e2)*m1*m2. Wiec wystarczy dodac wykladniki
    # oraz pomnozyc mantysy danych liczb (mozemy zignorowac znak).

sqrf:
    movq $0, %rax
    movq %rdi, %r10            # kopiuje liczbe do r10
    shrq $23, %r10             # przesuwam liczbe w prawo o 23 aby wydobyc wykladnik
    andq $0xff, %r10           # anduje powstala liczbe z maska 0 1111 1111 aby pozbyc sie znaku
    cmpq $0, %r10              # jesli wykladnik rowny 0 to mozemy zwrocic 0
    je L1
    subq $127, %r10            # odejmuje Bias aby uzyskac faktyczna wartosc wykladnika
    addq %r10, %r10            # podwajam wartosc wykladnika
    addq $127, %r10            # dodaje na nowo Bias

    movq %rdi, %rax
    andq $0x7FFFFF, %rax       # wyodrebniam 23 bity mantysy
    addq $0x800000, %rax       # mantysa jest z przedzialu [1,2) wiec dodaje 1 na poczatek przed pomnozeniem (jedynka nie jest zapisywana)
    imulq %rax, %rax           # mnoze mantyse przez sama siebie
    shrq $23, %rax             # jako ze na najbardziej znaczym bicie jest po dodaniu zawsze 1 (mantysa znormalizowana)
                               # to wynik takiego mnozenia musze przesunac o 23 bity w prawo. W ten sposob na bicie 24
                               # liczac od najmniej znaczacego otrzymam jedynke.
    
    cmpq $0x01000000, %rax     # sprawdzamy czy wystapilo przeniesienie (na bicie numer 25 bedzie 1)
    jb L0
    addq $1, %r10              # jesli wystapilo przeniesienie to musze dodac jeden do wykladnika
    shrq $1, %rax              # oraz przesunac mantyse w prawo o jedna pozycje
L0:
    subq $0x800000, %rax       # usuwam jedynke z bitu numer 24 aby przywrocic oczekiwana wartosc mantysy
    salq $23, %r10             # ustawiam wykladnik na odpowiednia pozycje
    orq %r10, %rax             # operacja or lacze mantyse z wykladnikiem i otrzymuje nowa liczbe bedaca kwadratem argumentu
L1:
    ret
	.size	sqrf, . - sqrf
