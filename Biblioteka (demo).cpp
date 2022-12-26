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

/* Funkcja zwracaj¹ca najd³u¿szy wiersz w tablicy 2d ------------------------------------------ Funkcja zwracaj¹ca najd³u¿szy wiersz w tablicy 2d ----------------------------------------- Funkcja zwracaj¹ca najd³u¿szy wiersz w tablicy 2d */
vector<string> max_element(vector<vector<string>> tab) {
	vector<string> max = {};
	for(int i = 0; i < tab.size(); i++) {
		if(tab[i].size() > max.size()) max = tab[i];
	}
	return max;
}

/* Funkcja rozdzialj¹ca ³añcuchy znakowe na podstawie znaku ------------------------------- Funkcja rozdzialj¹ca ³añcuchy znakowe na podstawie znaku ------------------------------- Funkcja rozdzialj¹ca ³añcuchy znakowe na podstawie znaku */
vector<string> split(string wpis, char znak) {
    stringstream ss(wpis);
    string atrybut;
    vector<string> atrybuty;
    while (getline(ss, atrybut, znak)) {
       atrybuty.push_back(atrybut);
    }
    return atrybuty;
}

/* Funkcja rozdzielaj¹ca ³añcuchy znakowe co <dlugosc> znaków ---------------------------- Funkcja rozdzielaj¹ca ³añcuchy znakowe co <dlugosc> znaków ---------------------------- Funkcja rozdzielaj¹ca ³añcuchy znakowe co <dlugosc> znaków */
vector<string> br(string komorka, int dlugosc) {
	vector<string> linie_komorki;
	for (size_t a = 0; a < komorka.size(); a += dlugosc) {
    	linie_komorki.push_back(komorka.substr(a, dlugosc));		
	}
    return linie_komorki;
}

void wip() {cout << "\nOpcja dostêpna tylko w wersji Premium! Wp³aæ conajmniej $21,37 na konto programisty aby odblokowaæ konto OnlyFa-- znaczy, wersjê Premium.\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\tNo dobra, ¿artujê, po prostu jeszcze tego nie zaimplementowa³em. Proszê mnie nie pozywaæ. B³agam. -MN\n";}

