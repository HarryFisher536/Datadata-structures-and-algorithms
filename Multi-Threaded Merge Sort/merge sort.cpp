#include <iostream>
#include <random>
#include <chrono>
#include <vector>
#include <thread>
#include <numeric>
#include <mutex>
#include <atomic>
#include <condition_variable>

using namespace std;
using std::cout;

// Generates a vector of random integers of given size
vector<int> generateRandomVector(int size) {

    vector<int> randomVector(size);

    // Use random_device to generate seed for Mersenne Twister random number generator
    random_device rd;
    mt19937 gen(rd());

    // Generate uniform distribution of integers from 0 to 999
    uniform_int_distribution<int> dis(0, 999);

    // Fill the vector with random integers
    generate(randomVector.begin(), randomVector.end(), [&]() { return dis(gen); });

    return randomVector;
}

void merge(vector<int>& data, int low, int mid, int high, vector<int>& left, vector<int>& right)
{
    // Calculate the size of the left and right subarrays
    int size_left = mid - low + 1;
    int size_right = high - mid;

    // Copy the values from the left and right subarrays into temporary arrays
    for (int i = 0; i < size_left; i++)
    {
        left[i] = data[i + low];
    }

    for (int j = 0; j < size_right; j++)
    {
        right[j] = data[mid + 1 + j];
    }

    // Merge the two subarrays in ascending order
    int leftIndex = 0; // Index of the left subarray
    int rightIndex = 0; // Index of the right subarray
    int subIndex = low; // Index of the merged subarray

    while (leftIndex < size_left && rightIndex < size_right) {
        if (left[leftIndex] <= right[rightIndex]) {
            data[subIndex] = left[leftIndex];
            leftIndex++;
        }
        else {
            data[subIndex] = right[rightIndex];
            rightIndex++;
        }
        subIndex++;
    }

    // Insert any remaining elements from the left subarray into the merged array
    while (leftIndex < size_left) {
        data[subIndex] = left[leftIndex];
        leftIndex++;
        subIndex++;
    }

    // Insert any remaining elements from the right subarray into the merged array
    while (rightIndex < size_right) {
        data[subIndex] = right[rightIndex];
        rightIndex++;
        subIndex++;
    }
}

void mergeSort(int low, int high, vector<int>& left, vector<int>& right, vector<int>& data)
{
    if (low < high) {
        // Calculate the midpoint of the array
        int mid = low + (high - low) / 2;

        // Recursively sort the left and right halves
        mergeSort(low, mid, left, right, data);
        mergeSort(mid + 1, high, left, right, data);

        // Merge the two sorted halves
        merge(data, low, mid, high, left, right);
    }
}

// thread function for multi-threading
void mergeSortThread(vector<int>& data, int thread_part, int maxThreads)
{
    // calculating low and high
    int low = thread_part * (data.size() / maxThreads);
    int high = (thread_part + 1) * (data.size() / maxThreads) - 1;

    // evaluating mid point
    int mid = low + (high - low) / 2;

    // allocate memory for left and right vectors
    vector<int> left(mid - low + 1);
    vector<int> right(high - mid);

    if (low < high) {
        mergeSort(low, mid, left, right, data);
        mergeSort(mid + 1, high, left, right, data);
        merge(data, low, mid, high, left, right);
    }
}

void mergeSortHelper(vector<int>& data, int maxThreads)
{
    if (maxThreads > 1) {
        // create threads and call mergeSortThread function
        vector<thread> threads;
        for (int i = 0; i < maxThreads; i++) {
            threads.push_back(thread(mergeSortThread, ref(data), i, maxThreads));
        }
        // join the threads
        for (int i = 0; i < maxThreads; i++) {
            threads[i].join();
        }
        // merge the sorted sub-arrays
        vector<int> left(data.size() / 2);
        vector<int> right(data.size() - data.size() / 2);
        merge(data, 0, data.size() / 2 - 1, data.size() - 1, left, right);
    }
    else
    {
        // if max_threads is 1, just call mergeSort function
        vector<int> left(data.size() / 2);
        vector<int> right(data.size() - data.size() / 2);
        mergeSort(0, data.size() - 1, left, right, data);
    }
}


void verifySorted(const std::vector<int>& data, int maxThreads) {
    // Calculate the chunk size based on the maximum number of threads
    std::size_t chunkSize = data.size() / maxThreads;

    // If the data size is not evenly divisible by the maximum number of threads, increase the chunk size by 1
    if (data.size() % maxThreads != 0)
    {
        chunkSize++;
    }

    // Calculate the number of chunks based on the chunk size
    std::size_t numChunks = data.size() / chunkSize;
    if (data.size() % chunkSize != 0)
    {
        numChunks++;
    }

    // Create a vector of threads with a maximum size of maxThreads
    std::vector<std::thread> threads(maxThreads);

    // Create a mutex and condition variable to protect the isSorted flag
    std::mutex mutex;
    std::condition_variable cv;
    bool isSorted = true;

    // Loop through the chunks, processing up to maxThreads at a time
    for (std::size_t i = 0; i < numChunks && isSorted; i += maxThreads)
    {
        // Determine the start and end indices for the current chunk
        std::size_t start = i * chunkSize;
        std::size_t end = std::min(start + chunkSize - 1, data.size() - 1);

        // Clear the thread vector for the current chunk
        threads.clear();

        // Loop through the indices in the chunk, creating a thread for each one
        for (int j = 0; j < maxThreads && start + j * chunkSize <= end; j++)
        {
            // Create a thread to check the elements in the current index range
            threads.push_back(std::thread([&]() {
                for (std::size_t k = start + j * chunkSize + 1; k <= end; k++)
                {
                    // Lock the mutex to protect the isSorted flag
                    std::unique_lock<std::mutex> lock(mutex);
                    if (data[k] < data[k - 1])
                    {
                        // If the elements are out of order, set isSorted to false
                        isSorted = false;
                        // Break out of the loop since the order is already incorrect
                        break;
                    }
                }
                // Notify the condition variable after the thread has completed
                cv.notify_all();
                }));
        }

        // Wait for all of the threads to complete
        for (auto& thread : threads)
        {
            thread.join();
        }

        // If the isSorted flag is false, break out of the loop early
        if (!isSorted) break;
    }

    // Print the final status of the isSorted flag
    if (!isSorted)
    {
        std::cout << "The vector is not sorted." << std::endl;
    }
}




