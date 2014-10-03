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
    : resolver_(io_service),
    socket_(io_service)
    {
        // Form the request. We specify the "Connection: close" header so that the
        // server will close the socket after transmitting the response. This will
        // allow us to treat all data up until the EOF as the content.

        std::ostream request_stream(&request_);
        request_stream << "GET " << path << " HTTP/1.0\r\n";
        request_stream << "Host: " << server << "\r\n";
        request_stream << "Accept: */*\r\n";
        request_stream << "Connection: close\r\n\r\n";
        std::cout<<"New Client created" <<std::endl;

        std::strcpy(mFileName, fileName.c_str());
        myfile.open(fileName,std::ios::binary);

        // Start an asynchronous resolve to translate the server and service names
        // into a list of endpoints.
        tcp::resolver::query query(server, "http");
        //sleep(1);
        std::cout<<"Addressssss " << server << path  <<std::endl;
        resolver_.async_resolve(query,
                                boost::bind(&client::handle_resolve, this,
                                            boost::asio::placeholders::error,
                                            boost::asio::placeholders::iterator));
    }

private:
    void handle_resolve(const boost::system::error_code& err,
                        tcp::resolver::iterator endpoint_iterator)
    {
        if (!err)
        {
            // Attempt a connection to the first endpoint in the list. Each endpoint
            // will be tried until we successfully establish a connection.
            sleep(1);
            tcp::endpoint endpoint = *endpoint_iterator;
            socket_.async_connect(endpoint,
                                  boost::bind(&client::handle_connect, this,
                                              boost::asio::placeholders::error, ++endpoint_iterator));
        }
        else
        {
            std::cout << "Error: " << err.message() << "\n";
        }
    }

    void handle_connect(const boost::system::error_code& err,
                        tcp::resolver::iterator endpoint_iterator)
    {
        if (!err)
        {
            // The connection was successful. Send the request.
            boost::asio::async_write(socket_, request_,
                                     boost::bind(&client::handle_write_request, this,
                                                 boost::asio::placeholders::error));
        }
        else if (endpoint_iterator != tcp::resolver::iterator())
        {
            // The connection failed. Try the next endpoint in the list.
            socket_.close();
            tcp::endpoint endpoint = *endpoint_iterator;
            socket_.async_connect(endpoint,
                                  boost::bind(&client::handle_connect, this,
                                              boost::asio::placeholders::error, ++endpoint_iterator));
        }
        else
        {
            std::cout << "Error: " << err.message() << "\n";
        }
    }

    void handle_write_request(const boost::system::error_code& err)
    {
        if (!err)
        {
            // Read the response status line.
            boost::asio::async_read_until(socket_, response_, "\r\n",
                                          boost::bind(&client::handle_read_status_line, this,
                                                      boost::asio::placeholders::error));
        }
        else
        {
            std::cout << "Error: " << err.message() << "\n";
        }
    }

    void handle_read_status_line(const boost::system::error_code& err)
    {
        if (!err)
        {
            // Check that response is OK.
            std::istream response_stream(&response_);
            std::string http_version;
            response_stream >> http_version;
            unsigned int status_code;
            response_stream >> status_code;
            std::string status_message;
            std::getline(response_stream, status_message);
            if (!response_stream || http_version.substr(0, 5) != "HTTP/")
            {
                std::cout << "Invalid response\n";
                return;
            }
            if (status_code != 200)
            {
                //std::cout << "Response returned with status code ";
                //std::cout << status_code << "\n";
                return;
            }

            // Read the response headers, which are terminated by a blank line.
            boost::asio::async_read_until(socket_, response_, "\r\n\r\n",
                                          boost::bind(&client::handle_read_headers, this,
                                                      boost::asio::placeholders::error));
        }
        else
        {
            std::cout << "Error: " << err << "\n";
        }
    }

    void handle_read_headers(const boost::system::error_code& err)
    {
        if (!err)
        {
            // Process the response headers.
            std::istream response_stream(&response_);
            std::string header;
            while (std::getline(response_stream, header) && header != "\r");
                //std::cout << header << "\n";
            //std::cout << "\n";

            // Write whatever content we already have to output.
            if (response_.size() > 0)
                //std::cout << &response_;

            // Start reading remaining data until EOF.
            boost::asio::async_read(socket_, response_,
                                    boost::asio::transfer_at_least(1),
                                    boost::bind(&client::handle_read_content, this,
                                                boost::asio::placeholders::error));
        }
        else
        {
            std::cout << "Error: " << err << "\n";
        }
    }

    void handle_read_content(const boost::system::error_code& err)
    {
        if (!err)
        {
            //JFIFHEAD* jf;
            //jf = (JFIFHEAD*) response_.;
            // Write all of the data that has been read so far.
            //std::cout << &response_;
            myfile<< &response_  ;

            // Continue reading remaining data until EOF.
            boost::asio::async_read(socket_, response_,
                                    boost::asio::transfer_at_least(1),
                                    boost::bind(&client::handle_read_content, this,
                                                boost::asio::placeholders::error));
        }
        else if (err == boost::asio::error::eof){
            std::cout << "\n \n EOF " <<std::endl;


            std::cout<< myfile.tellp() << std::endl;

            if(myfile.tellp() < 20000){
                myfile.close();
                std::remove(mFileName);
            }
            myfile.close();



        }
        else if (err != boost::asio::error::eof)
        {
            std::cout << "Error: " << err << "\n";
            myfile.close();
        }
    }
    
    tcp::resolver resolver_;
    tcp::socket socket_;
    boost::asio::streambuf request_;
    boost::asio::streambuf response_;
    std::ofstream myfile;
    char* mFileName;
};



#endif /* defined(__LibLoAndCap__HttpClient__) */
