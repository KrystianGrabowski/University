#!/usr/bin/ruby

@tab10 = ["zero", "jeden", "dwa", "trzy", "cztery", "pięć", "sześć", "siedem", "osiem", "dziewięć"]
@tab20 = ["dziesięć", "jedenaście", "dwanaście", "trznaście", "czternaście", "piętnaście", "szesnaście", "siedemnaście", "osiemnaśćie", "dziewiętnaście"]
@tab100 = ["dwadzieścia", "trzydzieści", "czterdzieści", "pięćdziesiąt", "sześćdziesiąt", "siedemdziesiąt", "osiemdziesiąt", "dziewięćdziesiąt"]
@tab1000 = ["sto", "dwieście", "trzysta", "czterysta", "pięćset", "sześćset", "siedemset", "osiemset", "dziewięćset"]
@tab1000000 = ["tysiąc", "tysiące", "tysięcy"]

def slownie(x)
    digits = x.to_s.split("").map{|item| item.to_i}
    length = digits.length + 1
    text = ""
    for i in digits
        length-=1
        next if i == 0
        case length
            when 4
                case i
                    when 1
                        text = text + @tab1000000[0] + " "
                    when 2..4
                        text = text + @tab10[i] + " " + @tab1000000[1] + " "
                    else
                        text = text + @tab10[i] + " " + @tab1000000[2] + " "
                    end
            when 3
                text = text + @tab1000[i-1] + " "
            when 2
                return text + @tab20[digits[-1]] if i == 1
                text = text + @tab100[i-2] + " "
            else
                text = text + @tab10[i]
        end
    end
    text.empty? ? "zero" : text
end

Test = [0,7,11,63,122,863,1024,2799,3942,5555,7532,5555,9999]
for t in Test
    puts "%d -> %s" % [t, slownie(t)] # 9999max
end







=begin
def slownie(x)
    digits = x.to_s.split("")
    length = digits.length
    text = ""
    for i in digits
        x = i.to_i
        if x == 0 and digits.length == 0
            return tab10[0]
        elsif x == 0 and digits.length != 1
            length = length - 1
            next
        elsif length == 4
            case x
                when 1
                    text = text + @tab1000000[0] + " "
                when 2..4
                    text = text + @tab10[x] + " " + @tab1000000[1] + " "
                else
                    text = text + @tab10[x] + " " + @tab1000000[2] + " "
            end
        elsif length == 3
            text = text + @tab1000[x-1] + " "
        elsif length == 2 and x == 1
            text = text + @tab20[digits[-1].to_i]
            return text
        elsif length == 2
            text = text + @tab100[x-2] + " "
        else
            text = text + @tab10[x]
        end
        length -= 1
    end
    text
end
=end
