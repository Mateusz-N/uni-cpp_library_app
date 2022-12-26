#include <cmath>
#include <algorithm>
#include <ctime>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <windows.h>
using namespace std;

/* Funkcja zwracaj�ca najd�u�szy wiersz w tablicy 2d ------------------------------------------ Funkcja zwracaj�ca najd�u�szy wiersz w tablicy 2d ----------------------------------------- Funkcja zwracaj�ca najd�u�szy wiersz w tablicy 2d */
vector<string> max_element(vector<vector<string>> tab) {
	vector<string> max = {};
	for(int i = 0; i < tab.size(); i++) {
		if(tab[i].size() > max.size()) max = tab[i];
	}
	return max;
}

/* Funkcja rozdzialj�ca �a�cuchy znakowe na podstawie znaku ------------------------------- Funkcja rozdzialj�ca �a�cuchy znakowe na podstawie znaku ------------------------------- Funkcja rozdzialj�ca �a�cuchy znakowe na podstawie znaku */
vector<string> split(string wpis, char znak) {
    stringstream ss(wpis);
    string atrybut;
    vector<string> atrybuty;
    while (getline(ss, atrybut, znak)) {
       atrybuty.push_back(atrybut);
    }
    return atrybuty;
}

/* Funkcja rozdzielaj�ca �a�cuchy znakowe co <dlugosc> znak�w ---------------------------- Funkcja rozdzielaj�ca �a�cuchy znakowe co <dlugosc> znak�w ---------------------------- Funkcja rozdzielaj�ca �a�cuchy znakowe co <dlugosc> znak�w */
vector<string> br(string komorka, int dlugosc) {
	vector<string> linie_komorki;
	for (size_t a = 0; a < komorka.size(); a += dlugosc) {
    	linie_komorki.push_back(komorka.substr(a, dlugosc));		
	}
    return linie_komorki;
}

void wip() {cout << "\nOpcja dost�pna tylko w wersji Premium! Wp�a� conajmniej $21,37 na konto programisty aby odblokowa� konto OnlyFa-- znaczy, wersj� Premium.\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\tNo dobra, �artuj�, po prostu jeszcze tego nie zaimplementowa�em. Prosz� mnie nie pozywa�. B�agam. -MN\n";}

