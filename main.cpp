#include<iostream>
#include<map>
#include<string>
#include<vector>
#include<algorithm>
#include<iomanip>
#include <limits>
#include <climits>
using namespace std;

struct Student{
    string id;
    string name;
    int score;
};

map<string,Student> students;

void printHeader(){
    cout<<left
        <<setw(12)<<"學號"
        <<setw(16)<<"姓名"
        <<setw(6)<<"成績"
        <<"\n";
    cout<<string(34,'-')<<"\n";
}
void printStudent(const Student& s){
    cout<<left
        <<setw(12)<<s.id
        <<setw(16)<<s.name
        <<setw(6)<<s.score
        <<"\n";
}

void addStudent(){
    string id,name;
    int score;

    cout<<"學號:";
    cin>>id;
    if(students.count(id)){
            cout<<"學號"<<id<<"已存在!\n";
            cout<<"是否覆蓋(Y or N)";
            char c;
            cin>>c;
            if(c=='N'){
                cout<<"已取消\n";
            }
        }
    cout<<"姓名:";
    cin>>name;
    cout<<"成績:";
    while(!(cin>>score)||score<0||score>100){
        cout<<"成績輸入有誤";
    }
    
    students[id]={id,name,score};
    cout<<name<<"("<<id<<")已加入\n";   
}

void listAll(){
    cout<<"全部學生\n";

    if(students.empty()){
        cout<<"無資料\n";
        return;
    }

    printHeader();
    for(auto&[key,s]:students){
        printStudent(s);
    }

    cout<<"\n共"<<students.size()<<"個學生\n";
}

void sortByScore(){
    cout<<"依成績排序\n";
    if(students.empty()){
        cout<<"無資料\n";
        return;
    }
    vector<Student> vec;
    vec.reserve(students.size());
    for(auto&[key,s]:students){
        vec.push_back(s);
    }

    sort(vec.begin(),vec.end(),[](Student& a,Student& b){
        return a.score > b.score;
    });

    printHeader();
    int rank=1;
    for(auto& s:vec){
        cout<<left<<setw(4)<<rank++;
        printStudent(s);
    }
}

void searchStudent(){
    cout<<"\n查詢學生\n";
    cout<<"id:";
    string id;
    cin>>id;
    auto it = students.find(id);
    if(it==students.end()){
        cout<<"找不到學號"<<id<<"的人\n";
    }else{
        printHeader();
        printStudent(it->second);
    }
}

void showStats(){
    cout<<"\n統計成績\n";
    if(students.empty()){
        cout<<"無資料\n";
        return;
    }

    int sum  = 0;
    int maxS = INT_MIN;
    int minS = INT_MAX;
    int pass = 0;
    int fail = 0;

    for(auto&[key,s]:students){
        sum+=s.score;
        maxS=max(maxS,s.score);
        minS=min(minS,s.score);
        if(s.score>=60){
            ++pass;
        }else{
            ++fail;
        }
    }
    double avg=sum/students.size();

    cout << "全班人數  :" << students.size() << " 人\n";
    cout << "平均成績  :" << avg  << "\n";
    cout << "最高分    :" << maxS << "\n";
    cout << "最低分    :" << minS << "\n";
    cout << "及格人數  :" << pass << " 人\n";
    cout << "不及格人數：" << fail << " 人\n";
}

void loadSampleData(){
    vector<Student>samples={
        {"S001", "AA", 85},
        {"S002", "BB", 72},
        {"S003", "CC", 91},
        {"S004", "DD", 58},
        {"S005", "EE", 66}
    };
    for(auto& s :samples){
        students[s.id]=s;
    }
    cout<<"（已載入 " << samples.size() << " 筆範例資料）\n";
}

void printMenu() {
    cout << "\n╔══════════════════════════════╗\n";
    cout <<   "║   學生資料管理系統           ║\n";
    cout <<   "╠══════════════════════════════╣\n";
    cout <<   "║  1. 新增學生資料             ║\n";
    cout <<   "║  2. 列出所有學生             ║\n";
    cout <<   "║  3. 依成績排序（高→低）      ║\n";
    cout <<   "║  4. 查詢學生                 ║\n";
    cout <<   "║  5. 統計成績                 ║\n";
    cout <<   "║  0. 離開程式                 ║\n";
    cout <<   "╚══════════════════════════════╝\n";
    cout <<   "請選擇功能(0-5):";
}
int main(){
    loadSampleData();
    int choice;
    while (true) {
        printMenu();

        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "請輸入有效數字。\n";
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice) {
            case 1: addStudent();    break;
            case 2: listAll();       break;
            case 3: sortByScore();   break;
            case 4: searchStudent(); break;
            case 5: showStats();     break;
            case 0:
                cout << "程式結束，再見！\n";
                return 0;
            default:
                cout << "無效選項，請重新輸入。\n";
        }
    }
}