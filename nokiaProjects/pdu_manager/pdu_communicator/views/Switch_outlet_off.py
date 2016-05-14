from django.views.generic import View
from django.http import JsonResponse
from pdu_communicator.pdu.aten import ATEN


class Switch_outlet_off(View):
    redirect_field_name = None

    def get(self, request):
        pdu_ip = request.GET.get("pdu_ip")
        outlet_nr = int(request.GET.get("outlet_nr"))
        aten = ATEN(pdu_ip, timeout=0.1)

        aten_oid = aten._build_snmp_oid(outlet_nr)
        status = aten.get_outlet_status(outlet_nr)
        if status == 'on':
            aten.set_outlet_value(outlet_nr, 'off')
            #text = "PDU IP {0}: Outlet {1} has been correctly switched off".format(pdu_ip, outlet_nr)
            return JsonResponse({'result': True})
        #text = "PDU IP {0}: Outlet {1} is currently switched off".format(pdu_ip, outlet_nr)
        return JsonResponse({'result': False})
