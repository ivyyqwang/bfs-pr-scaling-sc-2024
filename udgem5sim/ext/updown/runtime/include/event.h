#pragma once
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <map>
#include <utility>

#include "debug.h"

#include "networkid.h"
#include "operands.h"

namespace UpDown {

/**
 * @brief Contains information of an )event in the UpDown
 *
 * This class constructs the information of the event word based on
 * each of its parameters. It also contains a pointer to the operands
 * that is used when sending the event
 *
 * @todo UpDown ID is not being used
 * @todo, event_t considers a 4 byte word size
 */
class event_t {
private:
  uint8_t ThreadId;      // Thread ID. CREATE_THREAD for any thread
  networkid_t NetworkId; // Thread ID. CREATE_THREAD for any thread
  uint32_t EventLabel;   // Number representing the event label
  uint8_t ThreadMode;

  operands_t *Operands; // Operands to be sent with this event

  word_t EventWord; // Concatenated event word that contains all the fields

public:
  /**
   * @brief Construct a new empty event object
   *
   */
  event_t()
      : ThreadId(0xFF), EventLabel(0), Operands(nullptr), ThreadMode(0),
        EventWord((((ThreadId << 24) & 0xff000000) | ((0 << 20) & 0xf00000) |
                   (EventLabel & 0xfffff)) &
                  0xffffffffffffffff) {
    UPDOWN_INFOMSG("Creating a new event label = %d, "
                   "thread_id = %d, num_operands = %d, ev_word = 0x%lX",
                   EventLabel, ThreadId, 0, EventWord);
  }

  /**
   * @brief Construct a new event_t object
   *
   * @param e_label Event label ID
   * @param nwid Network ID representing Lane, Updown, Node, etc
   * @param tid Thread ID
   * @param operands Pointer to operands. Must be pre-initialized
   */
  event_t(uint32_t e_label, networkid_t nwid, uint8_t tid = CREATE_THREAD,
          operands_t *operands = nullptr)
      : NetworkId(nwid), ThreadId(tid), EventLabel(e_label),
        Operands(operands) {
    ThreadMode = 0;
    assert(Operands->get_NumOperands() > 1 && "Num Operands > 2");
    EventWord = (NetworkId.get_NetworkId() & 0xffffffff);
    EventWord =
        ((EventWord << 32) & 0xffffffff00000000) |
        ((ThreadId << 24) & 0xff000000) | ((ThreadMode << 23) & 0x800000) |
        (((Operands != nullptr ? Operands->get_NumOperands() - 2 : 0) << 20) &
         0xf00000) |
        (EventLabel & 0xfffff);
    UPDOWN_INFOMSG("Creating a new event label = %d, network_id = %d, "
                   "thread_id = %d, num_operands = %d, ev_word = 0x%lx",
                   EventLabel, NetworkId.get_NetworkId(), ThreadId,
                   (Operands != nullptr) ? Operands->get_NumOperands() : 0,
                   EventWord);
  }

  /**
   * @brief Set the event word object with new values
   *
   * @param e_label the ID of the event in the updown
   * @param noperands the number of operands
   * @param lid Lane ID
   * @param tid Thread ID
   */
  void set_event(uint32_t e_label, networkid_t nwid,
                 uint8_t tid = CREATE_THREAD, operands_t *operands = nullptr) {
    EventLabel = e_label;
    NetworkId = nwid;
    ThreadId = tid;
    Operands = operands;
    ThreadMode = 0;
    assert(Operands->get_NumOperands() > 1 && "Num Operands > 2");
    EventWord =
        (((static_cast<uint64_t>(NetworkId.get_NetworkId()) << 32) &
          0xffffffff00000000) |
         ((ThreadId << 24) & 0xff000000) | ((ThreadMode << 23) & 0x0800000) |
         (((Operands != nullptr ? Operands->get_NumOperands() - 2 : 0) << 20) &
          0xf00000) |
         (EventLabel & 0xfffff));
    UPDOWN_INFOMSG("Setting the event word = %d, network_id = %d, "
                   "thread_id = %d, num_operands = %d, ev_word = 0x%lX",
                   EventLabel, NetworkId.get_NetworkId(), ThreadId,
                   (Operands != nullptr) ? Operands->get_NumOperands() : 0,
                   (unsigned long)EventWord);
  }

  word_t get_EventWord() { return EventWord; }
  operands_t *get_Operands() { return Operands; }
  void set_operands(operands_t *ops) { Operands = ops; }
  networkid_t get_NetworkId() { return NetworkId; }
  uint8_t get_ThreadId() { return ThreadId; }
  uint32_t get_EventLabel() { return EventLabel; }
  void set_EventLabel(uint32_t label) {
    EventLabel = label;
    EventWord =
        (EventWord & 0xFFFFFFFFFFF00000) | (EventLabel & 0xfffff);
  }

  uint8_t get_NumOperands() {
    return (Operands != nullptr) ? Operands->get_NumOperands() : 0;
  }

  uint8_t get_EncodedNumOperands() {
    return EventWord >> 20 & 0x7;
  }

  ptr_t get_OperandsData() {
    return (Operands != nullptr) ? Operands->get_Data() : nullptr;
  }
};

} // namespace UpDown
