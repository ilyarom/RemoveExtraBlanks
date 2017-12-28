#include "stdafx.h"
#include "CommentHandler.h"
#include "Constants.h"
#include "LexicalAnalysator.h"
#include "StringHandler.h"
#include "Token.h"
using namespace std;

void parseInput(ifstream &input, ofstream &output)
{
	string line;
	string result;
	bool isComment = false;
	CommentHandler commentHandler;
	StringHandler stringHandler;
	LexicalAnalysator analysator;
	Token token;
	size_t lineCount = 0;
	size_t charCount = 0;
	size_t stringPos;
	string stringBuffer;
	Token stringToken;
	bool isNeedPrintStringToken = false;;
	bool isProcessingString = false;
	while (!input.eof())
	{
		char symbol;
		input.get(symbol);
		if (commentHandler.isCommentEnd(symbol) && !isProcessingString || input.eof())
		{
			symbol = ' ';
		}
		else if (commentHandler.isComment(symbol) && !isProcessingString)
		{
			continue;
		}
		if (stringHandler.isStringBegin(symbol))
		{
			if (input.eof())
			{
				stringToken.setType(TokenType::UNCLOSED_STRING);
				isNeedPrintStringToken = true;
			}
			else
			{
				stringHandler.setReadMode(ReadMode::STRING);
				stringToken.setValue(stringToken.getValue() + symbol);
				stringToken.setType(TokenType::STRING);
				isProcessingString = true;
				continue;
			}
		}
		else if (stringHandler.isStringEnd(symbol))
		{
			if (input.eof())
			{
				stringToken.setType(TokenType::UNCLOSED_STRING);
				isNeedPrintStringToken = true;
			}
			else
			{
				if (!stringHandler.isEcraning)
				{
					stringHandler.setReadMode(ReadMode::CODE);
				}
				stringToken.setValue(stringToken.getValue() + symbol);
				isNeedPrintStringToken = true;
				symbol = ' ';
				isProcessingString = false;
			}
		}
		else if (stringHandler.isString(symbol))
		{
			if (input.eof())
			{
				stringToken.setType(TokenType::UNCLOSED_STRING);
				isNeedPrintStringToken = true;
			}
			else
			{
				stringToken.setValue(stringToken.getValue() + symbol);
				if (symbol == Constants::ECRANING_SYMBOL)
				{
					stringHandler.isEcraning = true;
				}
				else
				{
					stringHandler.isEcraning = false;
				}
				continue;
			}
		}
		/*if (stringHandler.isStringReading(symbol))
		{
			stringBuffer += symbol;
			continue;
		}*/
		if (analysator.isIndent(symbol) || input.eof())
		{
			analysator.getTokensFromString(result);
			result.clear();
		}
		else {
			result += symbol;
		}
		if (isNeedPrintStringToken)
		{
			stringToken.printToken();
			isNeedPrintStringToken = false;
			stringToken.clear();
		}
	}
	cout << "Token: <EOF> type: <markers>" << endl;
}

int main()
{
	ifstream input("input.txt");
	ofstream output("output.txt");
	parseInput(input, output);
	return 0;
}
