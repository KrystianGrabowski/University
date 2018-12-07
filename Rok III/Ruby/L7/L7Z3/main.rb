require "drb"
require 'thread'
#require_relative "kernel"
class Status
    def initialize()
        open("list.txt", 'r') do | fh |
            fh.each_line { | line | (@list ||= []) << line }
        end
    end

    def cpu_memory(commands)
        for server in @list
            obj = DRbObject.new_with_uri(server)
            if obj.respond_to?('save')
                puts server
                commands.each {|command| print obj.save(command)}
            end
        end
        puts("++++++++++++++++++++++++++++++++++++++++++++++++")
    end

    def start_check(commands)
        @end = false
        @t = Thread.new do
            while (!@end)
                cpu_memory(commands)
                sleep 15
            end
        end
    end

    def end_check()
        @end = true
        @t.join
    end
end

s = Status.new
#s.start_check(['df -h', 'top -n 1'])
#s.start_check(['df -h /home/ ',"grep 'cpu ' /proc/stat | awk '{usage=($2+$4)*100/($2+$4+$5)} END {print usage}'"])
#s.start_check(['df','top -n 1'])
s.start_check(['df -h /home', 'top -n 1| grep Cpu'])
sleep(30)
s.end_check

