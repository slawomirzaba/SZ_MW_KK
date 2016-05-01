from django.views.generic import View
from django.contrib.auth.mixins import LoginRequiredMixin
from django.shortcuts import render


class Home(LoginRequiredMixin, View):
    redirect_field_name = None

    def get(self, request):
        username = request.user.username
        return render(request, 'main/home.html', {'username': username})
