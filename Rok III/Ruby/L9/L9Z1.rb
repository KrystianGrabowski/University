require 'tk'
require 'tkextlib/bwidget'
class Wykres
    def run
        @size = 600.0
        @excluded = 20
        @win = TkRoot.new('height' => 640, 'width' => 640) { title 'Wykres' }
        @canvas = TkCanvas.new(@parent, 'background' => 'light goldenrod yellow') {place('height' => 640 , 'width' => 640)}
        menu = TkMenu.new()
        one = TkMenu.new(menu)
         
        menu.add('cascade', :menu => one, :label => 'Nowy')
        one.add('command', :label => 'Nowy',
            :command => proc { data_window })
        one.add('command', :label => 'KONIEC',
            :command => proc { @win.destroy })

        two = TkMenu.new(menu)
        menu.add('cascade', :menu => two, :label => 'Edycja')
        two.add('command', :label => 'Wyczyść', :command => proc { @canvas.delete("all") })
        @win.menu(menu)
        Tk.mainloop
    end


    def describe(line_coor, a, b, vertical)
        scale = @size/(b-a)
        iter = @size + @excluded
        if vertical
            (a..b).each do |x|
                TkcLine.new(@canvas, line_coor-3, iter , line_coor+3, iter,  'width' => '1' )
                TkcLine.new(@canvas, @excluded, iter , @size+@excluded, iter,  'width' => '0.2', 'fill' => 'gray80')
                TkcText.new(@canvas, line_coor+10, iter, 'text' => "#{x}") if x!= 0
                iter -= scale
            end 
        else
            b.downto(a).each do |x|
                TkcLine.new(@canvas, iter, line_coor-3 ,iter, line_coor+3,  'width' => '1' )
                TkcLine.new(@canvas, iter, @excluded ,iter, @size+@excluded,  'width' => '0.5', 'fill' => 'gray80' )
                TkcText.new(@canvas, iter, line_coor+10, 'text' => "#{x}") if x!= 0
                iter -= scale
            end 
        end
    end

    def lines(x0, x1, y0, y1)
        scale_x = @size/(x1-x0)
        scale_y = @size/(y1-y0)
        if (x0 <= 0 && x1 >= 0 )
            y_coor = x0.abs * scale_x + @excluded
            y_coor = y_coor.abs
            TkcLine.new(@canvas, y_coor, @size + @excluded  , y_coor, 0, 'width' => '2', 'fill' => 'black', 'arrow' => "last")
            describe(y_coor, y0, y1, true)
        else
            describe(@excluded, y0, y1, true)
        end
        if (y0 <= 0 && y1 >= 0 )
            x_coor = y1.abs * scale_y + @excluded
            x_coor = x_coor.abs
            TkcLine.new(@canvas, @excluded, x_coor , @size + 2 * @excluded, x_coor, 'width' => '2', 'fill' => 'black', 'arrow' => "last")
            describe(x_coor, x0, x1, false)
        else
            describe(@size+@excluded, x0, x1, false)
        end
        if x_coor && y_coor
            TkcText.new(@canvas, y_coor+7 ,x_coor+7, 'text' => 0)
        end
    end

    def draw(x0, x1, y0, y1, step_size, &blok)
        scale_x = @size/(x1-x0)
        scale_y = @size/(y1-y0)

        prev_y = blok.call(x0 - step_size)
        prev_x = (-step_size * scale_x) + @excluded
        prev_y = (y1 - prev_y) * scale_y + @excluded

        (x0..x1).step(step_size).each do |curr|
            y = blok.call(curr)
            x = (curr - x0) * scale_x + @excluded
            y = (y1 - y) * scale_y + @excluded
            TkcLine.new(@canvas, prev_x, prev_y, x, y, 'width' => 2, 'fill' => 'dark slate gray')
            prev_x = x
            prev_y = y
            #TkcOval.new(@canvas, x-1, y-1 , x+1, y+1, 'width' => '2', 'fill' => 'black')
        end
    end

    def data_window
        begin
           $win.destroy
        rescue
        end
        $win = TkToplevel.new {title "Dane"}
        @label_fun = TkLabel.new($win) { text "Funkcja"; grid('row' => 1, 'column' => 1) }
        @combobox = Tk::BWidget::ComboBox.new($win) { grid('row' => 1, 'column' => 2) }
        @combobox.values = ['x^2', 'x^3', 'x', '|x|', '1/x']

        label_x1 = TkLabel.new($win) { text "X0"; grid('row' => 2, 'column' => 1) }
        @entry_x1 = TkEntry.new($win)  { grid('row' => 2, 'column' => 2) }
        label_x2 = TkLabel.new($win) { text "X1"; grid('row' => 3, 'column' => 1) }
        @entry_x2 = TkEntry.new($win)  { grid('row' => 3, 'column' => 2) }
        label_x3 = TkLabel.new($win) { text "Y0"; grid('row' => 4, 'column' => 1) }
        @entry_x3 = TkEntry.new($win)  { grid('row' => 4, 'column' => 2) }
        label_x4 = TkLabel.new($win) { text "Y1"; grid('row' => 5, 'column' => 1) }
        @entry_x4 = TkEntry.new($win)  { grid('row' => 5, 'column' => 2) }
        @butt = TkButton.new($win) { text 'Narysuj funkcję'; grid('row' => 6, 'column' => 1) }
        @butt.command {save_and_run; $win.destroy}
    end

    def save_and_run
        lines(@entry_x1.value.to_i, @entry_x2.value.to_i, @entry_x3.value.to_i, @entry_x4.value.to_i)
        fun = case @combobox.value
            when 'x^2' 
                proc{|x| x*x}
            when 'x^3' 
                proc{|x| x*x*x}
            when 'x'
                proc{|x| x}
            when '|x|'
                proc{|x| x.abs}
            when '1/x'
                proc{|x| 1.0/x}
        end
        draw(@entry_x1.value.to_i, @entry_x2.value.to_i, @entry_x3.value.to_i, @entry_x4.value.to_i, 0.001, &fun)
    end

end




a = Wykres.new
a.run