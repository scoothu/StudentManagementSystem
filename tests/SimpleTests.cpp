#include "Student.h"
#include "StudentManager.h"
#include <iostream>
#include <cassert>

void testStudentClass() {
    std::cout << "Testing Student class..." << std::endl;
    
    Student s(1, "Alice", 20, 85.5);
    assert(s.getId() == 1);
    assert(s.getName() == "Alice");
    assert(s.getAge() == 20);
    assert(s.getScore() == 85.5);
    
    s.setName("Bob");
    s.setAge(21);
    s.setScore(90.0);
    assert(s.getName() == "Bob");
    assert(s.getAge() == 21);
    assert(s.getScore() == 90.0);
    
    std::cout << "Student class tests passed!" << std::endl;
}

void testStudentManager() {
    std::cout << "\nTesting StudentManager class..." << std::endl;
    
    StudentManager manager;
    Student s1(1, "Alice", 20, 85.0);
    Student s2(2, "Bob", 21, 90.0);
    Student s3(3, "Charlie", 22, 75.0);
    
    assert(manager.addStudent(s1) == true);
    assert(manager.addStudent(s2) == true);
    assert(manager.addStudent(s3) == true);
    assert(manager.getStudentCount() == 3);
    
    assert(manager.addStudent(s1) == false);
    
    auto found = manager.findStudentById(2);
    assert(found.has_value());
    assert(found->getName() == "Bob");
    
    assert(manager.removeStudent(3) == true);
    assert(manager.getStudentCount() == 2);
    
    assert(manager.removeStudent(999) == false);
    
    auto top = manager.getTopStudents(1);
    assert(top.size() == 1);
    assert(top[0].getName() == "Bob");
    
    std::cout << "StudentManager class tests passed!" << std::endl;
}

int main() {
    testStudentClass();
    testStudentManager();
    
    std::cout << "\n=== All tests passed! ===" << std::endl;
    return 0;
}
