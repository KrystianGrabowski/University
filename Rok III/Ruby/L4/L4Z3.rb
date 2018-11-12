class DrzewoBinarne
    def initialize(value)
        @root = Element.new(value)
    end
    def usun(value)
        @root = usun2(Element.new(value), @root)
    end
    def wstaw(value)
        @root = wstaw2(Element.new(value), @root)
    end
    def istnieje?(value)
        istnieje2?(Element.new(value), @root)
    end

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
    def istnieje2?(newElement, tree)
        return false if tree.nil?
        return true if tree == newElement
        if newElement < tree
            istnieje2?(newElement, tree.left)
        else
            istnieje2?(newElement, tree.right)
        end
    end
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
    def min(tree=@root)
        return tree if tree.left.nil?
        min(tree.left)
    end
    def to_s(tree=@root)
        return "" if tree.nil?
        return "#{to_s(tree.left)} #{tree.value.to_s} #{to_s(tree.right)}" 
    end
end

class StringBT < DrzewoBinarne
    
end

class Element
    include Comparable
    attr_accessor :value, :left, :right 
    def <=>(otherElement)
        value <=> otherElement.value   
    end
    def initialize(value, left=nil, right=nil)
        @value = value
        @left = left
        @right = right
    end
    def to_s
        "Value:#{@value.inspect} Left:#{@left.inspect} Right:#{@right.inspect}"
    end
end

bt = DrzewoBinarne.new(2)
puts bt
bt.wstaw(4)
bt.wstaw(1)
puts bt
bt.wstaw(3)
bt.wstaw(5)
puts bt
puts bt.istnieje?(2)
bt.usun(2)
puts bt.istnieje?(2)
puts bt
bt.usun(1)
puts bt
bt.usun(3)
puts bt
bt.usun(4)
bt.usun(5)
puts bt

sbt = StringBT.new("bbb")
puts sbt
sbt.wstaw("aaaa")
sbt.wstaw("bb")
puts sbt.istnieje?("bbbb")
puts sbt
sbt.wstaw("ccczz")
puts sbt
sbt.usun("bbb")
puts sbt
sbt.usun("ccczz")
puts sbt
sbt.usun("bb")
puts sbt.istnieje?("bb")
sbt.usun("aaaa")
puts sbt



