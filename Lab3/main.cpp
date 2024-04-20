#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

struct Zadanie{
    int index;
    int waga;
    vector<int>zadania;
};

void wczytajDane(const string& dane, vector<Zadanie>& zadania){
    //ifstream f("neh.data.txt");
    //ifstream f("D:\\Studia\\ISA\\SEMESTR 6\\KZI\\Lab3\\neh.data.txt");
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
        int w=0;
        zad.index=i;
        for(int i=0; i<ilosc_maszyn; i++){
            int tmp=0;
            f>>tmp;
            w+=tmp;
            zad.zadania.push_back(tmp);
        }
        zad.waga=w;
        zadania.push_back(zad);
    }
}

void wyswietlDane(vector<Zadanie>& zadania){
    for(Zadanie zad : zadania){
        for(int z : zad.zadania){
            cout<<z<<" ";
        }
        cout<<" | w: "<<zad.waga<<" |"<<endl;
    }
}

int obliczCmaxKolejnosc(const vector<Zadanie>& zadania, const vector<int>& kolejnosc) {
    int liczbaMaszyn = zadania.front().zadania.size();
    vector<int> czasyZakonczeniaMaszyn(liczbaMaszyn, 0);

    for (int idx : kolejnosc) {
        vector<int> noweCzasyZakonczeniaMaszyn(liczbaMaszyn, 0);
        for (int m = 0; m < liczbaMaszyn; m++) {
            int czasZakonczeniaPoprzedniegoZadania = (m == 0) ? 0 : noweCzasyZakonczeniaMaszyn[m - 1];
            int czasZakonczeniaNaPoprzedniejMaszynie = czasyZakonczeniaMaszyn[m];
            noweCzasyZakonczeniaMaszyn[m] = max(czasZakonczeniaPoprzedniegoZadania, czasZakonczeniaNaPoprzedniejMaszynie) + zadania[idx].zadania[m];
        }
        czasyZakonczeniaMaszyn = noweCzasyZakonczeniaMaszyn;
    }

    return czasyZakonczeniaMaszyn.back();
}

int obliczCmax(const vector<Zadanie>& zadania){
    int liczbaMaszyn = zadania.front().zadania.size();
    vector<int> czasyZakonczeniaMaszyn(liczbaMaszyn, 0);
    for(Zadanie zad : zadania){
        vector<int> noweCzasyZakonczeniaMaszyn(liczbaMaszyn, 0);
        for (int m = 0; m < liczbaMaszyn; m++) {
            int czasZakonczeniaPoprzedniegoZadania = (m == 0) ? 0 : noweCzasyZakonczeniaMaszyn[m - 1];
            int czasZakonczeniaNaPoprzedniejMaszynie = czasyZakonczeniaMaszyn[m];
            noweCzasyZakonczeniaMaszyn[m] = max(czasZakonczeniaPoprzedniegoZadania, czasZakonczeniaNaPoprzedniejMaszynie) + zad.zadania[m];
        }
        czasyZakonczeniaMaszyn = noweCzasyZakonczeniaMaszyn;
    }
    return  czasyZakonczeniaMaszyn.back();
}

vector<int> indeksy(const vector<Zadanie>& zadania){
    vector<int> kol;
    for(const auto & i : zadania){
        kol.push_back(i.index);
    }
    return kol;
}

int neh(const vector<Zadanie>& dane){
    vector<Zadanie> posortowane = dane;
    std::sort(posortowane.begin(), posortowane.end(), [](const Zadanie& a, const Zadanie& b){
        return a.waga > b.waga;
    } );
    vector<int> najlepszaKolejnosc;
    vector<Zadanie> aktualna;
    int bestCmax=INT_MAX;
    for(Zadanie zad : posortowane){
        aktualna.push_back(zad);
        bestCmax = obliczCmax(aktualna);
       for(int j=aktualna.size()-1; j>0 ; j--){
           if(j!=1){
               swap(aktualna[j],aktualna[j-1]);
           }
           vector<int> indxy = indeksy(aktualna);
           int currCmax = obliczCmax(aktualna);
           if( bestCmax > currCmax){
               bestCmax = currCmax;
           }
       }
    }
    cout<<endl;
    wyswietlDane(aktualna);
    return bestCmax;
}


int main() {
    vector<Zadanie> zadania;
    //string dane = "data.000:";
    //wersja MacOS
    string dane = "data.000:\r";
    wczytajDane(dane,zadania);
    wyswietlDane(zadania);
    cout <<"Z kol: " <<obliczCmaxKolejnosc(zadania, {0, 1, 2, 3}) << endl;
    cout <<"Bez kol: " <<obliczCmax(zadania)<<endl;
    cout<< "NEH: "<<neh(zadania)<<endl;
    return 0;
}
