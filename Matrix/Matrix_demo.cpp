
#include <cstddef>
#include <iostream>
#include "Matrix.hpp"

using namespace std;

int main( )
{
    vtsu::Matrix<double> m{ 10, 10 };

    cout << "dimension = (" << m.rows( ) << ", " << m.columns( ) << ")" << endl;
    
    return EXIT_SUCCESS;
}
