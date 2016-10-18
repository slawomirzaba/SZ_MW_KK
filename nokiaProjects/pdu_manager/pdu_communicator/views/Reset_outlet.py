from django.utils import timezone
from django.views.generic import View
from django.http import JsonResponse
from pdu_communicator.pdu.aten import ATEN
from main.models import User, User_action, Pdu, Outlet, Type_user_action

import time

class Reset_outlet(View):
    redirect_field_name = None

    def get(self, request):
        pdu_ip = request.GET.get("pdu_ip")
        outlet_nr = int(request.GET.get("outlet_nr"))
        aten = ATEN(pdu_ip, timeout=0.1)

        aten_oid = aten._build_snmp_oid(outlet_nr)
        status = aten.get_outlet_status(outlet_nr)

        if status == 'on':
            aten.set_outlet_value(outlet_nr, 'off')
            time.sleep(2)
            aten.set_outlet_value(outlet_nr, 'on')
            
            user = User.objects.get(user_name=request.user.username)
            time_ = timezone.now()
            pdu_object = Pdu.objects.get(ip=pdu_ip)
            outlet_object = Outlet.objects.get(pdu=pdu_object, number=outlet_nr)
            type_object = Type_user_action.objects.get(type="reset")
            User_action.objects.create(time=time_, user=user, outlet=outlet_object, type=type_object)
            
            return JsonResponse({'result': True})
        return JsonResponse({'result': False})