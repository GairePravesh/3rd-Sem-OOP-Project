#include<gtkmm.h>
#include<iostream>
//#include<stdio.h> //printf
//#include<iostream>
#include<unistd.h>//close()
#include<string>    //strlen
#include<sys/socket.h>    //socket
#include<arpa/inet.h> //inet_addr
//#include<cstring>
//#include<thread>
using namespace std;
class myWindow;
class Client
{
private:
    int sock,bytes_recv;
    struct sockaddr_in server;
    char sendmesg[256];
    char readmesg[256];

    //char message[4096] , server_reply[4096],str[10000],str1[10000];
    //fd_set readfds;
public:
    Client()
    {
        //Create socket
    sock = socket(AF_INET , SOCK_STREAM , 0);
    if (sock == -1)
    {
        cout<<"Could not create socket";
    }
    cout<<"Socket created";

    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_family = AF_INET;
    server.sin_port = htons( 8888 );

    //Connect to remote server
    if (connect(sock , (struct sockaddr *)&server , sizeof(server)) < 0)
    {
        cout<<"connect failed. Error";

    }

    cout<<"Connected\n";

    //keep communicating with server

    }
    void sendMessage()
    {
        //message
        bytes_recv=send(sock, sendmesg, strlen(sendmesg), 0);
    }
    void readMessage()
    {
        recv(sock, readmesg, strlen(readmesg), 0);
        //read message continuously
    }
    ~Client()
    {
        close(sock);
    }



};

class myWindow:public Gtk::Window,public::Client
{
private:

    Gtk::TreeView *treeview;
    Gtk::Label *label;
    Gtk::Entry *text;
    Gtk::ScrolledWindow *scroll;
    std::string emessage;
    std::string Username;


public:
    myWindow()
    {
        //set_default_size(400,400);
        set_title("Messenger");
        set_position(Gtk::WIN_POS_CENTER);
        Gtk::Box *vbox=Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_VERTICAL,0));
        add(*vbox);
        Gtk::Grid *grid=Gtk::manage(new Gtk::Grid);
        vbox->add(*grid);
        grid->set_border_width(20);
        grid->set_row_spacing(10);
        Gtk::Image *image=Gtk::manage(new Gtk::Image);
        Gtk::Button *button=Gtk::manage(new Gtk::Button);
        image->set("client");
        button->set_label("Open");
        button->set_hexpand(true);
        grid->attach(*image,0,0,1,1);
        grid->attach(*button,0,1,1,1);
        button->signal_pressed().connect(sigc::mem_fun(*this,&myWindow::login));
        vbox->show_all();
    }
    void login()
    {
        //set_default_size(200,200);
        //set_position(Gtk::WIN_POS_CENTER);
        Glib::ListHandle<Widget*> childList = this->get_children();
        Glib::ListHandle<Widget*>::iterator it = childList.begin();
        while (it != childList.end())
        {
            Gtk::Container::remove(*(*it));
            it++;
        }
                set_title("Login");
        Gtk::Box *vbox=Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_VERTICAL,0));
        add(*vbox);
        Gtk::Grid *grid=Gtk::manage(new Gtk::Grid);
        grid->set_border_width(10);
        grid->set_row_spacing(10);
        vbox->add(*grid);
        Gtk::Label *lusername=Gtk::manage(new Gtk::Label("Username:"));
        grid->attach(*lusername,0,0,1,1);
        Gtk::Label *lpassword =Gtk::manage(new Gtk::Label("Password:"));
        grid->attach(*lpassword,0,1,1,1);
        Gtk::Entry *eusername=Gtk::manage(new Gtk::Entry());
        eusername->set_hexpand(true);
        grid->attach(*eusername,1,0,2,1);
        Gtk::Entry *epassword=Gtk::manage(new Gtk::Entry());
        epassword->set_hexpand(true);
        epassword->set_visibility(false);
        grid->attach(*epassword,1,1,2,1);
        Gtk::Button *blogin=Gtk::manage(new Gtk::Button("Login"));
        blogin->signal_clicked().connect(sigc::bind<Gtk::Entry*,Gtk::Entry*>(sigc::mem_fun(*this,&myWindow::on_login_click),eusername,epassword));
        grid->attach(*blogin,2,2,1,1);
        vbox->show_all();

    }


    void chat()
    {
        set_size_request(800,600);
        set_title("Messenger: Group Chat");
        set_position(Gtk::WIN_POS_CENTER);
        Gtk::Box *vbox=Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_VERTICAL,0));
        add(*vbox);
        Gtk::Grid *grid=Gtk::manage(new Gtk::Grid);
        grid->set_border_width(10);
        grid->set_row_spacing(10);
        vbox->add(*grid);
        Gtk::TreeView *treeview=Gtk::manage(new Gtk::TreeView);
        treeview->set_hexpand(true);
        treeview->set_vexpand(true);
        Gtk::ScrolledWindow *scroll=Gtk::manage(new Gtk::ScrolledWindow);

        scroll->set_policy(Gtk::POLICY_ALWAYS, Gtk::POLICY_ALWAYS);
        scroll->set_resize_mode(Gtk::ResizeMode::RESIZE_IMMEDIATE);
            //(treeview->get_vadjustment(),Gtk::ORIENTATION_VERTICAL);
        //scroll->set_focus_vadjustment();
        scroll->add(*treeview);
        grid->attach(*scroll,0,0,3,1);
        refTreeModel = Gtk::ListStore::create(columns);
        treeview->set_model(refTreeModel);
        treeview->append_column("Username", columns.col_name);
        treeview->append_column("Message", columns.col_text);
        //treeview->append_column("Online", columns.col_online);
        label = Gtk::manage(new Gtk::Label);
        label->set_markup("<b>Enter Message: </b>");
        grid->attach(*label, 0, 1, 1, 1);

        text = Gtk::manage(new Gtk::Entry);
        grid->attach(*text, 1, 1, 2, 1);

        Gtk::Button *button1 = Gtk::manage(new Gtk::Button("Send Message"));
        Gtk::Button *button2 = Gtk::manage(new Gtk::Button("Leave Group"));
        Gtk::Button *button3 = Gtk::manage(new Gtk::Button("Send File"));
        button1->signal_clicked().connect(sigc::mem_fun(*this, &myWindow::on_button1_click));
        button2->signal_clicked().connect(sigc::mem_fun(*this, &myWindow::on_button2_click));
        button3->signal_clicked().connect(sigc::mem_fun(*this, &myWindow::on_button3_click));
        grid->attach(*button1, 2, 2, 1, 1);
        grid->attach(*button2, 1, 2, 1, 1);
        grid->attach(*button3, 0, 2, 1, 1);

        vbox->show_all();
    }

