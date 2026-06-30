//Написати програму, яка:
// 1. копіює вміст вхідного файла у вихідний; 
// 2. підраховує кількість слів у тексті, які закінчуються на голосну літеру; 
// 3. знаходить всі слова, довжина яких менша п'яти символів; 
// 4. видаляє всі слова, які містять хоча б одну латинську літеру
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <cctype>
#include <windows.h>

using namespace std;

const string ukrVowels = "аеиіоуяюєї";

bool isVowel(char c) {
	c = tolower(c);
	for (char v : ukrVowels) {
		if (c == v) { return true; }
	}
	return false;
}

bool endsWithVowel(const string& word) {
	if (word.empty()) { return false; }
	return isVowel(word[word.length() - 1]);
}

bool containsLat(const string& word) {
	for (char c : word) {
		if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) { return true; }
	}
	return false;
}

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	//відкриття вхідного файлу
	ifstream inputFile("file_input.txt");
	if (!inputFile.is_open()) {
		cout << "Помилка: не вдалося відкрити вхідний файл file_input.txt\n";
		return 1;
	}

	//відкриття вихідного файлу
	ofstream outputFile("file_output.txt");
	if (!outputFile.is_open()) {
		cout << "Помилка: не вдалося відкрити вихідний файл file_output.txt\n";
		inputFile.close();
		return 1;
	}

	// 1. копіює вміст вхідного файла у вихідний; 
	string line;
	string fullText;
	while (getline(inputFile, line)) {
		fullText += line + "\n";
		outputFile << line << "\n";
	}
	inputFile.close();

	// 2. підраховує кількість слів у тексті, які закінчуються на голосну літеру; 
	int vowelEndingCount = 0;
	vector<string> words;
	string word;

	// потік для читання слів із тексту
	istringstream iss(fullText);
	while (iss >> word) {
		words.push_back(word);
		if (endsWithVowel(word)) {
			vowelEndingCount++;
		}
	}

	// 3. знаходить всі слова, довжина яких менша п'яти символів; 
	vector<string> shortWords;
	for (const string& w : words) {
		if (w.length() < 5) {
			shortWords.push_back(w);
		}
	}

	// 4. видаляє всі слова, які містять хоча б одну латинську літеру
	vector<string> filteredWords;
	for (const string& w : words) {
		if (!containsLat(w)) {
			filteredWords.push_back(w);
		}
	}



	// виведення результатів на екран
	cout << "Кількість слів, які закінчуються на голосну літеру: " << vowelEndingCount << "\n";

	cout << "Слова, довжина яких менша за 5 символів:\n";
	if (shortWords.empty()) {
		cout << "Немає таких слів.\n";
	} else {
		for (const string& w : shortWords) {
			cout << w << " ";
		}
		cout << "\n";
	}

	cout << "Текст після видалення слів із латинськими літерами:\n";
	if (filteredWords.empty()) {
		cout << "Усі слова містили латинські літери.\n";
	} else {
		for (const string& w : filteredWords) {
			cout << w << " ";
		}
		cout << "\n";
	}

	// запис результатів у file_output.txt
	outputFile << "\n=== Результати ===\n";
	outputFile << "Кількість слів, які закінчуються на голосну літеру: " << vowelEndingCount << "\n";

	outputFile << "Слова, довжина яких менша за 5 символів:\n";
	if (shortWords.empty()) {
		outputFile << "Немає таких слів.\n";
	}
	else {
		for (const string& w : shortWords) {
			outputFile << w << " ";
		}
		outputFile << "\n";
	}

	outputFile << "Текст після видалення слів із латинськими літерами:\n";
	if (filteredWords.empty()) {
		outputFile << "Усі слова містили латинські літери.\n";
	}
	else {
		for (const string& w : filteredWords) {
			outputFile << w << " ";
		}
		outputFile << "\n";
	}

	outputFile.close();
	cout << "Результати записано у файл file_output.txt\n";

	return 0;
}