#pragma once
#include <string>
#include <vector>

class Student {
public:
    Student() = default;
    Student(int id, const std::string& name, int age, double score);

    int getId() const;
    std::string getName() const;
    int getAge() const;
    double getScore() const;

    void setName(const std::string& name);
    void setAge(int age);
    void setScore(double score);

    std::string toString() const;

private:
    int m_id = 0;
    std::string m_name;
    int m_age = 0;
    double m_score = 0.0;
};

bool operator==(const Student& lhs, const Student& rhs);
