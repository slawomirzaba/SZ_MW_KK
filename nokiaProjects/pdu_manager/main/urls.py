from django.conf.urls import url
from django.contrib.auth.views import login, logout
from main.views.Home import Home
from main.views.Login_by_LDAP import Login_by_LDAP


urlpatterns = [
    url(r'^$', Home.as_view(), name='home'),
    url(r'home/$', Home.as_view(), name='home'),
    url(r'login/$', Login_by_LDAP.as_view(), name='login_by_ldap'),
    url(r'logout/$', logout, {'next_page': '/'}, name='logout'),
]

