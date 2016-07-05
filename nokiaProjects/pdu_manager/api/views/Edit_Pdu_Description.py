from django.views.decorators.csrf import csrf_exempt
from django.views.generic import View
import json

from JSONResponse import JSONResponse

from api.models import *

class Edit_Pdu_Description(View):

    def post(self,request):
        data = json.loads(request.body)
        pdu_id = data.get("pdu_id")
        pdu_description = data.get("pdu_description")

        if Pdu.objects.filter(id = pdu_id).exists():
            pdu = Pdu.objects.get(id = pdu_id)
            if pdu.description == pdu_description:
                return JSONResponse({'Succes' : True})
            elif len(pdu_description) > 200:
                return JSONResponse({'Succes' : False})
            else:
                pdu.description = pdu_description
                pdu.save()
                return JSONResponse({'Succes' : True})
        else:
            return JSONResponse({'Succes' : False})
