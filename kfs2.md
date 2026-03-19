# kfs2

## GDT (global descriptor table)
The Global Descriptor Table (GDT) is a binary data structure specific to the IA-32 and x86-64 architectures. It contains entries telling the **CPU** about **memory segments**. 

GDT is used to define memory segments and access permissions, like kernel vs user mode.

In our projct, GDT should contains entries below:
- **Kernel code**
- **Kernel data**
- **Kernel stack**
- **User code**
- **User data**
- **User stack**

*process memory layout used by operating systems (OS view)*


## Segment descriptor = GDT entry structure
A segment descriptor is a data structure used by the CPU (in x86 architecture) to describe a memory segment. It is 8 bytes (64 bits)

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
For all segment descriptor, we put `0x0`. WHY?

Let's see how segmentation works:
```
linear address = segment_base + offset
```

If we set:
```
base = 0
```

Then:
```
linear address = offset
```

Instead of using segments:

The OS uses paging (page tables) to:
- isolate processes
- protect memory
- map virtual → physical memory

Yes, all segments refer to the same space. We call it, **flat momery model**.

### Limit
A 20-bit value defining the address of the last accessible data. 

The length is one more than the value stored here. 

How exactly this should be interpreted depends on the Granularity bit of the segment descriptor.

#### In kfs2
For all segment descriptor, we put max value `0xFFFFFFFF`.

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
All descriptor:
```
G | DB | L | AVL
1   1    0   0

G = 1	Limit is scaled in 4 KiB blocks
DB = 1	32-bit segment
L = 0	Not 64-bit
AVL = 0	Unused
```

### All descriptor
With flat model:

| Index | Segment Name     | Base | Limit        | Access | Flags | DPL |
|-------|------------------|------|--------------|--------|-------|-----|
| 0x00  | Null Descriptor  | 0x0  | 0x0          | 0x00   | 0x0   | -   |
| 0x08  | Kernel Code      | 0x0  | 0xFFFFFFFF   | 0x9A   | 0xC   | 0   | 
| 0x10  | Kernel Data      | 0x0  | 0xFFFFFFFF   | 0x92   | 0xC   | 0   | 
| 0x18  | Kernel Stack     | 0x0  | 0xFFFFFFFF   | 0x92   | 0xC   | 0   | 
| 0x20  | User Code        | 0x0  | 0xFFFFFFFF   | 0xFA   | 0xC   | 3   | 
| 0x28  | User Data        | 0x0  | 0xFFFFFFFF   | 0xF2   | 0xC   | 3   | 
| 0x30  | User Stack       | 0x0  | 0xFFFFFFFF   | 0xF2   | 0xC   | 3   | 


If we use non-flat model, our segment descriptors would be like below:
| Index | Segment Name     | Base        | Limit        | Access | Flags | DPL | Size |
|-------|------------------|-------------|--------------|--------|-------|-----|------|
| 0x00  | Null Descriptor  | 0x0         | 0x0          | 0x00   | 0x0   | -   | 4MiB | 
| 0x08  | Kernel Code      | 0x00000000  | 0x003FFFFF   | 0x9A   | 0xC   | 0   | 4MiB | 
| 0x10  | Kernel Data      | 0x00400000  | 0x003FFFFF   | 0x92   | 0xC   | 0   | 4MiB | 
| 0x18  | Kernel Stack     | 0x00800000  | 0x001FFFFF   | 0x92   | 0xC   | 0   | 2MiB | 
| 0x20  | User Code        | 0x01000000  | 0x007FFFFF   | 0xFA   | 0xC   | 3   | 8MiB | 
| 0x28  | User Data        | 0x01800000  | 0x007FFFFF   | 0xF2   | 0xC   | 3   | 8MiB | 
| 0x30  | User Stack       | 0x02000000  | 0x001FFFFF   | 0xF2   | 0xC   | 3   | 2MiB | 
