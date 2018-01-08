#include <iostream>
using namespace std;

int main ()
{
	//Dados dos vertices opuestos de un rectangulko comprobar si un punto A pertenece al interior, borde o no pertenece a este.
	double x1, y1;
	double x2, y2;
	double a1, a2;

	cout << "Introduzca dos vertices del rectangulo que sean opuestos" << endl;
	cin >> x1 >> y1;
	cin >> x2 >> y2;
	cout << "Introduzca un punto" << endl;
	cin >> a1 >> a2;

	if ( (a1<x1 && a1<x2) || (a1>x1 && a1>x2) || (a2<y1 && a2<y2) || (a2>y1 && a2>y2) )
	{
		cout << "EL punto no esta en el rectangulo";
	}
	else if ( (a1==x1 && ( ( a2>=y1 && a2<=y2) || (a2<=y1 && a2>=y2) ) )  ||
				 (a1==x2 && ( ( a2>=y1 && a2<=y2) || (a2<=y1 && a2>=y2) ) )  ||
				 (a2==y1 && ( ( a1>=x1 && a1<=x2) || (a1<=x1 && a1>=x2) ) )  ||
				 (a2==y2 && ( ( a1>=x1 && a1<=x2) || (a1<=x1 && a1>=x2) ) ) )
	{
		cout << "El punto pertenece al borde del rectangulo";
	}
	else
	{
		cout << "El punto esta dentro del rectangulo";
	}
}
