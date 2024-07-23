#include "cmd.hpp"

#define ERR_NEEDMOREPARAMS(command) "461 " + command + " :Not enough parameters"

void Server::quit(std::string &msg, int fd)
{
	std::vector<std::string> cmd = split_command(msg);
	if(cmd.size() > 2)
	{
		senderreur(fd, ERR_NEEDMOREPARAMS(cmd[0]));
		return;
	}
	Client *client = this->getClient(fd);
	if (client->getIsRegistered())
	{
		for(std::vector<Channel *>::iterator it = this->channels.begin(); it != this->channels.end(); ++it)
		{
			if ((*it)->getMemberByName(client->getNickname()))
			{
				(*it)->removeMember(*client);
				if ((*it)->getOperatorByName(client->getNickname()))
					(*it)->removeOperator(*client);
				std::string msg;
				if(cmd.size() == 2)
					msg = ":" + client->getNickname() + "!~" + client->getHostname() + "@localhost QUIT " + cmd[1];
				else
					msg = ":" + client->getNickname() + "!~" + client->getHostname() + "@localhost QUIT";
				for(size_t i = 0; i < (*it)->getMembers().size(); i++)
					sendMsg((*it)->getMembers()[i]->getFd(), msg);
			}
		}
	}
	close(fd);
}