#include <bits/stdc++.h>

using namespace std;

int main() {
    cerr << "running sorting algorithms..." << endl;
    freopen("result.txt", "w", stdout);
    cout << setw(16) << left;
    cout << " ";

    for (int i = 1; i <= 8; i++) {
        cout << setw(12) << left;
        string filename;
        stringstream ss;
        ss << "input", ss << i;
        ss >> filename;
        cout << filename;
    }
    cout << "\n";
    fclose(stdout);
    system(
        "cd \"d:\\Program\\sorting\\code\" && g++ insertion.cpp -o insertion &&"
        "\"d:\\Program\\sorting\\code\\insertion\"");
    system(
        "cd \"d:\\Program\\sorting\\code\" && g++ selection.cpp -o selection &&"
        "\"d:\\Program\\sorting\\code\\selection\"");
    system(
        "cd \"d:\\Program\\sorting\\code\" && g++ bubble.cpp -o bubble &&"
        "\"d:\\Program\\sorting\\code\\bubble\"");
    system(
        "cd \"d:\\Program\\sorting\\code\" && g++ shell.cpp -o shell &&"
        "\"d:\\Program\\sorting\\code\\shell\"");
    system(
        "cd \"d:\\Program\\sorting\\code\" && g++ heap.cpp -o heap &&"
        "\"d:\\Program\\sorting\\code\\heap\"");
    system(
        "cd \"d:\\Program\\sorting\\code\" && g++ merge.cpp -o merge &&"
        "\"d:\\Program\\sorting\\code\\merge\"");
    system(
        "cd \"d:\\Program\\sorting\\code\" && g++ quick.cpp -o quick &&"
        "\"d:\\Program\\sorting\\code\\quick\"");
    system(
        "cd \"d:\\Program\\sorting\\code\" && del insertion.exe && del "
        "selection.exe && del bubble.exe && del shell.exe && del heap.exe && "
        "del merge.exe && del quick.exe");
    return 0;
}