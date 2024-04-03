#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <mutex>
#include <map>

using namespace std;

struct Zadanie{
    int p; //czas
    int w; //kara
    int d; //deadline

    Zadanie() : p(0), w(0), d(0) {}
};

int obliczOptymalneRozwiazanie(const vector<Zadanie>& zadania, vector<int>& najlepszaKolejnosc) {
    int n = zadania.size();
    int N = 1 << n;
    vector<int> F(N, INT_MAX);
    map<int, vector<int> > poprzednik;
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
                int nowyKoszt = F[set - (1 << k)] + zadania[k].w * max(Cmax - zadania[k].d, 0);
                if (nowyKoszt < F[set]) {
                    F[set] = nowyKoszt;
                    poprzednik[set] = poprzednik[set - (1 << k)];
                    poprzednik[set].push_back(k);
                }
            }
        }
    }

    najlepszaKolejnosc = poprzednik[N - 1];
    return F[N - 1];
}

void wczytajDane(const string& dane, vector<Zadanie>& zadania){
    //windows
    //ifstream f("C:\\Users\\miql\\Desktop\\Lab2\\witi.data.txt");

    //terminal
    ifstream f("witi.data.txt");

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
    vector<int> najlepszaKolejnosc;
    chrono::milliseconds czas(0);

    for(int i = 10; i<21;i++){
        cout << "========= Przetwarzanie danych: data." << i <<" =========" << endl;
        string data = "data."+to_string(i)+":";
        wczytajDane(data, zadania);
        auto start = chrono::high_resolution_clock::now();
        cout << "Minimalna suma kar: " << obliczOptymalneRozwiazanie(zadania,najlepszaKolejnosc);
        auto stop = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::milliseconds>(stop-start);
        cout << " | Najlepsza kolejność zadań: ";
        for(int indeks : najlepszaKolejnosc) {
            cout << indeks + 1 << " ";
        }
        cout<<" | Czas trwania algorytmu: "<< duration.count()<<" ms"<<endl;
        czas+=duration;
        zadania.clear();
    }
    cout << "========= Calkowity czas trwania algorytmu: " << czas.count() <<" ms =========" << endl;
    return 0;
}