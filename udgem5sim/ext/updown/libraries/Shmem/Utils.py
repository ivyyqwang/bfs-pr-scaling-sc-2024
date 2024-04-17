from typing import Any
import math
pmap = {
    'all-start': 0,
    'all-end': 1,
    'head-tail-starts': 2,
    'worker-starts': 3,
    'worker-read-ends': 4,
    'worker-write-starts': 5,
    'worker-write-ends': 6,
    'worker-ack-starts': 7,
    'worker-ends': 8,
    'worker-read-starts': 9,
    
    'all-message-sent': 10,
    'ubench-worker-ends': 2,
}

class Register:
    def __init__(self) -> None:
        self.reg = {}
        for i in range(16):
            self.reg[f'X{16+i}'] = None
    
    def __getitem__(self, key):
        r = None
        for k,v in self.reg.items():
            if v == key:
                r = k
                break
        if r is None:
            raise Exception(f"Register {key} is not initialized")
        return r

    def __str__(self) -> str:
        r = ""
        for k, v in self.reg.items():
            r += f"{k} -> {v}\n"
        return r
    
    def alloc(self, key):
        for k, v in self.reg.items():
            if k == key:
                raise Exception(f"Register {key} is already allocated")
            if v is None:
                self.reg[k] = key
                return k
        raise Exception("No free register")

    def free(self, key):
        for k, v in self.reg.items():
            if v == key:
                self.reg[k] = None
                return

    def freemany(self, keys):
        for key in keys:
            self.free(key)
        return

    def freeall(self):
        for k, v in self.reg.items():
            self.reg[k] = None
        return
  
  
class TwoWayDict(dict):
    def __init__(self):
        self._forward = {}
        self._backward = {}
    
    def __setitem__(self, key, value):
        if key in self._forward:
            raise Exception(f"Key {key} already exists")
        if value in self._backward:
            raise Exception(f"Value {value} already exists")
        self._forward[key] = value
        self._backward[value] = key
    
    def __getitem__(self, key):
        if key in self._forward:
            return self._forward[key]
        if key in self._backward:
            return self._backward[key]
        raise KeyError(key)
    
    def __delitem__(self, key):
        if key in self._forward:
            del self._backward[self._forward[key]]
            del self._forward[key]
        elif key in self._backward:
            del self._forward[self._backward[key]]
            del self._backward[key]
        else:
            raise KeyError(key)
    
    def __contains__(self, __key: object) -> bool:
        return __key in self._forward or __key in self._backward
    
    def __str__(self) -> str:
        r = "----------------REG MAP BEGIN----------------\n"
        for k, v in self._forward.items():
            r += f"                  {k} <-> {v}\n"
        # r += "\nBackward:\n"
        # for k, v in self._backward.items():
        #     r += f"{k} -> {v}\n"
        r += "----------------REG MAP END------------------\n"
        return r
    

