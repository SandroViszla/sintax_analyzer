#pragma once
#include <iostream>
#include <regex> // не стоит это использовать
#include <string>
#include <vector>
#include <cctype>

#include "token.h"


const int CommandsAmount = 3;

enum class CommandType { // пример использования: CommandNames[(int)CommandType::CREATE] = "create table" и с CommandTypesFunctions работает аналогично
	CREATE, 
	ALTER, 
	DROP 
};

const std::string CommandNames[CommandsAmount] = { // статический массив для основоных операторов, с которых может начинаться запрос
	"create table",
	"alter table",
	"drop table"
};

class Analyzer
{
private:
	std::string command;
	std::vector<Token>* TokensLinePtr;
	void initialise();
	bool StrStartsWith(std::string);
public:
	Analyzer();
	bool AnaliseCreateTable(); 
	bool AnaliseAlterTable();
	bool AnaliseDropTable();
	bool StartAnalis(std::string command);

};

typedef bool (Analyzer::*TypeCommandAnalise)();		//тип данных, представляющий собой указатель на метод

const TypeCommandAnalise CommandTypesFunctions[CommandsAmount] = { // статический массив для основоных операторов, с которых может начинаться запрос
	&Analyzer::AnaliseCreateTable,	// здесь собраны все специализированные методы для каждого типа запроса
	&Analyzer::AnaliseAlterTable,
	&Analyzer::AnaliseDropTable
};

Analyzer::Analyzer() 
{ 
	initialise();
}

void Analyzer::initialise()
{
	//может потом пригодится
}

bool Analyzer::AnaliseCreateTable()		// специализированные методы. они нужны так для каждого ключевого оператора (create alter и т д ) используются разные вспомогательные операторы
{
	Token tkn("");
	if (TokensLinePtr==NULL ) {
		std::cout << "::::" << std::endl;
		//TokensLinePtr->clear(); // очищаем старый массив токенов, чтобы перезаписать его
	}
	std::vector<Token>* TokensLinePtr = tkn.GetTokens(command);
	for (auto& tkn : *TokensLinePtr)
	{
		//std::cout << tkn.GetName() << (int)tkn.GetType();
	}
	if ((*TokensLinePtr)[0].GetType() != token_type::MainOperator && (*TokensLinePtr)[1].GetType() != token_type::MainOperator)
		return false;
	if ((*TokensLinePtr)[2].GetType() != token_type::Identifier) return false;
	if ((*TokensLinePtr)[3].GetType() != token_type::LPAR) return false;
	int i = 4;
	for (; i < TokensLinePtr->size()-4;i+=3)
	{
		if ((*TokensLinePtr)[i].GetType() != token_type::Identifier) return false;
		if ((*TokensLinePtr)[i+1].GetType() != token_type::VariableType) return false;
		if ((*TokensLinePtr)[i + 2].GetType() != token_type::COMMA) return false;
	}
	if ((*TokensLinePtr)[i].GetType() != token_type::Identifier) return false;
	if ((*TokensLinePtr)[++i].GetType() != token_type::VariableType) return false;
	if ((*TokensLinePtr)[++i].GetType() != token_type::RPAR) return false;
	if ((*TokensLinePtr)[++i].GetType() != token_type::SMCLN) return false;
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

bool Analyzer::StrStartsWith(std::string key) // проверка с какого ключевого слова начинается запрос
{
	for (int i = 0; i < this->command.length(); i++)
	{
		if (this->command[i] == ' ' || this->command[i] == '\t')	//игнорирование пробелов и табуляций
			continue;
		if (this->command.find(key) == i)
			return true;
		else
			return false;
	}
	return false;
}

bool Analyzer::StartAnalis(std::string _command)	//запуск анализа 
{
	command.clear();
	for (auto& c : _command) {
		command += std::tolower(c);
	}
	//if (!TokensLinePtr->empty()) {
		//TokensLinePtr->clear(); // очищаем старый массив токенов, чтобы перезаписать его
	//}
	for (int i = 0; i < CommandsAmount; i++) {
		if (this->StrStartsWith(CommandNames[i]))
		{
			return ((this->*CommandTypesFunctions[i])());	// в зависимости от ключевого слова в начале запроса вызываются разные специализированные методы
		}
	}
	return false;
}

int main()
{
	std::string text = "12345";
	std::string text2 = "create table tablename (id int, data date, cost int);";
	Analyzer analyzer;
	std::cout << analyzer.StartAnalis(text) << std::endl;
	std::cout << analyzer.StartAnalis(text2) << std::endl;
	std::cout << analyzer.StartAnalis(text2) << std::endl;
	return 0;
}

/*
CREATE TABLE table_name
(
	column_name_1 column_type_1,
	column_name_2 column_type_2,
	...,
	column_name_N column_type_N,
);

ALTER TABLE название_таблицы [WITH CHECK | WITH NOCHECK]
{ ADD название_столбца тип_данных_столбца [атрибуты_столбца] |
  DROP COLUMN название_столбца |
  ALTER COLUMN название_столбца тип_данных_столбца [NULL|NOT NULL] |
  ADD [CONSTRAINT] определение_ограничения |
  DROP [CONSTRAINT] имя_ограничения}

DROP TABLE table_name
*/