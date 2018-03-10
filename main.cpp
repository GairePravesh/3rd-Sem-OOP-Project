#include<gtkmm.h>
/**
    C++ client example using sockets
*/
#include<iostream>    //cout
#include<stdio.h> //printf
#include<string.h>    //strlen
#include<string>  //string
#include<sys/socket.h>    //socket
#include<arpa/inet.h> //inet_addr
#include<netdb.h> //hostent
#include<unistd.h>

//#include <stdio.h>
#include <stdlib.h>
//#include <unistd.h>
#include <errno.h>
//#include <string.h>
//#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
//#include <sys/socket.h>

//#include <arpa/inet.h>

using namespace std;

class myWindow:public Gtk::Window
{
private:

    Gtk::TreeView *treeview;
    Gtk::Label *label;
    Gtk::Entry *text;
    Gtk::ScrolledWindow *scroll;
    std::string emessage;
    std::string Username;
    std::string recevmesg;

private:
    int sockfd, numbytes;
    char buf[256];
    struct addrinfo hints, *servinfo, *p;
    int rv;
    char s[INET6_ADDRSTRLEN];

public:
  void  createClient()
{

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    if ((rv = getaddrinfo("127.0.0.1","8888", &hints, &servinfo)) != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
        exit(1);
    }

    // loop through all the results and connect to the first we can
    for(p = servinfo; p != NULL; p = p->ai_next) {
        if ((sockfd = socket(p->ai_family, p->ai_socktype,
                p->ai_protocol)) == -1) {
            perror("client: socket");
            continue;
        }

        if (connect(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
           // close(sockfd);
            perror("client: connect erro");
            exit(1);
        }

        break;
    }

    if (p == NULL) {
        fprintf(stderr, "client: failed to connect\n");
        exit(1);
    }

    inet_ntop(p->ai_family, get_in_addr((struct sockaddr *)p->ai_addr),
            s, sizeof s);
    printf("client: connecting to %s\n", s);

    freeaddrinfo(servinfo); // all done with this structure

}
void  *get_in_addr(struct sockaddr *sa)
{
    if (sa->sa_family == AF_INET) {
        return &(((struct sockaddr_in*)sa)->sin_addr);
    }

    return &(((struct sockaddr_in6*)sa)->sin6_addr);
}
void sendMessage(const char *buffer)
    {
    //buffer=sm.c_str();
    if ((numbytes = send(sockfd, buffer, 255, 0)) == -1) {
        perror("recv");
        exit(1);
    }

    //buffer[numbytes] = '\0';

    printf("client: sent '%s'\n",buffer);
}

bool receiveMessage()
{
    while(recv(sockfd, buf, 255, MSG_DONTWAIT) >0){
    //exit(1);

    displayText("seerver sent:",string(buf));
    }
    return true;

}
public:
    myWindow()
    {

        //set_size_request(200,200);
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
        image->set("clients");
        button->set_label("Open");
        button->set_hexpand(true);
        grid->attach(*image,0,0,1,1);
        grid->attach(*button,0,1,1,1);
        button->signal_pressed().connect(sigc::mem_fun(*this,&myWindow::login));
        vbox->show_all();
    }
    void login()
    {
        //set_size_request(200,200);
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
        //set_size_request(800,600);
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
        //Gtk::add_events(Gtk::KEY_MASK);
        //signal_key_press_event().connect(sigc::mem_fun(*this, &myWindow::receiveMessage));
        Gtk::Button *button1 = Gtk::manage(new Gtk::Button("Send Message"));
        Gtk::Button *button2 = Gtk::manage(new Gtk::Button("Leave Group"));
        Gtk::Button *button3 = Gtk::manage(new Gtk::Button("Send File"));
        button1->signal_clicked().connect(sigc::mem_fun(*this, &myWindow::on_button1_click));
        button2->signal_clicked().connect(sigc::mem_fun(*this, &myWindow::on_button2_click));
        button3->signal_clicked().connect(sigc::mem_fun(*this, &myWindow::on_button3_click));
        Glib::signal_timeout().connect( sigc::mem_fun(*this, &myWindow::receiveMessage),50 );

        grid->attach(*button1, 2, 2, 1, 1);
        grid->attach(*button2, 1, 2, 1, 1);
        grid->attach(*button3, 0, 2, 1, 1);
        vbox->show_all();
     //  Glib::signal_idle().connect( sigc::mem_fun(*this, &myWindow::receiveMessage) );

       // Glib::signal_timeout().connect((sigc::mem_fun(*this,)))
                //guint g_timeout_add(10,receiveMessage,NULL);
        //receiveMessage();

    }


virtual ~myWindow()
{

}
protected:

    void on_button3_click()
    {
        //treeview->
        //Gtk::TreeViewColumn::clear() ;
      // displayText(Username," sent a file.");



    }
    void on_button2_click()
    {
        //displayText("mitesh","hi hows there");
        //exit(1);
       // displayText(Username,"Goodbye");
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
            //sendMessage(emessage);
            //displayText(Username,emessage);
            //Gtk::ListStore::clear();
            text->set_text("");
           sendMessage(emessage.c_str());
           displayText("client msg:",emessage);
            receiveMessage();


        }
    }

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
    void displayText(std::string User,string mesg)
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
            //if(mesg.size()>50)
              //  mesg=mesg.substr(0,50)+"\n"+mesg.substr(50);
            row[columns.col_text] = mesg;
            //row[columns.col_online]=onlineClients();

        }

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
            //gtk_window_set_modal(dlg,true);
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

   // Client client;
    //client.createClient();
   // client.sendMessage("gello");
        Glib::RefPtr<Gtk::Application>app =Gtk::Application::create(argc,argv);
        myWindow window;
        window.createClient();
        app->run(window);


    return 0;
}
