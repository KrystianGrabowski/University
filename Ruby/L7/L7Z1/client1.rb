require "drb"
#require_relative "kernel"

msg = "test1"
obj = DRbObject.new_with_uri('druby://localhost:9000')
if obj.respond_to?('save')
    obj.save(1, msg)
end