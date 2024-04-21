# bfs-pr-scaling-sc-2024

This repository contains the UpDown accelerator simulator, UpDown accelerator programs and the projection model for the full system design.

## Folder Structure 
The folder structure of the respository

```
├── graph_analytics_and_modeling        # projection model. 
│   ├── julia                           # key experiment drivers, graph generators and project level parameters
|   ├── data                            # SNAP & random graphs used in GEM5 simulations, and data used for computing statistics used in models
│   └── python                          # modeling code for projecting performance for BFS and PageRank routines 
├── udgem5sim                           # pre-made default configurations for gem5
│   ├──configs                          # gem5 simulation configuration files
│   |   └── updown                      # updown system configuration files
│   ├── ext                             # gem5 extensions
│   |   ├── updown                      # updown simulator extension and program files
│   |   |   └── apps                    # updown program code and top drivers
└── util                                # useful utility programs and files (gem5)
```