from django.shortcuts import render
from django.http import HttpResponse
from django.views.decorators.csrf import csrf_exempt
from django.views.generic import View

from rest_framework.renderers import JSONRenderer
from rest_framework.parsers import JSONParser

from JSONResponse import JSONResponse

from api.models import *
from api.serializers import *
from api.views.Pdu_detail import get_object_by_id

class Get_pdu_outlets(View):

    def get(self,request, id):
        pdu_obj = get_object_by_id(id)
        if Outlet.objects.filter(pdu = pdu_obj).exists():
            pdu_outlets = Outlet.objects.filter(pdu = pdu_obj)
        serializer = OutletSerializer(pdu_outlets, many=True)
        return JSONResponse(serializer.data)
