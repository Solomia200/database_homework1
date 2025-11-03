#ifndef DATABASE_VECTOR_H
#define DATABASE_VECTOR_H

#include "DatabaseBase.h"
#include "Student.h"
#include <string>
#include <vector>
#include <unordered_map>
#include <utility>

class DatabaseVector : public DatabaseBase {
public:
    size_t getStudentCount() const;
    void StudentsLoad(const std::string& filePath) override;
    std::vector<Student> Operetion1() override;
    void Operation2(const std::string& email, float newRating) override;
    std::pair<std::string, float> Operation3() override;

private:
    std::vector<Student> students;
};

#endif 
