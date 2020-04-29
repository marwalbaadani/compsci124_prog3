#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <sstream>
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
    // for (int i = 0; i < A.H.size(); i++)
    // {
    //     std::cout << A.H.at(i) << ' ';
    // }
    // cout << endl;

    return kkAlgo(A);
}

vector<int> randomSignedList()
{
    vector<int> S;
    for (int i = 0; i < 100; i++)
    {
        int rando = rand() % 10 + 1;
        if (rando > 5)
            S.push_back(-1);
        else
            S.push_back(1);
    }
    return S;
}

int rrResidue(vector<int> H, vector<int> S)
{
    int sum = 0;
    for (int i = 0; i < 100; i++)
    {
        sum += H[i] * S[i];
    }
    return sum;
}

vector<int> rrAlgo(vector<int> H)
{
    vector<int> S = randomSignedList();
    int sResidue = rrResidue(H, S);

    for (int i = 0; i < 25000; i++)
    {
        vector<int> sPrime = randomSignedList();
        int sPrimeResidue = rrResidue(H, sPrime);
        if (sPrimeResidue < sResidue)
            S = sPrime;
    }
    return S;
}

vector<int> randomNList()
{
    vector<int> S;
    for (int i = 0; i < 100; i++)
    {
        int rando = rand() % 100 + 1;
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

// A random move on this state space can be defined as follows.
// Choose two random indices i and j from [1,n] with pi ̸= j and set pi to j.
void neighborPartitioning(vector<int> *p)
{
    int i = rand() % 100 + 1;
    int j = rand() % 100 + 1;
    while (i == j)
        j = rand() % 100 + 1;
    p->at(i) = j;
}

int pHillClimbing(MaxHeap H)
{
    vector<int> p = randomNList();

    int residue = partitioningResidue(H.H, p);
    for (int i = 0; i < 25000; i++)
    {
        vector<int> p2;
        for (int i = 0; i < 100; i++)
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
    //   for testing
    for (int i = 0; i < H.H.size(); i++)
    {
        std::cout << H.H.at(i) << ' ';
    }
    cout << endl;
    return residue;
}

void neighbor(vector<int> *p)
{
    for (int i = 0; i < 100; i++)
    {
        cout << p->at(i) << endl;
    }
    int i = rand() % 100;
    p->at(i) *= -1;
    int half = rand() % 10 + 1;
    if (half > 5)
    {
        int j = rand() % 100;
        while (i == j)
            j = rand() % 100;
        cout << "j " << j << endl;
        p->at(j) *= -1;
    }
}

int hillClimbing(MaxHeap H)
{
    vector<int> S = randomSignedList();
    int residue = rrResidue(H.H, S);
    for (int i = 0; i < 25000; i++)
    {
        vector<int> p2;
        for (int i = 0; i < 100; i++)
        {
            p2.push_back(H.H[i]);
        }
        for (int i = 0; i < 100; i++)
        {
            cout << p2.at(i) << endl;
        }
        neighbor(&p2);

        int residueP = rrResidue(H.H, p2);
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

    // while (getline(inFile, line))
    // {
    //     istringstream ss(line);
    //     A.push(stol(line));
    // }

    A.buildHeap();
    // for (int i = 0; i < A.H.size(); i++)
    // {
    //     std::cout << A.H.at(i) << ' ';
    // }
    // cout << endl;

    // pop first two values from maxHeap
    // subtract the lesser value from the greater values
    // push that value back into the max heap
    // run maxHeap on the new array
    // repeat
    // when array.size == 0, return the new array

    // sort(vec.begin(), vec.end());
    // reverse(vec.begin(), vec.end());

    // inFile.close();

    vector<int> k = randomSignedList();
    kkAlgo(A);
    // int tester = partitioningResidue(randomNList(), randomNList());
    // cout << tester << endl;
    // for (int i = 0; i < tester.size(); i++)
    // {
    //     std::cout << tester.at(i) << ' ';
    // }
    // cout << endl;

    hillClimbing(A);
}
