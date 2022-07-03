#include <iostream>
#include "Array.h"
#include "List.h"
#include "Strlist.h"
#include "Stack.h"
#include "Queue.h"
#include "PQueue.h"
#include "CQueue.h"
#include "test.h"

using namespace std;

int main() {
    /*List<int> arr = {1,2,3,4};
    cout << arr << endl;
    arr << 1 << 2;
    cout << arr << endl;

    List<int> arr2 = {7,8,4,5,1,2,3,4};
    List<int> arr3 = arr2;
    List<int> arr4(10, 1);
    arr3 << 123;
    cout << arr2 << endl;
    cout << arr2 << endl;
    cout << arr2 << endl;

    cout << arr2.length() << endl;
    cout << arr3.length() << endl;

    foreach(int i, arr, {cout << i << " ";});
    //for(int i : arr) cout << i << " ";
    for(int i = 0; i < arr3.length(); i++){
        arr3[i] = 2;
        cout << arr3[i];
    }
    cout << arr2 << endl;

    arr2.pop(0);
    cout << arr2 << endl;
    arr2.pop(-1);
    cout << arr2 << endl;
    arr2.insert(0, 345);
    arr2.insert(1, 12345);
    arr2.insert(-1,888);
    arr2.insert(arr2.length(),9888);
    arr2.pop(2);
    cout << arr2 << endl;

    arr2.clear();
    cout << arr2 << endl;
    arr2.insert(0, 345);
    arr2.insert(1, 12345);
    arr2.insert(1, 1245);
    arr2.pop(-1);
    cout << arr2 << endl;

    cout << Str(arr2 == arr2) << " " << Str(arr2 == arr3);
    cout << arr2.type();*/

    /*Queue<int> s = {1,3,4};
    cout << s << endl;
    cout << s.length() << endl;
    cout << s.pop() << endl;
    cout << s << endl;
    s << 100;
    cout << s << endl;
    cout << s.top() << endl;
    s.pop();
    cout << s.top() << endl;
    s.pop();
    //s.pop();
    cout << s.top() << endl;
    cout << s << endl;
    cout << Type(s);*/

    /*PQueue<int> pq({1,2,3,4,5}, [](const int& a, const int &b)->int{return a - b;});
    cout << pq << endl;
    cout << pq.pop() << endl;
    cout << pq << endl;
    cout << pq.pop() << endl;
    cout << pq << endl;
    pq << 20;
    cout << pq << endl;
    pq << 1;
    cout << pq << endl;
    pq << 16;
    pq = pq + pq;
    PQueue<int> pq1 = pq;
    cout << pq1;
    cout << pq1.pop() << endl;
    pq1 += pq;
    cout << pq1 << endl;

    while(pq1.length() > 0){
        cout << pq1.pop() << endl;
    }
    pq.clear();
    cout << pq << endl;
    for(int i = 0; i < 10; i++) pq << i;
    cout << pq;
    while(pq.length() > 0){
        cout << pq.pop() << endl;
    }
    cout << Type(pq);*/

    /*CQueue<int> cq = {1,2,3,4,5};
    cout << cq << endl;
    cq << 20;
    cout << cq << endl;
    cq.pop();
    cout << cq << endl;
    cq << 30;
    cout << cq << endl;

    CQueue<string> cq1(10);
    cout << cq1 << endl;
    cq1 << "asd";
    cout << cq1 << endl;
    cq1 << "a";
    cout << cq1 << endl;
    cout << cq1.type();

    CQueue<char> cq2(10);
    for(int i = 0; i < 100; i++){
        cq2 << char(i%26 + 'a');
        cout << cq2 << endl;
    }
    cq2.clear();
    for(int i = 0; i < 100; i++){
        cq2 << char(i%26 + 'a');
        cout << cq2 << endl;
    }
    cq2.pop();cq2.pop();cq2 << 't';
    foreach(char c, cq2, {
        cout << c << " ";
    });
    cout << cq2.type();*/

    /*List<List<int>> arr;
    List<int> arr2 = {1,2,3};
    cout << arr2;
    arr << arr2;
    arr << arr2;
    arr << arr2;
    arr << arr2;
    arr << List<int>({1, 2});
    arr << List<int>({3, 4});
    cout << arr[0].length();
    cout << arr.type();
    arr.insert(1,List<int>({5, 4}));
    cout << arr << endl;

    List<List<List<int>>> arrt = {{{1,2},{1,3}},{{1},{2,2,2}},{{6}},{{234},{1}}};
    cout << arrt << endl;
    cout << arrt.pop() << endl;
    cout << arrt << endl;
    cout << arrt[Range(1,3, 1)] << endl;
    cout << arrt << endl;

    List<int> b = {1,2,3,4,5,6};
    cout << b[Range(1,4)];*/



    /*List<int> arr2 = {1,2,3};
    List<int> arr3(arr2);
    cout << arr3;
    cout << Type(arr2);

    List<List<int>> arr5;
    arr5 << List<int>({1, 2});
    arr5 << List<int>({3, 4});
    cout << arr5;
    cout << Type(arr5);*/

    /*List<List<int>> arr4;
    arr4 << List<int>({1, 6, 2});
    arr4 << List<int>({3, 4});
    cout << arr4;*/


    /*Test t;
    for(int i = 0; i < 10; i++) t.arr[i] = i;
    foreach(int i, t, {
        cout << i << " ";
    });
    List<int> arr2 = t;
    cout << arr2;
    foreach(int i, arr2, {
        cout << i << " ";
    });
    List<int> li = arr2;
    cout << li;
    foreach(int i, li, {
        cout << i << " ";
    });

    List<int> li3;
    li3 = li;
    cout << li3;

    List<int> ar;
    ar = arr2;
    cout << ar;

    Stack<int> s;
    s = li;
    cout << endl << s << endl;
    cout << s.pop();
    cout << s.pop();

    Queue<int> q(li);
    cout << q;*/

    cout << replace("HAHahahehahehahehhahahehhehakjasdjkjkhehahhhaaahahehhauyhhhehehhhaheeeeeeuuu",Strlist() << "hahe" << " " << "asd", "HELLO") << endl;
    Strlist sl0 = split("HAHahahehhahah ehheha jasdjkj    khHHeha hhhaaHHHahahehhauyh hHHhehehhhaheeeeeeuuu",Strlist() << "hahe" << " " << "asd" << "HH"<< "eeee" << "eu");
    cout << sl0;
    foreach(string& s, sl0, {
            cout << s << "QQQ";
    });
    cout << lstrip("  \t\r\n   asdasdjhhsajjh  \t\t\r\n  ") << endl;
    cout << rstrip("  \t\r\n   asdasdjhhsajjh  \t\t\r\n  ") << endl;
    cout << strip("  \t\r\n   asdasdjhhsajjh  \t\t\r\n  ") << endl;
    cout << strip("HELLO  P") << endl;


    Strlist sl;
    sl << "hello" << "world" << "asdasdsa";
    cout << sl;
    cout << sl.join("????") << endl;
    Strlist sl2;
    sl2 << "hoadas" << "woad" << "sdsa";
    Strlist sl3 = sl2 + sl;
    cout << sl3;
    sl2 += sl3;
    cout << sl2;
    cout << sl2.join("HEELO") << endl;

    sl.insert(0, "ABC");
    sl.insert(sl.length(), "DFR");
    cout << sl;
    cout << sl.join("..;;") << endl;

    sl.pop(0);
    cout << sl;
    sl.pop(2);
    cout << sl;
    sl.pop(-1);
    cout << sl;
    sl.clear();
    cout << sl;
    //sl << "hoadas" << "woad" << "sdsa";
    cout << sl.length();
    cout << sl;
    sl.insert(0, "ABC");
    sl.insert(sl.length(), "DFR");
    cout << sl;

    char a = 'a';
    cout << Hash(a);
    //cout << sl.toString();

    /*string s;
    getline(cin, s);
    cout << s;
    Strlist sl = split(strip(s));
    cout << sl << sl.length();*/



    std::cout << "Hello, World!" << std::endl;
    return 0;
}
