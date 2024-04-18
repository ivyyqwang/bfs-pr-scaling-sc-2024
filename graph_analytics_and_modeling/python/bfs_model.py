from scipy.stats import linregress
import numpy as np
from scipy.special import binom
from collections import namedtuple

# GEM5 Analysis Dependencies 
import pandas as pd
from io import StringIO
from scipy.optimize import lsq_linear
from sklearn.linear_model import LinearRegression
import math

#  Plotting depdencies 
import matplotlib.pyplot as plt
from matplotlib.ticker import LogLocator, LogFormatter
from matplotlib.ticker import FuncFormatter


#  -- Machine configuration

LanesPerUpdown = 64
LanesPerNode = 32*LanesPerUpdown
RoundtripTime = 2.5e-6

DRAMBandwidthStack = 500e9 # 500 GB/s
DRAMBandwidth = DRAMBandwidthStack*8


#
#  BFS Model
#

def er_dataset_projection(scale):
    d_avg = 35
    frontier_count = math.ceil(math.log(2**scale * d_avg, d_avg))
    # frontier i size will be d_avg^i
    ProblemSetup = namedtuple('ProblemSetup',['vertices_touched','edges_touched','vertices','edges','average_degree','num_frontiers'])
    return ProblemSetup(vertices_touched = 2**scale, #2**RMAT_scale,
                        edges_touched = 2**scale * d_avg,
                        vertices = 2**scale,
                        edges=2**scale * d_avg,
                        average_degree=d_avg,
                        num_frontiers = frontier_count)

def forest_fire_dataset_projection(scale):

    # edge data collected over 10 trials
    graph_scales = np.log2([256, 512, 1024, 2048, 4096, 8192, 16384, 32768, 65536, 131072, 262144, 524288, 1048576, 2097152, 4194304, 8388608, 16777216])
    edges = [1172,2324,4502,9157, 18070, 36201, 72489, 145102, 290164, 578913, 1157238, 2316556, 4632162, 9263641, 18517991, 37048602, 74081380]
    
    median_frontier_counts = [10.0,10.5,12.5,13.0,15.0,16.0,18.0,18.75,20.0,21.0,23.0,23.0,25.25,26.0,28.0,29.0,30.0]


    edge_r = linregress(graph_scales,np.log10(edges))
    frontier_r = linregress(graph_scales,median_frontier_counts)
    
    ProblemSetup = namedtuple('ProblemSetup',['vertices_touched','edges_touched','vertices','edges','num_frontiers'])
    return ProblemSetup(vertices_touched = 2**scale, #2**RMAT_scale,
                        edges_touched = 10**((edge_r.slope*scale + edge_r.intercept)), # Forest Fire Graphs are connected
                        vertices = 2**scale,
                        edges=10**((edge_r.slope*scale + edge_r.intercept)),
                        num_frontiers = frontier_r.slope*scale + frontier_r.intercept)


def rmat_dataset_projection(scale):

    ProblemSetup = namedtuple('ProblemSetup',['vertices_touched','edges_touched','vertices','edges','num_frontiers'])
    exp_data_scales = [10,12,14,16,18,20,22]
    ratio_of_edges_touched = [1.09880126953125,
                            1.242509521484375,
                            1.2426015625,
                            1.2352741165161132,
                            1.1760031700134277,
                            1.0855578474998475,
                            1.1700884662866593]
                            # > 1 bc the graph is undirected.

    exp_data_scales = [10,12,14,16,18,20]#,22,24,26,28]
    ratio_of_edges_touched = np.array([
        1.2854736328125,
        1.478036499023437,
        1.62550048828125,
        1.73480167388916,
        1.814803934097290,
        1.8716458439826966,])

    #expected_vertices_visited = 0.33 * 2**RMAT_scale# this is what happens after scale 22...
    expected_vertices_visited = 2**scale - Graph500_isolated_nodes(scale)
                                # vast majority of non-isolated nodes will be in the
                                # largest connected component.


    r = linregress(exp_data_scales,np.log10(2 - ratio_of_edges_touched))
    expected_edges_visited = (2 - 10**((r.slope*scale+ r.intercept)))*(16*2**scale)
    #expected_edges_visited = 2*16*2**RMAT_scale # we touch each edge twice.

    return ProblemSetup(vertices_touched = expected_vertices_visited, #2**RMAT_scale,
                        edges_touched = expected_edges_visited,
                        vertices = 2**scale,
                        edges=16*2**scale,
                        num_frontiers = 8)# RMAT graphs frontier's don't grow quickly


