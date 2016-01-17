#include <iostream>
using namespace std;

#include "lexicalA.h"

namespace parser {

	std::string m_input;

	/* Current char */
	char m_currentChar = ' ';
	/* Index of current char */
	int m_currentCharIndex = 0;

	/* Symbol */
	int m_currentSymbol;

	/* Current identifier */
	std::vector<char> m_currentIdentifier;


	LexicalA::LexicalA(std::string input)
	{
		m_input = input;
		GetNextSymbol(false);
	}

	LexicalA::~LexicalA()
	{
	}

	void LexicalA::GetNextSymbol(bool ignoreKeyWords)
	{
		
		m_currentIdentifier.clear();

		while (m_currentChar <= ' ')
			m_currentChar = InputGetChar();
		
		if (m_currentChar == '<') // file input
		{
			m_currentSymbol = NutSymDef::INPUT;
			m_currentChar = InputGetChar();
		}
		else if (m_currentChar == '>') // file output
		{
			m_currentSymbol = NutSymDef::OUTPUT;
			m_currentChar = InputGetChar();
		}
		else if (m_currentChar == '|') // pipeline
		{
			m_currentSymbol = NutSymDef::PIPE;
			m_currentChar = InputGetChar();
		}
		else
		{
			do {
				m_currentIdentifier.push_back(m_currentChar);

				m_currentChar = InputGetChar();

				if ((m_currentChar == '!'))
				{
					m_currentSymbol = NutSymDef::SOMETHING;
					break;
				}
				
				bool isOperator = IsOperator(m_currentChar);

				if (ignoreKeyWords == false)
				{
					int returnValue = IsKeyword(m_currentIdentifier);
					if (returnValue != -1) // string is the key word
					{

						if (m_currentChar == ' ' || isOperator == true || m_currentChar == '\0')
						{
							m_currentSymbol = returnValue;
							break;
						}
					}
				}

				if (isOperator)
				{
					m_currentSymbol = NutSymDef::SOMETHING;
					break;
				}

			} while (true); // loop until we find something familiar

		}

	}


	bool LexicalA::IsOperator(char character)
	{
		for (unsigned int i = 0; i < parser::operators.size(); i++)
		{
			if (character == parser::operators[i])
			{
				return true;
			}
		}

		return false;
	}

	int LexicalA::IsKeyword(std::vector<char> currentIdentifier)
	{
		std::string str(currentIdentifier.begin(), currentIdentifier.end());
		for (unsigned int i = 0; i < parser::keywords.size(); i++)
		{
			if (str == parser::keywords[i])
			{
				return i;
			}
		}

		return -1;
	}

	char LexicalA::InputGetChar()
	{
		if (m_currentCharIndex == m_input.length()+1)
		{
			return '!';
		}
		else
		{
			char ret = m_input[m_currentCharIndex];
			m_currentCharIndex++;

			return ret;
		}
	}

	/* ************************************ GETTERS ********************************** */
	int LexicalA::GetCurrentSymbol() {
		return m_currentSymbol;
	}

	std::string LexicalA::GetCurrentIdentifier() {
		std::string str(m_currentIdentifier.begin(), m_currentIdentifier.end());
		return str;
	}

} // namespace parser