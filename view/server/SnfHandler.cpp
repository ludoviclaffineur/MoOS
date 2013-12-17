//
//  SnfHandler.cpp
//  LibLoAndCap
//
//  Created by Ludovic Laffineur on 2/12/13.
//  Copyright (c) 2013 Ludovic Laffineur. All rights reserved.
//

#include "SnfHandler.h"
#include <string.h>
#include "mime_types.hpp"

namespace http {
namespace server{

SnfHandler::SnfHandler(Grid* g){
    mGrid = g;
}

bool SnfHandler::computeRequest(std::string method, std::string parameters, reply &rep){
    rep.status = reply::ok;
    
    rep.content.append("<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"yes\"?>\n<response>\n");
    printf("%s \n", method.c_str());
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
        for (int i =0; i<mGrid->getNbrInputs(); i++){
            std::stringstream s;
            s<<mGrid->getOutputs()->at(i)->getName();
            rep.content.append("<name>"+ s.str() + "</name>\n");
        }
        rep.content.append("</outputs>\n");

    }
    else if (method.compare("updateCell")==0){

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