# ft_irc
Server to host a chat.

//port un peu comme un fd
TESTTESTTEST

## Netcat:
* Everything happens in the terminal. No graphic interface 
* Check if you have Netcat. Terminal: nc. To install: brew install netcat
* To connect: nc localhost <port>
* NOTE : localhost -> system preference/network -> IP adress

PASS <pass> CTRL-VM before ENTER
USER <username> CTRL-VM before ENTER
NICK <nick> CTRL-VM before ENTER

PRIVMSG #chanName :<le message> CTRL-VM before ENTER
PRIVMSG nickname :<le message> CTRL-VM before ENTER

JOIN #chanName CTRL-VM before ENTER
PART #chanName CTRL-VM before ENTER ->quit a channel
QUIT CTRL-VM before ENTER ->quit the server

## Limechat

At School ---> Get LimeChat IRC Client
Ouvre Limechat-> server/serverproperties/

Network name : irc42
server : localhost
Port: 6666

Nickname : al
Login: al
Real name : al

Click Droit --> Connect ( Va dire que la connection est refusee)
Dans le terminal (apres le make) : ./ircserv 6667 1234
