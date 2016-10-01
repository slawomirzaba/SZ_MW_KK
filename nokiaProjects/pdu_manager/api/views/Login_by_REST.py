from django.views import View
from django.contrib.auth import authenticate
from django.http import HttpResponse


class Login_by_REST(View):
	
	def get(self, request):
		username = request.GET.get("username")
		password = request.GET.get("password")

		response = HttpResponse()
		user = authenticate(username=username, password=password)

		if user is not None:
			if user.is_active:
				response.write("true")
			else:
				response.write("false")
		else:
			response.write("false")

		return response