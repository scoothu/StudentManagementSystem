#include <gtest/gtest.h>
#include "Student.h"

class StudentTest : public ::testing::Test {
protected:
    Student student{1, "John", 20, 85.5};
};

TEST_F(StudentTest, ConstructorAndGetters) {
    EXPECT_EQ(student.getId(), 1);
    EXPECT_EQ(student.getName(), "John");
    EXPECT_EQ(student.getAge(), 20);
    EXPECT_DOUBLE_EQ(student.getScore(), 85.5);
}

TEST_F(StudentTest, Setters) {
    student.setName("Jane");
    student.setAge(21);
    student.setScore(90.0);
    
    EXPECT_EQ(student.getName(), "Jane");
    EXPECT_EQ(student.getAge(), 21);
    EXPECT_DOUBLE_EQ(student.getScore(), 90.0);
}

TEST_F(StudentTest, ToString) {
    std::string result = student.toString();
    EXPECT_NE(result.find("ID: 1"), std::string::npos);
    EXPECT_NE(result.find("Name: John"), std::string::npos);
    EXPECT_NE(result.find("Age: 20"), std::string::npos);
    EXPECT_NE(result.find("Score: 85.5"), std::string::npos);
}

TEST_F(StudentTest, EqualityOperator) {
    Student student2{1, "Different", 25, 70.0};
    Student student3{2, "John", 20, 85.5};
    
    EXPECT_TRUE(student == student2);
    EXPECT_FALSE(student == student3);
}