def Graph500_isolated_nodes(scale):
    a = .57
    b = .19
    p = a + b
    isolated_nodes = 0
    for i in range(scale+1):
        P_i = (p**i)*(1-p)**(scale -i)
        z = 2*np.log(1-P_i)*(16*2**scale)
        # factor of 2 is to account for the in and out degrees both being 0.
        isolated_nodes += np.exp(np.log(binom(scale,i)) + z)

    return isolated_nodes


def PUSH_BFS_UpDown_perf_from_GEM5():
    num_lanes =2048
    web_google = pd.read_csv(StringIO(
        """Phase runtime,New visited vertices,edges touched
        0.000002694340,2,203
        0.000002845000,206,3292
        0.000003353500,674,37128
        0.000008574000,4355,100010
        0.000060001500,32669,1599897
        0.000070580500,313995,4647691
        0.000042831500,262170,2220058
        0.000021106000,164571,774421
        0.000008592500,65047,192301
        0.000004515500,19346,50539
        0.000003039500,6703,15115
        0.000002754000,1923,3471
        0.000002202500,528,679
        0.000002142000,73,79
        0.000001630500,31,35
        0.000001397500,2,0
        """
    ))

    cit_patents = pd.read_csv(StringIO(
        """Phase runtime,New visited vertices,edges touched
        0.000001618840,1,5
        0.000001747500,5,36
        0.000001929500,32,612
        0.000002641500,348,6307
        0.000009887000,2733,49806
        0.000055190500,22705,427175
        0.000248682000,155130,2781308
        0.000703944500,694269,9845350
        0.000676967500,1475042,13957949
        0.000162904000,1069500,4846738
        0.000023291000,293904,456570
        0.000004716500,43330,30510
        0.000002229500,6046,3210
        0.000001936000,1088,571
        0.000001801000,270,154
        0.000001739000,70,37
        0.000001684500,19,2
        0.000001131500,1,0
        """
    ))
    youtube = pd.read_csv(StringIO(
        """Phase runtime,New visited vertices,edges touched
        0.00000236334,2,192
        0.00001078800,387,28653
        0.00008720050,40109,2746579
        0.00010134500,428168,3921358
        0.00003963000,478407,713061
        0.00001274800,160554,120927
        0.00000496900,42061,23959
        0.00000243150,10751,5304
        0.00000239500,2629,1409
        0.00000220750,801,321
        0.00000215700,145,110
        0.00000209700,52,36
        0.00000209100,21,27
        0.00000209300,19,2
        0.00000160300,1,0
     """
    ))

    flikr = pd.read_csv(StringIO(
    """Phase runtime,New visited vertices,edges touched
    0.000002653340,1,103
    0.000005631000,228,23426
    0.000033254000,19687,2109332
    0.000023756500,15716,1432975
    0.000065147500,60826,3952115
    0.000019692000,58923,612331
    0.000002165500,2979,17729
    0.000001561500,2,0
    """))

    forest_fire = pd.read_csv(StringIO(
        """Phase runtime,New visited vertices,edges touched
        0.0000026963350,1,128
        0.0000029150000,141,5698
        0.0000062030000,3278,69263
        0.0000175540000,26135,315972
        0.0000346045000,85218,681900
        0.0000549410000,153716,924534
        0.0000566125000,191846,931310
        0.0000563125000,188059,839369
        0.0000224760000,155192,496580
        0.0000150185000,110876,314407
        0.0000101125000,68840,172162
        0.0000057760000,36836,80589
        0.0000035500000,17371,33569
        0.0000023010000,7285,12789
        0.0000025995000,2660,4041
        0.0000024420000,836,1131
        0.0000023705000,246,251
        0.0000017515000,60,68
        0.0000017455000,12,6
        0.0000015420000,1,0
        """
    ))

    er = pd.read_csv(StringIO(
    """Phase runtime,New visited vertices,edges touched
    2.2658350E-06,1,38
    2.6155000E-06,38,1320
    9.4520000E-06,1281,46439
    1.2976000E-04,44163,1602513
    2.4415550E-04,773494,27412502
    7.7617500E-05,229599,7728318
    """))

    """"""
    perf = pd.concat([web_google,cit_patents,youtube,flikr,forest_fire,er])
    vertex_timings = []
    edge_timings = [] 

    runtimes = perf["Phase runtime"]
    perf[["New visited vertices","edges touched"]].astype(int)
    work_per_phase = perf[["New visited vertices","edges touched"]] / num_lanes
    #work_per_phase = pd.concat([work_per_phase[["New visited vertices","edges touched"]].applymap(np.ceil))
    #work_per_phase['intercept'] = [1.0]*work_per_phase.shape[0]
    pos_coeffs = lsq_linear(work_per_phase,runtimes,bounds=(1e-16,np.Inf))
        # using lsq_linear to prevent for regression          bounds prevent a 0.0
        # solutions which allow for access times to be 0.     access timesolution
    print(f"total data regression:{pos_coeffs.x}")
    TimePerNewVertexPerLane = pos_coeffs.x[0]
    TimePerEdgePerLane = pos_coeffs.x[1]



    print(f"TimePerNewVertexPerLane:{TimePerNewVertexPerLane} -- TimePerEdgePerLane:{TimePerEdgePerLane}")
    print(f"NewVertexPerLanePerSecond:{1/TimePerNewVertexPerLane} -- EdgePerLanePerSecond:{1/TimePerEdgePerLane}")
    return TimePerNewVertexPerLane, TimePerEdgePerLane


    #def bfs_runtime(data_model, num_lanes):
    #  return sum([(frontier_sizes/num_lanes)*TimePerEdge for frontier_sizes in data_model.frontier_sizes])


