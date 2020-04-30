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
int SIZE = 100;
std::random_device rd;
std::mt19937 gen(rd());
std::uniform_real_distribution<> dis(0.0, 1.0);

struct MaxHeap
{
    vector<long long int> H;

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

    void swap(long long int index1, int index2)
    {
        long long int temp = H[index1];
        H[index1] = H[index2];
        H[index2] = temp;
    }

    void push(long long int v)
    {
        H.push_back(v);
        int N = H.size() - 1;
        while (N != 0 && H[parent(N)] < H[N])
        {
            swap(parent(N), N);
            N = parent(N);
        }
    }

    void maxHeapify(int N)
    {
        int l = left(N);
        int r = right(N);
        long long int largest = N;

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
    long long int newVal = val1 - val2;

    A.push(newVal);
    A.maxHeapify(A.H.size());

    return kkAlgo(A);
}

vector<int> randomSignedList()
{

    vector<int> S;
    for (int i = 0; i < SIZE; i++)
    {
        float rando = dis(gen);
        if (rando > .5)
            S.push_back(-1);
        else
            S.push_back(1);
    }
    return S;
}

long long int rrResidue(MaxHeap H, vector<int> S)
{
    long long int sum = 0;
    for (int i = 0; i < SIZE; i++)
    {
        sum += H.H[i] * S[i];
    }
    return abs(sum);
}

long long int rrAlgo(MaxHeap H)
{
    vector<int> S = randomSignedList();
    long long int sResidue = rrResidue(H, S);

    for (int i = 0; i < MAX_ITER; i++)
    {
        vector<int> sPrime = randomSignedList();
        long long int sPrimeResidue = rrResidue(H, sPrime);
        if (sPrimeResidue < sResidue)
        {
            sResidue = sPrimeResidue;
            if (sResidue == 0)
            {
                break;
            }
        }
    }

    return sResidue;
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

long long int partitioningResidue(vector<long long int> H, vector<int> p)
{
    vector<long long int> aPrime(SIZE);
    for (int i = 0; i < SIZE; i++)
    {
        aPrime[i] = 0;
    }

    for (int i = 0; i < SIZE; i++)
    {
        aPrime[p[i]] += H[i];
    }

    MaxHeap A;
    for (int i = 0; i < SIZE; i++)
        A.push(aPrime[i]);

    A.buildHeap();
    return kkAlgo(A);
}

long long int prepartitionedRR(MaxHeap A)
{
    vector<int> p = randomNList();
    long long int residue = partitioningResidue(A.H, p);
    for (int i = 0; i < MAX_ITER; i++)
    {
        vector<int> preP = randomNList();
        long long int prePResidue = partitioningResidue(A.H, preP);
        if (prePResidue < residue)
        {
            residue = prePResidue;
        }
    }

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

long long int pHillClimbing(MaxHeap H)
{
    vector<int> p = randomNList();

    long long int residue = partitioningResidue(H.H, p);
    for (int i = 0; i < MAX_ITER; i++)
    {
        vector<int> p2;
        for (int i = 0; i < SIZE; i++)
        {
            p2.push_back(p[i]);
        }
        neighborPartitioning(&p2);
        long long int prePResidue = partitioningResidue(H.H, p2);
        if (prePResidue < residue)
        {
            residue = prePResidue;
            for (int i = 0; i < SIZE; i++)
            {
                p.push_back(p2[i]);
            }

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
    float half = dis(gen);
    if (half > .5)
    {
        int j = rand() % SIZE;
        while (i == j)
            j = rand() % SIZE;
        p->at(j) *= -1;
    }
}

long long int hillClimbing(MaxHeap H)
{
    vector<int> S = randomSignedList();
    long long int residue = rrResidue(H, S);

    for (int i = 0; i < MAX_ITER; i++)
    {

        vector<int> p2;
        for (int i = 0; i < SIZE; i++)
        {
            p2.push_back(S[i]);
        }
        neighbor(&p2);

        long long int residueP = rrResidue(H, p2);

        if (abs(residueP) < abs(residue))
        {
            residue = residueP;
            for (int i = 0; i < SIZE; i++)
            {
                S.push_back(p2[i]);
            }

            if (residue == 0)
                break;
        }
    }
    return residue;
}

long long int simulatedAnnealing(MaxHeap H)
{
    vector<int> S = randomSignedList();
    long long int S_residue = rrResidue(H, S);
    vector<int> cur = S;
    long long int cur_residue = S_residue;
    for (int i = 0; i < MAX_ITER; i++)
    {
        vector<int> p;
        for (int i = 0; i < SIZE; i++)
        {
            p.push_back(cur[i]);
        }
        neighbor(&p);
        long long int residueP = rrResidue(H, p);
        if (residueP < cur_residue || (dis(gen) < exp(-(residueP - cur_residue) / ((pow(10, 10) * (pow(0.8, floor(i / 300))))))))
        {
            for (int i = 0; i < SIZE; i++)
            {
                cur.push_back(p[i]);
            }

            cur_residue = residueP;
        }
        if (cur_residue < S_residue)
        {
            for (int i = 0; i < SIZE; i++)
            {
                S[i] = cur[i];
            }
            S_residue = cur_residue;
        }
    }
    return S_residue;
}

long long int prepartitionedSimulatedAnnealing(MaxHeap H)
{
    vector<int> S = randomNList();
    long long int S_residue = partitioningResidue(H.H, S);
    vector<int> cur = S;
    long long int cur_residue = S_residue;
    for (int i = 0; i < MAX_ITER; i++)
    {
        vector<int> p;
        for (int i = 0; i < SIZE; i++)
        {
            p.push_back(cur[i]);
        }
        neighbor(&p);
        long long int residueP = partitioningResidue(H.H, p);
        if (residueP < cur_residue || (dis(gen) < exp(-(residueP - cur_residue) / ((pow(10, 10) * (pow(0.8, floor(i / 300))))))))
        {
            for (int i = 0; i < SIZE; i++)
            {
                cur.push_back(p[i]);
            }

            cur_residue = residueP;
        }
        if (cur_residue < S_residue)
        {
            for (int i = 0; i < SIZE; i++)
            {
                S[i] = cur[i];
            }
            S_residue = cur_residue;
        }
    }
    return S_residue;
}

int main(int argc, char **argv)
{
    int flag = atoi(argv[1]);
    (void)flag;
    int algo = atoi(argv[2]);
    char *file = argv[3];

    MaxHeap A;

    string line;
    ifstream inFile(file);
    long long int a;

    while (inFile >> a)
    {
        A.push(a);
    }
    inFile.close();
    A.buildHeap();

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