class AdvancedRegisterOld():
    _reg_pool = []
    _all_regs = []
    _two_way_dict = TwoWayDict()
    for i in range(16):
        _reg_pool.append(f"X{i+16}")
        _all_regs.append(f"X{i+16}")
        
    def __init__(self, exclude=[]) -> None:
        for e in exclude:
            self._reg_pool.remove(e)
            self._all_regs.remove(e)


    def __setattr__(self, __name: str, __value: Any) -> None:
        print(self._reg_pool)
        if __name in self._two_way_dict:
            raise Exception(f"Register {__name} already exists")
        if __value == 'alloc':
            regx = self._reg_pool.pop(0)
            self.__dict__[__name] = regx
            self._two_way_dict[__name] = regx
        else:
            raise Exception(f"Invalid operadion {__value}, please use 'alloc'")
    
    
    def alloc(self, name) -> None:
        if name not in self.__dict__:
            try:
                xreg = self._reg_pool.pop(0)
                self.__setattr__(name, xreg)
                self._two_way_dict[name] = xreg
            except IndexError:
                raise Exception("No more registers available!")
        else:
            raise Exception(f"Register {name} already exists")
      
      
    def free(self, reg): 
        if isinstance(reg, list):
            for r in reg:
                self.free(r)
            return
        if reg in self._all_regs:
            # this is a register
            if reg in self._reg_pool:
                raise Exception(f"Register {reg} was not allocated!")
            else:
                found = False
                for k, v in self.__dict__.items():
                    if v == reg:
                        found = True
                        del self.__dict__[k]
                        break
                if not found:
                    raise Exception(f"Register {reg} was not allocated!")
                self._reg_pool.insert(0, reg)
        else:
            # this is a name
            if reg in self.__dict__:
                self._reg_pool.insert(0, self.__dict__[reg])
                del self.__dict__[reg]
            else:
                raise Exception(f"Register {reg} does not exist")
        del self._two_way_dict[reg]
    
    def freeall(self):
        to_del = []
        for k, v in self.__dict__.items():
            if k.startswith("_"):
                continue
            self._reg_pool.insert(0, v)
            to_del.append(k)
        for k in to_del:
            self.free(k)
        # for k in to_del:    
        #     del self.__dict__[k]
        #     del self._two_way_dict[k]
        # assert len(self._reg_pool) == len(self._all_regs)
        # for r in self._all_regs:
        #     assert r in self._reg_pool
            

    def __str__(self) -> str:
        r = ""
        # r +="reg_pool:" + self._reg_pool.__str__() + "\n"
        r += self._two_way_dict.__str__()
        return r
        
    def __repr__(self) -> str:
        return self.__str__()


class AdvancedRegister(dict):
      
    def __init__(self, exclude=[]) -> None:
        pass


    def __setattr__(self, __name: str, __value: Any) -> None:
        if __name in self:
            raise Exception(f"Register {__name} already exists")
        if __value != 'alloc':
            raise Exception(f"Invalid operation {__value}, please use 'alloc'")
        if '_reg_pool' not in self:
            self['_reg_pool'] = []
            self['_all_regs'] = []
            self['_two_way_dict'] = TwoWayDict()
            for i in range(16):
                self['_reg_pool'].append(f"X{i+16}")
                self['_all_regs'].append(f"X{i+16}")

        regx = self['_reg_pool'].pop(0)
        self[__name] = regx
        self['_two_way_dict'][__name] = regx
        # super().__setattr__(__name, regx)
    
    def __getattribute__(self, __name: str) -> Any:
        if __name in self:
            return self[__name]
            # raise Exception(f"Register {__name} does not exist")
        return super().__getattribute__(__name)
    
    
    def free(self, reg): 
        if isinstance(reg, list):
            for r in reg:
                self.free(r)
            return
        if reg in self['_all_regs']:
            # this is a register
            # print("reg:", reg, reg in self['_reg_pool'], self['_reg_pool'])
            if reg in self['_reg_pool']:
                raise Exception(f"Register {reg} was not allocated!")
            else:
                name = self['_two_way_dict'][reg]
                # self.__delattr__(name)
                del self[name]
                self['_reg_pool'].insert(0, reg)
                self['_reg_pool'].sort()
        else:
            # this is a name
            if reg in self:
                self['_reg_pool'].insert(0, self[reg])
                del self[reg]
                self['_reg_pool'].sort()

            else:
                raise Exception(f"Register {reg} does not exist")
        del self['_two_way_dict'][reg]
    

    def freeall(self):
        to_del = []
        for k, v in self.items():
            if k.startswith("_"):
                continue
            # self['_reg_pool'].insert(0, v)
            to_del.append(k)
        for k in to_del:
            self.free(k)
        assert len(self['_reg_pool']) == len(self['_all_regs'])
        

    def __str__(self) -> str:
        r = ""
        # r += self['_reg_pool'].__str__() + "\n"
        r += self['_two_way_dict'].__str__()
        return r
        
    def __repr__(self) -> str:
        return self.__str__()
    
    
    def get(self, key):
        if key in self['_two_way_dict']:
            return self['_two_way_dict'][key]
        else:
            print(self['_two_way_dict'])
            print("key:", key, "not found in regFile")
            return key
        

