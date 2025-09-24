#include <iostream>
#include <string>
#include <cstdlib> // For rand() and srand()
#include <ctime> // For time()

using namespace std;

// Function prototypes
string getPlayerChoice();
string getComputerChoice();
string determineWinner(const string& playerChoice, const string& computerChoice);
void updateScores(const string& winner, int& playerScore, int& computerScore);
void displayTournamentWinner(int playerScore, int computerScore);

int main() {
	srand(static_cast<unsigned int>(time(0))); // seed random number generator

	int playerScore = 0, computerScore = 0;
	string playerChoice, computerChoice, winner;

	cout << "Welcome to the Rock, Paper, Scissors Tournament" << endl;

	while (true) {
		playerChoice = getPlayerChoice();

		if (playerChoice == "quit") {
			break; // end tournament
		}

		computerChoice = getComputerChoice();
		cout << "Computer chose: " << computerChoice << endl;

		winner = determineWinner(playerChoice, computerChoice);
		cout << "Round result: " << winner << endl;

		updateScores(winner, playerScore, computerScore);

		cout << "Current Scores - You: " << playerScore << " | Computer: " << computerScore << "\n\n";
	}

	displayTournamentWinner(playerScore, computerScore);
	return 0;
}

// function to get and validate player choice
string getPlayerChoice() {
	string choice;
	while (true) {
		cout << "Enter rock, paper, scissors, or quit: ";
		cin >> choice;

		// convert input to lowercase for robustness
		for (char& c : choice) c = tolower(c);

		if (choice == "rock" || choice == "paper" || choice == "scissors" || choice == "quit") {
			return choice;
		}
		else {
			cout << "Invalid choice. Please try again." << endl;
		}
	}
}

// function yo generate computer choice
string getComputerChoice() {
	int randomNum = rand() % 3 + 1;
	switch (randomNum) {
	case 1: return "rock";
	case 2: return "paper";
	default: return "scissors";
	}
}

// funtion to determine winner of the round
string determineWinner(const string& playerChoice, const string& computerChoice) {
	if (playerChoice == computerChoice)
		return "draw";
	if ((playerChoice == "rock" && computerChoice == "scissors") || (playerChoice == "scissors" && computerChoice == "paper") || (playerChoice == "paper" && computerChoice == "rock")) {
		return "player";
	}
	else {
		return "computer";
	}
}

// function to update scores
void updateScore(const string& winner, int& playerScore, int& computerScore) {
	if (winner == "player")
		playerScore++;
	else if (winner == "computer")
		computerScore++;
}

// function to display final results
void displayTournamentWinner(int playerScore, int computerScore) {
	cout << "\n==== TOURNAMENT RESULTS ====" << endl;
	cout << "Final Scores - You: " << playerScore << " | Computer: " << computerScore << endl;

	if (playerScore > computerScore)
		cout << "Congratulations! you win the tournament" << endl;
	else if (computerScore > playerScore)
		cout << "Computer wins the tournament" << endl;
	else
		cout << "The tournament ends in a draw" << endl;
}