#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char **argv)
{

    int flag = atoi(argv[1]);
    int algo = atoi(argv[2]);
    char *file = argv[3];

    string line;
    ifstream inFile(file);
    if (inFile.is_open())
    {
        cout << "file reading business goes here" << endl;
    }

    inFile.close();
}