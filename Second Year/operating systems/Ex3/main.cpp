#include "iostream"
#include "Producer.h"
#include "chrono"
#include "vector"
#include "thread"
#include "fstream"
#include "array"
#include "UnboundedBuffer.h"
#include "BoundedBuffer.h"
using namespace std;

//NOTE:
//i choose to work with the Second option of the configuration file.
//to active the program type the command: make
//for cleaning all the .o files run the command: make clear


//global variabels to get access from anywhere
vector<Producer> producers;
vector<UnboundedBuffer> editors;
BoundedBuffer screenManager = BoundedBuffer() ;
array<string, 3> myNews = {"SPORT", "WEATHER", "NEWS"};


//function printing all the news from the ScreenManage Queue In a separate thread.
void* printAll(void* arg){
    int counter = 0;
    while(counter < 3){
        pair<int, string> p = screenManager.remove();
        if(p.second == "Done")
            counter++;
        else
            cout << p.second << endl;

    }
    cout << "Done" << endl;
    return nullptr;
}

//function that transfer Sport news from the sport Queue to the screenManager Queue In a separate thread.
void* editSport(void* arg){
    string s;
    do{
        this_thread::sleep_for(chrono::milliseconds(100));
        s = editors[0].remove();
        screenManager.insert(0, s);
    }while(s != "Done");
    return nullptr;
}

//function that transfer Weather news from the Weather Queue to the screenManager Queue In a separate thread.
void* editWeather(void* arg){
    string s;
    do{
        this_thread::sleep_for(chrono::milliseconds(100));
        s = editors[1].remove();
        screenManager.insert(1, s);
    }while(s != "Done");
    return nullptr;
}

//function that transfer News news from the News Queue to the screenManager Queue In a separate thread.
void* editNews(void* arg){
    string s;
    do{
        this_thread::sleep_for(chrono::milliseconds(100));
        s = editors[2].remove();
        screenManager.insert(2, s);
    }while(s != "Done");
    return nullptr;
}


void func(Producer &p){
    pair<int, string> myPair = p.getQueue().remove();
    //check the news kind and according to the kind we know to which editor we need to insert this news.
    switch (myPair.first) {
        case 0:
            editors[0].insert(myPair.second);
            break;
        case 1:
            editors[1].insert(myPair.second);
            break;
        case 2:
            editors[2].insert(myPair.second);
            break;
        default:
            break;
    }
    //increase the number of the news that this producer made until now by 1.
    p.increaseWorkCounter();
}

//we active the dispatcher on this function in a separate thread,
//the dispatcher in this function iterate over the Producers vector according the round robin algorithem
//and getting news from those producers.
void *activeDispatcher(void *arg) {
    int counter = 0;

    while (counter < producers.size()) {
        for (int i = 0; i < producers.size(); i++) {
            //this condition check if the finish flag of the producer is on or off.
            if(!producers[i].getisDone()){
                if(producers[i].getWorkCounter() < producers[i].getNumberOfProducts()){
                    //function to take a news from producer and put it in the editors queue.
                    func(producers[i]);
                }
                else{
                    //every time producer finish its job we promote counter by 1 and set flag to 1.
                    producers[i].setisDone();
                    counter++;
                }
            }
        }
    }
    string s = "Done";
    editors[0].insert(s);
    editors[1].insert(s);
    editors[2].insert(s);
    return nullptr;
}

//this function called every time we create a new Producer in separate thread and creating news according
//the amount of News that the Producer asked to create (according the data in the configuration file).
void *createNews(void *arg) {
    int *producerNumber = (int *) arg;
    int counter = 0;
    while (counter < producers[*producerNumber].getNumberOfProducts()) {
        //according the random index we pick the type of the news.
            int randomIndex = (int) random() % 3;
            string s = "Producer " + to_string(producers[*producerNumber].getSerialNumber()) + " " + myNews[randomIndex] +
                " " + to_string(producers[*producerNumber].getAmount(randomIndex));
            producers[*producerNumber].getQueue().insert(randomIndex, s);
            producers[*producerNumber].increase(randomIndex);
            counter++;
    }
    return nullptr;
}

//function to extract the Data about all the Producers from the configuration file.
int initDataFromConf(char *argv[]) {
    fstream configFile;
    configFile.open(argv[1], ios::in);
    if (!configFile.is_open()) {
        cout << "NO SUCH A FILE" << endl;
        exit(-1);
    }
    string line[3];
    int i = 0, j = 0;
    while (getline(configFile, line[i])) {
        if (line[i].empty()) {
            i = 0;
            continue;
        }
        if (i == 2) {
            //a vector of Producers, any producer has its own Data.
            producers.push_back(Producer(stoi(line[0]), stoi(line[1]), stoi(line[2])));
            j++;
            i = 0;
            continue;
        }
        i++;
    }
    return stoi(line[0]);
}


int main(int argc, char *argv[]) {
    int size = initDataFromConf(argv);
    pthread_t tid, did, one, two, three, screen;
    //creating the unbounded Queues for all the kind of News.
    editors.push_back(UnboundedBuffer());
    editors.push_back(UnboundedBuffer());
    editors.push_back(UnboundedBuffer());

    //initialize the size of the bounded Queue for the ScreenManager.
    screenManager.setSize(size);

    //creating all the Producers in a for loop, every single producer on a separate thread.
    for (int i = 0; i < producers.size(); i++) {
        pthread_create(&tid, 0, createNews, new int(i));
    }
    //creating the dispatcher thread, all the editors thread and the ScreenManager thread.
    pthread_create(&did, nullptr, activeDispatcher, nullptr);
    pthread_create(&one, nullptr, editSport, nullptr);
    pthread_create(&two, nullptr, editWeather, nullptr);
    pthread_create(&three, nullptr, editNews, nullptr);
    pthread_create(&screen, nullptr, printAll, nullptr);
    pthread_join(screen, nullptr);
    return 0;
}