/*
 * CLI.cpp
 * Authors: Noa Amit 315231274 & Tomer Hadar 207651027
 */
#include "CLI.h"

CLI::CLI(DefaultIO* dio) {
    this->dio = dio;
    this->cd = new clientDate;
    this->cd->threashold = 0.9;
    c.push_back(new UploadCSVfile(dio, cd));
    c.push_back(new GetCorrelation(dio, cd));
    c.push_back(new Detection(dio, cd));
    c.push_back(new Results(dio, cd));
    c.push_back(new AnalyzeAndUpload(dio, cd));
    c.push_back(new Exit(dio, cd));
}

void CLI::start(){
    string choice;
    int chooseIndex = 0;
    while(chooseIndex != 5){
        dio->write("Welcome to the Anomaly Detection Server.\n");
        dio->write("Please choose an option:\n");
        for(int i = 0; i < c.size(); i++){
            dio->write((char)(i + 1));
            dio->write("." + c.at(i)->description + "\n");
        }
        choice = dio->read();
        stringstream a(choice);
        a >> chooseIndex;
        chooseIndex--;
        if(chooseIndex>=0 && chooseIndex<=6)
            c.at(chooseIndex)->execute();
    }
}

CLI::~CLI() {
    for (size_t i = 0; i < c.size(); i++) {
        delete c[i];
    }

}