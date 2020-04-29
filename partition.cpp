#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <sstream>
#include <random>
#include <ctime>
#include <chrono>
#include <cstdlib>

using namespace std::chrono;
using namespace std;

using namespace std;
int MAX_ITER = 25000;
int SIZE = 100;

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
        int residual = abs(A.H.at(0));
        return residual;
    }

    int val1 = A.extractMax();
    int val2 = A.extractMax();
    int newVal = val1 - val2;
    A.push(newVal);
    A.maxHeapify(A.H.size());

    // print A.H for testing as needed

    return kkAlgo(A);
}

vector<int> randomSignedList()
{
    vector<int> S;
    for (int i = 0; i < SIZE; i++)
    {
        int rando = rand() % 10 + 1;
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
    for (int i = 0; i < SIZE; i++)
    {
        sum += H.H[i] * S[i];
    }

    return sum;
}

int rrAlgo(MaxHeap H)
{
    vector<int> S = randomSignedList();
    int sResidue = rrResidue(H, S);

    for (int i = 0; i < MAX_ITER; i++)
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
    // cout << bestResidue << endl;

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
    for (int i = 0; i < SIZE; i++)
    {
        int rando = rand() % SIZE;
        S.push_back(rando);
    }
    return S;
}

int partitioningResidue(vector<int> H, vector<int> p)
{
    vector<int> aPrime(SIZE);

    for (int j = 0; j < SIZE; j++)
    {
        // @josh... this is so weird why would randomNlist ever return something negative?!!! unless....
        int i = abs(p[j]);
        aPrime[i] += H[i];
    }

    MaxHeap A;
    for (int i = 0; i < SIZE; i++)
        A.push(aPrime[i]);

    return kkAlgo(A);
}

int prepartitionedRR(MaxHeap A)
{
    vector<int> p = randomNList();
    int residue = partitioningResidue(A.H, p);
    for (int i = 0; i < MAX_ITER; i++)
    {
        vector<int> preP = randomNList();
        int prePResidue = partitioningResidue(A.H, preP);
        if (prePResidue == 0)
        {
            p = preP;
            residue = prePResidue;
            break;
        }
        if (prePResidue < residue)
        {
            p = preP;
            residue = prePResidue;
        }
    }
    // cout << "smallestResidue: " << residue << endl;
    return residue;
}

// A random move on this state space can be defined as follows.
// Choose two random indices i and j from [1,n] with pi ̸= j and set pi to j.
void neighborPartitioning(vector<int> *p)
{
    int i = rand() % SIZE;
    int j = rand() % SIZE;
    while (i == j)
        j = rand() % SIZE;
    p->at(i) = j;
}

int pHillClimbing(MaxHeap H)
{
    vector<int> p = randomNList();

    int residue = partitioningResidue(H.H, p);
    for (int i = 0; i < MAX_ITER; i++)
    {
        vector<int> p2;
        for (int i = 0; i < SIZE; i++)
        {
            p2.push_back(p[i]);
        }
        int prePResidue = partitioningResidue(H.H, p2);
        if (prePResidue < residue)
        {
            residue = prePResidue;
            p = p2;
            if (residue == 0)
            {
                break;
            }
        }
    }
    return residue;
}

void neighbor(vector<int> *p)
{
    int i = rand() % SIZE;
    p->at(i) *= -1;
    int half = rand() % 10 + 1;
    if (half > 5)
    {
        int j = rand() % SIZE;
        while (i == j)
            j = rand() % SIZE;

        p->at(j) *= -1;
    }
}

int hillClimbing(MaxHeap H)
{
    vector<int> S = randomSignedList();
    int residue = rrResidue(H, S);
    for (int i = 0; i < MAX_ITER; i++)
    {
        vector<int> p2;
        for (int i = 0; i < SIZE; i++)
        {
            p2.push_back(H.H[i]);
        }
        neighbor(&p2);
        int residueP = rrResidue(H, p2);
        if (residueP < residue)
        {
            residue = residueP;
            S = p2;
            if (residueP == 0)
                break;
        }
    }
    return residue;
}

int simulatedAnnealing(MaxHeap H)
{
    vector<int> S = randomSignedList();
    int s2 = rrResidue(H, S);
    vector<int> s3 = S;
    int s4 = s2;
    for (int i = 0; i < MAX_ITER; i++)
    {
        vector<int> p2;
        for (int i = 0; i < SIZE; i++)
        {
            p2.push_back(s3[i]);
        }
        neighbor(&p2);
        int residueP = rrResidue(H, p2);
        if (residueP < s4 || (rand() < exp(-(residueP - s4) / ((pow(10, 10) * (pow(0.8, floor(i / 300))))))))
        {
            s3 = p2;
            s4 = residueP;
        }
        if (s4 < s2)
        {
            vector<int> p3;
            for (int i = 0; i < SIZE; i++)
            {
                p3.push_back(s3[i]);
            }
            S = p3;
            s2 = s4;
        }
    }
    return s2;
}
int prepartitionedSimulatedAnnealing(MaxHeap H)
{
    vector<int> partitioned = randomNList();
    int s = rrResidue(H, partitioned);
    vector<int> partitioned2 = partitioned;
    int s2 = s;
    for (int i = 0; i < MAX_ITER; i++)
    {
        vector<int> p3;
        for (int i = 0; i < SIZE; i++)
        {
            p3.push_back(partitioned2[i]);
        }
        neighbor(&p3);
        int residueP = partitioningResidue(H.H, p3);
        if (residueP < s || rand() < exp(-(residueP - s) / ((pow(10, 10) * (pow(0.8, floor(i / 300)))))))
        {
            partitioned2 = p3;
            s2 = residueP;
            if (s2 < s)
            {
                vector<int> p4;
                for (int i = 0; i < SIZE; i++)
                {
                    p4.push_back(partitioned2[i]);
                }
                partitioned = p4;
                s = s2;
            }
        }
    }
    return s;
}

int main(int argc, char **argv)
{
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0.0, pow(10, 12));

    int flag = atoi(argv[1]);
    int algo = atoi(argv[2]);
    char *file = argv[3];

    MaxHeap A;

    ofstream outFile(file);
    for (int i = 0; i < SIZE; i++)
    {
        outFile << dis(gen) << endl;
    }

    // Close the file

    string line;
    ifstream inFile(file);
    int a;

    while (getline(inFile, line))
    {
        istringstream ss(line);
        A.push(stol(line));
    }

    A.buildHeap();
    // int residue = 0;
    // switch (algo)
    // {
    // case 0:
    //     residue = kkAlgo(A);
    //     break;
    // case 1:
    //     residue = rrAlgo(A);
    //     break;
    // case 2:
    //     residue = hillClimbing(A);
    //     break;
    // case 3:
    //     residue = simulatedAnnealing(A);
    //     break;
    // case 11:
    //     residue = prepartitionedRR(A);
    //     break;
    // case 12:
    //     residue = pHillClimbing(A);
    //     break;
    // case 13:
    //     residue = prepartitionedSimulatedAnnealing(A);
    //     break;
    // }

    // cout << "heres ya residue: " << residue << endl;

    cout << "TESTING TIME " << endl;

    int nums[7] = {0, 1, 2, 3, 11, 12, 13};
    for (int i = 0; i < 7; i++)
    {
        auto start = steady_clock::now();
        int residues = 0;
        for (int j = 0; j < 100; j++)
        {
            switch (i)
            {
            case 0:
                residues += kkAlgo(A);
                break;
            case 1:
                residues += rrAlgo(A);
                break;
            case 2:
                residues += hillClimbing(A);
                break;
            case 3:
                residues += simulatedAnnealing(A);
                break;
            case 4:
                residues += prepartitionedRR(A);
                break;
            case 5:
                residues += pHillClimbing(A);
                break;
            case 6:
                residues += prepartitionedSimulatedAnnealing(A);
                break;
            }
        }
        int average = residues / 100;
        auto end = steady_clock::now();
        auto elapsed = duration_cast<microseconds>(end - start);
        auto modified = elapsed.count();
        cout << i << " average residue: " << average << endl;
        cout << "elapsed.count() time: " << modified << endl;
        cout << "average elapsed.count() time: " << modified / 10 << endl;
        cout << endl;
    }
}
