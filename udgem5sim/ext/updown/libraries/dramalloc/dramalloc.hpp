#include "networkid.h"
#include "updown.h"
#include <cstdint>
#include <cstdio>
#include <optional>
#include <updown.h>
#include <utility>
#include <vector>
#include <mutex>

#ifdef FASTSIM
#include <simupdown.h>
#elif ASST
#include <updown.h>
#else
#include <updown.h>
#include <gem5/m5ops.h>
#endif

#ifdef BASIM
#include <basimupdown.h>
#endif


#define PRINT_LOG_MESSAGE(level, message, ...)             \
    printf("[DRAMalloc_" level ":%s:%i] " message "\n",    \
           __FILENAME__, __LINE__, ##__VA_ARGS__);

// Enable info messages if debug is enabled
#ifdef LOG_DEBUG
#define LOG_INFO
#endif

#ifdef LOG_DEBUG
#define DRAMALLOC_DEBUG(message, ...)                      \
    PRINT_LOG_MESSAGE("DEBUG", message, ##__VA_ARGS__);
#else
#define DRAMALLOC_DEBUG(message, ...)
    // No-op
#endif

#ifdef LOG_INFO
#define DRAMALLOC_INFO(message, ...)                       \
    PRINT_LOG_MESSAGE("DEBUG", message, ##__VA_ARGS__);
#else
#define DRAMALLOC_INFO(message, ...)
    // No-op
#endif

namespace dramalloc
{

enum DRAMallocRequestType : UpDown::word_t {
    NO_REQUEST,
    ALLOCATE_MEMORY,
    FREE_MEMORY,
    FINISH
};

struct AllocationRequestArgs {
    UpDown::word_t size = 0;
    UpDown::word_t blockSize = 0;
    UpDown::word_t nrNodes = 0;
    UpDown::word_t startNode = 0;
};

struct FreeRequestArgs {
    UpDown::word_t address = 0;
};

struct DRAMRequest {
    DRAMallocRequestType reqType = NO_REQUEST;
    UpDown::word_t networkId = -1;
    UpDown::word_t returnEvent = -1;
    union {
        AllocationRequestArgs allocArgs;
        FreeRequestArgs freeArgs;
    };
};

struct Block {
    UpDown::word_t *start;
    UpDown::word_t *end;

    inline bool operator==(const Block& other) const {
        return (this->start == other.start && this->end == other.end);
    }

    inline bool operator!=(const Block& other) const {
        return !(*this == other);
    }
};

class MemorySegment
{
  public:
    MemorySegment() = default;
    MemorySegment(std::vector<Block> blks);
    ~MemorySegment() = default;

    Block allocateFirstFit(uint64_t size);

    bool isAvailable(Block required);
    Block allocate(Block required);
    UpDown::word_t *findCandidate(UpDown::word_t *offset, uint64_t size);

    void printAllocated();
    void printAvailable();

  private:
    std::vector<Block> available;
    std::vector<Block> allocated;
};

class Allocator
{
  public:
#ifdef FASTSIM
    Allocator(uint64_t nrNodes, uint64_t minSize, uint64_t sharedSegSize,
              UpDown::ud_machine_t machineConfig, UpDown::networkid_t nwid,
              UpDown::SimUDRuntime_t *runtime, std::mutex* rt_lock);
#else
    Allocator(uint64_t nrNodes, uint64_t minSize, uint64_t sharedSegSize,
              UpDown::ud_machine_t machineConfig, UpDown::networkid_t nwid,
              UpDown::UDRuntime_t *runtime, std::mutex* rt_lock);
#endif
    Allocator(uint64_t nrNodes, uint64_t minSize, DRAMRequest *args);

    void run();
    std::optional<UpDown::word_t *> executeCommand();
    DRAMRequest *getArgAddr();

    void printMemoryState();

  private:
#ifdef FASTSIM
    UpDown::SimUDRuntime_t *runtime;
    std::mutex *rt_lock;
#elif ASST
    UpDown::UDRuntime_t *runtime;
    std::mutex *rt_lock;
#else 
    UpDown::UDRuntime_t *runtime;
    std::mutex *rt_lock;
#endif 
    UpDown::networkid_t nwid;

    uint64_t nrTotalNodes;
    uint64_t minSize;
    DRAMRequest *args;
    std::vector<MemorySegment> nodeSharedSegments;
    MemorySegment virtSegment;
    UpDown::word_t *virtStart;
    UpDown::word_t *phyStart;
    

    UpDown::word_t *allocateBlocks();
    void installTranslationEntries(UpDown::word_t *virt, UpDown::word_t *phy, uint64_t nrNodes);
    void writeAllocationResponse(UpDown::word_t *addr);

    bool freeBlocks();
    void writeFreeResponse();

    void resetArgs();
};

inline uint64_t getNodeId(uint64_t id) { return (id >> 11) & 0xffff; }

}; // namespace dramalloc
