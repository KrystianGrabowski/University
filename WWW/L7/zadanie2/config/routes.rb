Rails.application.routes.draw do
  root 'users#home'
  get 'users/show'
  get 'users/index'
  get 'users/new'

  resources :users
  # For details on the DSL available within this file, see http://guides.rubyonrails.org/routing.html
end
