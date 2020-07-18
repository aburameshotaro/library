#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdlib.h>   
#include <bits/stdc++.h> 
#include <windows.h>
#include <iomanip>
#include <cctype>
#include <algorithm>
#include <stdio.h>
#include <ctype.h>
using namespace std;

#pragma pack(push,1)
struct Ksiazka{
	long numerKolejny;
	char sygnatura[61];
	char autor[61];
	char tytul[91];
	char ISBN[21];
	char wydawnictwo[51];
	short rokWydania;
	Ksiazka(long nr): numerKolejny(nr){
	}
	Ksiazka(){
	}
	bool operator < (const Ksiazka& k2) const{
		string autor1(autor);
		string autor2(k2.autor);
		string tytul1(tytul);
		string tytul2(k2.tytul);
		if(autor1!=autor2)
		return (autor1<autor2);
		else
		return (tytul1<tytul2);	
	}
	
	bool operator == (const Ksiazka &other) const{
		return (autor==other.autor)&&(tytul==other.tytul)&&(ISBN==other.ISBN);
	}
	
};
#pragma pack(pop)


ostream &operator<<(ostream &out, const Ksiazka& ksiazki){
	out<< setw(6)<<ksiazki.numerKolejny<<". "<<setw(10) <<ksiazki.sygnatura<<"; "<<setw(29)<<ksiazki.autor<<"; "<<setw(28)<<ksiazki.tytul<<"; "<<setw(15)<<ksiazki.ISBN<<"; "<<setw(14)<<ksiazki.wydawnictwo<<"; "<<setw(4)<<ksiazki.rokWydania;
	return out;
}

string przygotujString(string s){
	transform(s.begin(), s.end(), s.begin(), ::toupper);
	s.erase(remove_if(s.begin(), s.end(), ::isspace), s.end());
	return s;
}

bool porownaj(char a[],string b){
	b=przygotujString(b);
    for(int i=0, j=0;a[i]!='\0';i++,j++){
       		if(!(isspace(a[j])))
				if(toupper(a[j])!=b[i])
            		return false;
            	else;
            else
            	i--;
    }
    return true;
}


class Biblioteka{
	private:
	long liczbaKsiazek;
	vector<Ksiazka> ksiazki;
	
	public:
	Biblioteka(){
		liczbaKsiazek=0;
		ifstream input;
		Ksiazka wczytywanaKsiazka;
		input.open("biblioteka.bin", ios::binary);
		
		if(input.is_open()){
			input.read(reinterpret_cast<char *> (&liczbaKsiazek), sizeof(int));
			while(input.read(reinterpret_cast<char *>(&wczytywanaKsiazka), sizeof(Ksiazka))){
				ksiazki.push_back(wczytywanaKsiazka);
			
			}
			input.close();
		}
		else{
			cout<<"Nie udało się otworzyć pliku: " << "biblioteka.bin"<<endl;
		}
	}
	
	void pokazMenu(){
		cout<<"1. Dodaj książkę \n2. Listuj książki \n3. Wyszukaj książkę \n4. Usuń książkę \n5. Zapisz do pliku \n6. Usuń plik z danymi \n7. Zakończ program \n>"<<flush;
	}
	
	void obslugaMenu(){
		int wybor;
		string linia;
		do {
			wybor=0;
			pokazMenu();
			while(!(wybor<=7 && wybor>=1)){
				getline(cin, linia);
				wybor= atoi(linia.c_str());
				
				if(!(wybor<=7 && wybor>=1)){
					cout<<"Proszę o podanie liczby całkowitej z przedzialu 1-7"<<endl;
					pokazMenu();
				}
			}
			
			switch(wybor){
				case 1:
					dodajKsiazke();
					break;
				case 2:
					listujKsiazki();
					break;
				case 3:
					wyszukajKsiazke();
					break;
				case 4:
					usunKsiazke();
					break;
				case 5:
					zapiszDoPliku();
					break;
				case 6:
					usunPlik();
					break;
			}
		}
		while(wybor!=7);
	}
	
