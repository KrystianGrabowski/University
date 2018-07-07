def palindrome?(str)
  str = (str.gsub(/[^a-z]/i, '')).downcase
  str==str.reverse
end

def test_palidnrome(string, result)
  raise "Wrong answer" unless palindrome?(string) == result
end

def pal_tests()
  test_palidnrome("A man, a plan, a canal -- Panama", true)
  test_palidnrome("k<a1^2ja,kj32>1ak%k3,ajk42a%^jak", true)
  test_palidnrome("Madam, I'm Adam!", true)
  test_palidnrome("Abracadabra", false)
  test_palidnrome("", true)
  test_palidnrome("ptpppppppppppp-ppppppppppptp", true) 
end

def count_words(str)
  words = Hash.new(0)
  str = (str.gsub(/[^a-z]/i, ' ')).downcase
  str.downcase.split(" ").each do |w|
    words[w] += 1
  end
  words
end

def test_count(string, result)
  raise "Wrong answer" unless count_words(string) == result
end


def count_tests()
  test_count(" ", {})
  test_count("A man, a plan, a canal -- Panama",
    {'a' => 3, 'man' => 1, 'canal' => 1, 'panama' => 1, 'plan' => 1}) 
  test_count("dlugi tekst, raz, dwa, tszy, tekst1 tekst 2 ---> tekst /d/as 3",
    {'dlugi' => 1, 'tekst' => 4, 'raz' => 1, 'dwa' => 1, 'tszy' => 1, 'd' => 1, "as" => 1})
end



def same23?(str)
  return false if ((str.length) != 5)
  tab = [str.count("a"), str.count("b"), str.count("c")]
  tab.include?(2) and tab.include?(3)
end

def test_same23(string, result)
  raise "Wrong answer" unless same23?(string) == result
end
  
def same_tests()
  test_same23(["c", "c", "a", "b", "b", "b"], false) #=> true // 1x "a" and 3x "b" and 3x "c"
  test_same23(["a", "a", "a", "b", "b", "b"], false) #=> false // 3x "a" and 3x "b"
  test_same23(["a", "a", "a", "a", "b", "b"], false) #=> false // 4x "a" and 2x "b"
  test_same23(["a", "a", "a", "b", "b"], true) #=> true // 3x "a" and 2x "b"
  test_same23(["a", "b", "c", "b", "c"], false) #=> false // 1x "a", 2x "b" and 2x "c"
  test_same23(["a", "a", "a", "a", "a"], false) #=> false // 5x "a"
  test_same23([], false) #=> false
end



pal_tests()
count_tests()
same_tests()


