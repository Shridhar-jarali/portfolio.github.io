#include <iostream>
#include <vector>
#include <string>

// Employee structure to store employee data
struct Employee {
    int employeeId;
    std::string currentPosition;
    std::string previousPosition;
    std::string skills;
    int experienceYears;
    std::string location;
};

// Function to predict the next position based on experience and current position
std::string predictNextPosition(const Employee& emp) {
    // If the employee has 5 or more years of experience
    if (emp.experienceYears >= 5) {
        if (emp.currentPosition == "Software Engineer") {
            return "Senior Software Engineer";
        } else if (emp.currentPosition == "Data Scientist") {
            return "Lead Data Scientist";
        } else if (emp.currentPosition == "Product Manager") {
            return "Senior Product Manager";
        } else if (emp.currentPosition == "HR Specialist") {
            return "HR Manager";
        } else if (emp.currentPosition == "Marketing Manager") {
            return "Marketing Director";
        }
    } else {
        // If less than 5 years of experience, predict a junior position
        return "Junior " + emp.currentPosition;
    }
}

// Function to display employee details and their predicted career path
void displayCareerPaths(const std::vector<Employee>& employees) {
    for (const auto& emp : employees) {
        std::string predictedPosition = predictNextPosition(emp);
        std::cout << "Employee ID: " << emp.employeeId << "\n"
                  << "Current Position: " << emp.currentPosition << "\n"
                  << "Experience: " << emp.experienceYears << " years\n"
                  << "Predicted Next Position: " << predictedPosition << "\n\n";
    }
}

int main() {
    // Creating sample employee data
    std::vector<Employee> employees = {
        {1, "Software Engineer", "Junior Developer", "Python, Java, SQL", 5, "New York"},
        {2, "Data Scientist", "Data Analyst", "R, Python, Machine Learning", 7, "San Francisco"},
        {3, "Product Manager", "Associate Product Manager", "Agile, Product Strategy", 6, "Seattle"},
        {4, "HR Specialist", "Recruiter", "Recruitment, Communication", 4, "Austin"},
        {5, "Marketing Manager", "Sales Associate", "SEO, Content Marketing", 8, "Boston"}
    };

    // Display career paths
    displayCareerPaths(employees);

    return 0;
}
