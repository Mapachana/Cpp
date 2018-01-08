/*Buscaminas es un juego muy conocido cuyo objetivo es encontrar todas las minas existentes en un tablero rectangular, sin abrir ninguna. Si se abre una mina, perdera la partida.
Se trabajara con una tabla de datos n × m en la que todas las filas tienen el mismo numero de columnas y los datos son de tipo bool. La clase se llamara TableroBuscaMinas y contendra valores true en caso de haber una mina en la
casilla especificada y false en caso contrario.
1. Defina los datos miembros de la clase TableroBuscaMinas.
2. Implemente un constructor que reciba el numero de filas y columnas que tendra el tablero y lo inicie fijando las casillas a false (no hay mina).
Nota: El numero de filas y columnas disponibles para construir tableros puede ser mayor que las que realmente se van a utilizar.
3. Escriba un metodo para modificar el estado de una casilla del tablero.
4. Implemente un metodo que reciba las coordenadas de una casilla y devuelva un valor entero que indique el numero de minas que rodean a la misma, incluyendo las diagonales.
• En caso de que la casilla no contenga una mina, el valor devuelto estara comprendido en [0, 8].
• En caso de que la casilla contenga una mina, se devolvera el valor −1.
Nota: Hay que tener en cuenta que las casillas de los bordes deben tratarse de manera diferenciada.*/

#include <iostream>
#include <vector>

using namespace std;


class TableroBuscaMinas
{
public:
    TableroBuscaMinas (int f, int c);
    void setmina (int i, int j);
    int minascerca (int i, int j);
    void jugar (int minas);
    void anadirusados (int j, int k);
    int tamanofilas();
    int tamanocolumnas();
    friend ostream& operator<<(ostream& os, TableroBuscaMinas& t);
private:
    vector<vector<bool> > tablero;
    vector<int> usadosx;
    vector<int> usadosy;
};

TableroBuscaMinas::TableroBuscaMinas (int f, int c)
{
    tablero = vector<vector<bool> > (f+2, vector<bool> (c+2, false));
    usadosx = vector<int> (0);
    usadosy = vector<int> (0);
}

int TableroBuscaMinas::tamanofilas()
{
    return tablero.size();
}
int TableroBuscaMinas::tamanocolumnas()
{
    return tablero[0].size();
}

void TableroBuscaMinas::setmina (int i, int j)
{
    if (i>0 && i<tablero.size()-1 && j>0 && j<tablero[0].size()-1 )
        tablero[i][j] = true;
    else
        cout << "Esa posición no es válida para la mina" << endl;
}

void TableroBuscaMinas::anadirusados (int j, int k)
{
    usadosx.push_back(j);
    usadosy.push_back(k);
}

int TableroBuscaMinas::minascerca (int i, int j)
{
    if (i>0 && i<tablero.size()-1 && j>0 && j<tablero.size()-1 )
    {
        int numminas = 0;
        for (int k = i-1; k <= i+1; k++)
            for (int l = j-1; l <= j+1; l++)
            {
                if (tablero[k][l] && !( k == i && l == j))
                    numminas++;
                    //numminas += (tablero[k][l);
                else if (tablero[k][l] && ( k == i && l == j))
                {
                    numminas = -1;
                    return numminas;
                }
            }
        return numminas;
    }
    else
        cout << "Te has salido del tablero" << endl;
}

ostream& operator<<(ostream& os, TableroBuscaMinas& t)
{
    int tamanofilas = t.tablero.size();
    int tamanocolumnas = t.tablero[0].size();

    bool found;

    int i;

    os << "====================================" << endl;
    os << "------------ Tablero ---------------" << endl;
    os << "====================================" << endl;

    os << endl;

    for (int j = 1; j < tamanofilas-1; j++)
    {
        for (int k = 1; k < tamanocolumnas-1; k++)
        {
            found = false;
            i = 0;
            while(!found && i < t.usadosx.size())
            {
                if (j == t.usadosx[i] && k == t.usadosy[i])
                {
                    os << t.minascerca(j,k) << " ";
                    found = true;
                }
                i++;
            }
            if (!found)
            {
                os << "? ";
            }
        }
        os << endl << endl;;
    }
    return os;
}

void TableroBuscaMinas::jugar (int minas)
{
    int numeromaximojugadas = (tablero.size()-2)*(tablero[0].size()-2)-minas;
    int ultimajugada = 0;
    int jugadaactual = 0;

    cout << (*(this)) << endl;

    while ((ultimajugada != -1) && (jugadaactual < numeromaximojugadas))
    {
        int a;
        int b;
        cout << "Cavar en " << endl;
        cin >> a >> b;


        bool encontrado = false;
        int g;
        g = 0;
        while(!encontrado && g < usadosx.size())
        {
            if (a == usadosx[g] && b == usadosy[g])
            {
                encontrado = true;
                cout << "Ya ha cavado ahí, pruebe con otra casilla" << endl;
            }
            g++;
        }
        if (!encontrado)
        {
            ultimajugada = minascerca(a,b);
            anadirusados(a,b);

            cout << (*(this)) << endl;
            jugadaactual++;
        }



    }
    if (ultimajugada == -1)
        cout << "Has perdido" << endl;
    else
        cout << "Has ganado" << endl;
}


int main ()
{
    int filas;
    int columnas;
    int minastotales;
    bool esvalido = true;
    int contador = 0;
    cout << "Introduzca las dimensiones del tablero" << endl;
    cin >> filas >> columnas;
    while (filas<=0 || columnas <= 0)
    {
        cout << "Las filas y columnas deben ser positivas" << endl;
        cin >> filas >> columnas;
    }

    TableroBuscaMinas mitablero (filas,columnas);
    cout << "Introduzca el numero total de minas" << endl;
    cin >> minastotales;
    while (minastotales <= 0)
    {
        cout << "Debe haber al menos una mina" << endl;
        cin >> minastotales;
    }
    while (esvalido && contador < minastotales)
    {
        cout << "introduzca la posicion de la mina" << endl;
        cin >> filas >> columnas;
        if (filas>0 && filas<mitablero.tamanofilas()-1 && columnas>0 && columnas<mitablero.tamanocolumnas()-1 )
        {
            contador++;
        }
        mitablero.setmina(filas, columnas);
    }

    mitablero.jugar(minastotales);
    return 0;
}





