#include <gtest/gtest.h>
#include "StudentManager.h"

class StudentManagerTest : public ::testing::Test {
protected:
    StudentManager manager;
    Student s1{1, "Alice", 20, 85.0};
    Student s2{2, "Bob", 21, 90.0};
    Student s3{3, "Charlie", 22, 75.0};
    Student s4{4, "Alice", 23, 95.0};
};

TEST_F(StudentManagerTest, AddStudent) {
    EXPECT_TRUE(manager.addStudent(s1));
    EXPECT_EQ(manager.getStudentCount(), 1);
}

TEST_F(StudentManagerTest, AddDuplicateStudent) {
    manager.addStudent(s1);
    EXPECT_FALSE(manager.addStudent(s1));
    EXPECT_EQ(manager.getStudentCount(), 1);
}

TEST_F(StudentManagerTest, RemoveStudent) {
    manager.addStudent(s1);
    EXPECT_TRUE(manager.removeStudent(1));
    EXPECT_EQ(manager.getStudentCount(), 0);
}

TEST_F(StudentManagerTest, RemoveNonExistentStudent) {
    EXPECT_FALSE(manager.removeStudent(999));
}

TEST_F(StudentManagerTest, UpdateStudent) {
    manager.addStudent(s1);
    Student updated{1, "Alice Updated", 21, 88.0};
    
    EXPECT_TRUE(manager.updateStudent(1, updated));
    auto result = manager.findStudentById(1);
    EXPECT_TRUE(result.has_value());
    EXPECT_EQ(result->getName(), "Alice Updated");
}

TEST_F(StudentManagerTest, UpdateNonExistentStudent) {
    EXPECT_FALSE(manager.updateStudent(999, s1));
}

TEST_F(StudentManagerTest, FindStudentById) {
    manager.addStudent(s1);
    auto result = manager.findStudentById(1);
    
    EXPECT_TRUE(result.has_value());
    EXPECT_EQ(result->getName(), "Alice");
}

TEST_F(StudentManagerTest, FindNonExistentStudentById) {
    auto result = manager.findStudentById(999);
    EXPECT_FALSE(result.has_value());
}

TEST_F(StudentManagerTest, FindStudentsByName) {
    manager.addStudent(s1);
    manager.addStudent(s4);
    
    auto results = manager.findStudentsByName("Alice");
    EXPECT_EQ(results.size(), 2);
}

TEST_F(StudentManagerTest, GetAllStudents) {
    manager.addStudent(s1);
    manager.addStudent(s2);
    
    const auto& all = manager.getAllStudents();
    EXPECT_EQ(all.size(), 2);
}

TEST_F(StudentManagerTest, GetStudentsByScoreRange) {
    manager.addStudent(s1);
    manager.addStudent(s2);
    manager.addStudent(s3);
    
    auto results = manager.getStudentsByScoreRange(80.0, 90.0);
    EXPECT_EQ(results.size(), 2);
}

TEST_F(StudentManagerTest, GetTopStudents) {
    manager.addStudent(s1);
    manager.addStudent(s2);
    manager.addStudent(s3);
    
    auto top = manager.getTopStudents(2);
    EXPECT_EQ(top.size(), 2);
    EXPECT_EQ(top[0].getName(), "Bob");
    EXPECT_EQ(top[1].getName(), "Alice");
}

TEST_F(StudentManagerTest, EmptyManager) {
    EXPECT_EQ(manager.getStudentCount(), 0);
    EXPECT_TRUE(manager.getAllStudents().empty());
}
