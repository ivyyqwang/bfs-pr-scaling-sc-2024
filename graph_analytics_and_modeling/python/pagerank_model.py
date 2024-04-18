from scipy.stats import linregress
import numpy as np
from scipy.special import binom
from collections import namedtuple

# GEM5 Analysis Dependencies 
import pandas as pd
from io import StringIO
from scipy.optimize import lsq_linear
import math

#  Plotting depdencies 
import matplotlib.pyplot as plt
from matplotlib.ticker import LogLocator, LogFormatter
from matplotlib.ticker import FuncFormatter

VERTEX_SPLIT_SIZE = 256

#  -- Machine configuration

LanesPerUpdown = 64
LanesPerNode = 32*LanesPerUpdown
RoundtripTime = 2.5e-6

DRAMBandwidthStack = 500e9 # 500 GB/s
DRAMBandwidth = DRAMBandwidthStack*8



def er_dataset_projection(scale):

    graph_scales = np.log2([256, 512, 1024, 2048, 4096, 8192, 16384, 32768, 65536, 131072, 262144, 524288, 1048576, 2097152, 4194304, 8388608, 16777216])
    # Results:(alpha = .85, tol = 1/n) 10 Trials
    PR_median_active_set_volume_sums = [2545.0, 5111.0, 10236.0, 20411.0, 40881.0, 82134.0, 163835.0, 327559.0, 655528.0, 1.310152e6, 2.622152e6, 5.244502e6, 1.0485793e7, 2.0970665e7, 4.1939426e7, 8.3889363e7, 1.67770398e8]
    PR_median_iterations = [1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0]
    DD_PR_median_active_set_volume_sums = [2545.0, 5111.0, 10236.0, 20411.0, 40881.0, 82134.0, 163835.0, 327559.0, 655528.0, 1.310152e6, 2.622152e6, 5.244502e6, 1.0485793e7, 2.0970665e7, 4.1939426e7, 8.3889363e7, 1.67770398e8]
    DD_PR_median_iterations = [2.0,2.0,2.0,2.0,2.0,2.0,2.0,2.0,2.0,2.0,2.0,2.0,2.0,2.0,2.0,2.0,2.0]
    

    PR_volume_r = linregress(graph_scales,np.log10(PR_median_active_set_volume_sums))
    PR_iterations_r = linregress(graph_scales,np.log10(PR_median_iterations))
    DD_PR_volume_r = linregress(graph_scales,np.log10(DD_PR_median_active_set_volume_sums))
    DD_PR_iterations_r = linregress(graph_scales,np.log10(DD_PR_median_iterations))


    d_avg = 35
    ProblemSetup = namedtuple('ProblemSetup',['PR_sum_of_active_set_volumes','DD_PR_sum_of_active_set_volumes','PR_iterations','DD_PR_iterations','vertices','edges','max_degree','average_degree'])
    return ProblemSetup(PR_sum_of_active_set_volumes=10**((PR_volume_r.slope*scale+ PR_volume_r.intercept)),
                        DD_PR_sum_of_active_set_volumes =10**((DD_PR_volume_r.slope*scale+ DD_PR_volume_r.intercept)),
                        PR_iterations = 10**((PR_iterations_r.slope*scale+ PR_iterations_r.intercept)),
                        DD_PR_iterations = 10**((DD_PR_iterations_r.slope*scale+ DD_PR_iterations_r.intercept)),
                        vertices=2**scale,
                        edges=2**scale * d_avg,
                        max_degree = d_avg,
                        average_degree = d_avg)
        
