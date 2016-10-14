from django.views.decorators.csrf import csrf_exempt
from django.views.generic import View
from django.views.decorators.csrf import csrf_exempt
from django.utils.decorators import method_decorator
import json

from JSONResponse import JSONResponse

from api.models import *

class Mobile_edit_user_groups(View):
    @method_decorator(csrf_exempt)
    def dispatch(self, request, *args, **kwargs):
        return super(Mobile_edit_user_groups, self).dispatch(request, *args, **kwargs)

    def post(self,request):
        username = request.GET.get("username")
        group_name = request.GET.get("group_name")
        print group_name

        if Group.objects.filter(name = group_name).exists():
            group = Group.objects.get(name = group_name)
            if User.objects.filter(user_name = username).exists():
                user = User.objects.get(user_name = username)
                if user in group.users.all():
                    return JSONResponse({'Succes' : False})
                else:
                    group.users.add(user)
                    return JSONResponse({'Succes' : True})
            else:
                user = User.objects.create(user_name = username)
                user.save()
                group.users.add(user)
                return JSONResponse({'Succes' : True})
        else:
            return JSONResponse({'Succes' : False})
