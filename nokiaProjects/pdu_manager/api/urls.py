from django.conf.urls import url
from api.views import *

urlpatterns = [
    url(r'^api/users/$', Listing_User),
    url(r'^api/type_pdu/$', Listing_Type_pdu),
    url(r'^api/pdu/$', Listing_Pdu),
    url(r'^api/group/$', Listing_Group),
    url(r'^api/outlet/$', Listing_Outlet),
    url(r'^api/type_user_action/$', Listing_Type_user_action),
    url(r'^api/user_action/$', Listing_User_action),
    url(r'^api/users/(?P<id>[0-9]+)/$', User_detail),
    url(r'^api/type_pdu/(?P<id>[0-9]+)/$', Type_pdu_detail),
    url(r'^api/pdu/(?P<id>[0-9]+)/$', Pdu_detail),
    url(r'^api/group/(?P<id>[0-9]+)/$', Group_detail),
    url(r'^api/outlet/(?P<id>[0-9]+)/$', Outlet_detail),
    url(r'^api/type_user_action/(?P<id>[0-9]+)/$', Type_user_action_detail),
    url(r'^api/user_action/(?P<id>[0-9]+)/$', User_action_detail),
]