def forest_fire_dataset_projection(scale):

    graph_scales = np.log2([256, 512, 1024, 2048, 4096, 8192, 16384, 32768, 65536, 131072, 262144, 524288, 1048576, 2097152, 4194304, 8388608, 16777216])
    edges = [1172,2324,4502,9157,18070,36201,72489,145102,290164,578913,1157238,2316556,4632162,9263641,18517991,37048602,74081380]
    max_degrees = [30.5,36.0,42.0,57.0,62.5,71.0,84.5,113.0,120.5,142.0,157.5,191.5,231.0,254.0,275.0,314.5,360.0]

    # Results:(alpha = .85, tol = 1e-12)
    PR_median_active_set_volume_sums = [592572.0, 1.309e6, 2.83824e6, 6.061741e6, 1.2695079e7, 2.651064e7, 5.4542208e7, 1.11273246e8, 2.2735425e8, 4.66114875e8, 9.4388738e8, 1.888730068e9, 3.799602675e9, 7.56116361e9, 1.5140025636e10, 3.0005248344e10, 5.988662467e10]
    DD_PR_median_active_set_volume_sums =[312586.5, 743654.5, 1.5656095e6, 3.444769e6, 6.7342e6, 1.4007107e7, 3.33594225e7, 6.0354513e7, 1.16453725e8, 2.46550537e8, 5.799371665e8, 1.2850511e9, 1.913519699e9, 4.0640463645e9, 8.0890991665e9, 1.7475391481e10, 2.9775739823e10]

    # Results:(alpha = .85, tol = 1/n) 10 trials
    PR_median_active_set_volume_sums = [1172.0, 2324.0, 4502.0, 9254.0, 18259.0, 72496.0, 367805.0, 1.018017e6, 2.324232e6, 5.216364e6, 1.0985749e7, 2.5482842e7, 5.557884e7, 1.20289715e8, 2.49972723e8, 5.1882761e8, 1.111459425e9]
    PR_median_iterations = [1.0,1.0,1.0,1.0,1.0,2.0,5.0,7.0,8.0,9.0,9.5,11.0,12.0,13.0,13.5,14.0,15.0]
    DD_PR_median_active_set_volume_sums = [1172.0, 2324.0, 4502.0, 9254.0, 18259.0, 37696.5, 76211.5, 151781.0, 302745.5, 609039.5, 1.211528e6, 2.423401e6, 4.8527125e6, 9.686378e6, 1.9370424e7, 3.87653785e7, 7.7518866e7]
    DD_PR_median_iterations = [2.0,2.0,2.0,2.0,2.0,3.0,3.0,3.0,3.0,4.0,4.0,4.0,4.0,5.0,5.0,5.0,5.0]
    
    edge_r = linregress(graph_scales,np.log10(edges))
    max_deg_r = linregress(graph_scales,np.log10(edges))
    PR_volume_r = linregress(graph_scales,np.log10(PR_median_active_set_volume_sums))
    PR_iterations_r = linregress(graph_scales,np.log10(PR_median_iterations))
    DD_PR_volume_r = linregress(graph_scales,np.log10(DD_PR_median_active_set_volume_sums))
    DD_PR_iterations_r = linregress(graph_scales,np.log10(DD_PR_median_iterations))
    #ADD_PR_volume_r = linregress(graph_scales,np.log10(ADD_PR_median_active_set_volume_sums))

    projected_edges = 10**((edge_r.slope*scale + edge_r.intercept))
    ProblemSetup = namedtuple('ProblemSetup',['PR_sum_of_active_set_volumes','DD_PR_sum_of_active_set_volumes','PR_iterations','DD_PR_iterations','vertices','edges','max_degree','average_degree'])
    return ProblemSetup(PR_sum_of_active_set_volumes=10**((PR_volume_r.slope*scale+ PR_volume_r.intercept)),
                        DD_PR_sum_of_active_set_volumes =10**((DD_PR_volume_r.slope*scale+ DD_PR_volume_r.intercept)),
                        PR_iterations = 10**((PR_iterations_r.slope*scale+ PR_iterations_r.intercept)),
                        DD_PR_iterations = 10**((DD_PR_iterations_r.slope*scale+ DD_PR_iterations_r.intercept)),
                        vertices=2**scale,
                        edges=projected_edges,
                        max_degree = 10**((max_deg_r.slope*scale + max_deg_r.intercept)),
                        average_degree = projected_edges/2**scale)

