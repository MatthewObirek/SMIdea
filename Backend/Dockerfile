# Use a base image suitable for your C++ application
FROM gcc:latest

# Install necessary dependencies
RUN apt-get upgrade
RUN apt-get install -y g++
RUN apt-get install libssl-dev
RUN apt-get install --reinstall libpq-dev \
  && apt-get install -y wget \
  && rm -rf /var/lib/apt/lists/* \
  && wget https://github.com/Kitware/CMake/releases/download/v3.24.1/cmake-3.24.1-Linux-x86_64.sh \
      -q -O /tmp/cmake-install.sh \
      && chmod u+x /tmp/cmake-install.sh \
      && mkdir /opt/cmake-3.24.1 \
      && /tmp/cmake-install.sh --skip-license --prefix=/opt/cmake-3.24.1 \
      && rm /tmp/cmake-install.sh \
      && ln -s /opt/cmake-3.24.1/bin/* /usr/local/bin

# Copy your C++ source code into the container
COPY . /app
# Install libpq-fe.h
# WORKDIR /app/pgfe
# RUN mkdir build
# WORKDIR /app/pgfe/build
# RUN cmake -DPq_ROOT=/usr/local/pgsql .. # -DPq_ROOT is optional
# RUN cmake --build .
# RUN sudo cmake --install .

# Set the working directory
WORKDIR /app

# Compile your C++ code
RUN mkdir -p out/build 
WORKDIR /app/out/build 
RUN cmake -S ../../ -B . -DCMAKE_PREFIX_PATH=/usr/include/postgresql
RUN make
# g++ -std=c++17 main.cpp -o main

# Expose the port your C++ application is listening on
EXPOSE 8080

# Command to run your C++ application
CMD ["./main"]