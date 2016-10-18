from django.views.generic import View
from django.contrib.auth.mixins import LoginRequiredMixin
from django.shortcuts import render
from main.models import Type_user_action


class Home(LoginRequiredMixin, View):
    redirect_field_name = None

    def get(self, request):
        username = request.user.username

        try:
        	type_on = Type_user_action.objects.get(type="on")
        except Type_user_action.DoesNotExist:
        	Type_user_action.objects.create(type="on")

        try:
        	type_off = Type_user_action.objects.get(type="off")
        except Type_user_action.DoesNotExist:
        	Type_user_action.objects.create(type="off")

        try:
        	type_reset = Type_user_action.objects.get(type="reset")
        except Type_user_action.DoesNotExist:
        	Type_user_action.objects.create(type="reset")

        return render(request, 'main/home.html', {'username': username})
