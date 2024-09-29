import tkinter as tk
from tkinter import messagebox

# Global Variables for CPU State
R0, R1, PC = 0, 0, 0
ZF, NF = 0, 0  # Zero and Negative flags
memory = [5, 10, 0, 0]  # Simple memory
program = []  # Program to be input through the GUI
current_instruction_type = "Unknown"  # Stores the type of the current instruction
instruction_cycles = 0  # Tracks cycles for the current instruction
instruction_number = 0  # Instruction number for display in GUI
total_cycles = 0  # Total cycles used so far
fetch_cycles = 0
decode_cycles = 0
execute_cycles = 0
mem_access_cycles = 0
write_back_cycles = 0

# Cycle times for different instruction types (in cycles)
cycle_times = {
    'FETCH': 1,
    'DECODE': 1,
    'EXECUTE': {
        'ADD': 1, 'SUB': 1, 'AND': 1, 'OR': 1, 'CMP': 1, 'MOV': 1,
        'MUL': 3, 'DIV': 3, 'MOD': 3,
    },
    'MEM_ACCESS': {
        'LOAD': 2, 'STORE': 2,
    },
    'WRITE_BACK': 1
}

# Classify instruction types
def classify_instruction(instruction):
    if instruction in ['ADD', 'SUB', 'MUL', 'DIV', 'MOD']:
        return 'Arithmetic'
    elif instruction in ['AND', 'OR', 'NOT', 'CMP', 'MOV']:
        return 'Logical'
    elif instruction in ['BRANCH_IF_ZERO', 'BRANCH_IF_NEG', 'BRANCH_IF_POS', 'JUMP']:
        return 'Branching'
    elif instruction in ['LOAD', 'STORE']:
        return 'Memory'
    return 'Unknown'

# Define the pipeline stages and cycle calculations
def fetch(PC):
    global fetch_cycles, total_cycles
    fetch_cycles = cycle_times['FETCH']
    total_cycles += fetch_cycles
    print(f"[DEBUG] Fetching instruction at PC={PC}: {program[PC]}, {fetch_cycles} cycle(s)")  # Debug print
    return program[PC]

def decode(instruction):
    global decode_cycles, total_cycles, current_instruction_type
    decode_cycles = cycle_times['DECODE']
    total_cycles += decode_cycles
    print(f"[DEBUG] Decoding instruction: {instruction}, {decode_cycles} cycle(s)")  # Debug print
    decoded_instr = instruction.replace(",", "").split()
    current_instruction_type = classify_instruction(decoded_instr[0])
    print(f"[DEBUG] Instruction Type: {current_instruction_type}")  # Show instruction type
    return decoded_instr

def execute(decoded_instr):
    global R0, R1, PC, ZF, NF, execute_cycles, total_cycles
    instruction = decoded_instr[0]
    execute_cycles = cycle_times['EXECUTE'].get(instruction, 1)  # Get execute time based on instruction
    total_cycles += execute_cycles
    print(f"[DEBUG] Executing instruction: {decoded_instr}, {execute_cycles} cycle(s)")  # Debug print

    if instruction == "LOAD":
        reg = decoded_instr[1]
        mem_loc = int(decoded_instr[2])
        if reg == "R0":
            R0 = memory[mem_loc]
        elif reg == "R1":
            R1 = memory[mem_loc]
        print(f"[DEBUG] After LOAD: R0={R0}, R1={R1}")  # Debug print
        
    elif instruction == "ADD":
        R0 += R1
        update_flags(R0)  # Update flags based on the result in R0
        print(f"[DEBUG] After ADD: R0={R0}, ZF={ZF}, NF={NF}")  # Debug print
        
    elif instruction == "SUB":
        R0 -= R1
        update_flags(R0)  # Update flags based on the result in R0
        print(f"[DEBUG] After SUB: R0={R0}, ZF={ZF}, NF={NF}")  # Debug print

    elif instruction == "MUL":
        R0 *= R1
        update_flags(R0)
        print(f"[DEBUG] After MUL: R0={R0}, ZF={ZF}, NF={NF}")  # Debug print
    
    elif instruction == "DIV":
        if R1 != 0:  # Avoid division by zero
            R0 //= R1
        else:
            print(f"[DEBUG] Division by zero error")  # Debug print
        update_flags(R0)
        print(f"[DEBUG] After DIV: R0={R0}, ZF={ZF}, NF={NF}")  # Debug print

    elif instruction == "MOD":
        if R1 != 0:
            R0 %= R1
        else:
            print(f"[DEBUG] Modulus by zero error")
        update_flags(R0)
        print(f"[DEBUG] After MOD: R0={R0}, ZF={ZF}, NF={NF}")  # Debug print
    
    elif instruction == "AND":
        R0 &= R1
        update_flags(R0)
        print(f"[DEBUG] After AND: R0={R0}, ZF={ZF}, NF={NF}")  # Debug print
    
    elif instruction == "OR":
        R0 |= R1
        update_flags(R0)
        print(f"[DEBUG] After OR: R0={R0}, ZF={ZF}, NF={NF}")  # Debug print
    
    elif instruction == "NOT":
        R0 = ~R0
        update_flags(R0)
        print(f"[DEBUG] After NOT: R0={R0}, ZF={ZF}, NF={NF}")  # Debug print

    elif instruction == "CMP":
        result = R0 - R1
        update_flags(result)
        print(f"[DEBUG] After CMP: ZF={ZF}, NF={NF}")  # Debug print

    elif instruction == "MOV":
        reg = decoded_instr[1]
        value = int(decoded_instr[2])
        if reg == "R0":
            R0 = value
        elif reg == "R1":
            R1 = value
        update_flags(R0)
        print(f"[DEBUG] After MOV: R0={R0}, R1={R1}")  # Debug print
    
    elif instruction == "STORE":
        memory[int(decoded_instr[2])] = R0
        print(f"[DEBUG] After STORE: Memory={memory}")  # Debug print