def rmat_dataset_projection(scale):

    graph_scales = np.log2([256, 512, 1024, 2048, 4096, 8192, 16384, 32768, 65536, 131072, 262144, 524288, 1048576, 2097152, 4194304, 8388608, 16777216])
    max_deg_scales = [12, 14, 16, 18, 20, 22, 24] # RMAT max degree data comes from a different study 
    max_deg = [  1303.,  3578.,   9586.,  24917.,  63827., 161217., 402034.]
    max_deg_r = linregress(max_deg_scales,np.log10(max_deg))

    # Results:(alpha = .85, tol = 1e-12)
    PR_median_active_set_volume_sums = [592572.0, 1.309e6, 2.83824e6, 6.061741e6, 1.2695079e7, 2.651064e7, 5.4542208e7, 1.11273246e8, 2.2735425e8, 4.66114875e8, 9.4388738e8, 1.888730068e9, 3.799602675e9, 7.56116361e9, 1.5140025636e10, 3.0005248344e10, 5.988662467e10]
    DD_PR_median_active_set_volume_sums = [312586.5, 743654.5, 1.5656095e6, 3.444769e6, 6.7342e6, 1.4007107e7, 3.33594225e7, 6.0354513e7, 1.16453725e8, 2.46550537e8, 5.799371665e8, 1.2850511e9, 1.913519699e9, 4.0640463645e9, 8.0890991665e9, 1.7475391481e10, 2.9775739823e10]
    ADD_PR_median_active_set_volume_sums = [649383.5, 1.4440455e6, 4.495623e6, 9.741252e6, 1.63961675e7, 3.01169655e7, 6.21313015e7, 1.302421725e8, 2.71673075e8, 5.41519421e8, 1.1525074065e9, 2.998476499e9, 4.9744113985e9, 8.991611773e9, 1.8261645128e10, 4.19123946825e10, 6.63400586185e10]

    # Results:(alpha = .85, tol = 1/n)
    PR_median_active_set_volume_sums = [8588.0, 38584.0, 147392.0, 455770.0, 1.162908e6, 3.05913e6, 7.669998e6, 1.766242e7, 4.1833182e7, 9.3222975e7, 2.1313586e8, 4.79882542e8, 1.036255275e9, 2.28741084e9, 4.875601476e9, 1.0605303294e10, 2.2392390094e10]
    PR_median_iterations = [2.0,4.0,7.0,10.0,12.0,15.0,18.0,20.0,23.0,25.0,28.0,31.0,33.0,36.0,38.0,41.0,43.0]
    
    DD_PR_median_active_set_volume_sums = [8507.5, 19126.5, 58525.5, 127114.5, 239740.0, 1.092211e6, 1.441181e6, 4.062289e6, 8.1860055e6, 1.5264268e7, 8.36007145e7, 7.4676056e7, 1.775295935e8, 6.04225391e8, 8.39808159e8, 2.401841338e9, 4.4558972115e9]
    DD_PR_median_iterations = [3.0,3.0,4.0,4.0,4.0,7.0,5.0,7.0,6.0,6.0,13.5,7.0,8.5,12.5,9.0,15.0,11.0]
    
    PR_volume_r = linregress(graph_scales,np.log10(PR_median_active_set_volume_sums))
    PR_iterations_r = linregress(graph_scales,np.log10(PR_median_iterations))
    DD_PR_volume_r = linregress(graph_scales,np.log10(DD_PR_median_active_set_volume_sums))
    DD_PR_iterations_r = linregress(graph_scales,np.log10(DD_PR_median_iterations))

    ProblemSetup = namedtuple('ProblemSetup',['PR_sum_of_active_set_volumes','DD_PR_sum_of_active_set_volumes','PR_iterations','DD_PR_iterations','vertices','edges','max_degree','average_degree'])
    return ProblemSetup(PR_sum_of_active_set_volumes=10**((PR_volume_r.slope*scale+ PR_volume_r.intercept)),
                        DD_PR_sum_of_active_set_volumes =10**((DD_PR_volume_r.slope*scale+ DD_PR_volume_r.intercept)),
                        PR_iterations = 10**((PR_iterations_r.slope*scale+ PR_iterations_r.intercept)),
                        DD_PR_iterations = 10**((DD_PR_iterations_r.slope*scale+ DD_PR_iterations_r.intercept)),
                        vertices=2**scale - Graph500_isolated_nodes(scale),
                        edges=2*2**scale * 16,
                        max_degree = 10**((max_deg_r.slope*scale + max_deg_r.intercept)),
                        average_degree = 2*16)



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


