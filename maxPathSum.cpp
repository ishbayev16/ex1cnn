#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <sstream>

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
					if (tri[i+1][j] > tri[i+1][j+1]){

						tri[i][j] += tri[i+1][j]; 
					}
					else{
						tri[i][j] += tri[i+1][j+1];
					}
			}			
		}
	} 
	return tri[0][0]; 
} 

//string split(const string& str, const string& delim){
//	string token;
//	size_t prev = 0, pos = 0;
//	pos = str.find(delim, prev);
//	token = str.substr(prev, pos);
//	return token;
//}//split


int main() 
{ 	
	ifstream file ("inputmatrix.txt");
	string row;
	int numrow = 0;
	int numcol = 0; 
	int value=0;
	istringstream iss;

	//gets num rows
	while(getline(file,row)){
		numrow++;
	}
		
	iss.str(row);
	while(row.length()!=0){
		string val;
		iss >> val;
		int start_position_to_erase = row.find(val);
		int end_position = val.length();
		row.erase(start_position_to_erase,end_position+1);
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
		istringstream iss1;
		iss1.str(row);
		while(row.length()!=0){
			string val;
			iss1 >> val;
			int start_position_to_erase = row.find(val);
			int end_position = val.length();
			row.erase(start_position_to_erase,end_position+1);
			value = stoi(val);
			if(!isPrime(value)){
				arr[temprow][tempcol]=value;
			}
			tempcol++;
		}
		temprow++;
		tempcol=0;
	}
	
	printm(arr,numrow,numcol);
	cout<<"result is: "<<maxPathSum(arr, numrow-1, numcol-1)<<endl;						
	return 0; 
}