class RegPrinter:
    def __init__(self, regFile, name="UDSHMEM") -> None:
        self.regFile = regFile
        self.msg_level_map={}
        self.name = name
        
    def set_all_level(self, level):
        for k in self.msg_level_map:
            self.msg_level_map[k] = level
    
    def get_level(self, msg):
        if msg in self.msg_level_map:
            return self.msg_level_map[msg]
        else:
            return 1
          
    def disable(self):
        for k in self.msg_level_map:
            self.msg_level_map[k] = math.inf
            
    def printr(self, msg, regs, level=1):
        rss = f"print '[{self.name}][NWID=%lu]: "
        rss += msg + ", "
        for r in regs:
            if isinstance(r, tuple):
                name = r[0]
            else:
                name = self.regFile.get(r)
            UNAME = name.upper()
            if 'SRC' in UNAME or 'DST' in UNAME or 'LMBASE' in UNAME or 'PTR' in UNAME:
                rss += f"{name}=%p(%lu), "
            elif UNAME.startswith('X'):
                rss += f"{name.replace('X', 'operand')}=%lu, "
            elif 'DIFF' in UNAME or 'NCHUNKS' in UNAME or 'NLEFT' in UNAME or 'NHEADS' in UNAME or 'NTAILS' in UNAME:
                rss += f"{name}=%ld, "
            elif 'BIT' in UNAME:
                rss += f"{name}=%p, "
            else:
                if isinstance(r, tuple):
                    rss += f"{name}=%lu, "
                else:
                    rss += f"{self.regFile.get(r)}=%lu, " 
        rss += "'"
        rss += " NWID"
        for r in regs:
            if isinstance(r, tuple):
                name = r[0]
                r = r[1]
            else:
                name = self.regFile.get(r)
            UNAME = name.upper()
            
            if 'SRC' in UNAME or 'DST' in UNAME or 'LMBASE' in UNAME or 'PTR' in UNAME:
                rss += " " +  r 
            rss += " " + r
        self.msg_level_map[rss] = level
        return rss
    
    def perflogr(self, msgid, msg, regs, level=1):
        rss = f"perflog 1 {msgid} 'NWID=%lu: "
        rss += msg + ","
        for r in regs:
            if isinstance(r, tuple):
                name = r[0]
            else:
                name = self.regFile.get(r)
            UNAME = name.upper()
            if 'SRC' in UNAME or 'DST' in UNAME or 'LMBASE' in UNAME:
                rss += f"{name}=%p(%lu), "
            elif UNAME.startswith('X'):
                rss += f"{name.replace('X', 'operand')}=%lu, "
            elif 'DIFF' in UNAME or 'NCHUNKS' in UNAME or 'NLEFT' in UNAME:
                rss += f"{name}=%ld, "
            else:
                if isinstance(r, tuple):
                    rss += f"{name}=%lu, "
                else:
                    rss += f"{self.regFile.get(r)}=%lu, " 
        rss += "'"
        rss += " NWID"
        for r in regs:
            if isinstance(r, tuple):
                name = r[0]
                r = r[1]
            else:
                name = self.regFile.get(r)
            UNAME = name.upper()
            
            if 'SRC' in UNAME or 'DST' in UNAME or 'LMBASE' in UNAME:
                rss += " " +  r 
            rss += " " + r
        self.msg_level_map[rss] = level
        return rss


class PrinterBlob:
    def __init__(self, msg, level) -> None:
        self.msg = msg
        self.level = level
    def getLevel(self):
        return self.level


class EventMap:
    def __init__(self, start=0, linker=False) -> None:
        self.event_map = {}
        self.last = start
        self.linker = linker
       
    def add_event(self, key):
        if self.linker:
            self.event_map[key] = key
        else:
            self.event_map[key] = self.last
        # print(f"event {key} is mapped to {self.last}")
        self.last += 1

    def __sizeof__(self) -> int:
        return self.last
    
    def __getitem__(self, key):
        if self.linker:
            return key
        else:
            # print(f"key {key} is mapped to {self.event_map[key]}")
            return self.event_map[key]
    def __str__(self) -> str:
        r = ""
        for k, v in self.event_map.items():
            r += f"{k} -> {v}\n"
        return r    
 
      
def appendTransActions(tran, actions):
    for action in actions:
        tran.writeAction(action)