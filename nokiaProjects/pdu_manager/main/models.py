from __future__ import unicode_literals

from django.db import models

class User(models.Model):
    id = models.AutoField(primary_key = True, blank = False, unique = True)
    user_name = models.CharField(max_length = 45, blank = False, unique = True)

class Type_pdu(models.Model):
    id = models.AutoField(primary_key = True, blank = False, unique = True)
    type = models.CharField(max_length = 45, blank = False, unique = True)

class Pdu(models.Model):
    id = models.AutoField(primary_key = True, blank = False, unique = True)
    name = models.CharField(max_length = 45)
    ip = models.CharField(max_length = 45, blank = False, unique = True)
    description = models.CharField(max_length = 200)
    type = models.ForeignKey(Type_pdu, blank = False)


class Outlet(models.Model):
    id = models.AutoField(primary_key = True, blank = False, unique = True)
    description = models.CharField(max_length = 200)
    pdu = models.ForeignKey(Pdu, blank = False)
    number = models.IntegerField(default=1)

class Group(models.Model):
    id = models.AutoField(primary_key = True, blank = False, unique = True)
    name = models.CharField(max_length = 45, blank = False, unique = True)
    owner = models.ForeignKey(User, blank = False, related_name = 'owner')
    users = models.ManyToManyField(User, related_name = 'users')
    pdus = models.ManyToManyField(Pdu, blank = False)
    outlets = models.ManyToManyField(Outlet, blank = False)

class Type_user_action(models.Model):
    id = models.AutoField(primary_key = True, blank = False, unique = True)
    type = models.CharField(max_length = 45, blank = False, unique = True)

class User_action(models.Model):
    id = models.AutoField(primary_key = True, blank = False, unique = True)
    time = models.DateTimeField(blank = False)
    user = models.ForeignKey(User, blank = False)
    outlet = models.ForeignKey(Outlet, blank = False)
    type = models.ForeignKey(Type_user_action, blank = False)
