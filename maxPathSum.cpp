#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std; 

bool isPrime(int n){ 
	if (n <= 1)
		return false; 
	for (int i = 2; i < n; i++) 
		if (n % i == 0)
			return false;
	return true;
}
	
void printm(int** tri, int m, int n){
	for(int i=0;i<m;i++){
		cout<<i+1<<" ";
		for(int j=0;j<n;j++){
			cout<<setw(4)<<tri[i][j]<<" ";
		}
		cout<<endl;	
	}
}	

int maxPathSum(int** tri, int m, int n){
	int maxx; 	
	for (int i=m-1; i>=0; i--){ 
		for (int j=0; j<=i; j++){
			if((tri[i+1][j]==0)&&(tri[i+1][j+1]==0)){
				tri[i][j]=0;
			}
			if(tri[i][j]!=0){
//				if(j==0){
					if (tri[i+1][j] > tri[i+1][j+1]){

						tri[i][j] += tri[i+1][j]; 
					}
					else{
						tri[i][j] += tri[i+1][j+1];
					}
//				}else{
//					maxx = max(tri[i+1][j-1],tri[i+1][j]);
//					maxx = max(maxx,tri[i+1][j+1]);
//					tri[i][j] += maxx;
//				}
			}			
		}
	} 
	return tri[0][0]; 
} 

string split(const string& str, const string& delim){
	string token;
	size_t prev = 0, pos = 0;
	pos = str.find(delim, prev);
	token = str.substr(prev, pos);
	return token;
}//split


int main() 
{ 	
	ifstream file ("inputmatrix.txt");
	string row,ivalue;
	int numrow = 0;
	int numcol = 0; 
	int pos=1;
	int value=0;
	//gets num rows
	while(getline(file,row)){
		numrow++;
	}
		

	//according to last row decides number of columns
	while(row!=""){
		ivalue=split(row," ");
		pos = row.find("",pos);
		row.erase(0,pos+3);
		numcol++;
	}
	//creates multidimentional array with each element 0
	int **arr;
	arr = new int *[numrow];
	for(int i=0;i<numrow;i++){
		arr[i]= new int[numcol];
		for(int j=0;j<numcol;j++){
			arr[i][j]=0;
		}	
	}
	//return to beginning of file
	file.clear();
	file.seekg(0, ios::beg);
	int temprow=0;
	int tempcol=0;
	while(getline(file,row)){
		while(row!=""){
			ivalue=split(row," ");
			pos = row.find("",pos);
			row.erase(0,pos+3);
			//splits each value, change type to int and assigns to corresponding coordinate from arrray 
			//if not prime
			value = stoi(ivalue);
			if(!isPrime(value)){
				arr[temprow][tempcol]=value;
			}
			tempcol++;
		}
		temprow++;
		tempcol=0;
	}

	cout<<"result is: "<<maxPathSum(arr, numrow-1, numcol-1)<<endl;						
	return 0; 
}