virtual ~myWindow()
{

}
protected:
    void on_button3_click()
    {
        //treeview->
        //Gtk::TreeViewColumn::clear() ;
        //displayText(Username,Username+" sent a file.");
        readMessage();
        displayText(Username,emessage);


    }
    void on_button2_click()
    {
        //displayText("mitesh","hi hows there");
        //exit(1);
        displayText(Username,"Goodbye");
        hide();
    }

    void on_button1_click()
    {
        if(text->get_text_length() == 0)
            label->set_markup("<span color='red'>Enter Message: </span>");
        else
        {

            label->set_markup("<span color='black'>Enter Message: </span>");

            emessage=text->get_text();
            sendMessage(emessage);
            //displayText(Username,emessage);
            //Gtk::ListStore::clear();
        }
    }
    //friend void Client::sendMessage(std::string emessage)
    //{

    //}
    std::string onlineClients()
    {
        return "Pravesh\nMitesh\nAmit\nAlex";
    }
    void showClients()
    {
            text->set_text("");
            std::string people="Pravesh\nMitesh\nAmit\nAlex";
            Gtk::MessageDialog dlg(people,false,Gtk::MESSAGE_INFO,Gtk::BUTTONS_OK,true);
            dlg.set_title("Online");
            dlg.run();
    }
    void displayText(std::string User,std::string mesg)
    {
        if(mesg=="clear window")
            refTreeModel->clear();

        else if(mesg=="online clients")
        {
            showClients();
        }
        else
        {
            //
            Gtk::TreeModel::Row row = *(refTreeModel->append());
            row[columns.col_name] = User;
            if(mesg.size()>50)
                mesg=mesg.substr(0,50)+"\n"+mesg.substr(50);
            row[columns.col_text] = mesg;
            //row[columns.col_online]=onlineClients();
            text->set_text("");
        }

        //treeview->erase(row);
        //erase(treeview);
    }

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

    void on_login_click(Gtk::Entry *euname,Gtk::Entry *epword)

    {
        Username=euname->get_text();
        if(euname->get_text().compare("admin")==0 && epword->get_text().compare("password")==0)
        {
            Gtk::MessageDialog dlg("You are now logged in.",false,Gtk::MESSAGE_INFO,Gtk::BUTTONS_OK,true);
            dlg.set_title("Login Successful");
            dlg.run();
            Glib::ListHandle<Widget*> childList = this->get_children();
            Glib::ListHandle<Widget*>::iterator it = childList.begin();
            while (it != childList.end())
            {
                Gtk::Container::remove(*(*it));
                it++;
            }
            chat();
        }
        else
        {
            Gtk::MessageDialog dlg("Unknown username or password.", false, Gtk::MESSAGE_ERROR, Gtk::BUTTONS_OK, true);
            dlg.set_title("Login Failed");
            dlg.run();
        }
    }
};




int main(int argc,char *argv[])
{
    // check for terminal input values
    // work accordingly
    Client client(argc,argv);
    Glib::RefPtr<Gtk::Application>app =Gtk::Application::create(argc,argv);
    myWindow window;
    app->run(window);
    return 0;
}
