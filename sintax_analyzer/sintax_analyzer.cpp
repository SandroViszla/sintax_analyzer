#pragma once
#include <iostream>
#include <regex>
#include <string>

#include "token.h"

using namespace std;

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
	*/
	string text = "Create table";
	Token token(text);
	Token token2(text);
}
