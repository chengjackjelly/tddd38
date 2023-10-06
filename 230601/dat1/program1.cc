#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

struct Product
{
    std::string name;
    double weight;
    double volume;

    double density()
    {
        return weight / volume;
    }
    
};

/* Examples:

$ ./a.out factory.txt 1000 1200 12
Found a faulty sequence after 87 products:
Watermelon [4 kg, 0.009 m^3]
Peach [0.25 kg, 0.0002 m^3]
Strawberry [0.05 kg, 4e-05 m^3]
Kiwi [0.08 kg, 6e-05 m^3]
Orange [0.55 kg, 0.0004 m^3]
Grapes [0.3 kg, 0.00021 m^3]
Kiwi [0.17 kg, 0.000105 m^3]
Kiwi [0.16 kg, 0.0001 m^3]
Banana [0.25 kg, 0.0003 m^3]
Strawberry [0.12 kg, 7.5e-05 m^3]
Banana [0.15 kg, 0.0002 m^3]
Banana [0.3 kg, 0.00035 m^3]

 ./a.out factory.txt 900 1500 5
Found a faulty sequence after 93 products:
Kiwi [0.17 kg, 0.000105 m^3]
Kiwi [0.16 kg, 0.0001 m^3]
Banana [0.25 kg, 0.0003 m^3]
Strawberry [0.12 kg, 7.5e-05 m^3]
Banana [0.15 kg, 0.0002 m^3]

$ ./a.out factory.txt 0 10000 100
No faults found

*/

int main(int argc, char** argv)
{
    if (argc < 5)
    {
        std::cerr << "USAGE: " << argv[0] << " FILE LOWER UPPER THRESHOLD\n";
        return 1;
    }
}