//
//  HttpClient.h
//  LibLoAndCap
//
//  Created by Ludovic Laffineur on 2/10/14.
//  Copyright (c) 2014 Ludovic Laffineur. All rights reserved.
//

#ifndef __LibLoAndCap__HttpClient__
#define __LibLoAndCap__HttpClient__

#include <iostream>
#include <istream>
#include <ostream>
#include <string>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <iostream>
#include <fstream>
#include <cstdio>
#include <iostream>

using boost::asio::ip::tcp;

typedef struct _JFIFHeader
{
    u_short SOI;          /* 00h  Start of Image Marker     */
    u_short APP0;         /* 02h  Application Use Marker    */
    u_short Length;       /* 04h  Length of APP0 Field      */
    u_char Identifier[5];   /* 06h  "JFIF" (zero terminated) Id String */
    u_char Version[2];      /* 07h  JFIF Format Revision      */
    u_char Units;           /* 09h  Units used for Resolution */
    u_short Xdensity;     /* 0Ah  Horizontal Resolution     */
    u_short Ydensity;     /* 0Ch  Vertical Resolution       */
    u_char XThumbnail;      /* 0Eh  Horizontal Pixel Count    */
    u_char YThumbnail;      /* 0Fh  Vertical Pixel Count      */
} JFIFHEAD;



class client
{
public:
    client(boost::asio::io_service& io_service,
           const std::string& server, const std::string& path, std::string fileName)
    :timer_(io_service,boost::posix_time::seconds(2))
    {
        mFileName.append(fileName.c_str());
        mTempName.append(mFileName).append("-temp");
        myfile.open(mTempName,std::ios::binary);
        timer_.async_wait(boost::bind(&client::close_connection, this));
        // Form the request. We specify the "Connection: close" header so that the
        // server will close the socket after transmitting the response. This will
        // allow us to treat all data up until the EOF as the content.
        //boost::asio::io_service io_service;

        // Get a list of endpoints corresponding to the server name.
        tcp::resolver resolver(io_service);
        tcp::resolver::query query(server, "http");
        tcp::resolver::iterator endpoint_iterator;
        tcp::socket socket(io_service);
        try{

            endpoint_iterator= resolver.resolve(query);

        // Try each endpoint until we successfully establish a connection.

        //try{
            boost::asio::connect(socket, endpoint_iterator);
        }
        catch (std::exception& e){
            
        }

        // Form the request. We specify the "Connection: close" header so that the
        // server will close the socket after transmitting the response. This will
        // allow us to treat all data up until the EOF as the content.
        boost::asio::streambuf request;
        std::ostream request_stream(&request);
        request_stream << "GET " << path << " HTTP/1.0\r\n";
        request_stream << "Host: " << server << "\r\n";
        request_stream << "Accept: */*\r\n";
        request_stream << "Connection: close\r\n\r\n";

        // Send the request.
        boost::asio::write(socket, request);

        // Read the response status line. The response streambuf will automatically
        // grow to accommodate the entire line. The growth may be limited by passing
        // a maximum size to the streambuf constructor.
        boost::asio::streambuf response;
        boost::asio::read_until(socket, response, "\r\n");

        // Check that response is OK.
        std::istream response_stream(&response);
        std::string http_version;
        response_stream >> http_version;
        unsigned int status_code;
        response_stream >> status_code;
        std::string status_message;
        std::getline(response_stream, status_message);
        if (!response_stream || http_version.substr(0, 5) != "HTTP/")
        {
            std::cout << "Invalid response\n";
            //return 1;
        }
        if (status_code != 200)
        {
            std::cout << "Response returned with status code " << status_code << "\n";
            //return 1;
        }

        // Read the response headers, which are terminated by a blank line.
        boost::asio::read_until(socket, response, "\r\n\r\n");

        // Process the response headers.
        std::string header;
        while (std::getline(response_stream, header) && header != "\r");
            //std::cout << header << "\n";
        //std::cout << "\n";

        // Write whatever content we already have to output.
        if (response.size() > 0){
            //std::cout << &response;
            myfile<< &response;
        }


        // Read until EOF, writing data to output as we go.
        boost::system::error_code error;
        while (boost::asio::read(socket, response,
                                 boost::asio::transfer_at_least(1), error)){
            //std::cout << &response;
            myfile<< &response;

        }


        if (error == boost::asio::error::eof){
            //std::cout << "\n \n EOF " <<std::endl;
            isDowloaded = true;

            //std::cout<< myfile.tellp() << std::endl;

            if(myfile.tellp() < 20000){
                myfile.close();
                std::remove(mTempName.c_str());
            }
            else{
                myfile.close();
                std::ifstream f(mFileName.c_str());
                if (f.good()) {
                    f.close();
                    std::remove(mFileName.c_str());
                    std::rename(mTempName.c_str(),mFileName.c_str());
                } else {
                    f.close();
                    std::rename(mTempName.c_str(),mFileName.c_str());
                }

            }

            
            
            
        }
        else if (error != boost::asio::error::eof)
            myfile.close();



        





//        isDowloaded = false;
//        std::ostream request_stream(&request_);
//        request_stream << "GET " << path << " HTTP/1.0\r\n";
//        request_stream << "Host: " << server << "\r\n";
//        request_stream << "Accept: */*\r\n";
//        request_stream << "Connection: close\r\n\r\n";
//        std::cout<<"New Client created" <<std::endl;
//
//        std::strcpy(mFileName, fileName.c_str());
//        myfile.open(fileName,std::ios::binary);
//
//        // Start an asynchronous resolve to translate the server and service names
//        // into a list of endpoints.
//        tcp::resolver::query query(server, "http");
//        //sleep(1);
//        std::cout<<"Addressssss " << server << path  <<std::endl;
//        resolver_.async_resolve(query,
//                                boost::bind(&client::handle_resolve, this,
//                                            boost::asio::placeholders::error,
//                                            boost::asio::placeholders::iterator));
    }
    void close_connection(){
        myfile.close();
        std::remove(mFileName.c_str());
    }

    boost::asio::deadline_timer timer_;
    std::ofstream myfile;
    std::string mFileName, mTempName;
    bool isDowloaded;
};



#endif /* defined(__LibLoAndCap__HttpClient__) */