def Pull_Push_BFS_UpDown_perf_from_GEM5():
    num_lanes =2048
    # This data is based on approximating the pulling vertex edges with the average degree of youtube (5.26)
    youtube1 = pd.read_csv(StringIO(
        """Phase runtime,New visited vertices,edges touched
        0.0000033218300,2,192
        0.0000052410000,387,28653
        0.0000566110000,39795,2746579
        0.0000253362500,427893,3921358
        0.0000260398960,479433,1017051
        0.0000124658460,154398,204146
        0.0000065590000,29833,47075
        0.0000016688000,6714,11726
        0.0000005670000,1603,3286
        0.0000010422500,475,785
        0.0000010350000,92,301
        0.0000010147500,43,74
        0.0000006895000,13,6
        0.0000007015000,1,0
        """
    ))


    # This data is based on approximating the pulling vertex edges with the median degree of youtube (4)
    youtube2 = pd.read_csv(StringIO(
    """Phase runtime,New visited vertices,edges touched
    0.0000033218300,2,192
    0.0000052410000,387,28653
    0.0000566110000,39795,2746579
    0.0000253362500,427893,3921358
    0.0000260398960,479433,772688
    0.0000124658460,154398,155096
    0.0000065590000,29833,35764
    0.0000016688000,6714,8908
    0.0000005670000,1603,2496
    0.0000010422500,475,596
    0.0000010350000,92,228
    0.0000010147500,43,56
    0.0000006895000,13,4
    0.0000007015000,1,0
    """))


    youtube2 = pd.read_csv(StringIO("""Phase runtime,New visited vertices,edges touched
    0.0000033218300,2,192
    0.0000052410000,387,28653
    0.0000566110000,39795,2746579
    0.0000253362500,427893,2690420
    0.0000260398960,479433,772688
    0.0000124658460,154398,155096
    0.0000065590000,29833,35764
    0.0000016688000,6714,8908
    0.0000005670000,1603,2496
    0.0000010422500,475,596
    0.0000010350000,92,228
    0.0000010147500,43,56
    0.0000006895000,13,4
    0.0000007015000,1,0
    """))

    runtimes = youtube2["Phase runtime"]
    youtube2[["New visited vertices","edges touched"]].astype(int)
    work_per_phase = youtube2[["New visited vertices","edges touched"]] / num_lanes
    #work_per_phase = pd.concat([work_per_phase[["New visited vertices","edges touched"]].applymap(np.ceil))
    #work_per_phase['intercept'] = [1.0]*work_per_phase.shape[0]
    pos_coeffs = lsq_linear(work_per_phase,runtimes,bounds=(1e-16,np.Inf))
        # using lsq_linear to prevent for regression          bounds prevent a 0.0
        # solutions which allow for access times to be 0.     access timesolution
    print(f"total data regression:{[1/y for y in pos_coeffs.x]}")
    TimePerNewVertexPerLane = pos_coeffs.x[0]
    TimePerEdgePerLane = pos_coeffs.x[1]

    return TimePerNewVertexPerLane, TimePerEdgePerLane 




