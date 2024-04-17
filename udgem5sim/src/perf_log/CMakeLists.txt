cmake_minimum_required(VERSION 3.5)

# Set the project name
project (log_example)

# find the protobuf compiler and libraries
find_package(Protobuf REQUIRED)

# check if protobuf was found
if(PROTOBUF_FOUND)
    message ("protobuf found")
else()
    message (FATAL_ERROR "Cannot find Protobuf")
endif()

# Generate the .h and .cxx files
PROTOBUF_GENERATE_CPP(PROTO_SRCS PROTO_HDRS proto/perf_log_packet.proto)
# PROTOBUF_GENERATE_PYTHON(PROTO_PY proto/perf_log_packet.proto)

# Print path to generated files
message ("PROTO_SRCS = ${PROTO_SRCS}")
message ("PROTO_HDRS = ${PROTO_HDRS}")

# Add an executable
add_executable(log_example
    log_example.cpp
    protoio.cc
    ${PROTO_SRCS}
    ${PROTO_HDRS})

target_include_directories(log_example
    PUBLIC
    ${PROTOBUF_INCLUDE_DIRS}
    ${CMAKE_CURRENT_BINARY_DIR}
)

# link the exe against the libraries
target_link_libraries(log_example
    PUBLIC
    ${PROTOBUF_LIBRARIES}
)
