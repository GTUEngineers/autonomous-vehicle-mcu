#################################
How To Install
#################################

1. ZMQ
###################

libZmq kurulumu

.. code-block:: bash

    git clone https://github.com/zeromq/libzmq.git -b v4.3.0 --single-branch /tmp/libzmq
    mkdir /tmp/libzmq/build
    pushd /tmp/libzmq/build
    cmake -D WITH_PERF_TOOL=OFF -D ZMQ_BUILD_TESTS=OFF -D ENABLE_CPACK=OFF -D CMAKE_BUILD_TYPE=Release ..
    make -j4
    sudo make install
    popd

CPPZMQ kurulumu

.. code-block:: bash

    git clone https://github.com/zeromq/cppzmq.git -b v4.3.0 --single-branch /tmp/cppzmq
    mkdir /tmp/cppzmq/build
    pushd /tmp/cppzmq/build
    cmake -D CPPZMQ_BUILD_TESTS=OFF ..
    make -j4
    sudo make install
    popd

2. SPDLOG
###################

.. code-block:: bash

    mkdir -p /tmp/spdlog
    git clone https://github.com/gabime/spdlog.git -b v1.3.1 /tmp/spdlog
    pushd /tmp/spdlog
    sudo cp -vr ./include/spdlog/ /usr/local/include
    popd    


3. ProtoBuff
###################

.. code-block:: bash

    sudo apt install autoconf automake libtool curl unzip protobuf-compiler
    git clone https://github.com/protocolbuffers/protobuf.git -b v3.9.1 --single-branch /tmp/protobuf
    cd /tmp/protobuf
    git submodule update --init --recursive
    ./autogen.sh
    ./configure --with-protoc=/usr/bin/protoc
    make -j4
    sudo make install
