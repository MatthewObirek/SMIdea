# Use a base image suitable for your C++ application
FROM ubuntu:latest

# Install necessary dependencies
RUN apt-get update && apt-get install -y \
    g++ \
    # Add other dependencies as needed \
    && rm -rf /var/lib/apt/lists/*

# Copy your C++ source code into the container
COPY . /app

# Set the working directory
WORKDIR /app

# Compile your C++ code
RUN g++ -o your_cpp_executable your_source_code.cpp

# Expose the port your C++ application is listening on
EXPOSE 8080

# Command to run your C++ application
CMD ["./your_cpp_executable"]