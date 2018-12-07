require "drb"
#require_relative "kernel"

class LogSerwer
    def save(str)
        `#{str}`
    end
    def LogSerwer.Run
       @@server = LogSerwer.new
        DRb.start_service( 'druby://localhost:7000', @@server)
        DRb.thread.join
        
    end
end
$SAFE = 0
LogSerwer.Run