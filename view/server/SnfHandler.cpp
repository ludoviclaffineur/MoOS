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
#include "vector"
#include "boost/variant.hpp"
#include "boost/any.hpp"
#include "OscHandler.h"
#include "boost/locale.hpp"
#include "SaveXml.h"
#include "KymaHandler.h"

namespace http {
    namespace server{

        SnfHandler::SnfHandler(Grid* g, Genetic* algoGen, ConstrainGenetic* constrainGene){
            mGrid = g;
            mAlgoGen = algoGen;
            mConstrainGene = constrainGene;
        }

        bool SnfHandler::computeRequest(std::string method, std::string parameters, reply &rep){
            rep.status = reply::ok;

            rep.content.append("<?xml version=\"1.0\"  standalone=\"yes\"?>\n<response>\n");
            //printf("%s \n", method.c_str());
            if( method.compare("addOutput")==0){
                std::stringstream ssName,ssTag ;
                ssName<<"NewOsc"<< mGrid->getCurrentOutputId();
                ssTag<<"/"<< mGrid->getCurrentOutputId();
                char* theName = new char[ssName.str().size()];
                strcpy(theName, ssName.str().c_str());
                mGrid->addOutput(new OscHandler(theName, "127.0.0.1", "20000", ssTag.str().c_str(), "f"));
                delete theName;
            }
            else if( method.compare("deleteOutput")==0){
                std::smatch m_input;
                std::regex e_input ("id=([0-9]+)");   // matches words beginning by "sub"
                std::regex_search (parameters,m_input,e_input);
                //std::cout<< m_input[1].str()<<std::endl;
                int id = atoi(m_input[1].str().c_str());
                mGrid->removeOutput(id);

            }
            else if (method.compare("kymaOutput")==0){
                std::vector <std::string> listParameters = ExtractPamameters(parameters);
                KymaHandler(listParameters[1].c_str(), "8000", mGrid);
                //std::cout<< listParameters[0] <<std::endl;

            }
            else if( method.compare("save")==0){
                 //std::cout<< "SAVE"<<std::endl;
                std::smatch m_input;
                std::regex e_input ("filename=(\\w+)", std::regex_constants::ECMAScript);   // matches words beginning by "sub"
                std::regex_search (parameters,m_input,e_input);
                //std::cout<< m_input[1].str()<<std::endl;
                std::stringstream ssFilename;
                ssFilename<<m_input[1].str()<<".xml";
                SaveXml(ssFilename.str().c_str(), mGrid);

            }
            else if( method.compare("rateGrid")==0){
                //std::cout<< "SAVE"<<std::endl;
                std::smatch m_input;
                std::regex e_input ("rate=([0-9]+)");   // matches words beginning by "sub"
                std::regex_search (parameters,m_input,e_input);
                //std::cout<< m_input[1].str()<<std::endl;

                mAlgoGen->evaluateAndEvolve(atoi(m_input[1].str().c_str()));
                //saveXml(ssFilename.str().c_str(), mGrid);

            }
            else if( method.compare("load")==0){
                //std::cout<< "LOAD"<<std::endl;
                std::smatch m_input;
                std::regex e_input ("filename=(\\w+)");   // matches words beginning by "sub"
                std::regex_search (parameters,m_input,e_input);
                //std::cout<< m_input[1].str()<<std::endl;
                std::stringstream ssFilename;
                ssFilename<<m_input[1].str()<<".xml";
                SaveXml::loadXml(ssFilename.str().c_str(), mGrid);

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

                    // rep.content.append("<name>"+ boost::locale::conv::utf_to_utf<char>(s.str()) + "</name>\n");
                }
                rep.content.append("</outputs>\n");

            }
            else if (method.compare("updateCell")==0){
                //std::codecvt_utf8<char32_t> converter;
                //printf("parametre %s \n",parameters.c_str());
                std::smatch m_coeff;
                std::regex e ("coeff=([0-9].[0-9]|[0-9]|[0-9].[0-9][0-9]\\-[0-9].[0-9]|\\-[0-9]|\\-[0-9].[0-9][0-9])");   // matches words beginning by "sub"
                std::regex_search (parameters,m_coeff,e);
                //std::cout<< m_coeff[1].str()<<std::endl;

                std::smatch m_input;
                std::regex e_input ("input=(\\w+)");   // matches words beginning by "sub"
                std::regex_search (parameters,m_input,e_input);
               // std::cout<< m_input[1].str()<<std::endl;

                std::smatch m_output;
                std::regex e_output ("output=(\\w+)");   // matches words beginning by "sub"
                std::regex_search (parameters,m_output,e_output);
                //std::cout<< m_output[1].str()<<std::endl;

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
            else if (method.compare("getOutput")==0){
                std::smatch m_output;
                std::regex e_output ("output=(\\w+)");   // matches words beginning by "sub"
                std::regex_search (parameters,m_output,e_output);
                //std::cout<<"REGEX"<< m_output[1].str()<<std::endl;

                OutputsHandler* cOutput = mGrid->getOutputWithName(m_output[1].str().c_str());
                std::vector<IParameter*>* Params = cOutput->getParameters();
                rep.content.append("<output>");
                for (int i=0; i<Params->size(); i++) {
                    std::stringstream s;
                    const char* cName = Params->at(i)->getName();
                    s<<"<"<<cName<<">"<< Params->at(i)->toString()->str()<<"</"<<cName<<">";
                    //printf("%s \n ",s.str().c_str());
                    rep.content.append(s.str().c_str());
                }
                rep.content.append("</output>");

            }
            else if (method.compare("updateOutput")==0){
                std::vector <std::string> listParameters =ExtractPamameters(parameters);
                int cId = findIdInListParameters(listParameters);
                //printf("ID %d\n", cId);

                mGrid->getOutputWithId(cId)->setParameters(listParameters);
            }
            else if( method.compare("setConstain")==0){
                mConstrainGene->setConstrain();

            }
            else if( method.compare("setOutputValue")==0){
                std::smatch m_input;
                std::regex e_input ("value=(([0-9].[0-9][0-9])|([0-9].[0-9][0-9][0-9])|([0-9].[0-9])|([0-9]))");   // matches words beginning by "sub"
                std::regex_search (parameters,m_input,e_input);

                std::smatch m_name;
                std::regex e_name ("name=(\\w+)");   // matches words beginning by "sub"
                std::regex_search (parameters,m_name,e_name);
                //std::cout<<"SetOUTPUT : " <<m_name[1] <<std::endl;
                mGrid->getOutputWithName(m_name[1].str().c_str())->setValue(std::atof(m_input[1].str().c_str()));
                mGrid->getOutputWithName(m_name[1].str().c_str())->sendData();


            }
            else if( method.compare("setActiveGrid")==0){
                mGrid->switchActive();
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

        int SnfHandler::findTypeInListParameters(std::vector<std::string> listParam){
            for(int i=0; i< listParam.size(); i=i+2){
                if(listParam.at(i).compare("Type")==0){
                    return std::atoi(listParam.at(i+1).c_str());
                }
            }
            return -1;

        }
        
        int SnfHandler::findIdInListParameters(std::vector<std::string> listParam){
            for(int i=0; i< listParam.size(); i=i+2){
                if(listParam.at(i).compare("Identifier")==0){
                    return std::atoi(listParam.at(i+1).c_str());
                }
            }
            return -1;
        }

        std::vector <std::string> SnfHandler::ExtractPamameters(std::string rawParameters){
            std::vector <std::string> listParameters;
            std::smatch m_output;
            std::regex e_output ("(\\w+)=([^&]+)&");   // matches words beginning by "sub"
            while(std::regex_search (rawParameters,m_output,e_output)){
                listParameters.push_back(m_output[1]);
                listParameters.push_back(m_output[2]);
                /*for (int i=0; i< m_output.size();i++){
                 printf(" %d, %s\n",i,m_output[i].str().c_str());
                 
                 }*/
                
                rawParameters =rawParameters.substr(rawParameters.find_first_of("&")+1,rawParameters.size()-1);
                //printf("Parameters left %s= \n",parameters.c_str());
            }
            return listParameters;
        }
        
        
    }
}