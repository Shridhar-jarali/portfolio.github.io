#include <iostream>
#include <set>
#include <vector>
#include <string>
#include <algorithm> // For set operations
#include <iterator>

using namespace std;

// Job structure to store job details
struct Job {
    string jobTitle;
    vector<string> requiredSkills;
    int experienceRequired;
    string location;
    string jobType;
    int applicants;
};

// Candidate structure to store candidate details
struct Candidate {
    string name;
    vector<string> skills;
    int experience;
    string location;
    string preferredJobType;
};

// Function to display a set of skills
void displaySkills(const set<string>& skills) {
    if (skills.empty()) {
        cout << "None" << endl;
    } else {
        for (const auto& skill : skills) {
            cout << skill << ", ";
        }
        cout << endl;
    }
}

// Function to perform skill gap analysis
void skillGapAnalysis(const Job& job, const Candidate& candidate) {
    set<string> requiredSkills(job.requiredSkills.begin(), job.requiredSkills.end());
    set<string> candidateSkills(candidate.skills.begin(), candidate.skills.end());

    set<string> missingSkills;
    set<string> extraSkills;
    set<string> matchedSkills;

    // Find missing skills: required but not possessed
    set_difference(requiredSkills.begin(), requiredSkills.end(),
                   candidateSkills.begin(), candidateSkills.end(),
                   inserter(missingSkills, missingSkills.begin()));

    // Find extra skills: possessed but not required
    set_difference(candidateSkills.begin(), candidateSkills.end(),
                   requiredSkills.begin(), requiredSkills.end(),
                   inserter(extraSkills, extraSkills.begin()));

    // Find matched skills: both required and possessed
    set_intersection(requiredSkills.begin(), requiredSkills.end(),
                     candidateSkills.begin(), candidateSkills.end(),
                     inserter(matchedSkills, matchedSkills.begin()));

    // Output the results
    cout << "For Job: " << job.jobTitle << " | Candidate: " << candidate.name << endl;
    cout << "Matched Skills: ";
    displaySkills(matchedSkills);
    cout << "Missing Skills: ";
    displaySkills(missingSkills);
    cout << "Extra Skills: ";
    displaySkills(extraSkills);

    // Check if the candidate meets other job requirements
    if (candidate.experience >= job.experienceRequired &&
        candidate.location == job.location &&
        candidate.preferredJobType == job.jobType) {
        cout << "Candidate meets all other requirements for the job.\n";
    } else {
        cout << "Candidate does not meet all other requirements for the job.\n";
    }
    cout << endl;
}

int main() {
    // Sample data for jobs
    vector<Job> jobs = {
        {"Software Engineer", {"Python", "Django", "SQL"}, 2, "New York", "Full-time", 150},
        {"Data Scientist", {"Python", "Machine Learning", "SQL"}, 3, "San Francisco", "Full-time", 200},
        {"Web Developer", {"HTML", "CSS", "JavaScript"}, 1, "Remote", "Part-time", 100}
    };

    // Sample data for candidates
    vector<Candidate> candidates = {
        {"Alice", {"Python", "Django", "SQL"}, 3, "New York", "Full-time"},
        {"Bob", {"Python", "Machine Learning", "SQL"}, 4, "San Francisco", "Full-time"},
        {"Charlie", {"HTML", "CSS", "JavaScript"}, 1, "Remote", "Part-time"},
        {"David", {"Python", "Django", "SQL"}, 1, "New York", "Full-time"}
    };

    // Input the candidate name to check
    string candidateName;
    cout << "Enter the candidate's name: ";
    cin >> candidateName;

    // Find the candidate by name
    auto it = find_if(candidates.begin(), candidates.end(),
                      [&candidateName](const Candidate& candidate) {
                          return candidate.name == candidateName;
                      });

    if (it != candidates.end()) {
        // Perform skill gap analysis for the found candidate
        for (const auto& job : jobs) {
            skillGapAnalysis(job, *it);
        }
    } else {
        cout << "Candidate " << candidateName << " not found.\n";
    }

    return 0;
}
