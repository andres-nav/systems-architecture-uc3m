# C Management Program

Multi-process form management system in C simulating bureaucratic workflow with automated rate calculations.

## Architecture

```
Box Officer (CLI) → Chief (Timestamps) → Admin (Calculations) → Form.txt
     Parent              Child 1              Child 2           Storage
```

Uses `fork()`, `wait()`, and file-based IPC for process communication.

## Form Types

| Code | Name | Fields |
|------|------|--------|
| **LS** | Individual License | Name, DNI, topic, item |
| **LC** | Company License | Company, CIF, topic, item |
| **DP** | Operations Declaration | Company, CIF, operations list |
| **DM** | Customer Declaration | Company, CIF, customers list |

## Rate System

**Base Rates**: Topic A (3.5%, 5.0%) | Topic B (7.5%, 10.0%)  
**Operation Multipliers**: Type 1 (1.5×), Type 2 (2.0×), Type 3 (2.5×)  
**Customer Multipliers**: Type 1 (15%), Type 2 (20%), Type 3 (25%)

## Quick Start

```bash
# Build
./Compile.sh

# Run
./P1

# Debug with Valgrind
./Compile.sh valgrind
valgrind --leak-check=full ./P1
```

## Project Structure

```
P1.c              # Entry point
Defines.h         # Constants and rates
Forms.h/c         # Data structures (LS/LC/DP/DM forms, linked lists)
Boxofficer.h/c    # CLI interface
Chief.h/c         # Timestamp manager
Admin.h/c         # Rate calculator
Heads.h/c         # File I/O
Tools.h/c         # Utilities
Compile.sh        # Build script (standard/debug/valgrind modes)
```

## Technical Features

- **Multi-process**: Parent-child hierarchy with `fork()` and `wait()`
- **IPC**: File-based communication via `Form.txt`
- **Data structures**: Union types, linked lists for operations/customers
- **Memory safe**: Valgrind-verified, no leaks
- **Signal handling**: SIGINT for graceful cleanup

## Example Calculation

**DP Form** (Operations Declaration):
```
Operation 1: $1000 × 3.5% × 2.0 = $70
Operation 2: $2000 × 10.0% × 2.5 = $500
Total: $3570
```

## Notes

- `Form.txt` is runtime-generated (excluded from git)
- All rates configurable in `Defines.h`
- Supports debug, standard, and valgrind build modes
