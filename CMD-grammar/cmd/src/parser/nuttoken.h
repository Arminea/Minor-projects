#pragma once

#include <string>
#include <vector>

namespace parser {

	class NutToken
	{

	public:
		NutToken(int p_token_type);
		~NutToken();

		int GetTokenType();
		std::string GetInput();
		std::string GetOutput();
		std::vector<std::string> GetParameters();
		std::string GetParameter(int index);

		void SetInput(std::string);
		void SetOutput(std::string);
		void AddParameter(std::string);

	private:
		/* Typ tokenu - cmd, echo, cd, atp. - vice v nutsymdef */
		int token_type;

		/* Vstup */
		std::string input;

		/* Vystup */
		std::string output;

		/* Parametry */
		std::vector<std::string> parameters;

	};


} // namespace parser