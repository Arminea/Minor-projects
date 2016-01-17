#include <iostream>
using namespace std;

#include "nutparser.h"

namespace parser {

	int m_returnValue = 0; // default true, if something bad happens, it's going to be false

	NutParser::NutParser(std::string input)
	{
		StartParsing(input);
		
	}

	void NutParser::StartParsing(std::string input)
	{
		LexicalA lex(input);
		ParseInput(lex);

	}

	void NutParser::ParseInput(parser::LexicalA &lex)
	{
		
			int currSymb = lex.GetCurrentSymbol();

			/* CMD ******************************************************************************************* */
			if (currSymb == NutSymDef::CMD)
			{
				lex.GetNextSymbol(true);
				if (EndOfCommand(lex))
				{
					NutToken new_token(NutSymDef::CMD);
					AddToken(new_token);
				}
				else
				{
					IncorrectSyntax();
					return;
				}
			}
			/* ECHO ******************************************************************************************* */
			else if (currSymb == NutSymDef::ECHO)
			{
				NutToken new_token(NutSymDef::ECHO);
				lex.GetNextSymbol(true);

				if (EndOfCommand(lex) == false) // pri nezadani parametru se zapise prazdny retezec
				{

					if (lex.GetCurrentSymbol() == NutSymDef::SOMETHING) // parametry echa - proste nejaky text
					{
						new_token.AddParameter(lex.GetCurrentIdentifier()); // vlozeni parametru echa

						lex.GetNextSymbol(false);
						if (lex.GetCurrentSymbol() == NutSymDef::OUTPUT) // echo ma vystup do souboru
						{
							OutputCommand(lex, new_token);
						}
						else if (lex.GetCurrentSymbol() == NutSymDef::PIPE)
						{
							AddToken(new_token);
							lex.GetNextSymbol(false);
							ParseInput(lex);
							return;
						}
						else if (lex.GetCurrentSymbol() == NutSymDef::INPUT)
						{
							IncorrectSyntax();
							return;
						}
					}
					else if (lex.GetCurrentSymbol() == NutSymDef::OUTPUT)
					{
						OutputCommand(lex, new_token);
					}
					else
					{
						IncorrectSyntax();
						return;
					}
				}

				AddToken(new_token);
			}
			/* CD ********************************************************************************************* */
			else if (currSymb == NutSymDef::CD)
			{
				NutToken new_token(NutSymDef::CD);
				lex.GetNextSymbol(true);
				if (EndOfCommand(lex) == false) // pri nezadani parametru se zapise prazdny retezec
				{
					if (lex.GetCurrentSymbol() == NutSymDef::SOMETHING)
					{
						new_token.AddParameter(lex.GetCurrentIdentifier()); // vlozeni parametru cd

						lex.GetNextSymbol(true); // kontrola, jestli za adresarem, jeste neco neni (treba pipa)
						if (EndOfCommand(lex) == false)
						{
							IncorrectSyntax();
							return;
						}
					}
					else
					{
						IncorrectSyntax();
						return;
					}
				}

				AddToken(new_token);
			}
			/* DIR ******************************************************************************************** */
			else if (currSymb == NutSymDef::DIR)
			{
				NutToken new_token(NutSymDef::DIR);
				lex.GetNextSymbol(true);
				if (EndOfCommand(lex) == false) // dir bez parametru ma jako parametr aktualni adresar
				{
					if (lex.GetCurrentSymbol() == NutSymDef::SOMETHING)
					{
						new_token.AddParameter(lex.GetCurrentIdentifier()); // vlozeni parametru dir

						lex.GetNextSymbol(false);
						if (lex.GetCurrentSymbol() == NutSymDef::OUTPUT) // vystup informaci o aktualnim adresari do souboru
						{
							OutputCommand(lex, new_token);
						}
						else if (lex.GetCurrentSymbol() == NutSymDef::PIPE)
						{
							AddToken(new_token);
							lex.GetNextSymbol(false);
							ParseInput(lex);
							return;
						}
						else
						{
							IncorrectSyntax();
							return;
						}
					}
					else {
						IncorrectSyntax();
						return;
					}
				}

				AddToken(new_token);
			}
			/* MD ********************************************************************************************* */
			else if (currSymb == NutSymDef::MD)
			{
				NutToken new_token(NutSymDef::MD);
				lex.GetNextSymbol(true);

				if (EndOfCommand(lex)) // parametr je povinny
				{
					IncorrectSyntax();
					return;
				}

				if (lex.GetCurrentSymbol() == NutSymDef::SOMETHING)
				{
					new_token.AddParameter(lex.GetCurrentIdentifier()); // vlozeni parametru md

					lex.GetNextSymbol(true); // kontrola, jestli za adresarem, jeste neco neni (treba pipa)
					if (EndOfCommand(lex) == false)
					{
						IncorrectSyntax();
						return;
					}

					
				}
				else
				{
					IncorrectSyntax();
					return;
				}

				AddToken(new_token);
			}
			/* RD ********************************************************************************************* */
			else if (currSymb == NutSymDef::RD)
			{
				NutToken new_token(NutSymDef::RD);
				lex.GetNextSymbol(true);

				if (EndOfCommand(lex)) // parametr je povinny
				{
					IncorrectSyntax();
					return;
				}

				if (lex.GetCurrentSymbol() == NutSymDef::SOMETHING)
				{
					new_token.AddParameter(lex.GetCurrentIdentifier()); // vlozeni parametru rd

					lex.GetNextSymbol(true); // kontrola, jestli za adresarem, jeste neco neni
					if (EndOfCommand(lex) == false)
					{
						IncorrectSyntax();
						return;
					}
				}
				else
				{
					IncorrectSyntax();
					return;
				}

				AddToken(new_token);
			}
			/* TYPE ****************************************************************************************** */
			else if (currSymb == NutSymDef::TYPE)
			{
				NutToken new_token(NutSymDef::TYPE);
				lex.GetNextSymbol(true);

				if (EndOfCommand(lex)) // parametr je povinny
				{
					IncorrectSyntax();
					return;
				}

				if (lex.GetCurrentSymbol() == NutSymDef::SOMETHING)
				{
					new_token.AddParameter(lex.GetCurrentIdentifier()); // vlozeni parametru type

					lex.GetNextSymbol(true); // kontrola, jestli neni vystup do souboru
					if (lex.GetCurrentSymbol() == NutSymDef::OUTPUT)
					{
						OutputCommand(lex, new_token);
					}
					else
					{
						IncorrectSyntax();
						return;
					}
				}
				else
				{
					IncorrectSyntax();
					return;
				}

				AddToken(new_token);
			}
			/* SORT ******************************************************************************************* */
			else if (currSymb == NutSymDef::SORT)
			{
				NutToken new_token(NutSymDef::SORT);

				lex.GetNextSymbol(true);

				if (EndOfCommand(lex)) // hned vracime, je blokujici
				{
					AddToken(new_token);
					return;
				}

				if (lex.GetCurrentSymbol() == NutSymDef::SOMETHING)
				{
					new_token.AddParameter(lex.GetCurrentIdentifier()); // vlozeni parametru sort, ocekavame nazev souboru
					lex.GetNextSymbol(true);
				}
				else if (lex.GetCurrentSymbol() == NutSymDef::INPUT)
				{
					InputCommand(lex, new_token);
					lex.GetNextSymbol(true);
				}

				// muze byt jeste output nebo pipa
					
				if (lex.GetCurrentSymbol() == NutSymDef::OUTPUT)
				{
					OutputCommand(lex, new_token);

					lex.GetNextSymbol(true); // kontrola, jestli za souborem, jeste neco neni
					if (EndOfCommand(lex) == false)
					{
						IncorrectSyntax();
						return;
					}
				}
				else if (lex.GetCurrentSymbol() == NutSymDef::PIPE)
				{
					AddToken(new_token);
					lex.GetNextSymbol(false);
					ParseInput(lex);
					return;
				}
				else
				{
					IncorrectSyntax();
					return;
				}

				AddToken(new_token);
			}
			/* RAND ******************************************************************************************* */
			else if (currSymb == NutSymDef::RAND)
			{
				NutToken new_token(NutSymDef::RAND);
				lex.GetNextSymbol(true);
				if (EndOfCommand(lex) == false)
				{
					IncorrectSyntax();
					return;
				}

				AddToken(new_token);
			}
			/* FREQ ******************************************************************************************* */
			else if (currSymb == NutSymDef::FREQ)
			{
				NutToken new_token(NutSymDef::FREQ);
				lex.GetNextSymbol(true);
				if (EndOfCommand(lex) == false)
				{
					IncorrectSyntax();
					return;
				}

				AddToken(new_token);
			}
			/* EXIT ******************************************************************************************* */
			else if (currSymb == NutSymDef::EXIT)
			{
				lex.GetNextSymbol(true);
				if (EndOfCommand(lex))
				{
					NutToken new_token(NutSymDef::EXIT);
					AddToken(new_token);
				}
				else
				{
					IncorrectSyntax();
					return;
				}
			}

			/* ANYTHING ELSE ********************************************************************************* */
			else {
				IncorrectSyntax();
			}


	}


