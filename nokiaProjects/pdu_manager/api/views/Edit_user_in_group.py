from django.views.decorators.csrf import csrf_exempt
from django.views.generic import View
import json

from JSONResponse import JSONResponse

from api.models import *

class Edit_user_in_group(View):

    def post(self,request):
        username = request.GET.get("username")
        group_name = request.GET.get("group_name")

        if Group.objects.filter(name = group_name).exists():
            group = Group.objects.get(name = group_name)
            if User.objects.filter(user_name = username).exists():
                user = User.objects.get(user_name = username)
                if group.users.filter(users__in = [user]).exists():
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

    def delete(self, request):
        username = request.GET.get("username")
        group_name = request.GET.get("group_name")

        if Group.objects.filter(name = group_name).exists():
            group = Group.objects.get(name = group_name)
            if User.objects.filter(user_name = username).exists():
                user = User.objects.get(user_name = username)
                if group.users.filter(users__in = [user]).exists():
                    if group.owner.id == user.id:
                        if len(group.users) > 1:
                            group.owner = group.users[1]
                            group.users.remove(user)
                            return JSONResponse({'Succes' : True})
                        else:
                            group.delete()
                            return JSONResponse({'Succes' : True})
                    else:
                        group.users.remove(user)
                        return JSONResponse({'Succes' : True})
                else:
                    return JSONResponse({'Succes' : False})
            else:
                return JSONResponse({'Succes' : False})
        else:
            return JSONResponse({'Succes' : False})
