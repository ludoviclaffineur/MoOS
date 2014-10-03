//
//  PcapGrabAndStorePictures.cpp
//  LibLoAndCap
//
//  Created by Ludovic Laffineur on 1/10/14.
//  Copyright (c) 2014 Ludovic Laffineur. All rights reserved.
//

#include "PcapGrabAndStorePictures.h"


PcapGrapAndStorePictures::PcapGrapAndStorePictures(){
    mActive = true;
    picturesNumber = 0;
}


void PcapGrapAndStorePictures::process (const u_char* data){
    if (mActive) {
        ip_header *ih;
        ih = (ip_header *) (data + 14);
        if(ih->proto == 6 ){
            tcp_header* tcp;
            tcp  = (tcp_header*)(data + 14 + sizeof(ip_header) - sizeof(u_int));
            if (ntohs(tcp->dport) == 80) {
                u_char* dataIn = (u_char*) (data + 14 + sizeof(ip_header) - sizeof(u_int)+sizeof(tcp_header));
                // std::cout<< dataIn << std::endl;

                int size_payload = ntohs(ih->tlen) - (sizeof(ip_header) - sizeof(u_int) + sizeof(tcp_header));
                //printPayload(dataIn, size_payload);
                /*
                }*/
                std::string path,host, fileName;
                bool foundPicture = getPictureUrl(dataIn, size_payload, "http", host, path, fileName);
                if (foundPicture){
                    try
                    {
                        boost::asio::io_service io_service;

                        std::stringstream fileNameSS;
                        fileNameSS <<"/Users/ludoviclaffineur/Documents/LibLoAndCap/build/Release/www/images/"<< ++picturesNumber;
                        client c(io_service, host, path, fileNameSS.str());

                        io_service.run();
                        /*int a;
                        std::cin>>a;*/
                    }
                    catch (std::exception& e)
                    {
                        std::cout << "Exception: " << e.what() << "\n";
                    }
                }



                //std::cout<< dataInString <<std::endl;

            }
        }
        
    }
}

void PcapGrapAndStorePictures::startConnection(){
    

}

bool PcapGrapAndStorePictures::getPictureUrl(u_char* dataIn, int size_payload, std::string typeOfRequest, std::string &host, std::string &path, std::string &fileName){
    std::string dataInString = convertPayloadToString(dataIn, size_payload);
    std::smatch m_output;
    std::regex e_output ("GET ([^ ]*)");   // matches words beginning by "sub"
    std::regex_search (dataInString,m_output,e_output);
    std::stringstream ss;

    if (!m_output.empty()) {m_output[1].str();
        ss<<typeOfRequest<<"://";
        std::smatch m_output_png;
        std::regex e_output_png ("(png|jpeg|jpg|gif|tiff|tif)$");

        if (std::regex_search (m_output[1].str(),m_output_png,e_output_png)){


            //std::cout<<"IMAGE "<< m_output[1].str()<<std::endl <<std::endl;
            std::smatch m_output_host;
            std::regex e_output_host ("Host: ([^ ]*)");
            std::regex_search (dataInString,m_output_host,e_output_host);
            //std::cout<<"Host: "<< m_output_host[1].str()<<std::endl <<std::endl;
            //printf("%c \n", m_output_png[0].str().c_str()[0]);
            //std::cout<<"name: "<< m_output_png[0].str()<<std::endl <<std::endl;
            ss<< m_output_host[1]<<m_output[1];
            std::cout<< ss.str() <<std::endl;
            host.append(m_output_host[1]);
            path.append(m_output[1]);
            return true;
        }
    }
    return false;
}

void PcapGrapAndStorePictures::setActive (bool active){
    mActive = active;
}

std::string PcapGrapAndStorePictures::convertPayloadToString(const u_char* payload, int size_payload){
    std::stringstream ss;
    for(int i = 0; i < size_payload; i++) {
        if (isprint(*payload)){
             //printf("%c", *payload);
             ss<<(char)*payload;
        }
        else{
            //printf(".");
            ss<<' ';

        }
        payload++;
     }
    return ss.str();

}
void PcapGrapAndStorePictures::printPayload(const u_char *payload, int len)
{

    int len_rem = len;
    int line_width = 16;			/* number of bytes per line */
    int line_len;
    int offset = 0;					/* zero-based offset counter */
    const u_char *ch = payload;

    if (len <= 0)
        return;

    /* data fits on one line */
    if (len <= line_width) {
        printHexAsciiLine(ch, len, offset);
        return;
    }

    /* data spans multiple lines */
    for ( ;; ) {
        /* compute current line length */
        line_len = line_width % len_rem;
        /* print line */
        printHexAsciiLine(ch, line_len, offset);
        /* compute total remaining */
        len_rem = len_rem - line_len;
        /* shift pointer to remaining bytes to print */
        ch = ch + line_len;
        /* add offset */
        offset = offset + line_width;
        /* check if we have line width chars or less */
        if (len_rem <= line_width) {
            /* print last line and get out */
            printHexAsciiLine(ch, len_rem, offset);
            break;
        }
    }
    
    return;
}

void PcapGrapAndStorePictures::printHexAsciiLine(const u_char *payload, int len, int offset)
{

    int i;
    int gap;
    const u_char *ch;

    /* offset */
    printf("%05d   ", offset);

    /* hex */
    ch = payload;
    for(i = 0; i < len; i++) {
        printf("%02x ", *ch);
        ch++;
        /* print extra space after 8th byte for visual aid */
        if (i == 7)
            printf(" ");
    }
    /* print space to handle line less than 8 bytes */
    if (len < 8)
        printf(" ");

    /* fill hex gap with spaces if not full line */
    if (len < 16) {
        gap = 16 - len;
        for (i = 0; i < gap; i++) {
            printf("   ");
        }
    }
    printf("   ");

    /* ascii (if printable) */
    ch = payload;
    for(i = 0; i < len; i++) {
        if (isprint(*ch))
            printf("%c", *ch);
        else
            printf(".");
        ch++;
    }
    
    printf("\n");
    
    return;
}