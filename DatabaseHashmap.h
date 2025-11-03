#ifndef DATABASE_HASHMAP_H
#define DATABASE_HASHMAP_H

#include "DatabaseBase.h"
#include "Student.h"
#include <string>
#include <vector>
#include <unordered_map>
#include <utility>

class DatabaseHashmap : public DatabaseBase {
public:
    void StudentsLoad(const std::string& filePath) override;
    std::vector<Student> Operetion1() override;
    void Operation2(const std::string& email, float newRating) override;
    std::pair<std::string, float> Operation3() override;
    std ::size_t getStudentCount() const ;


private:
    std::unordered_map<std::string, Student> students;
};

#endif 
