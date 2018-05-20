
from django.urls import path
from . import views

urlpatterns = [
    path('', views.index, name='index'),
    path('loaded_files/', views.downloaded_page, name='loaded_files'),
]