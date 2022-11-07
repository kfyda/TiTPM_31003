#include <iostream>
#include <string>
#include <algorithm>
#include <map>
#include <vector>

using namespace std;

vector<float> mnoznik;


void wypisanie(vector<char> znaki, map<char, float> mymap, string text, int licznik, float mapFirtstValue)
{
    cout<<endl;
    if(licznik<text.length())
    {
        if(licznik == 0)
        {
    	    for(int i=0; i<znaki.size(); i++)
            {
        	    cout<<mymap.find(znaki[i])->first <<" -> " <<mymap.find(znaki[i])->second<<endl;
    	    }
        }
    	float newPartition;
    	float tempMap = mapFirtstValue;
    	for(int i=0; i<znaki.size(); i++)
        {
        	cout<< "[" << tempMap << ";" << tempMap + (mymap.find(znaki[i])->second)<<")"<<endl;
        	if(text[licznik] == mymap.find(znaki[i])->first)
        	{
        	    newPartition = mymap.find(znaki[i])->second;
        	    mapFirtstValue = tempMap;
        	    
        	}
        	tempMap += mymap.find(znaki[i])->second;
    	}
    
    }	
}

int main()
{
    string text, text_temp;
    cout<<"Podaj slowo do zakodowania:"<<endl;
    cin>>text;text_temp = text;
    sort(text_temp.begin(), text_temp.end());
    cout<<endl<<"Uzyte znaki w tym slowie: "<<endl<<text_temp<<endl;
    
    map<char, float> mymap;
    vector<char> znaki;
    
    char znak = text_temp[0];
    int counter = 0;
    for(int i=0; i<text_temp.length(); i++)
    {
        
        if(i == text_temp.length()-1 && znak != text_temp[i])
        {
            mymap.insert(pair<char,float>(znak, float(counter)/float(text.length())));
            znaki.push_back(znak);
            mnoznik.push_back(float(counter)/float(text.length()));
            mymap.insert(pair<char,float>(text_temp[i], float(1)/float(text.length())));
            znaki.push_back(text_temp[i]);
            mnoznik.push_back(float(counter)/float(text.length()));
            break;
        }
        if(znak != text_temp[i] || i == text_temp.length()-1)
        {
            if(i == text_temp.length()-1) counter++;
            mymap.insert(pair<char,float>(znak, float(counter)/float(text.length())));
            znaki.push_back(znak);
            mnoznik.push_back(float(counter)/float(text.length()));
            counter = 0;
            znak =text_temp[i];
        }
        counter++;
    }
    
	wypisanie(znaki, mymap, text, 0, 0);
    
    return 0;
}
