#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <utility>
#include <stdexcept>
using namespace std;

//global variables
string DNA1;
string DNA2;

void printLCS(vector<vector<char>> b, string X, int i, int j, string &sum)
{
		//base case
	if (i == 0 || j == 0)
	{
		return;
	}
	if (b[i][j] == '*')
	{
		printLCS(b, X, i - 1, j - 1, sum);
		sum += X[i-1];
	}
	else if (b[i][j] == '^')
	{
		printLCS(b, X, i - 1, j, sum);
	}
	else
	{
		printLCS(b, X, i, j - 1, sum);
	}
}

//find the length of a the common strings
int LCSLength(string &X, string &Y, int &m, int &n, vector<vector<char>> &b)
{
	//matric for C, m+1, n+1
	vector<vector<char>> c(m + 1, vector<char>(n + 1, 0));

	//loop through columns
	for (int i = 0; i <= m; i++)
	{
		//loop through rows
		for (int j = 0; j <= n; j++)
		{
			//default fill
			if (i == 0 || j == 0)
			{
				c[i][j] = 0;
				b[i][j] = '/';
			}
			else if (X[i] == Y[j])
			{
				c[i][j] = c[i - 1][j - 1] + 1;
				b[i][j] = '*'; //this is the up/left arrow
			}
			else if (c[i - 1][j] >= c[i][j - 1])
			{
				c[i][j] = c[i - 1][j];
				b[i][j] = '^';
			}
			else
			{
				c[i][j] = c[i][j - 1];
				b[i][j] = '<';
			}

		}
	}
	return c[m][n];
}

int main() 
{
	//read in the file to DNA1 and DNA2
	ifstream myfile("C:\\Users\\Thebl\\source\\repos\\315Project4\\dna.txt");
	if (myfile.is_open())
	{
		myfile >> DNA1;
		myfile >> DNA2;
	}

	//INITIALIZATION
	string space = " ";
	DNA1.insert(0, space);
	DNA2.insert(0, space);
	int m = DNA1.length();
	int n = DNA2.length();
	string sum;
	vector<vector<char>> b(m + 1, vector<char>(n + 1, 0));
	ofstream out;
	//gets the length and runs the code to display the string
	int lcsLength = LCSLength(DNA1, DNA2, m, n, b);
	out.open("output.txt");
	out << "printed result is: " << endl;
	out << lcsLength - 1<<endl;
	printLCS(b, DNA1, m, n, sum);
	out << sum << endl;
	out.close();
	return 0;
}