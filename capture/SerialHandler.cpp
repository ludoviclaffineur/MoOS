//
//  SerialHandler.cpp
//  LibLoAndCap
//
//  Created by Ludovic Laffineur on 21/03/14.
//  Copyright (c) 2014 Ludovic Laffineur. All rights reserved.
//

#include "SerialHandler.h"

using namespace boost;

SerialHandler::SerialHandler(Grid* g){
    mGrid = g;
}


char SerialHandler::readChar() {
        asio::io_service io;
        asio::serial_port port(io);

        port.open("COM3");
        port.set_option(asio::serial_port_base::baud_rate(115200));

        char c;

        // Read 1 character into c, this will block
        // forever if no character arrives.
        asio::read(port, asio::buffer(&c,1));
        std::cout<< c << " "<< std::endl;
        port.close();


	return c;
}


std::string SerialHandler::readResponse() {

	asio::io_service io;
	asio::serial_port port(io);

	port.open("COM3");
	port.set_option(asio::serial_port_base::baud_rate(115200));

	// A blocking reader for this port that
	// will time out a read after 500 milliseconds.
	//blocking_reader reader(port, 500);

	char c;

	std::string rsp;

	// read from the serial port until we get a
	// \n or until a read times-out (500ms)
	//while (reader.read_char(c) && c != '\n') {
		rsp += c;
	//}

	if (c != '\n') {
		// it must have timed out.
		//throw std::exception("Read timed out!");
	}
    
	return rsp;
}

