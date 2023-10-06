#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

// Outline for Gallery::print:

void print(std::ostream& os)
{
    std::vector<std::istringstream> streams;
    std::vector<std::size_t> widths;
    
    for (auto plot : plots)
    {
        std::ostringstream oss;
        plot->print(oss);
        streams.emplace_back(oss.str());
        widths.push_back(plot->get_width());
    }
    
    os << std::setfill(' ') << std::left;
    
    bool processing { true };
    while (processing)
    {
        processing = false;
        for (std::size_t i { 0 }; i < streams.size(); ++i)
        {   
            std::string line { };
            if (/* we could read the next line from streams[i] */)
            {
                processing = true;
            }
            
            os << std::setw(widths[i]) << line << " | ";
        }
        os << std::endl;
    }
}

/*

Expected output:

C++ Books         =============
Python Books      =====
C# Books          ===
Java Books        ==
Theoretical Books ===========

Apples  =======     |                          + | 
Oranges ===         |                 +          | 
Bananas =========== |          +                 | 
Pears   =====       |     +                      | 
                    |  +                         | 
                    | +                          | 
                    |  +                         | 
                    |     +                      | 
                    |          +                 | 
                    |                 +          | 
                    |                          + | 
                    |                            | 

          +
             +
               +
                  +
                   +
                    +
                   +
                  +
               +
             +
          +
      +
    +
 +
+
+
+
 +
    +
      +
         +


 */

int main()
{
    std::vector</* Plot */> plots {
        Bar_Plot {
            { "C++ Books", 13 },
            { "Python Books", 5 },
            { "C# Books", 3 },
            { "Java Books", 2 },
            { "Theoretical Books", 11 }
        },
        
        Gallery {
            Bar_Plot {
                { "Apples", 7 },
                { "Oranges", 3 },
                { "Bananas", 11 },
                { "Pears", 5 }
            },
            Function_Plot {
                [](unsigned x)
                {
                    x -= 5;
                    return x * x;
                }
            },
        },
        
        Function_Plot {
            [](unsigned x) -> unsigned
            {
                return (10.0*(std::sin(3.1415926535 * x / 10) + 1.0));
            },
            0, 20
        }        
    };
    
    for (auto plot : plots)
    {
        plot->print(std::cout);
        std::cout << std::endl;
    }
}