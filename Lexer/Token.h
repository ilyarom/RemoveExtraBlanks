#pragma once
#include <string>
enum TokenType {
	IDENTIFIER,
	REGULAR,
	INT,
	REAL,
	OPERATION,
	COMMENT,
	DELIMITER,
	STRING,
	UNCLOSED_STRING,
	DOT_DELIMITER,
	ERROR
};

class Token
{
public:
	size_t tokenFromString(std::string arg);
	void clear();
	void printToken() const;
	std::string getValue() const;
	std::string getType() const;
	void setValue(const std::string &argValue);
	void setType(TokenType argType);
	bool isIdentifier(const std::string &arg);
	bool isRegularWord(const std::string &arg);
	bool isOperation(const std::string &arg);
	bool isIntNumber(const std::string &arg);
	bool isIntNumberIn16(const std::string &arg);
	bool isIntNumberIn8(const std::string &arg);
	bool isIntNumberIn2(const std::string &arg);
	bool isRealNumber(const std::string &arg);
	bool isDelimiter(const std::string &arg);
	std::string toLowerCase(const std::string &arg);
private:
	std::string value;
	TokenType type;
};

