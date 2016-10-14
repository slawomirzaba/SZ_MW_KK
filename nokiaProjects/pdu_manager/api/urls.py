from django.conf.urls import url

from api.views.Listing_User import Listing_User
from api.views.Listing_Group import Listing_Group
from api.views.Listing_Outlet import Listing_Outlet
from api.views.Listing_Pdu import Listing_Pdu
from api.views.Listing_Type_pdu import Listing_Type_pdu
from api.views.Listing_Type_user_action import Listing_Type_user_action
from api.views.Listing_User_action import Listing_User_action
from api.views.User_detail import User_detail
from api.views.Outlet_detail import Outlet_detail
from api.views.Pdu_detail import Pdu_detail
from api.views.Type_pdu_detail import Type_pdu_detail
from api.views.Type_user_action_detail import Type_user_action_detail
from api.views.User_action_detail import User_action_detail
from api.views.Group_detail import Group_detail
from api.views.Create_Groups import Create_Groups
from api.views.Get_user_groups import Get_user_groups
from api.views.Edit_user_in_group import Edit_user_in_group
from api.views.Edit_Group import Edit_Group
from api.views.Edit_Pdu_Description import Edit_Pdu_Description
from api.views.Edit_Outlet_Description import Edit_Outlet_Description
from api.views.Login_by_REST import Login_by_REST
from api.views.Get_pdu_outlets import Get_pdu_outlets
from api.views.Mobile_edit_user_groups import Mobile_edit_user_groups


urlpatterns = [
    url(r'^users/$', Listing_User.as_view(), name = 'users'),
    url(r'^type_pdu/$',  Listing_Type_pdu.as_view(),name = 'type_pdu'),
    url(r'^pdus/$',  Listing_Pdu.as_view(), name = 'pdus'),
    url(r'^groups/$',  Listing_Group.as_view(), name = 'groups'),
    url(r'^outlets/$',  Listing_Outlet.as_view(), name = 'outlets'),
    url(r'^type_user_action/$',  Listing_Type_user_action.as_view(), name = 'type_user_action'),
    url(r'^user_action/$',  Listing_User_action.as_view(), name = 'user_action'),
    url(r'^users/(?P<id>[0-9]+)/$',  User_detail.as_view(), name = 'user_detail'),
    url(r'^type_pdu/(?P<id>[0-9]+)/$',  Type_pdu_detail.as_view(), name = 'Type_pdu_detail'),
    url(r'^pdu/(?P<id>[0-9]+)/$',  Pdu_detail.as_view(), name = 'Pdu_detail'),
    url(r'^pdu/edit_pdu_description/$',  Edit_Pdu_Description.as_view(), name = 'edit_pdu_description'),
    url(r'^group/(?P<id>[0-9]+)/$',  Group_detail.as_view(), name = 'Group_detail'),
    url(r'^outlet/(?P<id>[0-9]+)/$',  Outlet_detail.as_view(), name = 'Outlet_detail'),
    url(r'^outlet/edit_outlet_description/$',  Edit_Outlet_Description.as_view(), name = 'edit_outlet_description'),
    url(r'^type_user_action/(?P<id>[0-9]+)/$',  Type_user_action_detail.as_view(), name = 'Type_user_action_detail'),
    url(r'^user_action/(?P<id>[0-9]+)/$',  User_action_detail.as_view(), name = 'User_action_detail'),
    url(r'^group/add/$',  Create_Groups.as_view(), name = 'Create_Groups'),
    url(r'^group/get_user_groups/$',  Get_user_groups.as_view(), name = 'Get_user_groups'),
    url(r'^group/edit_user_in_group/$',  Edit_user_in_group.as_view(), name = 'edit_user_in_group'),
    url(r'^group/edit_group/$',  Edit_Group.as_view(), name = 'edit_group'),
    url(r'^login_by_rest/$', Login_by_REST.as_view(), name='login_by_rest'),
    url(r'^pdu_outlets/(?P<id>[0-9]+)/$', Get_pdu_outlets.as_view(), name='get_pdu_outlets'),
    url(r'^group/mobile_edit_user_groups/$',  Mobile_edit_user_groups.as_view(), name = 'mobile_edit_user_groups'),
]
