#pragma once

#include <vector>

namespace parser {
	/* check symbol code \u2713 */

	const std::vector<std::string> keywords = { "cmd", "echo", "cd", "dir", "md", "rd", "type", "sort", "rand", "freq", "exit" };

	const std::vector<char> operators = { '<', '>', '|' };

	const std::vector<std::string> pom = { "cmd", "echo", "cd", "dir", "md", "rd", "type", "sort", "rand", "freq", "<", ">", "|", "exit" };

	class NutSymDef
	{

		public:
			
			enum {
				CMD = 0, ECHO = 1, CD = 2, DIR = 3, MD = 4, RD = 5, TYPE = 6,
				SORT = 7, RAND = 8, FREQ = 9, INPUT = 10, OUTPUT = 11, PIPE = 12, EXIT = 13,
				SOMETHING = 14,

				EOL = 1000 // end of line - konec commandu
			};
			
	};

} //namespace parser