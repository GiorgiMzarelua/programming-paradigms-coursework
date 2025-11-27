# Programming Paradigms Course - CS206004

This repository contains my coursework from the Programming Paradigms course (CS206004) at Free University of Tbilisi. The course explores different programming paradigms and their practical applications in solving computational problems.

## About the Course

Throughout this course, I worked with multiple programming paradigms and languages:

* **C Programming** - Low-level systems programming and memory management
* **C++ Programming** - Object-oriented design and generic programming
* **Scheme (Functional)** - Functional programming concepts and recursion
* **Python** - Dynamic programming and algorithm implementation

The curriculum also included theoretical coverage of concurrent programming patterns.

> **Note:** Assignments 5 and 6 were not assigned during the 2024-2025 academic year.

## Assignment Overview

| Assignment | Topic | Language | Core Concepts |
|:----------:|-------|:--------:|---------------|
| 1 | **Random Sentence Generator** | C++ | Context-free grammar parsing, recursive generation, dynamic memory |
| 2 | **Six Degrees** | C++ | Graph traversal (BFS), shortest path algorithms, file I/O |
| 3 | **Vector & HashSet Implementation** | C | Generic data structures, void pointers, hash functions |
| 4 | **RSS News Aggregator** | C | Network programming, XML parsing, search indexing |
| 7 | **Trilateration Algorithm** | Scheme | Functional paradigm, geometric calculations, immutability |
| 8 | **Sequence Alignment** | Python | Dynamic programming, bioinformatics, Needleman-Wunsch |

## Tech Stack

**Languages**
- C (C99 standard)
- C++ (C++11 features)
- Scheme (Kawa implementation)
- Python 3

**Development Tools**
- GNU Make for build automation
- GCC/G++ compilers
- Valgrind for memory debugging
- Standard Template Library (STL)

**External Libraries**
- libcurl for HTTP requests
- Standard C/C++ libraries

## Key Takeaways

Throughout these assignments, I developed skills in:

- Manual memory management and avoiding memory leaks
- Implementing generic data structures from scratch
- Working with different programming paradigms
- Applying classic algorithms (BFS, dynamic programming)
- Building practical applications (search engines, alignment tools)

## Running the Projects

Each assignment directory contains its own build configuration. To compile and run:

```bash
cd assn-0X  # Replace X with assignment number
make        # Build the project
# Run according to assignment-specific instructions

Refer to individual assignment directories for detailed build and usage instructions.

## Academic Info

- **Course Code:** CS206004
- **University:** Free University of Tbilisi
- **Year:** 2024-2025
- **Instructor:** Course lecturer at FreeUni

## Project Structure

programming-paradigms-coursework/
│
├── assn-01/          # Random Sentence Generator (C++)
├── assn-02/          # Six Degrees of Separation (C++)
├── assn-03/          # Custom Vector & HashSet (C)
├── assn-04/          # RSS News Search Engine (C)
├── assn-07/          # Trilateration Problem (Scheme)
└── assn-08/          # DNA Alignment Algorithm (Python)


