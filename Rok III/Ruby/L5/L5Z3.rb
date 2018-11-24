require 'open-uri'
require 'set'

class WebDistanceAgent
    @@max_depth = 3
    @@linkexpr = /<a[^>]*href\s*=\s*"([^|#@?\s"]*)"/i
    @content = ""
    
    def initialize()
        @visited_urls = Set.new()
        @current_urls = Set.new()
        @new_urls = Set.new()
        @min_result = -1
    end

    def distance(page_a, page_b)
        print "#{page_a} => #{page_b} : "
        @success = false
        @end_page = page_b
        @visited_urls << page_a
        search(Set.new() << page_a, 1)
        if @min_result == -1
            return "No results"
        else
            return @min_result
        end
    end

    def search(set, depth)
        return 0 if depth == @@max_depth
        for i in set
            @content = content(i)
            @current_page = i
            @current_urls += find_links(i)
        end
        @current_urls = @current_urls - @visited_urls
        if @current_urls.member?(@end_page)
            @min_result = depth
            return
        else
            @new_urls = @current_urls.clone
            @visited_urls += @current_urls
            @current_urls = Set.new()
            search(@new_urls, depth+1 )
        end
    end

    def make_full_link(link)
        now =/.*\/\/[^\/]*\//.match(@current_page).to_s
        if (/^\//.match(link) and now[-1] == '/')
            now + link[1..-1]
        elsif (link.length != 0 && link[0] != '/' && now[-1] != '/')
            now + '/' + link
        else
            now + link
        end
    end

    def content(page_address)
        begin
            open(page_address) do | fh |
                @content = fh.read
            end
        rescue => e
            @content = "ERROR"
        end
    end

    def find_links(page_address)
        begin 
            @content.scan(@@linkexpr).map {|p_url| p_url[0].match(/^http|https/)? p_url[0] : make_full_link(p_url[0]) }
        rescue => e
            @content = "ERROR"
            return Array.new()
        end        
    end
end

page1 = WebDistanceAgent.new()
puts page1.distance('http://www.ii.uni.wroc.pl/', 'http://zapisy.ii.uni.wroc.pl' )
puts page1.distance('http://www.ii.uni.wroc.pl/', 'http://www.ii.uni.wroc.pl/instytut/pracownicy/30' )