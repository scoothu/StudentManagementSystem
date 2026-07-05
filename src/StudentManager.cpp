#include "StudentManager.h"
#include <algorithm>

bool StudentManager::addStudent(const Student& student) {
    if (findStudentById(student.getId()).has_value()) {
        return false;
    }
    m_students.push_back(student);
    return true;
}

bool StudentManager::removeStudent(int id) {
    auto it = std::find_if(m_students.begin(), m_students.end(),
        [id](const Student& s) { return s.getId() == id; });
    if (it == m_students.end()) {
        return false;
    }
    m_students.erase(it);
    return true;
}

bool StudentManager::updateStudent(int id, const Student& newStudent) {
    auto it = std::find_if(m_students.begin(), m_students.end(),
        [id](const Student& s) { return s.getId() == id; });
    if (it == m_students.end()) {
        return false;
    }
    *it = newStudent;
    return true;
}

std::optional<Student> StudentManager::findStudentById(int id) const {
    auto it = std::find_if(m_students.begin(), m_students.end(),
        [id](const Student& s) { return s.getId() == id; });
    if (it == m_students.end()) {
        return std::nullopt;
    }
    return *it;
}

std::vector<Student> StudentManager::findStudentsByName(const std::string& name) const {
    std::vector<Student> result;
    for (const auto& student : m_students) {
        if (student.getName() == name) {
            result.push_back(student);
        }
    }
    return result;
}

const std::vector<Student>& StudentManager::getAllStudents() const {
    return m_students;
}

size_t StudentManager::getStudentCount() const {
    return m_students.size();
}

std::vector<Student> StudentManager::getStudentsByScoreRange(double minScore, double maxScore) const {
    std::vector<Student> result;
    for (const auto& student : m_students) {
        double score = student.getScore();
        if (score >= minScore && score <= maxScore) {
            result.push_back(student);
        }
    }
    return result;
}

std::vector<Student> StudentManager::getTopStudents(size_t count) const {
    std::vector<Student> sorted = m_students;
    std::sort(sorted.begin(), sorted.end(),
        [](const Student& a, const Student& b) {
            return a.getScore() > b.getScore();
        });
    if (count > sorted.size()) {
        count = sorted.size();
    }
    return std::vector<Student>(sorted.begin(), sorted.begin() + count);
}