def UpDown_perf_from_GEM5():
    #=
    num_lanes =64*32*2
    #2048 data
    PR_10_iterations = [
        0.003224,
        0.008702,
        0.017199,
        0.002871,
        0.001686,
        0.015092,
        0.011201,
        0.003685,
    ]
    PR_10_iterations = [
        0.002744,
        0.007389,
        0.012397,
        0.001891,
        0.00146,
        0.011211,
        0.008585,
        0.002734,
    ]

    DD_PR_1_iteration = [
       0.000428,
       0.000835,
       0.001362,
       0.000306,
       0.000196,
       0.00228,
    ]
    edges = [
        7561938,
        32398535,
        71950084,
        9644919,
        6865626,
        63540880,#2410360,
        73418470,#36791130,
        9250848,#4883767,
    ]

    print([pr_t/(dd_pr_t) for (dd_pr_t,pr_t) in zip(DD_PR_1_iteration,PR_10_iterations)])

    PR_time_per_edge_per_lane = [((PR_t/(e*10/num_lanes))) for (PR_t,e) in zip(PR_10_iterations,edges)]
    DD_PR_time_per_edge_per_lane = [((DD_PR_t/(e/num_lanes))) for (DD_PR_t,e) in zip(DD_PR_1_iteration,edges)]
    
    return np.median(PR_time_per_edge_per_lane), np.median(DD_PR_time_per_edge_per_lane)

PR_TimePerEdgePerLane, DD_PR_TimePerEdgePerLane = UpDown_perf_from_GEM5()

def pagerank_runtime(data_model,num_lanes,method):
    
    if method == "PR": # standard pagerank 
        total_work = data_model.PR_sum_of_active_set_volumes
        iterations = data_model.PR_iterations
        TimePerEdgePerLane = PR_TimePerEdgePerLane
    elif method == "DD-PR": # Data Driven pagerank 
        total_work = data_model.DD_PR_sum_of_active_set_volumes
        iterations = data_model.DD_PR_iterations
        TimePerEdgePerLane = DD_PR_TimePerEdgePerLane
    else:
        raise ValueError(f"method is expected to be on of: `PR` or `DD-PR`.\n got {method}")
    
    #print(f"method:{method}   sum_of_volumes:{total_work}   iterations:{iterations}  max_degree:{data_model.max_degree}")
    full_time = (total_work/num_lanes)*TimePerEdgePerLane
    if data_model.max_degree > VERTEX_SPLIT_SIZE:
        components_to_synchronize = math.ceil(math.ceil((data_model.max_degree/VERTEX_SPLIT_SIZE))/(num_lanes/2048))
        #NOTE: This would assume that each split vertex is placed on a different node.
        #      Definitely overkill as sychronization on node would be much faster. 
        full_time += iterations*RoundtripTime*math.ceil(math.log2(components_to_synchronize))
    full_time += iterations*RoundtripTime*math.ceil(math.log2(num_lanes/2048))
    return full_time


