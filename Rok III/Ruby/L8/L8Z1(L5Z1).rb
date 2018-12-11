require 'open-uri'
require 'set'
require 'benchmark'
require "thread"
require 'resolv-replace'

class WebAgent
    @@linkexpr1 = /<a[^>]*href\s*=\s*"([^|#@"]*)"/i
    @@linkexpr = /<a[^>]*href\s*=\s*"([^|#@?\s%"]*)"/i

    def initialize()
        @visited_urls = Set.new()
    end

    def revise(start_page, depth, block)
        return if depth == -1
        url = start_page
        content = content(url)
        block.call(url, content)
        @visited_urls << url
        if depth != 0
            new_urls = Set.new(find_links(url, content)) - @visited_urls
            for url in new_urls
                revise(url, depth-1, block)
            end
        else
            return
        end
    end

    def content(page_address)
        begin
            open(page_address) do | fh |
                fh.read
            end
        rescue => e
            puts e
            ""
        end
    end

    def find_links(base, page)
        begin 
            page.scan(@@linkexpr).map {|p_url| p_url[0].match(/^http|https/)? p_url[0] : make_full_link(base, p_url[0]) }
        rescue => e
            puts e
            return Array.new()
        end        
    end

    def make_full_link(base, link)
        now =/.*\/\/[^\/]*\//.match(base).to_s
        if (/^\//.match(link) and now[-1] == '/')
            now + link[1..-1]
        elsif (link.length != 0 && link[0] != '/' && now[-1] != '/')
            now + '/' + link
        else
            now + link
        end
    end

    def page_weight(page_address, page)
        re = /(<img([\w\W]+?)>)|(<applet([\w\W]+?)>)/i
        #puts "#{page_address} #{page.scan(re).length}"
        page.scan(re).length
    end

    def page_summary(page_address, page)
        re = /<title>.*<\/title>|<meta[^>]*>/m
        puts "URL: #{page_address}"
        puts extract_head(page).scan(re)
        puts
    end
    
    def extract_head(page)
        re = /<head[^>]*>(.*)<\/head>/m
        re.match(page)[1]
    end
end


class WebAgentThreads
    @@linkexpr1 = /<a[^>]*href\s*=\s*"([^|#@"]*)"/i
    @@linkexpr = /<a[^>]*href\s*=\s*"([^|#@?\s%"]*)"/i

    def initialize()
        @mutex=Mutex.new
        @visited_urls = Set.new()
    end

    def revise_thread(start_page,depth, block)
        @visited_urls << start_page
        thread = Thread.new(start_page, depth, block) {|url, depth, block| revise_help(url, depth, block)}
        thread.join
    end

    def revise_help(start_page, depth, block)
        return if depth == -1
        content = content(start_page)
        block.call(start_page, content)
        if depth != 0
            new_urls = Set.new(find_links(start_page, content))
            @mutex.lock
            new_urls = new_urls - @visited_urls
            @visited_urls = @visited_urls | new_urls
            @mutex.unlock
            threads = []
            for url in new_urls
                threads <<  Thread.new(url,depth-1,block) {|url, depth, block| revise_help(url, depth, block)}
            end
        else
            return
        end
        threads.each { |thr| thr.join }
    end

    def content(page_address)
        begin
            open(page_address, :read_timeout=>nil).read
        rescue => e
            puts e
            ""
        end
    end

    def find_links(base, page)
        begin 
            page.scan(@@linkexpr).map {|p_url| p_url[0].match(/^http|https/)? p_url[0] : make_full_link(base, p_url[0]) }
        rescue => e
            puts e
            return Array.new()
        end        
    end

    def make_full_link(base, link)
        now =/.*\/\/[^\/]*\//.match(base).to_s
        if (/^\//.match(link) and now[-1] == '/')
            now + link[1..-1]
        elsif (link.length != 0 && link[0] != '/' && now[-1] != '/')
            now + '/' + link
        else
            now + link
        end
    end

    def page_weight(page_address, page)
        re = /(<img([\w\W]+?)>)|(<applet([\w\W]+?)>)/i
        #puts "#{page_address} #{page.scan(re).length}"
        page.scan(re).length
    end

    def page_summary(page_address, page)
        re = /<title>.*<\/title>|<meta[^>]*>/m
        puts "URL: #{page_address}"
        puts extract_head(page).scan(re)
        puts
    end
    
    def extract_head(page)
        re = /<head[^>]*>(.*)<\/head>/m
        re.match(page)[1]
    end
end


#page1b = WebAgentThreads.new()
#page1b.revise_thread('http://www.ii.uni.wroc.pl/', 1,  lambda {|url,content| page1b.page_weight(url, content)} )

#puts("-------")
#page1a = WebAgent.new()
#page1a.revise('http://www.ii.uni.wroc.pl/', 1, lambda {|url,content| page1a.page_weight(url, content)} )


page1a = WebAgent.new()
page1b = WebAgentThreads.new()
Benchmark.bm(7) do |x|
  x.report("Reg:")   { page1a.revise('http://www.ii.uni.wroc.pl/', 1, lambda {|url,content| page1a.page_weight(url, content)} ) }
  x.report("Thr:")   { page1b.revise_thread('http://www.ii.uni.wroc.pl/', 1, lambda {|url,content| page1b.page_weight(url, content)} ) }
end
=begin
page1b = WebAgent.new()
start = Time.now
page1b.revise('http://www.ii.uni.wroc.pl/', 1, lambda {|url,content| page1a.page_weight(url, content)} )
finish = Time.now
diff = finish - start
puts diff

page1 = WebAgent.new()
start = Time.now
page1.revise('http://www.ii.uni.wroc.pl/', 1, lambda {|text| page1.page_weight(text)} )
finish = Time.now
diff = finish - start
puts diff
=end

#page1.revise('http://www.ii.uni.wroc.pl/', 1, lambda {|text| page1.page_weight(text)} )
#page1.revise('http://www.ii.uni.wroc.pl/', 1, lambda {|text| page1.page_summary(text)})