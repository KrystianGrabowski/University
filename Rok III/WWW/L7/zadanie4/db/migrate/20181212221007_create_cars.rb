class CreateCars < ActiveRecord::Migration[5.2]
  def change
    create_table :cars do |t|
      t.string :reg_number
      t.date :reg_date
      t.string :make
      t.integer :year
      t.string :fuel

      t.timestamps
    end
  end
end
