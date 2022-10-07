#include <iostream>
using namespace std;

string szyfrowanie(string tekst, int klucz)
{
	string wynik = "";
	
	for (int i = 0; i < tekst.length(); i++) {
		if (isupper(tekst[i])) 
		{
			if (int(tekst[i] + klucz) < 65)
			{
				wynik = wynik + char(int(tekst[i] + klucz - 64) % 26 + 90); 
			}			
			else
			{
				wynik = wynik + char(int(tekst[i] + klucz - 65) % 26 + 65); 
			}
			
		}		
		else
		{
			if (int(tekst[i] + klucz) < 97)
			{
				wynik = wynik + char(int(tekst[i] + klucz - 96) % 26 + 122); 
			}			
			else
			{
				wynik = wynik + char(int(tekst[i] + klucz - 97) % 26 + 97); 
			}
		}			
	}
	
	return wynik; 
}

int main()
{
	string tekst;
	cout << "Tutaj wpisz przykladowy tekst: " << endl; 
	
	cin >> tekst;
	
	int klucz;	
	cout << "Tutaj wprowadz klucz do szyfrowania: " << endl;  
	cin >> klucz;
	
	cout << "Tutaj dostajesz swoj zaszyfrowany tekst: " << szyfrowanie(tekst, klucz) << endl; 
	return 0;
}
