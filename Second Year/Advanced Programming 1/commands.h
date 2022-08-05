/*
 * command.h
 * Authors: Noa Amit & Tomer Hadar
 */
#ifndef COMMANDS_H_
#define COMMANDS_H_

#include<iostream>
#include <string.h>

#include <fstream>
#include <vector>
#include "HybridAnomalyDetector.h"

using namespace std;

class DefaultIO{
public:
    virtual string read()=0;
    virtual void write(string text)=0;
    virtual void write(float f)=0;
    virtual void read(float* f)=0;
    virtual ~DefaultIO(){}

// you may add additional methods here
    void readFile(string text){
        ofstream f(text);
        string s = "";
        while((s = read()) != "done\n"){
            f<<s<<endl;
        }
        f.close();
    }
};

struct sequenceDetections {
    int start;
    int end;
    string description;
    bool FP;
};

struct clientDate{
    float threashold;
    HybridAnomalyDetector hd;
    vector<correlatedFeatures> trainReports;
    vector<AnomalyReport> testReports;
    vector <sequenceDetections> sd;
    int sizeTable;
};
// you may edit this class
class Command{
protected:
    DefaultIO* dio;
    clientDate* cd;
public:
    const string description;
    Command(DefaultIO* dio, const string& description,clientDate* cd):dio(dio),description(description),cd(cd){}
    virtual void execute()=0;
    virtual ~Command(){}

};

// implement here your command classes

class UploadCSVfile:public Command{
public:
    UploadCSVfile(DefaultIO* dio ,clientDate* cd):Command(dio, "upload a time series csv file",cd){}

    void execute(){
        dio->write("Please upload your local train CSV file.\n");
        dio->readFile("anomalyTrain.csv");
        dio->write("Upload complete.\n");
        dio->write("Please upload your local test CSV file.\n");
        dio->readFile("anomalyTest.csv");
        dio->write("Upload complete.\n");
    }

};

class GetCorrelation:public Command{
public:
    GetCorrelation(DefaultIO* dio,clientDate* cd):Command(dio, "algorithm settings", cd){}

    void execute(){
        float threshold = cd->threashold;
        dio->write("The current correlation threshold is ");
        dio->write(cd->threashold);
        dio->write("\nType a new threshold");
        dio->read(&threshold);
        while(threshold < 0 || threshold > 1){
            dio->write("\nplease choose a value between 0 and 1.\n");
            dio->write("The current correlation threshold is ");
            dio->write(cd->threashold);
            dio->write("\nType a new threshold");
            dio->read(&threshold);
        }
        dio->write("\n");
        cd->threashold = threshold;
        cd->hd.setThreshold(threshold);
    }
};

class Detection:public Command{
public:
    Detection(DefaultIO* dio, clientDate* cd):Command(dio, "detect anomalies", cd){}

    void execute(){
        if(cd->hd.getNormalModel().size()!=0) {
            cd->hd.emptyNormalModel();
        }
        TimeSeries ts1("anomalyTrain.csv");
        int sizeTable = ts1.getColumnSize();
        cd->hd.learnNormal(ts1);
        cd->trainReports = cd->hd.getNormalModel();
        TimeSeries ts2("anomalyTest.csv");
        cd->testReports= cd->hd.detect(ts2);
        dio->write("anomaly detection complete.\n");
        cd->sizeTable = sizeTable;
    }
};

class Results:public Command{
public:
    Results(DefaultIO* dio, clientDate* cd):Command(dio, "display results", cd){}
    void execute(){
        int sizeVec = cd->testReports.size();
        for(int i = 0; i < sizeVec; i++){
            dio->write(cd->testReports.at(i).timeStep);
            dio->write("\t");
            dio->write(cd->testReports.at(i).description);
            dio->write("\n");
        }
        dio->write("Done.\n");
    }
};

class AnalyzeAndUpload:public Command{
public:
    AnalyzeAndUpload(DefaultIO* dio, clientDate* cd):Command(dio, "upload anomalies and analyze results", cd){}
    void execute() {
        float p=0;
        float TP=0;
        int N = cd->sizeTable;
        if (cd->sd.size() != 0) {
            cd ->sd.clear();
        }
        init();
        dio->write("Please upload your local anomalies file.\n");
        string s = "";
        while((s = dio->read()) != "done\n"){
            p++;
            int counter = 0;
            for (int i = 0; s[i]!=',' ; i++){
                counter = i;
            }

            string begin = s.substr(0, counter+1);
            string end = s.substr(counter+2, s.length());
            int numBegin = stoi(begin);
            int numEnd = stoi(end);
            N = N - (numEnd - numBegin + 1);
            if (changeTP(numBegin, numEnd)){
                TP++;
            }
        }
        float allFT = checkFP();
        float FalseAlarmRate = ((int)(1000.0*allFT/N))/1000.0f;
        float TruePositiveRate = ((int)(1000.0*TP/p))/1000.0f;
        dio->write("Upload complete.\n");
        dio->write("True Positive Rate: ");
        dio->write(TruePositiveRate);
        dio->write("\n");
        dio->write("False Positive Rate: ");
        dio->write(FalseAlarmRate);
        dio->write("\n");
    }

    void init() {
        int sizeVecTrain = cd->trainReports.size();
        int sizeVecTest = cd->testReports.size();
        for (int i = 0; i < sizeVecTrain ; i++) {
            string currentDescription;
            currentDescription.append((cd->trainReports.at(i).feature1)).append("-").append((cd->trainReports.at(i).feature2));
            for (int j = 0; j < sizeVecTest; j++) {
                int firstSeq = -1;
                int endSeq = -1;
                if (cd->testReports.at(j).description == currentDescription) {
                    firstSeq = cd->testReports.at(j).timeStep;
                    endSeq = firstSeq;
                    while (((j + 1) < sizeVecTest) && (cd->testReports.at(j + 1).description == currentDescription)) {
                        if (cd->testReports.at(j + 1).timeStep == (endSeq + 1)) {
                            j++;
                            endSeq = cd->testReports.at(j).timeStep;
                        } else {
                            break;
                        }
                    }
                    if (firstSeq != -1) {
                        sequenceDetections newSD;
                        newSD.description = currentDescription;
                        newSD.start = firstSeq;
                        newSD.end = endSeq;
                        newSD.FP = false;
                        cd->sd.push_back(newSD);
                    }
                    if (((j + 1) < sizeVecTest)) {
                        if(cd->testReports.at(j + 1).description != currentDescription) {
                            j = sizeVecTest;
                        }
                    }
                }
            }
        }
    }

    bool changeTP(int numBegin, int numEnd){
        bool result = false;
        int sizeVecTest = cd->sd.size();
        for (int i = 0; i < sizeVecTest; ++i) {
            if ((cd->sd.at(i).end < numBegin) || (cd->sd.at(i).start > numEnd)){
                continue;
            }
            else {
                result = true;
                cd->sd.at(i).FP=true;
            }
        }
        return result;
    };
    float checkFP () {
        int sizeVecSD = cd->sd.size();
        float counter=0;
        for (int i = 0; i < sizeVecSD; i++) {
            if (!cd->sd.at(i).FP) {
                counter ++;
            }
        }
        return counter;
    }
};

class Exit:public Command{
public:
    Exit(DefaultIO* dio, clientDate* cd):Command(dio, "exit", cd){}
    void execute(){
        return;
    }
};


#endif /* COMMANDS_H_ */
