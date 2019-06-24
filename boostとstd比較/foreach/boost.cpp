#include <bits/stdc++.h>
#include <boost/foreach.hpp>

using namespace std;

int main(void)
{
    chrono::system_clock::time_point start, end;
    vector<int> v(100000, 100);
    start = chrono::system_clock::now();
    BOOST_FOREACH (int x, v)
    {
        cout << x << endl;
    }
    end = chrono::system_clock::now();
    double dur = chrono::duration_cast<chrono::milliseconds>(end - start).count();
    cout << dur << endl;
    return 0;
}
