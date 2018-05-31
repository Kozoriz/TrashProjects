
from django.urls import path
from . import views

urlpatterns = [
    path('', views.index, name='index'),
    path('loaded_files/', views.downloaded_page, name='loaded_files'),
    path('loaded_files/check_loaded_state/', views.check_loaded_state, name='check_loaded_state'),
]