def memory_access(decoded_instr):
    global mem_access_cycles, total_cycles
    instruction = decoded_instr[0]
    mem_access_cycles = cycle_times['MEM_ACCESS'].get(instruction, 0)  # Memory access time
    total_cycles += mem_access_cycles
    print(f"[DEBUG] Memory access for {instruction}, {mem_access_cycles} cycle(s)")  # Debug print

def write_back():
    global write_back_cycles, total_cycles
    write_back_cycles = cycle_times['WRITE_BACK']
    total_cycles += write_back_cycles
    print(f"[DEBUG] Write back stage, {write_back_cycles} cycle(s)")  # Debug print

def update_flags(result):
    global ZF, NF
    ZF = 1 if result == 0 else 0  # Zero flag is 1 only if the result is zero
    NF = 1 if result < 0 else 0   # Negative flag is 1 if the result is negative
    print(f"[DEBUG] Flags updated: ZF={ZF}, NF={NF}")  # Debug print

def step_through_pipeline():
    global PC, instruction_cycles, instruction_number, fetch_cycles, decode_cycles, execute_cycles, mem_access_cycles, write_back_cycles
    if PC < len(program):
        instr = fetch(PC)
        decoded_instr = decode(instr)
        execute(decoded_instr)
        if current_instruction_type == 'Memory':
            memory_access(decoded_instr)
        write_back()
        instruction_number += 1  # Increment the instruction count
        PC += 1
        print(f"[DEBUG] PC after step: {PC}")  # Debug print
        update_GUI()
    else:
        messagebox.showinfo("Info", "Program has finished execution.")
        print(f"[DEBUG] Program finished")  # Debug print

def run_program_step():
    global PC, instruction_cycles, fetch_cycles, decode_cycles, execute_cycles, mem_access_cycles, write_back_cycles
    instruction_cycles = 0  # Reset cycle counter for each instruction
    fetch_cycles, decode_cycles, execute_cycles, mem_access_cycles, write_back_cycles = 0, 0, 0, 0, 0  # Reset individual cycles
    if PC < len(program):
        step_through_pipeline()
        root.after(500, run_program_step)  # Run the next step after 500 ms
    else:
        messagebox.showinfo("Info", "Program has finished execution.")
        print(f"[DEBUG] Program finished running")  # Debug print

def run_program():
    global PC, instruction_number, total_cycles
    PC = 0  # Reset the program counter
    instruction_number = 1  # Reset instruction number counter
    total_cycles = 0  # Reset total cycle counter
    print(f"[DEBUG] Running program, reset PC to {PC}")  # Debug print
    run_program_step()

# Enhanced update_GUI function to include cycle times
def update_GUI():
    register_text.set(f"R0: {R0}, R1: {R1}, PC: {PC}, ZF: {ZF}, NF={NF}")
    memory_text.set(f"Memory: {memory}")
    instruction_type_text.set(f"Instruction Type: {current_instruction_type}")
    instruction_cycle_text.set(f"Instruction #{instruction_number}: Fetch: {fetch_cycles} cycle(s), Decode: {decode_cycles} cycle(s), Execute: {execute_cycles} cycle(s), Mem Access: {mem_access_cycles} cycle(s), Write Back: {write_back_cycles} cycle(s)")
    total_cycle_text.set(f"Total Cycles So Far: {total_cycles}")

def load_program():
    global program, PC
    program = input_area.get("1.0", tk.END).strip().splitlines()
    PC = 0
    print(f"[DEBUG] Program loaded: {program}")  # Debug print
    update_GUI()

# GUI Setup
root = tk.Tk()
root.title("Enhanced CPU Simulator with Cycle Times")

# Input area for assembly code
input_label = tk.Label(root, text="Input Assembly Code:")
input_label.pack()

input_area = tk.Text(root, height=10, width=40)
input_area.pack()

# Button to load the program
load_button = tk.Button(root, text="Load Program", command=load_program)
load_button.pack()

# Register and memory display
register_text = tk.StringVar()
memory_text = tk.StringVar()
instruction_type_text = tk.StringVar()
instruction_cycle_text = tk.StringVar()
total_cycle_text = tk.StringVar()

register_label = tk.Label(root, textvariable=register_text)
register_label.pack()

memory_label = tk.Label(root, textvariable=memory_text)
memory_label.pack()

instruction_type_label = tk.Label(root, textvariable=instruction_type_text)
instruction_type_label.pack()

instruction_cycle_label = tk.Label(root, textvariable=instruction_cycle_text)
instruction_cycle_label.pack()

total_cycle_label = tk.Label(root, textvariable=total_cycle_text)
total_cycle_label.pack()

# Button to step through the program
step_button = tk.Button(root, text="Step", command=step_through_pipeline)
step_button.pack()

# Button to run the program to completion
run_button = tk.Button(root, text="Run", command=run_program)
run_button.pack()

# Initialize the GUI with default register/memory values
update_GUI()

# Start the GUI event loop
root.mainloop()
