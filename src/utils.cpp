#include "IRC.hpp"

void	debugPrint(std::string color, std::string message)	{std::cout << color << message << DEFCOL << std::endl;} //		DEBUG

//							SPLITS A STRING INTO A VECTOR OF STRINGS, USING CHARS AS DELIMIERS
std::vector<std::string>	splitStringPrivate(const char *str, const char *chrs)//std::string
{
	std::vector<std::string> args;
	int		i = 0;

//	NOTE : strtok works iteratively, so it needs to be called once per token
	char	*tmp1 = strdup(str);
	char	*ptr = strtok(tmp1, chrs);
	free	(tmp1); //												NOTE : BAD

	ptr = strtok(strdup(str), chrs);

	while (ptr != NULL)
	{
		char	*tmp2 = strdup(ptr);
		free (ptr); //												NOTE : BAD
		args.push_back(std::string(tmp2));
		free (tmp2); //												NOTE : BAD
		ptr = strtok(NULL, chrs);
		i++;
	}

	free (ptr); //													NOTE : BAD

	return args;
}


//							PUBLIC OVERLOADS OF splitStringPrivate THAT TAKES COMBINATIONS OF C_STRs and STD::STRINGs
std::vector<std::string>	splitString(const char *str, const char *chrs)				{ return splitStringPrivate(str, chrs); }
std::vector<std::string>	splitString(const char *str, const std::string chrs)		{ return splitStringPrivate(str, chrs.c_str()); }
std::vector<std::string>	splitString(const std::string str, const char *chrs)		{ return splitStringPrivate(str.c_str(), chrs); }
std::vector<std::string>	splitString(const std::string str, std::string const chrs)	{ return splitStringPrivate(str.c_str(), chrs.c_str()); }

std::string	makeChanMsg(User *user, std::string input)
{
	std::ostringstream 	message;
	message << ":" << user->getNick() << "!" << user->getUsername() << "@" << user->getHostname() << " " << input << "\r\n";
	return (message.str());
}
std::string	makeChanMsg(User *user, std::string code, std::string input)
{
	std::ostringstream 	message;
	message << ":" << user->getNick() << "!" << user->getUsername() << "@" << user->getHostname() << " " << code << " " << input << "\r\n";
	return (message.str());
}

std::string	makeUserMsg(User *user, std::string input)
{
	std::ostringstream 	message;
	message << ":" << user->getHostname() << " " << user->getNick() << " :" << input << "\r\n";
	return (message.str());
}
std::string	makeUserMsg(User *user, std::string code, std::string input)
{
	std::ostringstream 	message;
	message << ":" << user->getHostname() << " " << code << " " << user->getNick() << " :" << input << "\r\n";
	return (message.str());
}

std::string	makePrivMsg(User *sender, std::string input)
{
	std::ostringstream 	message;
	message << ":" << sender->getNick() << " " << input << "\r\n";
	return (message.str());
}


//	SENDS A SINGLE MESSAGE TO A SINGLE CLIENT
void	sendToUser(User *targetUser, std::string message)
{
	std::ostringstream debug; //															DEBUG
	debug << "OUTGOING USER_MSG TO : (" << targetUser->getFD() << ")\t| " << message; //	DEBUG
	debugPrint(GREEN, debug.str()); //														DEBUG

	if (send(targetUser->getFD(), message.c_str(), message.size(), 0) < 0)
		throw std::invalid_argument(" > Error at sendToUser() ");
}
