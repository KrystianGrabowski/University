module Kernel
    alias_method :old_system, :system
    def system(*args)
        puts "system(#{args.join(',')})"
        old_system(args)
    end
end