# CPU Simulator with Pipeline Phases and Cycle Tracking

This is a simple **CPU simulator** built using Python and Tkinter for the GUI, simulating the **5 stages** of an instruction pipeline: **Fetch (IF)**, **Decode (ID)**, **Execute (EX)**, **Memory Access (MEM)**, and **Write Back (WB)**. The simulator tracks the number of CPU cycles consumed during the execution of each instruction, breaking down each phase individually.

## Features:
- Supports arithmetic, logical, memory, and branching instructions.
- Tracks the cycles for each pipeline phase for every instruction.
- Displays the total cycles consumed so far during program execution.
- Simulates basic instructions such as `MOV`, `ADD`, `MUL`, `LOAD`, `STORE`, etc.

## Instructions Used:

### Arithmetic Instructions:
- `ADD R0, R1` – Adds the contents of `R1` to `R0`.
- `SUB R0, R1` – Subtracts the contents of `R1` from `R0`.
- `MUL R0, R1` – Multiplies `R0` by `R1`.
- `DIV R0, R1` – Divides `R0` by `R1`.
- `MOD R0, R1` – Computes the modulus of `R0` divided by `R1`.

### Logical Instructions:
- `AND R0, R1` – Bitwise AND of `R0` and `R1`.
- `OR R0, R1` – Bitwise OR of `R0` and `R1`.
- `NOT R0` – Bitwise NOT of `R0`.
- `CMP R0, R1` – Compares `R0` and `R1` and sets the flags (ZF, NF).
- `MOV R0, imm` – Moves an immediate value into `R0` or `R1`.

### Memory Instructions:
- `LOAD R0, mem_addr` – Loads the value from memory address into `R0`.
- `STORE R0, mem_addr` – Stores the value of `R0` into the specified memory address.

### Branching Instructions:
- `BRANCH_IF_ZERO addr` – Jumps to `addr` if the zero flag (ZF) is set.
- `BRANCH_IF_NEG addr` – Jumps to `addr` if the negative flag (NF) is set.
- `BRANCH_IF_POS addr` – Jumps to `addr` if the result is positive.
- `JUMP addr` – Jumps unconditionally to the instruction at `addr`.

## Pipeline Phases:
Each instruction goes through the following five phases:

1. **Fetch (IF)** – The instruction is fetched from memory (1 cycle).
2. **Decode (ID)** – The instruction is decoded to determine the operation and operands (1 cycle).
3. **Execute (EX)** – The operation is executed (variable cycles depending on the instruction).
4. **Memory Access (MEM)** – For memory operations like `LOAD` or `STORE`, memory is accessed (2 cycles for these instructions).
5. **Write Back (WB)** – The result is written back to the destination register (1 cycle).

## Cycle Time Breakdown:
| Phase           | Cycle Time | Description                                                                 |
|-----------------|------------|-----------------------------------------------------------------------------|
| Fetch (IF)      | 1 cycle    | Fetches the instruction from memory.                                         |
| Decode (ID)     | 1 cycle    | Decodes the instruction to determine the operation and operands.             |
| Execute (EX)    | Varies     | Arithmetic and logical operations take 1-3 cycles depending on the instruction. |
| Memory Access (MEM) | 2 cycles | Memory instructions (`LOAD` and `STORE`) take 2 cycles for memory access.     |
| Write Back (WB) | 1 cycle    | Writes the result back to the destination register.                          |

### Execution Times for `Execute (EX)` Phase:
- **Arithmetic Instructions** (`ADD`, `SUB`, `AND`, `OR`, `CMP`, `MOV`): 1 cycle.
- **Multiplication/Division/Modulus** (`MUL`, `DIV`, `MOD`): 3 cycles.
- **Memory Instructions** (`LOAD`, `STORE`): 2 cycles for memory access plus 1 cycle for execution.

## Running the Project:

### Prerequisites:
Ensure you have **Python 3** installed on your machine. The code uses **Tkinter** for the GUI, which is bundled with most Python installations.

### How to Run:
1. Clone or download the repository.
2. Ensure you are in the directory where the `index.py` file is located.
3. Run the following command to start the simulator:

### Example program you can execute
1. MOV R0, 20        
2. MOV R1, 4         
3. DIV R0, R1         
4. CMP R0, R1        
5. SUB R0, R1         
6. STORE R0, 2     
7. JUMP 0            



```bash
python3 index.py
