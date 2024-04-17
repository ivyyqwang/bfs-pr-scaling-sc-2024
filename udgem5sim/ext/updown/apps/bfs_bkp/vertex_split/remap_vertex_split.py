import random
import sys
import argparse

DEBUG_OUTPUT = False
VERBOSE = True

# Parse command line arguments
parser = argparse.ArgumentParser()
parser.add_argument("graph", help="Path to the graph text file")
parser.add_argument("max_degree", type=int, help="Maximum degree for vertex splitting")
parser.add_argument("--stats", action="store_true", help="Enable statistics mode")
parser.add_argument("--directed", action="store_true", help="Enable directed graph mode")
parser.add_argument("--debug", action="store_true", help="Enable debug mode")
args = parser.parse_args()

graph_file = args.graph
max_degree = args.max_degree
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
num_edges    = len(edge_list)

# Remap vertex ids
mappings = {}
new_vid = 0
for v in orig_vertices:
    mappings[v] = new_vid
    new_vid += 1

if DEBUG:
    print (f"Mapping from original vids to new vids: {mappings}")

max_vid = max(orig_vertices)
print(f"Read in {num_vertices} vertices (max_vid = {max_vid}) and {num_edges} edges from {graph_file}")

# Construct the neighbor list from the edge list 
neighbor_list = [set() for _ in range(new_vid)]
remapped_edges = set()

for source, destination in edge_list:
    new_src = mappings[source]
    new_dst = mappings[destination]
    neighbor_list[new_src].add(new_dst)
    remapped_edges.add((new_src, new_dst))

if DEBUG:
    for v in range(new_vid):
        neighbor_list[v].sort()
        neighbors = [(v, dst) for dst in neighbor_list[v]]
        print(f"Neighbors of vertex {v}: \n{neighbors}")

if max_degree == 0:
    stat_max_degree = 0
    stat_avg_degree = 0
    # Write the split neighbor list to a binary file
    output_file = graph_file.replace('.txt', f'_remap_nlist.bin')
    print(f"Writing remapped non-split neighbor list to {output_file}")
    distance = 0xffffffffffffffff
    parent = 0
    vid_range = 0
    dummy_vertex = {'vid': 0, 'deg': 0, 'split': True, 'orig_vid': 0, 'base_vid': 0, 'split_num': 0}

    with open(output_file, 'wb') as file:
        file.seek(0)
        file.write((new_vid).to_bytes(8, 'little'))  # Write number of vertices
        file.write(num_edges.to_bytes(8, 'little'))  # Write number of edges
        if VERBOSE:
            print(f"Writing number of vertices = {new_vid}, edges = {num_edges}")
        for v in range(new_vid):
            neighbors = neighbor_list[v]
            degree = len(neighbors)
            file.write(degree.to_bytes(8, 'little')) # Write degree
            file.write(v.to_bytes(8, 'little'))              # Write original vertex ID
            file.write(v.to_bytes(8, 'little'))              # Write vertex ID
            file.write(id(neighbors).to_bytes(8, 'little'))  # Write neighbor list
            file.write(distance.to_bytes(8, 'little'))       # Write default distance
            file.write(parent.to_bytes(8, 'little'))         # Write default parent
            file.write(vid_range.to_bytes(8, 'little'))      # Write split range
            file.write((0).to_bytes(8, 'little'))
            for neighbor in neighbors:
                file.write(neighbor.to_bytes(8, 'little'))  # Write neighbor ID
            if DEBUG_OUTPUT:
                print(f"Vertex vid={v} - deg {degree}, dist {-1}, neigh_list {hex(id(neighbors))}")
                print(f"Neighbors: [{', '.join([f'{n}' for n in neighbors])}{', '  if neighbors else ''}]")
            stat_max_degree = max(degree, stat_max_degree)
            stat_avg_degree += degree
    stat_avg_degree = stat_avg_degree / num_vertices
    print(f"Input graph max degree: {stat_max_degree}, Avg degree: {stat_avg_degree}")
    print(f"Done writing original neighbor list to {output_file}")
    exit(0)

split_vid = new_vid
v_dict = {}
print(f"Max vertex id after remapping: {new_vid - 1}")

