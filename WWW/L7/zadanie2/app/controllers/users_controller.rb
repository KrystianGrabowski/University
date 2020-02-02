class UsersController < ApplicationController
  def show
    @user = User.find(params[:id])
  end

  def index
    @users = User.all
    @users = @users.order(:created_at).page params[:page]
  end

  def new
    @user = User.new
  end

  def create
    @user = User.new(user_params)
    @user.save
    redirect_to users_index_path
  end

  def user_params
    params.require(:user).permit!
  end

  def destroy
    @user = User.find(params[:id])
    @user.destroy
    redirect_back(fallback_location: root_path)
    flash[:notice] = 'User was destroyed!'
  end



  
end
