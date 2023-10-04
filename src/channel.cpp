#include "IRC.hpp"

//	0================ BASE FUNCTIONS ================0

Channel::Channel(std::string chanName): _chanName(chanName)			{ debugPrint(YELLOW, CONSTR_CHAN); }
Channel::~Channel(void) 											{ debugPrint(YELLOW, DEST_CHAN); }

//	0================ GETTERS - SETTERS ================0

std::string const & Channel::getChanName(void) const				{ return (this->_chanName); }
std::string const & Channel::getAdminName(void) const 				{ return (this->_adminName); }
std::string const & Channel::getPass(void) const 					{ return (this->_password); }

void				Channel::setChanName(std::string const &chan)	{ this->_chanName = chan; }
void				Channel::setAdminName(std::string const &admin) { this->_adminName = admin; }

//	0================ OTHER FUNCTIONS ================0

//	The channel is created implicitly when the first client joins it, and the channel ceases to exist when the last client leaves it.
//		:test!test@127.0.0.1 JOIN #

// void	Channel::joinChan(User *user, int fd, std::string code, std::string input)
// {
// // 	debugPrint(MAGENTA, "\n > joining channel\n"); //								DEBUG

// // 	std::ostringstream joinMsg;
// // 	joinMsg << ":" << user->getNick() << "!" << user->getUsername() << "@" << user->getHostname() << " JOIN " << this->getChanName() << "\n";

// // 	std::cout << joinMsg.str() << std::endl;
// // 	std::string joinChan = joinMsg.str();

// // //	letting everyone knows what happens
// // //	??????																			NOTE : ask valerie
// // 	if (send(fd, joinChan.c_str(), joinChan.size(), 0) < 0) //						TODO : Use sendToClient() instead
// // 		throw std::invalid_argument(" > Error at joinChan() ");

// 	std::ostringstream 	message;
// 	std::string 		result;

// //	Fixed struct to send all messages (template)
// 	message << ":" << user->getNick() << "!" << user->getUsername() << "@" << user->getHostname() << " " << code << " " << input << "\r\n";
// 	result = message.str();

// 	std::ostringstream debug; //											DEBUG
// 	debug << "OUTGOING C_MSG TO : (" << fd << ")\t| " << result; //			DEBUG
// 	debugPrint(GREEN, debug.str()); //										DEBUG

// 	if (send(fd, result.c_str(), result.size(), 0) < 0)
// 		throw std::invalid_argument(" > Error at sendToClient() ");

// }

void	Channel::joinChan(User* user, int fd, std::string code, std::string input)
{
	std::ostringstream 	message;
	std::string 		result;

//	Fixed struct to send all messages (template)
	message << ":" << user->getNick() << "!" << user->getUsername() << "@" << user->getHostname() << " " << code << " " << input << "\r\n";
	result = message.str();

	std::ostringstream debug; //											DEBUG
	debug << "OUTGOING C_MSG TO : (" << fd << ")\t| " << result; //			DEBUG
	debugPrint(GREEN, debug.str()); //										DEBUG

	if (send(fd, result.c_str(), result.size(), 0) < 0)
		throw std::invalid_argument(" > Error at sendToClient() ");
}
