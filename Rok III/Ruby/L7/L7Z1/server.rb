require "drb"
require 'dbm'
require 'time'
#require_relative "kernel"

class LogSerwer
    def initialize()
        db_open
    end

    def db_open
        @db = DBM.open('z1', 0666, DBM::WRCREAT) 
    end

    def my_db_add(log_time ,prg_id, msg)
        @db[log_time] = "#{prg_id}|#{msg}"
    end

    def save(prg_id, msg)
        fn = Time.new.to_s
        my_db_add(fn, prg_id, msg)
    end

    def LogSerwer.Run
       @@server = LogSerwer.new
        DRb.start_service( 'druby://localhost:9000', @@server)
        DRb.thread.join
    end

    def db_all()
        @db.each do |k, v|
            print "#{k}: #{v.split("|").join(" ")}\n"
        end
    end

    def raport(time_start, time_end, prg_id, re)
        str = ""
        @db.each do |k, v|
            log_time = Time.parse(k)
            tab = v.split("|")
            if time_start <= log_time and log_time <= time_end
                if prg_id == tab[0].to_i && re.match(tab[1])
                    str << "#{k}: #{v.split("|").join(" ")}<br>"
                end
            end
        end
        html = "<html> <body>" + str + "</body>"
    end

    def export(str)
        file = File.open("file.html", 'w')
        file << str
        file.close
    end

end


s = LogSerwer.new
s.db_all
puts("------------")
s.export(s.raport(Time.parse("2018-12-1 20:30"), Time.parse("2018-12-1 21:14"), 1, /test/))

#LogSerwer.Run