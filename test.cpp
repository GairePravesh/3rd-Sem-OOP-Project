/*
	A simple multi socket based chat server in c
	@Author: Rohith Uppala
	*/

	#include <iostream>
	#include <string>
	#include <sstream>
	#include <stdio.h>
	#include <vector>
	#include <map>
	#include <stdlib.h>
	#include <unistd.h>
	#include <errno.h>
	#include <string.h>
	#include <sys/types.h>
	#include <sys/socket.h>
	#include <netinet/in.h>
	#include <arpa/inet.h>
	#include <netdb.h>
	#include <poll.h>
	#include <pthread.h>
	#define MAX_CLIENTS 10
	#define BACKLOG 5
	#define MAXLEN 100

	using namespace std;
	vector<map<int, string> > clients_info;

	vector<string> split_message(char *buff) {
		string header = "", message = "";
		vector<string> result;
		int flag = 0;
		for(int i=0; i<strlen(buff)-1; i++) {
			if(flag == 0) {
				if(buff[i] != ':') header = header + buff[i];
				else flag = 1;
			}
			else message = message + buff[i];
		}
		result.push_back(header);
		result.push_back(message);
		return result;
	}

	int main(int argc,char *argv[]) {
		int master_socket, max_sockets_allowed;
		int client_socket[MAX_CLIENTS];
		struct sockaddr_in servaddr, client_addr;
		fd_set rfds;

		// Create a masterfd connection
		master_socket = socket(AF_INET, SOCK_STREAM,0);
		bzero (&servaddr , sizeof(servaddr));
		servaddr.sin_family = AF_INET ;
		servaddr.sin_port = htons(3693);
		servaddr.sin_addr.s_addr = htons(INADDR_ANY);
		bind(master_socket, (struct sockaddr *)&servaddr, sizeof(servaddr));
		listen(master_socket, BACKLOG);

		for(int i=0; i<MAX_CLIENTS; i++) client_socket[i] = 0;

		while(1) {
			FD_ZERO(&rfds);
			FD_SET(master_socket, &rfds);
			max_sockets_allowed = master_socket;
			for(int i=0; i<MAX_CLIENTS; i++) {
				int sd = client_socket[i];
				if(sd > 0) FD_SET(sd, &rfds);
				if(sd > max_sockets_allowed) max_sockets_allowed = sd;
			}
			int activity = select(max_sockets_allowed + 1, &rfds, NULL, NULL, NULL);
			if(activity < 0) {
				perror("select error");
				exit(1);
			}
			if(FD_ISSET(master_socket, &rfds)) {
				int new_socket = accept(master_socket, (struct sockaddr *)&client_addr, (socklen_t *)&client_addr);
				char *msg = "\nHello welcome to Chat Room. I hope you will have wonderful time here.\n"
							"options:\n"
							"0) NAME: <Enter you name> \n"
						    "1) HELP: <Get list of all options>\n"
							"2) SEND: <send message to specific member\n"
							"3) PUBLISH: <send message to everyone \n"
							"4) LIST: <list all users>  \n"
							"5) QUIT: <leave the chat room \n\n";
				if(send(new_socket, msg, strlen(msg), 0) != strlen(msg))  perror("Error in sending the message");
				for(int i=0; i<MAX_CLIENTS; i++) {
					if(client_socket[i] == 0) {
						client_socket[i] = new_socket;
						map<int, string> mp;
						mp[new_socket] = "NULL";
						clients_info.push_back(mp);
						printf("Adding %d to chat list\n", new_socket);
						break;
					}
				}
			}
			for(int i=0; i<MAX_CLIENTS; i++) {
				int sd = client_socket[i];
				if(FD_ISSET(sd, &rfds)) {
					char buff[MAXLEN];
					memset(buff, 0, strlen(buff));
					int nbytes = read(sd, buff, MAXLEN);
					buff[nbytes] = '\0';
					vector<string> result = split_message(buff);
					string header = result[0];
					string message = result[1];
					cout << "header:  " << header << " and message:  " << message << endl;
					if(header == "NAME") {
						char msg[MAXLEN];
						memset(msg, 0, strlen(msg));
						strcpy(msg, "Your name changed to ");
						for(int i=0; i<clients_info.size(); i++) {
							map<int, string> mp = clients_info[i];
							for(auto it=mp.begin(); it != mp.end(); it++) {
								if(it -> first == sd) {
									mp[sd] = message;
									break;
								}
							}
							clients_info[i] = mp;
						}
						message = message + "\n";
						strcat(msg, message.c_str());
						write(sd, msg, strlen(msg));
					}
					else if(header == "SEND") {
						string client_name = "", client_message = "", sender_name;
						int flag = 0;
						for(int i=0; i<message.length(); i++) {
							if(flag == 0) {
								if(message[i] != '#') client_name = client_name + message[i];
								else flag = 1;
							}
							else client_message = client_message + message[i];
						}
						int recv_socket;
						for(int i=0; i<clients_info.size(); i++) {
							map<int, string> mp = clients_info[i];
							for(auto it=mp.begin(); it != mp.end(); it++) {
								if(it -> second == client_name) {
									recv_socket = it -> first;
								}
								if(it -> first == sd) {
									sender_name = it -> second;
								}
							}
						}
						client_message = client_message + "\n";
						char msg[MAXLEN];
						memset(msg, 0, strlen(msg));
						strcpy(msg, "[");
						strcat(msg, sender_name.c_str());
						strcat(msg, "]:\t");
						strcat(msg, client_message.c_str());
						write(recv_socket, msg, strlen(msg));
					}
					else if(header == "PUBLISH") {
						string sender_name;
						message = message + "\n";
						vector<string> client_names;
					    vector<int>	client_sockets;
						for(int i=0; i<clients_info.size(); i++) {
							map<int, string> mp = clients_info[i];
							for(auto it = mp.begin(); it != mp.end(); it++) {
								if(it -> first != sd) {
									client_sockets.push_back(it->first);
									client_names.push_back(it->second);
								}
								else {
									sender_name = it -> second;
								}
							}
						}
						for(int i=0; i<client_names.size(); i++) {
							char msg[MAXLEN];
							memset(msg, 0, strlen(buff));
							strcpy(msg, "[");
							strcat(msg, sender_name.c_str());
							strcat(msg, "]:\t");
							strcat(msg, message.c_str());
							write(client_sockets[i], msg, strlen(msg));
						}
					}
					else if(header == "QUIT")  {
						int erase_index, is_found;
						for(int i=0; i<clients_info.size(); i++) {
							map<int, string> mp = clients_info[i];
							is_found = 0;
							for(auto it=mp.begin(); it != mp.end(); it++) {
								if(it -> first == sd) {
									erase_index = i;
									is_found = 1;
									break;
								}
							}
							if(is_found == 1) break;
						}
						if(is_found == 1) clients_info.erase(clients_info.begin() + erase_index);
						char *buff = "You have been removed from chat room\n";
						write(sd, buff, strlen(buff));
						FD_CLR(sd, &rfds);
					}
					else if(header == "LIST") {
						string client_names = "";
						for(int i=0; i<clients_info.size(); i++) {
							map<int, string> mp = clients_info[i];
							for(auto it = mp.begin(); it != mp.end(); it++) {
								if(it -> second != "NULL" && it -> first != sd) {
									stringstream convert;
									convert << it -> first;
									client_names = client_names + convert.str();
									client_names = client_names + "|";
									client_names = client_names + it -> second;
									client_names = client_names + "\n";
								}
							}
						}
						if(client_names.length() == 0) {
							char *msg = "Sorry there are no users\n";
							write(sd, msg, strlen(msg));
						}
						else {
							char msg[1000];
							memset(msg, 0, strlen(msg));
							string temp = "List of users:\n";
							strcat(msg, temp.c_str());
							string client_details = "#############################\n";
							client_details = client_details + client_names;
							client_details = client_details + "#############################\n";
							strcat(msg, client_details.c_str());
							write(sd, msg, strlen(msg));
						}
					}
					else {
						char *buff = "invalid command\n";
						write(sd, buff, strlen(buff));
					}
				}
			}
		}
		return 0;
}