	void NutParser::InputCommand(parser::LexicalA & lex, parser::NutToken &nut_token)
	{
		lex.GetNextSymbol(true);
		if (lex.GetCurrentSymbol() == NutSymDef::SOMETHING)
		{
			if (EndOfCommand(lex))
				IncorrectSyntax();
			else
			{
				nut_token.SetInput(lex.GetCurrentIdentifier());
			}
		}
	}


	void NutParser::OutputCommand(parser::LexicalA &lex, parser::NutToken &nut_token)
	{
		lex.GetNextSymbol(true);
		if (lex.GetCurrentSymbol() == NutSymDef::SOMETHING)
		{
			if (EndOfCommand(lex))
				IncorrectSyntax();
			else
			{
				nut_token.SetOutput(lex.GetCurrentIdentifier());
			}
				
		}
	}

	bool NutParser::EndOfCommand(parser::LexicalA &lex)
	{
		if (trim_in_place(lex.GetCurrentIdentifier()) == "!")
			return true;
		else
			return false;
	}

	void NutParser::IncorrectSyntax()
	{
		cout << "The syntax of the command is incorrect." << endl;
		m_returnValue = 1;
	}

	// ****************************** TRIM ********************************************


	// modifies input string, returns input

	std::string& NutParser::trim_left_in_place(std::string& str) {
		size_t i = 0;
		while (i < str.size() && isspace(str[i])) { ++i; };
		return str.erase(0, i);
	}

