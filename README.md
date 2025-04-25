# SLIP - A stack based, self modifying eslonag

## The language:
### Instruction Set

| Opcode    | Value | Behavior                                     |
|-----------|-------|----------------------------------------------|
| `OP_NOP`  | 0     | No operation                                 |
| `OP_ADD`  | 1     | Pops `a`, `b` → pushes `a + b`               |
| `OP_SUB`  | 2     | Pops `a`, `b` → pushes `a - b`               |
| `OP_READ` | 3     | Blocking destructive read from stdin         |
| `OP_WRITE`| 4     | Peeks at the top of stack and writes it      |
| `OP_INT`  | 5     | Modifies code: pops `op` then `line`         |
| `OP_POP`  | 6     | Destroys the top of the stack                |
| `OP_PUSH` | 7     | Pushes argument (only instruction with args) |

### Example: Infinite 'A' Printer

```
NOP       ; [0] No-op (wastes a cycle)
PUSH -6   ; [1] INT jump offset (relative line jump from INT)
PUSH 0    ; [2] Opcode to write (NOP)
PUSH 65   ; [3] ASCII 'A'
WRITE     ; [4] Print
POP       ; [5] Discard the top of the stack (it will overflow sooner than the I/O buffer)
INT       ; [5] Overwrites the line 6 lines above with NOP, jumps there
```
Currently, to make a program you need to edit the *program* variable in slip.c - array of Instruction {count, OpCode, arg} - and recompile

## Compilation:
Compile using CMake:
```bash
git clone https://github.com/DFTHLM/slip.git
mkdir build && cd build/
CMake ..
make
```

## Roadmap
- [ ] Parse program from file
- [x] Dynamic program expansion for `INT`
- [x] Unified I/O system (shared buffer for READ/WRITE)
- [ ] Better error handling
- [ ] Example programs gallery
