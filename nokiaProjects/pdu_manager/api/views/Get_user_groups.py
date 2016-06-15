from django.views.decorators.csrf import csrf_exempt
from django.views.generic import View
import json

from JSONResponse import JSONResponse

from rest_framework import serializers

from api.models import *



class Group_detail(object):

    def __init__(self):
        self.group_name = ""
        self.pdus_in_group = []
        self.outlets_in_group = []

    def appendpdu(self, x):
        self.pdus_in_group.append(x)

    def appendoutlet(self, y):
        self.outlets_in_group.append(y)

class Group_detailSerializer(serializers.Serializer):
    group_name = serializers.CharField(max_length = 45)
    pdus_in_group = serializers.ListField()
    outlets_in_group = serializers.ListField()

class Get_user_groups(View):
    def get(self,request):
        username = request.GET.get("username")

        if User.objects.filter(user_name = username).exists():
                user = User.objects.get(user_name = username)
        else:
                user = User.objects.create(user_name = username)
                user.save()

        if Group.objects.filter(users__in = [user]).exists():
            user_groups = Group.objects.filter(users__in = [user])
            result = []
            for every_group in user_groups:
                single_group = Group_detail()
                single_group.group_name = every_group.name
                for every_pdu in every_group.pdus.all():
                    single_group.appendpdu(every_pdu.id)
                for every_outlet in every_group.outlets.all():
                    single_group.appendoutlet(every_outlet.id)
                serializer = Group_detailSerializer(single_group) #dodane
#                result.append(single_group)
                result.append(serializer.data)

            return JSONResponse({'result' : result})
        else:
            print "Nie dziala pobieranie grup gdzie nalezy uzytkownik"
