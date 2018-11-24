require 'open-uri'
require 'set'

class WebAgent
    @@linkexpr1 = /<a[^>]*href\s*=\s*"([^|#@"]*)"/i
    @@linkexpr = /<a[^>]*href\s*=\s*"([^|#@?\s%"]*)"/i

    @content = ""
    def initialize()
        @visited_urls = Set.new()
        @current_urls = Set.new()
    end

    def revise(start_page, depth, block)
        return if depth == -1
        @url = start_page
        block.call(@url)
        @visited_urls << @url
        if depth != 0
            new_urls = Set.new(find_links(@content))
            @current_urls = new_urls - @visited_urls
            for url in @current_urls
                revise(url, depth-1, block )
            end
        else
            return
        end
    end

    def content(page_address)
        begin
            open(page_address) do | fh |
                @content = fh.read
            end
        rescue => e
            puts e
            @content = "ERROR"
        end
    end

    def find_links(page_address)
        begin 
            @content.scan(@@linkexpr).map {|p_url| p_url[0].match(/^http|https/)? p_url[0] : make_full_link(p_url[0]) }
        rescue => e
            puts e
            @content = "ERROR"
            return Array.new()
        end        
    end

    def make_full_link(link)
        now =/.*\/\/[^\/]*\//.match(@url).to_s
        if (/^\//.match(link) and now[-1] == '/')
            now + link[1..-1]
        elsif (link.length != 0 && link[0] != '/' && now[-1] != '/')
            now + '/' + link
        else
            now + link
        end
    end

    def page_weight(page_address)
        @content = content(page_address)
        re = /(<img([\w\W]+?)>)|(<applet([\w\W]+?)>)/i
        puts "#{page_address} #{@content.scan(re).length}"
    end

    def page_summary(page_address)
        @content = content(page_address)
        re = /<title>.*<\/title>|<meta[^>]*>/m
        puts "URL: #{page_address}"
        puts extract_head().scan(re)
        puts
    end
    
    def extract_head()
        re = /<head[^>]*>(.*)<\/head>/m
        re.match(@content)[1]
    end


end

page1 = WebAgent.new()
start = Time.now
page1.revise('http://www.ii.uni.wroc.pl/', 1, lambda {|text| page1.page_weight(text)} )
finish = Time.now
diff = finish - start
puts diff

#page1.revise('http://www.ii.uni.wroc.pl/', 1, lambda {|text| page1.page_weight(text)} )
#page1.revise('http://www.ii.uni.wroc.pl/', 1, lambda {|text| page1.page_summary(text)})