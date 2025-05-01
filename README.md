# SLIP - A stack based, self modifying eslonag

## What is it?
SLIP is a stack based esolang with a self-modifying instruction set. The language is inspired by the concept of self-modifying code, where the program can change its own instructions at runtime.

## The language:
### Instruction Set

| Opcode    | Value | Behavior                                                                             |
|-----------|-------|--------------------------------------------------------------------------------------|
| `OP_NOP`  | 0     | No operation                                                                         |
| `OP_ADD`  | 1     | Pops `a`, `b` → pushes `a + b`                                                       |
| `OP_SUB`  | 2     | Pops `a`, `b` → pushes `a - b`                                                       |
| `OP_READ` | 3     | Reads the I/O buffer                                                                 |
| `OP_WRITE`| 4     | Peeks at the top of stack and writes the corresponding ASCII character               |
| `OP_INT`  | 5     | Modifies code: pops `x` then `y` and writes instruction with value `x` `y` lines away|
| `OP_POP`  | 6     | Destroys the top of the stack                                                        |
| `OP_PUSH` | 7     | Pushes argument (only instruction with arguments, wiriting it using INT adds PUSH 0) |
| `OP_SWAP` | 8     | Swaps the 2 highest elements of the stack                                            |
| `OP_PRINT`| 9     | Peeks at the top of stack and prints the value as an integer                         |

PRINT, WRITE and READ all operate on the same I/O buffer, meaning READ can read values written by WRITE/PRINT and vice-versa.
PRINT and WRITE are the same, but PRINT will print the value as an integer, while WRITE will print the value as an ASCII character, both are non-destructive.
READ is destructive, meaning it will pop the value from the buffer, and if its empty it will wait for user input.
INT only jumps if the current top of stack is a valid instruction, otherwise it will act as a NOP.

### Example: Infinite (until overflow) 'A' Printer

```
NOP       ; [0] No-op (wastes a cycle)
PUSH -6   ; [1] INT jump offset (relative line jump from INT)
PUSH 0    ; [2] Opcode to write (NOP)
PUSH 65   ; [3] ASCII 'A'
WRITE     ; [4] Print
POP       ; [5] Discard the top of the stack (it will overflow sooner than the I/O buffer)
INT       ; [5] Overwrites the line 6 lines above with NOP, jumps there
```

## Compilation:
Compile using CMake:
```bash
git clone https://github.com/DFTHLM/slip.git
mkdir build && cd build/
CMake ..
make
# to test: make test
```

## Usage:
```bash
./slip <path/to/file.slip> [-(-d)ebug]
```

## Roadmap
- [ ] Unit tests (partially done so far)
- [x] Parse program from file
- [x] Dynamic program expansion for `INT`
- [x] Unified I/O system (shared buffer for READ/WRITE)
- [x] Better error handling
- [x] Example programs gallery
