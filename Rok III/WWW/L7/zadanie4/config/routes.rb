Rails.application.routes.draw do
  root 'cars#new'
  get 'cars/new'
  get 'cars/confirmation'
  get 'cars/index'

  resources :cars
  # For details on the DSL available within this file, see http://guides.rubyonrails.org/routing.html
end
