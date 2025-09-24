#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
using namespace std;

// global constants
const int Max_Students = 200; // capacity; file may be fewer
const int numTests = 5;

// function prototypes
int readData(ifstream& in, string names[], double scores[][numTests], int maxStudents);
void computeAverages(const double scores[][numTests], int count, double avgs[]);
char letterFromAverage(double avg);
void printReport(const string names[], const double avgs[], int count);

int main() {
	// opens the input file
	ifstream fin("StudentGrades.txt");
	if (!fin) {
		cerr << "Error: could not open input file.\n";
		return 1;
	}

	// parallel arrays
	string names[Max_Students];
	double scores[Max_Students][numTests];
	double avgs[Max_Students];

	// read data
	int studentCount = readData(fin, names, scores, Max_Students);
	fin.close();

	if (studentCount == 0) {
		cout << "Nostudent records found.\n";
		return 0;
	}

	// computes averages then prints report
	computeAverages(scores, studentCount, avgs);
	printReport(names, avgs, studentCount);

	return 0;
}

// reads names and NumTests scores per student into parallel arrays
// returns the number of student records actually read
int readData(ifstream& in, string names[], double scores[][numTests], int maxStudents) {
	int count = 0;
	string line;
	while (count < maxStudents && getline(in, line)) {
		if (line.empty()) continue; // skips blank lines

		// create a stringstream to parse this line
		size_t lastSpace = line.find_last_of(" ");
		if (lastSpace == string::npos) continue; // skip invalid lines

		// reads scores from the end of the line
		// split into tokens, last numTests tokens = scores, rest = name
		double tempScores[numTests];
		size_t pos = line.size();
		int scoresFound = 0;

		// parse backwards for numTests scores
		while (scoresFound < numTests && lastSpace != string::npos) {
			string token = line.substr(lastSpace + 1, pos - lastSpace - 1);
			tempScores[numTests - 1 - scoresFound] = stod(token);
			scoresFound++;

			pos = lastSpace;
			if (pos == 0) break;
			lastSpace = line.find_last_of(" ", pos - 1);
		}

		if (scoresFound != numTests) continue; // incomplete record = skip

		names[count] = line.substr(0, pos); // remaining part is the name

		for (int j = 0; j < numTests; ++j) // copy scores into 2d array
			scores[count][j] = tempScores[j];

		++count;
	}
	return count;
}

// computes per-student averages from the scores array
void computeAverages(const double scores[][numTests], int count, double avgs[]) {
	for (int i = 0; i < count; ++i) {
		double sum = 0.0;
			for (int j = 0; j < numTests; ++j) sum += scores[i][j];
		avgs[i] = sum / numTests;
	}
}

// converts numeric average to a letter grade
char letterFromAverage(double avg) {
	if (avg >= 90.0) return 'A';
	if (avg >= 80.0) return 'B';
	if (avg >= 70.0) return 'C';
	if (avg >= 60.0) return 'D';
	return 'F';
}

// prints report
void printReport(const string names[], const double avgs[], int count) {
	const int NAME_W = 15;
	cout << left << setw(NAME_W) << "Student"
		<< right << setw(10) << "Average"
		<< setw(10) << "Grade" << '\n';
	cout << string(NAME_W + 20, '-') << '\n';

	cout << fixed << setprecision(1);
	for (int i = 0; i < count; ++i) {
		cout << left << setw(NAME_W) << names[i]
			<< right << setw(10) << avgs[i]
			<< setw(10) << letterFromAverage(avgs[i])
			<< '\n';
	}
}