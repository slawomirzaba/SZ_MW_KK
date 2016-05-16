from django.shortcuts import render

from django.http import HttpResponse
from django.views.decorators.csrf import csrf_exempt
from rest_framework.renderers import JSONRenderer
from rest_framework.parsers import JSONParser
from api.models import *
from api.serializers import *

# Create your views here.

#Creating a JSons
class JSONResponse(HttpResponse):
    def __init__(self, data, **kwargs):
        content = JSONRenderer().render(data)
        kwargs['content_type'] = 'application/json'
        super(JSONResponse, self).__init__(content, **kwargs)


def Listing_User(request):

    if request.method == 'GET':
        User_object = User.objects.all()
        User_serializer = UserSerializer(User_object, many=True)
        return JSONResponse(User_serializer.data)

    elif request.method == 'POST':
        data = JSONParser().parse(request)
        User_serializer = UserSerializer(data=data)
        if User_serializer.is_valid():
            User_serializer.save()
            return JSONResponse(User_serializer.data, status=201)
        return JSONResponse(User_serializer.errors, status=400)

def Listing_Type_pdu(request):

    if request.method == 'GET':
        Type_pdu_object = Type_pdu.objects.all()
        Type_pdu_serializer = Type_pduSerializer(Type_pdu_object, many=True)
        return JSONResponse(Type_pdu_serializer.data)

    elif request.method == 'POST':
        data = JSONParser().parse(request)
        Type_pdu_serializer = Type_pduSerializer(data=data)
        if Type_pdu_serializer.is_valid():
            Type_pdu_serializer.save()
            return JSONResponse(Type_pdu_serializer.data, status=201)
        return JSONResponse(Type_pdu_serializer.errors, status=400)

def Listing_Pdu(request):

    if request.method == 'GET':
        obj = Pdu.objects.all()
        serializer = PduSerializer(obj, many=True)
        return JSONResponse(serializer.data)

    elif request.method == 'POST':
        data = JSONParser().parse(request)
        serializer = PduSerializer(data=data)
        if serializer.is_valid():
            serializer.save()
            return JSONResponse(serializer.data, status=201)
        return JSONResponse(serializer.errors, status=400)

def Listing_Group(request):

    if request.method == 'GET':
        obj = Group.objects.all()
        serializer = GroupSerializer(obj, many=True)
        return JSONResponse(serializer.data)

    elif request.method == 'POST':
        data = JSONParser().parse(request)
        serializer = GroupSerializer(data=data)
        if serializer.is_valid():
            serializer.save()
            return JSONResponse(serializer.data, status=201)
        return JSONResponse(serializer.errors, status=400)

def Listing_Outlet(request):

    if request.method == 'GET':
        obj = Outlet.objects.all()
        serializer = OutletSerializer(obj, many=True)
        return JSONResponse(serializer.data)

    elif request.method == 'POST':
        data = JSONParser().parse(request)
        serializer = OutletSerializer(data=data)
        if serializer.is_valid():
            serializer.save()
            return JSONResponse(serializer.data, status=201)
        return JSONResponse(serializer.errors, status=400)

def Listing_Type_user_action(request):

    if request.method == 'GET':
        obj = Type_user_action.objects.all()
        serializer = Type_user_actionSerializer(obj, many=True)
        return JSONResponse(serializer.data)

    elif request.method == 'POST':
        data = JSONParser().parse(request)
        serializer = Type_user_actionSerializer(data=data)
        if serializer.is_valid():
            serializer.save()
            return JSONResponse(serializer.data, status=201)
        return JSONResponse(serializer.errors, status=400)

def Listing_User_action(request):

    if request.method == 'GET':
        obj = User_action.objects.all()
        serializer = User_actionSerializer(obj, many=True)
        return JSONResponse(serializer.data)

    elif request.method == 'POST':
        data = JSONParser().parse(request)
        serializer = User_actionSerializer(data=data)
        if serializer.is_valid():
            serializer.save()
            return JSONResponse(serializer.data, status=201)
        return JSONResponse(serializer.errors, status=400)

