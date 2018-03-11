#include<iostream>
#include<string>
#include<cstring>
#include<map>
#include<vector>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include<cstdlib>
#define PORT "8080"   // port we're listening on
using namespace std;

class Server
{
private:
	fd_set master;    // master file descriptor list
    fd_set read_fds;  // temp file descriptor list for select()
    int fdmax;        // maximum file descriptor number

    int listener;     // listening socket descriptor
    int newfd;        // newly accept()ed socket descriptor
    struct sockaddr_storage remoteaddr; // client address
    socklen_t addrlen;

    char buf[256];    // buffer for client data
    int nbytes;

    char remoteIP[INET6_ADDRSTRLEN];

    int yes=1;        // for setsockopt() SO_REUSEADDR, below
    int i, j, rv;

	int client_socket[10];

    struct addrinfo hints, *ai, *p;

    vector<map<int,string> > clients_info;



public:
// sockaddr, IPv4 or IPv6:
void *get_in_addr(struct sockaddr *sa)
{
    if (sa->sa_family == AF_INET) {
        return &(((struct sockaddr_in*)sa)->sin_addr);
    }

    return &(((struct sockaddr_in6*)sa)->sin6_addr);
}
void createSocket()
{
	 for(p = ai; p != NULL; p = p->ai_next) {
        listener = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
        if (listener < 0) {
            continue;
        }

        // lose the pesky "address already in use" error message
        setsockopt(listener, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));

        if (bind(listener, p->ai_addr, p->ai_addrlen) < 0) {
            close(listener);
            continue;
        }

        break;
    }
    // if we got here, it means we didn't get bound
    if (p == NULL) {
        cout<<"failed to bind"<<endl;
        exit(2);
    }

    freeaddrinfo(ai); // all done with this

}
void listenSocket()
{
	 // listen
    if (listen(listener, 10) == -1) {
        cout<<"failed to listen"<<endl;
        exit(3);
    }

    // add the listener to the master set
    FD_SET(listener, &master);

    // keep track of the biggest file descriptor
    fdmax = listener; // so far, it's this one
}
void initSocket()
{
	FD_ZERO(&master);    // clear the master and temp sets
    FD_ZERO(&read_fds);
	// get us a socket and bind it
    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;
    if ((rv = getaddrinfo(NULL, PORT, &hints, &ai)) != 0) {
        cout<<"getaddrinfo error"<<endl;
        exit(1);
    }


}



void runServer()
{
	read_fds = master; // copy it
        if (select(fdmax+1, &read_fds, NULL, NULL, NULL) == -1) {
            cout<<"error on select"<<endl;
            exit(4);
        }

        // run through the existing connections looking for data to read
        for(i = 0; i <= fdmax; i++) {
            if (FD_ISSET(i, &read_fds)) { // we got one!!
                if (i == listener) {
                    // handle new connections
                    addrlen = sizeof remoteaddr;
                    newfd = accept(listener,
                        (struct sockaddr *)&remoteaddr,
                        &addrlen);
                        
                        
						for(int itr=0; itr<fdmax; itr++) {
					if(client_socket[itr] == 0) {
						client_socket[itr] = newfd;
						map<int, string> mp;
						mp[newfd] = "NULL";
						clients_info.push_back(mp);

						break;
					}
				}


                    if (newfd == -1) {
                       	cout<<"error on accept"<<endl;
                    } else {
                        FD_SET(newfd, &master); // add to master set
                        if (newfd > fdmax) {    // keep track of the max
                            fdmax = newfd;
                        }
                        cout<<"selectserver: new connection from "<<inet_ntop(remoteaddr.ss_family,
                                get_in_addr((struct sockaddr*)&remoteaddr),
                                remoteIP, INET6_ADDRSTRLEN)<<" on socket "<<newfd<<"\n";

                    }
                } else {
                    // handle data from a client
                    if ((nbytes = recv(i, buf, sizeof buf, 0)) <= 0) {
                        // got error or connection closed by client
                        if (nbytes == 0) {
                            // connection closed

                            cout<<"selectserver: socket "<<i<<" hung up\n"<<endl;
                            int erase_index, is_found;
						for(int iter=0; iter<clients_info.size(); iter++) {
							map<int, string> mp = clients_info[iter];
							is_found = 0;
							for(auto it=mp.begin(); it != mp.end(); it++) {
								if(it -> first == i) {
									erase_index = iter;
									is_found = 1;
									break;
								}
							}
							if(is_found == 1) break;
						}
						if(is_found == 1) clients_info.erase(clients_info.begin() + erase_index);

                        } else {
                           cout<<"error on recv"<<endl;
                        }
                        close(i); // bye!
                        FD_CLR(i, &master); // remove from master set
                    } else {
                        // we got some data from a client
                        int pos=string(buf).find(":");

						for(int iter=0; iter<clients_info.size(); iter++) {
							map<int, string> mp = clients_info[iter];
							for(auto it=mp.begin(); it != mp.end(); it++) {
								if(it -> first == i && it->second!="online clients") {
									mp[i] = string(buf).substr(0,pos);
									break;
								}
							}
							clients_info[iter] = mp;
						}
						if(string(buf).find("online clients")!=string::npos)
						{
							string client_names;
							for(int itr=0; itr<clients_info.size(); itr++) {
							map<int, string> mp = clients_info[itr];
							for(auto it = mp.begin(); it != mp.end(); it++) {
								if(it -> second != "NULL"&& it -> first != i) {
									client_names = client_names + it -> second +"\n";

								}
							}
						}

							//strcpy(buf,client_names.c_str());
							if (send(i, client_names.c_str(), nbytes, 0) == -1) {
		                                    cout<<"erro on send"<<endl;
		                                }

						}else{

		                    for(j = 0; j <= fdmax; j++) {
		                        // send to everyone!

		                        if (FD_ISSET(j, &master)) {
		                            // except the listener and ourselves
		                            if (j != listener && j != i) {
		                                if (send(j, buf, nbytes, 0) == -1) {
		                                    cout<<"erro on send"<<endl;
		                                }
		                            }
		                        }
		                    }}

                    }
                } // END handle data from client
            } // END got new incoming connection
        } // END looping through file descriptors
    } // END for(;;)--and you thought it would never end!

};