/* G³ówna czêœæ programu ------------------------------------------------------------------------------------ G³ówna czêœæ programu ----------------------------------------------------------------------------------- G³ówna czêœæ programu */
int main() {
	
	/* Zwiêkszenie bufora konsoli, by poprawnie wyœwietla³o spis ksi¹¿ek -------------- Zwiêkszenie bufora konsoli, by poprawnie wyœwietla³o spis ksi¹¿ek ------------- Zwiêkszenie bufora konsoli, by poprawnie wyœwietla³o spis ksi¹¿ek */
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
	tm *const tp = localtime(&t);			/* Obecny rok; porównywany z rokiem wydania dodawanej ksi¹¿ki, aby uniemo¿liwiæ wprowadzenie roku, który jeszcze nie nadszed³ */
	short obecny_rok = tp->tm_year + 1900;	/*----------------------------------------------------------------------------------------------------------------------------*/
	
	bool blad; // Zmienna odpowiedzialna za ustawianie stanu poprawnoœci danych wejœciowych przy dodawaniu ksi¹¿ki
	
	vector<vector<string>> pozycja; // Stworzenie dwuwymiarowej tablicy, która bêdzie przechowywaæ ksi¹¿ki
	vector<string> kolumna; // Zmienna pomocnicza do rozdzielania jednoliniowych komend dodania i usuniêcia ksi¹¿ki
	vector<string> linia; // Zmienna pomocnicza do rozbijania wartoœci komórek w spisie na wiele linii
	vector<vector<string>> duza_komorka; // Tablica przechowuj¹ca wartoœci komórek, które nie mieszcz¹ siê w jednym wierszu, wraz z indeksami kolumn, dla których do tego dochodzi
	vector<string> max_komorka; // Tablica przechowuj¹ca cz³ony (a na koñcu indeks kolumny, do której nale¿y) najd³u¿szej 'du¿ej komórki'	
	vector<int> kol_idx; // Tablica przechowuj¹ca indeksy kolumn 'du¿ych komórek'
	
	fstream plik;
	int rozmiar; // Przechowuje rozmiar pliku BIN
	char wypis_z_bazy[1]; // Bufor znakowy przy odczytywaniu z pliku BIN
	vector<string> wypis_z_bazy_v; // Przechowuje rekordy odczytane z pliku BIN
	string wzb;
	stringstream wpis_do_bazy; // Przechowuje rekordy dodane podczas bie¿¹cej sesji
	string wpis_do_bazy_s; // Poœrednik miêdzy wpis_do_bazy a plikiem BIN
	
	int ileUsunieto = 0;
	string ksiazkaOdmiana = "ksi¹¿ek";
	
	/* Wiadomoœæ powitalna ----------------------------------------------------------------------------------- Wiadomoœæ powitalna ---------------------------------------------------------------------------------- Wiadomoœæ powitalna */
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

	cout << "Wybierz jedn¹ z poni¿szych funkcji wpisuj¹c jej (numer) lub zwi¹zan¹ z ni¹ s³own¹ komendê. Wpisz \'/help\', jeœli potrzebujesz pomocy. Wpisz \'/exit\' aby opuœciæ program.\n";
	cout << "(1) ZnajdŸ ksi¹¿kê\n(2) Spis ksi¹¿ek\n(3) Dodaj ksi¹¿kê\n(4) Usuñ ksi¹¿kê\n\n";
	
	/* Wczytanie rekordów, które s¹ ju¿ w bazie (pliku BIN) --------------------------------- Wczytanie rekordów, które s¹ ju¿ w bazie (pliku BIN) --------------------------------- Wczytanie rekordów, które s¹ ju¿ w bazie (pliku BIN) */
	plik.open("Baza biblioteczna.bin", ios::in | ios::binary);
	plik.seekg(0, ios::end); // WskaŸnik koñca pliku
	rozmiar = (int) plik.tellg();
	plik.seekg(0, ios::beg); // WskaŸnik pocz¹tku pliku
	while(plik.tellg() < rozmiar) {
		plik.read((char*) wypis_z_bazy, sizeof(wypis_z_bazy)); // Przechowuje zawartoœæ pliku w tablicy znaków wypis_z_bazy
		wzb.append(wypis_z_bazy); // Konwersja tablicy znaków do ³añcucha znakowego
	}
	wypis_z_bazy_v = split(wzb, '\n'); // Rozbicie zawartoœci pliku na wiersze (rekordy)
	for (int z = 0; z < wypis_z_bazy_v.size(); z++) {
		pozycja.push_back(split(wypis_z_bazy_v[z], '|')); // Rozbicie rekordów na komórki i wpisanie ich do tablicy ksi¹¿ek
	}
	if(plik.is_open()) plik.close();
	
	// Usuniêcie 'œmieci' (\r, \n) z wczytanych danych
	for (int poz = 0; poz < pozycja.size(); poz++) {
		for (int atr = 0; atr < pozycja[poz].size(); atr++) {
			pozycja[poz][atr].erase(remove(pozycja[poz][atr].begin(), pozycja[poz][atr].end(), '\r'), pozycja[poz][atr].end());
			pozycja[poz][atr].erase(remove(pozycja[poz][atr].begin(), pozycja[poz][atr].end(), '\n'), pozycja[poz][atr].end());
		}
	}
	
	/* Interakcja u¿ytkownika z programem ------------------------------------------------------------ Interakcja u¿ytkownika z programem ------------------------------------------------------------ Interakcja u¿ytkownika z programem */
	while(true) {
		
		getline(cin, komenda);
		
		/* Komendy pomocy -------------------------------------------------------------------------------------- Komendy pomocy -------------------------------------------------------------------------------------- Komendy pomocy */
		// HELP i INFO
		if (komenda == "/help") cout << 
			"Wywo³anie funkcji wygl¹da nastêpuj¹co:\n\n"
			"1      \t      \t      \t      \t      \t      \t      \t      <- wprowadzone przez u¿ytkownika\n"
			"Wpisz s³owo (s³owa) kluczowe, aby odnaleŸæ to, czego szukasz. <- wyprowadzone przez program\n\n";
		
		if (komenda == "/help" || komenda == "/info") cout <<
			"Jeœli chcesz dowiedzieæ siê wiêcej o danej funkcji programu, wpisz /info [numer], np.:\n\n"
			"/info 1 \t \t \t \t \t \t <- wprowadzone przez u¿ytkownika,\n"
			"Wpisz \'1\' lub \'/znajdz\', a program sam ciê poprowadzi... <- wyprowadzone przez program.\n\n";
		
		// SPIS KSI¥¯EK
		else if (komenda == "/info 1") cout <<
			"Wpisz \'1\' lub \'/znajdz\', a program sam ciê poprowadzi. Alternatywnie, mo¿esz od razu wyszukaæ ksi¹¿kê wpisuj¹c \'/znajdz [slowo (slowa) kluczowe]\', np.:\n\n"
			"/znajdz Pinokio   \t   \t   \t   <- wprowadzone przez u¿ytkownika\n"
			"Uda³o nam siê znaleŸæ nastêpuj¹ce pozycje: <- wyprowadzone przez program\n"
			"...   \t   \t   \t   \t   \t   <-\n"
			"...   \t   \t   \t   \t   \t   <-\n"
			"...   \t   \t   \t   \t   \t   <-\n\n"
			"Mo¿esz tak¿e wyszukaæ ksi¹¿kê wed³ug konkretnego atrybutu. Poni¿ej znajduje siê lista oraz sk³adnia s³u¿¹cych do tego poleceñ:\n\n"
			"/znajdz -id [id]          <- np. \'/znajdz -id 503\' zwróci ksi¹¿kê o ID 503,\n"
			"/znajdz -t  [tytul]       <- np. \'/znajdz -t Harry Potter\' zwróci ksi¹¿ki maj¹ce w tytule frazê \'Harry Potter\',\n"
			"/znajdz -a  [autor]       <- np. \'/znajdz -a Stephen King\' zwróci ksi¹¿ki autorstwa Stephena Kinga,\n"
			"/znajdz -rw [rok_wydania] <- np. \'/znajdz -rw 1789\' zwróci ksi¹¿ki wydane w roku 1789,\n"
			"/znajdz -i  [isbn]        <- np. \'/znajdz -i 978-83-900210-1-0\' zwróci ksi¹¿kê o numerze ISBN 978-83-900210-1-0,\n"
			"/znajdz -w  [wydawnictwo] <- np. \'/znajdz -w Nasza Ksiêgarnia\' zwróci ksi¹¿ki wydane przez wydawnictwo Nasza Ksiêgarnia,\n"
			"/znajdz -r  [rodzaj]      <- np. \'/znajdz -r liryka\' zwróci dzie³a liryczne,\n"
			"/znajdz -g  [gatunek]     <- np. \'/znajdz -g epopeja\' zwróci wszystkie epopeje.\n"
			"/znajdz -s  [sygnatura]   <- np. \'/znajdz -s C.00559\' zwróci ksi¹¿kê o sygnaturze C.00559.\n\n"
			"Oczywiœcie, nie ma potrzeby wprowadzaæ pe³nych danych (przyk³adowo, wystarczy wpisaæ imiê podczas wyszukiwania wg. autora), jednak¿e wtedy wyniki bêd¹, rzecz jasna, du¿o mniej precyzyjne.\n\n";
		
		// WYSZUKIWARKA KSI¥¯EK
		else if (komenda == "/info 2") cout <<
			"Wpisz \'2\' lub \'/spis\', aby wyœwietliæ wszystkie ksi¹¿ki w bazie (mo¿e to chwilê zaj¹æ).\n"
			"Mo¿esz tak¿e wyœwietliæ spis wszystkich wartoœci danego atrybutu. Poni¿ej znajduje siê lista oraz sk³adnia s³u¿¹cych do tego poleceñ:\n\n"
			"/spis -id <- zwróci spis numerów ID ksi¹¿ek,\n"
			"/spis -t  <- zwróci spis tytu³ów ksi¹¿ek,\n"
			"/spis -a  <- zwróci spis autorów,\n"
			"/spis -rw <- zwróci spis roczników ksi¹¿ek,\n"
			"/spis -i  <- zwróci spis numerów ISBN ksi¹¿ek,\n"
			"/spis -w  <- zwróci spis wydawnictw\n"
			"/spis -r  <- zwróci spis rodzajów literackich\n"
			"/spis -g  <- zwróci spis gatunków literackich\n"
			"/spis -s  <- zwróci spis sygnatur ksi¹¿ek w bibliotece\n\n"
			"Oczywiœcie, nie ma potrzeby wprowadzaæ pe³nych danych (przyk³adowo, wystarczy wpisaæ imiê podczas wyszukiwania wg. autora), jednak¿e wtedy wyniki bêd¹, rzecz jasna, du¿o mniej precyzyjne.\n\n";
		
		// DODAWANIE KSI¥¯EK
		else if (komenda == "/info 3") cout <<
			"Wpisz \'3\' lub \'/dodaj\', a program sam ciê poprowadzi.\n"
			"Alternatywnie, mo¿esz od razu dodaæ ksi¹¿kê wpisuj¹c \'/dodaj [id]|[tytul]|[autor]|[rok_wydania]|[isbn]|[wydawnictwo]|[rodzaj]|[gatunek][sygnatura]\', pamiêtaj¹c o separatorze w postaci znaku |, np.:\n\n"
			"/dodaj 420|Ania z Zielonego Wzgórza|Lucy Maud Montgomery|1908|978-83-900210-1-0|L. C. Page & Co.|epika|powieœæ|C.00559\n\n"
			"Pamiêtaj o zachowaniu kolejnoœci i iloœci danych! Niew³aœciwa iloœæ separatorów poskutkuje b³êdem!\n\n";
		
		// USUWANIE KSI¥¯EK
		else if (komenda == "/info 4") cout <<
			"Wpisz \'4\' lub \'/usun\', a program sam ciê poprowadzi.\n"
			"Alternatywnie, mo¿esz od razu usun¹æ ksi¹¿kê wpisuj¹c \'/usun [id]|[tytul]|[autor]|[rok_wydania]|[isbn]|[wydawnictwo]|[rodzaj]|[gatunek]\', pamiêtaj¹c o separatorze w postaci znaku |, np.:\n\n"
			"/usun 420|Ania z Zielonego Wzgórza|Lucy Maud Montgomery|1908|978-83-900210-1-0|L. C. Page & Co.|epika|powieœæ|C.00559\n\n"
			"Pamiêtaj o zachowaniu kolejnoœci i iloœci danych! Niew³aœciwa iloœæ separatorów poskutkuje b³êdem!\n"
			//"UWAGA!!! PUSTE DANE ZOSTAN¥ POTRAKTOWANE JAKO DOWOLNE! Przyk³ad: \'/usun |||||||komedia|\' usunie WSZYSTKIE komedie!\n"
			"Jeœli ŒWIADOMIE chcesz wyczyœciæ ca³¹ bazê, u¿yj komendy \'/usun *\'\n\n";
		
		// WYJŒCIE Z PROGRAMU
		else if (komenda == "/exit") break;
		
		/* Komendy funkcjonalne ----------------------------------------------------------------------------- Komendy funkcjonalne ----------------------------------------------------------------------------- Komendy funkcjonalne */
		// WYSZUKIWARKA KSI¥¯EK
		else if (komenda == "1" || komenda.find("/znajdz") == 0) {
			if 		(komenda.find(" -id ") == 7) wip(); /* TUTAJ MA BYÆ SZUKANIE PO ID */
			else if (komenda.find(" -t " ) == 7) wip(); /* TUTAJ MA BYÆ SZUKANIE PO TYTU£ACH */
			else if (komenda.find(" -a " ) == 7) wip(); /* TUTAJ MA BYÆ SZUKANIE PO AUTORACH */
			else if (komenda.find(" -rw ") == 7) wip(); /* TUTAJ MA BYÆ SZUKANIE PO ROCZNIKACH */
			else if (komenda.find(" -i " ) == 7) wip(); /* TUTAJ MA BYÆ SZUKANIE PO ISBN */
			else if (komenda.find(" -w " ) == 7) wip(); /* TUTAJ MA BYÆ SZUKANIE PO WYDAWNICTWACH */
			else if (komenda.find(" -r " ) == 7) wip(); /* TUTAJ MA BYÆ SZUKANIE PO RODZAJACH */
			else if (komenda.find(" -g " ) == 7) wip(); /* TUTAJ MA BYÆ SZUKANIE PO GATUNKACH */
			else if (komenda.find(" -s " ) == 7) wip(); /* TUTAJ MA BYÆ SZUKANIE PO SYGNATURACH */
			
			else {
				cout << "Wpisz pe³ne has³o lub s³owa kluczowe pozycji, której szukasz\n\n";
				getline(cin, komenda);
				cout << "\nOto znalezione pozycje:\n\n";
				for (int poz = 0; poz < pozycja.size(); poz++) {
					for (int atr = 0; atr < pozycja[poz].size(); atr++) {
						if (pozycja[poz][atr].find(komenda) != string::npos) {
							cout << "-> " << pozycja[poz][0] << ": \"" << pozycja[poz][1] << "\" autorstwa: " << pozycja[poz][2] << ", wydana w " << pozycja[poz][3] << " przez " << pozycja[poz][5] << ".\n"
							<< "-> Jest to ksi¹¿ka rodzaju " << pozycja[poz][6] << " i gatunku " << pozycja[poz][7] << ".\n"
							<< "-> Jej ISBN to: " << pozycja[poz][4] << ", a jej sygnatura to " << pozycja[poz][8] << ".\n\n";
							break;
						}
					}
				}
			}
		}
		
		// SPIS KSI¥¯EK
		else if (komenda == "2" || komenda.find("/spis") == 0) {
			if 		(komenda.find(" -id") == 5) wip(); /* TUTAJ MA BYÆ SPIS ID */
			else if (komenda.find(" -t" ) == 5) wip(); /* TUTAJ MA BYÆ SPIS TYTU£ÓW */
			else if (komenda.find(" -a" ) == 5) wip(); /* TUTAJ MA BYÆ SPIS AUTORÓW */
			else if (komenda.find(" -rw") == 5) wip(); /* TUTAJ MA BYÆ SPIS ROCZNIKÓW */
			else if (komenda.find(" -i" ) == 5) wip(); /* TUTAJ MA BYÆ SPIS ISBN */
			else if (komenda.find(" -w" ) == 5) wip(); /* TUTAJ MA BYÆ SPIS WYDAWNICTW */
			else if (komenda.find(" -r" ) == 5) wip(); /* TUTAJ MA BYÆ SPIS RODZAJÓW */
			else if (komenda.find(" -g" ) == 5) wip(); /* TUTAJ MA BYÆ SPIS GATUNKÓW */
			else if (komenda.find(" -s" ) == 5) wip(); /* TUTAJ MA BYÆ SPIS SYGNATUR */
			
			// ITERACJA PO TABLICY W CELU WYPISANIA WSZYSTKICH REKORDÓW W CA£OŒCI
			else {
				
				cout << // Sta³y nag³ówek tabeli
					"\n||         I D         ||        Tytu³        ||        Autor        ||     Rok wydania     ||       I S B N       ||     Wydawnictwo     ||  Rodzaj  literacki  ||  Gatunek literacki  ||      Sygnatura      ||\n"
					"=================================================================================================================================================================================================================\n";
				for (int i = 0; i < pozycja.size(); i++) { // 1 wymiar (rekord)
					cout << "||"; // Lewa krawêdŸ wiersza
					for (int j = 0; j < pozycja[i].size(); j++) { // 2 wymiar (kolumna)
						
						// Wyœwietlenie rekordu
						linia = br(pozycja[i][j], 19);	// Przeniesienie wartoœci komórki do nowego wiersza co 19 znaków (aby nie wychodzi³a poza swoj¹ kolumnê)
						if(linia.size() > 1) {
							linia.push_back(to_string(j)); // Dodaj komórce indeks kolumny
							duza_komorka.push_back(linia); // Jeœli komórka zosta³a rozbita na dodatkowe wiersze, dodaj j¹ do 'du¿ych komórek' (patrz: linia 185 kodu)
						}
						
						kol_idx.clear();
						for(int index = 0; index < duza_komorka.size(); index++) {
							kol_idx.push_back(stoi(duza_komorka[index].back())); // Przechowuje indeksy kolumn 'du¿ych komórek'
						}
						
						// Wstawienie komórki
						for(int padding_l = 0; padding_l < 20-linia[0].length(); padding_l+=2) cout << " "; // Lewy padding œrodkowania komórki
						cout << linia[0]; // Wstawienie wartoœci komórki
						for(int padding_r = 0; padding_r < 21-linia[0].length(); padding_r+=2) cout << " "; // Prawy padding œrodkowania komórki
						cout << "||"; // Prawa krawêdŸ komórki
					
					}
					
					// Przeniesienie 'du¿ych komórek' do kolejnych wierszy
					if(!duza_komorka.empty()) { // Oczywiœcie, jeœli dosz³o do rozbicia
						max_komorka = max_element(duza_komorka); // Najd³u¿sza komórka
						for(int w = 1; w < max_komorka.size()-1; w++) { // Wiersze (na ile wierszy rozbito nawiêksz¹ komórkê, czyli ile ich musi byæ wygenerowanych); -1 w warunku, bo nie chcemy wygenerowaæ nr kolumny
							cout << "\n||";
							for(int k = 0; k < 9; k++) { // Kolumny
								for(int kom = 0; kom < duza_komorka.size(); kom++) { // Ile komórek zosta³o rozbitych
								
								/**/// Jeœli w tej kolumnie w ogóle jest du¿a komórka...
								/**/if(find(kol_idx.begin(), kol_idx.end(), k) != kol_idx.end()) {
								/**/	if(k == kol_idx[kom]) { // ...I jeœli nr kolumny pokrywa siê z indeksem kolumny 'du¿ej komórki'...
								/**/		
								/**/// ...To wstaw kolejn¹ komórkê w odpowiednim wierszu
								/**/		if (w < duza_komorka[kom].size()-1) { // [!] Ale jeœli du¿a komórka nie jest najwiêksz¹
								/**/			for(int padding_l = 0; padding_l < 20-duza_komorka[kom][w].length(); padding_l+=2) cout << " "; // Lewy padding œrodkowania komórki
								/**/			cout << duza_komorka[kom][w]; // Wpisz kolejny wiersz komórki
								/**/			for(int padding_r = 0; padding_r < 21-duza_komorka[kom][w].length(); padding_r+=2) cout << " "; // Prawy padding œrodkowania komórki
								/**/			cout << "||"; // Prawa krawêdŸ komórki
								/**/		}
								/**/		else cout << "                     ||";//[!] To wstaw puste wiersze tam gdzie najwiêksza komórka jeszcze ma zawartoœæ!
								/**/	}
								/**/}
								/**/// A jeœli nie...	
									else {
										cout << "                     ||"; // ...To wstaw pust¹ komórkê
										break; // Jeœli nie ma w tej kolumnie da¿ej komórki, to przejdŸ od razu do kolejnej
									}
								}
							}
						}
					}
					if (i+1 < pozycja.size()) cout << // Jeœli wiersz nie jest ostatnim
						"\b\n"
						"-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n";
					duza_komorka.clear();
					kol_idx.clear();
				}
				cout << "\n\n";
			}
			
		}
		
		// DODAWANIE KSI¥¯EK
		else if (komenda == "3" || komenda.find("/dodaj") == 0) {
			
			// Jednoliniowe
			if(komenda.find(" ") == 6) { // Jeœli wyst¹pi spacja po komendzie doawania, musi to oznaczaæ jednoliniowe dodanie ksi¹¿ki
			
				kolumna = split(komenda, '|'); // Rozdziela ³añcuch wejœciowy wg. separatora |
				if(kolumna.size() == 9 && komenda.back() != '|')	{ // Prymitywne zapewnienie, ¿e komenda sk³ada siê z w³aœciwej iloœci separatorów (dodatkowy separator na koñcu polecenia jest domyœlnie akceptowany)
					
					// DODANIE KSI¥¯KI DO BAZY (STWORZENIE NOWEGO WIERSZA W TABLICY ZE WPISANYMI ATRYBUTAMI)
					pozycja.push_back( {kolumna[0].substr(7, kolumna[0].length()), kolumna[1], kolumna[2], kolumna[3], kolumna[4], kolumna[5], kolumna[6], kolumna[7], kolumna[8]} );
					cout << "\nKsi¹¿ka dodana!\n\n";
				}
				
				else cout << "\nNiepoprawny zapis! Spróbuj jeszcze raz. Jeœli potrzebujesz pomocy dot. tej komendy, wpisz \'/info 3\'\n\n";
								
			}
			// "Poprowadzone za rêkê" przez program
			else {
				
			/**/// Bardzo prymitywny sposób zapewnienia integralnoœci danych
			/**/do {
			/**/	blad = false;
			/**/	cout << "Podaj id (musi byæ unikatowe i dodatnie!): ";
			/**/	string s_id;
			/**/	cin >> s_id;
			/**/	char* k;
			/**/	id = strtol(s_id.c_str(), &k, 0);
			/**/	if ((id == LONG_MAX || id == LONG_MIN) && errno == ERANGE || k != s_id.c_str()+s_id.size() || id < 0) { // Dana musi mieœciæ siê w przedziale typu long oraz byæ liczb¹ naturaln¹
			/**/		blad = true;
			/**/		cout << "Niepoprawny typ! Upewnij siê, ¿e wpisujesz liczbê naturaln¹!\n\n";
			/**/		cin.clear();
			/**/		cin.ignore();
			/**/	}
			/**/} while(blad);				
			/**/cin.ignore(); // Wyczyszczenie bufora cin, aby nie pominê³o nastêpnego getline (dotyczy ka¿dego wyst¹pienia tej linijki kodu)
				
				cout << "\nPodaj tytu³: ";
				while (getline(cin, tytul)) { // Wczytuj tak d³ugo, a¿ nie zostanie podana jakaœ wartoœæ (zamiast samego Entera); dotyczy ka¿dego ponownego wyst¹pienia
					if(tytul.find('|') != string::npos) cout << "\nProsimy o nieu¿ywanie znaku | w tej metodzie wprowadzania danych\n\n";
					if(tytul.size() != 0 && tytul.find('|') == string::npos) break;
				}
				
				cout << "\nPodaj autora: ";
				while (getline(cin, autor)) {
					if(autor.find('|') != string::npos) cout << "\nProsimy o nieu¿ywanie znaku | w tej metodzie wprowadzania danych\n\n";
					if(autor.size() != 0 && autor.find('|') == string::npos) break;
				}
			/**/// Bardzo prymitywny sposób zapewnienia integralnoœci danych
			/**/do {
			/**/	blad = false;
			/**/	cout << "\nPodaj rok wydania (jeœli p.n.e. to zapisz jako liczba ujemna, np. -3015 = 3015p.n.e.): ";
			/**/	string s_rw;
			/**/	cin >> s_rw;
			/**/	char* l;
			/**/	s_rw = s_rw.substr(0, 6);
			/**/	long l_rw = strtol(s_rw.c_str(), &l, 10);
			/**/	if(l_rw < SHRT_MIN || l_rw > SHRT_MAX) { // Dana musi mieœciæ siê w przedziale typu short
			/**/		blad = true;
			/**/		cout << "Niepoprawny typ! Upewnij siê, ¿e wpisujesz liczbê naturaln¹!\n\n";
			/**/		cin.clear();
			/**/		cin.ignore();
			/**/	}
			/**/	else rok_wydania = l_rw;
			/**/	if (((rok_wydania == LONG_MAX || rok_wydania == LONG_MIN) && errno == ERANGE || l != s_rw.c_str()+s_rw.size() || rok_wydania > obecny_rok) && blad == false) { // Dana musi byæ liczb¹ ca³kowit¹ niewiêksz¹ ni¿ obecny rok
			/**/		blad = true;
			/**/		rok_wydania <= obecny_rok ? cout << "Niepoprawny typ! Upewnij siê, ¿e wpisujesz liczbê naturaln¹!\n\n" : cout << "A co ty, podró¿nik w czasie? WprowadŸ poprawny rok!\n\n";
			/**/		cin.clear();
			/**/		cin.ignore();
			/**/	}
			/**/} while(blad);
			/**/cin.ignore();
				
				cout << "\nPodaj ISBN: ";
				while (getline(cin, isbn)) {
					if(isbn.find('|') != string::npos) cout << "\nProsimy o nieu¿ywanie znaku | w tej metodzie wprowadzania danych\n\n";
					if(isbn.size() != 0 && isbn.find('|') == string::npos) break;
				}
				
				cout << "\nPodaj wydawnictwo: ";
				while (getline(cin, wydawnictwo)) {
					if(wydawnictwo.find('|') != string::npos) cout << "\nProsimy o nieu¿ywanie znaku | w tej metodzie wprowadzania danych\n\n";
					if(wydawnictwo.size() != 0 && wydawnictwo.find('|') == string::npos) break;
				}
				
				cout << "\nPodaj rodzaj literacki: ";
				while (getline(cin, rodzaj)) {
					if(rodzaj.find('|') != string::npos) cout << "\nProsimy o nieu¿ywanie znaku | w tej metodzie wprowadzania danych\n\n";
					if(rodzaj.size() != 0 && rodzaj.find('|') == string::npos) break;
				}
				
				cout << "\nPodaj gatunek literacki: ";
				while (getline(cin, gatunek)) {
					if(gatunek.find('|') != string::npos) cout << "\nProsimy o nieu¿ywanie znaku | w tej metodzie wprowadzania danych\n\n";
					if(gatunek.size() != 0 && gatunek.find('|') == string::npos) break;
				}
				
				cout << "\nPodaj sygnaturê: ";
				while (getline(cin, sygnatura)) {
					if(sygnatura.find('|') != string::npos) cout << "\nProsimy o nieu¿ywanie znaku | w tej metodzie wprowadzania danych\n\n";
					if(sygnatura.size() != 0 && sygnatura.find('|') == string::npos) break;
				}
				
				// DODANIE KSI¥¯KI DO BAZY (STWORZENIE NOWEGO WIERSZA W TABLICY ZE WPISANYMI ATRYBUTAMI)
				pozycja.push_back({to_string(id), tytul, autor, to_string(rok_wydania), isbn, wydawnictwo, rodzaj, gatunek, sygnatura});
				cout << "\nKsi¹¿ka dodana!\n\n";
				
				// WYPISANIE BAZY DO PLIKU BINARNEGO
				wpis_do_bazy.str("");
				wpis_do_bazy << to_string(id) << "|" << tytul << "|" << autor << "|" << to_string(rok_wydania) << "|" << isbn << "|" << wydawnictwo << "|" << rodzaj << "|" << gatunek << "|" << sygnatura << "\n";
				wpis_do_bazy_s = wpis_do_bazy.str();
				
				plik.open("Baza biblioteczna.bin", ios::app);
				if(plik.is_open()) plik << wpis_do_bazy_s;
				if(plik.is_open()) plik.close();
				
			}
			
		}
		
		// USUWANIE KSI¥¯EK
		else if (komenda == "4" || komenda.find("/usun") == 0) {
			
			// Jednoliniowe
			if(komenda.find(" ") == 5) {
				
				// Wyczyszczenie bazy
				if(komenda.find("*") == 6) {
					
					cout << "\nCzy na pewno chcesz wyczyœciæ CA£¥ bazê ksi¹¿ek? Jest to nieodwracalny proces, wiêc zastanów siê dobrze!\nWpisz \'TAK\' (koniecznie wielkimi literami), jeœli potwierdzasz, lub cokolwiek innego, by powróciæ do menu g³ównego.\n\n";
					getline(cin, komenda);
					if (komenda == "TAK") {
						
						plik.open("Baza biblioteczna.bin", ios::out | ios::trunc);
						remove("Baza biblioteczna.bin");
						rename("test", "Baza biblioteczna.bin");
						cout << "\n\nBaza wyczyszczona pomyœlnie! Aby zatwierdziæ zmiany, nale¿y zamkn¹æ program\n\n";
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
								poz--; // Zapobiega przeskakiwaniu pozycji po usuniêciu
								
							}
							
						}
						
					}
				
					else cout << "\nNiepoprawny zapis! Spróbuj jeszcze raz. Jeœli potrzebujesz pomocy dot. tej komendy, wpisz \'/info 4\'\n\n";
					
				}
				
			}
			
			// "Poprowadzone za rêkê" przez program
			else {cout << "\nUsuwanie jest jeszcze w trakcie implementacji. Prosimy o stosowanie usuwania jednoliowego - ono ju¿ w pe³ni dzia³a :)\nJeœli nie wiesz, jak to zrobiæ, wpisz \'/info 4\'\n\n";
			
				/*cout << "Podaj id: "; 
				cin >> id;
				
				cout << "Podaj tytu³: ";
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
				
				cout << "Podaj sygnaturê: ";
				getline(cin, sygnatura);*/
			}
			
			if(ileUsunieto != -1) {
				if(ileUsunieto == 1) ksiazkaOdmiana = "ksi¹¿kê";
				if(ileUsunieto > 1 && ileUsunieto < 5) ksiazkaOdmiana = "ksi¹¿ki";
				ileUsunieto != 0 ? cout << "Usuniêto " << ileUsunieto << " " << ksiazkaOdmiana << ".\n\n" : cout << "Nie znaleziono ¿adnej takiej ksi¹¿ki. Nic nie zosta³o usuniête.\n\n";
			}
			ileUsunieto = 0;
			
			// Aktualizacja bazy po usuniêciu pozycji
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
		else cout << "Niepoprawna komenda! Wpisz /help jeœli potrzebujesz pomocy.\n\n";
		
	}
	
	/* Wiadomoœæ po¿egnalna --------------------------------------------------------------------------------- Wiadomoœæ po¿egnalna --------------------------------------------------------------------------------- Wiadomoœæ po¿egnalna */
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
