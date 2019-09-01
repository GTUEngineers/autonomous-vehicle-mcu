from seqreqrep import Client
from pubsub import Subscriber
import commonlib
import thread


class LidarReq(object):
	def __init__(self):
		self.subscription = Subscriber(False)
		self.subscription.connect(Client.PROC.format("ControlSub"))
		self.subscription.subscribe("lidardata");

		self.lastdata = []
	#	self.requester = Client()
	#	requester.connect(Client.PROC.format("ControlReq"))

	
	#def request(x1, y1, x2, y2):
	#	request = self.__create_request(x1, y1, x2, y2)
	#	reply = requester.reqrep(request);
	#	if(reply != None and self.__parse_response(reply, ) != None):


	def substhread(self):
		while(True):
			top, msg = self.recv()
			if(top == "lidardata"):
				self.lastdata = commonlib.parse_clusters(msg)

	def run(self):
		thread.start_new_thread(self.substhread)

	def __del__(self):
	#	requester.disconnect()
		self.subscription.unsubscribe("lidardata")
		self.subscription.disconnect()