#include <iostream>
#include <cmath>
using namespace std;

void wczytywanie(float **tab, int n)
{
	for (int i=0; i<n; i++)
	{
		cout << endl << "Podaj " << i+1 << " wiersz:" << endl;
		for (int j=0; j<n+1; j++)
            cin >> tab[i][j];
	}
}

void wyswietl_macierz(float **tab, int n)
{
    for(int i=0;i<n;i++)
    {
        cout.width(9);
        cout<<"X"<<i+1;
        if(i==n-1)
        {
            cout.width(9);
            cout<<"B";
        }
    }
    cout<<endl;
    for(int i=0; i<n; i++)
    {

        for(int j=0; j<n+1; j++)
        {
            cout.width(10);
            cout << tab[i][j];
        }

        cout << endl;
    }
}

void wyczysc_pamiec(float **tab, float *W, int n)
{
      for(int i=0;i<n;i++)
		delete [] tab[i];
	delete [] tab;
	delete [] W;
}

void zerowanie_macierzy(float **tab, int n, int i)
{
    float p;
	for (int j=i+1; j<n; j++)
    {
        p = tab[j][i]/tab[i][i];
        for (int k=i; k<n+1; k++)
        {
            tab[j][k] = tab[j][k]-p*tab[i][k];
            if(fabs(tab[j][k]) < 0.000001) //przypisywanie wartosciom bliskich zera wartosci zero
                tab[j][k]=0;
        }
    }
}

void oblicz_rozwiazania(float *W, float **tab, int n)
{
    float s;
    W[n-1] = tab[n-1][n]/tab[n-1][n-1];
    for(int i=n-2; i>=0; i--)
    {
        s = 0;
        for(int j=n-1; j>i; j--)
            s = s + W[j]*tab[i][j];
        W[i] = (tab[i][n] - s)/tab[i][i];
    }
}

void wyswietl_rozwiazania(float *W, int n)
{
    cout << endl << "Obliczone wartosci:" << endl << endl;
    for(int i=0; i<n; i++)
        cout << "x" << i+1 << " = " << W[i] << endl;
    cout<<"Wektor rozwiazan x = [";
    for(int i=0;i<n;i++){
        if(i == n-1)
            cout<<W[i];
        else
            cout<<W[i]<<", ";
    }
    cout<<"]"<<endl;

}

bool czy_przekatna_zero(float **tab, int i) //funkcja sprawdzajaca czy mozna dalej przeksztalcac macierz(czy spelnione sa zalozenia metody)
{
    if(tab[i][i] == 0 || fabs(tab[i][i]) < 0.000001)
    {
        cout<<"Element na glownej przekatnej jest rowny zero! Przerywam dzialanie."<<endl;
        return true;
    }
    else
        return false;

}

void metoda_podstawowa(float **tab, int n) //przeksztalcenia macierzy kwadratowej do postaci trojkatnej gornej
{
    float *W = new float[n]; //tablica wynikow
    for(int i=0; i<n; i++)
    {
        if(czy_przekatna_zero(tab,i)==true)
            exit(1);
        else
        	zerowanie_macierzy(tab, n, i);
    }
    cout << endl << "Macierz po przeksztalceniu:" << endl << endl;
    wyswietl_macierz(tab, n);
    oblicz_rozwiazania(W, tab, n);
    wyswietl_rozwiazania(W,n);
    wyczysc_pamiec(tab,W,n);
}

void zamiana_kolumn(float **tab, int i, int kolumna, int n) //funkcja pomocnicza do metoda_max
{
	for (int j=0; j<n+1; j++)
		swap(tab[i][j],tab[kolumna][j]);
}

void metoda_max(float **tab, int n) //metoda z wyborem elementu maksymalnego w kolumnie
{
    int kolumna;
    float *W = new float[n]; //tablica wynikow
    for(int i=0; i<n; i++)
    {
		for(int j=i; j<n; j++)
            if (fabs(tab[i][i]) < fabs(tab[i][j]))
                kolumna=j;

        if(kolumna!=i)
            zamiana_kolumn(tab,i,kolumna,n);

        if(czy_przekatna_zero(tab,i)==true)
            exit(1);
        else
        	zerowanie_macierzy(tab, n, i);
    }
    cout << endl << "Macierz po przeksztalceniu:" << endl << endl;
    wyswietl_macierz(tab, n);
    oblicz_rozwiazania(W, tab, n);
    wyswietl_rozwiazania(W,n);
    wyczysc_pamiec(tab,W,n);
}

int main()
{
    int n, wybor, dane;
    do{
    cout<<endl<<"Wybierz metode:"<<endl;
    cout<<"1. Metoda podstawowa"<<endl<<"2. Metoda z elementem maksymalnym w kolumnie"<<endl<<"3. Wyjscie"<<endl<<"Wybor: ";
    cin >> wybor;
    switch(wybor)
    {
        case 1:
            cout<<"4. Skorzystaj z macierzy testowej"<<endl<<"5. Wprowadz wlasne dane"<<endl<<"Wybor: ";
            cin>>dane;
            if(dane == 4)
            {
                cout<<"Dane testowe:"<<endl;
                n=4;
                float **tab = new float *[n];
                for(int i=0; i<n; i++)
                    tab[i] = new float [n+1];
                float T[][n+1]={{1,2,-1,2,0},{1,0,-2,4,4},{0,-3,1.5,7,0},{0,-1,1,6,-1}};//tab testowa
                for (int i=0; i<n; i++)
                    for (int j=0; j<n+1; j++)
                        tab[i][j]=T[i][j]; //przypisanie zawartosci tablicy testowej do "wlasciwej" tablicy
                wyswietl_macierz(tab,n);
                metoda_podstawowa(tab,n);
                }
                else
                {
                    cout << "Podaj ilosc zmiennych: ";
                    cin >> n;
                    float **tab = new float *[n];
                    for(int i=0; i<n; i++)
                        tab[i] = new float [n+1];
                    wczytywanie(tab, n);
                    metoda_podstawowa(tab,n);
                }
                break;
            case 2:
                cout<<"4. Skorzystaj z macierzy testowej"<<endl<<"5. Wprowadz wlasne dane"<<endl<<"Wybor: ";
                cin>>dane;
                if(dane==4)
                {
                    cout<<"Dane testowe:"<<endl;
                    n=5;
                    float **tab = new float *[n];
                    for(int i=0; i<n; i++)
                        tab[i] = new float [n+1];
                    float T[][n+1]={{14,-13,3,-16,-42,-37},{3.5,-18,13,-23.75,-21,-5.5},{3.5,3,-5.25,9.25,10.5,12.5},{2,14.5,-10.5,18.5,21,23.5},{1.5,6.75,-9.25,17,-10.5,-45.25}};//tab testowa
                    for (int i=0; i<n; i++)
                        for (int j=0; j<n+1; j++)
                            tab[i][j]=T[i][j]; //przypisanie zawartosci tablicy testowej do "wlasciwej" tablicy
                    wyswietl_macierz(tab,n);
                    metoda_max(tab,n);
                }
                else
                {
                    cout << "Podaj ilosc zmiennych: ";
                    cin >> n;
                    float **tab = new float *[n];
                    for(int i=0; i<n; i++)
                        tab[i] = new float [n+1];
                    wczytywanie(tab, n);
                    metoda_max(tab,n);
                }
                break;
        }
    }while(wybor!=3);

    return 0;
}
