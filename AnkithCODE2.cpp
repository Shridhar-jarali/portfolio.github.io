#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

// Job structure to define job requirements
struct Job {
    std::string jobTitle;
    std::vector<std::string> requiredSkills;
    int experienceRequired;
    std::string location;
    std::string jobType;
    int applicants;
};

// Candidate structure to store candidate details
struct Candidate {
    std::string name;
    std::vector<std::string> skills;
    int experience;
    std::string location;
    std::string preferredJobType;
};

// Function to check if the candidate matches the job requirements
bool matchJobs(const Candidate &candidate, const Job &job) {
    int matches = 0;
    for (const auto &skill : job.requiredSkills) {
        if (std::find(candidate.skills.begin(), candidate.skills.end(), skill) != candidate.skills.end()) {
            matches++;
        }
    }
    return matches > 0 && candidate.experience >= job.experienceRequired;
}

int main() {
    // Sample data for jobs
    std::vector<Job> jobs = {
        {"Software Engineer", {"Python", "Django", "SQL"}, 2, "New York", "Full-time", 150},
        {"Data Scientist", {"Python", "Machine Learning", "SQL"}, 3, "San Francisco", "Full-time", 200},
        {"Web Developer", {"HTML", "CSS", "JavaScript"}, 1, "Remote", "Part-time", 100}
    };

    // Sample data for candidates
    std::vector<Candidate> candidates = {
        {"Alice", {"Python", "Django", "SQL"}, 3, "New York", "Full-time"},
        {"Bob", {"Python", "Machine Learning", "SQL"}, 4, "San Francisco", "Full-time"},
        {"Charlie", {"HTML", "CSS", "JavaScript"}, 1, "Remote", "Part-time"},
        {"David", {"Python", "Django", "SQL"}, 1, "New York", "Full-time"}
    };

    // Ask the user to enter the candidate's name they want to check
    std::string candidateName;
    std::cout << "Enter the name of the candidate you want to check: ";
    std::getline(std::cin, candidateName);

    // Find the candidate
    auto it = std::find_if(candidates.begin(), candidates.end(), [&candidateName](const Candidate& candidate) {
        return candidate.name == candidateName;
    });

    // If the candidate is found
    if (it != candidates.end()) {
        Candidate selectedCandidate = *it;
        std::cout << "\nChecking job matches for Candidate: " << selectedCandidate.name << std::endl;
        for (const auto& job : jobs) {
            std::cout << "\nJob Title: " << job.jobTitle << std::endl;
            std::cout << "Location: " << job.location << std::endl;
            std::cout << "Experience Required: " << job.experienceRequired << " years" << std::endl;
            std::cout << "Job Type: " << job.jobType << std::endl;

            std::cout << "\nCandidate: " << selectedCandidate.name << std::endl;
            std::cout << "Location: " << selectedCandidate.location << std::endl;
            std::cout << "Skills: ";
            for (const auto& skill : selectedCandidate.skills) {
                std::cout << skill << " ";
            }
            std::cout << std::endl;
            std::cout << "Experience: " << selectedCandidate.experience << " years" << std::endl;

            if (matchJobs(selectedCandidate, job)) {
                std::cout << "This candidate is a match for the job!" << std::endl;
            } else {
                std::cout << "This candidate does not match the job requirements." << std::endl;
            }
        }
    } else {
        std::cout << "Candidate not found!" << std::endl;
    }

    return 0;
}
