###########################################################################################################################################
                                                          <b>Locenger</b>\n
                                                    A Local Area Network Messaging App 
###########################################################################################################################################

Language Used\n
* C++\n
Tech used\n
* Gtkmm3.0 for GUI impmlementation and TCP Socket for communication over network\n

By-\n
Alex Bhattrai\n
Prashant Bhatta\n
Pravesh Gaire\n
Sishir Panta\n


###########################################################################################################################################
                                                   A minor project for 3rd Sem OOP project \n
###########################################################################################################################################

Feautres\n
* Multi Client Handling Server using select()\n
* Read / Write at same time using timers and non-blocking mode\n
* File transfer ( Under Development ) \n
* Group Chat\n
* Online Clients information\n
* User friendly GUI \n
* Login System ( Enter username, default password is password ) \n

Some features are underdevlopment due to lack of time and other subject pressures! \n
Gtk used over to Qt as Qt was not permitted to use\n


########################################################################################################################################
Usage:\n
* set the ip address and port in the server.hpp and client.cpp as per requirements\n
* build and run server.cpp on terminal \n
* build main.cpp on other terminal\n
* open the exe file as much as you can and enjoy chatting. (10 max Clients)\n

for server:\n
 g++ server.cpp -o server\n
 ./server\n
 
 for client\n
 g++ main.cpp Client.cpp -o main `pkg-config --cflags --libs gtkmm-3.0`\n
 ./main\n

########################################################################################################################################
Note:\n
The project might be stopped within this, was developed as class project\n
Real implementation and further features will be added in new App using Qt\n 
So follow for more \n

