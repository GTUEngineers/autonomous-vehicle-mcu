from seqreqrep import Client
from pubsub import Subscriber
import commonlib
import thread


class LidarReq(object):
	def __init__(self):
		self.subscription = Subscriber(False)
		self.subscription.connect(Client.PROC.format("ControlSub"))
		self.subscription.subscribe("lidardata");

		self.requester = Client()
		requester.connect(Client.PROC.format("ControlReq"))

		self.sub_thread = threading.Thread(target = self.subThreadFunc);
		self.last_data = []

	def request(x1, y1, x2, y2):
		request = create_lidar_req(x1, y1, x2, y2)
		reply = requester.reqrep(request);
		if(reply != None):
			return self.parse_lidar_rep(reply)

	def subThreadFunc(self):
		while(True):
			top, msg = self.recv()
			if(top == "lidardata"):
				self.last_data = commonlib.parse_clusters(msg)

	def run(self):
		sub_thread.start()

	def getPublished(self):
		return self.last_data;

	def __del__(self):
		self.sub_thread.join()
		self.requester.disconnect()
		self.subscription.unsubscribe("lidardata")
		self.subscription.disconnect()