from django.shortcuts import render
from django.http import HttpResponse
from django.views.decorators.csrf import csrf_exempt
from django.views.generic import View

from rest_framework.renderers import JSONRenderer
from rest_framework.parsers import JSONParser

from JSONResponse import JSONResponse

from api.models import *
from api.serializers import *


class Listing_Pdu(View):
    def get(self, request):
        obj = Pdu.objects.all()
        serializer = PduSerializer(obj, many=True)
        return JSONResponse(serializer.data)

    def post(self,request):
        data = JSONParser().parse(request)
        serializer = PduSerializer(data=data)
        if serializer.is_valid():
            serializer.save()
            return JSONResponse(serializer.data, status=201)
        return JSONResponse(serializer.errors, status=400)
