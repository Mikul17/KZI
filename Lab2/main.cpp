#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <algorithm>
#include <thread>
#include <mutex>

using namespace std;

struct Zadanie{
    int p; //czas
    int w; //kara
    int d; //deadline

    Zadanie() : p(0), w(0), d(0) {}
};


int obliczOptymalneRozwiazanie(const vector<Zadanie>& zadania) {
    int n = zadania.size();
    int N = 1 << n;
    vector<int> F(N, 999999);
    F[0] = 0;

    for (int set = 1; set < N; set++) {
        int Cmax = 0;
        for (int i = 0; i < n; i++) {
            if (set & (1 << i)) {
                Cmax += zadania[i].p;
            }
        }

        for (int k = 0; k < n; k++) {
            if (set & (1 << k)) {
                F[set] = min(F[set], F[set - (1 << k)] + zadania[k].w * max(Cmax - zadania[k].d, 0));
            }
        }
    }
    return F[N - 1];
}


void wczytajDane(const string& dane, vector<Zadanie>& zadania){
    ifstream f("C:\\Users\\miql\\Desktop\\Lab2\\witi.data.txt");
    string tmp;
    int n=0;
    while(getline(f,tmp)){
        if(tmp==dane){
            break;
        }
    }

    f>>n;
    for(int i=0;i<n;i++){
        Zadanie zad;
        f>>zad.p>>zad.w>>zad.d;
        zadania.push_back(zad);
    }
    f.close();
}

int main() {
    vector<Zadanie> zadania;
    for(int i = 10; i<21;i++){
        string data = "data."+to_string(i)+":";
        wczytajDane(data, zadania);
        cout << "Optymalne rozwiazanie dla " << data << " to: " << obliczOptymalneRozwiazanie(zadania) << endl;
        zadania.clear();
    }
    return 0;
}