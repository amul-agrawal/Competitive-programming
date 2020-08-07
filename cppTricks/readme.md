# Cpp Tricks
Here I try to put cpp stuff that i find useful and will like to add to my cpp codes.
## General
### Fast I/O
`ios_base::sync_with_stdio(false);`

This command turns off iostreams and stdio synchronization ([description](http://cplusplus.com/reference/iostream/ios_base/sync_with_stdio/)). It is on by default, which means that calls to iostreams and stdio functions can be freely interleaved even for the same underlying stream. When synchronization is turned off, mixing calls is no longer allowed, but iostreams can potentially operate faster.

The second optimization is about untying `cin` and `cout`:

`cin.tie(NULL);`

By default, `cin` is tied to `cout`, which means that `cout` is flushed before any operation on `cin` ([description](http://cplusplus.com/reference/iostream/ios/tie/)). Turning this feature off allows iostreams, again, to operate faster. One should be careful with this optimization in interactive problems: it should either not be used, or an explicit `flush` should be issued each time.

I should also note that frequent use of `endl` also negatively affects iostreams performance, because `endl` not only outputs a newline character, but also flushes the stream's buffer ([decription](http://cplusplus.com/reference/iostream/manipulators/endl/)). You can simply output `'\n'` or `"\n"` instead of `endl`.

### Use of auto keyword
The auto keyword specifies that the type of the variable that is being declared will be automatically deducted from its initializer. In case of functions, if their return type is auto then that will be evaluated by return type expression at runtime.

I will just give a few examples where i use auto. To learn more go [here.](https://docs.microsoft.com/en-us/cpp/cpp/auto-cpp?view=vs-2019)

Common use cases in cp:
- To declare a variable.
    ```cpp
    int j = 0;  // Variable j is explicitly type int.
    auto k = 0; // Variable k is implicitly type int because 0 is an integer.
    ```
    The following declarations are equivalent, but the second declaration is simpler than the first. One of the most compelling reasons to use the auto keyword is simplicity.
    ```cpp
    map<int,list<string>>::iterator i = m.begin();
    auto i = m.begin();
    ```
    Also note `auto p = {1,2}; cout<<p.ff;` gives error as p is not of type `pair<int,int>` but of type `initializer_list<int>`. Generally don't try to initialize variables with auto.
- In for loop.
    ```cpp
    // x references to each element of Arr one by one.
    for(auto& x:Arr) 
    {
        cin>>x;
    }
    // x is a copy of each element of Arr one by one.
    for(auto x:Arr)
    {
        cout<<x<<" ";
    }
    ```
    Iterate over map.
    ```cpp
    map<int, string> m;
    for (auto [key, value] : m)
    cout << "key: " << key << '\n' << "value: " << value << '\n';
    ```
    We can use those `[]` to unpack each element of a container. `C++17 required` 
- To declare lambdas
    ```cpp
    auto multiply = [](auto a, auto b) {return a*b;};
    ```
### Range delete with iterators
Don't do the following because once you delete `it`, you can't increment it.
```cpp
// erasing from [it1,it2)
for(auto it=it1;it!=it2;it++)
{
    st.erase(it); // this works as it returns an iterator to next element;
}
```
For the containers that don't have range delete methods we can use the following:
```cpp
// erasing from [it1,it2)
for(auto it=it1;it!=it2;)
{
    it=st.erase(it); // this works as it returns an iterator to next element;
}
```
We can also use this when we want to delete elements from a range that follow a condition.
```cpp
// erasing from [it1,it2)
for(auto it=it1;it!=it2;)
{
    if(condition())
    {
        it=st.erase(it); // this works as .erase returns an iterator to next element;
    }
    else
    {
        it++;
    }
}
```
### Print a binary representation of a number
If you want to print, say, last 20 bits of a number, it's not necessary to write smth like
```cpp 
void show_binary(int n) {
    for (int i = 0; i < 20; ++i) {
        if((1LL<<i)&n) cout<<1;
        else cout<<0;
    }
    cout << "\n";
}
```
Instead, one can simply write
```cpp
cout << bitset<20>(n) << "\n"; // for n=10 it prints 01010000000000000000
```
However, you need to fix the number of bits to show (which is usually not a problem because in most of the cases you need it for debug purposes) and get used to the order where the lowest bit is the rightmost (which is actually a natural order for a binary representation of a number, but not so natural if you consider a mask as a sort of a boolean vector).

Also, if you want to print an octal or a hexadecimal representation of a number, you can simply write `cout << oct << n << "\n"` and `cout << hex << n << "\n"`, respectively. To return back to ~~normal~~ decimal, use `cout << dec`.
### Assigning values to a structure instance
```cpp
struct node {
    int a,b,c;
};
node n1={1,2,3}; // this makes n1.a=1,n1.b=2,n1.c=3;
```
### useful stl functions
- `std::merge`
    If you want to build a segment tree where each node contains a sorted list of values from the corresponding range then on its initialization you may need to merge two vectors several times (or if you implement your own merge sort). Some of you, probably, write some code like this:
    ```cpp
    for (int v = n - 1; v > 0; --v) {
        int i = 0, j = 0;
        while (i < (int)nodes[2 * v].size() || j < (int)nodes[2 * v + 1].size()) {
            if (j == (int)nodes[2 * v + 1].size() || (i < (int)nodes[2 * v].size() && nodes[2 * v][i] < nodes[2 * v + 1][j])) {
                nodes[v].push_back(nodes[2 * v][i++]);
            } else {
                nodes[v].push_back(nodes[2 * v + 1][j++]);
            }
        }
    }
    ```
    However, this code can be shortened:
    ```cpp
    for (int v = n - 1; v > 0; --v) {
        nodes[v].resize(nodes[2 * v].size() + nodes[2 * v + 1].size());
        merge(all(nodes[2 * v]), all(nodes[2 * v + 1]), nodes[v].begin());
    }
    ```
    Basically, `std::merge` takes 5 arguments: begin and end of one interval to merge, begin and end of the second interval to merge, and where to write the result. Don't forget to allocate the required memory (the purpose of `.resize()` in the code above)!
- `std::fill` and `std::iota`
    Many of you know that if one wants to fill a piece of memory with a specific byte, they can use memset. It's quite fast and can be used to fill some (usually 1-dimensional) C-arrays by zeroes and minus ones. What if you want to fill a container by ones? The answer is as easy as pie:
    ```cpp
    fill(all(vec), 1);
    ```
    And if you want to fill it by consecutive numbers then:
    ```cpp
    iota(all(vec), 0); // vec[0]=0, vec[1]=1 ....
    ```
- `std::unique`
    This is also well known, but not as well as I want, so I leave it here. `std::unique(begin, end)` goes from begin to end, removes consecutive duplicates and returns the end of the resulting iterator range. So, for example, if `vec = {1, 1, 2, 2, 3, 2, 1}`, then `unique(all(vec))` makes it equal `{1, 2, 3, 2, 1, ?, ?}` (where ? is not known, but probably the last two symbols are `2` and `1`) and returns `vec.begin() + 5`. Usually, to make a vector containing only its unique elements, one writes
    ```cpp
    sort(all(vec));
    vec.resize(unique(all(vec)) - vec.begin());
    ```
## Not Trick but General things i forget everytime
### freopen
Many contests require you to output to a file rather than to stdout.
syntax: `FILE * freopen ( const char * filename, const char * mode, FILE * stream );`
```cpp
freopen("input.txt","r",stdin); // read from input.txt using cin
freopen("output.txt","w",stdout); // write to output.txt using cout
```
[more details](https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/freopen-wfreopen?view=vs-2019)
### getline
I use it to read line inputs.
syntax: `istream& getline(istream& is, string& str, char delim);` delim has a default value of `"\n"`.
```cpp
string s;
getline(cin,s);
```
Mistakes i make when i use this:
1. don't forget to read the last `"\n"`. The following code only reads `t-1` strings as during the 1st iteration of while loop getline reads the left out `"\n"` character by `cin` in the iostream when reading `t`.
    ```cpp
    int t;
    cin>>t;
    while(t--)
    {
        string s;
        cin>>s;
        getline(cin,s);
    }
    ```
    fix:
    ```cpp
    int t;
    cin>>t;
    string dummy;
    getline(cin,dummy);
    while(t--)
    {
        string s;
        cin>>s;
        getline(cin,s);
    }
    ```
2. When I read blank lines. Remember line containing space character is not considered blank. Often sites don't have correct input in sample input cases, so don't blindly copy those inputs. we can just check blank lines with `s.length()==0` condition.
## After C++17
### Introducing variables inside an `if` statement
Now in c++17 you can declare variables inside an if statement. The scope of those variables is limited to all the `else if` and `else` branches of that if statement.
```cpp
if(int x=func();check(x))
{
    use_x(x);
}
``` 
### Finding min/max of 4 values
old way:
```cpp
int min1 = min(a,min(b,min(c,d)));
```
cpp17 way:
```cpp
int min1 = min({a,b,c,d});
```
### gcd and lcm with two arguments.
```cpp
cout << gcd(24, 60); // 12
cout << lcm(8, 10);  // 40
```
# References
- [Fast I/O](https://codeforces.com/blog/entry/5217)
- [C++ tips and tricks](https://codeforces.com/blog/entry/74684)
- [C++17, competitive programming edition](https://codeforces.com/blog/entry/57729)