class CarsController < ApplicationController
  def new
    @car = Car.new
  end

  def index
    @cars = Car.all
  end

  def confirmation
  end

  def create 
    @car = Car.new(car_params)
    respond_to do |format|
      if @car.save
        format.html { redirect_to cars_confirmation_path, notice: 'Mark was successfully created.' }
      else
        format.html { render action: 'new' }
      end
    end
  end


  def car_params
    params.require(:car).permit!
  end

  def destroy
    @car = Car.find(params[:id])
    @car.destroy
    redirect_back(fallback_location: cars_index_path)
    flash[:notice] = 'User was destroyed!'
  end

end
