#!/bin/sh
mkdir -p ProtoOut
protoc --python_out=ProtoOut -I=../ProtoFiles ../ProtoFiles/*.proto
