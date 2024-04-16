#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

struct Zadanie{
    int index;
    vector<int>zadania;
};

void wczytajDane(const string& dane, vector<Zadanie>& zadania){
    //ifstream f("neh.data.txt");
    ifstream f("/Users/miql/Desktop/KZI/Lab3/neh.data.txt");
    string tmp;
    int ilosc_zadan;
    int ilosc_maszyn;

    while(getline(f,tmp)){
        if(tmp==dane){
            break;
        }
    }

    f>>ilosc_zadan>>ilosc_maszyn;
    for(int i=0;i<ilosc_zadan;i++){
        Zadanie zad;
        zad.index=i+1;
        for(int i=0; i<ilosc_maszyn; i++){
            int tmp=0;
            f>>tmp;
            zad.zadania.push_back(tmp);
        }
        zadania.push_back(zad);
    }
}

void wyswietlDane(vector<Zadanie>& zadania){
    for(Zadanie zad : zadania){
        for(int z : zad.zadania){
            cout<<z<<" ";
        }
        cout<<endl;
    }
}

void obliczCmax(vector<int> kolejnosc){
    
}

int main() {
    vector<Zadanie> zadania;
    string dane = "data.000:\r";
    wczytajDane(dane,zadania);
    wyswietlDane(zadania);
    return 0;
}
