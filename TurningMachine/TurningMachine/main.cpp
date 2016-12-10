/*
Mohd Sabra
TuringMachine


*/

#include<iostream>
#include <map>
#include<string>
#include<fstream>
#include <vector>



using namespace std;



class TuringMachine
{
public:
	TuringMachine(string tcurState, char tcurValue, string tnewState, char tnewValue, char tdir)
	{
		curState = tcurState;
		curValue = tcurValue;
		newState = tnewState;
		newValue = tnewValue;
		dir = tdir;
	}
	string curState;
	char curValue;
	string newState; 
	char newValue;
	char dir;
};

string FILE_NAME = "test.txt";
void parseDataFromFile();
map<string, vector<TuringMachine> > machine;
map<int, char > value;

int main() 
{
	int index = 0;
	int topLim = 0, botLim = 0;
	parseDataFromFile();
	string input; cout << "Insert Input: "; cin >> input;

	for (int i = 0; i < input.length(); i++)
	{
		topLim = i;
		value[i] = input[i];
	}
	string curState = "S0";
	for (;;)
	{
		if (machine[curState].empty())
		{
			cout << "Completed:" << endl; // add output
			for (int i = botLim; i <= topLim; i++)
			{
				if(value[i] != 'B')
				cout << value[i];
			}
			break;
		}
		else
		{
			for (int i = 0; i < machine[curState].size(); i++)
			{
				if (machine[curState][i].curValue == value[index])
				{
					value[index] = machine[curState][i].newValue;


					if (machine[curState][i].dir == 'R' || machine[curState][i].dir == 'r')
					{
						index++;
						if (index > topLim)
						{
							value[index] = 'B';
							topLim++;
						}
					}
					else if (machine[curState][i].dir == 'l' || machine[curState][i].dir == 'L')
					{
						index--;
						if (index < botLim)
						{
							value[index] = 'B';
							botLim--;
						}
					}
					curState = machine[curState][i].newState;
					break;
				}
				if (i + 1 == machine[curState].size())
				{
					cout << "Hault!!! String not accepted (last string view):" << endl; // add output
					for (int i = botLim; i <= topLim; i++)
					{
						cout << value[i];
					}
					int ends;
					cin >> ends;
					return 2;
				}
			}
		}
	}
	int ends;
	cin >> ends;
	return 1;
}

void parseDataFromFile()
{
	ifstream file;
	file.open(FILE_NAME.c_str());
	string temp[5];

	if (file.is_open())
	{
		while (file >> temp[0] >> temp[1][0] >> temp[2] >> temp[3][0] >> temp[4][0] )
		{			   
				TuringMachine tempMachine(temp[0], temp[1][0], temp[2], temp[3][0] , temp[4][0]);
				machine[temp[0]].push_back(tempMachine);
		}
		file.close();
	}
	else
	{ 
		std::cout << " failed to open file";
	}

}
