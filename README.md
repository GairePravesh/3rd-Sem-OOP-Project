###########################################################################################################################################
                                                          <b>Locenger</b>
                                                    A Local Area Network Messaging App 
###########################################################################################################################################

Language Used
* C++
Tech used
* Gtkmm3.0 for GUI impmlementation and TCP Socket for communication over network

By-
Alex Bhattrai
Prashant Bhatta
Pravesh Gaire
Sishir Panta


###########################################################################################################################################
                                                   A minor project for 3rd Sem OOP project 
###########################################################################################################################################

Feautres
* Multi Client Handling Server using select()
* Read / Write at same time using timers and non-blocking mode
* File transfer ( Under Development ) 
* Group Chat
* Online Clients information
* User friendly GUI 
* Login System ( Enter username, default password is password ) 

Some features are underdevlopment due to lack of time and other subject pressures! 
Gtk used over to Qt as Qt was not permitted to use


########################################################################################################################################
Usage:
* set the ip address and port in the server.hpp and client.cpp as per requirements
* build and run server.cpp on terminal 
* build main.cpp on other terminal
* open the exe file as much as you can and enjoy chatting. (10 max Clients)

for server:
 g++ server.cpp -o server
 ./server
 
 for client
 g++ main.cpp Client.cpp -o main `pkg-config --cflags --libs gtkmm-3.0`
 ./main

########################################################################################################################################
Note:
The project might be stopped within this, was developed as class project
Real implementation and further features will be added in new App using Qt 
So follow for more 

