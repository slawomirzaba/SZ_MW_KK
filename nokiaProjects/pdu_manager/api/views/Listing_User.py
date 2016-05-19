from django.shortcuts import render
from django.http import HttpResponse
from django.views.decorators.csrf import csrf_exempt
from django.views.generic import View

from rest_framework.renderers import JSONRenderer
from rest_framework.parsers import JSONParser

from JSONResponse import JSONResponse

from api.models import *
from api.serializers import *


class Listing_User(View):
    def get(self,request):
        User_object = User.objects.all()
        User_serializer = UserSerializer(User_object, many=True)
        return JSONResponse(User_serializer.data)

    def post(self,request):
        data = JSONParser().parse(request)
        User_serializer = UserSerializer(data=data)
        if User_serializer.is_valid():
            User_serializer.save()
            return JSONResponse(User_serializer.data, status=201)
        return JSONResponse(User_serializer.errors, status=400)
