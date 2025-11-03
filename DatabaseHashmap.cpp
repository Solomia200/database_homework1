#include "DatabaseHashmap.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <unordered_map>
#include <string>
#include <vector>
#include <utility>
using namespace std;

void DatabaseHashmap::StudentsLoad(const string& filePath) {
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

        students[s.m_email] = move(s);
    }
}

vector<Student> DatabaseHashmap::Operetion1() {
    vector<Student> all;
    all.reserve(students.size());

    for (auto& [email, student] : students)
        all.push_back(student);

    sort(all.begin(), all.end(), [](const Student& a, const Student& b) {
        return a.m_rating > b.m_rating;
    });

    if (all.size() > 100)
        all.resize(100);

    return all;
}

void DatabaseHashmap::Operation2(const string& email, float newRating) {
    if (students.contains(email)) {
        Student& student = students[email];
        student.m_rating = newRating;
    } else {
        cout << "Student with email " << email << " not found.\n";
    }
}

pair<string, float> DatabaseHashmap::Operation3() {
    unordered_map<string, float> groupSum;
    unordered_map<string, int> groupCount;

    for (auto& [email, student] : students) {
        groupSum[student.m_group] += student.m_rating;
        groupCount[student.m_group]++;
    }

    unordered_map<string, float> groupAvg;
    for (const auto& [group, sum] : groupSum) {
        groupAvg[group] = sum / groupCount[group];
    }

    auto best = max_element(
        groupAvg.begin(), groupAvg.end(),
        [](const pair<const string, float>& a, const pair<const string, float>& b) {
            return a.second < b.second;
        });

    if (best != groupAvg.end()) {
        return {best->first, best->second};
    } else {
        return {"", 0.0f};
    }
    
    
}

size_t DatabaseHashmap::getStudentCount() const {
    return students.size();
    }