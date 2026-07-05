import random
import string
import datetime
import csv
import os


class StudentDataGenerator:
    def __init__(self):
        self.first_names = ["张", "李", "王", "刘", "陈", "杨", "赵", "黄", "周", "吴"]
        self.last_names = ["伟", "芳", "娜", "敏", "静", "强", "磊", "洋", "勇", "艳"]

    def generate_random_name(self):
        first = random.choice(self.first_names)
        last = random.choice(self.last_names)
        return first + last

    def generate_student(self, student_id):
        name = self.generate_random_name()
        age = random.randint(18, 25)
        score = round(random.uniform(0, 100), 1)
        return {
            "id": student_id,
            "name": name,
            "age": age,
            "score": score
        }

    def generate_students(self, count):
        students = []
        for i in range(1, count + 1):
            students.append(self.generate_student(i))
        return students

    def save_to_csv(self, students, filepath):
        with open(filepath, 'w', newline='', encoding='utf-8-sig') as f:
            writer = csv.DictWriter(f, fieldnames=["id", "name", "age", "score"])
            writer.writeheader()
            writer.writerows(students)
        return filepath


class StudentValidator:
    @staticmethod
    def validate_id(student_id):
        if not isinstance(student_id, int):
            return False, "ID必须是整数"
        if student_id <= 0:
            return False, "ID必须大于0"
        return True, ""

    @staticmethod
    def validate_name(name):
        if not isinstance(name, str):
            return False, "姓名必须是字符串"
        if len(name) < 2 or len(name) > 10:
            return False, "姓名长度必须在2-10个字符之间"
        return True, ""

    @staticmethod
    def validate_age(age):
        if not isinstance(age, int):
            return False, "年龄必须是整数"
        if age < 16 or age > 60:
            return False, "年龄必须在16-60岁之间"
        return True, ""

    @staticmethod
    def validate_score(score):
        if not isinstance(score, (int, float)):
            return False, "成绩必须是数字"
        if score < 0 or score > 100:
            return False, "成绩必须在0-100分之间"
        return True, ""

    @staticmethod
    def validate_student(student):
        errors = []
        valid, err = StudentValidator.validate_id(student["id"])
        if not valid:
            errors.append(err)
        valid, err = StudentValidator.validate_name(student["name"])
        if not valid:
            errors.append(err)
        valid, err = StudentValidator.validate_age(student["age"])
        if not valid:
            errors.append(err)
        valid, err = StudentValidator.validate_score(student["score"])
        if not valid:
            errors.append(err)
        return len(errors) == 0, errors


class TestReport:
    def __init__(self):
        self.test_cases = []
        self.start_time = None
        self.end_time = None

    def start(self):
        self.start_time = datetime.datetime.now()

    def add_result(self, case_name, passed, message=""):
        self.test_cases.append({
            "name": case_name,
            "passed": passed,
            "message": message,
            "time": datetime.datetime.now()
        })

    def finish(self):
        self.end_time = datetime.datetime.now()

    def get_summary(self):
        total = len(self.test_cases)
        passed = sum(1 for t in self.test_cases if t["passed"])
        failed = total - passed
        duration = (self.end_time - self.start_time).total_seconds() if self.end_time and self.start_time else 0
        return {
            "total": total,
            "passed": passed,
            "failed": failed,
            "pass_rate": round(passed * 100.0 / total, 2) if total > 0 else 0,
            "duration": round(duration, 3)
        }

    def print_report(self):
        summary = self.get_summary()
        print("=" * 60)
        print("                    测 试 报 告")
        print("=" * 60)
        print(f"测试开始时间: {self.start_time.strftime('%Y-%m-%d %H:%M:%S')}")
        print(f"测试结束时间: {self.end_time.strftime('%Y-%m-%d %H:%M:%S')}")
        print(f"测试总耗时: {summary['duration']} 秒")
        print("-" * 60)
        print(f"用例总数: {summary['total']}")
        print(f"通过: {summary['passed']}")
        print(f"失败: {summary['failed']}")
        print(f"通过率: {summary['pass_rate']}%")
        print("-" * 60)
        print("详细结果:")
        for i, case in enumerate(self.test_cases, 1):
            status = "✅ 通过" if case["passed"] else "❌ 失败"
            print(f"  {i}. {case['name']} - {status}")
            if case["message"]:
                print(f"     {case['message']}")
        print("=" * 60)

    def save_to_file(self, filepath):
        summary = self.get_summary()
        with open(filepath, 'w', encoding='utf-8') as f:
            f.write("=" * 60 + "\n")
            f.write("                    测 试 报 告\n")
            f.write("=" * 60 + "\n\n")
            f.write(f"测试开始时间: {self.start_time.strftime('%Y-%m-%d %H:%M:%S')}\n")
            f.write(f"测试结束时间: {self.end_time.strftime('%Y-%m-%d %H:%M:%S')}\n")
            f.write(f"测试总耗时: {summary['duration']} 秒\n\n")
            f.write(f"用例总数: {summary['total']}\n")
            f.write(f"通过: {summary['passed']}\n")
            f.write(f"失败: {summary['failed']}\n")
            f.write(f"通过率: {summary['pass_rate']}%\n\n")
            f.write("详细结果:\n")
            for i, case in enumerate(self.test_cases, 1):
                status = "通过" if case["passed"] else "失败"
                f.write(f"  {i}. {case['name']} - {status}\n")
                if case["message"]:
                    f.write(f"     {case['message']}\n")
            f.write("\n" + "=" * 60 + "\n")
        return filepath