	void dodajKsiazke(){
		string line;
		Ksiazka nowaKsiazka(liczbaKsiazek);
		cout<<"Podaj sygnaturę książki (maks 60 znaków) (aby anulować naciśnij e i enter) \n>"<<flush;
		getline(cin, line);
		if (line == "e")
			return;
		strncpy(nowaKsiazka.sygnatura, line.c_str(), 60);
		cout<<"Podaj autora ksiazki (maks 60 znaków) (aby anulować naciśnij e i enter) \n>"<<flush;
		getline(cin, line);
		if (line == "e")
			return;
		strncpy(nowaKsiazka.autor, line.c_str(), 60);
		cout<<"Podaj tytuł książki (maks 90 znaków) (aby anulować nacisnij e i enter) \n>"<<flush;
		getline(cin, line);
		if (line == "e")
			return;
		strncpy(nowaKsiazka.tytul, line.c_str(), 90);
		cout<<"Podaj ISBN ksiazki (maks 20 znaków) (aby anulować nacisnij e i enter) \n>"<<flush;
		getline(cin, line);
		if (line == "e")
			return;
		strncpy(nowaKsiazka.ISBN, line.c_str(), 20);
		cout<<"Podaj wydawnictwo książki (maks 50 znaków) (aby anulować naciśnij e i enter) \n>"<<flush;
		getline(cin, line);
		if (line == "e")
			return;
		strncpy(nowaKsiazka.wydawnictwo, line.c_str(), 50);
		cout<<"Podaj rok wydania książki \n>"<<flush;
		getline(cin, line);
		nowaKsiazka.rokWydania = atoi(line.c_str());
		ksiazki.push_back(nowaKsiazka);
		liczbaKsiazek++;
		cout<<endl <<"Następująca książka została dodana: "<< endl<<ksiazki.back()<<endl<<endl;
	}
	
	void listujKsiazki(){
		sort(ksiazki.begin(),ksiazki.end());
		cout<<endl<<"Książki to" << endl;
		cout<< setw(6)<<"Nr"<<". "<<setw(10) <<"Sygnatura"<<"; "<<setw(29)<<"Autor"<<"; "<<setw(28)<<"Tytuł"<<"; "<<setw(15)<<"ISBN"<<"; "<<setw(14)<<"Wydawnictwo"<<"; "<<setw(4)<<"RokW" <<endl;
		for(int i=0;i<ksiazki.size();++i)
			cout<<ksiazki[i]<<endl;
		cout<<endl;		
	}
	
	void wyszukajKsiazke(){
		int wybor =0;
		string linia;
		cout<<"1. Wyszukaj po autorze \n2. Wyszukaj po tytule \n3. Wyszukaj po autorze i tytule \n4. Anuluj szukanie \n>"<<flush;
		while(!(wybor<=4 && wybor>=1)){
				getline(cin, linia);
				wybor= atoi(linia.c_str());
				
				if(!(wybor<=4 && wybor>=1)){
					cout<<"1. Wyszukaj po autorze \n2. Wyszukaj po tytule \n3. Wyszukaj po autorze i tytule \n4. Anuluj szukanie "<<endl;
					cout<<"Prosze o podanie liczby całkowitej z przedzialu 1-4 \n>"<<flush ;
				}
			}
			string autor, tytul;
			switch(wybor){
				
				case 1:
					cout<<"Podaj autora: (naciśnij e i enter aby anulować) \n>" <<flush;
					getline(cin, autor);
					if (autor == "e")
						return;
					
					cout<<"Wyszukane książki to:"<<endl;
					autor=przygotujString(autor);
					for(int i=0;i<ksiazki.size();++i){
						string autorKsiazki(ksiazki[i].autor);
						autorKsiazki=przygotujString(autorKsiazki);
						if (autor==autorKsiazki)
							cout<<ksiazki[i]<<endl;
					}
					break;
				
				case 2:
					cout<<"Podaj tytuł: (nacisnij e i enter aby anulować) \n>" <<flush;
					getline(cin, tytul);
					if (tytul == "e")
						return;
					
					cout<<"Wyszukane książki to:"<<endl;
					tytul=przygotujString(tytul);
					for(int i=0;i<ksiazki.size();++i){
						string tytulKsiazki(ksiazki[i].tytul);
						tytulKsiazki = przygotujString(tytulKsiazki);
						if (tytul==tytulKsiazki)
							cout<<ksiazki[i]<<endl;
					}
					break;
					
				case 3:
					cout<<"Podaj autora: (naciśnij e i enter aby anulować) \n>" <<flush;
					getline(cin, autor);
					if (autor == "e")
						return;
					cout<<"Podaj tytuł: (naciśnij e i enter aby anulować) \n>" <<flush;
					getline(cin, tytul);
					if (tytul == "e")
						return;
					
					cout<<"Wyszukane książki to:"<<endl;
					autor=przygotujString(autor);
					tytul=przygotujString(tytul);
					for(int i=0;i<ksiazki.size();++i){
						string tytulKsiazki(ksiazki[i].tytul), autorKsiazki(ksiazki[i].autor);
						tytulKsiazki = przygotujString(tytulKsiazki);
						autorKsiazki=przygotujString(autorKsiazki);
						if (tytul==tytulKsiazki && autor==autorKsiazki)
							cout<<ksiazki[i]<<endl;
					}
						
					break;
			}
			cout<<endl;
		
	}
	
