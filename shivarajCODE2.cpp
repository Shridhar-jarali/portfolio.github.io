#include <iostream>
#include <vector>
#include <algorithm> // For sort function

// Define a structure to hold job data
struct Job {
    std::string title;  // Job title
    int applicants;     // Number of applicants or popularity score

    // Constructor for convenience
    Job(std::string t, int a) : title(t), applicants(a) {}
};

// Comparator function to sort jobs by the number of applicants in descending order
bool compareJobs(const Job& a, const Job& b) {
    return a.applicants > b.applicants; // Higher applicants come first
}

int main() {
    // Input: List of jobs with their applicant count
    std::vector<Job> jobs = {
        Job("Software Engineer", 150),
        Job("Data Scientist", 200),
        Job("Web Developer", 100),
        Job("Product Manager", 180),
        Job("Graphic Designer", 90)
    };

    // Sort the jobs based on popularity
    std::sort(jobs.begin(), jobs.end(), compareJobs);

    // Output: Display the ranked list of jobs
    std::cout << "Job Popularity Ranking:\n";
    for (size_t i = 0; i < jobs.size(); ++i) {
        std::cout << i + 1 << ". " << jobs[i].title << " (" << jobs[i].applicants << " applicants)\n";
    }

    return 0;
}

