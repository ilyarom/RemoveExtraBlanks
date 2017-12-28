#include "stdafx.h"
#include "Token.h"
#include "Constants.h"
using namespace std;

void Token::clear()
{
	value = "";
	type = ERROR;
}

string Token::getValue() const
{
	return value;
}

void Token::setValue(const string &argValue)
{
	value = argValue;
}

void Token::setType(TokenType argType)
{
	type = argType;
}

string Token::getType() const
{
	string stringType = "";
	switch (type) {
		case IDENTIFIER:
			stringType = "IDENTIFIER";
			break;
		case INT:
			stringType = "INT";
			break;
		case REAL:
			stringType = "REAL";
			break;
		case OPERATION:
			stringType = "OPERATION";
			break;
		case COMMENT:
			stringType = "COMMENT";
			break;
		case DELIMITER:
			stringType = "DELIMITER";
			break;
		case DOT_DELIMITER:
			stringType = "DELIMITER";
			break;
		case REGULAR:
			stringType = "REGULAR";
			break;
		case STRING:
			stringType = "STRING";
			break;
		case UNCLOSED_STRING:
			stringType = "ERROR. UNCLOSED STRING LITERAL";
			break;
		default:
			stringType = "ERROR";
			break;
	}
	return stringType;
}

void Token::printToken() const
{
	if (!getValue().empty())
	{
		cout << "Token: <" + getValue() + "> type: <" + getType() + ">" << endl;
	}
}

string Token::toLowerCase(const string &arg)
{
	string result;
	for (char symbol : arg)
	{
		result += (char)tolower(symbol);
	}
	return result;
}


bool Token::isIdentifier(const string &arg)
{
	/*regex identifier("[_a-zA-Z][_a-zA-Z0-9]*");
	return regex_match(arg, identifier);*/
	if (!arg.empty())
	{
		if ((find(Constants::IDENTIFIER_FIRST_SYMBOLS.begin(), Constants::IDENTIFIER_FIRST_SYMBOLS.end(), tolower(arg[0])) == Constants::IDENTIFIER_FIRST_SYMBOLS.end()) || arg.length() > 30)
		{
			return false;
		}
	}
	else
	{
		return false;
	}
	for (char symbol : arg)
	{
		if (find(Constants::IDENTIFIER_SYMBOLS.begin(), Constants::IDENTIFIER_SYMBOLS.end(), tolower(symbol)) == Constants::IDENTIFIER_SYMBOLS.end())
		{
			return false;
		}
	}
	return true;
}

bool Token::isRegularWord(const string& arg)
{
	return find(Constants::REGULAR_WORDS.begin(), Constants::REGULAR_WORDS.end(), toLowerCase(arg)) != Constants::REGULAR_WORDS.end();
}

bool Token::isOperation(const string& arg)
{
	return find(Constants::OPERATIONS.begin(), Constants::OPERATIONS.end(), arg) != Constants::OPERATIONS.end();
}

bool Token::isIntNumber(const string &arg)
{
	//regex number("^(?=.)([+-]?([0-9]*)(\.([0-9]+))?)$");
	if (arg.empty())
		return false;
	for (size_t i = 0; i < arg.length(); ++i)
	{
		if (find(Constants::NUMBER_ALPHABET.begin(), Constants::NUMBER_ALPHABET.end(), arg[i]) == Constants::NUMBER_ALPHABET.end())
			return false;
	}
	return true;
}

bool Token::isIntNumberIn16(const string &arg)
{
	//regex number("^(?=.)([+-]?([0-9]*)(\.([0-9]+))?)$");
	string lowerCaseArg = toLowerCase(arg);
	if (lowerCaseArg.length() < 3 || lowerCaseArg[0] != '0' || lowerCaseArg[1] != Constants::SYSTEM_16_SYMBOL)
		return false;
	for (size_t i = 2; i < lowerCaseArg.length(); ++i)
	{
		if (find(Constants::NUMBER_ALPHABET_16.begin(), Constants::NUMBER_ALPHABET_16.end(), lowerCaseArg[i]) == Constants::NUMBER_ALPHABET_16.end())
			return false;
	}
	return true;
}

bool Token::isIntNumberIn8(const string &arg)
{
	//regex number("^(?=.)([+-]?([0-9]*)(\.([0-9]+))?)$");

	if (arg.length() < 3 || arg[0] != '0' || tolower(arg[1]) != Constants::SYSTEM_8_SYMBOL)
		return false;
	for (size_t i = 2; i < arg.length(); ++i)
	{
		if (find(Constants::NUMBER_ALPHABET_8.begin(), Constants::NUMBER_ALPHABET_8.end(), arg[i]) == Constants::NUMBER_ALPHABET_8.end())
			return false;
	}
	return true;
}

