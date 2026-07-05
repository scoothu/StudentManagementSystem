#pragma once
#include "Student.h"
#include <vector>
#include <optional>

class StudentManager {
public:
    StudentManager() = default;

    bool addStudent(const Student& student);
    bool removeStudent(int id);
    bool updateStudent(int id, const Student& newStudent);
    std::optional<Student> findStudentById(int id) const;
    std::vector<Student> findStudentsByName(const std::string& name) const;
    
    const std::vector<Student>& getAllStudents() const;
    size_t getStudentCount() const;
    
    std::vector<Student> getStudentsByScoreRange(double minScore, double maxScore) const;
    std::vector<Student> getTopStudents(size_t count) const;

private:
    std::vector<Student> m_students;
};
