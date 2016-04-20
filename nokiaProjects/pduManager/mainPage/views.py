from django.shortcuts import render
from django.http import HttpResponse
from django.template import RequestContext

def home(request):
    return render(request, 'mainPage/home.html')
# Create your views here.

def login_by_ldap(request):
    if request.method == 'POST':
        username = request.POST['username'];
        password = request.POST['password'];

        #przekazanie tych parametrow do ldapa i proba logowania
        #jesli sukces to render homa, w przeciwnym razie wynik o blednym logowaniu
        #trzeba tez zrobic autentyfikacje uzytkownika, aby moc sprawdzac w innych viewsach
        #czy uzytkownik jest zalogowany. request.user.is_authenticated()
        if 1 < 2:
            return render(request, 'mainPage/home.html') #symulacja sukcesu
        else:
            print "Invalid login details: {0}, {1}".format(username, password) #symulacja bledu
            return HttpResponse("Invalid login details supplied.")
    else:
        return render(request, 'mainPage/login.html')
