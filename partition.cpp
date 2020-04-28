#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

using namespace std;

int left(int i)
{

    return (2 * i) + 1;
}

int right(int i)
{

    return (2 * i) + 2;
}

int parent(int i)
{ // i-1?
    return (floor(i / 2));
}

void swap(vector<int> *H, int index1, int index2)
{

    for (int i = 0; i < H->size(); i++)
    {
        std::cout << H->at(i) << ' ';
    }
    cout << endl;
    int temp = H->at(index1);
    H->at(index1) = H->at(index2);
    H->at(index2) = temp;

    for (int i = 0; i < H->size(); i++)
    {
        std::cout << H->at(i) << ' ';
    }
    cout << endl;
}

void insert(vector<int> H, int v)
{
    H.push_back(v);
    int N = H.size();
    while (H[parent(N)] < H[N] && H[0] != N)
    {
        swap(&H, H[parent(N)], H[N]);
        N = parent(N);
    }
}

void maxHeapify(vector<int> *H, int N)
{
    //    make_tuple(left(N), right(N));
    int l = left(N);
    int r = right(N);

    int largest = -1;

    if (l < H->size() && H[l] > H[N])
    {
        // cout << "left of " << H[N] << " is" << H[l] << endl;
        // cout << "N = " << N << " and l =" << left(N) << endl;
        largest = l;
    }
    else
    {

        largest = N;
    }
    if (r < H->size() && H[r] > H[largest])
    {
        // cout << "right of " << H[N] << " is" << H[r] << endl;
        largest = r;
    }
    if (largest != N)
    {

        swap(H, N, largest);
        // cout << "swapped " << H[N] << " and " << H[largest] << endl;
        maxHeapify(H, largest);
    }
}

void extractMax(vector<int> *H)
{
    if (!H->empty())
    {
        int max = H->at(0);
        H[0] = H[H->size()];
        H->pop_back(); //size(H) -= 1
        maxHeapify(H, 0);
    }
}

void buildHeap(vector<int> *A)
{

    for (int i = floor(A->size() / 2) + 1; i >= 0; i--)
    {
        cout << "i " << i << endl;
        maxHeapify(A, i);
    }
}

int main(int argc, char **argv)
{

    int flag = atoi(argv[1]);
    int algo = atoi(argv[2]);
    char *file = argv[3];

    int arr[] = {10, 81, 3, 600, 4, 700, 9};
    int n = sizeof(arr) / sizeof(arr[0]);
    vector<int> *a;
    for (int i = 0; i < n; i++)
    {
        a->push_back(arr[0]);
    }

    // sort(vec.begin(), vec.end());
    // reverse(vec.begin(), vec.end());

    // string line;
    // ifstream inFile(file);
    // if (inFile.is_open())
    // {
    //     cout << "file reading business goes here" << endl;
    // }

    // inFile.close();

    cout << "The vector elements are : ";

    for (int i = 0; i < a->size(); i++)
    {
        std::cout << a->at(i) << ' ';
    }

    // now we make a max heap
    buildHeap(a);

    cout << endl
         << "hoe dont do it : ";

    for (int i = 0; i < a->size(); i++)
    {
        std::cout << a->at(i) << ' ';
    }
    cout << endl;
}