	std::string& NutParser::trim_right_in_place(std::string& str) {
		size_t i = str.size();
		while (i > 0 && isspace(str[i - 1])) { --i; };
		return str.erase(i, str.size());
	}

	std::string& NutParser::trim_in_place(std::string& str) {
		return trim_left_in_place(trim_right_in_place(str));
	}

	// ************************** TOKEN VECTOR ****************************************

	std::vector<parser::NutToken> NutParser::GetNutTokens()
	{
		return nut_tokens;
	}

	NutToken NutParser::GetToken(int index)
	{
		return nut_tokens[index];
	}

	void NutParser::AddToken(parser::NutToken new_token)
	{
		nut_tokens.push_back(new_token);
	}

	std::string NutParser::GetDebugInfo()
	{
		std::string st = "";

		for (int i = 0; i < nut_tokens.size(); i++)
		{
			string input = trim_in_place(nut_tokens[i].GetInput());
			string output = trim_in_place(nut_tokens[i].GetOutput());

			st += "Token: " + pom[nut_tokens[i].GetTokenType()];

			// command's input
			if (input == "")
				st += ", input: -";
			else
				st += ", input: " + input;

			// command's output
			if (output == "")
				st += ", output: -";
			else
				st += ", output: " + output;

			// parameters
			if (nut_tokens[i].GetParameters().size() != 0) {
				st += ", params: ";
				for (string s : nut_tokens[i].GetParameters()) {
					st += trim_in_place(s) + ", ";
				}
			} 

			st += "\n";
		}

		return st;
	}

	NutParser::~NutParser()
	{
	}

} // namespace parser