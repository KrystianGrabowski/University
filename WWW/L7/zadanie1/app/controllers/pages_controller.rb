class PagesController < ApplicationController
  def home

    render html: helpers.tag.strong('Not Found')
    #render inline: '<strong>HTML String</strong>'
    #render json: 'plain text'
    #render xml: 'plain text'
    #render plain: 'plain text'
  end

  def index
  end

  def show
  end
end
