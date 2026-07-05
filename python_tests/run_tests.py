import sys
import os
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))

from test_utils import StudentDataGenerator, StudentValidator, TestReport


class StudentManagerSimulator:
    def __init__(self):
        self.students = []

    def add_student(self, student):
        for s in self.students:
            if s["id"] == student["id"]:
                return False
        self.students.append(student)
        return True

    def remove_student(self, student_id):
        for i, s in enumerate(self.students):
            if s["id"] == student_id:
                self.students.pop(i)
                return True
        return False

    def update_student(self, student_id, new_student):
        for i, s in enumerate(self.students):
            if s["id"] == student_id:
                self.students[i] = new_student
                return True
        return False

    def find_by_id(self, student_id):
        for s in self.students:
            if s["id"] == student_id:
                return s
        return None

    def find_by_name(self, name):
        result = []
        for s in self.students:
            if s["name"] == name:
                result.append(s)
        return result

    def get_all(self):
        return self.students

    def get_count(self):
        return len(self.students)

    def get_by_score_range(self, min_score, max_score):
        result = []
        for s in self.students:
            if min_score <= s["score"] <= max_score:
                result.append(s)
        return result

    def get_top_students(self, count):
        sorted_students = sorted(self.students, key=lambda x: x["score"], reverse=True)
        return sorted_students[:count]


