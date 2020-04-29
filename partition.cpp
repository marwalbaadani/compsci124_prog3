#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <sstream>
#include <random>
#include <cassert>

using namespace std;
int MAX_ITER = 25000;
int SIZE = 10;

struct MaxHeap
{
    vector<long long int> H;

    int left(long long int i)
    {
        return (2 * i) + 1;
    }

    int right(long long int i)
    {

        return (2 * i) + 2;
    }

    int parent(long long int i)
    {
        return (floor((i - 1) / 2));
    }

    void swap(long long int index1, int index2)
    {
        long long int temp = H[index1];
        H[index1] = H[index2];
        H[index2] = temp;
    }

    void insert(long long int v)
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
        long long int largest = -1;

        if (l < int(H.size()) && H[l] > H[N])
            largest = l;
        else
            largest = N;
        if (r < int(H.size()) && H[r] > H[largest])
            largest = r;
        if (largest != N)
        {
            swap(N, largest);
            maxHeapify(largest);
        }
    }

    void push(int key)
    {
        H.push_back(key);
        int index = H.size() - 1;
        maxHeapify(index);
    }

    long long int extractMax()
    {
        assert(!H.empty());
        if (!H.empty())
        {
            long long int max = H.at(0);
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

long long int kkAlgo(MaxHeap A)
{
    if (A.H.size() == 1)
    {
        long long int residual = abs(A.H.at(0));
        return residual;
    }

    long long int val1 = A.extractMax();
    long long int val2 = A.extractMax();
    long long int newVal = abs(val1 - val2);

    A.push(newVal);
    A.maxHeapify(A.H.size());

    return kkAlgo(A);
}
vector<long long int> randomSignedList()
{
    vector<long long int> S;
    for (int i = 0; i < SIZE; i++)
    {
        int rando = rand() % 10;
        if (rando > 4)
            S.push_back(-1);
        else
            S.push_back(1);
    }

    return S;
}

long long int rrResidue(MaxHeap H, vector<long long int> S)
{
    long long int sum = 0;
    for (int i = 0; i < SIZE; i++)
    {
        sum += H.H[i] * S[i];
    }
    // cout << "sum: " << sum << endl;
    return sum;
}

long long int rrAlgo(MaxHeap H)
{
    vector<long long int> S = randomSignedList();
    long long int sResidue = rrResidue(H, S);

    for (int i = 0; i < MAX_ITER; i++)
    {
        vector<long long int> sPrime = randomSignedList();
        long long int sPrimeResidue = rrResidue(H, sPrime);
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

    long long int bestS = rrResidue(H, S);
    long long int bestResidue = abs(bestS);
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

vector<long long int> randomNList()
{
    vector<long long int> S;
    for (int i = 0; i < SIZE; i++)
    {
        int rando = rand() % SIZE;
        S.push_back(rando);
    }
    return S;
}

long long int partitioningResidue(vector<long long int> H, vector<long long int> p)
{
    vector<long long int> aPrime(SIZE);

    for (int j = 0; j < SIZE; j++)
    {
        int i = abs(p[j]);
        aPrime[i] += H[j];
    }

    MaxHeap A;
    for (int i = 0; i < SIZE; i++)
        A.push(aPrime[i]);

    return kkAlgo(A);
}

long long int prepartitionedRR(MaxHeap A)
{
    vector<long long int> p = randomNList();
    long long int residue = partitioningResidue(A.H, p);
    for (int i = 0; i < MAX_ITER; i++)
    {
        vector<long long int> preP = randomNList();
        long long int prePResidue = partitioningResidue(A.H, preP);
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
void neighborPartitioning(vector<long long int> *p)
{
    int i = rand() % SIZE;
    int j = rand() % SIZE;
    while (i == j)
        j = rand() % SIZE;
    p->at(i) = j;
}

long long int pHillClimbing(MaxHeap H)
{
    vector<long long int> p = randomNList();

    long long int residue = partitioningResidue(H.H, p);
    for (int i = 0; i < MAX_ITER; i++)
    {
        vector<long long int> p2;
        for (int i = 0; i < SIZE; i++)
        {
            p2.push_back(p[i]);
        }
        long long int prePResidue = partitioningResidue(H.H, p2);
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

void neighbor(vector<long long int> *p)
{
    int i = rand() % SIZE;
    p->at(i) *= -1;
    int half = rand() % 10;
    if (half > 4)
    {
        int j = rand() % SIZE;
        while (i == j)
            j = rand() % SIZE;

        p->at(j) *= -1;
    }
}

long long int hillClimbing(MaxHeap H)
{
    vector<long long int> S = randomSignedList();
    long long int residue = rrResidue(H, S);
    for (int i = 0; i < MAX_ITER; i++)
    {
        vector<long long int> p2;
        for (int i = 0; i < SIZE; i++)
        {
            p2.push_back(S[i]);
        }
        neighbor(&p2);
        long long int residueP = rrResidue(H, p2);
        if (residueP < residue)
        {
            residue = residueP;
            S.clear();
            for (int i = 0; i < SIZE; i++)
            {
                S.push_back(p2[i]);
            }
            if (residueP == 0)
                break;
        }
    }
    return residue;
}

long long int simulatedAnnealing(MaxHeap H)
{
    vector<long long int> S = randomSignedList();
    long long int s2 = rrResidue(H, S);
    vector<long long int> s3 = S;
    long long int s4 = s2;
    for (int i = 0; i < MAX_ITER; i++)
    {
        vector<long long int> p2;
        for (int i = 0; i < SIZE; i++)
        {
            p2.push_back(s3[i]);
        }
        neighbor(&p2);
        long long int residueP = rrResidue(H, p2);
        if (residueP < s4 || (rand() < exp(-(residueP - s4) / ((pow(10, 10) * (pow(0.8, floor(i / 300))))))))
        {
            s3 = p2;
            s4 = residueP;
        }
        if (s4 < s2)
        {
            vector<long long int> p3;
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
long long int prepartitionedSimulatedAnnealing(MaxHeap H)
{
    vector<long long int> partitioned = randomNList();
    long long int s = rrResidue(H, partitioned);
    vector<long long int> partitioned2 = partitioned;
    long long int s2 = s;
    for (int i = 0; i < MAX_ITER; i++)
    {
        vector<long long int> p3;
        for (int i = 0; i < SIZE; i++)
        {
            p3.push_back(partitioned2[i]);
        }
        neighbor(&p3);
        long long int residueP = partitioningResidue(H.H, p3);
        if (residueP < s || rand() < exp(-(residueP - s) / ((pow(10, 10) * (pow(0.8, floor(i / 300)))))))
        {
            partitioned2 = p3;
            s2 = residueP;
            if (s2 < s)
            {
                vector<long long int> p4;
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
    long long int num = pow(10, 12);
    uniform_int_distribution<> dis(1, int(num));

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
    // int a;

    while (getline(inFile, line))
    {

        istringstream ss(line);
        A.push(stol(line));
    }

    A.buildHeap();
    // for (int i = 0; i < A.H.size(); i++)
    // {
    //     cout << A.H[i] << ' ';
    // }
    // cout << endl;

    long long int residue = 0;
    switch (algo)
    {
    case 0:
        residue = kkAlgo(A);
        break;
    case 1:
        residue = rrAlgo(A);
        break;
    case 2:
        residue = hillClimbing(A);
        break;
    case 3:
        residue = simulatedAnnealing(A);
        break;
    case 11:
        residue = prepartitionedRR(A);
        break;
    case 12:
        residue = pHillClimbing(A);
        break;
    case 13:
        residue = prepartitionedSimulatedAnnealing(A);
        break;
    }
    cout << abs(residue) << endl;
}
// print A.H for testing as needed
// for (int i = 0; i < A.H.size(); i++)
// {
//     cout << A.H[i] << ' ';
// }
// cout << endl;