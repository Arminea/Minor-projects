#pragma once

#include <string>
#include <vector>

#include "lexicalA.h"
#include "nutsymdef.h"
#include "nuttoken.h"

namespace parser {

	class NutParser
	{
	public:
		NutParser(std::string input);

		std::vector<parser::NutToken> GetNutTokens();

		NutToken GetToken(int index);

		void AddToken(parser::NutToken new_token);

		std::string GetDebugInfo();

		~NutParser();

	private:
		/* Vektor tokenu */
		std::vector<parser::NutToken> nut_tokens;

		void StartParsing(std::string input);
		
		void ParseInput(parser::LexicalA &lex);

		/* Processes input command */
		void InputCommand(parser::LexicalA &lex, parser::NutToken &nut_token);
		/* Processes output command */
		void OutputCommand(parser::LexicalA &lex, parser::NutToken &nut_token);
		/* End of command? */
		bool EndOfCommand(parser::LexicalA &lex);
		/* Incorrect syntax message */
		void IncorrectSyntax();

		/* Trim functions */
		std::string& trim_left_in_place(std::string& str);
		std::string& trim_right_in_place(std::string& str);
		std::string& trim_in_place(std::string& str);

	};

} // namespace parser