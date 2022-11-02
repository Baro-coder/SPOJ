#include <iostream>
#include <fstream>

const char * stream_in  = "./data/tbdw.in";
const char * stream_out = "./data/tbdw.out";


int * execute(int * root, char opt, int val)
{
    std::cout << "OPT: " << opt << " | " << "VAL: " << val << std::endl;
    return nullptr;
}


void testHandle(int testNr)
{
    std::cout << "test " << testNr << std::endl;

    int * root = nullptr;

    int n;
    std::cin >> n;

    for (int i = 0; i < n; i++)
    {
        char opt = '\0';
        int val = 0;
        std::cin >> opt >> val;
        root = execute(root, opt, val);
    }
}


// ------------
// -- DRIVER --
int main()
{
    // Change I/O streams
    // -- new I/O sources
    std::ifstream in(stream_in);
    std::ofstream out(stream_out);

    // -- optional performance optimizations
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);

    // -- redirect I/O streams
    std::cin.rdbuf(in.rdbuf());
    std::cout.rdbuf(out.rdbuf());

    // Main program
    // -- tests count
    int t = 0;
    std::cin >> t;
    for (int i = 0; i < t; i++)
    {
        testHandle(i+1);
    }

    return 0;
}