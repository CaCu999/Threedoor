#include "ThreeDoor.h"

inline int ThreeDoor::ensureCorrectDoor(int n) {
    //get the correct door
    srand(time(0));
    printf("all doors is %d\n",n);
    int res = rand() % n;
    printf("the correct door is %d\n",res);
    return res;
}

inline void ThreeDoor::displayRemain() {
    printf("\n==========================================\n");
    printf("==========================================\n");
    printf("\t[ door\t,\tprobability ]\n");
    for(int i = 0; i < remainDoors.size() ; i ++) {
        if(remainDoors[i] == 0)
            printf("\t[  %d\t,\t  \t  ]",i);
        else
            printf("\t[  %d\t,\t %f  ]",i,remainDoors[i]);
        if(i == selectedDoor)
            printf(" < ");
        else if(i == deletedDoor)
            printf(" ×");
        if(i == correctDoor) 
            printf(" ○");
        printf("\n");
    }
    printf("==========================================\n");
    printf("==========================================\n");
}

inline  void ThreeDoor::displayGameProcess(int a) {
    printf("\n\n\n");
    printf(">>>>>>>>>>>>>>>>>>>>>Games Start<<<<<<<<<<<<<<<<<<<\n");
    printf(">>>>>>     current turn :         %d       <<<<<<<\n",a);
    printf(">>>>>>     last turn selected :   %d       <<<<<<<\n",selectedDoor);
    printf(">>>>>>     last turn deleted :    %d       <<<<<<<\n",deletedDoor);    
    printf(">>>>>>     remain doors :         %d       <<<<<<<\n",doorNum);
    printf(">>>>>>     correct doors :        %d       <<<<<<<\n",correctDoor);
    printf(">>>>>>>>>>>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<<<<<<<\n");
    displayRemain();
}

inline void ThreeDoor::startGame() {
    // for(int i = 0; i < remainDoors.size(); i++){
    for(int i = 0; i < 2; i++){
        displayGameProcess(i);
        if(doorNum <= 2)    break;
        selectDoor();
        deleteDoor();
        retryProbability();
    }
    if(selectedDoor != correctDoor) {
        printf("    you  win!!!!!!!\n");
        isWin =  true;
    }
    else
        printf("    you  lose!!!!!!!\n");
}

bool cmp(pair<int,float> a , pair<int,float> b) {
    return a.second > b.second;
}

inline void ThreeDoor::selectDoor() {
    printf("\n\n start to select doors........\n");
    //change to vector and sort according probability ASC (from big to small)
    vector<pair<int,float>> doorVect(remainDoors.begin(),remainDoors.end());
    sort(doorVect.begin(),doorVect.end(),cmp);

    //get all max probability, and selected one
    vector<pair<int,float>>::iterator iter = doorVect.begin();
    float max = doorVect.begin()->second;
    printf("\t get the max probability \t%f\n",max);
    while (iter != doorVect.end()) {
        // printf("[%d,%f]\t",iter->first,iter->second);
        if(max > iter->second) {
            // printf("\n current probability is %f , max probability is %f\n",iter->second,max);
            iter --;
            break;
        }
        iter++;
    }   
    // cout << endl;
    int num = iter - doorVect.begin();
    
    printf("\t probability  \t num \n");
    printf("\t   %f  \t  %d \n",max,num);
    int tmp;
    do {
        // printf("all door num is %d  doorNum = %d\n",num,doorNum);
        tmp = rand() % num;
        // printf("the selected number is :  %d   all door num is %d  doorNum = %d\n",tmp,num,doorNum);
    } while(remainDoors[doorVect[tmp].first]== 0);
    selectedDoor = doorVect[tmp].first;
    printf("\t get the selected door is \t%d\n",doorVect[tmp].first);
    cout << endl;
}

inline void ThreeDoor::deleteDoor() {
    printf(" start to delete doors........\n");
    printf("\t the num can be deleted \t %d\n",doorNum);
    int tmp;
    printf("\t the  door doors : \t");
    do {
        tmp = rand() % remainDoors.size();
        printf("%d   ",tmp);
    } while(remainDoors[tmp]== 0 || tmp == selectedDoor || tmp == correctDoor);
    printf("\n");
    printf("\t get the deleted door is \t%d\n",tmp);
    // do {
    //     printf("input the door to be deleted : ");
    //     scanf("%d",&tmp);
    //     printf("\n");
    // } while (tmp == selectedDoor || remainDoors[tmp] == 0 || tmp > remainDoors.size() || tmp < 0);
    
    remainDoors[tmp] = 0;
    doorNum -= 1;
    deletedDoor = tmp;
    displayRemain();
}

inline void ThreeDoor::retryProbability() {
    printf(" start to caculate probability........\n");
    float prob = (1.0 - remainDoors[selectedDoor]) / (doorNum - 1 );
    printf("\t selectedProb \t remainProbe \t remainDoor \t result\n");
    printf("\t   %f  \t   %f  \t   %d  \t  %d  \n",
                remainDoors[selectedDoor],(1.0 - remainDoors[selectedDoor]),doorNum,prob);
    printf("the probability is  %f",prob);
    for(int i = 0; i < remainDoors.size();i++) {
        if(remainDoors[i] == 0 || i == selectedDoor) continue;
        remainDoors[i] = prob;
    }
}

static int winner = 0;

int main(){
    
    srand(time(0));
    int n;
    // scanf("%d",&n);
    n = 3;
    for(int i = 1 ; i <= 100 ; i++) {
        ThreeDoor td(n);
        // threeDoors(n);
        td.startGame();
        if(td.isWin) winner++;
    }
    printf("/////////////////////////////////////////////////\n");
    printf("\t\twinner is %d\n",winner);
    printf("/////////////////////////////////////////////////\n");
    return 0;
}