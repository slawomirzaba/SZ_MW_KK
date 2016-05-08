from django.views.generic import View
from django.shortcuts import render
from django.http import HttpResponse
from pdu_communicator.pdu.aten import ATEN


class Switch_outlet_on(View):
    redirect_field_name = None

    def get(self, request):
        pdu_id = request.GET.get("pduId")
        outlet_id = request.GET.get("outletId")

        # twoj kod wlaczajacy urzadzenie
        ip = "192.168.0.60"
        aten = ATEN(ip, timeout=0.1)
        aten_oid = aten._build_snmp_oid(8)
        aten.set_outlet_value(8, 'off')
        aten.set_outlet_value(8, 'on')
        text = "PDU" + pdu_id + ": Outlet" + outlet_id + " has been correctly switched on"
        return HttpResponse(text)
