#include<bits/stdc++.h>
using namespace std;

void output(ofstream &fout, int *M, int l, char ch){
	int N[256]={0},k=-1,i=0,t=0;
	int c=l;
	while(c>0){
		t++;
		c/=10;
	}
	string s;
	for(int i=0;i<256;i++){
		if( ( (ch=='Y')?M[i]>0:M[i]>-1) && i!=10 && i!=13 && i!=9){
			N[++k]=M[i];
			s+=char(i);
		}
	}
	int f=k;
	if(M[10]>0||ch=='N') f+=9;
	if(M[9]>0||ch=='N') f+=5;
	if(M[13]>0||ch=='N') f+=15;
	
	for(i=(f+t-22);i>=(f+t-22)/2;i--)
	fout<<"=";
	fout<<" Symbol Usage Statistics ";
	for( ;i>=0;i--)
	fout<<"=";
	fout<<endl;
	for(int i=l,c=i;i>0;--i){ {
			int g=0;
			while(c>0){
				g++;
				c/=10;
			}
			
			for(int i=g;i<t;i++)
			fout<<" ";
			fout<<i<<"|";
		}
		for(int j=0;j<=k;++j){
			if(N[j]>=i) 
				fout<<"*";
			else 
				fout<<" ";
		}
		if(M[10]>=i) fout<<"    *    ";
		else if(ch=='N' || M[9]>0 || M[13]>0)fout<<"         ";
		if(M[9]>=i) fout<<"  *  ";
		else if(ch=='N' || M[13]>0)fout<<"     ";
		if(M[13]>=i) fout<<"       *       ";
		else if(ch=='N')fout<<"               ";
		fout<<"|"<<endl;
	}
	for(int i=1;i<=t;i++)
	fout<<" ";
	fout<<"|";
	for(int i=0;i<=f;i++)
	fout<<"-";
	fout<<"|"<<endl;
	for(int i=1;i<=t;i++)
	fout<<" ";
	fout<<"|";
	fout<<s;
	if(M[10]>0 || ch=='N') s+="N",fout<<" NewLine ";
	if(M[9]>0 || ch=='N') s+="T",fout<<" Tab ";
	if(M[13]>0 || ch=='N') s+="R",fout<<" Return-Cursor ";
	fout<<"|"<<endl<<endl<<"> Number of hidden symbols: "<<256-s.length()<<endl;
	return;
}
int main(){
	string infname;
	string outfname;
	cout<<"Input input file name: ";
	cin>>infname;
	ifstream fin(infname);
	if(!fin){
		cout<<"Can't open file "<<infname<<endl;
		return 31;
	}
	cout<<"Input output file name: ";
	cin>>outfname;
	ofstream fout(outfname);
	if(!fout){
		fin.close();
		cout<<"Can't write to file "<<outfname<<endl;
		return 33;
	}
	int M[256]={0};
	int k;
	while((k=fin.get())!=EOF){
		M[k]++;
	}
	int mx=0,mn=0;
	for(int i=0;i<256;i++){
		if(M[i]>mx) mx=M[i];
		if(M[i]==0) mn++;
	}
	char ans;
	if(mn>0){
		do{
			cout<<"Hide characters with zero values?[Y/N]: ";
			cin>>ans;
		}while(ans!='Y' && ans!='N');
	}
	output(fout,M,mx,(mn>0)? ans:'N');
	fin.close();
	fout.close();
	return 0;
}
