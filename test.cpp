#include <iostream>
#include "csv/csv.h"

using namespace std;

int main() {
    io::CSVReader<3> in("ram.csv");
    in.read_header(io::ignore_extra_column, "vendor", "size", "speed");
    std::string vendor;
    int size;
    double speed;
    while (in.read_row(vendor, size, speed)) {
        // do stuff with the data
        cout << "Vendor: " << vendor << " Size:\t" << size << " Speed: " << speed << endl;
    }
}