/* G��wna cz�� programu ------------------------------------------------------------------------------------ G��wna cz�� programu ----------------------------------------------------------------------------------- G��wna cz�� programu */
int main() {
	
	/* Zwi�kszenie bufora konsoli, by poprawnie wy�wietla�o spis ksi��ek -------------- Zwi�kszenie bufora konsoli, by poprawnie wy�wietla�o spis ksi��ek ------------- Zwi�kszenie bufora konsoli, by poprawnie wy�wietla�o spis ksi��ek */
	COORD c;
    c.X = 1920;
    c.Y = 1080;
    SetConsoleScreenBufferSize( GetStdHandle( STD_OUTPUT_HANDLE ), c );
	
	/* Polskie znaki w konsoli ----------------------------------------------------------------------------- Polskie znaki w konsoli ---------------------------------------------------------------------------- Polskie znaki w konsoli */
	SetConsoleCP(852);
	setlocale(LC_ALL,"");
	
	/* Deklaracja zmiennych potrzebnych w programie ---------------------------------------------- Deklaracja zmiennych potrzebnych w programie -------------------------------------------- Deklaracja zmiennych potrzebnych w programie */
	long id;
	string sygnatura, autor, tytul, isbn, wydawnictwo, rodzaj, gatunek, komenda;
	short rok_wydania;
	
	time_t t = time(0);						/*----------------------------------------------------------------------------------------------------------------------------*/
	tm *const tp = localtime(&t);			/* Obecny rok; por�wnywany z rokiem wydania dodawanej ksi��ki, aby uniemo�liwi� wprowadzenie roku, kt�ry jeszcze nie nadszed� */
	short obecny_rok = tp->tm_year + 1900;	/*----------------------------------------------------------------------------------------------------------------------------*/
	
	bool blad; // Zmienna odpowiedzialna za ustawianie stanu poprawno�ci danych wej�ciowych przy dodawaniu ksi��ki
	
	vector<vector<string>> pozycja; // Stworzenie dwuwymiarowej tablicy, kt�ra b�dzie przechowywa� ksi��ki
	vector<string> kolumna; // Zmienna pomocnicza do rozdzielania jednoliniowych komend dodania i usuni�cia ksi��ki
	vector<string> linia; // Zmienna pomocnicza do rozbijania warto�ci kom�rek w spisie na wiele linii
	vector<vector<string>> duza_komorka; // Tablica przechowuj�ca warto�ci kom�rek, kt�re nie mieszcz� si� w jednym wierszu, wraz z indeksami kolumn, dla kt�rych do tego dochodzi
	vector<string> max_komorka; // Tablica przechowuj�ca cz�ony (a na ko�cu indeks kolumny, do kt�rej nale�y) najd�u�szej 'du�ej kom�rki'	
	vector<int> kol_idx; // Tablica przechowuj�ca indeksy kolumn 'du�ych kom�rek'
	
	fstream plik;
	int rozmiar; // Przechowuje rozmiar pliku BIN
	char wypis_z_bazy[1]; // Bufor znakowy przy odczytywaniu z pliku BIN
	vector<string> wypis_z_bazy_v; // Przechowuje rekordy odczytane z pliku BIN
	string wzb;
	stringstream wpis_do_bazy; // Przechowuje rekordy dodane podczas bie��cej sesji
	string wpis_do_bazy_s; // Po�rednik mi�dzy wpis_do_bazy a plikiem BIN
	
	int ileUsunieto = 0;
	string ksiazkaOdmiana = "ksi��ek";
	
	/* Wiadomo�� powitalna ----------------------------------------------------------------------------------- Wiadomo�� powitalna ---------------------------------------------------------------------------------- Wiadomo�� powitalna */
	cout <<
		"        _ _ _ _ ___ ____ _  _ _   _        \n"
		"        | | | |  |  |__| |\\/|  \\_/       \n"
		"        |_|_| |  |  |  | |  |   |          \n"
		"                                           \n"
		"                  _ _ _                    \n"
		"                  | | |                    \n"
		"                  |_|_|                    \n"
		"                                           \n"
		"___  _ ___  _    _ ____ ___ ____ ____ ____ \n"
		"|__] | |__] |    | |  |  |  |___ |    |___ \n"
		"|__] | |__] |___ | |__|  |  |___ |___ |___ \n"
		"                                           \n";

	cout << "Wybierz jedn� z poni�szych funkcji wpisuj�c jej (numer) lub zwi�zan� z ni� s�own� komend�. Wpisz \'/help\', je�li potrzebujesz pomocy. Wpisz \'/exit\' aby opu�ci� program.\n";
	cout << "(1) Znajd� ksi��k�\n(2) Spis ksi��ek\n(3) Dodaj ksi��k�\n(4) Usu� ksi��k�\n\n";
	
	/* Wczytanie rekord�w, kt�re s� ju� w bazie (pliku BIN) --------------------------------- Wczytanie rekord�w, kt�re s� ju� w bazie (pliku BIN) --------------------------------- Wczytanie rekord�w, kt�re s� ju� w bazie (pliku BIN) */
	plik.open("Baza biblioteczna.bin", ios::in | ios::binary);
	plik.seekg(0, ios::end); // Wska�nik ko�ca pliku
	rozmiar = (int) plik.tellg();
	plik.seekg(0, ios::beg); // Wska�nik pocz�tku pliku
	while(plik.tellg() < rozmiar) {
		plik.read((char*) wypis_z_bazy, sizeof(wypis_z_bazy)); // Przechowuje zawarto�� pliku w tablicy znak�w wypis_z_bazy
		wzb.append(wypis_z_bazy); // Konwersja tablicy znak�w do �a�cucha znakowego
	}
	wypis_z_bazy_v = split(wzb, '\n'); // Rozbicie zawarto�ci pliku na wiersze (rekordy)
	for (int z = 0; z < wypis_z_bazy_v.size(); z++) {
		pozycja.push_back(split(wypis_z_bazy_v[z], '|')); // Rozbicie rekord�w na kom�rki i wpisanie ich do tablicy ksi��ek
	}
	if(plik.is_open()) plik.close();
	
	// Usuni�cie '�mieci' (\r, \n) z wczytanych danych
	for (int poz = 0; poz < pozycja.size(); poz++) {
		for (int atr = 0; atr < pozycja[poz].size(); atr++) {
			pozycja[poz][atr].erase(remove(pozycja[poz][atr].begin(), pozycja[poz][atr].end(), '\r'), pozycja[poz][atr].end());
			pozycja[poz][atr].erase(remove(pozycja[poz][atr].begin(), pozycja[poz][atr].end(), '\n'), pozycja[poz][atr].end());
		}
	}
	
	/* Interakcja u�ytkownika z programem ------------------------------------------------------------ Interakcja u�ytkownika z programem ------------------------------------------------------------ Interakcja u�ytkownika z programem */
	while(true) {
		
		getline(cin, komenda);
		
		/* Komendy pomocy -------------------------------------------------------------------------------------- Komendy pomocy -------------------------------------------------------------------------------------- Komendy pomocy */
		// HELP i INFO
		if (komenda == "/help") cout << 
			"Wywo�anie funkcji wygl�da nast�puj�co:\n\n"
			"1      \t      \t      \t      \t      \t      \t      \t      <- wprowadzone przez u�ytkownika\n"
			"Wpisz s�owo (s�owa) kluczowe, aby odnale�� to, czego szukasz. <- wyprowadzone przez program\n\n";
		
		if (komenda == "/help" || komenda == "/info") cout <<
			"Je�li chcesz dowiedzie� si� wi�cej o danej funkcji programu, wpisz /info [numer], np.:\n\n"
			"/info 1 \t \t \t \t \t \t <- wprowadzone przez u�ytkownika,\n"
			"Wpisz \'1\' lub \'/znajdz\', a program sam ci� poprowadzi... <- wyprowadzone przez program.\n\n";
		
		// SPIS KSI��EK
		else if (komenda == "/info 1") cout <<
			"Wpisz \'1\' lub \'/znajdz\', a program sam ci� poprowadzi. Alternatywnie, mo�esz od razu wyszuka� ksi��k� wpisuj�c \'/znajdz [slowo (slowa) kluczowe]\', np.:\n\n"
			"/znajdz Pinokio   \t   \t   \t   <- wprowadzone przez u�ytkownika\n"
			"Uda�o nam si� znale�� nast�puj�ce pozycje: <- wyprowadzone przez program\n"
			"...   \t   \t   \t   \t   \t   <-\n"
			"...   \t   \t   \t   \t   \t   <-\n"
			"...   \t   \t   \t   \t   \t   <-\n\n"
			"Mo�esz tak�e wyszuka� ksi��k� wed�ug konkretnego atrybutu. Poni�ej znajduje si� lista oraz sk�adnia s�u��cych do tego polece�:\n\n"
			"/znajdz -id [id]          <- np. \'/znajdz -id 503\' zwr�ci ksi��k� o ID 503,\n"
			"/znajdz -t  [tytul]       <- np. \'/znajdz -t Harry Potter\' zwr�ci ksi��ki maj�ce w tytule fraz� \'Harry Potter\',\n"
			"/znajdz -a  [autor]       <- np. \'/znajdz -a Stephen King\' zwr�ci ksi��ki autorstwa Stephena Kinga,\n"
			"/znajdz -rw [rok_wydania] <- np. \'/znajdz -rw 1789\' zwr�ci ksi��ki wydane w roku 1789,\n"
			"/znajdz -i  [isbn]        <- np. \'/znajdz -i 978-83-900210-1-0\' zwr�ci ksi��k� o numerze ISBN 978-83-900210-1-0,\n"
			"/znajdz -w  [wydawnictwo] <- np. \'/znajdz -w Nasza Ksi�garnia\' zwr�ci ksi��ki wydane przez wydawnictwo Nasza Ksi�garnia,\n"
			"/znajdz -r  [rodzaj]      <- np. \'/znajdz -r liryka\' zwr�ci dzie�a liryczne,\n"
			"/znajdz -g  [gatunek]     <- np. \'/znajdz -g epopeja\' zwr�ci wszystkie epopeje.\n"
			"/znajdz -s  [sygnatura]   <- np. \'/znajdz -s C.00559\' zwr�ci ksi��k� o sygnaturze C.00559.\n\n"
			"Oczywi�cie, nie ma potrzeby wprowadza� pe�nych danych (przyk�adowo, wystarczy wpisa� imi� podczas wyszukiwania wg. autora), jednak�e wtedy wyniki b�d�, rzecz jasna, du�o mniej precyzyjne.\n\n";
		
		// WYSZUKIWARKA KSI��EK
		else if (komenda == "/info 2") cout <<
			"Wpisz \'2\' lub \'/spis\', aby wy�wietli� wszystkie ksi��ki w bazie (mo�e to chwil� zaj��).\n"
			"Mo�esz tak�e wy�wietli� spis wszystkich warto�ci danego atrybutu. Poni�ej znajduje si� lista oraz sk�adnia s�u��cych do tego polece�:\n\n"
			"/spis -id <- zwr�ci spis numer�w ID ksi��ek,\n"
			"/spis -t  <- zwr�ci spis tytu��w ksi��ek,\n"
			"/spis -a  <- zwr�ci spis autor�w,\n"
			"/spis -rw <- zwr�ci spis rocznik�w ksi��ek,\n"
			"/spis -i  <- zwr�ci spis numer�w ISBN ksi��ek,\n"
			"/spis -w  <- zwr�ci spis wydawnictw\n"
			"/spis -r  <- zwr�ci spis rodzaj�w literackich\n"
			"/spis -g  <- zwr�ci spis gatunk�w literackich\n"
			"/spis -s  <- zwr�ci spis sygnatur ksi��ek w bibliotece\n\n"
			"Oczywi�cie, nie ma potrzeby wprowadza� pe�nych danych (przyk�adowo, wystarczy wpisa� imi� podczas wyszukiwania wg. autora), jednak�e wtedy wyniki b�d�, rzecz jasna, du�o mniej precyzyjne.\n\n";
		
		// DODAWANIE KSI��EK
		else if (komenda == "/info 3") cout <<
			"Wpisz \'3\' lub \'/dodaj\', a program sam ci� poprowadzi.\n"
			"Alternatywnie, mo�esz od razu doda� ksi��k� wpisuj�c \'/dodaj [id]|[tytul]|[autor]|[rok_wydania]|[isbn]|[wydawnictwo]|[rodzaj]|[gatunek][sygnatura]\', pami�taj�c o separatorze w postaci znaku |, np.:\n\n"
			"/dodaj 420|Ania z Zielonego Wzg�rza|Lucy Maud Montgomery|1908|978-83-900210-1-0|L. C. Page & Co.|epika|powie��|C.00559\n\n"
			"Pami�taj o zachowaniu kolejno�ci i ilo�ci danych! Niew�a�ciwa ilo�� separator�w poskutkuje b��dem!\n\n";
		
		// USUWANIE KSI��EK
		else if (komenda == "/info 4") cout <<
			"Wpisz \'4\' lub \'/usun\', a program sam ci� poprowadzi.\n"
			"Alternatywnie, mo�esz od razu usun�� ksi��k� wpisuj�c \'/usun [id]|[tytul]|[autor]|[rok_wydania]|[isbn]|[wydawnictwo]|[rodzaj]|[gatunek]\', pami�taj�c o separatorze w postaci znaku |, np.:\n\n"
			"/usun 420|Ania z Zielonego Wzg�rza|Lucy Maud Montgomery|1908|978-83-900210-1-0|L. C. Page & Co.|epika|powie��|C.00559\n\n"
			"Pami�taj o zachowaniu kolejno�ci i ilo�ci danych! Niew�a�ciwa ilo�� separator�w poskutkuje b��dem!\n"
			//"UWAGA!!! PUSTE DANE ZOSTAN� POTRAKTOWANE JAKO DOWOLNE! Przyk�ad: \'/usun |||||||komedia|\' usunie WSZYSTKIE komedie!\n"
			"Je�li �WIADOMIE chcesz wyczy�ci� ca�� baz�, u�yj komendy \'/usun *\'\n\n";
		
		// WYJ�CIE Z PROGRAMU
		else if (komenda == "/exit") break;
		
		/* Komendy funkcjonalne ----------------------------------------------------------------------------- Komendy funkcjonalne ----------------------------------------------------------------------------- Komendy funkcjonalne */
		// WYSZUKIWARKA KSI��EK
		else if (komenda == "1" || komenda.find("/znajdz") == 0) {
			if 		(komenda.find(" -id ") == 7) wip(); /* TUTAJ MA BY� SZUKANIE PO ID */
			else if (komenda.find(" -t " ) == 7) wip(); /* TUTAJ MA BY� SZUKANIE PO TYTU�ACH */
			else if (komenda.find(" -a " ) == 7) wip(); /* TUTAJ MA BY� SZUKANIE PO AUTORACH */
			else if (komenda.find(" -rw ") == 7) wip(); /* TUTAJ MA BY� SZUKANIE PO ROCZNIKACH */
			else if (komenda.find(" -i " ) == 7) wip(); /* TUTAJ MA BY� SZUKANIE PO ISBN */
			else if (komenda.find(" -w " ) == 7) wip(); /* TUTAJ MA BY� SZUKANIE PO WYDAWNICTWACH */
			else if (komenda.find(" -r " ) == 7) wip(); /* TUTAJ MA BY� SZUKANIE PO RODZAJACH */
			else if (komenda.find(" -g " ) == 7) wip(); /* TUTAJ MA BY� SZUKANIE PO GATUNKACH */
			else if (komenda.find(" -s " ) == 7) wip(); /* TUTAJ MA BY� SZUKANIE PO SYGNATURACH */
			
			else {
				cout << "Wpisz pe�ne has�o lub s�owa kluczowe pozycji, kt�rej szukasz\n\n";
				getline(cin, komenda);
				cout << "\nOto znalezione pozycje:\n\n";
				for (int poz = 0; poz < pozycja.size(); poz++) {
					for (int atr = 0; atr < pozycja[poz].size(); atr++) {
						if (pozycja[poz][atr].find(komenda) != string::npos) {
							cout << "-> " << pozycja[poz][0] << ": \"" << pozycja[poz][1] << "\" autorstwa: " << pozycja[poz][2] << ", wydana w " << pozycja[poz][3] << " przez " << pozycja[poz][5] << ".\n"
							<< "-> Jest to ksi��ka rodzaju " << pozycja[poz][6] << " i gatunku " << pozycja[poz][7] << ".\n"
							<< "-> Jej ISBN to: " << pozycja[poz][4] << ", a jej sygnatura to " << pozycja[poz][8] << ".\n\n";
							break;
						}
					}
				}
			}
		}
		
		// SPIS KSI��EK
		else if (komenda == "2" || komenda.find("/spis") == 0) {
			if 		(komenda.find(" -id") == 5) wip(); /* TUTAJ MA BY� SPIS ID */
			else if (komenda.find(" -t" ) == 5) wip(); /* TUTAJ MA BY� SPIS TYTU��W */
			else if (komenda.find(" -a" ) == 5) wip(); /* TUTAJ MA BY� SPIS AUTOR�W */
			else if (komenda.find(" -rw") == 5) wip(); /* TUTAJ MA BY� SPIS ROCZNIK�W */
			else if (komenda.find(" -i" ) == 5) wip(); /* TUTAJ MA BY� SPIS ISBN */
			else if (komenda.find(" -w" ) == 5) wip(); /* TUTAJ MA BY� SPIS WYDAWNICTW */
			else if (komenda.find(" -r" ) == 5) wip(); /* TUTAJ MA BY� SPIS RODZAJ�W */
			else if (komenda.find(" -g" ) == 5) wip(); /* TUTAJ MA BY� SPIS GATUNK�W */
			else if (komenda.find(" -s" ) == 5) wip(); /* TUTAJ MA BY� SPIS SYGNATUR */
			
			// ITERACJA PO TABLICY W CELU WYPISANIA WSZYSTKICH REKORD�W W CA�O�CI
			else {
				
				cout << // Sta�y nag��wek tabeli
					"\n||         I D         ||        Tytu�        ||        Autor        ||     Rok wydania     ||       I S B N       ||     Wydawnictwo     ||  Rodzaj  literacki  ||  Gatunek literacki  ||      Sygnatura      ||\n"
					"=================================================================================================================================================================================================================\n";
				for (int i = 0; i < pozycja.size(); i++) { // 1 wymiar (rekord)
					cout << "||"; // Lewa kraw�d� wiersza
					for (int j = 0; j < pozycja[i].size(); j++) { // 2 wymiar (kolumna)
						
						// Wy�wietlenie rekordu
						linia = br(pozycja[i][j], 19);	// Przeniesienie warto�ci kom�rki do nowego wiersza co 19 znak�w (aby nie wychodzi�a poza swoj� kolumn�)
						if(linia.size() > 1) {
							linia.push_back(to_string(j)); // Dodaj kom�rce indeks kolumny
							duza_komorka.push_back(linia); // Je�li kom�rka zosta�a rozbita na dodatkowe wiersze, dodaj j� do 'du�ych kom�rek' (patrz: linia 185 kodu)
						}
						
						kol_idx.clear();
						for(int index = 0; index < duza_komorka.size(); index++) {
							kol_idx.push_back(stoi(duza_komorka[index].back())); // Przechowuje indeksy kolumn 'du�ych kom�rek'
						}
						
						// Wstawienie kom�rki
						for(int padding_l = 0; padding_l < 20-linia[0].length(); padding_l+=2) cout << " "; // Lewy padding �rodkowania kom�rki
						cout << linia[0]; // Wstawienie warto�ci kom�rki
						for(int padding_r = 0; padding_r < 21-linia[0].length(); padding_r+=2) cout << " "; // Prawy padding �rodkowania kom�rki
						cout << "||"; // Prawa kraw�d� kom�rki
					
					}
					
					// Przeniesienie 'du�ych kom�rek' do kolejnych wierszy
					if(!duza_komorka.empty()) { // Oczywi�cie, je�li dosz�o do rozbicia
						max_komorka = max_element(duza_komorka); // Najd�u�sza kom�rka
						for(int w = 1; w < max_komorka.size()-1; w++) { // Wiersze (na ile wierszy rozbito nawi�ksz� kom�rk�, czyli ile ich musi by� wygenerowanych); -1 w warunku, bo nie chcemy wygenerowa� nr kolumny
							cout << "\n||";
							for(int k = 0; k < 9; k++) { // Kolumny
								for(int kom = 0; kom < duza_komorka.size(); kom++) { // Ile kom�rek zosta�o rozbitych
								
								/**/// Je�li w tej kolumnie w og�le jest du�a kom�rka...
								/**/if(find(kol_idx.begin(), kol_idx.end(), k) != kol_idx.end()) {
								/**/	if(k == kol_idx[kom]) { // ...I je�li nr kolumny pokrywa si� z indeksem kolumny 'du�ej kom�rki'...
								/**/		
								/**/// ...To wstaw kolejn� kom�rk� w odpowiednim wierszu
								/**/		if (w < duza_komorka[kom].size()-1) { // [!] Ale je�li du�a kom�rka nie jest najwi�ksz�
								/**/			for(int padding_l = 0; padding_l < 20-duza_komorka[kom][w].length(); padding_l+=2) cout << " "; // Lewy padding �rodkowania kom�rki
								/**/			cout << duza_komorka[kom][w]; // Wpisz kolejny wiersz kom�rki
								/**/			for(int padding_r = 0; padding_r < 21-duza_komorka[kom][w].length(); padding_r+=2) cout << " "; // Prawy padding �rodkowania kom�rki
								/**/			cout << "||"; // Prawa kraw�d� kom�rki
								/**/		}
								/**/		else cout << "                     ||";//[!] To wstaw puste wiersze tam gdzie najwi�ksza kom�rka jeszcze ma zawarto��!
								/**/	}
								/**/}
								/**/// A je�li nie...	
									else {
										cout << "                     ||"; // ...To wstaw pust� kom�rk�
										break; // Je�li nie ma w tej kolumnie da�ej kom�rki, to przejd� od razu do kolejnej
									}
								}
							}
						}
					}
					if (i+1 < pozycja.size()) cout << // Je�li wiersz nie jest ostatnim
						"\b\n"
						"-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n";
					duza_komorka.clear();
					kol_idx.clear();
				}
				cout << "\n\n";
			}
			
		}
		
		// DODAWANIE KSI��EK
		else if (komenda == "3" || komenda.find("/dodaj") == 0) {
			
			// Jednoliniowe
			if(komenda.find(" ") == 6) { // Je�li wyst�pi spacja po komendzie doawania, musi to oznacza� jednoliniowe dodanie ksi��ki
			
				kolumna = split(komenda, '|'); // Rozdziela �a�cuch wej�ciowy wg. separatora |
				if(kolumna.size() == 9 && komenda.back() != '|')	{ // Prymitywne zapewnienie, �e komenda sk�ada si� z w�a�ciwej ilo�ci separator�w (dodatkowy separator na ko�cu polecenia jest domy�lnie akceptowany)
					
					// DODANIE KSI��KI DO BAZY (STWORZENIE NOWEGO WIERSZA W TABLICY ZE WPISANYMI ATRYBUTAMI)
					pozycja.push_back( {kolumna[0].substr(7, kolumna[0].length()), kolumna[1], kolumna[2], kolumna[3], kolumna[4], kolumna[5], kolumna[6], kolumna[7], kolumna[8]} );
					cout << "\nKsi��ka dodana!\n\n";
				}
				
				else cout << "\nNiepoprawny zapis! Spr�buj jeszcze raz. Je�li potrzebujesz pomocy dot. tej komendy, wpisz \'/info 3\'\n\n";
								
			}
			// "Poprowadzone za r�k�" przez program
			else {
				
			/**/// Bardzo prymitywny spos�b zapewnienia integralno�ci danych
			/**/do {
			/**/	blad = false;
			/**/	cout << "Podaj id (musi by� unikatowe i dodatnie!): ";
			/**/	string s_id;
			/**/	cin >> s_id;
			/**/	char* k;
			/**/	id = strtol(s_id.c_str(), &k, 0);
			/**/	if ((id == LONG_MAX || id == LONG_MIN) && errno == ERANGE || k != s_id.c_str()+s_id.size() || id < 0) { // Dana musi mie�ci� si� w przedziale typu long oraz by� liczb� naturaln�
			/**/		blad = true;
			/**/		cout << "Niepoprawny typ! Upewnij si�, �e wpisujesz liczb� naturaln�!\n\n";
			/**/		cin.clear();
			/**/		cin.ignore();
			/**/	}
			/**/} while(blad);				
			/**/cin.ignore(); // Wyczyszczenie bufora cin, aby nie pomin�o nast�pnego getline (dotyczy ka�dego wyst�pienia tej linijki kodu)
				
				cout << "\nPodaj tytu�: ";
				while (getline(cin, tytul)) { // Wczytuj tak d�ugo, a� nie zostanie podana jaka� warto�� (zamiast samego Entera); dotyczy ka�dego ponownego wyst�pienia
					if(tytul.find('|') != string::npos) cout << "\nProsimy o nieu�ywanie znaku | w tej metodzie wprowadzania danych\n\n";
					if(tytul.size() != 0 && tytul.find('|') == string::npos) break;
				}
				
				cout << "\nPodaj autora: ";
				while (getline(cin, autor)) {
					if(autor.find('|') != string::npos) cout << "\nProsimy o nieu�ywanie znaku | w tej metodzie wprowadzania danych\n\n";
					if(autor.size() != 0 && autor.find('|') == string::npos) break;
				}
			/**/// Bardzo prymitywny spos�b zapewnienia integralno�ci danych
			/**/do {
			/**/	blad = false;
			/**/	cout << "\nPodaj rok wydania (je�li p.n.e. to zapisz jako liczba ujemna, np. -3015 = 3015p.n.e.): ";
			/**/	string s_rw;
			/**/	cin >> s_rw;
			/**/	char* l;
			/**/	s_rw = s_rw.substr(0, 6);
			/**/	long l_rw = strtol(s_rw.c_str(), &l, 10);
			/**/	if(l_rw < SHRT_MIN || l_rw > SHRT_MAX) { // Dana musi mie�ci� si� w przedziale typu short
			/**/		blad = true;
			/**/		cout << "Niepoprawny typ! Upewnij si�, �e wpisujesz liczb� naturaln�!\n\n";
			/**/		cin.clear();
			/**/		cin.ignore();
			/**/	}
			/**/	else rok_wydania = l_rw;
			/**/	if (((rok_wydania == LONG_MAX || rok_wydania == LONG_MIN) && errno == ERANGE || l != s_rw.c_str()+s_rw.size() || rok_wydania > obecny_rok) && blad == false) { // Dana musi by� liczb� ca�kowit� niewi�ksz� ni� obecny rok
			/**/		blad = true;
			/**/		rok_wydania <= obecny_rok ? cout << "Niepoprawny typ! Upewnij si�, �e wpisujesz liczb� naturaln�!\n\n" : cout << "A co ty, podr�nik w czasie? Wprowad� poprawny rok!\n\n";
			/**/		cin.clear();
			/**/		cin.ignore();
			/**/	}
			/**/} while(blad);
			/**/cin.ignore();
				
				cout << "\nPodaj ISBN: ";
				while (getline(cin, isbn)) {
					if(isbn.find('|') != string::npos) cout << "\nProsimy o nieu�ywanie znaku | w tej metodzie wprowadzania danych\n\n";
					if(isbn.size() != 0 && isbn.find('|') == string::npos) break;
				}
				
				cout << "\nPodaj wydawnictwo: ";
				while (getline(cin, wydawnictwo)) {
					if(wydawnictwo.find('|') != string::npos) cout << "\nProsimy o nieu�ywanie znaku | w tej metodzie wprowadzania danych\n\n";
					if(wydawnictwo.size() != 0 && wydawnictwo.find('|') == string::npos) break;
				}
				
				cout << "\nPodaj rodzaj literacki: ";
				while (getline(cin, rodzaj)) {
					if(rodzaj.find('|') != string::npos) cout << "\nProsimy o nieu�ywanie znaku | w tej metodzie wprowadzania danych\n\n";
					if(rodzaj.size() != 0 && rodzaj.find('|') == string::npos) break;
				}
				
				cout << "\nPodaj gatunek literacki: ";
				while (getline(cin, gatunek)) {
					if(gatunek.find('|') != string::npos) cout << "\nProsimy o nieu�ywanie znaku | w tej metodzie wprowadzania danych\n\n";
					if(gatunek.size() != 0 && gatunek.find('|') == string::npos) break;
				}
				
				cout << "\nPodaj sygnatur�: ";
				while (getline(cin, sygnatura)) {
					if(sygnatura.find('|') != string::npos) cout << "\nProsimy o nieu�ywanie znaku | w tej metodzie wprowadzania danych\n\n";
					if(sygnatura.size() != 0 && sygnatura.find('|') == string::npos) break;
				}
				
				// DODANIE KSI��KI DO BAZY (STWORZENIE NOWEGO WIERSZA W TABLICY ZE WPISANYMI ATRYBUTAMI)
				pozycja.push_back({to_string(id), tytul, autor, to_string(rok_wydania), isbn, wydawnictwo, rodzaj, gatunek, sygnatura});
				cout << "\nKsi��ka dodana!\n\n";
				
				// WYPISANIE BAZY DO PLIKU BINARNEGO
				wpis_do_bazy.str("");
				wpis_do_bazy << to_string(id) << "|" << tytul << "|" << autor << "|" << to_string(rok_wydania) << "|" << isbn << "|" << wydawnictwo << "|" << rodzaj << "|" << gatunek << "|" << sygnatura << "\n";
				wpis_do_bazy_s = wpis_do_bazy.str();
				
				plik.open("Baza biblioteczna.bin", ios::app);
				if(plik.is_open()) plik << wpis_do_bazy_s;
				if(plik.is_open()) plik.close();
				
			}
			
		}
		
		// USUWANIE KSI��EK
		else if (komenda == "4" || komenda.find("/usun") == 0) {
			
			// Jednoliniowe
			if(komenda.find(" ") == 5) {
				
				// Wyczyszczenie bazy
				if(komenda.find("*") == 6) {
					
					cout << "\nCzy na pewno chcesz wyczy�ci� CA�� baz� ksi��ek? Jest to nieodwracalny proces, wi�c zastan�w si� dobrze!\nWpisz \'TAK\' (koniecznie wielkimi literami), je�li potwierdzasz, lub cokolwiek innego, by powr�ci� do menu g��wnego.\n\n";
					getline(cin, komenda);
					if (komenda == "TAK") {
						
						plik.open("Baza biblioteczna.bin", ios::out | ios::trunc);
						remove("Baza biblioteczna.bin");
						rename("test", "Baza biblioteczna.bin");
						cout << "\n\nBaza wyczyszczona pomy�lnie! Aby zatwierdzi� zmiany, nale�y zamkn�� program\n\n";
						ileUsunieto = -1;
						
					}
					
				}
				
				else {
					kolumna = split(komenda, '|');
					if(kolumna.size() == 9 && komenda.back() != '|') {
						
						kolumna[0] = kolumna[0].substr(6, kolumna[0].length());
						for (int poz = 0; poz < pozycja.size(); poz++) {
							
							if (pozycja[poz] == kolumna) {
								
								ileUsunieto++;
								pozycja.erase(pozycja.begin()+poz);
								poz--; // Zapobiega przeskakiwaniu pozycji po usuni�ciu
								
							}
							
						}
						
					}
				
					else cout << "\nNiepoprawny zapis! Spr�buj jeszcze raz. Je�li potrzebujesz pomocy dot. tej komendy, wpisz \'/info 4\'\n\n";
					
				}
				
			}
			
			// "Poprowadzone za r�k�" przez program
			else {cout << "\nUsuwanie jest jeszcze w trakcie implementacji. Prosimy o stosowanie usuwania jednoliowego - ono ju� w pe�ni dzia�a :)\nJe�li nie wiesz, jak to zrobi�, wpisz \'/info 4\'\n\n";
			
				/*cout << "Podaj id: "; 
				cin >> id;
				
				cout << "Podaj tytu�: ";
				getline(cin, tytul);
				
				cout << "Podaj autora: ";
				getline(cin, autor);
				
				cout << "Podaj rok wydania: ";
				cin >> rok_wydania;
				
				cout << "Podaj ISBN: ";
				getline(cin, isbn);
				
				cout << "Podaj wydawnictwo: ";
				getline(cin, wydawnictwo);
				
				cout << "Podaj rodzaj literacki: ";
				getline(cin, rodzaj);
				
				cout << "Podaj gatunek literacki: ";
				getline(cin, gatunek);
				
				cout << "Podaj sygnatur�: ";
				getline(cin, sygnatura);*/
			}
			
			if(ileUsunieto != -1) {
				if(ileUsunieto == 1) ksiazkaOdmiana = "ksi��k�";
				if(ileUsunieto > 1 && ileUsunieto < 5) ksiazkaOdmiana = "ksi��ki";
				ileUsunieto != 0 ? cout << "Usuni�to " << ileUsunieto << " " << ksiazkaOdmiana << ".\n\n" : cout << "Nie znaleziono �adnej takiej ksi��ki. Nic nie zosta�o usuni�te.\n\n";
			}
			ileUsunieto = 0;
			
			// Aktualizacja bazy po usuni�ciu pozycji
			wpis_do_bazy.str("");
			wpis_do_bazy_s = "";
			for (int poz = 0; poz < pozycja.size(); poz++) {
				
				wpis_do_bazy << pozycja[poz][0] << "|" << pozycja[poz][1] << "|" << pozycja[poz][2] << "|" << pozycja[poz][3] << "|" << pozycja[poz][4]
				 << "|" << pozycja[poz][5]<< "|" << pozycja[poz][6] << "|" << pozycja[poz][7] << "|" << pozycja[poz][8] << "\n";
				 
			}
			wpis_do_bazy_s = wpis_do_bazy.str();
			plik.open("Baza biblioteczna.bin", ios::out);
			if(plik.is_open()) plik << wpis_do_bazy_s;
			if(plik.is_open()) plik.close();
		
		}
		
		// NIEPOPRWANA KOMENDA
		else cout << "Niepoprawna komenda! Wpisz /help je�li potrzebujesz pomocy.\n\n";
		
	}
	
	/* Wiadomo�� po�egnalna --------------------------------------------------------------------------------- Wiadomo�� po�egnalna --------------------------------------------------------------------------------- Wiadomo�� po�egnalna */
	cout << 
		"___  ____ ___  ____ ____ ____ ___  ____ _  _ _   _ \n"
		"  /  |__| |__] |__/ |__| [__    /  |__| |\\/|  \\_/\n"
		" /__ |  | |    |  \\ |  | ___]  /__ |  | |  |   |  \n"
		"                                                   \n"
		"      ___  ____ _  _ ____ _ _ _ _  _ _ ____        \n"
		"      |__] |  | |\\ | |  | | | | |\\ | | |___      \n"
		"      |    |__| | \\| |__| |_|_| | \\| | |___      \n"
		"                                                   \n"
		"                                                   \n"
		"             \\/  /  /\\    /\\  \\  \\/           \n"
		"            ||-\\                /-||              \n"
		"            \\__/ \\   \\____/   / \\__/           \n"
		"                                                   \n";
	system("pause");
	
	return 0;
}
