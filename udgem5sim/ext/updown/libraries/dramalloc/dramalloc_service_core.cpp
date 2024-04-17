#include "dramalloc.hpp"
#include "networkid.h"
#include "operands.h"
#include "updown_config.h"
#include <cassert>
#include <cmath>
#include <cstddef>
#include <cstdio>
#include <iostream>
#include <limits>
#include <mutex>

namespace dramalloc
{

#ifdef FASTSIM
Allocator::Allocator(uint64_t nrNodes, uint64_t minSize, uint64_t sharedSegSize,
                     UpDown::ud_machine_t machineConfig,
                     UpDown::networkid_t nwid, UpDown::SimUDRuntime_t *runtime, std::mutex *rt_lock)
    : nrTotalNodes(nrNodes), minSize(minSize), nwid(nwid), runtime(runtime), rt_lock(rt_lock)
#else
Allocator::Allocator(uint64_t nrNodes, uint64_t minSize, uint64_t sharedSegSize,
                     UpDown::ud_machine_t machineConfig,
                     UpDown::networkid_t nwid, UpDown::UDRuntime_t *runtime, std::mutex *rt_lock)

    : nrTotalNodes(nrNodes), minSize(minSize), nwid(nwid), runtime(runtime), rt_lock(rt_lock)
#endif
{
    phyStart = reinterpret_cast<UpDown::word_t *>(
        machineConfig.MapMemBase +
        (machineConfig.MapMemSize / machineConfig.NumStacks));
    // phyStart = reinterpret_cast<UpDown::word_t *>(
    //     machineConfig.GMapMemBase +
    //     (machineConfig.GMapMemSize / (machineConfig.NumStacks * machineConfig.NumNodes * machineConfig.NumUDs)));


    UpDown::word_t *sharedSegEnd =
        phyStart + sharedSegSize / sizeof(UpDown::word_t);

    for (uint64_t idx = 0; idx < nrNodes; idx++) {
        this->nodeSharedSegments.push_back(
            std::move(std::vector<Block>({{phyStart, sharedSegEnd}})));
    }
    this->rt_lock->lock();
#ifdef FASTSIM

    this->virtStart = reinterpret_cast<UpDown::word_t *>(
        runtime->mm_malloc(sharedSegSize));
#else
    this->virtStart = reinterpret_cast<UpDown::word_t *>(
        runtime->mm_malloc_global(sharedSegSize));
#endif
    this->rt_lock->unlock();
    std::cout << "Allocator: After Lock." << std::endl;
    printf("Allocator: Virtual segment start: = %p (%ld)\n", this->virtStart, (uint64_t)this->virtStart);
    // std::cout << "Virtual segment start: " << this->virtStart << std::dec << this->virtStart<< std::endl;

    MemorySegment tempVirtSegment(std::move(std::vector<Block>(
        {{this->virtStart, reinterpret_cast<UpDown::word_t *>(
                               std::numeric_limits<UpDown::word_t>::max())}})));
    this->virtSegment = std::move(tempVirtSegment);
    // Initialize the first segment in all nodes
    // and use the first sizeof(DRAMRequest) bytes for DRAMalloc args
    this->args = reinterpret_cast<DRAMRequest *>(this->virtStart);
    this->args->allocArgs.size = nrTotalNodes * minSize;
    this->args->allocArgs.blockSize = minSize;
    this->args->allocArgs.nrNodes = nrTotalNodes;
    this->args->allocArgs.startNode = 0;
    // std::cout << "Before allocating ..." << std::endl;
    this->args = reinterpret_cast<DRAMRequest *>(allocateBlocks());
    assert(reinterpret_cast<UpDown::word_t *>(this->args) == this->virtStart);
    std::cout << "Allocator: Before the rtlock" << std::endl;
    this->rt_lock->lock();
    this->runtime->t2ud_memcpy(this->args, sizeof(UpDown::word_t *), this->nwid,
                               0);
    resetArgs();
    this->rt_lock->unlock();
    std::cout << "Allocator: After rtlock" << std::endl;
}

Allocator::Allocator(uint64_t nrNodes, uint64_t minSize, DRAMRequest *args)
    : nrTotalNodes(nrNodes), minSize(minSize), args(args), phyStart(0)
{
    UpDown::word_t *sharedSegStart = 0; // TODO: Get from GSM
    uint64_t sharedSegSize = 1 << 16;   // TODO: Get from GSM

    UpDown::word_t *sharedSegEnd =
        sharedSegStart + sharedSegSize / sizeof(UpDown::word_t);

    for (uint64_t idx = 0; idx < nrNodes; idx++) {
        this->nodeSharedSegments.push_back(
            std::move(std::vector<Block>({{sharedSegStart, sharedSegEnd}})));
    }

    this->virtStart =
        std::nullptr_t(); // TODO: Get virtual segment start from the GSM
    MemorySegment tempVirtSegment(std::move(std::vector<Block>(
        {{this->virtStart, reinterpret_cast<UpDown::word_t *>(
                               std::numeric_limits<UpDown::word_t>::max())}})));
    this->virtSegment = std::move(tempVirtSegment);
}

__attribute__ ((optimize("O0"))) void Allocator::run()
{
    while (args->reqType != DRAMallocRequestType::FINISH) {
        // std::cout << "Allocator(run): Looping:"<< this->args->reqType << std::endl;
        if (args->reqType == DRAMallocRequestType::ALLOCATE_MEMORY) {
            printf("Allocator(run): Current args: reqType=%ld, size=%ld, blockSize=%ld, nrNodes=%ld, startNode=%ld\n", args->reqType, args->allocArgs.size, args->allocArgs.blockSize, args->allocArgs.nrNodes, args->allocArgs.startNode);
            UpDown::word_t *addr = allocateBlocks();
            resetArgs();
            writeAllocationResponse(addr);
        } else if (args->reqType == DRAMallocRequestType::FREE_MEMORY) {
            freeBlocks();
            resetArgs();
            writeFreeResponse();
        }
    }
    // std::cout << "Allocator(run): Done." << std::endl;
}

std::optional<UpDown::word_t *> Allocator::executeCommand()
{
    if (args->reqType == DRAMallocRequestType::ALLOCATE_MEMORY) {
        UpDown::word_t *addr = allocateBlocks();
        return addr;
    }

    return {};
}

DRAMRequest *Allocator::getArgAddr() { return this->args; }

void Allocator::printMemoryState()
{
    uint64_t idx = 0;
    for (auto it = this->nodeSharedSegments.begin();
         it != this->nodeSharedSegments.end(); it++, idx++) {
        std::cout << "----------Node " << idx << "----------\n";

        std::cout << "Allocated: ";
        it->printAllocated();
        std::cout << std::endl;

        std::cout << "Available: ";
        it->printAvailable();
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

UpDown::word_t *Allocator::allocateBlocks()
{
    std::cout << "Allocator: Request detected, allocating blocks..." << std::endl;
    uint64_t size = args->allocArgs.blockSize;
    uint64_t startNode = args->allocArgs.startNode;
    uint64_t nrNodes = args->allocArgs.nrNodes;

    UpDown::word_t nrWords = size / sizeof(UpDown::word_t);
    UpDown::word_t *candidate =
        this->nodeSharedSegments[startNode].findCandidate(NULL, size);

    // std::cout << "Candidate: " << candidate << std::endl;
    uint64_t nid = startNode;
    Block requiredBlock = {candidate, candidate + nrWords};
    
    uint64_t globalCounter = 0;

    while (nid < startNode + nrNodes) {
        // printf("Allocator: Inside allocator loop(%ld): nid = %ld, startNode = %ld, nrNodes = %ld\n",globalCounter, nid, startNode, nrNodes);
        globalCounter++;
        uint64_t idx = nid % this->nodeSharedSegments.size();
        uint64_t nrWraps = nid / this->nrTotalNodes;

        Block wrappedBlock = {requiredBlock.start + nrWords * nrWraps,
                              requiredBlock.end + nrWords * nrWraps};
        if (!this->nodeSharedSegments[idx].isAvailable(wrappedBlock)) {
            candidate =
                this->nodeSharedSegments[idx].findCandidate(candidate, size);
            requiredBlock = {requiredBlock.end, requiredBlock.end + nrWords};
            nid = startNode;
            continue;
        }

        nid++;
    }

    std::vector<Block> allocatedBlocks;
    nid = startNode;
    while (nid < startNode + nrNodes) {
        uint64_t idx = nid % this->nodeSharedSegments.size();
        uint64_t nrWraps = nid / this->nrTotalNodes;
        Block wrappedBlock = {requiredBlock.start + nrWords * nrWraps,
                              requiredBlock.end + nrWords * nrWraps};

        if (allocatedBlocks.empty() || allocatedBlocks.back() != wrappedBlock) {
            allocatedBlocks.push_back(wrappedBlock);
        }

        this->nodeSharedSegments[idx].allocate(wrappedBlock);
        nid++;
    }

    UpDown::word_t *virtAddr =
        this->virtSegment.allocateFirstFit(size * nrNodes).start;

    virtAddr = std::nullptr_t();
    for (auto& block : allocatedBlocks) {
        // NOTE: This is a temporary hack to compute a pre-determined virtual
        // address
        uint64_t virtOffset =
            (nrTotalNodes * minSize *
             (reinterpret_cast<uint64_t>(block.start) -
              reinterpret_cast<uint64_t>(this->phyStart)) /
             minSize) +
            minSize * startNode;
        UpDown::word_t *currentAddr = virtOffset / sizeof(UpDown::word_t) + this->virtStart;

#ifndef DRY_RUN
        printf("Installing translation entry (virtual address: %p, "
                       "physical offset: %p) on UpDowns\n", currentAddr, block.start);
        // TODO: Replace with call to GSM when it is available
        installTranslationEntries(currentAddr, block.start, nrNodes);
#endif

        if (!virtAddr) {
            virtAddr = currentAddr;
        }
    }
    printf("Finish allocate memory (virtual address: %p, "
                    "physical offset: %p)\n", virtAddr, allocatedBlocks[0].start);
    return virtAddr;
}

void Allocator::installTranslationEntries(UpDown::word_t *virt,
                                          UpDown::word_t *phy,
                                          uint64_t nrNodes)
{
    std::cout << "args->allocArgs.blockSize: " << this->args->allocArgs.blockSize << std::endl;
    std::cout << "args->allocArgs.nrNodes: " << this->args->allocArgs.nrNodes << std::endl;
    uint64_t nrC = log2(this->args->allocArgs.blockSize);
    uint64_t nrB = log2(this->args->allocArgs.nrNodes);
    uint64_t nrF = 37 - nrC;
    uint64_t mask = 0 | (uint64_t(pow(2, nrF)) - 1) << (nrC + nrB) |
                    (uint64_t(pow(2, nrC)) - 1);
    uint64_t phyBase = reinterpret_cast<uint64_t>(phy) |
                       (this->args->allocArgs.startNode) << 37;
    std::cout << "swizzle mask = " << mask << std::endl;

    UpDown::word_t opsData[5];
    UpDown::operands_t ops(5, opsData);
    ops.set_operand(0, reinterpret_cast<UpDown::word_t>(virt));
    ops.set_operand(1, this->args->allocArgs.size);
    ops.set_operand(2, mask);
    ops.set_operand(3, phyBase);
#ifdef FASTSIM
    // If on fastsim, install local translation entry instead
    ops.set_operand(4, 0);
#else
    ops.set_operand(4, nrNodes);
#endif
    UpDown::event_t eventOps(500, nwid, UpDown::CREATE_THREAD, &ops);

    std::cout << "InstallTranslationEntries: Before Lock" << std::endl;
    this->rt_lock->lock();
    UpDown::word_t zeroVal = 0;
    runtime->t2ud_memcpy(&zeroVal, sizeof(UpDown::word_t), nwid, sizeof(UpDown::word_t));
    runtime->send_event(eventOps);
    runtime->start_exec(nwid);
    runtime->test_wait_addr(nwid, 0, -1);
    this->rt_lock->unlock();
    std::cout << "InstallTranslationEntries: After Lock" << std::endl;
}

void Allocator::writeAllocationResponse(UpDown::word_t *addr)
{
    UpDown::word_t opsData[2];
    UpDown::operands_t ops(2, opsData);
    ops.set_operand(0, reinterpret_cast<UpDown::word_t>(addr));
    ops.set_operand(1, 0); // temp fix: bogus data
    UpDown::event_t eventOps(this->args->returnEvent, this->args->networkId,
                             UpDown::CREATE_THREAD, &ops);
    std::cout << "WriteAllocationReponse: Before Lock." << std::endl;
    this->rt_lock->lock();
    runtime->send_event(eventOps);
    runtime->start_exec(this->args->networkId);
    this->rt_lock->unlock();
    std::cout << "WriteAllocationResponse: After Lock." << std::endl;
    // std::cout << "unlocking...\n";
}

bool Allocator::freeBlocks() { return true; }

void Allocator::writeFreeResponse() {}

void Allocator::resetArgs()
{
    this->args->freeArgs.address = 0;

    this->args->allocArgs.size = 0;
    this->args->allocArgs.blockSize = 0;
    this->args->allocArgs.nrNodes = 0;
    this->args->allocArgs.startNode = 0;

    this->args->reqType = DRAMallocRequestType::NO_REQUEST;
}

MemorySegment::MemorySegment(std::vector<Block> blks) : available(blks) {}

Block MemorySegment::allocateFirstFit(uint64_t size)
{
    uint64_t words = size / sizeof(UpDown::word_t);
    for (auto it = this->available.begin(); it != this->available.end(); it++) {
        if ((it->end - it->start) >= size) {
            Block retBlk = {it->start, it->start + words};
            this->allocated.push_back(retBlk);

            Block remaining = {it->start + words, it->end};
            if (remaining.end - remaining.start) {
                // If there is residual space then save
                // the remaining in the current block
                it->start = remaining.start;
                it->end = remaining.end;
            } else {
                // Otherwise, erase the current block
                this->available.erase(it);
            }

            break;
        }
    }

    // The caller should check for this invalid response
    return {0, 0};
}

bool MemorySegment::isAvailable(Block required)
{
    auto it = this->available.begin();
    while (it != this->available.end()) {
        if (it->start <= required.start && it->end >= required.end) {
            return true;
        }

        it++;
    }

    return false;
}

Block MemorySegment::allocate(Block required)
{
    std::vector<Block> temp;

    auto it = this->available.begin();
    while (it != this->available.end() &&
           !(it->start <= required.start && it->end >= required.end)) {
        temp.push_back(*it);

        it++;
    }

    Block left = {it->start, required.start};
    if (left.end - left.start) {
        temp.push_back(left);
    }
    Block right = {required.end, it->end};
    if (right.end - right.start) {
        temp.push_back(right);
    }
    it++;

    while (it != this->available.end()) {
        temp.push_back(*it);

        it++;
    }

    this->available = temp;
    this->allocated.push_back(required);

    return required;
}

UpDown::word_t *MemorySegment::findCandidate(UpDown::word_t *offset,
                                             uint64_t size)
{
    auto it = this->available.begin();
    while (it != this->available.end() && it->start < offset) {
        it++;
    }

    while (it != this->available.end()) {
        if (it->end - it->start > size) {
            return it->start;
        }

        it++;
    }

    // The caller should check for this incorrect return
    return std::nullptr_t();
}

void MemorySegment::printAllocated()
{
    if (this->allocated.empty()) {
        std::cout << "No allocations";
        return;
    }

    uint64_t idx = 0;
    for (; idx < this->allocated.size() - 1; idx++) {
        std::cout << "("
                  << reinterpret_cast<uint64_t>(this->allocated[idx].start)
                  << ", "
                  << reinterpret_cast<uint64_t>(this->allocated[idx].end)
                  << "), ";
    }
    std::cout << "(" << reinterpret_cast<uint64_t>(this->allocated[idx].start)
              << ", " << reinterpret_cast<uint64_t>(this->allocated[idx].end)
              << ")";
}

void MemorySegment::printAvailable()
{
    if (this->available.empty()) {
        std::cout << "No available";
        return;
    }

    uint64_t idx = 0;
    for (; idx < this->available.size() - 1; idx++) {
        std::cout << "("
                  << reinterpret_cast<uint64_t>(this->available[idx].start)
                  << ", "
                  << reinterpret_cast<uint64_t>(this->available[idx].end)
                  << "), ";
    }
    std::cout << "(" << reinterpret_cast<uint64_t>(this->available[idx].start)
              << ", " << reinterpret_cast<uint64_t>(this->available[idx].end)
              << ")";
}

} // namespace dramalloc
