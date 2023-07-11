#include <iostream>
#include <regex> // не стоит это использовать
#include <string>


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
	void initialise();
	bool StrStartsWith(std::string);
public:
	Analyzer();
	bool AnaliseCreateTable(); 
	bool AnaliseAlterTable();
	bool AnaliseDropTable();
	bool StartAnalis(std::string command);

};

typedef bool (Analyzer::*TypeCommandAnalise)();

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
	return true; // пока методы не работают
}		// в перспективе они будут осуществлять лексическую проверку и/или выполнение запроса

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
}

bool Analyzer::StartAnalis(std::string _command)	//запуск анализа 
{
	command = _command;
	for (int i = 0; i < CommandsAmount; i++)
	{
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
	std::string text2 = "create table tablename(id int, name varchar(10), cost int);";
	Analyzer analyzer;
	std::cout << analyzer.StartAnalis(text) << std::endl;
	std::cout << analyzer.StartAnalis(text2) << std::endl;
	return 0;
}

