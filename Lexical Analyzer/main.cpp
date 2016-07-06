#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <locale>

using namespace std;
int linecount=0;
struct words
{
    string name;
    vector<int> lineNumber;
    int occurances=0;
    int type=0;
};
vector <words> unsortedWords;

int isAlphabet(char a)
{
    if(a=='#'|| a=='('|| a==')'|| a==';'|| a=='+'|| a=='-'|| a=='*'|| a=='='|| a=='<'|| a=='>')
    return 0;
    else return 1;
}

void call_sort(string x){
    int words_size= unsortedWords.size();
    for(int i=0;i<words_size; i++){
        if(x==unsortedWords[i].name){
            unsortedWords[i].lineNumber.push_back(linecount);
            unsortedWords[i].occurances++;
            return;
        }
    }
    struct words s;
    s.name=x;
    s.lineNumber.push_back(linecount);
    s.occurances=1;
    if(x=="int" || x=="include" || x=="main" || x=="printf" || x=="iostream" || x=="return")
        s.type=1;
    else if (x=="#" || x=="<" || x==">" || x=="(" || x==")" || x=="{" || x=="}" || x==";" || x=="=" || x=="*" || x=="-" || x=="+")
        s.type=3;
    else if(!isdigit(x[0]))
            s.type=2;

    unsortedWords.push_back(s);
}

void exportFiles()
{
    ofstream identifiers;
    identifiers.open("identifiers.txt", ios::out);
    ofstream keywords;
    keywords.open("keywords.txt", ios::out);
    ofstream operators;
    operators.open("operators.txt",ios::out);
    for(int i=0;i<unsortedWords.size();i++)
    {
        if(unsortedWords[i].type==2)
        {
            identifiers<<unsortedWords[i].name<<"\t\t";
            for(int j=0;j<unsortedWords[i].lineNumber.size();j++)
                identifiers<<unsortedWords[i].lineNumber[j]<<",";
            identifiers<<"\t\t"<<unsortedWords[i].occurances<<endl;
        }
         else if(unsortedWords[i].type==1)
        {
            keywords<<unsortedWords[i].name<<"\t\t";
            for(int j=0;j<unsortedWords[i].lineNumber.size();j++)
                keywords<<unsortedWords[i].lineNumber[j]<<",";
            keywords<<"\t\t"<<unsortedWords[i].occurances<<endl;
        }
         else if(unsortedWords[i].type==3)
        {
            operators<<unsortedWords[i].name<<"\t\t";
            for(int j=0;j<unsortedWords[i].lineNumber.size();j++)
                operators<<unsortedWords[i].lineNumber[j]<<",";
            operators<<"\t\t"<<unsortedWords[i].occurances<<endl;
        }
    }

}
int main()
{
    ifstream source;
    source.open("source.txt", ios::in);
    string line;
    while (getline(source, line)) {
        if (line.empty()) continue;

        istringstream iss(line);
        linecount++;
        string fetchWord;
        while (iss >> fetchWord)
        {
            string temp="";
            for(int i=0;i<fetchWord.length();i++)
            {
                if(isAlphabet(fetchWord[i])==0)
                {
                    if(i!=0) temp+=' ';
                    temp+=fetchWord[i];
                    temp+=' ';
                }
                else
                {
                    temp+=fetchWord[i];
                }
            }
            string buf;
            stringstream ss(temp);
            while(ss>>buf)
                call_sort(buf);
        }
    }
    exportFiles();
    source.close();
    return 0;
}
