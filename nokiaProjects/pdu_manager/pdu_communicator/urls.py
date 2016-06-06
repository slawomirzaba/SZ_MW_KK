from django.conf.urls import url
from pdu_communicator.views.Switch_outlet_on import Switch_outlet_on
from pdu_communicator.views.Switch_outlet_off import Switch_outlet_off
from pdu_communicator.views.Reset_outlet import Reset_outlet
from pdu_communicator.views.Check_state import Check_state

urlpatterns = [
    url(r'^switch_outlet_on', Switch_outlet_on.as_view(), name='switch_outlet_on'),
    url(r'^switch_outlet_off', Switch_outlet_off.as_view(), name='switch_outlet_off'),
    url(r'^reset_outlet', Reset_outlet.as_view(), name='reset_outlet'),
    url(r'^check_state', Check_state.as_view(), name='check_state'),
]
