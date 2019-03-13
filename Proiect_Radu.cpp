#include <iostream>
using namespace std;
class Multime
{
private:
	int v[1000];
	int n;
public:
	void transformare();
	friend ostream & operator << (ostream &out, const Multime &c);
	friend istream & operator >> (istream &in, Multime &c);
	friend Multime & operator + (Multime A, Multime B);
	friend Multime & operator * (Multime A, Multime B);
	friend Multime & operator - (Multime A, Multime B);
	friend class Multime_perechi produs_cartezian(Multime A, Multime B);
};

class Pereche
{
private:
	int a, b;
public:
	friend ostream & operator << (ostream &out, const Pereche &c);
	friend istream & operator >> (istream &in, Pereche &c);
	friend class Multime_perechi;
	friend class Multime_perechi produs_cartezian(Multime A, Multime B);

};

class Multime_perechi
{
private:
	Pereche per[100];
	int nr;
public:
	friend ostream & operator << (ostream &out, const Multime_perechi &c);
	friend istream & operator >> (istream &in, Multime_perechi &c);
	friend class Multime_perechi produs_cartezian(Multime A, Multime B);
};

ostream & operator << (ostream &out, const Pereche &c)
{
	out << "(" << c.a << "," << c.b << ") ";
	return out;
}

istream & operator >> (istream &in, Pereche &c)
{
	cout << "Perechea este : ";
	in >> c.a;
	in >> c.b;
	return in;
}

ostream & operator << (ostream & out, const Multime_perechi & c)
{
	for (int i = 0; i < c.nr; i++)
		cout << c.per[i];

	return out;
}

istream & operator >> (istream &in, Multime_perechi &c)
{
	cout << "Nr de perechi : ";
	in >> c.nr;
	cout << endl;

	Pereche help;

	for (int i = 0; i < c.nr; i++)
	{
		cin >> help;
		c.per[i] = help;
	}
	return in;
}

Multime & operator+(Multime A, Multime B)
{
	Multime rezultat;
	rezultat.n = A.n;
	int ok;
	for (int i = 0; i < A.n; i++)
		rezultat.v[i] = A.v[i];

	for (int i = 0; i < B.n; i++)
	{
		ok = 1;
		for (int j = 0; j < rezultat.n; j++)
		{
			if (rezultat.v[j] == B.v[i])
			{
				ok = 0;
				break;
			}
		}
		if (ok == 1)
		{
			rezultat.v[rezultat.n] = B.v[i];
			rezultat.n++;
		}
	}
	return rezultat;
}

Multime & operator-(Multime A, Multime B)
{
	Multime rezultat;
	int ok;
	rezultat.n = 0;
	for (int i = 0; i < A.n; i++)
	{
		ok = 1;
		for (int j = 0; j < B.n; j++)
			if (A.v[i] == B.v[j])
			{
				ok = 0;
				break;
			}
		if (ok == 1)
			rezultat.v[rezultat.n++] = A.v[i];
	}
	return rezultat;
}

Multime & operator*(Multime A, Multime B)
{
	Multime rezultat;
	rezultat.n = 0;
	for (int i = 0; i < A.n; i++)
		for (int j = 0; j < B.n; j++)
		{
			if (A.v[i] == B.v[j])
				rezultat.v[rezultat.n++] = A.v[i];
		}
	cout << "n=" << rezultat.n << endl;
	return rezultat;
}

void Multime::transformare()
{
	for (int i = 0; i < n - 1; i++)
		for (int j = i + 1; j < n; j++)
			if (v[i] == v[j])
			{
				for (int k = j; k < n - 1; k++)
					v[k] = v[k + 1];
				n--;
				j--;
			}
}

ostream & operator << (ostream &out, const Multime &c)
{
	for (int i = 0; i < c.n; i++)
		out << "[" << c.v[i] << "] ";
	out << endl;
	return out;
}

istream & operator >> (istream &in, Multime &c)
{
	cout << "Nr de numere :";
	int x;

	in >> c.n;
	for (int i = 0; i < c.n; i++)
	{
		cout << "x = ";
		in >> c.v[i];
		cout << endl;
	}

	return in;
}

Multime_perechi produs_cartezian(Multime A, Multime B)
{
	Multime_perechi rezultat;
	rezultat.nr = 0;
	for (int i = 0; i < A.n; i++)
	{
		for (int j = 0; j < B.n; j++)
		{
			rezultat.per[rezultat.nr].a = A.v[i];
			rezultat.per[rezultat.nr].b = B.v[j];
			rezultat.nr++;
		}
	}
	return rezultat;
}

int main()
{
	Multime mult1;
	Multime mult2;
	cin >> mult1;
	cout << endl;
	cin >> mult2;
	mult1.transformare();
	mult2.transformare();
	cout << "CELE 2 MULTIMI SUNT :\n\n";
	cout << "multime 1 : " << mult1;
	cout << "multime 2 : " << mult2;
	cout << endl;
	Multime_perechi pc;

	pc = produs_cartezian(mult1, mult2);
	cout << pc << endl;
	return 0;
}
