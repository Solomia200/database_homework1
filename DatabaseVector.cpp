#include "DatabaseVector.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <unordered_map>
#include <string>
#include <vector>
#include <utility>
using namespace std;

size_t DatabaseVector::getStudentCount() const {
    return students.size();
}

void DatabaseVector::StudentsLoad(const string& filePath) {
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
    }
}

vector<Student> DatabaseVector::Operetion1() {
    vector<Student> copiedStudents = students;

    sort(copiedStudents.begin(), copiedStudents.end(),
         [](const Student& a, const Student& b) {
             return a.m_rating > b.m_rating;
         });

    int limit_100 = min(100, static_cast<int>(copiedStudents.size()));
    return vector<Student>(copiedStudents.begin(), copiedStudents.begin() + limit_100);
}

void DatabaseVector::Operation2(const string& email, float newRating) {
    for (Student& s : students) {
        if (email == s.m_email) {
            s.m_rating = newRating;
            return;
        }
    }
    cout << "Student with email " << email << " not found.\n";
}

pair<string, float> DatabaseVector::Operation3() {
    unordered_map<string, float> groupSum;
    unordered_map<string, int> groupCount;

    for (const Student& s : students) {
        groupSum[s.m_group] += s.m_rating;
        groupCount[s.m_group]++;
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
