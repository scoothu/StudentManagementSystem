#include "Student.h"
#include <sstream>

Student::Student(int id, const std::string& name, int age, double score)
    : m_id(id), m_name(name), m_age(age), m_score(score) {}

int Student::getId() const { return m_id; }
std::string Student::getName() const { return m_name; }
int Student::getAge() const { return m_age; }
double Student::getScore() const { return m_score; }

void Student::setName(const std::string& name) { m_name = name; }
void Student::setAge(int age) { m_age = age; }
void Student::setScore(double score) { m_score = score; }

std::string Student::toString() const {
    std::ostringstream oss;
    oss << "ID: " << m_id << ", Name: " << m_name 
        << ", Age: " << m_age << ", Score: " << m_score;
    return oss.str();
}

bool operator==(const Student& lhs, const Student& rhs) {
    return lhs.getId() == rhs.getId();
}