def get_GTEPS(scale, method, graph_type): 

    def projection(data_model,numnodes,graph_type):
        lanes = 2048*numnodes
        return pagerank_runtime(data_model,lanes,graph_type)

    def touched_edges(data_model):
        return data_model.PR_iterations*data_model.edges

    if graph_type == "RMAT":
        data_model = rmat_dataset_projection(scale)
    elif graph_type == "ER":
        data_model = er_dataset_projection(scale)
    elif graph_type == "FF":
        data_model = forest_fire_dataset_projection(scale)
    else: 
        raise ValueError(f"inputted `graph_type` must be one of: 'RMAT', 'ER', or 'FF'. got {graph_type}\n")
    
    numnodes_list = [32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384, 32768]
    projections = [ touched_edges(data_model)/projection(data_model,numnodes,method)/1e9 for numnodes in numnodes_list]
    print(projections)



def make_figure():
    def projection(data_model,numnodes,graph_type):
        lanes = 2048*numnodes
        return pagerank_runtime(data_model,lanes,graph_type)

    def simple_formatter(x, pos):
        return f'{int(x)}'

    def feasible(data_model,numnodes,method):
        #data_model = rmat_dataset_projection(scale)
        memrequired = data_model.edges*8 # 8 bytes per edge
        if method == "PR":
            memrequired +=  3*data_model.vertices*8 #8 bytes per vertex
                             # 2 vectors for x and x_new, and 1 for degrees
        elif method == "DD-PR":
            memrequired +=  data_model.vertices*(2*8 +(2*0.125)) #8 bytes per vertex
                             # 2 vector for x & degrees, and 2 Bit-vectors for active_sets
        else:
            raise ValueError(f"method is expected to be on of: `PR` or `DD-PR`.\n got {method}")
    
        return memrequired < numnodes*512e9 # 512 GB/node

    def touched_edges(data_model, method):
        return data_model.PR_iterations*data_model.edges
        if method == "PR":
            return data_model.PR_sum_of_active_set_volumes
        elif method == "DD-PR":
            return data_model.PR_iterations
        else:
            ValueError(f"method is expected to be on of: `PR` or `DD-PR`.\n got {method}")

    numnodes_list = [32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384]

    bbox = dict(boxstyle="round", ec="w", fc="w", alpha=.4,pad=.00)
    graph_labels = ["RMAT", "Erdos\nRenyi", "Forest\nFire"]
    plt.ioff()
    fig = plt.figure()
    gs = fig.add_gridspec(1, 3,
                          left=0.1, right=0.975,top=.925,bottom=0.125,
                          wspace=0.35,hspace=.25) 

    all_axes = np.empty((3),dtype=object)

    for i in range(3): 
        all_axes[i] = fig.add_subplot(gs[0,i])

    methods = ["DD-PR"] #["PR"]
    #methods = ["PR"]
    graph_types = ["RMAT", "ER", "FF"]
    scales = [26,28,30,32,36,40]
    for scale in scales:
        for method in methods:
            for (i,graph_type) in enumerate(graph_types):
                if graph_type == "RMAT":
                    data_model = rmat_dataset_projection(scale)
                elif graph_type == "ER":
                    data_model = er_dataset_projection(scale)
                elif graph_type == "FF":
                    data_model = forest_fire_dataset_projection(scale)
                else: 
                    raise ValueError(f"inputted `graph_type` must be one of: 'RMAT', 'ER', or 'FF'. got {graph_type}\n")
                
                projections = [projection(data_model,numnodes,method) for numnodes in numnodes_list]
                line1, = all_axes[i].loglog(numnodes_list, projections, linestyle="--", linewidth=0.5)

                feasible_nodes = [numnodes for numnodes in numnodes_list if feasible(data_model, numnodes, method)]

                projections = [projection(data_model,numnodes,method) for numnodes in feasible_nodes ]
                label = f'{method} - {graph_type} - {scale}'

                all_axes[i].loglog(feasible_nodes, projections, label=label, color=line1.get_color())
                print(f"method:{method}\ngraph_type:{graph_type}\nfeasible_nodes:{feasible_nodes}\nprojections:{projections}")




 
    for (i,ax) in enumerate(all_axes):
        ax.set_xscale('log', base=2)
        ax.set_yscale('log', base=2)
        #plt.gca().xaxis.set_major_locator(LogLocator(base=2))

        ax.yaxis.tick_right()

        ax.annotate(graph_labels[i],xy=(.3,.9),fontsize=15,xycoords="axes fraction",ha="center",va="top").set_bbox(bbox)
        #if box is not None:

        ax.set_xlabel('Number of Nodes')
        if i == 0:
            ax.set_ylabel('Projected Runtime')
           
        if i == 1:
            ax.set_title('Projected Compute Rate for Different Scales, Graphs, and Nodes')
            if methods[0] == "PR":
                ax.legend(loc='lower right')    

        if i == 2:
            if methods[0] == "DD-PR":
                ax.legend(loc='lower right')    

        ax.set_xticks(numnodes_list[::2])
        
        ax.grid(True, which="both", ls="-")
        ax.grid(which='minor', axis='both', linestyle='', color='none')
        ax.spines[:].set_visible(False)

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


    s = 40 
    graph_types = ["RMAT", "ER", "FF"]
    scales = [28,32,36,40]
    for scale in scales:
        for method in methods:
            for (i,graph_type) in enumerate(graph_types):
                if graph_type == "RMAT":
                    data_model = rmat_dataset_projection(scale)
                elif graph_type == "ER":
                    data_model = er_dataset_projection(scale)
                elif graph_type == "FF":
                    data_model = forest_fire_dataset_projection(scale)
                else: 
                    raise ValueError(f"inputted `graph_type` must be one of: 'RMAT', 'ER', or 'FF'. got {graph_type}\n")
                
                projections = [touched_edges(data_model,method)/projection(data_model,numnodes,method)/1e9 for numnodes in numnodes_list]
                line1, = all_axes[i].loglog(numnodes_list, projections, linestyle="--", linewidth=0.5)
                feasible_nodes = [numnodes for numnodes in numnodes_list if feasible(data_model,numnodes, method)]
                projections = [ touched_edges(data_model,method)/projection(data_model,numnodes,method)/1e9 for numnodes in feasible_nodes  ]
                label = f'scale - {scale}'

                all_axes[i].loglog(feasible_nodes, projections, label=label, color=line1.get_color())

                #if method == "DD-PR" and graph_type == "FF":
                #    all_axes[i].axhline(max(projections),color=line1.get_color(),linewidth=.5)

    # add a star for the PDR projection
    #plt.scatter([16384], [8128.8], marker="*", label="PDR Projection (Scale 36)",color='orange')
    #plt.scatter([16384], [8728.8], marker="*", label="PDR Projection (Scale 42)",color=targetcolor)


    for (i,ax) in enumerate(all_axes):
        ax.set_xscale('log', base=2)
        ax.set_yscale('log', base=2)
        #plt.gca().xaxis.set_major_locator(LogLocator(base=2))

        ax.yaxis.tick_right()


        ax.annotate(graph_labels[i],xy=(.3,.9),fontsize=15,xycoords="axes fraction",ha="center",va="top").set_bbox(bbox)
        #if box is not None:

        ax.set_xlabel('Number of Nodes')
        if i == 0:
            if method == "DD-PR":
                ax.set_ylabel('Projected Effective Compute Rate (GTEPS)')
            else:
                ax.set_ylabel('Projected Compute Rate (GTEPS)')  
            
            
        if i == 1:
            ax.set_title(f'Projected {methods[0]} Compute Rate for Different Scales, Graphs, and Nodes')
            if methods[0] == "PR":
                    ax.legend(loc='lower right')    

        if i == 2:
            if methods[0] == "DD-PR":
                ax.legend(loc='lower right')    
            
        ax.set_xticks(numnodes_list[::2])
        ax.set_yticks([2**8, 2**11, 2**14, 2**17, 2**20, 2**23, 2**26, 2**28])
        
        ax.grid(True, which="both", ls="-")
        ax.grid(which='minor', axis='both', linestyle='', color='none')
        ax.spines[:].set_visible(False)
        ax.set_ylim(2**8, 2**29)

    plt.show()