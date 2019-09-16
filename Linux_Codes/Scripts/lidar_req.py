import requests 

API_ENDPOINT = "http://192.168.1.201/cgi/setting/fov"

a = requests.post(url = API_ENDPOINT, data={"start":300,"end":100})