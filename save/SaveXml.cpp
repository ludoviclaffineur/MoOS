//
//  SaveXml.cpp
//  LibLoAndCap
//
//  Created by Ludovic Laffineur on 25/02/14.
//  Copyright (c) 2014 Ludovic Laffineur. All rights reserved.
//

#include "SaveXml.h"
#include <boost/foreach.hpp>
#include <boost/filesystem.hpp>

SaveXml::SaveXml(const std::string &filename, Grid* g){
    using boost::property_tree::ptree;
    ptree pt;

    // Put log filename in property tree
    pt.put("save.filename", filename);
    std::vector <OutputsHandler*>* Outputs = g->getOutputs();
    std::vector <Input*>* Inputs = g->getInputs();
    std::vector <Cell*>* Cells = g->getCells();

    std::vector<OutputsHandler*>::iterator o;
    for ( o = Outputs->begin(); o != Outputs->end(); o++) {
        ptree & node = pt.add("save.outputs.output", "");
        node.put("type", (*o)->getOuputType());
        std::vector <IParameter*>* Params = (*o)->getParameters();
        std::vector <IParameter*>::iterator currentParam;
        for (currentParam=Params->begin(); currentParam != Params->end(); currentParam++) {
            std::stringstream ss1,ss2;
            ss1 << (*currentParam)->getName();
            //std::cout<<(*currentParam)->toString()<<std::endl;
            ss2 <<(*currentParam)->toString()->str();
            node.put(ss1.str().c_str(), ss2.str());
        }
    }


    std::vector<Input*>::iterator i;
    for ( i = Inputs->begin(); i != Inputs->end(); i++) {
        ptree & node = pt.add("save.inputs.input", "");
        node.put("name", (*i)->getName());
    }


    std::vector<Cell*>::iterator c;
    for ( c = Cells->begin(); c != Cells->end(); c++) {
        ptree & node = pt.add("save.cells.cell", "");
        node.put("InputName", (*c)->getInput()->getName());
        node.put("OutputName", (*c)->getOutput()->getName());
        node.put("Coefficient", (*c)->getCoeff());
    }

    write_xml(filename, pt);
}

void SaveXml::loadXml(const std::string &filename, Grid* g){
    std::ifstream file (filename);
    if ( file){
        g->getOutputs()->clear();
        //g->getInputs()->clear();
        g->getCells()->clear();
        // Create an empty property tree object
        using boost::property_tree::ptree;
        ptree pt;

        // Load the XML file into the property tree. If reading fails
        // (cannot open file, parse error), an exception is thrown.
        read_xml(filename, pt);
        // Get the filename and store it in the m_file variable.
        // Note that we construct the path to the value by separating
        // the individual keys with dots. If dots appear in the keys,
        // a path type with a different separator can be used.
        // If the debug.filename key is not found, an exception is thrown.


        // Get the debug level and store it in the m_level variable.
        // This is another version of the get method: if the value is
        // not found, the default value (specified by the second
        // parameter) is returned instead. The type of the value
        // extracted is determined by the type of the second parameter,
        // so we can simply write get(...) instead of get<int>(...).


        // Iterate over the debug.modules section and store all found
        // modules in the m_modules set. The get_child() function
        // returns a reference to the child at the specified path; if
        // there is no such child, it throws. Property tree iterators
        BOOST_FOREACH(ptree::value_type &v, pt.get_child("save.outputs")){
            const ptree& child = v.second;
            int type = child.get<int>("type");
            switch (type) {
                case CONSTANCES::OSC:
                    createOsc( g, child);
                    break;
                case CONSTANCES::GRANULAR_SYNTH:
                //    createOsc( g, child);
                    break;
                default:
                    break;
            }
        }

        BOOST_FOREACH(ptree::value_type &v, pt.get_child("save.cells")){
            const ptree& child = v.second;
            std::string IName = child.get<std::string>("InputName");
            std::string OName = child.get<std::string>("OutputName");
            float coeff = child.get<float>("Coefficient");
            g->getCellWithName(IName, OName)->setCoeff(coeff);
        }


        /*for(ptree::iterator iter = pt.get_child("save.inputs.input").begin(); iter != pt.get_child("save.inputs.input").end(); iter++)
         {
         std::cout << iter->first << "," << iter->second.data() << std::endl;
         }
         
         for(ptree::iterator iter = pt.get_child("save.cells.cell").begin(); iter != pt.get_child("save.cells.cell").end(); iter++)
         {
         std::cout << iter->first << "," << iter->second.data() << std::endl;
         }*/

    }

}




void SaveXml::createOsc( Grid* g, const boost::property_tree::ptree& pt){
    OscHandler* o = new OscHandler();
    o->setName(pt.get<std::string>("Name").c_str());
    o->setOscAddress(pt.get<std::string>("OscAddressPattern").c_str());
    //o->setId(pt.get<int>("Identifier"));
    //o->setOscAddress(pt.get<std::string>("OscAddressPattern").c_str());
    o->setIpAdress(pt.get<std::string>("IPAddress").c_str());
    o->setPort(pt.get<std::string>("Port").c_str());
    g->addOutput(o);
}

std::vector<std::string>* SaveXml::listFiles(std::string path){
    namespace fs = boost::filesystem;
    std::vector<std::string>* filesVector = new std::vector<std::string>();
    std::stringstream ss ;

    ss<< CURRENT_PATH<<path;
    fs::path someDir(ss.str());
    fs::directory_iterator end_iter;

    typedef std::multimap<std::time_t, fs::path> result_set_t;
    result_set_t result_set;

    if ( fs::exists(someDir) && fs::is_directory(someDir))
    {
        for( fs::directory_iterator dir_iter(someDir) ; dir_iter != end_iter ; ++dir_iter)
        {
            if (fs::is_regular_file(dir_iter->status()) )
            {
                filesVector->push_back(dir_iter->path().filename().string());
            }
        }
    }
    return filesVector;
}
