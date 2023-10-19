#include "IRC.hpp"



void	Server::knownChannel(User *user, Channel *chan, std::vector<std::string> args)
{
//	Check all conditions in mode if we can add the member to this channel
	if (!isUserInChan(user, chan) && !chan->hasSameNick(user, this) && checkInvitePerm(user, chan) \
		&& checkPass(user, chan, args[2]) && checkMaxMbr(user, chan)) //	NOTE : these send their own error messages
	{
//		the client can enter the channel
		debugPrint(MAGENTA, "\n > joinning a channel\n"); // DEBUG

		chan->addMember(user); //								1st : add user to channel
		chan->sendToChan(user, makeChanMsg(user, "JOIN", chan->getChanName()), true);	//	2nd : tell channel they joined
		chan->updateMemberList(user); //						3rd : update member list for all members
	}
}



void	Server::newChannel(User *user, std::vector<std::string> args)
{
 		if (args.size() > 2)
 		{
//			If more args are added, we assume the client wanted to join a channel, so we block the creation
			sendToUser(user, makeUserMsg(user, "403", ERR_NOSUCHCHANNEL));
 		}
		else //	create the channel
		{
			debugPrint(MAGENTA, "\n > adding a new channel\n"); //										DEBUG

			Channel *newChannel = new Channel(args[1]); //												WARNING : may need to deal with leaks
			this->_chanContainer.insert(std::pair<std::string, Channel*>(args[1], newChannel));

			newChannel->setChanName(args[1]);
			newChannel->addMember(user);
			newChannel->sendToChan(user, makeChanMsg(user, "JOIN", newChannel->getChanName()), true);

			std::cout << "newChannel: invite or not? " << newChannel->getInviteFlag() << std::endl; //	DEBUG

			newChannel->setAdminName(user->getNick());
			newChannel->addChanOps(user);

			std::string chanOp = "o " + user->getNick(); //												DEBUG
			std::cout << "chanOP string: " << chanOp << std::endl; //									DEBUG

			sendToUser(user, makeUserMsg(user, "MODE", chanOp));
		}
}



void	Server::dragToChannel(User *invitee, Channel *chan)
{
//	Check all conditions in mode if we can add the member to this channel
	if (!isUserInChan(invitee, chan) && checkMaxMbr(invitee, chan)) //	NOTE : these send their own error messages
	{
//		the client can enter the channel
		debugPrint(MAGENTA, "\n > inviting (dragging) to a channel\n"); // DEBUG

		chan->addMember(invitee); //															1st : add user to channel
		chan->sendToChan(invitee, makeChanMsg(invitee, "JOIN", chan->getChanName()), true); //	2nd : tell channel they joined
		chan->updateMemberList(invitee); //													3rd : update member list for all members
	}
}


/*
//	SENDS A SINGLE MESSAGE TO ALL MEMBERS OF A CHANNEL
void	Server::sendToChan(User *fromUser, std::string message, std::vector<std::string> args)
{
	Channel *chan = findChannel(args[1]);

//	Sends a message to every channel member if it has at least 3 args (PRIVMSG + chan + message[0])
	if (chan != NULL && args.size() > 2)
	{
		std::cerr << "sendToChan(), chan not NULL : " << args[1] << std::endl; //			DEBUG
		for (int i = 0; i < chan->getMemberCnt(); i++)
		{
			User *toUser = chan->getMember(i);

			//	Prevents sending the message to the sender or bad FD
			if (toUser != NULL && toUser != fromUser)
			{
				std::cerr << "sending chan msg to : " << toUser->getNick() << " ("; //		DEBUG
				std::cerr << i << ")" << " : " << message << std::endl; //					DEBUG
				replyTo(CHAN, fromUser, toUser, "", message);

			}
		}
	}
}
*/

void	Server::processChanMsg(User *sender, std::string message, std::vector<std::string> args)
{
	Channel *chan = findChannel(args[1]);

//	Sends a message to every channel member if it has at least 3 args (PRIVMSG + chan + message[0])
	if (chan != NULL && args.size() > 2)
	{
		std::cerr << "sendToChan(), chan not NULL : " << args[1] << std::endl; //			DEBUG

		chan->sendToChan(sender, makeChanMsg(sender, message));
	}
}
