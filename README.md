# Macro Assembler 

## Project Overview

This project implements a **Two-Pass Assembler** tailored for an 8085-like microprocessor assembly language. The assembler converts human-readable assembly code into machine code by processing the source code in two distinct passes:

- **Pass 1:** Scans the source code to identify labels, macros, and calculate addresses, building the symbol table and macro definitions without producing machine code.
- **Pass 2:** Expands macros, resolves symbolic addresses, generates the actual machine opcodes, and outputs the final machine code.

This approach mirrors real-world assembler designs, ensuring forward references (e.g., jumps to labels defined later) are correctly handled. The project also supports basic instructions, data directives (`DB`, `DW`), and macro facilities with parameters.

---

## Motivation

Assemblers are foundational tools in systems programming, bridging the gap between human-readable code and machine instructions. Implementing a two-pass assembler deepens understanding of compiler design principles, symbol resolution, and code generation.

Real-life assemblers rely on multiple passes to handle forward references and complex macros efficiently. This project simulates these core concepts, reinforcing practical compiler construction knowledge with hands-on coding in:

- **C** for core logic  
- **Assembler language** for instruction processing  
- **Lex & Yacc** for lexical analysis and parsing

Additionally, an optional web UI using HTML, CSS, and JavaScript facilitates interactive assembly code input and output display.

---

## Features

- **Macro Processing:** Define reusable code blocks with parameters, expanded in Pass 2  
- **Symbol Table Management:** Collects labels and their addresses, resolving forward references  
- **Two-Pass Architecture:**  
  - Pass 1: Scans, stores symbols and macros, calculates instruction addresses  
  - Pass 2: Expands macros, generates machine code, and resolves labels  
- **Instruction Support:** Includes common 8085 instructions like `MVI`, `MOV`, `ADD`, `INR`, `JMP`, `NOP`, `HLT`  
- **Data Directives:** Supports `DB` (Define Byte) and `DW` (Define Word)  
- **Output:** Generates hexadecimal machine code with memory addresses  
- **User Interface:** A simple, clean UI for code editing and output viewing (optional)

---

## Implementation Details

### Languages and Tools Used

- **C:** Core implementation of Pass 1 and Pass 2 logic  
- **8085 Assembly:** Used for low-level instruction processing and macros  
- **Lex (Flex):** Tokenizes assembly source code, macro keywords, labels, and instructions  
- **Yacc (Bison):** Parses tokenized input into syntax trees and handles grammar rules for macros and directives  
- **HTML/CSS/JavaScript:** Optional front-end UI to input assembly code and display machine code output dynamically  

### Pass 1: Symbol Table and Macro Storage

- Parses assembly lines sequentially  
- Identifies and stores label names with corresponding addresses in a symbol table  
- Detects macro definitions and stores their bodies without expansion  
- Calculates instruction sizes for address assignment without generating machine code  
- Builds a comprehensive macro table

### Pass 2: Macro Expansion and Machine Code Generation

- Processes the source code again, this time expanding macros inline where invoked  
- Converts mnemonics and operands into machine opcodes according to the 8085 instruction set  
- Resolves symbolic addresses in jump instructions using the symbol table  
- Handles data bytes and words as raw memory content  
- Outputs a hex dump with precise memory addresses for loading in an emulator or hardware  

---

## How to Use

1. **Prepare your assembly source code:** Use labels, macros, instructions, and data directives.  
2. **Run Pass 1:** Generate the symbol table and macro definitions, verifying no syntax errors.  
3. **Run Pass 2:** Expand macros and generate the final machine code output.  
4. **Review output:** The machine code hex dump with addresses can be loaded into an 8085 simulator or hardware.  
5. *(Optional)* Use the web UI to input your code and get real-time output visualization.

---

## Sample Input and Output

### Sample Assembly Input (snippet)

```asm
ORG 4000H
MACRO INCR_AND_ADD
    INR A
    MOV B, A
    ADD C
MEND

START:
    MVI A, 0AH
    INCR_AND_ADD
    JMP START


### Corresponding Machine Code Output (hex dump)

| Address | Machine Code | Description          |
|---------|--------------|----------------------|
| 4000    | 3E 0A        | MVI A, 0AH           |
| 4002    | 3C           | INR A                |
| 4003    | 47           | MOV B, A             |
| 4004    | 81           | ADD C                |
| 4005    | C3 00 40     | JMP 4000H (START)    |

---

### Project Structure

Macro Assembler/
│
├── src/
│   ├── pass1.c          # Pass 1 implementation: symbol table, macro recording
│   ├── pass2.c          # Pass 2 implementation: macro expansion, code generation
│   ├── lexer.l          # Lex specification for tokenizing assembly language
│   ├── parser.y         # Yacc grammar for parsing macros, instructions, labels
│   └── assembler.asm    # Sample assembly program with macros and labels
│
├── docs/
│   └── output_documentation.md  # Detailed machine code output and explanations
│
├── README.md            # Project documentation (this file)
├── LICENSE             # MIT License file


---

### Challenges Faced

- **Symbol resolution:** Handling forward references and backpatching required a robust symbol table with efficient lookups.  
- **Macro expansion:** Avoiding infinite macro expansion loops and handling parameters posed logical challenges.  
- **Multi-language integration:** Coordinating between C, assembler, Lex, and Yacc was tricky but rewarding — it gave great insight into compiler toolchains.  
- **Address calculation:** Ensuring accurate address assignments when macros expand to variable instruction counts took careful design.

---

### Future Work & Enhancements

- Support for conditional assembly directives (`IF`, `ELSE`, `ENDIF`).  
- Expand instruction set for other architectures beyond 8085.  
- Implement code optimization passes to reduce machine code size.  
- Integrate an assembler debugger with step-by-step macro expansion visualization.  
- Enhance the UI with syntax highlighting, error detection, and suggestions.

---

### License

This project is licensed under the [MIT License](LICENSE).

---

### Contact & Contribution

Created by Rahul, a passionate backend and systems developer focused on compiler design, AI/ML, and real-time data systems.

- **Email:** your.email@example.com  
- **GitHub:** [github.com/yourusername](https://github.com/yourusername)  

Contributions, bug reports, and feature requests are welcome! Feel free to fork and send pull requests.

---

### Final Words

This Two-Pass Assembler project is a deep dive into the guts of compiler design, blending theory with practical low-level programming. It’s a solid foundation for anyone looking to build or understand assemblers, linkers, or even full compilers. Ready to turn assembly instructions into machine code magic? Let’s get assembling! 🚀
