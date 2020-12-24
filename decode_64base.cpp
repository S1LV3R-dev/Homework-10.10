#include <bits/stdc++.h>
using namespace std;

unsigned char b64char(char a) {
    if (a >= 'A' && a <= 'Z')return a - 'A';
    if (a >= 'a' && a <= 'z')return a - 'a' + 26;
    if (a >= '0' && a <= '9')return a - '0' + 52;
    if (a == '+')return 62;
    if (a == '/')return 63;
    return 64;
}
int decode(char* instr, int sz, char* outstr) {
    unsigned char b1, b2, b3, b4;
    char a1, a2, a3;
    int j = 0, k = 0;
    for (int i=0;i<sz;i+=4) {
        b1=b64char(instr[i]),
        b2=b64char(instr[i + 1]),
        b3=b64char(instr[i + 2]),
        b4=b64char(instr[i + 3]);
        if (b3 == 64)
            b3 = 0,
            b4 = 0,
            k = 2;
        if(b4 == 64)
            b4 = 0,
            k = 1;
        a1 = (b1 << 2) | (b2 >> 4);
        a2 = (b2 << 4) | (b3 >> 2);
        a3 = (b3 << 6) | b4;
        outstr[j++]=a1;
        outstr[j++]=a2;
        outstr[j++]=a3;
    }
    return j-k;
}
int main(){
    char infname[1024];
    char outfname[1024];
    cout << "Input source file name: ";
    cin.getline(infname,1024);
    ifstream fin(infname);
    if(!fin.is_open()) {
        cout<<"Can not open the file "<<infname<<endl;
        return 1;
    }
    cout << "Input file name: ";
    cin.getline(outfname, 1024);

    ofstream fout(outfname);
    if (!fout){
        fin.close();
        cout << "Can not write to this file " << outfname << endl;
        return 2;
    }
    char inStr[4*19], outStr[3*19];
    while (fin.peek() != EOF) {
        int s=0;
        for (int i=0; i<4*19&&fin.peek()!=EOF;++i){
            char k = fin.get();
            if (k>='A'&&k<='Z'||k>='a'&&k<='z'||k>='0'&&k<='9'||k=='+'||k=='/'||k=='=') {
              inStr[i]=k;
              ++s;
            }
        }
        
        s = decode(inStr, s, outStr);
        fout.write(outStr, s);
    }
    fin.close();
    fout.close();
}