#include "HashTable.h"

int unitTests();

int main()
{
    int score = unitTests();

    istream_iterator<string> eos1;

    cout << "Loading the complete works of Shakespeare into a vector..." << endl;
    ifstream f("shakespeare.txt");
    if(!f)
    {
        cout << "Failed opening shakespeare.txt" << endl;
        return 1;
    }
    istream_iterator<string> iit(f);
    vector<string> vShake(iit, eos1);
    cout << vShake.size() << " words loaded." << endl;

    cout << "Loading the English dictionary into the hash table..." << endl;
    ifstream f2("words_alpha.txt");
    if(!f2)
    {
        cout << "Failed opening words_alpha.txt" << endl;
        return 1;
    }
    istream_iterator<string> iit2(f2);
    HashTable<string> ht1(iit2, eos1);
    cout << "Hash table loaded." << endl;

    int foundCount = 0;
    auto t1 = system_clock::now();
    for(const string& str : vShake)
    {
        auto it = ht1.find(str);
        if(it != ht1.end()) foundCount++;
    }
    auto t2 = system_clock::now();
    cout << foundCount << " out of " << vShake.size() << " total words matched.\n";
    cout << "Required number of matches: " << 519831 << endl;

    long long int ms = std::chrono::duration_cast<std::chrono::milliseconds>(t2-t1).count();
    cout << "Time to search hash table: " << ms << "ms" << endl;
    cout << "Required time: < 400ms" << endl;

    if(ms < 400 && foundCount == 519831)
    {
        cout << "passed.  +5 points" << endl;
        score += 5;
    }
    else
    {
        cout << "Failed." << endl;
    }

    cout << "Final score: " << score << "/15" << endl;
    ofstream scoreOfs("score.txt");
    scoreOfs << score << endl;

    return 0;
}

int unitTests()
{
    int score = 0;

    cout << "Testing one insert and one find..." << endl;
    HashTable<string> h1(3);
    h1.insert("hello");
    auto it1 = h1.find("hello");
    auto itN = h1.find("nope");
    if(it1 != h1.end() && itN == h1.end())
    {
        cout << "passed. +2 points" << endl;
        score+=2;
    }
    else
    {
        cout << "failed." << endl;
    }
    cout << "Testing iterator access operator (*)..." << endl;
    if(*it1 == "hello")
    {
        cout << "passed. +1 point" << endl;
        score++;
    }
    else
    {
        cout << "failed." << endl;
    }

    cout << "Testing multiple inserts with collisions..." << endl;
    h1.insert("world");
    h1.insert("I");
    h1.insert("Love");
    h1.insert("C++");
    auto it2 = h1.find("world");
    auto it3 = h1.find("I");
    auto it4 = h1.find("Love");
    auto it5 = h1.find("C++");
    if(*it1 == "hello" && *it2 == "world" && *it3 == "I" && *it4 == "Love" && *it5 == "C++" && itN == h1.end())
    {
        cout << "passed. +1 point" << endl;
        score+=1;
    }
    else
    {
        cout << *it1 << *it2 << *it3 << *it4 << *it5 << endl;
        cout << "failed." << endl;
    }

    cout << "Testing multiple inserts with collisions, different hash table..." << endl;
    HashTable<string> h2(65535);
    h2.insert("hello");
    h2.insert("world");
    h2.insert("I");
    h2.insert("Love");
    h2.insert("C++");
    it1 = h2.find("hello");
    it2 = h2.find("world");
    it3 = h2.find("I");
    it4 = h2.find("Love");
    it5 = h2.find("C++");
    if(*it1 == "hello" && *it2 == "world" && *it3 == "I" && *it4 == "Love" && *it5 == "C++" && itN == h1.end())
    {
        cout << "passed. +1 point" << endl;
        score+=1;
    }
    else
    {
        cout << *it1 << *it2 << *it3 << *it4 << *it5 << endl;
        cout << "failed." << endl;
    }

    cout << "Testing begin iterator..." << endl;
    it1 = h1.begin();
    it2 = h2.begin();
    if(*it1 == "hello" && *it2 == "I")
    {
        cout << "passed.  +1 point" << endl;
        score++;
    }
    else
    {
        cout << "failed." << endl;
    }

    cout << "Testing one execution of ++ operator..." << endl;
    ++it1;
    ++it2;
    if(*it1 == "I" && *it2 == "C++")
    {
        cout << "passed.  +1 point" << endl;
        score++;
    }
    else
    {
        cout << "failed." << endl;
    }

    cout << "Testing execution of ++ operator until it reaches end..." << endl;
    bool passed = true;
    ++it1;
    ++it2;
    if(!(*it1 == "Love" && *it2 == "Love")) passed = false;
    ++it1;
    ++it2;
    if(!(*it1 == "C++" && *it2 == "world")) passed = false;
    ++it1;
    ++it2;
    if(!(*it1 == "world" && *it2 == "hello")) passed = false;
    ++it1;
    ++it2;
    if(!(it1 == h1.end() && it2 == h2.end())) passed = false;

    if(passed)
    {
        cout << "passed.  +2 points" << endl;
        score+=2;
    }
    else
    {
        cout << "failed." << endl;
    }


    cout << "Testing ostream operator..." << endl;
    ofstream testOfs("testOut.txt");
    testOfs << h1 << h2 << endl;
    testOfs.close();
    vector<string> ans = {"hello","I","Love","C++","world","I","C++","Love","world","hello"};
    istream_iterator<string> eos;
    ifstream ifs("testOut.txt");
    istream_iterator<string> iis(ifs);
    vector<string> tst(iis, eos);
    if(ans == tst)
    {
        cout << "passed.  +1 point" << endl;
        score++;
    }
    else
    {
        cout << "failed." << endl;
    }
    ifs.close();

    ofstream scoreOfs("score.txt");
    scoreOfs << score << endl;
    cout << "Score: " << score << endl;

    return score;
}

