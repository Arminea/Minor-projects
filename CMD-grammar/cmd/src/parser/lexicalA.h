#pragma once

#include <string>
#include <map>
#include <vector>

#include "nutsymdef.h"

namespace parser {

	class LexicalA
	{
		
	public:
		
		LexicalA(std::string input);
		~LexicalA();

		/* Precte dalsi symbol */
		void GetNextSymbol(bool ignoreKeyWords);
		
		/* Vraci cislo aktualne nalezeneho symbolu. */
		int GetCurrentSymbol();

		/* Vrati aktualni identifikator */
		std::string GetCurrentIdentifier();

	private:
		/* Funkce pro vraceni dalsiho znaku ve zpracovavanem retezci. */
		char InputGetChar();

		/* Funkce pro zjisteni, jestli je znak operator. */
		bool IsOperator(char character);

		/* Funkce pro zjisteni, jestli je naakumulovany retezec klicove slovo. */
		int IsKeyword(std::vector<char> currentIdentifier);
	};

} // namespace parser