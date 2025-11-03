#include "DatabaseHybrid.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <unordered_map>
#include <set>
#include <string>
#include <vector>
#include <utility>
using namespace std;

void DatabaseHybrid::StudentsLoad(const string& filePath) {
    ifstream file(filePath);
    if (!file.is_open()) {
        cout << "Error opening file: " << filePath << endl;
        return;
    }

    string line;
    getline(file, line);
    while (getline(file, line)) {
        Student s;
        stringstream ss(line);
        string num;

        getline(ss, s.m_name, ',');
        getline(ss, s.m_surname, ',');
        getline(ss, s.m_email, ',');
        getline(ss, num, ','); s.m_birth_year = stoi(num);
        getline(ss, num, ','); s.m_birth_month = stoi(num);
        getline(ss, num, ','); s.m_birth_day = stoi(num);
        getline(ss, s.m_group, ',');
        getline(ss, num, ','); s.m_rating = stof(num);
        getline(ss, s.m_phone_number, ',');

        students.push_back(s);
        int id = students.size() - 1;
        email_index[s.m_email] = id;
        rating_index.insert({s.m_rating, id});

        auto& stat = group_rating[s.m_group];
        stat.first += s.m_rating;
        stat.second += 1;
    }

    // Build average index
    for (const auto& [group, stat] : group_rating) {
        double avg = stat.first / stat.second;
        avg_index.insert({avg, group});
    }
}

vector<Student> DatabaseHybrid::Operetion1() {
    vector<Student> topStudents;
    topStudents.reserve(100);

    int i = 0;
    for (auto it = rating_index.rbegin(); it != rating_index.rend() && i < 100; ++it, ++i) {
        int id = it->second;
        topStudents.push_back(students[id]);
    }

    return topStudents;
}

void DatabaseHybrid::Operation2(const string& email, float newRating) {
    auto it = email_index.find(email);
    if (it == email_index.end()) {
        cout << "Student with email " << email << " not found.\n";
        return;
    }

    int id = it->second;
    Student& student = students[id];

   
    rating_index.erase({student.m_rating, id});
    float oldRating = student.m_rating;
    student.m_rating = newRating;
    rating_index.insert({student.m_rating, id});

   
    auto& stat = group_rating[student.m_group];
    stat.first += (newRating - oldRating);

  
    double oldAvg = (stat.first - (newRating - oldRating)) / stat.second;
    avg_index.erase({oldAvg, student.m_group});

    double newAvg = stat.first / stat.second;
    avg_index.insert({newAvg, student.m_group});
}

pair<string, float> DatabaseHybrid::Operation3() {
    if (avg_index.empty()) {
        return {"", 0.0f};
    }

    auto it = avg_index.rbegin();
    string bestGroup = it->second;
    float bestAvg = it->first;

    return {bestGroup, bestAvg};
}

size_t DatabaseHybrid::getStudentCount() const {
    return students.size();
}
