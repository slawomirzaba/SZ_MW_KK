from django.shortcuts import render
from django.http import HttpResponse
from django.views.decorators.csrf import csrf_exempt
from django.views.generic import View

from rest_framework.renderers import JSONRenderer
from rest_framework.parsers import JSONParser

from JSONResponse import JSONResponse

from api.models import *
from api.serializers import *


def get_object_by_id(id):
    try:
        obj =  Pdu.objects.get(id=id)
        return obj
    except  Pdu.DoesNotExist:
        return HttpResponse(status=404)

class  Pdu_detail(View):

    def get(self,request, id):
        obj = get_object_by_id(id)
        serializer =  PduSerializer(obj)
        return JSONResponse(serializer.data)

    def put(self,request,id):
        get_object_by_id(id)
        data = JSONParser().parse(request)
        serializer =  PduSerializer(obj, data=data)
        if serializer.is_valid():
            serializer.save()
            return JSONResponse(serializer.data)
        return JSONResponse(serializer.errors, status=400)

    def delete(self,request,id):
        get_object_by_id(id)
        obj.delete()
        return HttpResponse(status=204)
