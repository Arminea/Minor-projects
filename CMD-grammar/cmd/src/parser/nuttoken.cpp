
#include "nuttoken.h"

parser::NutToken::NutToken(int p_token_type)
{
	token_type = p_token_type;
}

parser::NutToken::~NutToken()
{
}

/* *********** GETTERS ************* */

int parser::NutToken::GetTokenType() { return token_type; }

std::string parser::NutToken::GetInput() { return input; }

std::string parser::NutToken::GetOutput() { return output; }

std::vector<std::string> parser::NutToken::GetParameters() { return parameters; }

std::string parser::NutToken::GetParameter(int index)
{
	return parameters[index];
}

/* *********** SETTERS ************* */

void parser::NutToken::SetInput(std::string in) { input = in; }

void parser::NutToken::SetOutput(std::string out) { output = out; }

void parser::NutToken::AddParameter(std::string param) { parameters.push_back(param); }
