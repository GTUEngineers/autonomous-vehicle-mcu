#!/usr/bin/python3

import zmq
from .combase import ComBase
import time


class Server(ComBase):
    def __init__(self):
        ComBase.__init__(self, zmq.REP, True)

        self.poller.register(self.socket, zmq.POLLIN)

    def recv(self, timeout):
        socks = dict(self.poller.poll(timeout))
        if self.socket in socks and socks[self.socket] == zmq.POLLIN:
            message = self.socket.recv()
            return message
        return None

    def send(self, msg):
        self.socket.send(msg)


class Client(ComBase):
    def __init__(self):
        ComBase.__init__(self, zmq.REQ, False)
        self.poller.register(self.socket, zmq.POLLIN | zmq.POLLOUT)

    def reqrep(self, req, timeout=-1):
        socks = dict(self.poller.poll(timeout*1000))
        if self.socket in socks and socks[self.socket] == zmq.POLLOUT:
            self.socket.send(req)
            socks = dict(self.poller.poll(timeout))

            if self.socket in socks and socks[self.socket] == zmq.POLLIN:
                message = self.socket.recv()
                return message
        return None
