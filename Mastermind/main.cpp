#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <stack>
#include <ctime>
#include <locale.h>
#include <iterator>
#include <Windows.h>

using namespace std;


class WordDB {
public:
	WordDB(string fileName) {
		string temp;
		wordFileName = fileName;
		myfile.open(wordFileName);
		if (myfile.is_open()) {
			while (getline(myfile, temp)) {
				words.push_back(temp);
			}
		}
		else {
			cout << "Kelime dosyasi bulunamadi ya da acilamadi." << endl;
		}
		tempWords = words;
	}
	~WordDB() {
		myfile.close();
	}
	int getWordsSize() {
		return words.size();
	}
	int getWordsMatches(string s1, string s2, string kvsn, int number = 100) {
		int numberOfMatches = 0;
		string temp = "";


		if (kvsn == "1") {
			for (int i = 0; i < s1.size(); i++) {
				for (int j = 0; j < s2.size(); j++) {

					if (s1[i] == s2[j]) {
						int eslesme = 0;
						for (int k = 0; k < temp.size(); k++) {
							if (s1[i] == temp[k]) {
								eslesme++;
								break;
							}
						}
						if (eslesme == 0) {
							numberOfMatches++;
							temp.push_back(s1[i]);
							if (numberOfMatches > number) {
								return numberOfMatches;
							}
						}

					}
				}
			}
		}
		else if (kvsn == "0") {
			for (int i = 0; i < s1.size(); i++) {
				for (int j = 0; j < s2.size(); j++) {
					if (s1[i] == s2[j]) {
						numberOfMatches++;
						if (numberOfMatches > number) {
							return numberOfMatches;
						}
					}
				}
			}
		}
		else {

		}

		return numberOfMatches;
	}

