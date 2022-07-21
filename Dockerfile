FROM redhat/ubi8

# install cmake
RUN \
   curl -L -o /tmp/cmake-install.sh https://github.com/Kitware/CMake/releases/download/v3.24.0-rc4/cmake-3.24.0-rc4-linux-x86_64.sh && \
   chmod +x /tmp/cmake-install.sh && \
   mkdir /usr/bin/cmake && \
   /tmp/cmake-install.sh --skip-license --prefix=/usr/bin/cmake && \
   rm /tmp/cmake-install.sh

ENV PATH="/usr/bin/cmake/bin:${PATH}"

# install make
RUN yum install -y make

# install gcc (version 8) and c++ libs
RUN yum install -y gcc
RUN yum install -y gcc-c++
RUN yum install libstdc++
