from django.views.generic import View
from django.shortcuts import render
from django.http import HttpResponse


class Switch_on_outlet(View):
    redirect_field_name = None

    def get(self, request):
        pdu_id = request.GET.get("pduId")
        outlet_id = request.GET.get("outletId")
        print pdu_id
        # twoj kod wlaczajacy urzadzenie
    	text = "PDU" + pdu_id + ": Outlet" + outlet_id + " has been correctly switched on"
        return HttpResponse(text)
