from django.shortcuts import render
from django.http import HttpResponse, HttpResponseRedirect
from django.template import RequestContext
from django.contrib.auth import authenticate, login, logout

def home(request):
    return render(request, 'mainPage/home.html')
# Create your views here.

def login_by_ldap(request):
    if request.method == 'POST':
        username = request.POST['username'];
        password = request.POST['password'];
        #zakomentowane zebyscie mogli normalnie strone przegladac
        # user = authenticate(username=username, password=password)

        # if user is not None:
        #     if user.is_active:
        #         login(request, user)
        #         return render(request, 'mainPage/home.html') # success
        #     else:
        #         return HttpResponse("Account {} is disabled".format(username))
        
        # else:
        #     return render(request, 'mainPage/login.html', {"error": "Invalid login details supplied. Please try again."})
        return HttpResponseRedirect('/home')
    else:
        return render(request, 'mainPage/login.html')

def logout(request):
    logout(request)
    return render(request, 'mainPage/home.html')