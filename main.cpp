#include <iostream>
#include <cmath>
using namespace std;

void load(float **tab, int n)
{
	for (int i=0; i<n; i++)
	{
		cout << endl << "Enter " << i+1 << " row:" << endl;
		for (int j=0; j<n+1; j++)
            cin >> tab[i][j];
	}
}

void show_matrix(float **tab, int n)
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

void clean_memory(float **tab, float *W, int n)
{
      for(int i=0;i<n;i++)
		delete [] tab[i];
	delete [] tab;
	delete [] W;
}

void row_reduction(float **tab, int n, int i)
{
    float p;
	for (int j=i+1; j<n; j++)
    {
        p = tab[j][i]/tab[i][i];
        for (int k=i; k<n+1; k++)
        {
            tab[j][k] = tab[j][k]-p*tab[i][k];
            if(fabs(tab[j][k]) < 0.000001) //assigning values close to zero the value zero
                tab[j][k]=0;
        }
    }
}

void solve_equations(float *W, float **tab, int n)
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

void show_equations(float *W, int n)
{
    cout << endl << "Calculated values:" << endl << endl;
    for(int i=0; i<n; i++)
        cout << "x" << i+1 << " = " << W[i] << endl;
    cout<<"Vector x = [";
    for(int i=0;i<n;i++){
        if(i == n-1)
            cout<<W[i];
        else
            cout<<W[i]<<", ";
    }
    cout<<"]"<<endl;

}

bool is_diagonal_zero(float **tab, int i) //function checking whether it is possible to transform the matrix (whether assumptions of the method are fulfilled)
{
    if(tab[i][i] == 0 || fabs(tab[i][i]) < 0.000001)
    {
        cout<<"The element on the main diagonal is zero! Program end."<<endl;
        return true;
    }
    else
        return false;

}

void standard_method(float **tab, int n) // transform a square matrix to an upper triangular matrix
{
    float *W = new float[n]; //result table
    for(int i=0; i<n; i++)
    {
        if(is_diagonal_zero(tab,i)==true)
            exit(1);
        else
        	row_reduction(tab, n, i);
    }
    cout << endl << "Matrix after transformation:" << endl << endl;
    show_matrix(tab, n);
    solve_equations(W, tab, n);
    show_equations(W,n);
    clean_memory(tab,W,n);
}

void swap_columns(float **tab, int i, int column, int n) // helper function to method_max
{
	for (int j=0; j<n+1; j++)
		swap(tab[i][j],tab[column][j]);
}

void method_max(float **tab, int n) //method with selecting the maximum element in the column
{
    int column;
    float *W = new float[n]; //result table
    for(int i=0; i<n; i++)
    {
		for(int j=i; j<n; j++)
            if (fabs(tab[i][i]) < fabs(tab[i][j]))
                column=j;

        if(column!=i)
            swap_columns(tab,i,column,n);

        if(is_diagonal_zero(tab,i)==true)
            exit(1);
        else
        	row_reduction(tab, n, i);
    }
    cout << endl << "Matrix after transformation:" << endl << endl;
    show_matrix(tab, n);
    solve_equations(W, tab, n);
    show_equations(W,n);
    clean_memory(tab,W,n);
}

int main()
{
    int n, choice, data;
    do{
    cout<<endl<<"Select method:"<<endl;
    cout<<"1. Standard(basic) method"<<endl<<"2. Method with maximal element in the column"<<endl<<"3. Exit"<<endl<<"Choice: ";
    cin >> choice;
    switch(choice)
    {
        case 1:
            cout<<"4. Use the test matrix"<<endl<<"5.  Enter your own data"<<endl<<"Choice: ";
            cin>>data;
            if(data == 4)
            {
                cout<<"Test data"<<endl;
                n=4;
                float **tab = new float *[n];
                for(int i=0; i<n; i++)
                    tab[i] = new float [n+1];
                float T[][n+1]={{1,2,-1,2,0},{1,0,-2,4,4},{0,-3,1.5,7,0},{0,-1,1,6,-1}};//test array
                for (int i=0; i<n; i++)
                    for (int j=0; j<n+1; j++)
                        tab[i][j]=T[i][j]; //assign the test array to the "proper" array
                show_matrix(tab,n);
                standard_method(tab,n);
                }
                else
                {
                    cout << "Enter the number of variables: ";
                    cin >> n;
                    float **tab = new float *[n];
                    for(int i=0; i<n; i++)
                        tab[i] = new float [n+1];
                    load(tab, n);
                    standard_method(tab,n);
                }
                break;
            case 2:
                cout<<"4. Use the test matrix"<<endl<<"5. Enter your own data"<<endl<<"Choice: ";
                cin>>data;
                if(data==4)
                {
                    cout<<"Test data:"<<endl;
                    n=5;
                    float **tab = new float *[n];
                    for(int i=0; i<n; i++)
                        tab[i] = new float [n+1];
                    float T[][n+1]={{14,-13,3,-16,-42,-37},{3.5,-18,13,-23.75,-21,-5.5},{3.5,3,-5.25,9.25,10.5,12.5},{2,14.5,-10.5,18.5,21,23.5},{1.5,6.75,-9.25,17,-10.5,-45.25}};//tab testowa
                    for (int i=0; i<n; i++)
                        for (int j=0; j<n+1; j++)
                            tab[i][j]=T[i][j]; //assign the test array to the "proper" array
                    show_matrix(tab,n);
                    method_max(tab,n);
                }
                else
                {
                    cout << "Enter the number of variables: ";
                    cin >> n;
                    float **tab = new float *[n];
                    for(int i=0; i<n; i++)
                        tab[i] = new float [n+1];
                    load(tab, n);
                    method_max(tab,n);
                }
                break;
        }
    }while(choice!=3);

    return 0;
}
