from django.views.decorators.csrf import csrf_exempt
from django.views.generic import View
import json

from JSONResponse import JSONResponse

from api.models import *

class Create_Groups(View):

    def post(self,request):
        username = request.GET.get("username")
        group_name = request.GET.get("group_name")
        data = json.loads(request.body)
        ids_pdu = data.get("idpdus")
        if User.objects.filter(user_name = username).exists():
            host = User.objects.get(user_name = username)
        else:
            host = User.objects.create(user_name = username)
            host.save()
        group = Group.objects.create(name = group_name ,owner = host)
        group.save()

        for idpdu in ids_pdu:
            print idpdu
            pdu = Pdu.objects.get(id = idpdu)
            group.pdus.add(pdu)

        if Group.objects.filter(owner = host, name = group_name).exists():
            return JSONResponse({'Succes' : True})
        else:
            return JSONResponse({'Succes' : False})
