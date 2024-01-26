#include "ComputedChaining.h"
using namespace std;

ComputedChaining::ComputedChaining(int table_size){
        for (int i = 0; i < table_size; ++i) {
            data_vec.push_back(entry());
        }
}
 int ComputedChaining::hash(int key) {
        return key % data_vec.size();
}
int ComputedChaining::hash2(int key){
        int step=(key/data_vec.size())%data_vec.size();
        if(step==0)step=1;
        return step;
}
void ComputedChaining::insert(int key){
        int index=hash(key); // index 6 
        if (data_vec[index].data != -1) { // collision
            if (isThisYourHome(data_vec[index].data)) { // Q1: Add to chain // 90  ishome -> 90 // True

            vector<int>chainofhome = find_chain(data_vec[index].data);
                if(chainofhome.size()>1){
                    while (data_vec[index].link != -1) {
                        int incrementer = hash2(data_vec[index].data);
                        index = (index + data_vec[index].link * incrementer) % data_vec.size(); //Eger link -1 degilse o chainde -1 olan yere gittik 
                    } 
                } 

                int inc = hash2(data_vec[index].data);
                int oldindex = index;
                  
                index = (index + inc)%data_vec.size();

                //data_vec[oldindex].link = 1;


                int counter = 1;
                while(data_vec[index].data!=-1){
                    counter++;
                    index = (index + inc) % data_vec.size();
                    
                }
                data_vec[oldindex].link = counter;

                data_vec[index].data = key;
                data_vec[index].link = -1;
 
            }else{
                int movedKey = data_vec[index].data; // movedKey = 55
                vector<int> movedKeyChain = find_chain(movedKey); // Chain 6, 2, 3
                int previousIndex = 0; 
                for(int i=0; i<movedKeyChain.size(); i++){
                    if(movedKeyChain[i] == index){
                        previousIndex = movedKeyChain[i-1];
                        break;
                    }
                }

                data_vec[previousIndex].link = -1;
                

                vector<int> movedKeyAfter;

                int movedKeyInChain=0; 
                while(int i=1 != movedKeyChain.size() ){
                    
                    if(movedKeyChain[i] == index)
                        movedKeyInChain = i; //1
                        break;
                    
                    i++;
                }  

                for(int x = movedKeyInChain ; x< movedKeyChain.size(); x++){
                    movedKeyAfter.push_back(movedKeyChain[x]);
                }
                
                vector<int> data;
                for (int i=0; i<movedKeyAfter.size(); i++) {
                    data.push_back(data_vec[movedKeyAfter[i]].data);
                }

               
                for(int x =0; x<movedKeyAfter.size(); x++){

                    data_vec[movedKeyAfter[x]].data = -1;
                    data_vec[movedKeyAfter[x]].link = -1;

                } 
                data_vec[index].data = key;
                data_vec[index].link = -1; 
                
                for (int newKey=0; newKey<data.size(); newKey++) {
                        insert(data[newKey]);
                
                }
            } 
        } else { // direct insertion //No collision 
            data_vec[index].data = key;
            data_vec[index].link = -1; //90 link = -1 
        } 


}
int ComputedChaining::find_index(int key){//find the index of 
        int idx=hash(key); //6
        int inc=hash2(key); //1
                if(data_vec[idx].data==key)
                        return idx;
                else{
                        while(data_vec[idx].data != -1){ //Doluyken
                                if(data_vec[idx].data != key){ 
                                        inc=hash2(data_vec[idx].data); //5
                                        idx=(idx+data_vec[idx].link*inc)%data_vec.size(); //
                                }else return idx; //4 returned
                
                        }
                }
        return -1;
}
bool ComputedChaining::isThisYourHome(int key){//If returns true if the hash of the key is same with the index of data_vec 
     

    if(hash(key) == find_index(key)){
        return true;
    }
    else {
         return false;
    } 

}
int ComputedChaining::first_of_my_chain(int key) {
        return data_vec[hash(key)].data;
}

int ComputedChaining::find_num_probes(int key) {
    int idx = hash(key);
    int inc = hash2(key);
    int probeCount = 1;

    if (data_vec[idx].data != key) {
        while (data_vec[idx].data != -1) {
            inc = hash2(data_vec[idx].data);
            idx = (idx + data_vec[idx].link * inc) % data_vec.size();
            probeCount++;
            if (data_vec[idx].data == key) {
                break;
            }
        }
    }
    return probeCount;
}

vector<int> ComputedChaining::find_chain(int key){ //gives you chain whose member is the key
        vector<int> chain;
        int index=hash(key); //key=55, index=6
        int inc;//1
        while(data_vec[index].data != -1){ //DOLUYKEN
                chain.push_back(index); //6
                if(data_vec[index].link != -1){ //Linki doluiken
                        inc=hash2(data_vec[index].data);//2 inc=5
                        index=(index+data_vec[index].link*inc)%data_vec.size();

        }else
                        break;
        }
        return chain;
} 


