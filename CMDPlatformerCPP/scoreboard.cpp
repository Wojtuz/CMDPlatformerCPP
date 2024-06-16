#include  <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>

using namespace std;
void openScoreboard() {
	fstream file;
	file.open("scoreboard.txt", ios::in);

	vector<pair<int, string>> scores;

	if (file.is_open()) {
		string line;
		while (getline(file, line)) {
			size_t pos = line.find_last_of(" ");
			if (pos != string::npos) {
				int score = stoi(line.substr(pos + 1));
				string name = line.substr(0, pos);
				scores.push_back(make_pair(score, name));
			}
		}
		file.close();
	}

	sort(scores.begin(), scores.end(), [](const pair<int, string>& a, const pair<int, string>& b) {
		return a.first > b.first;
		});


	for (const auto& score : scores) {
		cout << score.second << " " << score.first << endl;
	}
}