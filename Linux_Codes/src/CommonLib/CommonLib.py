import lidar_comm_pb2

def create_clusters(cluster_list):
    data = lidar_comm_pb2.LidarComm.pub_sub()
    for sublist in cluster_list:
        data.clusters.add()
        data.clusters = lidar_comm_pb2.LidarComm.Cluster()
        data.clusters.center = lidar_comm_pb2.LidarComm.Position()
        data.clusters.center.x = sublist[0]
        data.clusters.center.y = sublist[1]
        data.clusters.center.z = sublist[2]
        data.clusters.size = lidar_comm_pb2.LidarComm.Size()
        data.clusters.size.width = sublist[3]
        data.clusters.size.height = sublist[4]
    return data.SerializeToStringD()

def parse_clusters(msg):
    cluster_list = []
    i = 0
    data = lidar_comm_pb2.LidarComm.pub_sub()
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
    request = lidar_comm_pb2.LidarComm.req_rep()
    request.lidar_req = lidar_comm_pb2.LidarComm.RequestData()
    request.lidar_req.upper_left = lidar_comm_pb2.LidarComm.Pixel()
    request.lidar_req.upper_left.x = x1
    request.lidar_req.upper_left.y = y1
    request.lidar_req.downer_right = lidar_comm_pb2.LidarComm.Pixel()
    request.lidar_req.downer_right.x = x2
    request.lidar_req.downer_right.y = y2
    return request.SerializeToString()

def parse_lidar_req(msg):
    request = lidar_comm_pb2.LidarComm.req_rep()
    request.ParseFromString(msg)
    return request.lidar_req.upper_left.x, request.lidar_req.upper_left.y, request.lidar_req.downer_right.x, request.lidar_req.downer_right.y

def create_lidar_rep(x, y, z, width, height):
    reply = lidar_comm_pb2.LidarComm.req_rep()
    reply.lidar_rep = lidar_comm_pb2.LidarComm.Cluster()
    reply.lidar_rep.center = lidar_comm_pb2.LidarComm.Position()
    reply.lidar_rep.center.x = x
    reply.lidar_rep.center.y = y
    reply.lidar_rep.center.z = z
    reply.lidar_rep.size = lidar_comm_pb2.LidarComm.Size()
    reply.lidar_rep.size.width = width
    reply.lidar_rep.size.height = height
    return reply.SerializeToString()

def parse_lidar_rep(msg):
    reply = lidar_comm_pb2.LidarComm.req_rep()
    reply.ParseFromString(msg)
    return reply.lidar_rep.center.x, reply.lidar_rep.center.y, reply.lidar_rep.center.z, reply.lidar_rep.size.width, reply.rep.size.height 
