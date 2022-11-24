#include "ThreeDoor.h"
#include <mingw.thread.h>
#include <mingw.mutex.h>
#include <vector>
#include <semaphore.h>
#include <stack>

inline int ThreeDoor::ensureCorrectDoor(int n) {
    //get the correct door
    // srand(time(0));
    // LOGA("all doors is %d\n",n);
    LOGA("all doors is %d\n",n);
    int res = rand() % n;
    LOGA("the correct door is %d\n",res);
    return res;
}

inline void ThreeDoor::displayRemain() {
    LOGA("\n==========================================\n");
    LOGA("==========================================\n");
    LOGA("\t[ door\t,\tprobability ]\n");
    for(int i = 0; i < remainDoors.size() ; i ++) {
        string signal = "";
        if(i == selectedDoor)
            signal += " < ";
        else if(i == deletedDoor)
            signal += " ×";
        if(i == correctDoor) 
            signal += " ○";
        if(remainDoors[i] == 0)
            LOGA("\t[  %d\t,\t  \t  ]%s\n",i,signal.c_str());
        else
            LOGA("\t[  %d\t,\t %f  ]%s\n",i,remainDoors[i],signal.c_str());
        LOGA("\n");
    }
    LOGA("==========================================\n");
    LOGA("==========================================\n");
}

inline  void ThreeDoor::getAllProbabilities() {
    string titles = "doors";
    for(int i = 0; i < remainDoors.size() ; i ++)
        titles += "\t\t  " + to_string(i);
    string values = "values";
    for(int i = 0; i < remainDoors.size() ; i ++)
        values += "\t   " + to_string(remainDoors[i]);
    LOGW("%s\n",titles.c_str());
    LOGW("%s\n",values.c_str());
}


inline void ThreeDoor::startGame() {
    // for(int i = 0; i < remainDoors.size(); i++){
    for(int i = 0; i < 2; i++){
        if(doorNum <= 2)    break;
        selectDoor();
        deleteDoor();
        retryProbability();
        getAllProbabilities();
    }
    if(selectedDoor != correctDoor) {
        LOGA("    you  win!!!!!!!\n");
        isWin =  true;
    }
    else
        LOGA("    you  lose!!!!!!!\n");
}

bool cmp(pair<int,float> a , pair<int,float> b) {
    return a.second > b.second;
}

inline void ThreeDoor::selectDoor() {
    LOGI("user start to select doors , select the door with max probability........\n");
    //change to vector and sort according probability ASC (from big to small)
    vector<pair<int,float>> doorVect(remainDoors.begin(),remainDoors.end());
    sort(doorVect.begin(),doorVect.end(),cmp);

    //get all max probability, and selected one
    // vector<pair<int,float>>::iterator iter = doorVect.begin();
    auto iter = doorVect.begin();
    float max = doorVect.begin()->second;
    LOGI("max probability  %f\n",max);
    LOGA("\t get the max probability \t%f\n",max);

    //locate the end of the max probability
    while (iter != doorVect.end()) {
        if(max > iter->second) {
            // LOGI("current probability is %f , max probability is %f\n",iter->second,max);
            break;
        }
        LOGI("[%d,%f]\n",iter->first,iter->second);
        iter++;
    }

    //get the num of max probability
    int num = iter - doorVect.begin();    
    // LOGE("\t probability  \t num \n");
    // LOGE("\t   %f  \t  %d \n",max,num);
    int tmp;
    // do {
        // LOGA("all door num is %d  doorNum = %d\n",num,doorNum);
        tmp = rand() % num;
        LOGI("random num: %d  the selected number is :  %d   max probability num is %d  doorNum = %d\n",tmp,doorVect[tmp].first,num,doorNum);
    // } while(remainDoors[doorVect[tmp].first] == 0);
    selectedDoor = doorVect[tmp].first;
    LOGI("\t get the selected door is   %d  max probability  %d\n",selectedDoor,num);
    cout << endl;
}

inline void ThreeDoor::deleteDoor() {
    LOGA(" start to delete doors........\n");
    LOGA("\t the num can be deleted \t %d\n",doorNum);
    int tmp;
    LOGA("\t the  door doors : \t");
    do {
        tmp = rand() % remainDoors.size();
        LOGA("%d   ",tmp);
    } while(remainDoors[tmp]== 0 || tmp== selectedDoor || tmp == correctDoor);
    LOGA("\n");
    LOGW("\t get the deleted door is \t%d\n",tmp);
    // do {
    //     LOGA("input the door to be deleted : ");
    //     scanf("%d",&tmp);
    //     LOGA("\n");
    // } while (tmp == selectedDoor || remainDoors[tmp] == 0 || tmp > remainDoors.size() || tmp < 0);
    
    remainDoors[tmp] = 0;
    doorNum -= 1;
    deletedDoor = tmp;
    displayRemain();
}

inline void ThreeDoor::retryProbability() {
    LOGA(" start to caculate probability........\n");
    float prob = (1.0 - remainDoors[selectedDoor]) / (doorNum - 1 );
    LOGW("\t selectedProb \t remainProbe \t remainDoor \t result\n");
    LOGW("\t   %f  \t   %f  \t   %d  \t  %f  \n",
                remainDoors[selectedDoor],(1.0 - remainDoors[selectedDoor]),doorNum,prob);
    LOGA("the probability is  %f",prob);
    for(int i = 0; i < remainDoors.size();i++) {
        if(remainDoors[i] == 0 || i == selectedDoor) continue;
        remainDoors[i] = prob;
    }
}

static int winner = 0;
static mutex m_mutex;

void start(int n) {
    for(int i = 1; i <= 10; i++) {
        ThreeDoor td(n);
        td.startGame();
        m_mutex.try_lock();
        if(td.isWin) winner++;
        m_mutex.unlock();
    }
}

int main(){
    
    // srand(time(0));
    int n;
    // scanf("%d",&n);
    n = 4;
    // vector<thread> all_thread;
    stack<thread> all_thread;
    for(int i = 1 ; i <= 200; i++) {
        all_thread.emplace(start,n);
        
        // ThreeDoor td(n);
        // // threeDoors(n);
        // td.startGame();
        // if(td.isWin) winner++;
        
    }
    for(int i = 1; i <= 200; i++) {
        all_thread.top().join();
        all_thread.pop();
    }

    // this_thread::sleep_for(chrono::seconds(100));
    LOGE("/////////////////////////////////////////////////\n");
    LOGE("\t\twinner is %d\n",winner);
    LOGE("/////////////////////////////////////////////////\n");
    return 0;
}