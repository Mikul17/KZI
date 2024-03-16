    #include <iostream>
    #include <fstream>

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
        ifstream f ("/Users/miql/Desktop/Cpp/Lab0/rpq.data.txt");
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

    int algorytm123(vector<Obiekt> obiekty){
        int t=0, Cmax=0;
        for(auto & i : obiekty){
            t = max(t,i.r)+i.p;
            Cmax=max(Cmax, t+i.q);
        }
        cout<<"t: "<<t<<" | Cmax: "<<Cmax<<endl;
    }

    int odwrotnyAlgorytm123(vector<Obiekt> obiekty){
        int t=0,Cmax=0;

        for(int i=obiekty.size()-1; i>=0; i--){
            t=max(t,obiekty.at(i).r)+obiekty.at(i).p;
            Cmax=max(Cmax, t+obiekty.at(i).q);
        }
        cout<<"t: "<<t<<" | Cmax: "<<Cmax<<endl;
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

    void sortRQratio(vector<Obiekt> obiekty){
        vector<Obiekt> posortowane=obiekty;
        sort(posortowane.begin(), posortowane.end(), [](const Obiekt& a, const Obiekt& b) {
            return abs(a.q/a.r) < abs(b.q/b.r);
        });

        int indeksy[posortowane.size()];

        for(int i=0; i<posortowane.size();i++) {
            indeksy[i] = posortowane.at(i).id-1;
        }

        int size = sizeof(indeksy)/sizeof(int);

        obliczDlaWycinka(obiekty,indeksy,size);
    }

    void sortQ(vector<Obiekt> obiekty){
        vector<Obiekt> posortowane = obiekty;
        sort(posortowane.begin(), posortowane.end(), [](const Obiekt& a, const Obiekt& b) {
            return a.q > b.q;
        });
        int indeksy[posortowane.size()];

        for(int i=0; i<posortowane.size();i++) {
            indeksy[i] = posortowane.at(i).id-1;
        }

        int size = sizeof(indeksy)/sizeof(int);

        obliczDlaWycinka(obiekty,indeksy,size);
    }




    int main() {
        vector<Obiekt> dane = wczytajDane("data.1");
        wyswietlDane(dane);
        //algorytm123(dane);
        //int wycinek[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23};
        //int size = sizeof(wycinek)/sizeof(int);
        //obliczDlaWycinka(dane,wycinek,size);
        sortR(dane);
        sortRQratio(dane);
        sortQ(dane);


        return 0;
    }

    //skrot nazwy przedmiotu, nr cwiczenia
    //KZW_Lab1
    //sprawozdanie + kod zrodlowy