#include"Client.hpp"
Client::Client()
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
    button->signal_pressed().connect(sigc::mem_fun(*this,&Client::login));
    vbox->show_all();
}

void  Client::createClientSocket()
  {
    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

	/*if ((rv = getaddrinfo(argv[1],argv[2], &hints, &servinfo)) != 0)
    {
        cout<<"Error on getaddrinffo";
        //exit(1);
    }
    else */
    try
    {
        if((rv = getaddrinfo("127.0.0.1","8888", &hints, &servinfo)) != 0)
        {
            throw(-1);
            //cout<<"Error on getaddrinffo";
            //exit(1);
        }
    }catch(int i)
    {
        cout<<"erro on getaddrifno"<<endl;
        exit(1);
    }


    // loop through all the results and connect to the first we can
    for(p = servinfo; p != NULL; p = p->ai_next) {
        try
        {
            if ((sockfd = socket(p->ai_family, p->ai_socktype,
                p->ai_protocol)) == -1)
            {
                throw(-1);
                continue;
            }

        }
        catch(int i)
    {
        cout<<"exception error caught on connecting to socket!"<<endl;
        exit(1);
    }

        try
        {
            if (connect(sockfd, p->ai_addr, p->ai_addrlen) == -1)
            {
               // close(sockfd);
                throw(-1);
            }
        }
	catch(int i)
    {
        cout<<"exception error caught on connecting to socket!"<<endl;
        exit(1);
    }

        break;
    }
    

    if (p == NULL) {
        cout<<"client failed to connect";
        exit(1);
    }

    inet_ntop(p->ai_family, get_in_addr((struct sockaddr *)p->ai_addr),
            s, sizeof s);
    cout<<"client: connecting to\n"<<s;

    freeaddrinfo(servinfo); // all done with this structure

}

void *Client::get_in_addr(struct sockaddr *sa)
{
    if (sa->sa_family == AF_INET) {
        return &(((struct sockaddr_in*)sa)->sin_addr);
    }

    return &(((struct sockaddr_in6*)sa)->sin6_addr);
}


void Client::login()
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
  	/*gtk_signal_connect (GTK_OBJECT(*eusername), "activate",
                      GTK_SIGNAL_FUNC(on_login_click),
                      NULL);*/
    //signal_clicked().
    Gtk::Button *blogin=Gtk::manage(new Gtk::Button("Login"));
    blogin->signal_clicked().connect(sigc::bind<Gtk::Entry*,Gtk::Entry*>(sigc::mem_fun(*this,&Client::on_login_click),eusername,epassword));
    grid->attach(*blogin,2,2,1,1);
    vbox->show_all();

    }

void Client::chat()
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
    text->signal_activate().connect(sigc::mem_fun(*this, &Client::on_button1_click));

    //Gtk::add_events(Gtk::KEY_MASK);
    //signal_key_press_event().connect(sigc::mem_fun(*this, &myWindow::receiveMessage));
    Gtk::Button *button1 = Gtk::manage(new Gtk::Button("Send Message"));
    Gtk::Button *button2 = Gtk::manage(new Gtk::Button("Leave Group"));
    Gtk::Button *button3 = Gtk::manage(new Gtk::Button("Send File"));
    Gtk::Button *button4 = Gtk::manage(new Gtk::Button("Clear Window"));
    Gtk::Button *button5 = Gtk::manage(new Gtk::Button("Online CLients"));
    button1->signal_clicked().connect(sigc::mem_fun(*this, &Client::on_button1_click));
    button2->signal_clicked().connect(sigc::mem_fun(*this, &Client::on_button2_click));
    button3->signal_clicked().connect(sigc::mem_fun(*this, &Client::on_button3_click));
    button4->signal_clicked().connect(sigc::mem_fun(*this, &Client::on_button4_click));
    button5->signal_clicked().connect(sigc::mem_fun(*this, &Client::showClients));
    Glib::signal_timeout().connect( sigc::mem_fun(*this, &Client::receiveMessage),100 );

    grid->attach(*button1, 2, 2, 1, 1);
    grid->attach(*button5, 1, 2, 1, 1);
    grid->attach(*button3, 0, 2, 1, 1);
    grid->attach(*button2, 1, 3, 1, 1);
    grid->attach(*button4, 2, 3, 1, 1);
    vbox->show_all();
 //  Glib::signal_idle().connect( sigc::mem_fun(*this, &myWindow::receiveMessage) );

   // Glib::signal_timeout().connect((sigc::mem_fun(*this,)))
            //guint g_timeout_add(10,receiveMessage,NULL);
    //receiveMessage();

}

void Client::sendMessage(const char *buffer)
    {
    //buffer=sm.c_str();
    if ((numbytes = send(sockfd, buffer, 255, 0)) == -1) {
        cout<<"recv";
        exit(1);
    }

    //buffer[numbytes] = '\0';

    printf("client: sent '%s'\n",buffer);
}


bool Client::receiveMessage()
{
    while(recv(sockfd, buf, 255, MSG_DONTWAIT) >0){
    //exit(1);
    int pos=string(buf).find(":");
    //cout<<buf<<endl;

    displayText(string(buf).substr(0,pos),string(buf).substr(pos+1));
    }
    return true;

}

void Client::on_login_click(Gtk::Entry *euname,Gtk::Entry *epword)
{
    Username=euname->get_text();
    if(epword->get_text().compare("password")==0)
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
        Gtk::MessageDialog dlg("Unknown password.", false, Gtk::MESSAGE_ERROR, Gtk::BUTTONS_OK, true);
        dlg.set_title("Login Failed");
        dlg.run();
    }
}


void Client::on_button4_click()
{
    refTreeModel->clear();

}

void Client::on_button3_click()
{
    //treeview->
    //Gtk::TreeViewColumn::clear() ;
  // displayText(Username," sent a file.");


}

void Client::on_button2_click()
{
    //displayText("mitesh","hi hows there");
    //exit(1);
    sendMessage((Username+":"+"Goodbye").c_str());
    displayText("me","Goodbye");
    hide();
}

void Client::on_button1_click()
{
    if(text->get_text_length() == 0)
        label->set_markup("<span color='red'>Enter Message: </span>");
    else
    {

        label->set_markup("<span color='black'>Enter Message: </span>");

        emessage=text->get_text();
        emessage=Username+":"+emessage;
        //sendMessage(emessage);
        //displayText(Username,emessage);
        //Gtk::ListStore::clear();

       sendMessage(emessage.c_str());
       displayText("Me",text->get_text());
       text->set_text("");
        //receiveMessage();


    }
}

std::string Client::onlineClients()
{
    sendMessage((Username+":"+"online clients").c_str());
    recv(sockfd, buf, 255, 0);

    	return string(buf);
}

void Client::showClients()
{
        Gtk::MessageDialog dlg(onlineClients(),false,Gtk::MESSAGE_INFO,Gtk::BUTTONS_OK,true);
        dlg.set_title("Online");
        dlg.run();
}

void Client::displayText(std::string User,string mesg)
{
    Gtk::TreeModel::Row row = *(refTreeModel->append());
    row[columns.col_name] = User;
    //if(mesg.size()>50)
      //  mesg=mesg.substr(0,50)+"\n"+mesg.substr(50);
    row[columns.col_text] = mesg;
    //row[columns.col_online]=onlineClients();

}