	void usunKsiazke(){
		int wybor =0;
		string linia;
		cout<<"1. Wyszukaj po autorze \n2. Wyszukaj po tytule \n3. Wyszukaj po autorze i tytule \n4. Anuluj szukanie \n>"<<flush;
		while(!(wybor<=4 && wybor>=1)){
				getline(cin, linia);
				wybor= atoi(linia.c_str());
				
				if(!(wybor<=4 && wybor>=1)){
					cout<<"1. Wyszukaj po autorze \n2. Wyszukaj po tytule \n3. Wyszukaj po autorze i tytule \n4. Anuluj szukanie "<<endl;
					cout<<"Proszę o podanie liczby całkowitej z przedziału 1-4 \n>"<<flush;
				}
			}
			string autor, tytul;
			switch(wybor){
				
				case 1:
					cout<<"Podaj autora, którego wszystkie książki zostaną usunięte: (naciśnij e i enter aby anulować) \n>" <<flush;
					getline(cin, autor);
					if (autor == "e")
						return;
				
					for(vector<Ksiazka>::iterator it=ksiazki.begin(); it!=ksiazki.end();){
						if (porownaj((*it).autor, autor)){
							it=ksiazki.erase(it);
							cout<<"Usunięto książkę."<<endl;
						}
							
						else
							++it;
					}
					break;
				
				case 2:
					cout<<"Podaj tytuł (wszystkie książki o podanym tytule zostana usunięte): (naciśnij e i enter aby anulowac) \n>" <<flush;
					getline(cin, tytul);
					if (tytul == "e")
						return;
					
					for(vector<Ksiazka>::iterator it=ksiazki.begin(); it!=ksiazki.end();){
						if (porownaj((*it).tytul, tytul)){
							it=ksiazki.erase(it);
							cout<<"Usunięto książkę."<<endl;
						}	
						else
							++it;
					}
					break;
					
				case 3:
					cout<<"Podaj autora: (naciśnij e i enter aby anulować) \n>" <<flush;
					getline(cin, autor);
					if (autor == "e")
						return;
					cout<<"Podaj tytuł: (naciśnij e i enter aby anulować) \n>" <<flush;
					getline(cin, tytul);
					if (tytul == "e")
						return;
						
					for(vector<Ksiazka>::iterator it=ksiazki.begin(); it!=ksiazki.end();){
						if (porownaj((*it).tytul, tytul) && porownaj((*it).autor, autor)){
							it=ksiazki.erase(it);
							cout<<"Usunięto książkę."<<endl;
						}
							
						else
							++it;
					}
						
					break;
			}
			cout<<endl;
	}
	
	void zapiszDoPliku(){
		ofstream output;
		output.open("biblioteka.bin", ios::binary);
		
		if(output.is_open()){
			output.write(reinterpret_cast<char *> (&liczbaKsiazek), sizeof(int));
			for(long i=0; i<ksiazki.size();++i)
				output.write(reinterpret_cast<char *>(&ksiazki[i]), sizeof(Ksiazka));
			output.close();
			cout<<endl<<"Pomyślnie zapisano do pliku." << endl<<endl;
		}
		else
			cout<<endl<<"Nie udało się utworzyć pliku: " << "biblioteka.bin"<<endl <<endl;
	}
	
	void usunPlik(){
		cout<<"Potwierdź chęć usunięcia wszystkich danych, wciskając 't' i enter"<<endl;
		string wybor;
		getline(cin,wybor);
		if(wybor!="t" && wybor !="T" )
		return;
		ofstream output;
		output.open("biblioteka.bin", ios::binary);
		if(output.is_open()){
			output.close();
			cout<< endl<<"Udało się usunąć plik z danymi." <<endl<<endl;
		}
		
		else
		cout<<endl<<"Nie udało się usunąć zapisu z pliku biblioteka.bin"<<endl<<endl;
	}
	
};


int main(){
	SetConsoleCP( 852 );
    setlocale ( LC_ALL, "" );
	Biblioteka biblioteka;
	
	biblioteka.obslugaMenu();
	
	return 0;	
}
