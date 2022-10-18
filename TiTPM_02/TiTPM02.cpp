#include <iostream>
#include <string>
#include <queue>
#include <unordered_map>
using namespace std;

// węzeł drzewa
struct wezel
{
	char ch;
	int czestotliwosc;
	wezel* lewy, * prawy;
};

//nowe drzewo
wezel* pobierzWezel(char ch, int czestotliwosc, wezel* lewy, wezel* prawy)
{
	wezel* node = new wezel();

	node->ch = ch;
	node->czestotliwosc = czestotliwosc;
	node->lewy = lewy;
	node->prawy = prawy;

	return node;
}

// porównanie
struct comp
{
	bool operator()(wezel* l, wezel* r)
	{
		return l->czestotliwosc > r->czestotliwosc;
	}
};
void koduj(wezel* root, string str,
	unordered_map<char, string>& kodHuffmana)
{
	if (root == nullptr)
		return;

	// liść
	if (!root->lewy && !root->prawy) {
		kodHuffmana[root->ch] = str;
	}

	koduj(root->lewy, str + "0", kodHuffmana);
	koduj(root->prawy, str + "1", kodHuffmana);
}

// odkodowanie
void decode(wezel* root, int& index, string str)
{
	if (root == nullptr) {
		return;
	}

	// liść
	if (!root->lewy && !root->prawy)
	{
		cout << root->ch;
		return;
	}

	index++;

	if (str[index] == '0')
		decode(root->lewy, index, str);
	else
		decode(root->prawy, index, str);
}

// Budowanie drzewa i dekodowanie wejścia
void budujDrzewo(string text)
{
	unordered_map<char, int> czestotliwosc;
	for (char ch : text) {
		czestotliwosc[ch]++;
	}

	priority_queue<wezel*, vector<wezel*>, comp> pq;

	for (auto pair : czestotliwosc) {
		pq.push(pobierzWezel(pair.first, pair.second, nullptr, nullptr));
	}

	while (pq.size() != 1)
	{
		// Usuwamy dwa węzły z najwyższym priorytetem - najniższą częstotliwością z kolejki
		wezel* lewy = pq.top(); pq.pop();
		wezel* prawy = pq.top();	pq.pop();

		// Tworzymy nowy węzeł wewnętrzny
		int sum = lewy->czestotliwosc + prawy->czestotliwosc;
		pq.push(pobierzWezel('\0', sum, lewy, prawy));
	}

	wezel* root = pq.top();

	unordered_map<char, string> kodHuffmana;
	koduj(root, "", kodHuffmana);

	cout << "\nKod Huffmana ma postac: \n" << '\n';
	for (auto pair : kodHuffmana) {
		cout << pair.first << " " << pair.second << '\n';
	}



	cout << "\nOryginalny tekst: \n" << text << '\n' << endl;



	// zakodowany tekst
	string str = "";
	for (char ch : text) {
		str += kodHuffmana[ch];
	}

	cout << "\nZakodowany tekst: \n" << str << '\n';

	// dekodujemy wcześniej zakodowany kod
	int index = -1;
	cout << "\nOdkodowany tekst: \n";
	while (index < (int)str.size() - 2) {
		decode(root, index, str);
	}
}

int main()
{
	string tekst;
	cout << "Wpisz tekst, ktory chcesz zakodowac: " << endl;
	cin >> tekst;

	string text = tekst;

	budujDrzewo(text);
	int i = 0, alphabet[26] = { 0 }, j;
	while (text[i] != '\0') {
		if (text[i] >= 'a' && text[i] <= 'z') {
			j = text[i] - 'a';
			++alphabet[j];
		}
		++i;
	}
	cout << "\nLiczba znakow wystepujacych w kodzie:" << endl;
	for (i = 0; i < 26; i++)
		cout << char(i + 'a') << " : " << alphabet[i] << endl;

	return 0;
}