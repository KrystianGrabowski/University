	.text
	.global	insert_sort
	.type	insert_sort, @function

    # Insert sort
    # Chcac posortowac ciag liczb (x1, x2 .. xn) zapamietuje
    # rejestrze wartosc e ktora jest kolejno x2, x3 ... xn oraz
    # wskaznik na element ja poprzedzajacy. Iteruje w kierunku poczatku tablicy
    # (odejmuje po 8 od wskaznika w petli wewnetrznej) az dotre do wskaznika 
    # na poczatek tablicy. W wewnetrznej peli porownuje e z elementem na ktory
    # wskazuje wskaznik. Jesli e jest mniejsze od elementu pod wskaznikiem,
    # to zamieniam pozycja te dwa elementy. Jesli e wieksze lub rowne elementowi pod wskaznikiem 
    # to przerywam petle wewnetrzna, przyjmuje za e kolejny element xk. Powtarzam proces 
    # dopoki ostatni element nie zostanie wstawiony w odpowiednie miejsce. 

insert_sort:
    movq $0, %r15
    cmpq %rdi, %rsi                 # sprawdzam czy wskaznik na koniec rowna sie wskaznikowi  
    je LE                           # na poczatek. Wtedy tablicy nie trzeba sortowac.
L0:
    addq $1, %r15                   # iterator++
    leaq (%rdi, %r15, 8), %r8       # wskaznik na element do wstawienia
    movq (%rdi, %r15, 8), %r9       # wartosc elementu do wstawienia
    leaq (%rdi, %r15, 8), %r10      # wskaznik na pozycje poczatkowa elementu do wstawienia
L1:
    leaq -8(%r8), %r8               # wskaznik na element do wstawienia zamieniam na wskaznik na jego poprzednika w tablicy
    cmpq (%r8), %r9                 # porwnuje wartosc elementu do wstawienia(e) do elementu pod wskaznikiem r8
    jns L11
    movq (%r8), %rax                # e mniejsze od elementu pod wskaznikiem
    movq %rax, 8(%r8)               # element pod adresem r8 przenosze pod adres r8 + 8
    movq %r9, (%r8)                 # wstawiam element e pod adres na ktory wskazuje r8
    cmpq %r8, %rdi                  # sprawdzam czy wskaznik r8 jest rozny od wskaznika na poczatek tablicy
    jne L1
L11:
    cmpq %r10, %rsi                 # sprawdzam czy wstawiony element byl ostatnim w tablicy
    jne L0
LE:    
    ret

	.size	insert_sort, . - insert_sort
