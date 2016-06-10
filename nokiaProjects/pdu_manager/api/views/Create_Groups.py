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
        outl = data.get("idoutlets")
        j = 0
        i = 0

        if User.objects.filter(user_name = username).exists():
            host = User.objects.get(user_name = username)
        else:
            host = User.objects.create(user_name = username)
            host.save()
        group = Group.objects.create(name = group_name ,owner = host)

        for idpdu in ids_pdu:
            i = i + 1
            pdu = Pdu.objects.get(id = idpdu)
            group.pdus.add(pdu)

        for idoutlet in outl:
            j = j + 1
            outlett = Outlet.objects.get(id = idoutlet)
            group.outlets.add(outlett)

        if i > 0 and j > 0:
            group.save()

        if Group.objects.filter(owner = host, name = group_name).exists():
            return JSONResponse({'Succes' : True})
        else:
            return JSONResponse({'Succes' : False})
