/************************************************************************************************************************
Hashtable_main.cpp

	Wersja: 1.0
	Data: 12.03.2019

*************************************************************************************************************************/
#include <iostream>
#include <string>
#include <cctype> // czy cyfra


//zamiana string na int
inline
int liczba_s(std::string znak)
{
	return atoi(znak.c_str());
}

//get wielkosc
inline
int size(std::string a)
{
	return a.length();
}

//struktura elementu
struct element
{
	int numer;
	std::string text;
	long index;
	int kolizja;
};
int main()
{
	element * tab = nullptr;
	std::string line = "";
	int rozmiar_tab = 0;

	while (!std::cin.eof())
	{
		getline(std::cin, line);

		if (line[0] == 's' && line[1] == 'i') //ustawienie wielkosci
		{
			std::string buf = "";
			for (int i = 5; i <= size(line); i++)
			{
				buf += line[i];
			}

			rozmiar_tab = liczba_s(buf);

				//tworzenie tablicy elementow
				tab = new element[rozmiar_tab];

				for (int i = 0; i < rozmiar_tab; i++)
				{
					tab[i].text = "empty";
					tab[i].numer = 0;
					tab[i].index = -1;
					tab[i].kolizja = 0;
				}
		}
		else if (line[0] == 'a') // dodanie elementu do tab
		{
		int buf = 0;
		std::string liczba = "";
		std::string text = "";


		for (int i = 0; i < size(line); i++)
		{
			if (isdigit(line[i]))
			{
				liczba += line[i];
			}
			else if (!isdigit(line[i]) && i > 3)
			{
				text += line[i];
			}
		}

		//tworzenie indexu
		buf = (liczba_s(liczba)) % rozmiar_tab;

		int licznik = 0;

		for (int i = 0; i < rozmiar_tab; i++)
		{
			if (tab[buf].text == "empty")
			{
				//konfiguracja i dodanie elementu do tablicy
				tab[buf].index = buf;
				tab[buf].kolizja = licznik;
				tab[buf].numer = liczba_s(liczba);
				tab[buf].text = text;
				break;
			}
			else
			{
				//jezeli chcemy dodac na ostatni element a on jest zajety to dodaj na pierwszy
				if (tab[buf].index == rozmiar_tab - 1)
				{
					buf = 0;
					licznik--;
				}
				else
				{
					buf++;
					licznik++;
				}
			}
		}
		}
		else if (line[0] == 'p') // drukowanie
		{
		for (int i = 0; i < rozmiar_tab; i++)
		{
			if (tab[i].text != "empty")
			{
				std::cout << tab[i].index << " " << tab[i].numer << " " << tab[i].text << std::endl;
			}
		}

		std::cout << std::endl;
		}
		else if (line[0] == 'd') // usuwanie elementu
		{
		std::string cyfra = "";

		for (int i = 0; i < size(line); i++)
		{
			if (isdigit(line[i]))
			{
				cyfra += line[i];
			}
		}

		int ser = 0;

		for (int i = 0; i < rozmiar_tab; i++)
		{
			if (liczba_s(cyfra) == tab[i].numer)
			{
				ser = tab[i].index;
			}
		}

		//usuwanie odpowiedniego elementu
			tab[ser].text = "empty";
			tab[ser].numer = 0;
			tab[ser].index = -1;
			tab[ser].kolizja = 0;

		//jezeli usuwany jest ostatni i pierwszy byl przenoszony z ostatniego to przenies pierwszy na ostatni element tablicy
			if (ser == rozmiar_tab - 1 && tab[0].kolizja < 0)
			{
				tab[ser] = tab[0];
				tab[ser].kolizja += 1;
				tab[ser].index = ser;

				tab[0].text = "empty";
				tab[0].numer = 0;
				tab[0].index = -1;
				tab[0].kolizja = 0;
			}

		//petla przesuwajaca elementy
		for (int i = ser; i < rozmiar_tab -1 ; i++)
		{
				//warunek sprawdzajacy czy element moze zostac przesuniety
				if(tab[i+1].kolizja != 0)
				{
					//warunek sprawdzajacy czy miejsce jest wolne
					if (tab[i].text == "empty")
					{
						tab[i] = tab[i + 1];
						tab[i].index -= 1;
						tab[i].kolizja -= 1;

						tab[i + 1].text = "empty";
						tab[i + 1].numer = 0;
						tab[i + 1].index = -1;
						tab[i + 1].kolizja = 0;
					}
				}
		}
		}

		else if (line[0] == 's') // koniec
		{
			//zwolnienie pamieci
			delete[] tab;
		}
		else
		{
		}
	}

	return 0;
}