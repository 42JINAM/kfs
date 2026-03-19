# kfs2

## GDT (global descriptor table)
A data structure used to define the different **memory areas**: 

the base address, the size and access privileges like execute and write.

These memory areas are called "**segments**".

- **Kernel code**, used to store the executable binary code
- **Kernel data**
- **Kernel stack**, used to store the call stack during kernel execution
- **User code**, used to store the executable binary code for user programs
- **User program data**
- **User stack**, used to store the call stack during execution in userland

*process memory layout used by operating systems (OS view)*


## Segment descriptor = GDT entry structure
A data structure used by the CPU (in x86 architecture) to describe a memory segment. It is 8 bytes (64 bits)

[check image](https://en.wikipedia.org/wiki/Segment_descriptor)

```
15                                                                0
+--------------------------------+--------------------------------+
|          Base 31:24            |      Flag     |   Limit 19:16  |
+--------------------------------+--------------------------------+
|          Access                |          Base 23:16            |
+--------------------------------+--------------------------------+
|                            Base 15:0                            |
+--------------------------------+--------------------------------+
|                            Limit 15:0                           |
+-----------------------------------------------------------------+
```

### Base
A 32-bit value containing the linear address where the segment begins.

#### In kfs2
- why all base is 0?
because OS uses 'flat memory model'



### Limit
A 20-bit value defining the address of the last accessible data. 

The length is one more than the value stored here. 

How exactly this should be interpreted depends on the Granularity bit of the segment descriptor.

#### In kfs2


### Acess
```
bit: 7  6  5  4  3  2  1  0
     P  DPL   S  E  DC RW A
```

| Bit | Name                         | Meaning |
|-----|------------------------------|--------|
| P   | Present                      | Indicates the segment is present in memory |
| DPL | Descriptor Privilege Level   | Privilege level (0 = kernel, 3 = user) |
| S   | Descriptor Type              | 1 = Code/Data segment, 0 = System segment |
| E   | Executable                   | 1 = Code segment, 0 = Data segment |
| DC  | Direction / Conforming       | Data: direction bit, Code: conforming bit |
| RW  | Readable / Writable          | Data: writable, Code: readable |
| A   | Accessed                     | Set by CPU when the segment is accessed |

#### In kfs2
```
P | DPL | S | E | DC | RW | A
1   00    1   0   0    1   0   ← kernel code (0x9A)
1   00    1   1   0    1   0   ← kernel data (0x92)
1   11    1   0   0    1   0   ← user code (0xFA)
1   11    1   1   0    1   0   ← user data (0xF2)
```
- E   → code vs data
- DPL → kernel(0) vs user(3)

### Flags
```
bit: 7  6   5  4
     G  DB  L  AVL
```
| Bit | Name                     | Meaning |
|-----|--------------------------|--------|
| G   | Granularity flag         | 0 = limit is 1 bytes block, 1 = limit is 4 KiB blocks |
| DB  | Default operation size   | 0 = 16-bit segment, 1 = 32-bit segment |
| L   | Long mode flag           | 0 = not 64-bit, 1 = 64-bit code segment |

#### In kfs2
