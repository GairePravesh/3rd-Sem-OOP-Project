#ifndef HEADER_H
#define HEADER_H
/**
    Author: Pravesh Gaire
    Class client contains the methods used for graphics implemented using gtkmm-3.0 and socket implemented in linux
    Works on Ubuntu provided that gtkmm is installed
*/
#include<gtkmm.h>
#include<iostream>    //cout
#include<string>  //string
#include<sys/socket.h>    //socket
#include<arpa/inet.h> //inet_addr
#include<netdb.h> //hostent
#include<unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <netinet/in.h>
//#include"client.cpp"
using namespace std;

class Client:public Gtk::Window
{

private:

    Gtk::TreeView *treeview;
    Gtk::Label *label;
    Gtk::Entry *text;
    Gtk::ScrolledWindow *scroll;
    std::string emessage;
    std::string Username;

    int sockfd, numbytes;
    char buf[256];
    struct addrinfo hints, *servinfo, *p;
    int rv;
    char s[INET6_ADDRSTRLEN];

public:
	Client();

	bool receiveMessage();

	void  createClientSocket();
    void  *get_in_addr(struct sockaddr *);
	void sendMessage(const char *);
	void login();
	void chat();
	void on_button4_click();
	void on_button3_click();
	void on_button2_click();
	void on_button1_click();
	void showClients();
	void displayText(std::string ,string );
	void on_login_click(Gtk::Entry *,Gtk::Entry *);

	std::string onlineClients();

	class ModelColumns:public Gtk::TreeModel::ColumnRecord
    {
    public:
        ModelColumns()
        {
        add(col_name);add(col_text);add(col_online);
        }
        Gtk::TreeModelColumn<Glib::ustring>col_name;
        Gtk::TreeModelColumn<Glib::ustring>col_text;
        Gtk::TreeModelColumn<Glib::ustring>col_online;
    };
    ModelColumns columns;
    Glib::RefPtr<Gtk::ListStore>refTreeModel;

	virtual ~Client(){}
};
#endif // HEADER_H
