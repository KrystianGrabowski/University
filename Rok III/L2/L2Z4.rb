def statystyka_slow0(name)
    text = IO.read(name)
    text = text.gsub(/[\W&&\S&&[^zżźćńółęąśŻŹĆĄŚĘŁÓŃ]]+/, "")
    hash = Hash.new(0.0)
    array = text.split(" ")
    total_size = array.size
    array.each{|it| hash[it.downcase] += 1}
    hash.each{|k, v| hash[k] =  (v/total_size * 100).round(4) } 
    hash = Hash[hash.sort_by{|key, value| value}]
end

start = Time.now
#puts statystyka_slow0("komedia.txt")
puts
puts statystyka_slow0("tragedia.txt")
stop = Time.now
puts stop-start



























=begin
def statystyka_slow1(name)
    my_file = File.open(name, 'r')
    text = my_file.read.gsub(/[\W&&\S&&[^zżźćńółęąśŻŹĆĄŚĘŁÓŃ]]+/, "")
    my_file.close
    array = text.split(" ")
    total_size = array.size
    hash = Hash.new(0.0)
    text.split(" ").each{|it| hash[it.downcase] += 1}
    hash.each{|k, v| hash[k] =  (v/total_size * 100).round(4)}
    hash = Hash[hash.sort_by{|key, value| value}]
end

def statystyka_slow2(name)
    my_file = File.open(name, 'r')
    text = my_file.read.gsub(/[\W&&\S&&[^zżźćńółęąśŻŹĆĄŚĘŁÓŃ]]/, "")
    i = 0
    hash = Hash.new(0.0)
    text.scan(/[0-9A-Za-zżźćńółęąśŻŹĆĄŚĘŁÓŃ]+/) {|it| hash[it.downcase] += 1; i+=1}
    hash.each{|k, v| hash[k] =  (v/i * 100).round(4)}
    hash = Hash[hash.sort_by{|key, value| value}]

end

def statystyka_slow3(name)
    my_file = File.open(name, 'r')
    text = my_file.read #gsub(/[\W&&\S&&[^zżźćńółęąśŻŹĆĄŚĘŁÓŃ]]/, "")
    i = 0
    hash = Hash.new(0.0)
    text.scan(/[0-9A-Za-zżźćńółęąśŻŹĆĄŚĘŁÓŃ]+/) {|it| hash[it.downcase] += 1; i+=1}
    hash.each{|k, v| hash[k] =  (v/i * 100).round(4)}
    hash = Hash[hash.sort_by{|key, value| value}]
end

=end