	list<string>* getWordsDB() {
		return &words;
	}
	void addWordsTheDict(string name) {
		ofstream newFile(wordFileName);
		tempWords.push_back(name);
		list<string>::iterator it = tempWords.begin();
		while (it != tempWords.end()) {
			newFile << *it << endl;
			it++;
		}
	}

private:
	string wordFileName;
	fstream myfile;
	list<string> words;
	list<string> tempWords;
};
class Game {
public:
	Game(WordDB* wordDB) {
		this->wordDB = wordDB;
		words = wordDB->getWordsDB();
		step = 0;
		number = -1;
	}
	void gameStart() {
		string kelime;
		string kvsn;
		cout << "Kartezyen (0) Normal (1) : ";
		cin >> kvsn;
		while (step < 100) {
			step++;
			cout << endl;
			string mStep = "<---------------Adim-" + to_string(step) + "--------------->";
			cout << mStep << endl;
			string mStr1 = "Sozlukteki kelime sayisi : " + to_string(wordDB->getWordsSize());
			cout << mStr1 << endl;
			if (wordDB->getWordsSize() == 0) {
				cout << "Sözlükte kelime kalmadi." << endl;
				cout << "<------------------------------------>" << endl;
				cout << "Sözlüge yeni kelimeyi ekleyin ya da (-) yazarak çikin :  ";
				cin >> kelime;
				if (kelime != "-") {
					wordDB->addWordsTheDict(kelime);
				}
				system("PAUSE");
				break;

			}
			selectedWords.push(chooseRandomWord());

			cout << "Tahminim '" << selectedWords.top() << "'" << endl;
			cout << "Eslesme Sayisi : ";
			cin >> number;
			if (number == -1) {
				cout << "Tuttugun kelime >> " << selectedWords.top() << endl;
				system("PAUSE");
				break;
			}
			removeTheUnWanted(kvsn);
			cout << "<------------------------------->" << endl;
		}
	}
	void secondGameStart() {

		selectedWords.push(chooseRandomWord());
		string kvsn;
		cout << "Kartezyen (0) Normal (1) : ";
		cin >> kvsn;
		while (step < 100) {
			step++;
			cout << endl;
			cout << "<------------Adim-" << step << "------------>" << endl;
			cout << "Bana bir kelime söyle : ";
			cin >> myWord;
			int matches = wordDB->getWordsMatches(myWord, selectedWords.top(), kvsn);
			if (myWord == selectedWords.top()) {
				cout << "Kelimeyi buldunuz tebrikler." << endl;
				cout << "<------------------------------->" << endl;
				system("PAUSE");
				break;
			}

			cout << "Eslesme : " << matches << endl;

			cout << "<------------------------------->" << endl;

		}
	}
	void thirdGameStart() {

		string kvsn;
		cout << "Kartezyen (0) Normal (1) : ";
		cin >> kvsn;
		string choosedStr;
		cout << "Tuttugunuz kelimeyi giriniz : ";
		cin >> choosedStr;
		while (step < 100) {
			step++;
			cout << endl;
			cout << "<------------Adim-" << step << "------------>" << endl << endl;
			cout << "Sozlukteki kelime sayisi : " << wordDB->getWordsSize() << endl;
			selectedWords.push(chooseRandomWord());
			if (selectedWords.top() == "") {
				cout << "Sözlükte kelime kalmadi." << endl;
				cout << "<------------------------------->" << endl;
				cout << endl;
				wordDB->addWordsTheDict(choosedStr);
				system("PAUSE");
				break;
			}
			cout << "Tahminim '" << selectedWords.top() << "'" << endl;
			if (choosedStr == selectedWords.top()) {
				cout << "Kelime bulundu." << endl;
				cout << "<------------------------------->" << endl;
				cout << endl;

				system("PAUSE");
				break;
			}
			number = wordDB->getWordsMatches(choosedStr, selectedWords.top(), kvsn);
			cout << "Kesisim = " << number << endl;
			removeTheUnWanted(kvsn);
			cout << "<------------------------------>" << endl;
		}
	}
	string chooseRandomWord() {
		int wordsSize = wordDB->getWordsSize();
		int randomNumber = 0;
		if (wordsSize != 0) {
			randomNumber = rand() % wordsSize;
			list<string>::iterator it = words->begin();
			advance(it, randomNumber);
			string randomselectedWord = *it;
			words->erase(it);
			return randomselectedWord;
		}
		else {
			return "";
		}


	}
	void removeTheUnWanted(string kvsn) {

		string w = selectedWords.top();
		list<string>::iterator it = words->begin();
		while (it != words->end()) {
			if (wordDB->getWordsMatches(*it, w, kvsn, number) != number)
				it = words->erase(it); // remove the unwanted
			else {

				it++;
			}
		}
	}
private:
	int step;
	int number; // kelimelerin eslesme sayisi
	string myWord;
	stack<string> selectedWords;
	list<string>* words;
	WordDB* wordDB;

};


int main() {

	setlocale(LC_ALL, "");
	srand(time(0));
	SetConsoleOutputCP(28599);
	SetConsoleCP(28599);

	bool gameON = true;
	while (gameON) {
		WordDB wordDB("sozluk.txt");
		Game game(&wordDB);
		int gameVer;
		system("cls");
		cout << endl << "<-----------------MENU---------------->" << endl;
		cout << "| [1] - Bilgisayar tahmin etsin       |" << endl;
		cout << "| [2] - Kullanýcý tahmin etsin        |" << endl;
		cout << "| [3] - Bilgisayar tahmin etsin(oto)  |" << endl;
		cout << "<------------------------------------->" << endl;
		cout << ">>> ";
		cin >> gameVer;
		system("cls");

		if (gameVer == 1) {
			cout << endl << "Sözlükten bir kelime seçiniz ve aklinizda tutunuz." << endl;
			system("PAUSE");
			game.gameStart();
		}
		else if (gameVer == 2) {
			cout << endl << "Bilgisayarin tuttugu kelimeyi tahmin edeceksiniz." << endl;
			system("PAUSE");
			game.secondGameStart();
		}
		else if (gameVer == 3) {
			system("PAUSE");
			game.thirdGameStart();
		}
		else {
			cout << "Öyle bir seçenek yok." << endl;
			system("PAUSE");
		}
	}

	system("PAUSE");
	return 0;
}
