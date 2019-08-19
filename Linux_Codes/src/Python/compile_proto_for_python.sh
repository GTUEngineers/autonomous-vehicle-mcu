#!/bin/sh
protoc --python_out=ProtoOut -I=../ProtoFiles ../ProtoFiles/*.proto