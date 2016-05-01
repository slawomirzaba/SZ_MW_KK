from django.views.generic.base import TemplateView
from django.contrib.auth import authenticate
from django.contrib.auth.views import login
from django.shortcuts import render, redirect
from django.http import HttpResponse


class Login_by_LDAP(TemplateView):
    template_name = 'main/login.html'

    def post(self, request):
        username = request.POST['username']
        password = request.POST['password']
        user = authenticate(username=username, password=password)

        if user is not None:
            if user.is_active:
                login(request, user)
                return redirect('/home/')
            else:
                return render(request, 'main/login.html', {'error': 'Account is disabled'})
        else:
            return render(request, 'main/login.html', {'error': 'Invalid login details supplied. Please try again.'})