#pragma once
#include <iostream>
#include <regex>
#include <string>

//#include "token.h"

using namespace std;

enum class CommandType : int { CREATE, ALTER , DROP };

class Analyzer;

typedef bool (Analyzer::*TypeCommandAnalise)();

class Analyzer
{
private:
	string command;
	static TypeCommandAnalise functions_array[10];
	bool AnaliseCreateTable();
	bool AnaliseAlterTable();
	bool AnaliseDropTable();
public:
	Analyzer();
	static void initialise();
	bool StartAnalis(string command);

};

Analyzer::Analyzer() 
{ 
	initialise();
}

void Analyzer::initialise()
{
	functions_array[(int)CommandType::CREATE] = &Analyzer::AnaliseCreateTable;
	functions_array[(int)CommandType::ALTER] = &Analyzer::AnaliseAlterTable;
	functions_array[(int)CommandType::DROP] =  &Analyzer::AnaliseDropTable;
}

bool Analyzer::AnaliseCreateTable()
{
	return true;
}

bool Analyzer::AnaliseAlterTable()
{
	return true;
}

bool Analyzer::AnaliseDropTable()
{
	return true;
}

bool Analyzer::StartAnalis(string command)
{
	regex expression("create table.*;");
	if (regex_match(command.c_str(), expression))
		cout << "true\n";
	else cout << "false\n";
	return true;
}

int main()
{
/*	string command = "create table tablename name";
	regex regular1("create table"
				   " (\\w)+");
	cmatch result;
	if (regex_match(command.c_str(), result, regular1))
	{
		for (int i = 0; i < result.size(); i++)
			cout << result[i] << endl;
	}
	else cout << "false\n";
	return 0;
	string text = "Create table";
	Token token(text);
	Token token2(text);
	*/
	string text = "create table tablename(id int, name varchar(10), cost int);";
	string text2 = "create table;";
	Analyzer analyzer;
	analyzer.initialise();
	analyzer.StartAnalis(text);
	analyzer.StartAnalis(text2);

}

