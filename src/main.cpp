#include "Student.h"
#include "StudentManager.h"
#include <iostream>
#include <memory>

void printMenu() {
    std::cout << "\n===== Student Management System =====" << std::endl;
    std::cout << "1. Add Student" << std::endl;
    std::cout << "2. Remove Student" << std::endl;
    std::cout << "3. Update Student" << std::endl;
    std::cout << "4. Find Student by ID" << std::endl;
    std::cout << "5. Find Students by Name" << std::endl;
    std::cout << "6. Display All Students" << std::endl;
    std::cout << "7. Get Top Students" << std::endl;
    std::cout << "8. Get Students by Score Range" << std::endl;
    std::cout << "0. Exit" << std::endl;
    std::cout << "====================================" << std::endl;
    std::cout << "Enter your choice: ";
}

void addStudent(StudentManager& manager) {
    int id, age;
    std::string name;
    double score;
    
    std::cout << "Enter ID: ";
    std::cin >> id;
    std::cout << "Enter Name: ";
    std::cin >> name;
    std::cout << "Enter Age: ";
    std::cin >> age;
    std::cout << "Enter Score: ";
    std::cin >> score;
    
    Student student(id, name, age, score);
    if (manager.addStudent(student)) {
        std::cout << "Student added successfully!" << std::endl;
    } else {
        std::cout << "Failed to add student. ID already exists." << std::endl;
    }
}

void removeStudent(StudentManager& manager) {
    int id;
    std::cout << "Enter Student ID to remove: ";
    std::cin >> id;
    
    if (manager.removeStudent(id)) {
        std::cout << "Student removed successfully!" << std::endl;
    } else {
        std::cout << "Student not found." << std::endl;
    }
}

void updateStudent(StudentManager& manager) {
    int id, age;
    std::string name;
    double score;
    
    std::cout << "Enter Student ID to update: ";
    std::cin >> id;
    std::cout << "Enter new Name: ";
    std::cin >> name;
    std::cout << "Enter new Age: ";
    std::cin >> age;
    std::cout << "Enter new Score: ";
    std::cin >> score;
    
    Student newStudent(id, name, age, score);
    if (manager.updateStudent(id, newStudent)) {
        std::cout << "Student updated successfully!" << std::endl;
    } else {
        std::cout << "Student not found." << std::endl;
    }
}

void findStudentById(const StudentManager& manager) {
    int id;
    std::cout << "Enter Student ID: ";
    std::cin >> id;
    
    auto student = manager.findStudentById(id);
    if (student.has_value()) {
        std::cout << "Found: " << student->toString() << std::endl;
    } else {
        std::cout << "Student not found." << std::endl;
    }
}

void findStudentsByName(const StudentManager& manager) {
    std::string name;
    std::cout << "Enter Student Name: ";
    std::cin >> name;
    
    auto students = manager.findStudentsByName(name);
    if (students.empty()) {
        std::cout << "No students found with name: " << name << std::endl;
    } else {
        std::cout << "Found " << students.size() << " student(s):" << std::endl;
        for (const auto& s : students) {
            std::cout << "  " << s.toString() << std::endl;
        }
    }
}

void displayAllStudents(const StudentManager& manager) {
    const auto& students = manager.getAllStudents();
    if (students.empty()) {
        std::cout << "No students in the system." << std::endl;
    } else {
        std::cout << "Total students: " << manager.getStudentCount() << std::endl;
        for (const auto& s : students) {
            std::cout << "  " << s.toString() << std::endl;
        }
    }
}

void getTopStudents(const StudentManager& manager) {
    size_t count;
    std::cout << "Enter number of top students: ";
    std::cin >> count;
    
    auto topStudents = manager.getTopStudents(count);
    if (topStudents.empty()) {
        std::cout << "No students in the system." << std::endl;
    } else {
        std::cout << "Top " << topStudents.size() << " student(s):" << std::endl;
        for (const auto& s : topStudents) {
            std::cout << "  " << s.toString() << std::endl;
        }
    }
}

void getStudentsByScoreRange(const StudentManager& manager) {
    double minScore, maxScore;
    std::cout << "Enter minimum score: ";
    std::cin >> minScore;
    std::cout << "Enter maximum score: ";
    std::cin >> maxScore;
    
    auto students = manager.getStudentsByScoreRange(minScore, maxScore);
    if (students.empty()) {
        std::cout << "No students found in score range [" << minScore << ", " << maxScore << "]" << std::endl;
    } else {
        std::cout << "Found " << students.size() << " student(s):" << std::endl;
        for (const auto& s : students) {
            std::cout << "  " << s.toString() << std::endl;
        }
    }
}

int main() {
    auto manager = std::make_unique<StudentManager>();
    int choice;
    
    while (true) {
        printMenu();
        std::cin >> choice;
        
        switch (choice) {
            case 1: addStudent(*manager); break;
            case 2: removeStudent(*manager); break;
            case 3: updateStudent(*manager); break;
            case 4: findStudentById(*manager); break;
            case 5: findStudentsByName(*manager); break;
            case 6: displayAllStudents(*manager); break;
            case 7: getTopStudents(*manager); break;
            case 8: getStudentsByScoreRange(*manager); break;
            case 0:
                std::cout << "Goodbye!" << std::endl;
                return 0;
            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
        }
    }
}
