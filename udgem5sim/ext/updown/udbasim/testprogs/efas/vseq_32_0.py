from EFA_v2 import *
def vseq_32_0():
    efa = EFA([])
    efa.code_level = "machine"
    state = State()
    efa.add_initId(state.state_id)
    efa.add_state(state)
    event_map = {
        "launch_events": 0,
    }
    tran0 = state.writeTransition("eventCarry", state, state, event_map['launch_events'])
# Input arguments: [1523300707, 1213072093, 290381687, 1142563087, 1670776870, 4168314076, 3253602391, 499207373, 4091307253, 4019894405, 3577965663, 1548142683, 3911714747, 885094305, 1627798387, 347121409, [7, 0, 0, 0, '16.0', 1], [7, 1, 1, 1, '3.0', 2], [7, 2, 2, 2, '11.75', 3], [7, 3, 3, 3, '8.5', 2], [7, 4, 4, 4, '6.5', 3], [7, 5, 5, 5, '15.5', 2], [7, 6, 6, 6, '2.5', 2], [7, 7, 7, 7, '9.375', 3], [4, 5, 6, 7, '20.0', 2], [6, 1, 2, 3, '20.875', 2], [7, 5, 5, 7, '6.5', 2], [0, 2, 6, 6, '14.125', 2], [3, 2, 6, 1, '18.0', 2], [7, 6, 5, 3, '18.625', 3], [3, 5, 5, 7, '9.25', 2], [3, 3, 2, 7, '12.25', 3], [0, 1, 4, 2, '0.125', 2], [3, 7, 5, 7, '13.375', 3], [2, 7, 6, 4, '9.0', 3], [2, 5, 2, 4, '7.25', 2], [2, 6, 2, 1, '5.375', 2], [3, 2, 4, 5, '9.75', 2], [2, 2, 3, 3, '14.375', 1], [2, 1, 2, 3, '15.0', 3], [0, 2, 3, 4, '19.125', 1], [7, 3, 3, 5, '3.5', 2], [3, 1, 3, 7, '19.0', 1], [1, 6, 4, 4, '0.375', 3], [2, 6, 5, 3, '1.625', 3], [7, 3, 1, 2, '8.125', 2], [1, 3, 5, 5, '8.75', 1], [0, 4, 2, 4, '9.625', 3], [1, 1, 1, 1, '14.875', 3], [3, 5, 5, 7, '18.875', 2], [7, 3, 3, 6, '11.875', 3], [7, 2, 6, 2, '2.25', 3], [7, 4, 5, 2, '15.625', 3], [0, 4, 7, 2, '20.875', 1], [3, 1, 7, 5, '13.25', 3], [5, 3, 4, 5, '7.25', 1]]
    tran0.writeAction("movir X16 0")
    tran0.writeAction("slorii X16 X16 12 1156")
    tran0.writeAction("slorii X16 X16 12 3586")
    tran0.writeAction("slorii X16 X16 8 221")
    tran0.writeAction("slorii X16 X16 12 1452")
    tran0.writeAction("slorii X16 X16 12 3001")
    tran0.writeAction("slorii X16 X16 8 99")
    tran0.writeAction("movir X17 0")
    tran0.writeAction("slorii X17 X17 12 1089")
    tran0.writeAction("slorii X17 X17 12 2593")
    tran0.writeAction("slorii X17 X17 8 15")
    tran0.writeAction("slorii X17 X17 12 276")
    tran0.writeAction("slorii X17 X17 12 3807")
    tran0.writeAction("slorii X17 X17 8 119")
    tran0.writeAction("movir X18 0")
    tran0.writeAction("slorii X18 X18 12 3975")
    tran0.writeAction("slorii X18 X18 12 876")
    tran0.writeAction("slorii X18 X18 8 220")
    tran0.writeAction("slorii X18 X18 12 1593")
    tran0.writeAction("slorii X18 X18 12 1544")
    tran0.writeAction("slorii X18 X18 8 38")
    tran0.writeAction("movir X19 0")
    tran0.writeAction("slorii X19 X19 12 476")
    tran0.writeAction("slorii X19 X19 12 332")
    tran0.writeAction("slorii X19 X19 8 205")
    tran0.writeAction("slorii X19 X19 12 3102")
    tran0.writeAction("slorii X19 X19 12 3592")
    tran0.writeAction("slorii X19 X19 8 87")
    tran0.writeAction("movir X20 0")
    tran0.writeAction("slorii X20 X20 12 3833")
    tran0.writeAction("slorii X20 X20 12 2744")
    tran0.writeAction("slorii X20 X20 8 133")
    tran0.writeAction("slorii X20 X20 12 3901")
    tran0.writeAction("slorii X20 X20 12 3172")
    tran0.writeAction("slorii X20 X20 8 245")
    tran0.writeAction("movir X21 0")
    tran0.writeAction("slorii X21 X21 12 1476")
    tran0.writeAction("slorii X21 X21 12 1736")
    tran0.writeAction("slorii X21 X21 8 91")
    tran0.writeAction("slorii X21 X21 12 3412")
    tran0.writeAction("slorii X21 X21 12 876")
    tran0.writeAction("slorii X21 X21 8 95")
    tran0.writeAction("movir X22 0")
    tran0.writeAction("slorii X22 X22 12 844")
    tran0.writeAction("slorii X22 X22 12 375")
    tran0.writeAction("slorii X22 X22 8 161")
    tran0.writeAction("slorii X22 X22 12 3730")
    tran0.writeAction("slorii X22 X22 12 2055")
    tran0.writeAction("slorii X22 X22 8 187")
    tran0.writeAction("movir X23 0")
    tran0.writeAction("slorii X23 X23 12 331")
    tran0.writeAction("slorii X23 X23 12 167")
    tran0.writeAction("slorii X23 X23 8 1")
    tran0.writeAction("slorii X23 X23 12 1552")
    tran0.writeAction("slorii X23 X23 12 1595")
    tran0.writeAction("slorii X23 X23 8 115")
    tran0.writeAction("vfill.32 X16 16.0")
    tran0.writeAction("vfill.32 X17 3.0")
    tran0.writeAction("vfill.32 X18 11.75")
    tran0.writeAction("vfill.32 X19 8.5")
    tran0.writeAction("vfill.32 X20 6.5")
    tran0.writeAction("vfill.32 X21 15.5")
    tran0.writeAction("vfill.32 X22 2.5")
    tran0.writeAction("vfill.32 X23 9.375")
    tran0.writeAction("vdiv.32 X21 X22 X23 2")
    tran0.writeAction("vgt.32 X17 X18 X19 2")
    tran0.writeAction("vfill.32 X23 6.5")
    tran0.writeAction("vmadd.32 X18 X22 X22 2")
    tran0.writeAction("vmul.32 X18 X22 X17 2")
    tran0.writeAction("vfill.32 X19 18.625")
    tran0.writeAction("vmul.32 X21 X21 X23 2")
    tran0.writeAction("vmul.32 X19 X18 X23 3")
    tran0.writeAction("vmadd.32 X17 X20 X18 2")
    tran0.writeAction("vmul.32 X23 X21 X23 3")
    tran0.writeAction("vsub.32 X23 X22 X20 3")
    tran0.writeAction("vsub.32 X21 X18 X20 2")
    tran0.writeAction("vsub.32 X22 X18 X17 2")
    tran0.writeAction("vmul.32 X18 X20 X21 2")
    tran0.writeAction("vsub.32 X18 X19 X19 1")
    tran0.writeAction("vsub.32 X17 X18 X19 3")
    tran0.writeAction("vmadd.32 X18 X19 X20 1")
    tran0.writeAction("vfill.32 X21 3.5")
    tran0.writeAction("vmul.32 X17 X19 X23 1")
    tran0.writeAction("vadd.32 X22 X20 X20 3")
    tran0.writeAction("vsub.32 X22 X21 X19 3")
    tran0.writeAction("vfill.32 X18 8.125")
    tran0.writeAction("vadd.32 X19 X21 X21 1")
    tran0.writeAction("vmadd.32 X20 X18 X20 3")
    tran0.writeAction("vadd.32 X17 X17 X17 3")
    tran0.writeAction("vmul.32 X21 X21 X23 2")
    tran0.writeAction("vfill.32 X22 11.875")
    tran0.writeAction("vfill.32 X18 2.25")
    tran0.writeAction("vfill.32 X18 15.625")
    tran0.writeAction("vmadd.32 X20 X23 X18 1")
    tran0.writeAction("vmul.32 X17 X23 X21 3")
    tran0.writeAction("vsqrt.32 X19 X21 1")
    tran0.writeAction("yieldt")
    return efa