def User_detail(request, id):

    try:
        obj = User.objects.get(id=id)
    except User.DoesNotExist:
        return HttpResponse(status=404)

    if request.method == 'GET':
        serializer = UserSerializer(obj)
        return JSONResponse(serializer.data)

    elif request.method == 'PUT':
        data = JSONParser().parse(request)
        serializer = UserSerializer(obj, data=data)
        if serializer.is_valid():
            serializer.save()
            return JSONResponse(serializer.data)
        return JSONResponse(serializer.errors, status=400)

    elif request.method == 'DELETE':
        obj.delete()
        return HttpResponse(status=204)

def Type_pdu_detail(request, id):

    try:
        obj = Type_pdu.objects.get(id=id)
    except Type_pdu.DoesNotExist:
        return HttpResponse(status=404)

    if request.method == 'GET':
        serializer = Type_pduSerializer(obj)
        return JSONResponse(serializer.data)

    elif request.method == 'PUT':
        data = JSONParser().parse(request)
        serializer = Type_pduSerializer(obj, data=data)
        if serializer.is_valid():
            serializer.save()
            return JSONResponse(serializer.data)
        return JSONResponse(serializer.errors, status=400)

    elif request.method == 'DELETE':
        obj.delete()
        return HttpResponse(status=204)

def Pdu_detail(request, id):

    try:
        obj = Pdu.objects.get(id=id)
    except Pdu.DoesNotExist:
        return HttpResponse(status=404)

    if request.method == 'GET':
        serializer = PduSerializer(obj)
        return JSONResponse(serializer.data)

    elif request.method == 'PUT':
        data = JSONParser().parse(request)
        serializer = PduSerializer(obj, data=data)
        if serializer.is_valid():
            serializer.save()
            return JSONResponse(serializer.data)
        return JSONResponse(serializer.errors, status=400)

    elif request.method == 'DELETE':
        obj.delete()
        return HttpResponse(status=204)

def Group_detail(request, id):

    try:
        obj = Group.objects.get(id=id)
    except Group.DoesNotExist:
        return HttpResponse(status=404)

    if request.method == 'GET':
        serializer = GroupSerializer(obj)
        return JSONResponse(serializer.data)

    elif request.method == 'PUT':
        data = JSONParser().parse(request)
        serializer = GroupSerializer(obj, data=data)
        if serializer.is_valid():
            serializer.save()
            return JSONResponse(serializer.data)
        return JSONResponse(serializer.errors, status=400)

    elif request.method == 'DELETE':
        obj.delete()
        return HttpResponse(status=204)

def Outlet_detail(request, id):

    try:
        obj = Outlet.objects.get(id=id)
    except Outlet.DoesNotExist:
        return HttpResponse(status=404)

    if request.method == 'GET':
        serializer = OutletSerializer(obj)
        return JSONResponse(serializer.data)

    elif request.method == 'PUT':
        data = JSONParser().parse(request)
        serializer = OutletSerializer(obj, data=data)
        if serializer.is_valid():
            serializer.save()
            return JSONResponse(serializer.data)
        return JSONResponse(serializer.errors, status=400)

    elif request.method == 'DELETE':
        obj.delete()
        return HttpResponse(status=204)

def Type_user_action_detail(request, id):

    try:
        obj = Type_user_action.objects.get(id=id)
    except Type_user_action.DoesNotExist:
        return HttpResponse(status=404)

    if request.method == 'GET':
        serializer = Type_user_actionSerializer(obj)
        return JSONResponse(serializer.data)

    elif request.method == 'PUT':
        data = JSONParser().parse(request)
        serializer = Type_user_actionSerializer(obj, data=data)
        if serializer.is_valid():
            serializer.save()
            return JSONResponse(serializer.data)
        return JSONResponse(serializer.errors, status=400)

    elif request.method == 'DELETE':
        obj.delete()
        return HttpResponse(status=204)

def User_action_detail(request, id):

    try:
        obj = User_action.objects.get(id=id)
    except User_action.DoesNotExist:
        return HttpResponse(status=404)

    if request.method == 'GET':
        serializer = User_actionSerializer(obj)
        return JSONResponse(serializer.data)

    elif request.method == 'PUT':
        data = JSONParser().parse(request)
        serializer = User_actionSerializer(obj, data=data)
        if serializer.is_valid():
            serializer.save()
            return JSONResponse(serializer.data)
        return JSONResponse(serializer.errors, status=400)

    elif request.method == 'DELETE':
        obj.delete()
        return HttpResponse(status=204)
