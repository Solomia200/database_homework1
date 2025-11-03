#ifndef DATABASE_HYBRID_H
#define DATABASE_HYBRID_H

#include "DatabaseBase.h"
#include "Student.h"
#include <string>
#include <vector>
#include <unordered_map>
#include <set>
#include <utility>

class DatabaseHybrid : public DatabaseBase {
public:
    void StudentsLoad(const std::string& filePath) override;
    std::vector<Student> Operetion1() override;
    void Operation2(const std::string& email, float newRating) override;
    std::pair<std::string, float> Operation3() override;
    size_t getStudentCount() const;

private:
    std::vector<Student> students;
    std::unordered_map<std::string, int> email_index;
    std::set<std::pair<float, int>> rating_index;
    std::unordered_map<std::string, std::pair<double, int>> group_rating;
    std::set<std::pair<double, std::string>> avg_index;
};

#endif 
