	.text
	.global	revbit
	.type	revbit, @function

    # Mam wyznaczyc odbicie lustrzane bitow.
    # Dziele ilosc bitow na dwie czesci (po 32 bity), a nastepnie
    # zamieniam polowki miejscami. Pozniej wystarczy odwrocic lewa i
    # prawa czesc osobno za pomoca masek. 
    # Majac 32 bitowe slowo zamieniam za pomoca maski jego poczatkowe oraz
    # koncowe 16 bitow. Nastepnie w dwoch slowach po 16 bitow zaminiam miejscami 
    # poczatkowe 8 bitow i koncowe 8 bitow. Powtarzam operacje az uzyskamy
    # odwrotny szyk bitow niz na poczatku (az zamienimy po jednym bicie).

revbit:
    mov %rdi, %rax
    shr $32, %rdi
    sal $32, %rax
    or %rdi, %rax  # zamieniam pierwsze 32 bity z ostatnimi.
    
    mov $0x0000ffff0000ffff, %rdi       # maska wyodrebniajaca pierwsze 16 bitow z kazdego slowa
    and %rax, %rdi                      # wyciagam pierwsze 16 bitow z pierwszego oraz drugiego slowa
    mov $0xffff0000ffff0000, %r8        # maska do pozostalych bitow (koncowe 16 bitow)
    and %r8, %rax                       # wyciagam ostatnie 16 bitow z pierwszego oraz drugiego slowa
    shr $16, %rax                       # ustawianie bitow na odpowiednich pozycjach (zamiana)
    sal $16, %rdi                       # przesuwamy rax o 16 bitow w prawo a rdi o 16 w lewo co po polaczeniu zaskutkuje zamiana miejsc
    or %rdi, %rax                       # operacja or lacze tworze nowy ciag z zamienionymi bitami


    # dalsze operacje sa analogiczne do powyzszych siedmiu.
    # zamieniamy w nich kolejno 8, 4, 2 oraz 1 bit nastepujace po sobie.
    # W rezultacie otrzymujemy odwrocone ciagi.

    mov $0x00ff00ff00ff00ff, %rdi # 0000 0000 1111 1111
    and %rax, %rdi
    mov $0xff00ff00ff00ff00, %r8  # 1111 1111 0000 0000
    and %r8, %rax
    shr $8, %rax
    sal $8, %rdi
    or %rdi, %rax

    mov $0x0f0f0f0f0f0f0f0f, %rdi # 0000 1111 0000 1111 ...
    and %rax, %rdi
    mov $0xf0f0f0f0f0f0f0f0, %r8  # 1111 0000 1111 0000 ...
    and %r8, %rax
    shr $4, %rax
    sal $4, %rdi
    or %rdi, %rax

    mov $0x3333333333333333, %rdi # 0011 0011 0011 0011 ...
    and %rax, %rdi
    mov $0xcccccccccccccccc, %r8  # 1100 1100 1100 1100 ...
    and %r8, %rax
    shr $2, %rax
    sal $2, %rdi
    or %rdi, %rax

    mov $0x5555555555555555, %rdi # 0101 0101 0101 0101 ...
    and %rax, %rdi
    mov $0xaaaaaaaaaaaaaaaa, %r8  # 1010 1010 1010 1010 ...
    and %r8, %rax
    shr $1, %rax
    sal $1, %rdi
    or %rdi, %rax
    ret
	.size	revbit, .-revbit
