require_relative "L8Z2(L4Z1).rb"
require "test/unit"
 
class TestSimpleNumber < Test::Unit::TestCase
  
  def test_random
    assert_nothing_raised() { DrzewoBinarne.new(-102) }
    assert_nothing_raised() { Element.new(66, nil,) }
    assert_nothing_raised() { StringBT.new("alibaba") }
  end
  
  def test_initial_value_exists
    tree = DrzewoBinarne.new(54)
    assert tree.istnieje?(54)
    assert !tree.istnieje?(55)
  end

  def test_delete
    tree = DrzewoBinarne.new(54)
    tree.usun(54)
    assert_equal tree.istnieje?(54), false
  end

  def test_five_values
    tree = DrzewoBinarne.new(54)
    (1..5).each {|x| tree.wstaw(x)}
    (3.downto(1)).each {|x| tree.usun(x)} 
    assert_equal tree.istnieje?(4), true
    assert_equal tree.istnieje?(5), true
    assert_equal tree.istnieje?(3), false
  end

  def test_min
    tree = DrzewoBinarne.new(54)
    (1..10).each {|x| tree.wstaw(x)}
    assert_equal tree.min.value, 1
  end



  def test_element
    a = Element.new(2, Element.new(1), Element.new(3))
    assert_equal a.value, 2
    assert_equal a.left.value, 1
    assert_equal a.right.value, 3

  end

end