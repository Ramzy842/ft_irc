#include "cmd.hpp"

void Server::quit(std::string &msg, int fd)
{
	std::vector<std::string> cmd = split_command(msg);
	Client *client = this->getClient(fd);
	if (client->getIsRegistered())
	{
		for(std::vector<Channel>::iterator it = this->channels.begin(); it != this->channels.end(); ++it)
		{
			if (it->getMemberByName(client->getNickname()))
			{
				it->removeMember(*client);
				if(it->getOperatorByName(client->getNickname()))
					it->removeOperator(*client);
				if(cmd.size() > 1)
					it->sendToAll(client->getNickname() + " has quit (" + cmd[1] + ")");
				else
					it->sendToAll(client->getNickname() + " has quit");
			}
		}
	}
	close(fd);
}