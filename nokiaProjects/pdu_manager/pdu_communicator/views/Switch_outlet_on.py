from django.utils import timezone
from django.views.generic import View
from django.http import JsonResponse
from pdu_communicator.pdu.aten import ATEN
from main.models import User, User_action, Pdu, Outlet, Type_user_action

import datetime

class Switch_outlet_on(View):
    redirect_field_name = None

    def get(self, request):
        pdu_ip = request.GET.get("pdu_ip")
        outlet_nr = int(request.GET.get("outlet_nr"))
        aten = ATEN(pdu_ip, timeout=0.1)

        aten_oid = aten._build_snmp_oid(outlet_nr)
        status = aten.get_outlet_status(outlet_nr)
        if status == 'off':
            aten.set_outlet_value(outlet_nr, 'on')

            user = request.useruser = User.objects.get(user_name=request.user.username)
            time = timezone.now()
            #time = datetime.datetime.now()
            pdu_object = Pdu.objects.get(ip=pdu_ip)
            outlet_object = Outlet.objects.get(pdu=pdu_object, number=outlet_nr)
            type_object = Type_user_action.objects.get(type="on")
            User_action.objects.create(time=time, user=user, outlet=outlet_object, type=type_object)
            
            #text = "PDU IP {0}: Outlet {1} has been correctly switched on".format(pdu_ip, outlet_nr)
            return JsonResponse({'result': True})
        #text = "PDU IP {0}: Outlet {1} is currently switched on".format(pdu_ip, outlet_nr)
        return JsonResponse({'result': False})