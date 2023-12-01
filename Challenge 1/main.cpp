#include <iostream>
#include <string>
#include <fstream>
#include <map>
using namespace std;

//It check if there is a written number on the string and returns the position
int findNumber(string row, string ext, string num, int pos, string digit)
{
	int found = row.find(ext);
	if (found == -1)
		return pos;
	else {
		if (found < pos)
			return found;
		else
			return pos;
	}
}

//A cycle to navigate on the written numbers array and get the closest number to the start of the string
string checkExtNumber(string row, string* ext, int pos, string digitFound) {
	string line = "";
	for (int i = 1; i < 9; i++) {
		int findpos = findNumber(row, ext[i], to_string(i + 1), pos, digitFound);
		if (pos > findpos) {
			line = to_string(i + 1);
			pos = findpos;
		}
	}
	return line;
}

//Get the digit and the position of the digit closest to the start of the string
map<string, string> getDigitAndPosition(string row) {
	int pos = 0;
	string digit = "";
	map<string, string> fileInfo;

	for (char ch : row) {
		if (isdigit(ch)) {
			digit = ch;
			break;
		}
		pos++;
	}

	fileInfo["Position"] = to_string(pos);
	fileInfo["Digit"] = digit;

	return fileInfo;
}

//It checks if there is any written number closest to the start than the digit is
string realDigit(string row, string* exts, int pos, string digit) {
	string line = "";
	string auxLine = "";
	int auxpos = findNumber(row, exts[0], "1", pos, digit);

	if (auxpos < pos) {
		line = "1";
		auxLine = checkExtNumber(row, exts, auxpos, digit);
		if (auxLine != "") {
			line = auxLine;
		}
	}
	else {
		line = digit;
		auxLine = checkExtNumber(row, exts, pos, digit);
		if (auxLine != "") {
			line = auxLine;
		}
	}

	return line;
}

//Check for the closest digit on the string and returns it
string checkDigit(string row) {
	string line = "";

	for (char ch : row) {
		if (isdigit(ch)) {
			line = ch;
			break;
		}
	}

	return line;
}

void challengeone() {
	int sum = 0;

	ifstream file("Texto.txt");

	if (file.is_open()) {
		string row;
		while (getline(file, row)) {
			string line = checkDigit(row);

			reverse(row.begin(), row.end());

			line += checkDigit(row);

			sum += stoi(line);
		}
	}
	else {
		cout << "Error opening file" << endl;
	}

	cout << "Your sum is " << sum << endl;
}

void challengetwo() {
	string ext[9] = { "one", "two", "three", "four", "five", "six", "seven", "eight", "nine" };
	string extreverse[9] = { "eno", "owt", "eerht", "ruof", "evif", "xis", "neves", "thgie", "enin" };
	int sum = 0;

	ifstream file("Texto.txt");

	if (file.is_open()) {
		string row;
		while (getline(file, row)) {

			map<string, string> fileInfo = getDigitAndPosition(row);

			string line = realDigit(row, ext, stoi(fileInfo["Position"]), fileInfo["Digit"]);

			reverse(row.begin(), row.end());
			fileInfo = getDigitAndPosition(row);

			string auxline = realDigit(row, extreverse, stoi(fileInfo["Position"]), fileInfo["Digit"]);

			line += auxline;
			sum += stoi(line);
		}
	}
	else {
		cout << "Error opening file" << endl;
	}

	cout << "Your sum is " << sum << endl;
}

int main() {
	challengeone();
	challengetwo();
}