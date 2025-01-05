#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <numeric>
#include <iomanip> // For precision formatting

using namespace std;

// Structure to represent a job posting
struct JobPosting {
    string role;
    string location;
    double salary;
};

// Function to calculate the average of a vector of salaries
double calculateAverage(const vector<double>& salaries) {
    if (salaries.empty()) return 0.0;
    double sum = accumulate(salaries.begin(), salaries.end(), 0.0);
    return sum / salaries.size();
}

// Function to display salary statistics for a specific role
void analyzeSalaryDistribution(const vector<JobPosting>& jobPostings) {
    // Map to group salaries by job roles
    map<string, vector<double>> roleSalaryMap;

    // Populate the map
    for (const JobPosting& posting : jobPostings) {
        roleSalaryMap[posting.role].push_back(posting.salary);
    }

    // Display analysis for each role
    for (map<string, vector<double>>::iterator it = roleSalaryMap.begin(); it != roleSalaryMap.end(); ++it) {
        string role = it->first;
        vector<double>& salaries = it->second;

        cout << "Role: " << role << endl;

        double minSalary = *min_element(salaries.begin(), salaries.end());
        double maxSalary = *max_element(salaries.begin(), salaries.end());
        double avgSalary = calculateAverage(salaries);

        cout << "  Minimum Salary: $" << fixed << setprecision(2) << minSalary << endl;
        cout << "  Maximum Salary: $" << fixed << setprecision(2) << maxSalary << endl;
        cout << "  Average Salary: $" << fixed << setprecision(2) << avgSalary << endl;
        cout << endl;
    }
}

// Function to compare salaries across locations for a specific role
void compareSalariesAcrossLocations(const vector<JobPosting>& jobPostings, const string& role) {
    // Map to group salaries by location for the given role
    map<string, vector<double>> locationSalaryMap;

    // Populate the map
    for (const JobPosting& posting : jobPostings) {
        if (posting.role == role) {
            locationSalaryMap[posting.location].push_back(posting.salary);
        }
    }

    // Display comparison
    cout << "Salary Comparison for Role: " << role << endl;
    for (map<string, vector<double>>::iterator it = locationSalaryMap.begin(); it != locationSalaryMap.end(); ++it) {
        string location = it->first;
        vector<double>& salaries = it->second;

        double avgSalary = calculateAverage(salaries);
        cout << "  Location: " << location
             << " | Average Salary: $" << fixed << setprecision(2) << avgSalary << endl;
    }
    cout << endl;
}

int main() {
    // Sample job postings data
    vector<JobPosting> jobPostings = {
        {"Software Engineer", "New York", 90000},
        {"Software Engineer", "San Francisco", 120000},
        {"Software Engineer", "Remote", 100000},
        {"Data Scientist", "New York", 110000},
        {"Data Scientist", "San Francisco", 130000},
        {"Web Developer", "Remote", 70000},
        {"Web Developer", "New York", 75000},
        {"Web Developer", "San Francisco", 85000}
    };

    // Analyze salary distribution for all roles
    analyzeSalaryDistribution(jobPostings);

    // Compare salaries for a specific role across locations
    compareSalariesAcrossLocations(jobPostings, "Software Engineer");

    return 0;
}

