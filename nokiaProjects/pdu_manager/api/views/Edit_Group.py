from django.views.decorators.csrf import csrf_exempt
from django.views.generic import View
import json

from JSONResponse import JSONResponse

from api.models import *

class Edit_Group(View):

    def post(self,request):
        group_id = request.GET.get("group_id")
        group_name = request.GET.get("group_name")
        data = json.loads(request.body)
        ids_pdu = data.get("idpdus")
        ids_outl = data.get("idoutlets")
        if Group.objects.filter(id = group_id).exists():
            group = Group.objects.get(id = group_id)
            if group.name != group_name:
                group.name = group_name
            for old_pdu in group.pdus.all(): ##Removing pdus which are removed
                check = False
                for new_id_pdu in ids_pdu:
                    if old_pdu.id == new_id_pdu:
                        check = True
                if check == False:
                    group.pdus.remove(old_pdu)
            for new_id_pdu in ids_pdu:    ## Add new pdus
                check = False
                for old_pdu in group.pdus.all():
                    if old_pdu.id == new_id_pdu:
                        check = True
                if check == False:
                    if Pdu.objects.filter(id = new_id_pdu).exists():
                        pdu = Pdu.objects.get(id = new_id_pdu)
                        group.pdus.add(pdu)

            for old_outlet in group.outlets.all(): ##Removing pdus which are removed
                check = False
                for new_id_outlet in ids_outl:
                    if old_outlet.id == new_id_outlet:
                        check = True
                if check == False:
                    group.outlets.remove(old_outlet)
            for new_id_outlet in ids_outl:    ## Add new pdus
                check = False
                for old_outlet in group.outlets.all():
                    if old_outlet.id == new_id_outlet:
                        check = True
                if check == False:
                    if Outlet.objects.filter(id = new_id_outlet).exists():
                        outlet = Outlet.objects.get(id = new_id_outlet)
                        group.outlets.add(outlet)
            return JSONResponse({'Succes' : True})
        else:
            return JSONResponse({'Succes' : False})
