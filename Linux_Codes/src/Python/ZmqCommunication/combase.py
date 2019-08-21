#!/usr/bin/python3

import zmq


class ComBase():
    TCP = "tcp://{}:{}"
    PROC = "inproc://{}"

    def __init__(self, socket_type, is_server):
        self.context = zmq.Context().instance()
        self.socket = self.context.socket(socket_type)
        self.is_server = is_server
        self.ip = None
        self.port = None
        self.label = None
        self.addr = None
        self.poller = zmq.Poller()

    def connect(self, addr):
        self.addr = addr
        if self.is_server:
            self.socket.bind(self.addr)
        else:
            self.socket.connect(self.addr)

    def disconnect(self):
        if not self.is_server:
            self.socket.disconnect(self.addr)
