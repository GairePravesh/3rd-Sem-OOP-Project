#include "Client.hpp"

int main(int argc,char *argv[])
{

    Glib::RefPtr<Gtk::Application>app =Gtk::Application::create(argc,argv);
    Client c;
    c.createClientSocket();
    app->run(c);
    return 0;

}
