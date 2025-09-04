

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stdexcept>
using namespace std;

// ---------------- Base Class ----------------
class Person {
protected:
    string name;
    int age;
public:
    Person(string n = "Unknown", int a = 0) : name(n), age(a) {}
    virtual void display() const {
        cout << "Name: " << name << ", Age: " << age << endl;
    }
    virtual ~Person() {}
};

// ---------------- Derived Class: Student ----------------
class Student : public Person {
    int rollNo;
    double gpa;
public:
    Student(string n, int a, int r, double g) : Person(n, a), rollNo(r), gpa(g) {}
    void display() const override {
        cout << "[Student] Name: " << name << ", Age: " << age
             << ", Roll No: " << rollNo << ", GPA: " << gpa << endl;
    }
};

// ---------------- Derived Class: Teacher ----------------
class Teacher : public Person {
    string subject;
    double salary;
public:
    Teacher(string n, int a, string sub, double sal) : Person(n, a), subject(sub), salary(sal) {}
    void display() const override {
        cout << "[Teacher] Name: " << name << ", Age: " << age
             << ", Subject: " << subject << ", Salary: " << salary << endl;
    }
};

// ---------------- Manager Class ----------------
class School {
    vector<Person*> members;
public:
    void addMember(Person* p) {
        members.push_back(p);
    }
    void showAll() {
        cout << "\n--- School Members ---\n";
        for (auto& m : members) {
            m->display();
        }
    }
    void saveToFile(const string& filename) {
        ofstream fout(filename);
        if (!fout) throw runtime_error("Cannot open file!");
        for (auto& m : members) {
            // Just a demo save (not complete serialization)
            fout << "Member Info Saved\n";
        }
        fout.close();
    }
    ~School() {
        for (auto& m : members) delete m;
    }
};

// ---------------- Main Function ----------------
int main() {
    try {
        School s;

        // Adding students and teachers
        s.addMember(new Student("Viraj", 20, 101, 8.5));
        s.addMember(new Student("Riya", 19, 102, 9.1));
        s.addMember(new Teacher("Mr. Sharma", 45, "Mathematics", 55000));
        s.addMember(new Teacher("Mrs. Patel", 39, "Physics", 60000));

        // Display all members
        s.showAll();

        // Save data to file
        s.saveToFile("school_data.txt");
        cout << "\nData saved to 'school_data.txt'\n";
    }
    catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
    }

    return 0;
}
