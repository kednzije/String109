#include <iostream>
#include <vector>
#include <thread>
#include <algorithm>
#include <functional>
#include <numeric>
#include <cmath>
using namespace std;
template<typename Iterator, typename T>
struct accumulate_block{
    void operator() (Iterator first, Iterator last, T& init) {
        init = accumulate(first, last, init);
    }
};

template<typename Iterator, typename T>
T parallel_accumulate(Iterator first, Iterator last, T init) {
    unsigned long const length = distance(first, last);
    if(!length) return init;

    unsigned long const min_per_thread = 25;
    unsigned long const max_threads = (length + min_per_thread - 1) / min_per_thread;

    unsigned long const hardware_threads = thread::hardware_concurrency();

    unsigned long const num_threads = min(hardware_threads != 0 ? hardware_threads : 2, max_threads);

    unsigned long const block_size = length / num_threads;

    vector<T> ans(num_threads);
    vector<thread> threads(num_threads - 1);

    Iterator block_start = first;
    for(unsigned long i = 0; i < num_threads - 1; i++) {
        Iterator block_end = block_start;
        advance(block_end, block_size);
        threads[i] = thread(accumulate_block<Iterator, T>(), block_start, block_end, ref(ans[i]));
        block_start = block_end;
    } 
    for_each(threads.begin(), threads.end(), mem_fn(&thread::join));

    accumulate_block <Iterator, T> ()(block_start, last, ans[num_threads - 1]);

    return accumulate(ans.begin(), ans.end(), init);
}

void test() {
    vector<int> a;
    for(int i = 1; i <= 10000000; i++)
        a.push_back(i);
    int ans_1 = 0;
    int start = clock();
    ans_1 = parallel_accumulate(a.begin(), a.end(), ans_1);
    int end = clock();
    cout << "parallel_accumulate cost " << end - start << endl;
    cout << "the answer is " << ans_1 << endl;
    cout << "----------------------------------------------------------------------------------------" << endl;
    int ans_2 = 0;
    start = clock();
    ans_2 = accumulate(a.begin(), a.end(), ans_2);
    end = clock();
    cout << "accumulate cost " << end - start << endl;
    cout << "the answer is " << ans_2 << endl;
    cout << "----------------------------------------------------------------------------------------" << endl;
}

int main() {
    test();
    return 0;
}