P_BFS_TimePerNewVertexPerLane, P_BFS_TimePerEdgePerLane = PUSH_BFS_UpDown_perf_from_GEM5()
PP_BFS_TimePerNewVertexPerLane, PP_BFS_TimePerEdgePerLane = Pull_Push_BFS_UpDown_perf_from_GEM5()


def high_degree_subsampling(edges, nodes):
    SubSampledEdgesProb = .01
    IngestEdgesPerSecondPerLane = 150264.0186 # from GEM5 12/30
    return max(
        edges*SubSampledEdgesProb/IngestEdgesPerSecondPerLane/(nodes*LanesPerNode),
        2*edges*16*SubSampledEdgesProb / (DRAMBandwidth*nodes))



def time_build_adj(problem, nodes):
    maxdeg = 3 * 256  # degrees are split to 256
                    # (add in a factor of 3 for fudgefactor)

    avgworkperlane = problem.edges/(nodes*LanesPerNode)

    BuildAdjAggregationRatePerLane = 2e8 # measured for PDR
    taillatency = maxdeg/BuildAdjAggregationRatePerLane  + maxdeg*RoundtripTime/16

    avgtime = avgworkperlane/BuildAdjAggregationRatePerLane + avgworkperlane*RoundtripTime/16
    return 2*(taillatency + avgtime) # factor of 2 accounts for two passes needed o
                                        # over the edges


def bfs_runtime(data_model,method,num_lanes):

    full_time = 0.0
    if method == "Push-BFS":
        full_time += (data_model.vertices/num_lanes)*P_BFS_TimePerNewVertexPerLane +(data_model.edges_touched/num_lanes)*P_BFS_TimePerEdgePerLane
    elif method == "Push-Pull-BFS":
        full_time += (data_model.vertices/num_lanes)*PP_BFS_TimePerNewVertexPerLane +(data_model.edges_touched/num_lanes)*PP_BFS_TimePerEdgePerLane
    else:
        raise ValueError(f"got{method}")
    full_time += 2*data_model.num_frontiers*RoundtripTime*math.ceil(math.log2(num_lanes/2048))
 
    return full_time


def get_GTEPS(scale, method, graph_type): 

    def projection(data_model,numnodes):
        lanes = 2048*numnodes
        return bfs_runtime(data_model,method, lanes)

    if graph_type == "RMAT":
        data_model = rmat_dataset_projection(scale)
    elif graph_type == "ER":
        data_model = er_dataset_projection(scale)
    elif graph_type == "FF":
        data_model = forest_fire_dataset_projection(scale)
    else: 
        raise ValueError(f"inputted `graph_type` must be one of: 'RMAT', 'ER', or 'FF'. got {graph_type}\n")
    
    numnodes_list = [32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384, 32768]
    projections = [data_model.edges_touched/projection(data_model,numnodes)/1e9 for numnodes in numnodes_list]
    print(projections)



