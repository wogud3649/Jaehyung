#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <unordered_map>

using namespace std;

int main()
{
	vector<string> quiz = { "3 - 4 = -3", "5 + 6 = 11" };
	vector<vector<string>> quizV(quiz.size(), vector<string>(0));
	stringstream streamquiz;
	for (int i = 0; i < quiz.size(); i++)
	{
		string temp;
		streamquiz.str(quiz[i]);
		while (streamquiz >> temp)
			quizV[i].push_back(temp);
		streamquiz.clear();
			
	}
	for (int i = 0; i < quizV.size(); i++)
	{
		int a = stoi(quizV[i][0]);
		int b = stoi(quizV[i][2]);
		int c = stoi(quizV[i][4]);
		if (quizV[i][1] == "-")
		{
			if (a - b == c)
				return "O";
			else
				return "X";
		}
		else
		{
			if (a + b == c)
				return "O";
			else
				return "X";
		}
	}

	return 0;
}