import lidar_comm_pb3

def create_clusters(cluster_list):
    data = lidar_comm_pb3.lidar.pub_sub()
    for sublist in cluster_list:
        data.clusters.add()
        data.clusters = lidar_comm_pb3.lidar.Cluster()
        data.clusters.center = lidar_comm_pb3.lidar.Position()
        data.clusters.center.x = sublist[0]
        data.clusters.center.y = sublist[1]
        data.clusters.center.z = sublist[2]
        data.clusters.size = lidar_comm_pb3.lidar.Size()
        data.clusters.size.width = sublist[3]
        data.clusters.size.height = sublist[4]
    return data.SerializeToStringD()

def parse_clusters(msg):
    cluster_list = []
    i = 0
    data = lidar_comm_pb3.lidar.pub_sub()
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

def create_req(x1, y1, x2, y2):
    request = lidar_comm_pb3.lidar.req_rep()
    request.req = lidar_comm_pb3.lidar.RequestData()
    request.req.upper_left = lidar_comm_pb3.lidar.Pixel()
    request.req.upper_left.x = x1
    request.req.upper_left.y = y1
    request.req.downer_right = lidar_comm_pb3.lidar.Pixel()
    request.req.downer_right.x = x2
    request.req.downer_right.y = y2
    return request.SerializeToString()

def parse_req(msg):
    request = lidar_comm_pb3.lidar.req_rep()
    request.ParseFromString(msg)
    return request.req.upper_left.x, request.req.upper_left.y, request.req.downer_right.x, request.req.downer_right.y

def create_rep(x, y, z, width, height):
    reply = lidar_comm_pb3.lidar.req_rep()
    reply.rep = lidar_comm_pb3.lidar.Cluster()
    reply.rep.center = lidar_comm_pb3.lidar.Position()
    reply.rep.center.x = x
    reply.rep.center.y = y
    reply.rep.center.z = z
    reply.rep.size = lidar_comm_pb3.lidar.Size()
    reply.rep.size.width = width
    reply.rep.size.height = height
    return reply.SerializeToString()

def parse_rep(msg):
    reply = lidar_comm_pb3.lidar.req_rep()
    reply.ParseFromString(msg)
    return reply.rep.center.x, reply.rep.center.y, reply.rep.center.z, reply.rep.size.width, reply.rep.size.height 
