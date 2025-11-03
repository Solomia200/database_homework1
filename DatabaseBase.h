#ifndef DATABASE_BASE_H
#define DATABASE_BASE_H

#include <string>
#include <vector>
#include <utility>
#include "Student.h"
using namespace std;

class DatabaseBase {
public:
    virtual ~DatabaseBase() = default;

    virtual void StudentsLoad(const string& FilePath) = 0;
    virtual vector<Student> Operetion1() = 0;
    virtual void Operation2(const string& email, float newRating) = 0;
    virtual pair<string, float> Operation3() = 0;
};

#endif 

