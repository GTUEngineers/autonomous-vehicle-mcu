from seqreqrep import Client
from pubsub import Subscriber
import commonlib
import thread
import mutex
import logging
logging.basicConfig(filename='lidar_comm_client.log', filemode='w', format='%(asctime)s - %(name)s - %(levelname)s - %(lineno)s - %(funcName)s - %(message)s')

class LidarReq(object):
	def __init__(self):
		self.subscription = Subscriber(False)
		self.subscription.connect(Client.PROC.format("ControlSub"))
		self.subscription.subscribe("lidardata")

		self.requester = Client()
		requester.connect(Client.PROC.format("ControlReq"))

		self.sub_thread = threading.Thread(target = self.subThreadFunc)
		self.last_data = []
		self.thread_stop = False
		self.sub_lock = threading.Lock()

	def request(x1, y1, x2, y2):
		request = create_lidar_req(x1, y1, x2, y2)
		reply = requester.reqrep(request)
		if(reply != None):
			logging.debug("Reply is non-none.")
			return self.parse_lidar_rep(reply)
		logging.warning("Reply is none.")

	def subThreadFunc(self):
		while(self.thread_stop == False):
			top, msg = self.recv()
			logging.debug("Published data received: {}".format(msg))
			if(top == "lidardata"):
				self.sub_lock.acquire()
				self.last_data = commonlib.parse_clusters(msg)
				logging.debug("Published data parsed: {}".format(last_data))
				self.sub_lock.release()

	def run(self):
		self.sub_thread.start()
		logging.debug("Thread started.")

	def getPublished(self):
		self.sub_lock.acquire()
		ret = self.last_data
		self.sub_lock.release()
		return ret

	def __del__(self):
		self.thread_stop = True
		self.sub_thread.join()
		self.requester.disconnect()
		self.subscription.unsubscribe("lidardata")
		self.subscription.disconnect()