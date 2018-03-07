/*g++ main.cpp -o main `pkg-config --libs --cflags gtkmm-3.0`
*/

#include<gtkmm.h>
#include<iostream>
#include<string>
using namespace std;

class mainWindow:public Gtk::Window
{
public:
mainWindow()
	{
	set_title("Messenger");
	set_size_request(400,400);
	set_border_width(50);
	set_position(Gtk::WIN_POS_CENTER);
	/*add(m_Frame);
	m_Frame.set_label("Click on the logo below to Login");
	m_Frame.set_shadow_type(Gtk::SHADOW_ETCHED_OUT);
	*/
	image.set("client");
	m_button.set_image(image);
	//mainGrid.attach(image,5,0,2,1);
	m_button.signal_pressed().connect(sigc::mem_fun(*this,&mainWindow::on_button_pressed));
	//mainGrid.attach(m_button,2,1,1,1);	
	//mainGrid.show_all();
	//add(mainGrid);
	add(m_button);
	show_all_children();
}
virtual ~mainWindow(){}
protected:
//Gtk::Frame m_Frame;
Gtk::Image image;
Gtk::Button m_button;
//Gtk::Grid mainGrid;
virtual void on_button_pressed()
{
	//exit(1);
	Gtk::Widget::hide();
}
};

class Login:public Gtk::Window
{
public:
Login():grid(6,4,true),m_button("Login"),image("login"),user_Label("Username"),password_Label("Password")
{
	set_title("Login");
	set_size_request(400,400);
	set_border_width(10);
	set_position(Gtk::WIN_POS_CENTER);
	user_Entry.set_max_length(20);
	password_Entry.set_max_length(20);
	password_Entry.set_visibility(false);
	add(grid);
	grid.attach(image,1,3,0,1);
	grid.attach(user_Label,1,3,1,2);
	grid.attach(user_Entry,1,3,2,3);
	grid.attach(password_Label,1,3,3,4);
	grid.attach(password_Entry,1,3,4,5);
	grid.attach(m_button,3,4,5,6);
	m_button.signal_pressed().connect(sigc::mem_fun(*this,&Login::checkLogin));
	show_all_children();
}

string getUsername()
{
	return Username;
}

string getPassword()	
{
	return Password;
}
virtual ~Login(){}
private:
string Username,Password;
Gtk::Image image;
Gtk::Button m_button;
Gtk::Table grid;
Gtk::Label user_Label;
Gtk::Label password_Label;
Gtk::Entry user_Entry;
Gtk::Entry password_Entry;
virtual void checkLogin()
{
	Username=user_Entry.get_text();
	Password=password_Entry.get_text();
	Gtk::Widget::hide();
}
};

class Chat:public Gtk::Window
{
private:
string Name;
Gtk::Entry messageEntry;
Gtk::Table grid;
public:
Chat(string n):Name(n),grid(10,1,true)
{
	set_title("Group Chat");
	set_size_request(800,600);
	set_border_width(10);
	set_position(Gtk::WIN_POS_CENTER);
	messageEntry.set_max_length(50);
	add(grid);
	grid.attach(messageEntry,0,1,9,10);
	show_all_children();
}
virtual ~Chat()
{
}
};
int main(int argc,char *argv[])
{
	Gtk::Main kit(argc,argv);
	mainWindow window;
	Gtk::Main::run(window);
	Login login;
	Gtk::Main::run(login);
	Chat chat(login.getUsername());
	Gtk::Main::run(chat);
	return 0;
}
