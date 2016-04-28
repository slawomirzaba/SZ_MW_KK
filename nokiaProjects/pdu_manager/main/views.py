from django.shortcuts import render
from django.http import HttpResponse, HttpResponseRedirect
from django.template import RequestContext
from django.contrib.auth import authenticate, login, logout

def home(request):
    return render(request, 'main/home.html')
# Create your views here.

def login_by_ldap(request):
    if request.method == 'POST':
        username = request.POST['username'];
        password = request.POST['password'];
        user = authenticate(username=username, password=password)

        if user is not None:
            if user.is_active:
                login(request, user)
                return render(request, 'main/home.html') # success
            else:
                return HttpResponse("Account {} is disabled".format(username))
        
        else:
            return render(request, 'main/login.html', {"error": "Invalid login details supplied. Please try again."})
        # return HttpResponseRedirect('/home')
    else:
        return render(request, 'main/login.html')

def logout(request):
    logout(request)
    return render(request, 'main/login.html')