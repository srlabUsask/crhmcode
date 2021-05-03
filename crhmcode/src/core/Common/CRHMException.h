#pragma once

#ifndef CRHMEXCEPTION
#define CRHMEXCEPTION


enum class TExcept { NONE, ERR, DECLERR, WARNING, USER, TERMINATE };


class CRHMException {
public:
	std::string Message;
	TExcept Kind;
	CRHMException() : Message(""), Kind(TExcept::NONE) {};
	CRHMException(std::string Message, TExcept Kind) :
		Message(Message), Kind(Kind) {};
};

#endif // !CRHMEXCEPTION
