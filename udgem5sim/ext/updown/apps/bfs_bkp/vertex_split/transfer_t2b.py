import sys
import argparse
from math import log2, ceil

DEBUG_OUTPUT = False
VERBOSE = True

# Parse command line arguments
parser = argparse.ArgumentParser()
parser.add_argument("graph", help="Path to the graph text file")
parser.add_argument("--stats", action="store_true", help="Enable statistics mode")
parser.add_argument("--directed", action="store_true", help="Enable directed graph mode")
parser.add_argument("--debug", action="store_true", help="Enable debug mode")
args = parser.parse_args()

graph_file = args.graph
stats = args.stats
directed = args.directed
DEBUG = args.debug

orig_vertices = set()
edge_list = set()

# Rest of the code
with open(graph_file, 'r') as file:
    for line in file:
        if line[0] == '#':
            continue
        source, destination = map(int, line.strip().split())
        edge_list.add((source, destination))
        if not directed: edge_list.add((destination, source))
        orig_vertices.add(source)
        orig_vertices.add(destination)

if DEBUG:
    print (f"Vertices: {orig_vertices}")

num_vertices = len(orig_vertices)
max_vid = max(orig_vertices)
print(f"Read in {num_vertices} vertices (max_vid = {max_vid}) and {len(edge_list)} edges from {graph_file}")

scale = ceil(log2(max_vid))

# Write the split neighbor list to a binary file
output_file = graph_file.replace('.txt', f'_edges.bin')
print(f"Writing edge list to {output_file}")

with open(output_file, 'wb') as file:
    file.seek(0)
    file.write((scale).to_bytes(8, 'little'))        # Write number of vertices
    file.write(len(edge_list).to_bytes(8, 'little')) # Write number of edges
    if VERBOSE:
        print(f"Writing number of vertices = {num_vertices}, max vid = {max_vid}, edges = {len(edge_list)}")
    for source, destination in edge_list:
        file.write(source.to_bytes(8, 'little'))  # Write source vertex ID
        file.write(destination.to_bytes(8, 'little'))  # Write destination vertex ID
        
print(f"Done writing edge list to {output_file}")

if not stats: sys.exit(0)

# Construct the neighbor list from the edge list 
neighbor_list = [set() for _ in range(max_vid + 1)]

for source, destination in edge_list:
    neighbor_list[source].add(destination)

if VERBOSE:
    stat_max_degree = 0
    stat_avg_degree = 0
    for v in orig_vertices:
        degree = len(neighbor_list[v])
        stat_max_degree = max(degree, stat_max_degree)
        stat_avg_degree += degree
    stat_avg_degree = stat_avg_degree / num_vertices
    print(f"Input graph max degree: {stat_max_degree}, Avg degree: {stat_avg_degree}")
