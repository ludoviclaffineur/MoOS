//
//  SerializeXml.h
//  LibLoAndCap
//
//  Created by Ludovic Laffineur on 20/03/15.
//  Copyright (c) 2015 Ludovic Laffineur. All rights reserved.
//

#ifndef __LibLoAndCap__SerializeXml__
#define __LibLoAndCap__SerializeXml__

#include <iostream>


#include <iomanip>
#include <iostream>
#include <fstream>
#include <string>

#include <cstdio> // remove
#include <boost/config.hpp>


#include <boost/archive/tmpdir.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include "Grid.h"
#include "demo_gps.hpp"

class SerializeXml{
public:
    bus_stop *bs0;
    void save_busstop(const bus_stop &s, const char * filename){
        // make an archive
        std::ofstream ofs(filename);
        assert(ofs.good());
        boost::archive::xml_oarchive oa(ofs);
        oa << BOOST_SERIALIZATION_NVP(s);
    }

    
    SerializeXml(){
      //  save_to_xml(g, "./demo-damien-ludo.xml");
         bs0 = new bus_stop_corner(
                                            gps_position(34, 135, 52.560f),
                                            gps_position(134, 22, 78.30f),
                                            "24th Street", "10th Avenue"
                                            );

       
    }

    void doIt(){

        save_busstop(*bs0, "./BUSTOP.XML");
        //delete bs0;

    }
    //void save_to_xml(Grid &g, const char * filename);





};






#endif /* defined(__LibLoAndCap__SerializeXml__) */
