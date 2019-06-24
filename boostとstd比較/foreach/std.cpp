#include <bits/stdc++.h>

using namespace std;

int main(void)
{
    chrono::system_clock::time_point start, end;
    vector<int> v(100000, 100);
    start = chrono::system_clock::now();
    for_each(v.begin(), v.end(), [](int x) { cout << x << endl; });
    end = chrono::system_clock::now();
    double dur = chrono::duration_cast<chrono::milliseconds>(end - start).count();
    cout << dur << endl;
    return 0;
}
