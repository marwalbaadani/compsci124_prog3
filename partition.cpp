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
            maxHeapify(i);
        }
    }
};

int kkAlgo(MaxHeap A)
{

    if (A.H.size() == 1)
    {
        int residue = abs(A.H.at(0));
        cout << "kkAlgo: " << residue << endl;
        return residue;
    }

    int val1 = A.extractMax();
    int val2 = A.extractMax();
    int newVal = val1 - val2;
    A.push(newVal);
    A.maxHeapify(A.H.size());


    /* 
    for testing
    for (int i = 0; i < A.H.size(); i++)
    {
        std::cout << A.H.at(i) << ' ';
    }
    cout << endl; 
    */

    kkAlgo(A);
}

vector<int> randomSignedList()
{
    vector<int> S;
    for (int i = 0; i < 100; i++)
    {
        float rando = rand() % 10 + 1;
        if (rando > 5)
            S.push_back(-1);
        else
            S.push_back(1);
    }

    return S;
}

int rrResidue(MaxHeap H, vector<int> S)
{
    int sum = 0;
    for (int i = 0; i < 100; i++)
    {
        sum += H.H[i] * S[i];
    }
    cout << "sum: " << sum << endl;
    return sum;
}

int rrAlgo(MaxHeap H)
{
    vector<int> S = randomSignedList();
    int sResidue = rrResidue(H, S);

    for (int i = 0; i < 25000; i++)
    {
        vector<int> sPrime = randomSignedList();
        int sPrimeResidue = rrResidue(H, sPrime);
        if (sPrimeResidue == 0) 
        {
            S = sPrime;
            sResidue = sPrimeResidue;
            break;            
        }
        if (abs(sPrimeResidue) < abs(sResidue))
        {
            S = sPrime;
            sResidue = sPrimeResidue;
        }
    }

    int bestS = rrResidue(H, S);
    int bestResidue = abs(bestS);
    cout << bestResidue << endl;

    /*
    For testing
    cout << "The Best S List" << endl;
    for (int i = 0; i < S.size(); i++)
    {
        std::cout << S.at(i) << ' ';
    }
    cout << endl; 
    */
    return bestResidue;

    //or return S?
}


vector<int> randomNList()
{
    vector<int> S;
    for (int i = 0; i < 100; i++)
    {
        float rando = rand() % 100 + 1;
        S.push_back(rando);
    }
    return S;
}

int partitioningResidue(vector<int> H, vector<int> p)
{
    vector<int> aPrime;
    for (int i = 0; i < 100; i++)
    {
        aPrime.push_back(0);
    }
    for (int j = 0; j < 100; j++)
    {
        aPrime[p[j]] = aPrime[p[j]] + H[p[j]];
    }
    MaxHeap A;
    for (int i = 0; i < 100; i++)
        A.push(aPrime[i]);

    return kkAlgo(A);
}

int prepartitionedRR(vector<int> H)
{
    vector<int> p = randomNList();
    int residue = partitioningResidue(H, p);
    for (int i = 0; i < 25000; i++)
    {
        vector<int> preP = randomNList();
        int prePResidue = partitioningResidue(H, preP);
        if (prePResidue < residue)
        {
            p = preP;
            residue = prePResidue;
        }
    }
    return residue;
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

    /*
    For Testing
    cout << "The list of N numbers to partition" << endl;
    for (int i = 0; i < A.H.size(); i++)
    {
        std::cout << A.H.at(i) << ' ';
    }
    cout << endl;
    */

    // pop first two values from maxHeap
    // subtract the lesser value from the greater values
    // push that value back into the max heap
    // run maxHeap on the new array
    // repeat
    // when array.size == 0, return the new array

    // sort(vec.begin(), vec.end());
    // reverse(vec.begin(), vec.end());

    // inFile.close();

    // vector<int> k = randomSignedList();
    // kkAlgo(A);
    rrAlgo(A);
}
