#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <random>

using namespace std;

struct MaxHeap
{
    vector<int> H;

    int left(int i)
    {

        return (2 * i) + 1;
    }

    int right(int i)
    {

        return (2 * i) + 2;
    }

    int parent(int i)
    {
        return (floor((i - 1) / 2));
    }

    void swap(int index1, int index2)
    {
        int temp = H[index1];
        H[index1] = H[index2];
        H[index2] = temp;

        // for (int i = 0; i < H.size(); i++)
        // {
        //     std::cout << H.at(i) << ' ';
        // }
        // cout << endl;
    }

    void insert(int v)
    {
        H.push_back(v);
        int N = H.size();
        while (H[parent(N)] < H[N] && H[0] != N)
        {
            swap(H[parent(N)], H[N]);
            N = parent(N);
        }
    }

    void maxHeapify(int N)
    {
        int l = left(N);
        int r = right(N);
        int largest = -1;

        if (l < H.size() && H[l] > H[N])
            largest = l;
        else
            largest = N;
        if (r < H.size() && H[r] > H[largest])
            largest = r;
        if (largest != N)
        {
            swap(N, largest);
            maxHeapify(largest);
        }
    }

    // remind me @josh
    void push(int key)
    {
        H.push_back(key);
        int index = H.size() - 1;
        maxHeapify(index);
    }

    int extractMax()
    {
        assert(!H.empty());
        if (!H.empty())
        {
            int max = H.at(0);
            H[0] = H[H.size() - 1];
            H.pop_back(); //size(H) -= 1
            maxHeapify(0);
            return max;
        }
        else
        {
            throw "error";
        }
    }

    void buildHeap()
    {

        for (int i = floor(H.size() / 2) + 1; i >= 0; i--)
        {
            // cout << "i = " << i << endl;
            maxHeapify(i);
        }
    }
};

int kkAlgo(MaxHeap A)
{

    if (A.H.size() == 1)
    {
        int residual = abs(A.H.at(0));
        cout << residual << endl;
        return residual;
    }

    // pop first two values from maxHeap
    int val1 = A.extractMax();
    int val2 = A.extractMax();
    // subtract the lesser value from the greater values
    int newVal = val1 - val2;
    // push that value back into the max heap
    A.push(newVal);
    // run maxHeap on the new array
    A.maxHeapify(A.H.size());
    // repeat
    // when array.size == 0, return the new array

    // for testing
    for (int i = 0; i < A.H.size(); i++)
    {
        std::cout << A.H.at(i) << ' ';
    }
    cout << endl;

    kkAlgo(A);
}

int main(int argc, char **argv)
{
    random_device rd;  //Will be used to obtain a seed for the random number engine
    mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
    uniform_int_distribution<> dis(0.0, pow(10, 12));

    int flag = atoi(argv[1]);
    int algo = atoi(argv[2]);
    char *file = argv[3];

    MaxHeap A;

    // A.push(2);
    // A.push(1);
    // A.push(4);
    // A.push(3);
    // A.push(6);
    // A.push(5);
    ofstream outFile(file);
    for (int i = 0; i < 100; i++)
    {
        outFile << dis(gen) << endl;
    }

    // Close the file

    string line;
    ifstream inFile(file);
    int a;
    while (inFile >> a)
    {
        A.push(a);
    }

    A.buildHeap();
    for (int i = 0; i < A.H.size(); i++)
    {
        std::cout << A.H.at(i) << ' ';
    }
    cout << endl;

    // pop first two values from maxHeap
    // subtract the lesser value from the greater values
    // push that value back into the max heap
    // run maxHeap on the new array
    // repeat
    // when array.size == 0, return the new array

    // sort(vec.begin(), vec.end());
    // reverse(vec.begin(), vec.end());

    // inFile.close();

    kkAlgo(A);
}
