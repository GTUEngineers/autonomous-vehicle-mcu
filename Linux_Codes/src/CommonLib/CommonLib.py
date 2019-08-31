import lidar_comm_pb3

def parse_clusters(msg):
    cluster_list = []
    i = 0
    data = lidar_comm_pb3.lidar.pub_sub()
    data.ParseFromString(msg)
    for cluster in data.clusters:
        cluster_list[i] = []
        cluster_list[i][0] = cluster.center.x
        cluster_list[i][1] = cluster.center.y
        cluster_list[i][2] = cluster.center.z
        cluster_list[i][3] = cluster.size.width
        cluster_list[i][4] = cluster.size.height
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

def parse_rep(msg):
    reply = lidar_comm_pb3.lidar.req_rep()
    reply.ParseFromString(msg)
    ret_tuple = (reply.rep.center.x, reply.rep.center.y, reply.rep.center.z, reply.rep.size.width, reply.rep.size.height)
    return ret_tuple
