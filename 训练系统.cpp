#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <random>  
#include <ctime>  
using namespace std;

typedef struct Question {
    int id;
    string question;
    double answer;
} Question;

vector<Question> questions;

// 生成指定范围内的随机整数
int getRandomIndex(int min, int max) {
    // 使用当前时间作为随机数种子
    static random_device rd;
    static mt19937 gen(rd());
    uniform_int_distribution<> dis(min, max);
    return dis(gen);
}
int main() {
    cout << "模式1--录题模式" << endl;
    cout << "模式2--训练模式" << endl;
    cout<<"模式3--修改答案"<<endl;
    cout<<"模式4--删除问题"<<endl;
    cout<<"退出训练--0"<<endl;
    int mode;
    do{
    cin >> mode;
    cin.ignore();  
    if (mode == 1) {
        cout << "请输入录题数量,以及对应数量的题目,需注意每个题包含题目和正确答案: ";
        int n;
        cin >> n;
        cin.ignore();  

        while (n--) {
            Question shuru;
            cout << "请输入题目: ";
            getline(cin,shuru.question);
            
            cout << "请输入正确答案: ";
            cin >> shuru.answer;
            cin.ignore();  
            if (questions.empty()) {
                shuru.id = 1;
            } else {
                shuru.id = questions.back().id + 1;
            }
            
            questions.push_back(shuru);
            cout << "题目添加成功,题目ID: " << shuru.id << endl;
        }
    }
    else if (mode == 2) {
    if (questions.empty()) {
        cout << "当前题库为空" << endl;
    } else {
        int questionCount;
        cout << "请输入要回答的题目数量: ";
        cin >> questionCount;
        
        if (questionCount <= 0) {
            cout << "题目数量必须大于0" << endl;
        } else if (questionCount > (int)questions.size()) {
            cout << "题库题目不足，题库中只有 " << questions.size() << " 道题目" << endl;
        } else {
            int correctCount = 0;
            for (int i = 0; i < questionCount; i++) {
                cout << "\n=== 第 " << (i + 1) << " 题 ===" << endl;
                int randomIndex = getRandomIndex(0, questions.size() - 1);
                Question randomQuestion = questions[randomIndex];
                cout << "题目: " << randomQuestion.question << endl;
                double userAnswer;
                cout << "请输入你的答案: ";
                cin >> userAnswer;
                if (userAnswer == randomQuestion.answer) {
                    cout << "回答正确" << endl;
                    correctCount++;
                } else {
                    cout << "回答错误，正确答案是: " << randomQuestion.answer << endl;
                }
            }
        }
    }
}else if(mode==3 && !questions.empty()){
    for(int i=0;i<questions.size();i++){
        cout<<"id为"<<i<<"的题目："<<questions[i].question<<endl;
    }
    cout<<"请输入想要修改答案的问题id:"<<endl;
    int ret;
    cin>>ret;
    if(ret>questions.size() || ret<0){
        cout<<"错误输入"<<endl;
    }else {
    cout<<"请输入想要修改的答案："<<endl;
    double correct;
    cin>>correct;
    int top=0;
    while(questions[top].id!=ret){
        top++;
    }
    questions[top].answer=correct;
}
}else if(mode==4 && !questions.empty()){
    for(int i=0;i<questions.size();i++){
        cout<<"id为"<<i+1<<"的题目："<<questions[i].question<<endl;
    }
    cout<<"请输入您想要删除的题目id:"<<endl;
    int ret;
    cin>>ret;
    if(ret>questions.size() || ret<0){
        cout<<"错误输入"<<endl;
    }else if(ret==questions.size()){
        questions.pop_back();
    }else{
        for(int i=ret-1;i<questions.size()-1;i++){
            questions[i].answer=questions[i+1].answer;
            questions[i].question=questions[i+1].question;
        }
        questions.pop_back();
    }
    if(questions.empty()){
            cout<<"题库已空"<<endl;
        }else{
            cout<<"当前题库："<<endl;
            for(int i=0;i<questions.size();i++){
        cout<<"id为"<<i+1<<"的题目："<<questions[i].question<<endl;
    }
        }
}else {
    cout<<"无效的选择"<<endl;
    }
    }while(mode!=0);
return 0;
}