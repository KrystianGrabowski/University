require "drb"


obj = DRbObject.new_with_uri(’druby://localhost:9000’)
if obj.respond_to?(’save’)
obj.save(html)
end

