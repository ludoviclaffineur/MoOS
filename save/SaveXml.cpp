//
//  SaveXml.cpp
//  LibLoAndCap
//
//  Created by Ludovic Laffineur on 25/02/14.
//  Copyright (c) 2014 Ludovic Laffineur. All rights reserved.
//

#include "SaveXml.h"

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
            ss2 <<(*currentParam)->toString();
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

    //pt.put("save.outputs.oschandler", filename);
    // Put debug level in property tree
    //pt.put("debug.level", 2);

    // Iterate over the modules in the set and put them in the
    // property tree. Note that the put function places the new
    // key at the end of the list of keys. This is fine most of
    // the time. If you want to place an item at some other place
    // (i.e. at the front or somewhere in the middle), this can
    // be achieved using a combination of the insert and put_own
    // functions.
/*    BOOST_FOREACH(const std::string &name, m_modules)
    pt.put("debug.modules.module", name, true);*/

    // Write the property tree to the XML file.
    write_xml(filename, pt);
}

void SaveXml::loadXml(const std::string &filename, Grid* g){
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
    ptree::iterator iter = pt.get_child("save.outputs.output").begin();
    int type = atoi(iter->second.data().c_str());
    switch (type) {
        case OutputsHandler::OSC:
            g->getOutputs()->push_back(new OscHandler());
            break;

        default:
            break;
    }

    for(ptree::iterator iter = pt.get_child("save.outputs.output").begin(); iter != pt.get_child("save.outputs.output").end(); iter++)
    {
        //Factory class for OutputHandler...

        std::cout << iter->first << "," << iter->second.data() << std::endl;
    }

    for(ptree::iterator iter = pt.get_child("save.inputs.input").begin(); iter != pt.get_child("save.inputs.input").end(); iter++)
    {
        std::cout << iter->first << "," << iter->second.data() << std::endl;
    }

    for(ptree::iterator iter = pt.get_child("save.cells.cell").begin(); iter != pt.get_child("save.cells.cell").end(); iter++)
    {
        std::cout << iter->first << "," << iter->second.data() << std::endl;
    }

}