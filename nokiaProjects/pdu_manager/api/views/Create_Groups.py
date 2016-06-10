from django.views.decorators.csrf import csrf_exempt
from django.views.generic import View

from JSONResponse import JSONResponse

from api.models import *

class Create_Groups(View):

    def post(self,request,username,ids_pdu,group_name):
        host = User.objects.get(user_name = username)
        group = Group.objects.create(name = group_name ,owner = host)
        group.save()

        for idpdu in ids_pdu:
            pdu = Pdu.objects.get(id = idpdu)
            group.pdus.add(pdu)

        if Group.objects.filter(owner = host, name = group_name).exists():
            return JSONResponse({'Succes' : True})
        else:
            return JSONResponse({'Succes' : False})
