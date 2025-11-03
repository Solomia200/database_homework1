#include <chrono>
#include <fstream>
#include <iostream>
#include <random>
#include <string>
#include <vector>
#include <malloc.h>
#include "DatabaseBase.h"
#include "DatabaseVector.h"
#include "DatabaseHashmap.h"
#include "DatabaseHybrid.h"

using namespace std;

struct ExperimentResult {
    string version;
    int n;
    long operations;
    double memoryMB;
};


long measure(DatabaseBase& db, int A, int B, int C, default_random_engine& rng) {
    uniform_int_distribution<int> opDist(1, A + B + C);
    uniform_int_distribution<int> ratingDist(50, 100);

    for (int i = 0; i < 10; ++i)
        db.Operetion1(); 

    long count = 0;
    auto start = chrono::high_resolution_clock::now();

    while (true) {
        int choice = opDist(rng);
        if (choice <= A)
            db.Operetion1();
        else if (choice <= A + B)
            db.Operation2("vitaliy.demchenko@student.org", ratingDist(rng));
        else
            db.Operation3();

        ++count;

        auto now = chrono::high_resolution_clock::now();
        if (chrono::duration<double>(now - start).count() >= 10.0)
            break;
    }

    return count;
}

double getMemoryUsageMB() {
    struct mallinfo2 info = mallinfo2();
    return info.uordblks / (1024.0 * 1024.0);
}


void appendToCSV(const ExperimentResult& res, const string& filename = "results.csv") {
    ofstream out(filename, ios::app);
    out << res.version << "," << res.n << "," << res.operations << "," << res.memoryMB << "\n";
}


int main() {
    vector<int> sizes = {100, 1000, 10000, 100000};

    ofstream out("results.csv");
    out << "Version,N,Operations,MemoryMB\n";
    out.close();

    default_random_engine rng(chrono::steady_clock::now().time_since_epoch().count());

    for (int n : sizes) {
        cout << "\n=== Testing with " << n << " students ===\n";

        {
            DatabaseVector db;
            db.StudentsLoad("students_" + to_string(n) + ".csv");

            double memBefore = getMemoryUsageMB();
            long ops = measure(db, 3, 2, 1, rng);
            double memAfter = getMemoryUsageMB();

            appendToCSV({"Vector", n, ops, memAfter - memBefore});
        }

      
        {
            DatabaseHashmap db;
            db.StudentsLoad("students_" + to_string(n) + ".csv");

            double memBefore = getMemoryUsageMB();
            long ops = measure(db, 3, 2, 1, rng);
            double memAfter = getMemoryUsageMB();

            appendToCSV({"Hashmap", n, ops, memAfter - memBefore});
        }

       
        {
            DatabaseHybrid db;
            db.StudentsLoad("students_" + to_string(n) + ".csv");

            double memBefore = getMemoryUsageMB();
            long ops = measure(db, 3, 2, 1, rng);
            double memAfter = getMemoryUsageMB();

            appendToCSV({"Hybrid", n, ops, memAfter - memBefore});
        }
    }


    return 0;
}

