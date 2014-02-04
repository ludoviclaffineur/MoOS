//
//  SnfHandler.cpp
//  LibLoAndCap
//
//  Created by Ludovic Laffineur on 2/12/13.
//  Copyright (c) 2013 Ludovic Laffineur. All rights reserved.
//

#include "SnfHandler.h"
#include <string.h>
#include <regex>
#include "mime_types.hpp"

namespace http {
namespace server{

SnfHandler::SnfHandler(Grid* g){
    mGrid = g;
}

bool SnfHandler::computeRequest(std::string method, std::string parameters, reply &rep){
    rep.status = reply::ok;
    
    rep.content.append("<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"yes\"?>\n<response>\n");
   // printf("%s \n", method.c_str());
    if( method.compare("addOutput")==0){
        rep.content.append("OK");
    }
    else if (method.compare("getInputs")==0){
        rep.content.append("<inputs>\n");
        for (int i =0; i<mGrid->getNbrInputs(); i++){
            std::stringstream s;
            s<<mGrid->getInputs()->at(i)->getName();
            rep.content.append("<name>"+ s.str() + "</name>\n");
        }
        rep.content.append("</inputs>\n");
    }
    else if (method.compare("getOutputs")==0){
        rep.content.append("<outputs>\n");
        for (int i =0; i<mGrid->getNbrOutputs(); i++){
            std::stringstream s;
            s<<mGrid->getOutputs()->at(i)->getName();
            rep.content.append("<name>"+ s.str() + "</name>\n");
        }
        rep.content.append("</outputs>\n");

    }
    else if (method.compare("updateCell")==0){
        //printf("parametre %s \n",parameters.c_str());
        std::string s ("coeff=0.7&input=TTL&output=OSC1 0.7&input=TTL&output=OSC1");
        std::smatch m_coeff;
        std::regex e ("coeff=([0-9].[0-9]|[0-9]|[0-9].[0-9][0-9])");   // matches words beginning by "sub"
        std::regex_search (parameters,m_coeff,e);
        std::cout<< m_coeff[1].str()<<std::endl;

        std::smatch m_input;
        std::regex e_input ("input=(\\w+)");   // matches words beginning by "sub"
        std::regex_search (parameters,m_input,e_input);
        std::cout<< m_input[1].str()<<std::endl;

        std::smatch m_output;
        std::regex e_output ("output=(\\w+)");   // matches words beginning by "sub"
        std::regex_search (parameters,m_output,e_output);
        std::cout<< m_output[1].str()<<std::endl;

        Cell* c = mGrid->getCellWithName(m_input[1], m_output[1]);
        char* err= nullptr;
        c->setCoeff(std::strtof(m_coeff[1].str().c_str(),&err));
        //printf("%s\n ",err);
        rep.content.append("<status>OK</status>\n");

        
        //s = m.suffix().str();
        //}
    }
    else if (method.compare("getCells")==0){
        for (int i = 0;i<mGrid->getCells()->size();i++){
            rep.content.append("<cell>\n");
            std::stringstream s ;
            s<< mGrid->getCells()->at(i)->getInput()->getName();
            rep.content.append("<input>"+s.str()+"</input>\n");
            std::stringstream s1 ;
            s1<< mGrid->getCells()->at(i)->getOutput()->getName();
            rep.content.append("<output>"+s1.str()+"</output>\n");
            std::stringstream s2 ;
            s2<< mGrid->getCells()->at(i)->getCoeff();
            rep.content.append("<coeff>"+s2.str()+"</coeff>\n");
            rep.content.append("</cell>");
        }
    }
    else if (method.compare("removeOuput")==0){

    }
    else {
        rep.content.append("<error>Not found</error>\n");
    }
    rep.content.append("</response>\n");

    rep.headers.resize(2);
    rep.headers[0].name = "Content-Length";
    rep.headers[0].value = std::to_string(rep.content.size());
    rep.headers[1].name = "Content-Type";
    rep.headers[1].value = mime_types::extension_to_type("xml");
    return true;

}


}
}