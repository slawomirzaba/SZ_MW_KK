from django.shortcuts import render
from django.http import HttpResponse
from django.views.decorators.csrf import csrf_exempt
from django.views.generic import View

from rest_framework.renderers import JSONRenderer
from rest_framework.parsers import JSONParser

from JSONResponse import JSONResponse

from api.models import *
from api.serializers import *


class Listing_Type_pdu(View):
    def get(self,request):
        Type_pdu_object = Type_pdu.objects.all()
        Type_pdu_serializer = Type_pduSerializer(Type_pdu_object, many=True)
        return JSONResponse(Type_pdu_serializer.data)

    def post(self,request):
        data = JSONParser().parse(request)
        Type_pdu_serializer = Type_pduSerializer(data=data)
        if Type_pdu_serializer.is_valid():
            Type_pdu_serializer.save()
            return JSONResponse(Type_pdu_serializer.data, status=201)
        return JSONResponse(Type_pdu_serializer.errors, status=400)
