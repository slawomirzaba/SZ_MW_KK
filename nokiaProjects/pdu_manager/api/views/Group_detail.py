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
        obj = Group.objects.get(id=id)
        if not obj:
            raise Exception
        return obj
    except Exception:
        return HttpResponse(status=404)

def get_groups_by_user_id(id):
    try:
        obj = Group.objects.filter(users__pk=id)
        if not obj:
            raise Exception
        return obj
    except Exception:
        return HttpResponse(status=404)

class Group_detail(View):

    def get(self,request, id):
        objs = get_groups_by_user_id(id)
        serializers = []
        for ob in objs:
            serializers.append(GroupSerializer(ob).data)
        return JSONResponse(serializers)

    def put(self,request,id):
        obj = get_object_by_id(id)
        data = JSONParser().parse(request)
        serializer = GroupSerializer(obj, data=data)
        if serializer.is_valid():
            serializer.save()
            return JSONResponse(serializer.data)
        return JSONResponse(serializer.errors, status=400)

    def delete(self,request,id):
        obj = get_object_by_id(id)
        obj.delete()
        return HttpResponse(status=204)
