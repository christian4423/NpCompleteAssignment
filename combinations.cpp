// combinations.cpp : CSE830 Term Project, brute force version
//
//Micky Badgero
//April 7, 2003

#include <cassert>
#include <cfloat>
#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include <time.h>

using namespace std;

#define MAX 10

void recurse(int A[], int B[], int i, int j);
void increment(int A[], int B[], int i, int j);

void main(int argc, char* argv[])
{
	double seconds; // run time seconds
	int A[MAX];
	int B[MAX];
	int i;
	//int j;
	int k;
	int n;
	int minutes;

	ofstream out;
	out.open("combinations.txt");

	for (i=0; i<MAX; i++)
	{
		A[i]=0;
		B[i]=0;
	}

	//test the recursive table generator

	clock_t start,stop;
	start=clock();

	i=4;
	recurse(A,B,i,i-1);

	stop=clock();
	seconds=stop-start;
	seconds=seconds/CLOCKS_PER_SEC;
	cout << "\n";
	minutes=(int)(seconds/60);
	seconds=seconds-(double)(minutes*60);
	cout << "Run time: " << minutes << ":";
	if(seconds/10<1) cout << "0";
	cout << seconds << "\n";

	cout << "\n\n";
	for(i=0; i<MAX; i++)
		cout << " " << A[i];
		B[i]=0;
	cout << "\n\n";


	//test the increment function
	A[0]=3;
	A[1]=2;
	A[2]=1;
	A[3]=0;
	A[4]=0;
	A[5]=0;
	A[6]=0;
	A[7]=0;
	A[8]=0;
	A[9]=0;

	n=4;
	for(k=0; k<60; k++)
	{
		//clear the B array
		for (i=0; i<MAX; i++)
			B[i]=0;

		increment(A,B,n,n-1);

		//cout << "\n\n";
		//for(i=0; i<MAX; i++)
		//cout << " " << A[i];
		//cout << "  A[]\n";

		for(i=0; i<n; i++)
			B[A[i]]=i+1;
		for(i=0; i<MAX; i++)
			cout << " " << B[i];
		cout << "\n";
	}

}


// recursive program to output combinations of selections of size i
void recurse(int A[], int B[], int i, int j)
{
	int n;

	i--;

	if(i==0)
	{
		for(A[i]=A[i+1]+1; A[i]<MAX-i; A[i]++)
		{
			B[A[i]]=1;
			for(n=0; n<MAX; n++)
				cout << " " << B[n];
			cout << "\n";
			B[A[i]]=0;
		}
	}
	else if(i==j)
	{
		for(A[i]=0; A[i]<MAX-i; A[i]++)
		{
			B[A[i]]=i+1;
			recurse(A,B,i,j);
			B[A[i]]=0;
		}
	}
	else 
	{
		for(A[i]=A[i+1]+1; A[i]<MAX-i; A[i]++)
		{
			B[A[i]]=i+1;
			recurse(A,B,i,j);
			B[A[i]]=0;
		}
	}
	i++;
}

// recursive program to output combinations of selections of size i
void increment(int A[], int B[], int i, int j)
{
	//int n;

	i--;
	if(i==0)
	{
		A[i]++;
		if(A[i]<MAX-i) 
		{}
		else
		{
			A[i+1]++;
			A[i]=A[i+1]+1;
		}
	}
	else if(i==j)
	{
		if(A[i]<MAX-i) 
			increment(A,B,i,j);
		else
			A[i]=0;
	}
	else
	{
		if(A[i]<MAX-i) 
			increment(A,B,i,j);
		else
		{
			A[i+1]++;
			A[i]=A[i+1]+1;
		}
	}
	i++;
}


