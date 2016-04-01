from django.shortcuts import render

def home(request):
    return render(request, 'mainPage/home.html')
# Create your views here.
