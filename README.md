# SLIP - A stack based, self modifying eslonag

## The language:
### Instruction Set

| Opcode    | Value | Behavior                                     |
|-----------|-------|----------------------------------------------|
| `OP_NOP`  | 0     | No operation                                 |
| `OP_ADD`  | 1     | Pops `a`, `b` → pushes `a + b`               |
| `OP_SUB`  | 2     | Pops `a`, `b` → pushes `a - b`               |
| `OP_READ` | 3     | Blocking destructive read from stdin         |
| `OP_WRITE`| 4     | Peeks at the top os stack and writes it      |
| `OP_INT`  | 5     | Modifies code: pops `op` then `line`         |
| `OP_POP`  | 5     | Destroys the top of the stack                |
| `OP_PUSH` | 6     | Pushes argument (only instruction with args) |

### Example: Infinite 'A' Printer

```
NOP       ; [0] Placeholder
PUSH -5   ; [1] INT jump offset (relative line jump from INT)
PUSH 0    ; [2] Opcode to write (NOP)
PUSH 65   ; [3] ASCII 'A'
DUMP      ; [4] Print
INT       ; [5] Overwrites line 5 lines above with NOP, jumps there
```
(Currently, to make a file you need to edit the program variable in slip.c - array of Instruction {count, OpCode, arg} - and recompile)

## Compilation:
Link slip.c and stack.c, compile and run:
```bash
git clone https://github.com/DFTHLM/slip.git
cd slip
gcc slip.c stack.c -o slip
./slip
```

## Roadmap
- [ ] Parse program from file
- [ ] Dynamic program expansion for `INT`
- [x] Unified I/O system (shared buffer for READ/DUMP)
- [ ] Better error handling
- [ ] Example programs gallery
