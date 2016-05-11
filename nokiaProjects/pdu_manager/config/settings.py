# -*- coding: utf-8 -*-
"""
Django settings for pdu_manager project.

Generated by 'django-admin startproject' using Django 1.9.4.

For more information on this file, see
https://docs.djangoproject.com/en/1.9/topics/settings/

For the full list of settings and their values, see
https://docs.djangoproject.com/en/1.9/ref/settings/
"""

import os
import ldap
from django_auth_ldap.config import LDAPSearch, GroupOfNamesType

# Build paths inside the project like this: os.path.join(BASE_DIR, ...)
BASE_DIR = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))


# Quick-start development settings - unsuitable for production
# See https://docs.djangoproject.com/en/1.9/howto/deployment/checklist/

# SECURITY WARNING: keep the secret key used in production secret!
SECRET_KEY = '2-zrjr1*-qwm#w+aak!kch6+p24b1plpjpubbqlbyq)raal2n^'

# SECURITY WARNING: don't run with debug turned on in production!
DEBUG = True

ALLOWED_HOSTS = []


# Application definition

INSTALLED_APPS = [
    'django.contrib.admin',
    'django.contrib.auth',
    'django.contrib.contenttypes',
    'django.contrib.sessions',
    'django.contrib.messages',
    'django.contrib.staticfiles',
    'main',
    'api',
    'rest_framework',    
]

MIDDLEWARE_CLASSES = [
    'django.middleware.security.SecurityMiddleware',
    'django.contrib.sessions.middleware.SessionMiddleware',
    'django.middleware.common.CommonMiddleware',
    'django.middleware.csrf.CsrfViewMiddleware',
    'django.contrib.auth.middleware.AuthenticationMiddleware',
    'django.contrib.auth.middleware.SessionAuthenticationMiddleware',
    'django.contrib.messages.middleware.MessageMiddleware',
    'django.middleware.clickjacking.XFrameOptionsMiddleware',
]

ROOT_URLCONF = 'config.urls'

TEMPLATES = [
    {
        'BACKEND': 'django.template.backends.django.DjangoTemplates',
        'DIRS': ['templates'],
        'APP_DIRS': True,
        'OPTIONS': {
            'context_processors': [
                'django.template.context_processors.debug',
                'django.template.context_processors.request',
                'django.contrib.auth.context_processors.auth',
                'django.contrib.messages.context_processors.messages',
            ],
        },
    },
]

WSGI_APPLICATION = 'config.wsgi.application'


# Database
# https://docs.djangoproject.com/en/1.9/ref/settings/#databases

DATABASES = {
    'default': {
        'ENGINE': 'django.db.backends.mysql',
        'NAME': 'base_for_pdu_application',
        'USER': 'PDU_ROOT',
        'PASSWORD': 'qwerty',
        'HOST': '127.0.0.1',
        'PORT': '3306',
    }
}


# Password validation
# https://docs.djangoproject.com/en/1.9/ref/settings/#auth-password-validators

AUTH_PASSWORD_VALIDATORS = [
    {
        'NAME': 'django.contrib.auth.password_validation.UserAttributeSimilarityValidator',
    },
    {
        'NAME': 'django.contrib.auth.password_validation.MinimumLengthValidator',
    },
    {
        'NAME': 'django.contrib.auth.password_validation.CommonPasswordValidator',
    },
    {
        'NAME': 'django.contrib.auth.password_validation.NumericPasswordValidator',
    },
]


# Internationalization
# https://docs.djangoproject.com/en/1.9/topics/i18n/

LANGUAGE_CODE = 'en-us'

TIME_ZONE = 'UTC'

USE_I18N = True

USE_L10N = True

USE_TZ = True


# Static files (CSS, JavaScript, Images)
# https://docs.djangoproject.com/en/1.9/howto/static-files/

STATIC_URL = '/static/'
PROJECT_ROOT = os.path.abspath(os.path.dirname(__file__))

STATICFILES_DIRS = (
    os.path.join('static'),
)

AUTHENTICATION_BACKENDS = [
    'django.contrib.auth.backends.ModelBackend',
    'django_auth_ldap.backend.LDAPBackend',
]

AUTH_LDAP_GLOBAL_OPTIONS = {    # Nie używamy TLS
#    ldap.OPT_X_TLS_REQUIRE_CERT: ldap.OPT_X_TLS_NEVER,
    #    ldap.OPT_REFERRALS: False,
}
AUTH_LDAP_SERVER_URI = 'ldaps://ed-p-gl.emea.nsn-net.net' # Nokiowy serwer LDAP

# AUTH_LDAP_START_TLS = True # Nie używamy TLS
AUTH_LDAP_BIND_DN = ""  # Nie ma logowania
AUTH_LDAP_BIND_PASSWORD = "" # Nie ma logowania
AUTH_LDAP_USER_SEARCH = LDAPSearch("o=NSN", ldap.SCOPE_SUBTREE, "(uid=%(user)s)") # Kogo i gdzie ma wyszukiwać, 'uid' to login (czyli jeśli loguje się użytkownik to tu podkładany jest jego username i szukany jest w LDAPie
# or perhaps:
# AUTH_LDAP_USER_DN_TEMPLATE = "uid=%(user)s,ou=users,dc=example,dc=com" # Bo to co wyżej można też tak zrobić
# Set up the basic group parameters.
AUTH_LDAP_GROUP_SEARCH = LDAPSearch("o=NSN",
                                    ldap.SCOPE_SUBTREE, "(objectClass=groupOfNames)"
)
AUTH_LDAP_GROUP_TYPE = GroupOfNamesType()
# Simple group restrictions
# AUTH_LDAP_REQUIRE_GROUP = "cn=enabled,ou=django,ou=groups,dc=example,dc=com"
# AUTH_LDAP_DENY_GROUP = "cn=disabled,ou=django,ou=groups,dc=example,dc=com"
# Populate the Django user from the LDAP directory.
AUTH_LDAP_USER_ATTR_MAP = { # Mapowanie pól z ldap na pola w modelu użytkownika Django
    "first_name": "cn", # To tak na prawdę jest imie i nazwisko
    "email": "mail",    # Mail
    "nsn_id": "employeeNumber" # nsn_id - pole dodane przez nas, ale może też je macie
}
AUTH_LDAP_USER_FLAGS_BY_GROUP = {   # Gdybyśmy chcieli określać dostęp na podstawie LDAPowych grup to można je jakoś wyszukać i pomapować
    #    "is_active": "cn=active,ou=django,ou=groups,dc=example,dc=com",
    #    "is_staff": "cn=staff,ou=django,ou=groups,dc=example,dc=com",
    #    "is_superuser": "cn=superuser,ou=django,ou=groups,dc=example,dc=com"
}
# Use LDAP group membership to calculate group permissions.
AUTH_LDAP_FIND_GROUP_PERMS = True
# Cache group memberships for an hour to minimize LDAP traffic
AUTH_LDAP_CACHE_GROUPS = True
AUTH_LDAP_GROUP_CACHE_TIMEOUT = 3600

LOGIN_URL = 'login/'
# LOGIN_REDIRECT_URL = '/login/'
