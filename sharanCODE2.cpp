#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <string>
#include <queue>

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

// Structure for storing job and its match score (for heap)
struct JobMatch {
    string jobTitle;
    double matchScore;

    bool operator<(const JobMatch& other) const {
        return matchScore < other.matchScore;  // For max-heap (descending order)
    }
};

// Function to find the best-ranked companies for each candidate
void findBestCompaniesForCandidates(const vector<Candidate>& candidates, const vector<Job>& jobs) {
    for (const Candidate& candidate : candidates) {
        cout << "Candidate: " << candidate.name << endl;
        cout << "Matching Companies:" << endl;

        priority_queue<JobMatch> matchedJobs;  // Max-heap to store jobs and their match scores

        for (const Job& job : jobs) {
            double score = matchCandidateToJob(candidate, job);
            matchedJobs.push({job.jobTitle, score});
        }

        // Display top 3 companies for the candidate
        int count = 0;
        while (!matchedJobs.empty() && count < 3) {
            JobMatch bestJob = matchedJobs.top();
            cout << "- " << bestJob.jobTitle << " with match score: " << bestJob.matchScore << endl;
            matchedJobs.pop();
            count++;
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
    findBestCompaniesForCandidates(candidates, jobs);

    return 0;
}
