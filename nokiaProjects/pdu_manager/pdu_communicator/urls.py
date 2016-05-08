from django.conf.urls import url
from pdu_communicator.views.Switch_outlet_on import Switch_outlet_on

urlpatterns = [
    url(r'^switch_outlet_on', Switch_outlet_on.as_view(), name='switch_outlet_on'),
]
