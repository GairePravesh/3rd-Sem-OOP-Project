#include<gtkmm.h>
#include<iostream>
class myWindow:public Gtk::Window{
private:

public:
myWindow()
{
	Gtk::Box *vbox=Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_VERTICAL,0));
    add(*vbox);
	Gtk::Grid *grid=Gtk::manage(new Gtk::Grid);
	vbox->add(*grid);
	grid->set_border_width(20);
    grid->set_row_spacing(10);
	Gtk::Image *image=Gtk::manage(new Gtk::Image);
	Gtk::Button *button=Gtk::manage(new Gtk::Button);
    set_default_size(100,100);
    set_title("Messenger");
    set_position(Gtk::WIN_POS_CENTER);
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

	Glib::ListHandle<Widget*> childList = this->get_children();
    Glib::ListHandle<Widget*>::iterator it = childList.begin();
    while (it != childList.end())
    {
        Gtk::Container::remove(*(*it));
        it++;
    }
	Gtk::Box *vbox=Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_VERTICAL,0));
    add(*vbox);
    Gtk::Grid *grid=Gtk::manage(new Gtk::Grid);
    grid->set_border_width(10);
    grid->set_row_spacing(5);
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
void on_exit_clicked()
{
exit(1);
}
virtual ~myWindow()
{

}
protected:
void on_login_click(Gtk::Entry *euname,Gtk::Entry *epword)
{
    if(euname->get_text().compare("admin")==0 && epword->get_text().compare("password")==0)
    {
    Gtk::MessageDialog dlg("You are now logged in.",false,Gtk::MESSAGE_INFO,Gtk::BUTTONS_OK,true);
    dlg.set_title("Login Successful");
    dlg.run();
    hide();
    }
    else
    {
        Gtk::MessageDialog dlg("Unknown username or password.", false, Gtk::MESSAGE_ERROR, Gtk::BUTTONS_OK, true);
        dlg.set_title("Login Failed");
        dlg.run();
    }
}



};


class Chat :public Gtk::Window
{
public:
Chat()
{
    set_default_size(500,500);
    set_title("Messenger: Group Chat");
    set_position(Gtk::WIN_POS_CENTER);
    Gtk::Box *vbox=Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_VERTICAL,0));
    add(*vbox);
    Gtk::Grid *grid=Gtk::manage(new Gtk::Grid);
    grid->set_border_width(10);
    grid->set_row_spacing(5);
    vbox->add(*grid);
    Gtk::TreeView *treeview=Gtk::manage(new Gtk::TreeView);
    treeview->set_hexpand(true);
    treeview->set_vexpand(true);
    Gtk::ScrolledWindow *scroll=Gtk::manage(new Gtk::ScrolledWindow);
    scroll->set_policy(Gtk::POLICY_NEVER, Gtk::POLICY_ALWAYS);
    scroll->set_resize_mode(Gtk::ResizeMode::RESIZE_IMMEDIATE);
    scroll->add(*treeview);
    grid->attach(*scroll,0,0,3,1);
    refTreeModel = Gtk::ListStore::create(columns);
    treeview->set_model(refTreeModel);
    treeview->append_column("Username", columns.col_name);
    treeview->append_column("Message", columns.col_text);

    label = Gtk::manage(new Gtk::Label);
    label->set_markup("<b>Enter Message: </b>");
    grid->attach(*label, 0, 1, 1, 1);

    text = Gtk::manage(new Gtk::Entry);
    grid->attach(*text, 1, 1, 2, 1);

    Gtk::Button *button = Gtk::manage(new Gtk::Button("Send"));
    button->signal_clicked().connect(sigc::mem_fun(*this, &Chat::on_button_click));
    grid->attach(*button, 2, 2, 1, 1);

    vbox->show_all();
}
virtual ~Chat()
{}
Gtk::TreeView *treeview;
Gtk::Label *label;
Gtk::Entry *text;
Gtk::ScrolledWindow *scroll;
std::string emessage;
int row=0;
protected:
void on_quit_click()
{
    hide();
}
void on_button_click()
{
    if(text->get_text_length() == 0)
        label->set_markup("<span color='red'>Enter Message: </span>");
    else
    {
    	row++;
        label->set_markup("<span color='black'>Enter Message: </span>");
        Gtk::TreeModel::Row row = *(refTreeModel->append());
        row[columns.col_name] = "Pravesh";
        emessage=text->get_text();
        if(emessage.size()>50)
            emessage=emessage.substr(0,50)+"\n"+emessage.substr(50);
        row[columns.col_text] = emessage;
        text->set_text("");
        //Gtk::ListStore::clear();
    }
}
class ModelColumns:public Gtk::TreeModel::ColumnRecord
{
public:
    ModelColumns()
    {
    add(col_name);add(col_text);
    }
    Gtk::TreeModelColumn<Glib::ustring>col_name;
    Gtk::TreeModelColumn<Glib::ustring>col_text;
    };
    ModelColumns columns;
    Glib::RefPtr<Gtk::ListStore>refTreeModel;
private:
};

int main(int argc,char *argv[])
{
    Glib::RefPtr<Gtk::Application>win1 =Gtk::Application::create(argc,argv);
    myWindow window;
    win1->run(window);

    Glib::RefPtr<Gtk::Application>win2 =Gtk::Application::create(argc,argv);
    Chat chat;
    win2->run(chat);

    return 0;
}
