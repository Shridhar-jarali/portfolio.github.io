#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <string>

using namespace std;

// Job structure to store job details
struct Job {
    string jobTitle;
    vector<string> requiredSkills;
    int experienceRequired;
    string location;
    string jobType;
};

// Candidate structure to store candidate details
struct Candidate {
    string name;
    vector<string> skills;
    int experience;
    string location;
    string preferredJobType;
};

// Function to calculate the match score between a candidate and a job
double matchCandidateToJob(const Candidate& candidate, const Job& job) {
    // Matching skills
    set<string> jobSkills(job.requiredSkills.begin(), job.requiredSkills.end());
    set<string> candidateSkills(candidate.skills.begin(), candidate.skills.end());
    
    int commonSkills = 0;
    for (const string& skill : candidateSkills) {
        if (jobSkills.find(skill) != jobSkills.end()) {
            commonSkills++;
        }
    }
    
    double skillMatch = (double)commonSkills / job.requiredSkills.size();
    
    // Experience match
    double experienceMatch = (double)min(candidate.experience, job.experienceRequired) / job.experienceRequired;
    
    // Location match
    double locationMatch = (candidate.location == job.location) ? 1.0 : 0.0;
    
    // Job type match
    double jobTypeMatch = (candidate.preferredJobType == job.jobType) ? 1.0 : 0.0;
    
    // Calculate overall match score
    double matchScore = 0.4 * skillMatch + 0.3 * experienceMatch + 0.2 * locationMatch + 0.1 * jobTypeMatch;
    
    return matchScore;
}

// Function to find the best matching candidates for each job
void findBestMatch(const vector<Candidate>& candidates, const vector<Job>& jobs) {
    for (const Job& job : jobs) {
        cout << "Job Title: " << job.jobTitle << endl;
        cout << "Matching Candidates:" << endl;

        vector<pair<string, double>> matchedCandidates;

        for (const Candidate& candidate : candidates) {
            double score = matchCandidateToJob(candidate, job);
            matchedCandidates.push_back({candidate.name, score});
        }

        // Sort candidates by match score in descending order
        sort(matchedCandidates.begin(), matchedCandidates.end(), 
             [](const pair<string, double>& a, const pair<string, double>& b) {
                 return a.second > b.second;
             });

        // Display top 3 matches for the job
        for (int i = 0; i < min(3, (int)matchedCandidates.size()); i++) {
            cout << "- " << matchedCandidates[i].first << " with match score: " << matchedCandidates[i].second << endl;
        }
        cout << endl;
    }
}

int main() {
    // Sample data for jobs
    vector<Job> jobs = {
        {"Software Engineer", {"Python", "Django", "SQL"}, 2, "New York", "Full-time"},
        {"Data Scientist", {"Python", "Machine Learning", "SQL"}, 3, "San Francisco", "Full-time"},
        {"Web Developer", {"HTML", "CSS", "JavaScript"}, 1, "Remote", "Part-time"}
    };

    // Sample data for candidates
    vector<Candidate> candidates = {
        {"Alice", {"Python", "Django", "SQL"}, 3, "New York", "Full-time"},
        {"Bob", {"Python", "Machine Learning", "SQL"}, 4, "San Francisco", "Full-time"},
        {"Charlie", {"HTML", "CSS", "JavaScript"}, 1, "Remote", "Part-time"},
        {"David", {"Python", "Django", "SQL"}, 1, "New York", "Full-time"}
    };

    // Run the matching process
    findBestMatch(candidates, jobs);

    return 0;
}

