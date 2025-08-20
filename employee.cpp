#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <iomanip>

using namespace std;

class Employee {
private:
    int employeeID;
    string name;
    double salary;
    string department;

public:
    // Constructor
    Employee(int id, const string& n, double sal, const string& dept)
        : employeeID(id), name(n), salary(sal), department(dept) {}

    // Getters
    int getEmployeeID() const { return employeeID; }
    string getName() const { return name; }
    double getSalary() const { return salary; }
    string getDepartment() const { return department; }

    // Setters
    void setName(const string& n) { name = n; }
    void setSalary(double sal) { salary = sal; }
    void setDepartment(const string& dept) { department = dept; }

    // Calculate net salary after tax deduction (10%)
    double calculateNetSalary() const {
        return salary * 0.9; // 10% tax deduction
    }

    // Display employee details
    void display() const {
        cout << left << setw(10) << employeeID 
             << setw(20) << name 
             << setw(15) << fixed << setprecision(2) << salary
             << setw(15) << department
             << setw(15) << fixed << setprecision(2) << calculateNetSalary() << endl;
    }
};

class EmployeeManagementSystem {
private:
    vector<Employee> employees;

    // Helper function to find employee by ID
    int findEmployeeIndex(int id) {
        for (size_t i = 0; i < employees.size(); ++i) {
            if (employees[i].getEmployeeID() == id) {
                return static_cast<int>(i);
            }
        }
        return -1; // Not found
    }

public:
    // Add a new employee
    void addEmployee() {
        int id;
        string name, department;
        double salary;

        cout << "\nEnter Employee ID: ";
        while (!(cin >> id)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a numeric ID: ";
        }

        // Check if ID already exists
        if (findEmployeeIndex(id) != -1) {
            cout << "Employee with ID " << id << " already exists.\n";
            return;
        }

        cin.ignore(); // Clear newline from buffer
        cout << "Enter Name: ";
        getline(cin, name);

        cout << "Enter Salary: ";
        while (!(cin >> salary)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a numeric salary: ";
        }

        cin.ignore(); // Clear newline from buffer
        cout << "Enter Department: ";
        getline(cin, department);

        employees.emplace_back(id, name, salary, department);
        cout << "Employee added successfully!\n";
    }

    // View all employees
    void viewEmployees() {
        if (employees.empty()) {
            cout << "\nNo employees in the system.\n";
            return;
        }

        cout << "\nEmployee List:\n";
        cout << left << setw(10) << "ID" 
             << setw(20) << "Name" 
             << setw(15) << "Salary"
             << setw(15) << "Department"
             << setw(15) << "Net Salary" << endl;
        cout << string(75, '-') << endl;

        for (const auto& emp : employees) {
            emp.display();
        }
    }

    // Update employee details
    void updateEmployee() {
        if (employees.empty()) {
            cout << "\nNo employees in the system to update.\n";
            return;
        }

        int id;
        cout << "\nEnter Employee ID to update: ";
        while (!(cin >> id)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a numeric ID: ";
        }

        int index = findEmployeeIndex(id);
        if (index == -1) {
            cout << "Employee with ID " << id << " not found.\n";
            return;
        }

        cout << "\nCurrent Employee Details:\n";
        cout << left << setw(10) << "ID" 
             << setw(20) << "Name" 
             << setw(15) << "Salary"
             << setw(15) << "Department" << endl;
        cout << string(60, '-') << endl;
        employees[index].display();

        int choice;
        cout << "\nWhat would you like to update?\n";
        cout << "1. Name\n";
        cout << "2. Salary\n";
        cout << "3. Department\n";
        cout << "4. Cancel\n";
        cout << "Enter your choice: ";
        while (!(cin >> choice) || choice < 1 || choice > 4) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid choice. Please enter 1-4: ";
        }

        cin.ignore(); // Clear newline from buffer
        switch (choice) {
            case 1: {
                string newName;
                cout << "Enter new name: ";
                getline(cin, newName);
                employees[index].setName(newName);
                cout << "Name updated successfully.\n";
                break;
            }
            case 2: {
                double newSalary;
                cout << "Enter new salary: ";
                while (!(cin >> newSalary)) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalid input. Please enter a numeric salary: ";
                }
                employees[index].setSalary(newSalary);
                cout << "Salary updated successfully.\n";
                break;
            }
            case 3: {
                string newDept;
                cout << "Enter new department: ";
                getline(cin, newDept);
                employees[index].setDepartment(newDept);
                cout << "Department updated successfully.\n";
                break;
            }
            case 4:
                cout << "Update cancelled.\n";
                break;
        }
    }

    // Delete an employee
    void deleteEmployee() {
        if (employees.empty()) {
            cout << "\nNo employees in the system to delete.\n";
            return;
        }

        int id;
        cout << "\nEnter Employee ID to delete: ";
        while (!(cin >> id)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a numeric ID: ";
        }

        int index = findEmployeeIndex(id);
        if (index == -1) {
            cout << "Employee with ID " << id << " not found.\n";
            return;
        }

        cout << "Are you sure you want to delete employee " << employees[index].getName() << "? (y/n): ";
        char confirm;
        cin >> confirm;
        if (tolower(confirm) == 'y') {
            employees.erase(employees.begin() + index);
            cout << "Employee deleted successfully.\n";
        } else {
            cout << "Deletion cancelled.\n";
        }
    }
};

int main() {
    EmployeeManagementSystem ems;
    int choice;

    cout << "EMPLOYEE MANAGEMENT SYSTEM\n";
    cout << "--------------------------\n";

    do {
        cout << "\nMENU:\n";
        cout << "1. Add Employee\n";
        cout << "2. View Employees\n";
        cout << "3. Update Employee\n";
        cout << "4. Delete Employee\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";

        while (!(cin >> choice) || choice < 1 || choice > 5) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid choice. Please enter 1-5: ";
        }

        switch (choice) {
            case 1:
                ems.addEmployee();
                break;
            case 2:
                ems.viewEmployees();
                break;
            case 3:
                ems.updateEmployee();
                break;
            case 4:
                ems.deleteEmployee();
                break;
            case 5:
                cout << "Exiting the system. Goodbye!\n";
                break;
        }
    } while (choice != 5);

    return 0;
}