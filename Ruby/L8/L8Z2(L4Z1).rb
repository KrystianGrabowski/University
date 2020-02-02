# Implementacja drzew poszukiwań binarnych
# zawierająca operacje wstawiania, usuwania
# umożiwiająca porównywanie i sprawdzanie istnienia elementu.
# Author::    Krystian Grabowsk



# Klasa zawierająca wskaźnik na korzeń drzewa.
# Umożliwia wykonywanie opracji takich jak wstaw, usuń, istnieje?

class DrzewoBinarne

    # Tworzy korzeń drzewa i przypisz mu wartość value.
    # Params:
    # +value+:: wartość nowego węzła
    def initialize(value)
        @root = Element.new(value)
    end

    # Wywołuje operację usunięcia na korzeniu drzewa.
    # Params:
    # +value+:: wartość do usunięcia
    def usun(value)
        @root = usun2(Element.new(value), @root)
    end

    # Wywołuje operację wstawienia węzła na korzeniu drzewa.
    # Params:
    # +value+:: wartość do wstawienia
    def wstaw(value)
        @root = wstaw2(Element.new(value), @root)
    end

    # Wywołuje operację sprawdzenia istnienia węzła na korzeniu drzewa.
    # Params:
    # +value+:: wartość do sprawdzenia
    def istnieje?(value)
        istnieje2?(Element.new(value), @root)
    end

    # Wstawia węzeł newElement do drzewa tree
    # w odpowienie miejsce. Jeśli tree jest nullem
    # tworzy nowe drzewo.
    # Params:
    # +newElement+:: Obiekt klasy +Element+
    # +tree+:: Obiekt klasy +Element+
    def wstaw2(newElement, tree)
        return newElement if tree.nil?
        return tree if newElement == tree
        if newElement < tree
            tree.left = wstaw2(newElement, tree.left)
        else
            tree.right = wstaw2(newElement, tree.right)
        end
        tree
    end 

    # Sprawdza czy węzeł newElement występuje w drzwie tree.
    # Zwraca true lub false w zależności od tego czy 
    # element występuje w drzewie.
    # Params:
    # +newElement+:: Obiekt klasy +Element+
    # +tree+:: Obiekt klasy +Element+
    def istnieje2?(newElement, tree)
        return false if tree.nil?
        return true if tree == newElement
        if newElement < tree
            istnieje2?(newElement, tree.left)
        else
            istnieje2?(newElement, tree.right)
        end
    end

    # Usuwa węzeł newElement z drzewa tree.
    # Jeśli tree jest nullem lub element nie 
    # występuje w drzewie zwraca nil
    # Params:
    # +newElement+:: Obiekt klasy +Element+
    # +tree+:: Obiekt klasy +Element+
    def usun2(element, tree)
        return nil if tree.nil?
        if element == tree
            if (tree.left.nil? && tree.right.nil?)
                tree = nil
            elsif tree.right.nil?
                tree = tree.left
            elsif tree.left.nil?
                tree = tree.right
            else
                tree.value = min(tree.right).value
                tree.right = usun2(min(tree.right), tree.right)
            end
        else
            if element < tree
                tree.left = usun2(element, tree.left)
            else    
                tree.right = usun2(element, tree.right)
            end
        end
        tree
    end

    # Znajduje najmniejszy element w drzewie tree (domyślnie @root).
    # Params:
    # +tree+:: Obiekt klasy +Element+
    def min(tree=@root)
        return tree if tree.left.nil?
        min(tree.left)
    end

    # Zwracająca string opisujący drzewo w postaci infiksowej.
    # Params:
    # +tree+:: Obiekt klasy +Element+
    def to_s(tree=@root)
        return "" if tree.nil?
        return "#{to_s(tree.left)} #{tree.value.to_s} #{to_s(tree.right)}" 
    end
end


# Klasa umożliwiająca wstawianie od drzewa obiektów typu string.
class StringBT < DrzewoBinarne
    
end

# Klasa przechowująca wartość węzła oraz jego prawe i lewe dziecko.
# Umożliwia porównywanie węzłów dzięki zaimplementowanej metodzie <=>
# oraz dołączonemu modułowi Comparable.


class Element
    include Comparable

    # Wartość węzła 
    attr_accessor :value
    # Lewe dziecko
    attr_accessor :left
    # Prawe dziecko
    attr_accessor :right
    
    # Prównuje dwa obiekty klasy +Element+.
    # Params:
    # +otherElement+:: Obiekt klasy +Element+
    def <=>(otherElement)
        value <=> otherElement.value   
    end

    # Przypisuje wartość korzenia oraz jego lewego 
    # oraz prawego dziecka.
    # Params:
    # +value+:: Dowolny element 
    # +left+:: Obiekt klasy +Element+ lub nil
    # +right+:: Obiekt klasy +Element+ lub nil
    def initialize(value, left=nil, right=nil)
        @value = value
        @left = left
        @right = right
    end

    # Zwracająca string opisujący korzeń.
    def to_s
        "Value:#{@value.inspect} Left:#{@left.inspect} Right:#{@right.inspect}"
    end
end
