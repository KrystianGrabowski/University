class Car < ApplicationRecord
    validates :reg_number, presence: true, format: { with: /\A[a-zA-z]{2,3}[0-9]{4,6}\z/ , message: "Błędny format numeru rejestracyjnego"}
    validates :reg_date, presence: true
    validates :make, presence: true, format: { with: /\A[a-zA-z]+\z/ , message: "Błędny format marki"}
    validates :year, presence: true, format: { with: /\A[0-9]{4}\z/ , message: "Błędny format roku produkcji"}
end
