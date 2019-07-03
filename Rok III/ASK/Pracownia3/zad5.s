read = 0
write = 1
exit  = 60
.section .data
    .global _start
    .type _start, @function
    .section .text

    # Chce wczytac ze standardowego wejscia ciag znakow do bufora
    # przydzielonego na stosie, po czym wypisac je w odwrotnej kolejnosci.
    # W tym celu uzywam wywolan funcji systemowych read oraz write.
    # Moj program wczytuje funkcja read znaki na stos(az read zwroci 0). Nastepnie za pomoca 
    # adresu ostatniego wczytanego elementu zaczynam wypisywac napis od tylu. 
    # Wypisuje po jednym znaku zaczynajac od konca i przesuwajac wskaznik w
    # kierunku poczatku napisu. W ten sposob wypisze znaki w odwrotnej kolejnosci.

_start: 
    movq %rsp, %r14
    leaq -1(%rsp), %r13
    movq $read, %rax       # chce wczytac ciag znakow
    movq $0, %rdi          # wczytuje ze standardowego wejscia
    movq $1, %rdx          # ilosc znakow do wczytania
L0:
    leaq 1(%r13), %r13     # dodaje do adresu wskaznika 1
    movq %r13, %rsi        # podaje funkcji wskaznik wskazujacy na miejsce do wpisania znaku
    syscall                # wywolanie funkcji read
    cmpq $0, %rax
    movq $read, %rax       # chce wczytac ciag znakow
    jne L0

    movq $write, %rax      # chce wypisac ciag znakow
    movq $1, %rdi          # wypisuje na standardowe wyjscie
    movq $1, %rdx          # bede wypisywal po 1 znaku
L1:
    leaq -1(%r13), %r13    # odejmuje 1 od adresu wskaznika
    movq %r13, %rsi        # podaje funkcji write ten argument
    syscall                # wywoluje funkcje write
    cmpq %r13, %r14        # sprawdzam czy wypisalem juz wszystkie znaki
    jb L1                  # jesli nie to powtarzam proces

    movq    $exit, %rax    # koncze dzialanie programu
    movq    $0, %rdi
    syscall
        
    .size   _start, . - _start
    