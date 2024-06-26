from EFA_v2 import *
def hashl64_99():
    efa = EFA([])
    efa.code_level = "machine"
    state = State()
    efa.add_initId(state.state_id)
    efa.add_state(state)
    event_map = {
        "launch_events": 0,
    }
    tran0 = state.writeTransition("eventCarry", state, state, event_map['launch_events'])
# Input arguments: [-5921020506515227428, -4363980403698433885, 4810094760072811678, -6199034029488942416, 2305363648503426975, 4143449408892124360, -3777394337004169469, -4089302660072881941, 20, 3936067251307022858]
    tran0.writeAction("addi X7 X16 0")
    tran0.writeAction("movir X17 44500")
    tran0.writeAction("slorii X17 X17 12 1267")
    tran0.writeAction("slorii X17 X17 12 2145")
    tran0.writeAction("slorii X17 X17 12 1459")
    tran0.writeAction("slorii X17 X17 12 3292")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 50032")
    tran0.writeAction("slorii X17 X17 12 111")
    tran0.writeAction("slorii X17 X17 12 438")
    tran0.writeAction("slorii X17 X17 12 3232")
    tran0.writeAction("slorii X17 X17 12 163")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 17088")
    tran0.writeAction("slorii X17 X17 12 3643")
    tran0.writeAction("slorii X17 X17 12 774")
    tran0.writeAction("slorii X17 X17 12 441")
    tran0.writeAction("slorii X17 X17 12 1182")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 43512")
    tran0.writeAction("slorii X17 X17 12 2486")
    tran0.writeAction("slorii X17 X17 12 1249")
    tran0.writeAction("slorii X17 X17 12 3085")
    tran0.writeAction("slorii X17 X17 12 688")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 8190")
    tran0.writeAction("slorii X17 X17 12 1216")
    tran0.writeAction("slorii X17 X17 12 1571")
    tran0.writeAction("slorii X17 X17 12 594")
    tran0.writeAction("slorii X17 X17 12 3999")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 14720")
    tran0.writeAction("slorii X17 X17 12 2004")
    tran0.writeAction("slorii X17 X17 12 2257")
    tran0.writeAction("slorii X17 X17 12 3347")
    tran0.writeAction("slorii X17 X17 12 3272")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 52115")
    tran0.writeAction("slorii X17 X17 12 4093")
    tran0.writeAction("slorii X17 X17 12 3374")
    tran0.writeAction("slorii X17 X17 12 1205")
    tran0.writeAction("slorii X17 X17 12 1795")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X17 51007")
    tran0.writeAction("slorii X17 X17 12 3598")
    tran0.writeAction("slorii X17 X17 12 1423")
    tran0.writeAction("slorii X17 X17 12 1212")
    tran0.writeAction("slorii X17 X17 12 235")
    tran0.writeAction("movrl X17 0(X16) 1 8")
    tran0.writeAction("movir X18 20")
    tran0.writeAction("add X7 X18 X5")
    tran0.writeAction("movir X16 13983")
    tran0.writeAction("slorii X16 X16 12 2948")
    tran0.writeAction("slorii X16 X16 12 3990")
    tran0.writeAction("slorii X16 X16 12 832")
    tran0.writeAction("slorii X16 X16 12 2570")
    tran0.writeAction("hashl64 X16 X17")
    tran0.writeAction("yieldt")
    return efa
