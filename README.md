# Stack & Queues Project  
### Data Structures Implementation and Application in C / C++

---

## 1. Overview

This project implements core **data structures** — **Stack** and **Queue** — in a structured, modular, and testable way.  
The goal is to demonstrate fundamental data structure design, memory management, and algorithmic applications using low-level programming concepts (pointers, arrays, and dynamic memory).

It serves as a complete educational project to understand:
- The internal working of stacks and queues.
- Differences between static and dynamic memory approaches.
- Algorithmic use cases such as **expression evaluation**, **BFS traversal**, and **syntax checking**.

---

## 2. Objectives

- Implement stack and queue using **both arrays** and **linked lists**.  
- Demonstrate the use of stack and queue in multiple applications.  
- Explore time and space complexity analysis.  
- Provide reusable, modular, and well-documented source code.  
- Handle all error cases (underflow, overflow, invalid input).

---

## 3. Project Structure

```
Stack-Queues-Project/
│
├── src/
│   ├── stack_array.c / .cpp      # Array-based stack
│   ├── stack_linked.c / .cpp     # Linked-list stack
│   ├── queue_array.c / .cpp      # Array-based circular queue
│   ├── queue_linked.c / .cpp     # Linked-list queue
│   ├── utils.c / .cpp            # Helper utilities (I/O, validation)
│   └── main.c / main.cpp         # Driver program with test menu
│
├── include/
│   ├── stack.h
│   ├── queue.h
│   └── utils.h
│
├── tests/
│   ├── test_stack.txt
│   ├── test_queue.txt
│   └── run_tests.sh
│
├── input.txt                     # Example input
├── output.txt                    # Example output
├── CMakeLists.txt or Makefile    # Build system
└── README.md
```

---

## 4. Implementation Details

### 4.1 Stack

- **Array-Based Stack**
  - Uses fixed-size or resizable array.
  - Implements functions: `push()`, `pop()`, `peek()`, `isEmpty()`, `isFull()`.
  - Error messages for overflow and underflow.
  - Amortized O(1) push/pop.

- **Linked-List Stack**
  - Dynamic memory allocation.
  - Push and pop occur at the head node.
  - Ideal for unknown or variable-size datasets.

### 4.2 Queue

- **Array-Based Circular Queue**
  - Uses head and tail pointers modulo array size.
  - Efficient O(1) enqueue and dequeue operations.

- **Linked-List Queue**
  - Maintains head and tail pointers.
  - Grows dynamically without fixed size.

### 4.3 Example Applications

- **Expression Evaluation (Infix → Postfix)** using a stack.
- **Parentheses Matching** for syntax validation.
- **Breadth-First Search (BFS)** for graph traversal using queue.

---

## 5. Algorithmic Complexity

| Operation        | Stack (Array) | Stack (Linked) | Queue (Array) | Queue (Linked) |
|------------------|---------------|----------------|----------------|----------------|
| Push / Enqueue   | O(1)*         | O(1)           | O(1)           | O(1)           |
| Pop / Dequeue    | O(1)          | O(1)           | O(1)           | O(1)           |
| Peek / Front     | O(1)          | O(1)           | O(1)           | O(1)           |
| Memory Use       | Fixed         | Dynamic        | Fixed          | Dynamic        |
| Resize Cost      | Amortized O(n)| None           | O(n) optional  | None           |

*O(1) amortized with dynamic resizing.

---

## 6. Building the Project

### Using Makefile
```
make
```

### Using CMake
```
mkdir build
cd build
cmake ..
make
```

### Run the Application
```
./stack_queue_app input.txt output.txt
```

---

## 7. Input / Output Example

### Input (input.txt)
```
PUSH 10
PUSH 20
POP
PUSH 5
PUSH 7
POP
PUSH 30
PEEK
ENQUEUE 1
ENQUEUE 2
DEQUEUE
```

### Output (output.txt)
```
20 popped from stack
7 popped from stack
Top of stack is 30
1 dequeued from queue
```

---

## 8. Error Handling

- Underflow: Prevent operations on empty stack/queue.
- Overflow: Detect when array-based implementations exceed capacity.
- Invalid input commands are ignored with warnings.
- Memory allocation errors handled gracefully.

---

## 9. Testing

### Automated Testing
Run shell script:
```
./tests/run_tests.sh
```

### Manual Testing
Edit `input.txt` with different commands and rerun `main`.

---

## 10. Educational Focus

This project reinforces:
- Core **data structure concepts** (LIFO/FIFO).
- **Memory allocation**, **pointers**, and **linked data structures**.
- Handling **dynamic data** efficiently.
- Building **reusable modules** in C/C++.

---

## 11. Future Enhancements

- Add support for **Deque (Double-Ended Queue)**.
- Implement **Generic Templates** (C++ templates for any datatype).
- Create **GUI / Visualization** using SFML or SDL.
- Add **unit testing framework** (CUnit / Catch2).
- Include **persistence layer** to save stack/queue state.
- Convert into **header-only library** for integration into other projects.

---

## 12. Author

Mohammed Salem  
Email: salemmohamad926@gmail.com  
LinkedIn: https://www.linkedin.com/in/msalem02  
GitHub: https://github.com/msalem02

---

## 13. License

This project is licensed under the **MIT License**.  
You may reuse, modify, and distribute this project with attribution.

---

## 14. Acknowledgements

- Birzeit University — Computer Engineering Department  
- Data Structures course instructors and teaching assistants  
- Open-source community for C/C++ learning resources  
- Fellow students for testing and peer review

---

## 15. Version History

| Version | Date | Description |
|----------|------|-------------|
| 1.0 | March 2024 | Initial array-based implementation |
| 1.1 | April 2024 | Added linked-list structures |
| 1.2 | May 2024 | Added BFS and expression evaluation examples |
| 2.0 | June 2024 | Full integration with testing and documentation |

---