class StudentManagementSystemTest:
    def __init__(self):
        self.manager = StudentManagerSimulator()
        self.generator = StudentDataGenerator()
        self.report = TestReport()
        self.test_data = []

    def setup(self):
        print("正在初始化测试数据...")
        self.test_data = [
            {"id": 1, "name": "张三", "age": 20, "score": 85.5},
            {"id": 2, "name": "李四", "age": 21, "score": 90.0},
            {"id": 3, "name": "王五", "age": 22, "score": 75.0},
            {"id": 4, "name": "张三", "age": 23, "score": 95.0},
            {"id": 5, "name": "赵六", "age": 19, "score": 88.5},
        ]
        for student in self.test_data:
            self.manager.add_student(student)
        print(f"已添加 {len(self.test_data)} 条测试数据")

    def test_add_student(self):
        print("\n[测试用例] 添加学生功能测试")
        
        new_student = {"id": 100, "name": "测试学生", "age": 20, "score": 80.0}
        result = self.manager.add_student(new_student)
        if result and self.manager.get_count() == 6:
            self.report.add_result("添加正常学生", True)
        else:
            self.report.add_result("添加正常学生", False, "添加失败或数量不对")

        result = self.manager.add_student(new_student)
        if not result:
            self.report.add_result("添加重复ID学生", True)
        else:
            self.report.add_result("添加重复ID学生", False, "重复ID应该添加失败")

    def test_remove_student(self):
        print("\n[测试用例] 删除学生功能测试")
        
        result = self.manager.remove_student(100)
        if result:
            self.report.add_result("删除存在的学生", True)
        else:
            self.report.add_result("删除存在的学生", False, "删除失败")

        result = self.manager.remove_student(9999)
        if not result:
            self.report.add_result("删除不存在的学生", True)
        else:
            self.report.add_result("删除不存在的学生", False, "不存在的学生应该删除失败")

    def test_update_student(self):
        print("\n[测试用例] 更新学生功能测试")
        
        updated = {"id": 1, "name": "张三更新", "age": 21, "score": 88.0}
        result = self.manager.update_student(1, updated)
        if result:
            student = self.manager.find_by_id(1)
            if student["name"] == "张三更新":
                self.report.add_result("更新存在的学生", True)
            else:
                self.report.add_result("更新存在的学生", False, "更新后数据不对")
        else:
            self.report.add_result("更新存在的学生", False, "更新失败")

        result = self.manager.update_student(9999, updated)
        if not result:
            self.report.add_result("更新不存在的学生", True)
        else:
            self.report.add_result("更新不存在的学生", False, "不存在的学生应该更新失败")

    def test_find_student(self):
        print("\n[测试用例] 查找学生功能测试")
        
        student = self.manager.find_by_id(2)
        if student and student["name"] == "李四":
            self.report.add_result("按ID查找存在的学生", True)
        else:
            self.report.add_result("按ID查找存在的学生", False, "查找结果不对")

        student = self.manager.find_by_id(9999)
        if student is None:
            self.report.add_result("按ID查找不存在的学生", True)
        else:
            self.report.add_result("按ID查找不存在的学生", False, "不存在的学生应该返回None")

        results = self.manager.find_by_name("张三")
        if len(results) == 2:
            self.report.add_result("按姓名查找学生", True)
        else:
            self.report.add_result("按姓名查找学生", False, f"应该找到2个，实际找到{len(results)}个")

    def test_score_range(self):
        print("\n[测试用例] 成绩区间筛选测试")
        
        results = self.manager.get_by_score_range(80, 90)
        count = len(results)
        if count >= 1:
            self.report.add_result("按成绩区间筛选", True, f"找到 {count} 个学生")
        else:
            self.report.add_result("按成绩区间筛选", False, "筛选结果不对")

    def test_top_students(self):
        print("\n[测试用例] 成绩排名测试")
        
        top3 = self.manager.get_top_students(3)
        if len(top3) == 3:
            if top3[0]["score"] >= top3[1]["score"] >= top3[2]["score"]:
                self.report.add_result("获取成绩排名前N", True)
            else:
                self.report.add_result("获取成绩排名前N", False, "排名顺序不对")
        else:
            self.report.add_result("获取成绩排名前N", False, "数量不对")

    def test_data_validation(self):
        print("\n[测试用例] 数据校验测试")
        
        valid_student = {"id": 1, "name": "测试", "age": 20, "score": 80.0}
        valid, errors = StudentValidator.validate_student(valid_student)
        if valid:
            self.report.add_result("正常数据校验通过", True)
        else:
            self.report.add_result("正常数据校验通过", False, str(errors))

        invalid_id = {"id": -1, "name": "测试", "age": 20, "score": 80.0}
        valid, errors = StudentValidator.validate_student(invalid_id)
        if not valid:
            self.report.add_result("无效ID校验失败", True)
        else:
            self.report.add_result("无效ID校验失败", False, "无效ID应该校验失败")

        invalid_score = {"id": 1, "name": "测试", "age": 20, "score": 101.0}
        valid, errors = StudentValidator.validate_student(invalid_score)
        if not valid:
            self.report.add_result("无效成绩校验失败", True)
        else:
            self.report.add_result("无效成绩校验失败", False, "无效成绩应该校验失败")

    def test_batch_data(self):
        print("\n[测试用例] 批量数据测试")
        
        batch_manager = StudentManagerSimulator()
        batch_students = self.generator.generate_students(50)
        for s in batch_students:
            batch_manager.add_student(s)
        
        if batch_manager.get_count() == 50:
            self.report.add_result("批量添加50条数据", True)
        else:
            self.report.add_result("批量添加50条数据", False, f"实际{batch_manager.get_count()}条")

        top10 = batch_manager.get_top_students(10)
        if len(top10) == 10:
            self.report.add_result("批量数据排名", True)
        else:
            self.report.add_result("批量数据排名", False, "排名数量不对")

        output_dir = os.path.join(os.path.dirname(os.path.abspath(__file__)), "output")
        os.makedirs(output_dir, exist_ok=True)
        csv_path = os.path.join(output_dir, "test_data.csv")
        self.generator.save_to_csv(batch_students, csv_path)
        if os.path.exists(csv_path):
            self.report.add_result("导出测试数据到CSV", True, f"文件路径: {csv_path}")
        else:
            self.report.add_result("导出测试数据到CSV", False, "文件生成失败")

    def run_all_tests(self):
        print("=" * 60)
        print("        学生信息管理系统 - 自动化测试")
        print("=" * 60)
        
        self.report.start()
        self.setup()
        
        self.test_add_student()
        self.test_remove_student()
        self.test_update_student()
        self.test_find_student()
        self.test_score_range()
        self.test_top_students()
        self.test_data_validation()
        self.test_batch_data()
        
        self.report.finish()
        
        print("\n")
        self.report.print_report()
        
        output_dir = os.path.join(os.path.dirname(os.path.abspath(__file__)), "output")
        os.makedirs(output_dir, exist_ok=True)
        report_path = os.path.join(output_dir, "test_report.txt")
        self.report.save_to_file(report_path)
        print(f"\n测试报告已保存到: {report_path}")
        
        summary = self.report.get_summary()
        return summary["failed"] == 0


def main():
    test = StudentManagementSystemTest()
    all_passed = test.run_all_tests()
    
    if all_passed:
        print("\n🎉 所有测试用例通过！")
        return 0
    else:
        print("\n❌ 部分测试用例失败，请检查！")
        return 1


if __name__ == "__main__":
    sys.exit(main())