bool Token::isIntNumberIn2(const string &arg)
{
	//regex number("^(?=.)([+-]?([0-9]*)(\.([0-9]+))?)$");

	if (arg.length() < 3 || arg[0] != '0' || tolower(arg[1]) != Constants::SYSTEM_2_SYMBOL)
		return false;
	for (size_t i = 2; i < arg.length(); ++i)
	{
		if (find(Constants::NUMBER_ALPHABET_2.begin(), Constants::NUMBER_ALPHABET_2.end(), arg[i]) == Constants::NUMBER_ALPHABET_2.end())
			return false;
	}
	return true;
}

bool Token::isRealNumber(const string &arg)
{
	//regex number("^(?=.)([+-]?([0-9]*)(\.([0-9]+))?)$");
	if 
	(
		arg.empty() 
		|| (arg.length() == 1 && arg[0] == Constants::DOT)
		|| arg[0] == Constants::E
		|| arg[arg.length() -1] == Constants::E	
		|| arg[arg.length() - 1] == Constants::PLUS
		|| arg[arg.length() - 1] == Constants::MINUS
	)
		return false;
	bool isDotUsed = false;
	bool isEUsed = false;
	bool isExpectedOperation = false;
	bool isOperationUsed = false;
	for (size_t i = 0; i < arg.length(); ++i)
	{
		if
		(
			find(Constants::REAL_ALPHABET.begin(), Constants::REAL_ALPHABET.end(), arg[i]) == Constants::REAL_ALPHABET.end()
			|| (arg[i] == Constants::DOT && isDotUsed)
			|| (arg[i] == Constants::E && isEUsed)
			|| (isExpectedOperation && arg[i] != Constants::PLUS && arg[i] != Constants::MINUS)
			|| (isOperationUsed && (arg[i] == Constants::PLUS || arg[i] == Constants::MINUS))
			|| (arg[i] == Constants::E && isEUsed)
			|| (!isExpectedOperation && (arg[i] == Constants::PLUS || arg[i] == Constants::MINUS))
		//	|| (arg[i] == Constants::E && find(Constants::NUMBER_ALPHABET.begin(), Constants::NUMBER_ALPHABET.end(), arg[i - 1]) == Constants::NUMBER_ALPHABET.end())
		)
			return false;
		if (arg[i] == Constants::DOT)
		{
			isDotUsed = true;
		}
		if (arg[i] == Constants::E)
		{
			isEUsed = true;
			isExpectedOperation = true;
		}
		else
		{
			isExpectedOperation = false;
		}
		if ((arg[i] == Constants::PLUS || arg[i] == Constants::MINUS) && !isOperationUsed)
		{
			isOperationUsed = true;
		}
	}
	return true;
}

bool Token::isDelimiter(const string& arg)
{
	return find(Constants::DELIMITERS.begin(), Constants::DELIMITERS.end(), arg) != Constants::DELIMITERS.end();
}

size_t Token::tokenFromString(string arg)
{
	/*string substring = "";
	for (size_t i = 0; i < arg.length(); ++i)
	{*/
		//substring = (arg.substr(0, arg.length() - i));
		if (arg.empty())
		{
			setValue("");
			setType(TokenType::ERROR);
			return 0;
		}
		if (isIntNumber(arg))
		{
			setType(TokenType::INT);
		}
		else if (isIntNumberIn16(arg))
		{
			setType(TokenType::INT);
		}
		else if (isIntNumberIn8(arg))
		{
			setType(TokenType::INT);
		}
		else if (isIntNumberIn2(arg))
		{
			setType(TokenType::INT);
		}
		else if (isRealNumber(arg))
		{
			setType(TokenType::REAL);
		}
		else if (isRegularWord(arg))
		{
			setType(TokenType::REGULAR);
		}
		else if (isIdentifier(arg))
		{
			setType(TokenType::IDENTIFIER);
		}
		else if (isOperation(arg))
		{
			setType(TokenType::OPERATION);
		}
		else if (isDelimiter(arg))
		{
			setType(TokenType::DELIMITER);
		}
		else {
			setType(TokenType::ERROR);
			//continue;
		}
		setValue(arg);
		return arg.length();
	//}
}
