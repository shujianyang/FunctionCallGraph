#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>

using namespace std;

struct FuncInfo{
    string function;
    string file;
    string folder;
    FuncInfo(string func, string fl, string fold)
        :function(func), file(fl), folder(fold) {}
};

int main()
{
    string filename;
    cout << "Please enter the input filename: ";
    cin >> filename;

    ifstream filein(filename);
    
    if(!filein.is_open()){
        cerr << "Error while opening file." << endl;
        return 1;
    }
    
    string func, file, folder;
    vector<FuncInfo> list;
    int maxHeader = 0;
    while(filein >> func && filein >> file && filein >> folder){
        if(file.length() > maxHeader)
            maxHeader = file.length();
        if(folder.length() > maxHeader)
            maxHeader = folder.length();
        FuncInfo fi(func, file, folder);
        list.push_back(fi);
    }
    maxHeader += 2;
    
    int maxLength = 0;
    int preLength = 0;
    int sumLength = 0;
    for(FuncInfo &fi : list){
        int len = fi.function.length();
        sumLength += (len - preLength / 2 - preLength % 2);
        if(sumLength > maxLength)
            maxLength = sumLength;
        preLength = len;
    }
        
    int pos = 0;
    for(vector<FuncInfo>::iterator iter = list.begin();
            iter!=list.end();iter++){
        cout << setw(maxHeader) << left << iter->file;
        string line = "";
        line.append(pos, ' ');
        line.append(iter->function);
        line.append((maxLength - line.length()), '.');
        pos += iter->function.length() / 2;
        cout << line << endl;
        
        cout << setw(maxHeader) << iter->folder;
        if(iter + 1 != list.end()){
            cout << setw(pos + 1) << right << "|" << endl;
            cout << left << setw(maxHeader) << "";
            cout << right << setw(pos + 1) << "|" << endl;
        }
        else
            cout << endl;
    }
    
    return 0;
}
