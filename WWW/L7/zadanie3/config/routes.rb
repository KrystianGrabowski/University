Rails.application.routes.draw do
  root 'pages#main'
  get 'pages/main'
  get 'pages/photos'
  get 'pages/contacts'
  # For details on the DSL available within this file, see http://guides.rubyonrails.org/routing.html
end
