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

struct Podzadanie {
    vector<int> kolejnosc;
    int Cmax = 0;
};

int obliczKoszt(const Zadanie& zadanie, int Cmax) {
    return zadanie.w * max(Cmax - zadanie.d, 0);
}


int obliczOptymalneRozwiazanie(const vector<Zadanie>& zadania, vector<int>& najlepszaKolejnosc) {
    int n = zadania.size();
    int N = 1 << n;
    vector<int> F(N, INT_MAX);
    vector<Podzadanie> podzadania(N);
    podzadania[0].Cmax=0;
    F[0] = 0;

    for (int podzadanie = 1; podzadanie < N; podzadanie++) {
        for (int k = 0; k < n; ++k) {
            if (podzadanie & (1 << k)) {
                int poprzednie = podzadanie - (1 << k);
                int Cmax = podzadania[poprzednie].Cmax + zadania[k].p;
                int nowyKoszt = F[poprzednie] + obliczKoszt(zadania[k], Cmax);
                if (nowyKoszt < F[podzadanie]) {
                    F[podzadanie] = nowyKoszt;
                    podzadania[podzadanie].kolejnosc = podzadania[poprzednie].kolejnosc;
                    podzadania[podzadanie].kolejnosc.push_back(k);
                    podzadania[podzadanie].Cmax = Cmax;
                }
            }
        }
    }

    najlepszaKolejnosc = podzadania[N - 1].kolejnosc;
    return F[N - 1];
}

void wczytajDane(const string& dane, vector<Zadanie>& zadania){
    //windows
    ifstream f("D:\\Studia\\ISA\\SEMESTR 6\\KZI\\Lab2\\witi.data.txt");

    //terminal
    //ifstream f("witi.data.txt");

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
        cout << " | Najlepsza kolejnosc zadan: ";
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