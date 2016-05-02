# This is an auto-generated Django model module.
# You'll have to do the following manually to clean this up:
#   * Rearrange models' order
#   * Make sure each model has one field with primary_key=True
#   * Make sure each ForeignKey has `on_delete` set to the desired behavior.
#   * Remove `managed = False` lines if you wish to allow Django to create, modify, and delete the table
# Feel free to rename the models, but don't rename db_table values or field names.
from __future__ import unicode_literals

from django.db import models


class Action(models.Model):
    idaction = models.IntegerField(db_column='idACTION')  # Field name made lowercase.
    time = models.DateField()
    user_iduser = models.ForeignKey('User', models.DO_NOTHING, db_column='USER_idUSER')  # Field name made lowercase.
    outlet_idoutlet = models.ForeignKey('Outlet', models.DO_NOTHING, db_column='OUTLET_idOUTLET')  # Field name made lowercase.
    outlet_pdu_idpdu = models.ForeignKey('Outlet', models.DO_NOTHING, db_column='OUTLET_PDU_idPDU')  # Field name made lowercase.
    type_action_idtype_action = models.ForeignKey('TypeAction', models.DO_NOTHING, db_column='TYPE_ACTION_idTYPE_ACTION')  # Field name made lowercase.

    class Meta:
        managed = True
        db_table = 'ACTION'
        unique_together = (('idaction', 'user_iduser', 'outlet_idoutlet', 'outlet_pdu_idpdu', 'type_action_idtype_action'),)


class Group(models.Model):
    idgroup = models.AutoField(db_column='idGROUP', primary_key=True)  # Field name made lowercase.
    name = models.CharField(max_length=45)

    class Meta:
        managed = True
        db_table = 'GROUP'


class GroupHasPdu(models.Model):
    group_idgroup = models.ForeignKey(Group, models.DO_NOTHING, db_column='GROUP_idGROUP')  # Field name made lowercase.
    pdu_idpdu = models.ForeignKey('Pdu', models.DO_NOTHING, db_column='PDU_idPDU')  # Field name made lowercase.

    class Meta:
        managed = True
        db_table = 'GROUP_has_PDU'
        unique_together = (('group_idgroup', 'pdu_idpdu'),)


class Outlet(models.Model):
    idoutlet = models.IntegerField(db_column='idOUTLET')  # Field name made lowercase.
    number = models.IntegerField()
    description = models.CharField(max_length=45, blank=True, null=True)
    pdu_idpdu = models.ForeignKey('Pdu', models.DO_NOTHING, db_column='PDU_idPDU')  # Field name made lowercase.

    class Meta:
        managed = True
        db_table = 'OUTLET'
        unique_together = (('idoutlet', 'pdu_idpdu'),)


class Pdu(models.Model):
    idpdu = models.AutoField(db_column='idPDU')  # Field name made lowercase.
    name = models.CharField(max_length=45)
    type = models.CharField(max_length=45)
    ip = models.CharField(unique=True, max_length=45)
    description = models.CharField(max_length=45, blank=True, null=True)
    types_idtypes = models.ForeignKey('TypesPdu', models.DO_NOTHING, db_column='TYPES_idTYPES')  # Field name made lowercase.

    class Meta:
        managed = True
        db_table = 'PDU'
        unique_together = (('idpdu', 'types_idtypes'),)


class TypesPdu(models.Model):
    idtypes = models.IntegerField(db_column='idTYPES', primary_key=True)  # Field name made lowercase.
    type = models.CharField(max_length=45)

    class Meta:
        managed = True
        db_table = 'TYPES_PDU'


class TypeAction(models.Model):
    idtype_action = models.IntegerField(db_column='idTYPE_ACTION', primary_key=True)  # Field name made lowercase.
    type = models.CharField(max_length=45)

    class Meta:
        managed = True
        db_table = 'TYPE_ACTION'


class User(models.Model):
    iduser = models.AutoField(db_column='idUSER', primary_key=True)  # Field name made lowercase.
    name = models.CharField(max_length=45)

    class Meta:
        managed = True
        db_table = 'USER'


class UserHasGroup(models.Model):
    user_iduser = models.ForeignKey(User, models.DO_NOTHING, db_column='USER_idUSER')  # Field name made lowercase.
    group_idgroup = models.ForeignKey(Group, models.DO_NOTHING, db_column='GROUP_idGROUP')  # Field name made lowercase.

    class Meta:
        managed = True
        db_table = 'USER_has_GROUP'
        unique_together = (('user_iduser', 'group_idgroup'),)


class DjangoMigrations(models.Model):
    app = models.CharField(max_length=255)
    name = models.CharField(max_length=255)
    applied = models.DateTimeField()

    class Meta:
        managed = True
        db_table = 'django_migrations'
