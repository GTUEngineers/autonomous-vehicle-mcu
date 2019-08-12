#!/usr/bin/python3

import zmq

class ComBase():
    def __init__(self, socket_type, is_server):
        self.context = zmq.Context().instance()
        self.socket = self.context.socket(socket_type)
        self.is_server = is_server
        self.ip = None
        self.port = None
        self.label = None
        self.addr = None

    def connect_tcp(self, port, ip=None):
        if self.is_server:
            self.addr = "tcp://*:" + str(port)
            self.socket.bind(self.addr)
        else:
            self.addr = "tcp://" + str(ip) + ":" + str(port)
            self.socket.connect(self.addr)

    def connect_proc(self, label):
        self.addr = "inproc://" + str(label)
        if self.is_server:
            self.socket.bind(self.addr)
        else:
            self.socket.connect(self.addr)

    def disconnect(self):
        if not self.is_server:
            self.socket.disconnect(self.addr)
