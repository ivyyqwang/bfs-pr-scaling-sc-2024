all: proto_cpp proto_py

PROTOC?=protoc
PROTO_DIR?=./proto
PROTO_FILES?=$(PROTO_DIR)/perf_log_packet.proto
OUTPUT_DIR_CPP?=.
OUTPUT_PROTO_FILES_CPP?=$(OUTPUT_DIR_CPP)/perf_log_packet_payload.pb.cc $(OUTPUT_DIR_CPP)/perf_log_packet_payload.pb.h $(OUTPUT_DIR_CPP)/perf_log_packet.pb.cc $(OUTPUT_DIR_CPP)/perf_log_packet.pb.h
OUTPUT_DIR_PY?=.
OUTPUT_PROTO_FILES_PY?=$(OUTPUT_DIR_PY)/perf_log_packet_payload_pb2.py $(OUTPUT_DIR_PY)/perf_log_packet_pb2.py

proto_py:
	mkdir -p $(OUTPUT_DIR_PY)
	$(PROTOC) -I=$(PROTO_DIR) --python_out=$(OUTPUT_DIR_PY) $(PROTO_FILES)

proto_cpp:
	mkdir -p $(OUTPUT_DIR_CPP)
	$(PROTOC) -I=$(PROTO_DIR) --cpp_out=$(OUTPUT_DIR_CPP) $(PROTO_FILES)

# cpp_example: proto_cpp
# 	g++ -std=c++11 -I/usr/include/google -I$(OUTPUT_DIR_CPP) -L/usr/lib/x86_64-linux-gnu -lprotobuf -pthread -o log_example_cpp protoio.cc $(OUTPUT_DIR_CPP)/perf_log_packet.pb.cc $(OUTPUT_DIR_CPP)/perf_log_packet_payload.pb.cc log_example.cpp

clean:
	rm -f $(OUTPUT_PROTO_FILES_CPP) $(OUTPUT_PROTO_FILES_PY)
	# rm -rf $(OUTPUT_DIR_CPP) $(OUTPUT_DIR_PY)
	# rm -f log_example_cpp
