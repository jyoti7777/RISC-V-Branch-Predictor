#include <bits/stdc++.h>
using namespace std;
regex branch(R"(^.*(beq |bge |blt |jal |jalr |bne |bnez |beqz ).*$)");
regex pcaddr(R"(^.*0x([0-9a-fA-F]{8}) )");

string toHex(int ic){
    stringstream ss;
    ss << hex << ic;
    while (ss.str().length() < 8) ss.str("0" + ss.str());
    return ss.str();
}

char one_bit(char history){
    
    if(history=='0'){  
       return '0';
    }
    else{
       return '1'; 
    }
}
int state;
char two_bit(char history){
      
    if(history=='0'){
        if(state!=0){
            state--;
        }
    }
    else if(history=='1'){
        if(state!=3){
            state++;
        }
    }

    if(state==0 || state==1){
        return '0';
    }
    else{
        return '1';
    }
    
}

int main() {
    string history,history1;
    char ch;
    int len,i;
    long long int count,count_len,stop=1000000,iterate=0;
    float icount=0;
    ifstream inputFile("input.txt");
    map<string, pair<string, string>> branchMap;
    if(inputFile.is_open()) {
        string line, nextline, pc, nextpc, pc4;
        smatch match, next_match;
        getline(inputFile, line);
        while(getline(inputFile, nextline) && iterate<stop) {
            iterate++;
            if (regex_match(line, branch)) {
                if(regex_search(line, match, pcaddr)) pc = match[1].str();
                if(regex_search(nextline, next_match, pcaddr)) nextpc = next_match[1].str();
                pc4 = toHex(stoull(pc, nullptr, 16) + 4);
                branchMap[pc].first=nextpc;
                if(nextpc==pc4) branchMap[pc].second+="0";
                else branchMap[pc].second+="1";
            }
            line = nextline;
        }
        inputFile.close();
        cout << "BRANCH TARGET BUFFER" << endl;
        cout << "S.No.\tPC\t Target" << endl;
        for (const auto& pair : branchMap) {
            cout << icount+1 << "\t" << pair.first << " " << pair.second.first << endl;
            icount+=1;
        }
    } else {
        cerr << "Unable to open input file." << endl;
        return 0;
    }

    float accuracy=0.0;
    cout << endl << "ACCURACY ANALYSIS" << endl;
    //Always Taken
    count=0;
    count_len=0;
    for(const auto& pair:branchMap){    
        history=pair.second.second;
        len=history.length();
        count_len+=len;
        ch='1';
        history1.push_back(ch);
        for(i=0;i<len-1;i++){
            if(ch==history[i]){
               count++;
            }
            history1.push_back(ch);    
        }
        if(ch==history[i]){
               count++;
        }
        history1="";
        //accuracy+=(float(count)/float(len))*100;
    }
    accuracy=(float(count)/float(count_len))*100;
    cout<<"Alway Taken Branch Predictor: "<<accuracy<<"%"<<endl;

    //Always Not-Taken
    accuracy=0.0;
    count=0;
    count_len=0;
    for(const auto& pair:branchMap){
        //count=0;
        history=pair.second.second;
        len=history.length();
        count_len+=len;
        ch='0';
        history1.push_back(ch);
        for(i=0;i<len-1;i++){
            if(ch==history[i]){
               count++;
            }
            history1.push_back(ch);    
        }
        if(ch==history[i]){
               count++;
        }
        history1="";
        //accuracy+=(float(count)/float(len))*100;
    }
    accuracy=(float(count)/float(count_len))*100;
    cout<<"Alway Not-Taken Branch Predictor: "<<accuracy<<"%"<<endl;

     // one bit predictor
    count=0;
    count_len=0;
    for(const auto& pair:branchMap){
        //count=0;
        history=pair.second.second;
        len=history.length();
        count_len+=len;
        ch='0';
        history1.push_back(ch);
        for(i=0;i<len-1;i++){
            if(ch==history[i]){
               count++;
            }
            //cout<<"history:"<<history.substr(0,i)<<endl;
            ch=one_bit(history[i]);
            history1.push_back(ch);
            
        }
        if(ch==history[i]){
               count++;
            }
        //cout<<"history:"<<history.substr(0,i)<<endl;
        //cout<<"history(predicted):"<<history1<<"\ncorrect:"<<count<<endl;
        history1="";
        //accuracy+=(float(count)/float(len))*100;
    }
    accuracy=(float(count)/float(count_len))*100;
    cout<<"1-Bit Branch Predictor: "<<accuracy<<"%"<<endl;

    // two bit predictor
    //starting state is weakly not-taken;
    accuracy=0.0;
    count=0;
    count_len=0;
    for(const auto& pair:branchMap){
        //count=0;
        state=1;
        history=pair.second.second;
        len=history.length();
        count_len+=len;
        ch='0';
        history1.push_back(ch); 
        for(i=0;i<(len-1);i++){
            if(ch==history[i]){
               //cout<<"correct\n";
               count++;
            }
            //cout<<"history:"<<history.substr(0,i+1)<<endl;
            ch=two_bit(history[i]);
            history1.push_back(ch);
        }
        if(ch==history[i]){
               count++;
            }
        //cout<<"history:"<<history.substr(0,i)<<endl;
        //cout<<"history(predicted):"<<history1<<"\ncorrect:"<<count<<endl;
        history1="";
        //accuracy+=(float(count)/float(len))*100;
        
    }
    accuracy=(float(count)/float(count_len))*100;
    cout<<"2-Bit Branch Predictor: "<<accuracy<<"%"<<endl;
    return 0;

}
