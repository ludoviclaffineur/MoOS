//
//  ODBCHandler.cpp
//  LibLoAndCap
//
//  Created by Ludovic Laffineur on 13/01/15.
//  Copyright (c) 2015 Ludovic Laffineur. All rights reserved.
//

#include "OdbcHandler.h"

OdbcHandler::OdbcHandler(Grid* g, std::string configFile):CaptureDevice(){
    mGrid = g;
    try
    {
        mSql = new soci::session(soci::odbc, configFile);
        //mSql->set_log_stream(&std::cout);

    }
    catch (std::exception const &e)
    {
        std::cerr << "Error: " << e.what() <<'\n';
    }
    mCurrentRow = 0;
    //init();

}

OdbcHandler::~OdbcHandler(){
    mSql->close();
    delete mSql;
}

void OdbcHandler::init(){
    mNames.push_back("nombreC");
    mNames.push_back("nombreH");
    mNames.push_back("nombreO");
    mNames.push_back("ac");
    mNames.push_back("al");
    mNames.push_back("db");
    mNames.push_back("es");
    mNames.push_back("ke");
    mNames.push_back("ol");
    mNames.push_back("MW");
    mNames.push_back("CoName");

    for (int i = 0; i<10; i++) {
        mRequest.push_back(std::vector<double>(500));
    }


    std::string OUTPUT = "";
    try
    {
        (*mSql) << "select \"nombreC\",\"nombreH\",\"nombreO\",\"ac\",\"al\",\"db\",\"es\",\"ke\",\"ol\",\"MW\",\"CoCode\" from sonification;",
                    soci::into(mRequest[0]),
                    soci::into(mRequest[1]),
                    soci::into(mRequest[2]),
                    soci::into(mRequest[3]),
                    soci::into(mRequest[4]),
                    soci::into(mRequest[5]),
                    soci::into(mRequest[6]),
                    soci::into(mRequest[7]),
                    soci::into(mRequest[8]),
                    soci::into(mRequest[9]),
                    soci::into(mDescriptions);
        //std::cout<<OUTPUT<<std::endl;
       /* std::cout<< "#C\t#H\t#O\tac\tal\tdb\tes\tke\tol\tMW"<<std::endl;
        for (int i = 0; i<mRequest[0].size(); i++) {

            for(int j = 0; j<mRequest.size(); j++){
                std::cout << mRequest[j][i]<<"\t";
            }
            std::cout<<std::endl;
        }*/
        for(int i = 0; i< mRequest.size(); i++){
            mProcessings.push_back(new ScalingProcessing<double>(mGrid, &mRequest[i], mNames[i]));
        }
        mDescription = mDescriptions[0];

    }
    catch (std::exception const &e)
    {
        std::cerr << "Error: " << e.what() <<'\n';
    }
   // trig();

}

void OdbcHandler::setRow(int identifier){
    mCurrentRow = identifier;
    mDescription = mDescriptions[mCurrentRow];
}

void OdbcHandler::trig(){

    for (int i=0; i<mProcessings.size();i++) {
        mProcessings[i]->process(&mRequest[i][mCurrentRow]);
    }
    //std::cout<<mDescriptions[LINE];

    //LINE = (LINE+1)%mRequest[0].size();

    
    mGrid->compute();
}


