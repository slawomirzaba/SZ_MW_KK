from rest_framework import serializers
from rest_framework.renderers import JSONRenderer

#from .models import Category
from main.models import *

class UserSerializer(serializers.ModelSerializer):
     class Meta:
        model = User
        fields = ('id', 'user_name')

class Type_pduSerializer(serializers.ModelSerializer):
    class Meta:
       model = Type_pdu
       fields = ('id', 'type')

class PduSerializer(serializers.ModelSerializer):
    class Meta:
        model = Pdu
        fields = ('id', 'name', 'ip', 'description', 'type')


class GroupSerializer(serializers.ModelSerializer):
    class Meta:
        model = Group
        fields = ('id', 'name', 'owner', 'users', 'pdus')

class OutletSerializer(serializers.ModelSerializer):
    class Meta:
        model = Outlet
        fields = ('id', 'description', 'pdu')

class Type_user_actionSerializer(serializers.ModelSerializer):
    class Meta:
        model = Type_user_action
        fields = ('id', 'type')

class User_actionSerializer(serializers.ModelSerializer):
    class Meta:
        model = User_action
        fields = ('id', 'time', 'user', 'outlet', 'type')
