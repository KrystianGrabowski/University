require 'set'
require 'tk'
require 'tkextlib/bwidget'
class Notebook
    def initialize
        @list = Array.new
        @groups = Set.new
    end

    def run
        @win = TkRoot.new() { title 'Kontakty' }
        menu = TkMenu.new()
        one = TkMenu.new(menu)
        
        @listbox = TkListbox.new(@win, 'height' => 40, 'width' => 100, 'setgrid' => 2) {grid('row' => 1, 'column' => 1) }
        scroll = TkScrollbar.new(@win, 'orient' => 'vertical') {place('height' => 400, 'x' => 788)}
         
         @listbox.yscrollcommand(proc { |*args|
            scroll.set(*args)
         })
         
         scroll.command(proc { |*args|
            @listbox.yview(*args)
         }) 

        menu.add('cascade', :menu => one, :label => 'Nowy')
        one.add('command', :label => 'Nowy',
            :command => proc { data_window })
        one.add('command', :label => 'Random',
            :command => proc { random_contacts })
        one.add('command', :label => 'KONIEC',
            :command => proc { @win.destroy })
        two = TkMenu.new(menu)
        menu.add('cascade', :menu => two, :label => 'Edycja')
        two.add('command', :label => 'Szukaj', :command => proc { search_name_window })
        two.add('command', :label => 'Wszystkie kontakty', :command => proc {refresh})
        two.add('command', :label => 'Wszystkie grupy', :command => proc { refresh({:allgroup => true}) })
        @win.menu(menu)
        Tk.mainloop
    end

    def add(name, number, groups)
        groups = groups.split(' ')
        if number.to_s.length != 0
            @list << [name, number.to_s, groups]
            @groups.merge(groups)
        end
    end
    
    def search_all
        @list
    end

    def search_name(name)
        @list.select{|n, _, _| n.downcase == name.downcase}
    end

    def search_number(number)
        @list.select{|_, nr, _| nr == number}
    end

    def find_groups
        @groups.to_a
    end

    def search_group(group)
        @list.select{|_, _, gr|  (gr & group) == group}
    end

    def format_change(list)
        new_list = []
        for i in list
            new_list << i[0].to_s + ' ' + i[1] + ' ' +i[2].to_s
        end
        new_list
    end

    def refresh(params = nil)
        if !params
            @listbox.value = format_change(@list)
        end
        if params
            if params.has_key?(:name) && params.has_key?(:group)
                array1 = search_name(params[:name])
                array2 = search_group(params[:group])
                @listbox.value = format_change(array1 & array2)
            elsif params.has_key?(:name)
                @listbox.value = format_change(search_name(params[:name]))
            elsif params.has_key?(:group)
                @listbox.value = format_change(search_group(params[:group]))
            elsif params.has_key?(:allgroup)
                @listbox.value = find_groups
            end
        end
        

            
    end

    def random_contacts
        (1..20).each do
            add('Adam', '123123123', 'dom')
            add('Magda', '321321312', 'praca')
        end
        refresh
    end

    def data_window
        begin
           $win.destroy
        rescue
        end
        $win = TkToplevel.new {title "Dane"}
        label_x1 = TkLabel.new($win) { text "Nazwa"; grid('row' => 1, 'column' => 1) }
        @entry_x1 = TkEntry.new($win)  { grid('row' => 1, 'column' => 2) }
        label_x2 = TkLabel.new($win) { text "Numer"; grid('row' => 2, 'column' => 1) }
        @entry_x2 = TkEntry.new($win)  { grid('row' => 2, 'column' => 2) }
        label_x3 = TkLabel.new($win) { text "Grupy"; grid('row' => 3, 'column' => 1) }
        @entry_x3 = TkEntry.new($win)  { grid('row' => 3, 'column' => 2) }
        @butt = TkButton.new($win) { text 'Dodaj kontakt'; grid('row' => 4, 'column' => 1) }
        @butt.command {save_and_run; $win.destroy}
    end

    def save_and_run
        add(@entry_x1.value, @entry_x2.value, @entry_x3.value)
        refresh
    end

    def search_name_window
        begin
            $win.destroy
        rescue
        end
        $win = TkToplevel.new {title "Dane"}
        label_x1 = TkLabel.new($win) { text "Nazwa"; grid('row' => 1, 'column' => 1) }
        @entry_x1 = TkEntry.new($win)  { grid('row' => 1, 'column' => 2) }
        label_x2 = TkLabel.new($win) { text "Grupa"; grid('row' => 2, 'column' => 1) }
        @entry_x2 = TkEntry.new($win)  { grid('row' => 2, 'column' => 2) }
        @butt = TkButton.new($win) { text 'Szukaj'; grid('row' => 4, 'column' => 1) }

        @butt.command {refresh(get_params); $win.destroy}
    end

    def get_params
        params = {}
        params[:name] = @entry_x1.value if !@entry_x1.value.gsub(/\s+/, "").empty?
        params[:group] = @entry_x2.value.split(" ") if !@entry_x2.value.gsub(/\s+/, "").empty?
        params
    end
end

ntb = Notebook.new
ntb.run