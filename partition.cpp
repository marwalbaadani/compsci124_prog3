#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

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

        for (int i = 0; i < H.size(); i++)
        {
            std::cout << H.at(i) << ' ';
        }
        cout << endl;
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
        //    make_tuple(left(N), right(N));
        int l = left(N);
        int r = right(N);

        int largest = -1;

        if (l < H.size() && H[l] > H[N])
        {
            // cout << "left of " << H[N] << " is" << H[l] << endl;
            // cout << "N = " << N << " and l =" << left(N) << endl;
            largest = l;
        }
        else
        {

            largest = N;
        }
        if (r < H.size() && H[r] > H[largest])
        {
            // cout << "right of " << H[N] << " is" << H[r] << endl;
            largest = r;
        }
        if (largest != N)
        {
            cout << "swapping " << H[N] << " and " << H[largest] << endl;
            swap(N, largest);
            maxHeapify(largest);
        }
    }
    void push(int key)
    {
        // insert the new element to the end of the vector
        H.push_back(key);

        // get element index and call heapify-up procedure
        int index = H.size() - 1;
        maxHeapify(index);
    }
    void extractMax()
    {
        if (!H.empty())
        {
            int max = H.at(0);
            H[0] = H[H.size()];
            H.pop_back(); //size(H) -= 1
            maxHeapify(0);
        }
    }

    void buildHeap()
    {

        for (int i = floor(H.size() / 2) + 1; i >= 0; i--)
        {
            cout << "i = " << i << endl;
            maxHeapify(i);
        }
    }
};
int main(int argc, char **argv)
{

    int flag = atoi(argv[1]);
    int algo = atoi(argv[2]);
    char *file = argv[3];

    int arr[] = {2, 1, 4, 3, 6, 5};
    int n = sizeof(arr) / sizeof(arr[0]);
    vector<int> a(arr, arr + n);

    MaxHeap pq;

    // Note - Priority is decided by element's value

    pq.push(2);
    pq.push(1);
    pq.push(4);

    pq.push(3);
    pq.push(6);
    pq.push(5);

    // sort(vec.begin(), vec.end());
    // reverse(vec.begin(), vec.end());

    // string line;
    // ifstream inFile(file);
    // if (inFile.is_open())
    // {
    //     cout << "file reading business goes here" << endl;
    // }

    // inFile.close();

    cout
        << "The vector elements are : ";

    for (int i = 0; i < a.size(); i++)
    {
        std::cout << a.at(i) << ' ';
    }
    cout << endl;
    // now we make a max heap

    cout << endl
         << "hoe dont do it : ";

    pq.buildHeap();

    for (int i = 0; i < pq.H.size(); i++)
    {
        std::cout << pq.H.at(i) << ' ';
    }
    cout << endl;
}