stat_max_degree = 0
stat_avg_degree = 0
for v in range(new_vid):
    degree = len(neighbor_list[v])
    if degree > max_degree:
        base_vid = split_vid
        num_split = (degree // max_degree) + 1
        for i in range(num_split):
            v_dict[split_vid] = {'vid': split_vid, 'deg': 0, 'split': True, 'orig_vid': v, 'base_vid': base_vid, 'split_num': num_split}
            split_vid += 1
        v_dict[v] = {'vid': v, 'deg': 0, 'split': True, 'orig_vid': v, 'base_vid': base_vid, 'split_num': num_split}
    else:
        v_dict[v] = {'vid': v, 'deg': degree, 'split': False, 'orig_vid': v, 'base_vid': 0, 'split_num': 0}
    stat_max_degree = max(degree, stat_max_degree)
    stat_avg_degree += degree
stat_avg_degree = stat_avg_degree / num_vertices
print(f"Input graph max degree: {stat_max_degree}, Avg degree: {stat_avg_degree}")
        
# Construct split edge list
split_edges = set()
for src, dst in remapped_edges:
    if v_dict[src]['split']:
        random_split = random.randint(0, v_dict[src]['split_num'] - 1)
        new_src = v_dict[src]['base_vid'] + random_split
        v_dict[new_src]['deg'] += 1
        if DEBUG:
            print(f"Vertex {src} deg={v_dict[src]['deg']} is split into {new_src} new deg={v_dict[new_src]['deg']}")
    else:
        new_src = src
        
    if v_dict[dst]['split']:
        random_split = random.randint(0, v_dict[dst]['split_num'] - 1)
        new_dst = v_dict[dst]['base_vid'] + random_split
        if DEBUG:
            print(f"Vertex {dst} deg={v_dict[dst]['deg']} is split into {new_dst}")
    else:
        new_dst = dst
    
    split_edges.add((new_src, new_dst))
    if DEBUG:
        print(f"Edge ({src}, {dst}) is split into ({new_src}, {new_dst})")
        
# Construct the neighbor list from the split edge list
split_nlist = [[] for _ in range(split_vid)]

for src, dst in split_edges:
    split_nlist[src].append(dst)

if DEBUG:
    for v in v_dict:
        if v_dict[v]['split'] and (v_dict[v]['orig_vid'] == v):
            continue
        split_nlist[v].sort()
        edges = [(v, dst) for dst in split_nlist[v]]
        print(f"Neighbors of vertex {v} {'after split' if v_dict[v]['split'] else ''}: \n{edges}")

# Write the split neighbor list to a binary file
output_file = graph_file.replace('.txt', f'_remap_split_m{max_degree}.bin')
print(f"Writing split neighbor list to {output_file}")

distance = 0xffffffffffffffff
parent = 0
dummy_vertex = {'vid': 0, 'deg': 0, 'split': True, 'orig_vid': 0, 'base_vid': 0, 'split_num': 0}

max_split_vid = max(v_dict)
with open(output_file, 'wb') as file:
    file.seek(0)
    file.write((new_vid).to_bytes(8, 'little'))  # Write number of vertices
    file.write((split_vid + 1).to_bytes(8, 'little'))  # Write number of split vertices
    file.write(num_edges.to_bytes(8, 'little'))  # Write number of edges
    if VERBOSE:
        print(f"Writing number of vertices = {max_vid}, split vertices = {split_vid}, edges = {num_edges}")
    for v in range(split_vid):
        # if v not in v_dict: 
        #     vertex = dummy_vertex
        #     neighbors = []
        # else: 
        vertex = v_dict[v]
        neighbors = split_nlist[v]
        file.write(vertex['deg'].to_bytes(8, 'little'))  # Write degree
        file.write(vertex['orig_vid'].to_bytes(8, 'little'))  # Write original vertex ID
        file.write(vertex['vid'].to_bytes(8, 'little'))  # Write vertex ID
        file.write(id(neighbors).to_bytes(8, 'little'))  # Write neighbor list
        file.write(distance.to_bytes(8, 'little'))       # Write default distance
        file.write(parent.to_bytes(8, 'little'))         # Write default parent
        vid_range = ((vertex['base_vid'] & 0xffffffff) << 32 | ((vertex['base_vid'] + vertex['split_num']) & 0xffffffff))
        file.write(vid_range.to_bytes(8, 'little'))      # Write split range
        file.write((0).to_bytes(8, 'little'))
        if vertex['split'] and (vertex['orig_vid'] == vertex['vid']):
            if DEBUG_OUTPUT:
                print(f"Vertex vid={v} - deg {vertex['deg']}, dist {-1}, ori_vid {vertex['orig_vid']}, split_range [{vertex['base_vid']}, {vertex['base_vid'] + vertex['split_num']}], neigh_list {hex(id(neighbors))}")
                print("Neighbors: []")
            continue
        for neighbor in split_nlist[v]:
            file.write(neighbor.to_bytes(8, 'little'))  # Write neighbor ID
        if DEBUG_OUTPUT:
            print(f"Vertex vid={v} - deg {vertex['deg']}, dist {-1}, ori_vid {vertex['orig_vid']}, split_range [{vertex['base_vid']}, {vertex['base_vid'] + vertex['split_num']}], neigh_list {hex(id(neighbors))}")
            print(f"Neighbors: [{', '.join([f'{n}' for n in neighbors])}{', '  if neighbors else ''}]")
        
print(f"Done writing split neighbor list to {output_file}")