long long findFastestTime(vector<long long>& results, int maxThreads) {
    // Calculate the chunk size for each thread
    int chunkSize = results.size() / maxThreads;

    // Vector to hold the fastest times found by each thread
    vector<long long> fastestTimes(maxThreads);

    // Vector to hold the threads
    vector<thread> threads(maxThreads);

    // Function to find the fastest time in a chunk of the results vector
    auto findFastestInChunk = [&](int startIndex, int endIndex, int threadIndex) {
        long long fastest = LLONG_MAX;
        for (int i = startIndex; i < endIndex; i++)
        {
            if (results[i] < fastest)
            {
                fastest = results[i];
            }
        }
        fastestTimes[threadIndex] = fastest;
    };

    // Start the threads to search for the fastest time in each chunk
    int startIndex = 0;
    for (int i = 0; i < maxThreads; i++)
    {
        int endIndex = startIndex + chunkSize;
        if (i == maxThreads - 1)
        {
            endIndex = results.size();
        }
        threads[i] = thread(findFastestInChunk, startIndex, endIndex, i);
        startIndex = endIndex;
    }

    // Wait for the threads to finish
    for (auto& thread : threads)
    {
        thread.join();
    }

    // Find the fastest time among the fastest times found by each thread
    long long fastest = *min_element(fastestTimes.begin(), fastestTimes.end());

    return fastest;
}

long long getMedian(vector<long long>& results) {
    // Sort the vector
    sort(results.begin(), results.end());

    // Calculate the index of the median
    int size = results.size();
    int mid = size / 2;

    // If the size of the vector is even, return the average of the two middle values
    if (size % 2 == 0) {
        return (results[mid - 1] + results[mid]) / 2;
    }

    // If the size of the vector is odd, return the middle value
    return results[mid];
}


void displayProgressBar(int percent) {
    // Define the width of the progress bar.
    int progressBarWidth = 50;

    // Display the opening bracket of the progress bar.
    cout << "[";

    // Calculate the current position of the progress bar.
    int currentPosition = progressBarWidth * percent / 100;

    // Iterate over the progress bar and print the appropriate symbols.
    for (int i = 0; i < progressBarWidth; ++i) {
        if (i < currentPosition) cout << "=";
        else if (i == currentPosition) cout << ">";
        else cout << " ";
    }

    // Display the closing bracket and the current percentage of completion.
    cout << "] " << percent << "%" << "\r";
    cout.flush();

    // If the progress reaches 100%, print a message indicating that the vectors are sorted.
    if (percent == 100) cout << "\n Vectors are sorted" << endl;
}




int main() {

    int vectorSize = 1000000;

    int maxThreads = 16;

    int repititions = 50;

    vector<long long> results{};

    int choice;
    bool useDefault = true;

    cout << " Default settings:" << endl;
    cout << "Vector size: " << vectorSize << endl;
    cout << "Maximum number of threads: " << maxThreads << endl;
    cout << "Number of repetitions: " << repititions << endl;


    cout << "Please choose an option:" << endl;
    cout << "1. Use default settings" << endl;
    cout << "2. Edit settings \n" << endl;
    cin >> choice;

    while (choice != 1 && choice != 2);

    if (choice == 2) {
        useDefault = false;
        cout << "Enter vector size: ";
        cin >> vectorSize;
        cout << "Enter maximum number of threads: ";
        cin >> maxThreads;
        cout << "Enter number of repetitions: ";
        cin >> repititions;
    }


    cout << "\n" << "Using the following settings : " << endl;
    cout << "Vector size: " << vectorSize << endl;
    cout << "Maximum number of threads: " << maxThreads << endl;
    cout << "Number of repetitions: " << repititions << endl;

    if (useDefault) {
        cout << "Using default settings..." << endl;
    }

    for (int n = 0; n < repititions; n++)
    {

        vector<int> data = generateRandomVector(vectorSize);

        // Time how long it takes to sort the vector using merge sort
        auto start = chrono::high_resolution_clock::now();
        mergeSortHelper(data, maxThreads); // run merge sort with threads
        auto end = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::nanoseconds>(end - start).count();

        results.push_back(duration);

        verifySorted(data, maxThreads);

        int progress = (n + 1) * 100 / repititions;
        displayProgressBar(progress);
    }


    long long median = getMedian(results);
    long long fastest = findFastestTime(results, maxThreads);

    cout << "Median value: " << median << " ns" << endl;
    cout << "Fastest time taken: " << fastest << " ns" << endl;

    return 0;
}