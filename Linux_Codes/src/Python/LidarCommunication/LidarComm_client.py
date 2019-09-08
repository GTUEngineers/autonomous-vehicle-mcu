# some_file.py
import sys
# insert at 1, 0 is the script path (or '' in REPL)
sys.path.insert(1, '../')
from ZmqCommunication.seqreqrep import Client
from ZmqCommunication.pubsub import Subscriber
from CommonLib.CommonLib import *
import threading
import logging
logging.basicConfig(filename='lidar_comm_client.log', filemode='w', format='%(asctime)s - %(name)s - %(levelname)s - %(lineno)s - %(funcName)s - %(message)s')

TOPIC_TO_SUBSCRIBE = "lidar/data"
PROC_CONNECT_SUBSCRIBE = "ControlSub"
PROC_CONNECT_CLIENT = "ControlReq"

class LidarCommClient(object):
	def __init__(self):
		self.__sub_thread = threading.Thread(target = self.subThreadFunc)
		self.last_data = []
		self.thread_stop = False
		self.sub_lock = threading.Lock()

		self.subscription = Subscriber(False)
		self.subscription.connect(Subscriber.PROC.format(PROC_CONNECT_SUBSCRIBE))
		self.subscription.subscribe(TOPIC_TO_SUBSCRIBE)

		self.requester = Client()
		self.requester.connect(Client.PROC.format(PROC_CONNECT_CLIENT))

	def request(self, x1, y1, x2, y2):
		request = create_lidar_req(x1, y1, x2, y2)
		reply = self.requester.reqrep(request)
		if(reply != None):
			logging.debug("Reply is non-none.")
			return self.parse_lidar_rep(reply)
		logging.warning("Reply is none.")

	def subThreadFunc(self):
		while(self.thread_stop == False):
			top, msg = self.recv()
			logging.debug("Published data received: {}".format(msg))
			if(top == TOPIC_TO_SUBSCRIBE):
				self.sub_lock.acquire()
				self.last_data = commonlib.parse_clusters(msg)
				logging.debug("Published data parsed: {}".format(last_data))
				self.sub_lock.release()

	def run(self):
		self.__sub_thread.start()
		logging.debug("Thread started.")

	def getPublished(self):
		self.sub_lock.acquire()
		ret = self.last_data
		self.sub_lock.release()
		return ret

	def __del__(self):
		self.thread_stop = True
		if(self.__sub_thread.isAlive()):
			self.__sub_thread.join()
		self.requester.disconnect()
		self.subscription.unsubscribe(TOPIC_TO_SUBSCRIBE)
		self.subscription.disconnect()