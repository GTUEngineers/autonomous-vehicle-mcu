#!/bin/sh
mkdir ProtoOut
protoc --python_out=ProtoOut -I=../ProtoFiles ../ProtoFiles/*.proto
