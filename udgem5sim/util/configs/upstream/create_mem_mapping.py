import sys

preamble = "/*\n * Copyright (c) 2021 University of Chicago\n  * All rights reserved.\n \
 * \n  * Redistribution and use in source and binary forms, with or without\n  \
 * modification, are permitted provided that the following conditions are\n \
 * met: redistributions of source code must retain the above copyright\n  \
 * notice, this list of conditions and the following disclaimer;\n \
 * redistributions in binary form must reproduce the above copyright\n \
 * notice, this list of conditions and the following disclaimer in the\n \
 * documentation and/or other materials provided with the distribution;\n \
 * neither the name of the copyright holders nor the names of its\n \
 * contributors may be used to endorse or promote products derived from \n\
 * this software without specific prior written permission.\n\
 *\n\
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS\n\
 * \"AS IS\" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT\n\
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR\n\
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT\n\
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,\n\
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT\n\
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,\n\
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY\n\
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT\n\
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE\n\
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.\n\
 * \n\
 * Author - Andronicus \n\
 * Initial UpStream Program to do a basic operation on data\n\
 * Add and return value\n\
 * AutoGenerated File! \n\
 * \n\
 */\n\
#ifndef UPSTREAM_H\n\
#define UPSTREAM_H \n"


def create_mapping(file_name, num_lanes, mapbase, upbase, scratchsize):
    with open(file_name, 'w+') as f:
        f.write(preamble)
        str = "#define MAPBASE {} // MapBase\n".format(f'{mapbase:#x}')
        f.write(str)
        str = "#define UBASE {} //Upstream Base\n".format(f'{upbase:#x}')
        f.write(str)
        str = "#define SBASE {} //ScratchPad Base (Local)\n".format(f'{0:#x}')
        f.write(str)
        ebase = 65536*num_lanes
        str = "#define EBASE {} //Event Queue\n".format(f'{ebase:#x}')
        f.write(str)
        str = "#define OBASE {} //Operand Buffer Base \n".format(f'{ebase+256:#x}')
        f.write(str)
        str = "#define EXEC {} // Exec Addr\n".format(f'{ebase+512:#x}')
        f.write(str)
        str = "#define STATBASE {} //Status - Unused now\n".format(f'{ebase+768:#x}')
        f.write(str)
        str = "#define NUMLANES {} //NumLanes\n".format(f'{num_lanes}')
        f.write(str)
        str = "#define LMBANK_SIZE {} // LM Bank Size\n".format(f'{int((scratchsize-1024)/num_lanes):#d}')
        f.write(str)
        str = "#define LMBANK_SIZE_4B {} //Event Queue (Local)\n".format(f'{int((scratchsize-1024)/(4*num_lanes)):#d}')
        f.write(str)
        f.write("#endif\n")
        #define UBASE 0x200000000 // Starts at 8GB 
        #define SBASE 0x0 // UBASE + 0 - ScratchPad
        #define EBASE 0x400000 // Beyond the 4MB for scratchpad Size - num_lanes * 4K
        #define OBASE 0x400100 // 64*4 - 256B for EvQ
        #define EXEC 0x400200 // 64*4 - 256B for OpB
        #define STATBASE 0x400300 // 64*4 - 256B for Exec Start and then 256B for Status of lane (this is only for simulations)

if __name__ == "__main__":
    num_lanes = int(sys.argv[1])
    #file_name = sys.argv[1]
    lmbanksize = 65536
    UpMemorySize = lmbanksize*num_lanes+1024
    #8GB = 8589934592
    gb8 = 8589934592
    create_mapping("upstream.h",num_lanes, 0x80000000, gb8, UpMemorySize)
    #create_mapping(file_name, num_lanes, 0x80000000,8589934592)
