# Dijkstra Algorithm Fuzzer

Fuzzing a Dijkstra shortest path implementation using AFL++ by comparing it against a reference implementation.

## What It Does

Generates random graphs, runs two Dijkstra implementations on them, and crashes if they disagree. Helps find bugs automatically.

## Prerequisites

- AFL++
- CMake 3.13+
- C++20 compiler
- Python 3

Binary format with 4-byte integers:
- Number of nodes (n)
- Number of edges (m)
- For each edge: from_node, to_node, weight
- Source node

## Limits

- Max 1000 nodes
- Max 50,000 edges
- Negative weights allowed


## Results
- Crashes saved to `findings/default/crashes/`
- Each crash file is an input that found a discrepancy
- Error messages show what went wrong (size mismatch, distance mismatch, etc.)

## Notes

- Uses AddressSanitizer and UndefinedBehaviorSanitizer
- AFL++ will mutate inputs to find edge cases
- Press Ctrl+C to stop fuzzing