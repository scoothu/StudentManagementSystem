# Student Management System

A C++ command-line student information management system with unit testing (Google Test) and Python automated testing.

## Features

- Add / Remove / Update student records
- Query by ID or Name
- Filter by score range
- Get top students by score
- C++17 with modern features (`std::optional`, smart pointers)
- Unit tests with Google Test
- Python automated test suite

## Tech Stack

- C++17
- CMake 3.14+
- Google Test (v1.14.0)
- Python 3.x (for automated testing)

## Project Structure

```
.
├── CMakeLists.txt          # CMake build configuration
├── include/
│   ├── Student.h           # Student model
│   └── StudentManager.h    # CRUD manager
├── src/
│   ├── main.cpp            # CLI entry point
│   ├── Student.cpp         # Student implementation
│   └── StudentManager.cpp  # Manager implementation
├── tests/
│   ├── StudentTests.cpp         # Unit tests for Student
│   ├── StudentManagerTests.cpp  # Unit tests for Manager
│   └── SimpleTests.cpp          # Additional tests
└── python_tests/
    ├── run_tests.py        # Python automated test runner
    ├── test_utils.py       # Test utilities
    └── README.md           # Python test guide
```

## Build & Run

### Prerequisites

- CMake 3.14 or higher
- A C++17 compatible compiler (MSVC, GCC, Clang)

### Build

```bash
# Clone the repository
git clone https://github.com/scoothu/StudentManagementSystem.git
cd StudentManagementSystem

# Create build directory
mkdir build && cd build

# Generate build files
cmake ..

# Build
cmake --build .
```

### Run

```bash
# Run the main application
./student_system

# Run unit tests
ctest --output-on-failure
```

## Python Automated Testing

See [python_tests/README.md](python_tests/README.md) for details.

```bash
cd python_tests
python run_tests.py
```

## Key Highlights

- **Object-oriented design**: Clean separation of `Student` (model) and `StudentManager` (controller)
- **Modern C++**: Uses `std::optional` for safe null handling, `std::make_unique` for memory management
- **CMake integration**: Cross-platform build with automatic Google Test fetching
- **Comprehensive testing**: C++ unit tests + Python automated tests covering 15+ test cases