def make_figure():
    def projection(data_model,method,numnodes):
        lanes = 2048*numnodes
        return bfs_runtime(data_model,method,lanes)

    def simple_formatter(x, pos):
        return f'{int(x)}'

    def feasible(data_model,numnodes):
        #data_model = rmat_dataset_projection(scale)

        memrequired = (data_model.edges*8 + # 16 edges per node, 8 bytes per edge
                        data_model.vertices*16) # 16 bytes per node for distance/parent

        #need space to store the frontiers
        max_frontier_size_mem = data_model.edges_touched * 8
                                    # frontier size projections run very large.
                                    # frontier cannot be larger than the number of
                                    # edges in the graph.
        memrequired += max_frontier_size_mem

        return memrequired < numnodes*512e9 # 512 GB/node

    numnodes_list = [32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384]


    plt.ioff()
    plt.figure()


    graph_types = ["RMAT"]#, "ER", "FF"]
    scales = [26,28,30,32,36,40]

    method = "Pull-Push-BFS"    
    method = "Push-BFS"
    for scale in scales:
        for graph_type in graph_types:
            if graph_type == "RMAT":
                data_model = rmat_dataset_projection(scale)
            elif graph_type == "ER":
                data_model = er_dataset_projection(scale)
            elif graph_type == "FF":
                data_model = forest_fire_dataset_projection(scale)
            else: 
                raise ValueError(f"inputted `graph_type` must be one of: 'RMAT', 'ER', or 'FF'. got {graph_type}\n")
            projections = [projection(data_model,method,numnodes) for numnodes in numnodes_list]
            line1, = plt.loglog(numnodes_list, projections, linestyle="--", linewidth=0.5)

            feasible_nodes = [numnodes for numnodes in numnodes_list if feasible(data_model, numnodes)]

            projections = [projection(data_model,method,numnodes) for numnodes in feasible_nodes ]

            label = f'{graph_type} Scale {scale}'
            plt.loglog(feasible_nodes, projections, label=label, color=line1.get_color())


    # add a star for the PDR projection
    #plt.plot(16384, 0.126, marker="*", label="PDR Projection (Scale 36)",color='orange')
    #plt.plot(16384, 8.563, marker="*", label="PDR Projection (Scale 42)",color=targetcolor)
    plt.xscale('log', base=2)
    plt.yscale('log', base=2)
    #plt.gca().xaxis.set_major_locator(LogLocator(base=2))


    plt.gca().xaxis.set_major_formatter(FuncFormatter(simple_formatter))
    plt.gca().yaxis.tick_right()

    plt.xlabel('Number of Nodes')
    plt.ylabel('Projected PageRank Runtime (s)')
    plt.title('Push BFS Projection Runtime for Different Graphs')
    plt.xticks(numnodes_list)
    plt.legend(loc='upper right')
    plt.grid(True, which="both", ls="-")
    plt.grid(which='minor', axis='both', linestyle='', color='none')
    

    bbox = dict(boxstyle="round", ec="w", fc="w", alpha=.4,pad=.00)
    graph_labels = ["RMAT", "Erdos\nRenyi", "Forest\nFire"]
    
    # Need to show this as GTEPS
    plt.ioff()
    fig = plt.figure()
    gs = fig.add_gridspec(1, 3,
                        left=0.1, right=0.9,top=.9,bottom=0.125,
                        wspace=0.35,hspace=.25) 

    all_axes = np.empty((3),dtype=object)

    for i in range(3): 
        if i == 0:
            all_axes[i] = fig.add_subplot(gs[0,i])
        else:
            all_axes[i] = fig.add_subplot(gs[0,i],sharey=all_axes[0])

    graph_types = ["RMAT", "ER", "FF"]
    scales = [28,32,36,40]
    #method = "Push-BFS"
    method = "Push-Pull-BFS" 


    for scale in scales:
        for (i,graph_type) in enumerate(graph_types):
            if graph_type == "RMAT":
                data_model = rmat_dataset_projection(scale)
            elif graph_type == "ER":
                data_model = er_dataset_projection(scale)
            elif graph_type == "FF":
                data_model = forest_fire_dataset_projection(scale)
            else: 
                raise ValueError(f"inputted `graph_type` must be one of: 'RMAT', 'ER', or 'FF'. got {graph_type}\n")
            
            print(f"edges touched:{data_model.edges_touched}")
            projections = [data_model.edges_touched/projection(data_model,method,numnodes) /1e9 for numnodes in numnodes_list]
            line1, = all_axes[i].loglog(numnodes_list, projections, linestyle="--", linewidth=0.5)
            feasible_nodes = [numnodes for numnodes in numnodes_list if feasible(data_model, numnodes)]
            projections = [data_model.edges_touched/projection(data_model,method,numnodes)/1e9 for numnodes in feasible_nodes]
            label = f'scale - {scale}' 
            all_axes[i].loglog(feasible_nodes, projections, label=label, color=line1.get_color())






    #plt.plot(numnodes_list,[32*nodes for nodes in numnodes_list], color='r', linestyle='--', label="AGILE Target (1 GTEP/UD)")

    for (i,ax) in enumerate(all_axes):
        ax.set_xscale('log', base=2)
        ax.set_yscale('log', base=2)
        #plt.gca().xaxis.set_major_locator(LogLocator(base=2))

        ax.yaxis.tick_right()

        ax.annotate(graph_labels[i],xy=(.3,.9),fontsize=15,xycoords="axes fraction",ha="center",va="top").set_bbox(bbox)
        #if box is not None:

        ax.set_xlabel('Number of Nodes')
        if i == 0:
            ax.set_ylabel('Projected Compute Rate (GTEPS)')

            
        if i == 1:
            ax.set_title(f'Projected {method} Compute Rate for Different Scales, Graphs, and Nodes',fontsize=11)
            ax.legend(loc='lower right')

        if i == 2:
            pass
            
        ax.set_xticks(numnodes_list[::2])
        
        ax.grid(True, which="both", ls="-")
        ax.grid(which='minor', axis='both', linestyle='', color='none')
        ax.spines[:].set_visible(False)
        ax.set_ylim((2**8,2**28))
    
    """
    # Need to show this as GTEPS
    plt.ioff()
    plt.figure()

    for s in scales:
        projections = [touched_edges(s, numnodes)/projection(s, numnodes)/1e9/(numnodes*0.590) for numnodes in numnodes_list]
        line1, = plt.semilogx(numnodes_list, projections, linestyle="--", linewidth=0.5)
        feasible_nodes = [numnodes for numnodes in numnodes_list if feasible(s, numnodes)]
        projections = [ touched_edges(s, numnodes)/projection(s, numnodes)/1e9/(numnodes*0.590) for numnodes in feasible_nodes  ]
        label = f'Scale {s}'
        if s == AGILE_TARGET:
            label += " - AGILE Target"
            targetcolor = line1.get_color()
        plt.semilogx(feasible_nodes, projections, label=label, color=line1.get_color())

    plt.xscale('log', base=2)
    #plt.yscale('log', base=10)
    #plt.gca().xaxis.set_major_locator(LogLocator(base=2))

    plt.gca().xaxis.set_major_formatter(FuncFormatter(simple_formatter))

    plt.xlabel('Number of Nodes')
    plt.ylabel('Projected Power Efficiency (GTEPS/KW)')
    plt.title('Projection Power Efficiency for Different Scales and Nodes')
    plt.xticks(numnodes_list)
    plt.legend()
    plt.grid(True, which="both", ls="-")
    plt.grid(which='minor', axis='both', linestyle='', color='none')
    """
    plt.show()