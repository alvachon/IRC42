#ifndef IRC_HPP
# define IRC_HPP

//test.cpp
# include <iostream>
# include <fcntl.h> //		fds
# include <unistd.h> //		close fds
# include <arpa/inet.h> //	IP stuff
# include <netinet/in.h> //	IP stuff
# include <sys/socket.h> //	socket stuff
# include <string.h> //		string (why not <string> instead ??)

# include "Message.hpp"
# include "Server.hpp"
# include "User.hpp"

# define BUFFSIZE 256

//	put defines here
static bool	stopFlag = false;

//test.cpp
void irc(Server *server);

#endif // IRC_HPP
