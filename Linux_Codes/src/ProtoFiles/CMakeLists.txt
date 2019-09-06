set(TARGET_NAME "ProtoFiles")
find_package(Protobuf REQUIRED)

protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS common.proto station_car.proto process.proto lidar_comm.proto)

ADD_LIBRARY(${TARGET_NAME} STATIC ${PROTO_SRCS})
