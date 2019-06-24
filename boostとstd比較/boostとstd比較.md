# C++ boost libraryとstandard libraryの速度比較

boostとstdで共通している関数、コンテナでどちらの方が処理時間が早いのか気になったので記事にしてみます。

1.std::for_eachとBOOST_FOREACHマクロ

**std::for_each**
```c++
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
```

**BOOST_FOREACH**
```c++
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
```

std::foreachを三回行なった結果が、<br>
1178ms<br>
1158ms<br>
1056ms<br>

BOOST_FOREACHが、<br>
1625ms<br>
1454ms<br>
1437ms<br>

また、std::for_eachとforループ（範囲for文)の場合の結果は,

[C++のvectorを使った二重ループの速度比較](https://qiita.com/takahiro_itazuri/items/1b7731aad72359d9b43e)

