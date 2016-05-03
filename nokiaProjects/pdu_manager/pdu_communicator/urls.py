from django.conf.urls import url
from pdu_communicator.views.Switch_on_outlet import Switch_on_outlet

urlpatterns = [
    url(r'^switch_on_outlet', Switch_on_outlet.as_view(), name='switch_on_outlet'),
]
