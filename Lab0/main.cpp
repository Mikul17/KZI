#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <climits>

    using namespace std;

    struct Obiekt{
        int r;
        int p;
        int q;
        int id;

        Obiekt(int _r = 0, int _p = 0, int _q = 0, int _id = -1) : r(_r), p(_p), q(_q), id(_id) {}
    };

    vector<Obiekt> wczytajDane(const string& dane){
        vector<Obiekt> obiekty;
        //ifstream f ("/Users/miql/Desktop/Cpp/Lab0/rpq.data.txt");
        ifstream f ("C:\\Users\\miql\\Desktop\\KZI\\Lab0\\rpq.data.txt");
        //ifstream f ("rpq.data.txt");
        string tmp;
        int n=0;

        while(getline(f,tmp)){
            if(tmp==dane){
                break;
            }
        }

        f>>n;

        for(int i=0;i<n;i++){
            Obiekt ob;
            f>>ob.r>>ob.p>>ob.q;
            ob.id=i+1;
            obiekty.push_back(ob);
        }
        return obiekty;
    }

    void wyswietlDane(vector<Obiekt> obiekty){
        for(int i=0; i<obiekty.size();i++){
            cout<<"["<<obiekty[i].id<<"]: "<<"r: "<<obiekty[i].r<<" p: "<<obiekty[i].p<<" q: "<<obiekty[i].q<<endl;
        }
    }

    void wyswietlKolejnosc(vector<Obiekt> obiekty){
        for(int i=0; i<obiekty.size();i++){
            cout<<obiekty[i].id<<" ";
        }
        cout<<endl;
    }

    int obliczDlaWycinka(vector<Obiekt> obiekty, int indeksy[], int& size){
        int t=0, Cmax=0;

        for(int k=0; k<size; k++){
            t = max(t, obiekty.at(indeksy[k]).r)+obiekty.at(indeksy[k]).p;
            Cmax = max(Cmax, t+obiekty[indeksy[k]].q);
        }
        cout<<"t: "<<t<<" | Cmax: "<<Cmax<<endl;
        return Cmax;
    }

    int obliczCmax(vector<Obiekt> obiekty){
        int t=0, Cmax=0;

        for(int k=0; k<obiekty.size(); k++){
            t = max(t, obiekty.at(k).r)+obiekty.at(k).p;
            Cmax = max(Cmax, t+obiekty[k].q);
        }
        return Cmax;
    }

    void sortR(vector<Obiekt> obiekty){
        vector<Obiekt> posortowane = obiekty;
        sort(posortowane.begin(), posortowane.end(), [](const Obiekt& a, const Obiekt& b) {
            return a.r < b.r;
        });

        int indeksy[posortowane.size()];

        for(int i=0; i<posortowane.size();i++) {
            indeksy[i] = posortowane.at(i).id-1;
        }

        int size = sizeof(indeksy)/sizeof(int);

        obliczDlaWycinka(obiekty,indeksy,size);
    }

    bool operator==(const Obiekt& a, const Obiekt& b) {
        return a.r == b.r && a.p == b.p && a.q == b.q && a.id == b.id;
    }
    bool operator==(const vector<Obiekt>& a, const vector<Obiekt>& b) {
        if (a.size() != b.size()) return false;
        for (size_t i = 0; i < a.size(); ++i) {
            if (!(a[i] == b[i])) return false;
        }
        return true;
    }

    void zamien(Obiekt& a, Obiekt& b){
        Obiekt tmp = a;
        a = b;
        b = tmp;
    }

    vector<Obiekt> tabuSearch(vector<Obiekt>& obiekty, int maxIteracji, int rozmiarTablicyPodobienstwa){
            vector<Obiekt> tab = obiekty;

            sort(tab.begin(), tab.end(), [](const Obiekt& a, const Obiekt& b) {
                return a.r < b.r;
            });

            vector<Obiekt> najlepszeRozwiazanie = tab;
            int Cmax = obliczCmax(tab);

            vector<vector<Obiekt>> tablicaPodobienstwa;

            for(int i=0; i< maxIteracji; i++) {
                vector<Obiekt> najlepszaKolejnosc;
                int najlepszyCmax = INT_MAX;

                for(int i = 0; i < tab.size(); i++){
                    for(int j=i+1; j < tab.size(); j++){
                        vector<Obiekt> aktualnaKolejnosc = tab;
                        zamien(aktualnaKolejnosc[i], aktualnaKolejnosc[j]);

                        bool istnieje = false;
                        for(auto& tablica : tablicaPodobienstwa){
                            if(tablica == aktualnaKolejnosc){
                                istnieje = true;
                                break;
                            }
                        }

                        if(!istnieje){
                            int aktualnyCmax = obliczCmax(aktualnaKolejnosc);
                            if(aktualnyCmax < najlepszyCmax){
                                najlepszaKolejnosc = aktualnaKolejnosc;
                                najlepszyCmax = aktualnyCmax;
                            }
                        }
                    }
                }

                tab = najlepszaKolejnosc;
                if(najlepszyCmax < Cmax){
                    najlepszeRozwiazanie = najlepszaKolejnosc;
                    Cmax = najlepszyCmax;
                }

                tablicaPodobienstwa.push_back(najlepszaKolejnosc);
                if(tablicaPodobienstwa.size() > rozmiarTablicyPodobienstwa){
                    tablicaPodobienstwa.erase(tablicaPodobienstwa.begin());
                }
            }

            return najlepszeRozwiazanie;
        }


    int main() {
        int Cmax = 0;
        chrono::milliseconds czas(0);

        vector<string> nazwyPlikow = {"data.1", "data.2", "data.3", "data.4"};

        for(int i=1; i<5; i++){
            string nazwaPliku = "data."+to_string(i);
            cout << "========= Przetwarzanie danych:  " << nazwaPliku <<" =========" << endl;

            vector<Obiekt> dane = wczytajDane(nazwaPliku);

            auto start = chrono::high_resolution_clock::now();

            vector<Obiekt> wynik = tabuSearch(dane,50,30);

            auto stop = chrono::high_resolution_clock::now();
            auto duration = chrono::duration_cast<chrono::milliseconds>(stop - start);
            czas += duration;


            int tmp = obliczCmax(wynik);
            Cmax += tmp;
            cout << "Cmax: " << tmp << endl;
            cout<< "Kolejnosc: ";
            wyswietlKolejnosc(wynik);
            cout << endl << "Czas wykonania: " << duration.count()  << " milisekund" << endl;

        }
        cout<< "=====================================" << endl;
        cout << "Laczny czas wykonania: " << czas.count()  << " milisekund" << endl;
        cout<<"Laczne Cmax: "<<Cmax<<endl;

        return 0;
    }

    //skrot nazwy przedmiotu, nr cwiczenia
    //KZW_Lab1
    //sprawozdanie + kod zrodlowy