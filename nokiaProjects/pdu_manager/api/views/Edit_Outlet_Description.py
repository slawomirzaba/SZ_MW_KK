from django.views.decorators.csrf import csrf_exempt
from django.views.generic import View
import json

from JSONResponse import JSONResponse

from api.models import *

class Edit_Outlet_Description(View):

    def post(self,request):
        data = json.loads(request.body)
        outlet_id = data.get("outlet_id")
        outlet_description = data.get("outlet_description")

        if Outlet.objects.filter(id = outlet_id).exists():
            outlet = Outlet.objects.get(id = outlet_id)
            if outlet.description == outlet_description:
                return JSONResponse({'Succes' : True})
            elif len(outlet_description) > 200:
                return JSONResponse({'Succes' : False})
            else:
                outlet.description = outlet_description
                outlet.save()
                return JSONResponse({'Succes' : True})
        else:
            return JSONResponse({'Succes' : False})
