# some_file.py
import sys
# insert at 1, 0 is the script path (or '' in REPL)
sys.path.insert(1, '../')
from ProtoOut.lidar_comm_pb2 import *

def create_clusters(cluster_list):
    data = pub_sub()
    for sublist in cluster_list:
        data_new = data.clusters.add()
        data_new.center.x = sublist[0]
        data_new.center.y = sublist[1]
        data_new.center.z = sublist[2]
        data_new.size.width = sublist[3]
        data_new.size.height = sublist[4]
    return data.SerializeToString()

def parse_clusters(msg):
    cluster_list = []
    i = 0
    data = pub_sub()
    data.ParseFromString(msg)
    for cluster in data.clusters:
        cluster_list.append([])
        cluster_list[i].append(cluster.center.x)
        cluster_list[i].append(cluster.center.y)
        cluster_list[i].append(cluster.center.z)
        cluster_list[i].append(cluster.size.width)
        cluster_list[i].append(cluster.size.height)
        i += 1
    return cluster_list

def create_lidar_req(x1, y1, x2, y2):
    request = req_rep()
    request.lidar_req.upper_left.x = x1
    request.lidar_req.upper_left.y = y1
    request.lidar_req.downer_right.x = x2
    request.lidar_req.downer_right.y = y2
    return request.SerializeToString()

def parse_lidar_req(msg):
    request = req_rep()
    request.ParseFromString(msg)
    return request.lidar_req.upper_left.x, request.lidar_req.upper_left.y, request.lidar_req.downer_right.x, request.lidar_req.downer_right.y

def create_lidar_rep(x, y, z, width, height):
    reply = req_rep()
    reply.lidar_rep.center.x = x
    reply.lidar_rep.center.y = y
    reply.lidar_rep.center.z = z
    reply.lidar_rep.size.width = width
    reply.lidar_rep.size.height = height
    return reply.SerializeToString()

def parse_lidar_rep(msg):
    reply = req_rep()
    reply.ParseFromString(msg)
    return reply.lidar_rep.center.x, reply.lidar_rep.center.y, reply.lidar_rep.center.z, reply.lidar_rep.size.width, reply.rep.size.height 
