#include<iostream>
#include<vector>
#include<cfloat>
#include<climits>
using namespace std;

struct Point{//Represents the points of the line 
  double x;
  double y;
};

struct building{//Represents Coordinates of the building
	double xleftbottom,yleftbottom;  
	double xlefttop,ylefttop;
	double xrightbottom,yrightbottom;
	double xrighttop,yrighttop;
};

Point lineLineIntersection(Point A, Point B, Point C, Point D)//finds intersection between two points
{ 
    //Equation of line joining Point A and Point B 
    double a1 = B.y - A.y; 
    double b1 = A.x - B.x; 
    double c1 = a1*(A.x) + b1*(A.y); 
  
    //Equation of line joining Point C and Point D 
    double a2 = D.y - C.y; 
    double b2 = C.x - D.x; 
    double c2 = a2*(C.x)+ b2*(C.y); 
  
   //Calculating determinant determined by the two lines
    double determinant = a1*b2 - a2*b1; 
  
    if (determinant == 0) //Condition for parallel lines
    { 
        return {FLT_MAX, FLT_MAX}; 
    } 
    else
    { 
        double x = (b2*c1 - b1*c2)/determinant; 
        double y = (a1*c2 - a2*c1)/determinant; 
        return {x, y}; //Intersection Point
    } 
} 
int main()
{
	int n;
	cin>>n;
	building arr[n];
	for(int i=0;i<n;i++){
	     cin>>arr[i].xlefttop;
		 cin>>arr[i].ylefttop;
		 
		 cin>>arr[i].xleftbottom;
		 cin>>arr[i].yleftbottom;
		
		 cin>>arr[i].xrightbottom;
		 cin>>arr[i].yrightbottom;
		 
		 cin>>arr[i].xrighttop;
		 cin>>arr[i].yrighttop;
	}
	
	double xpos , ypos; //coordiantess of the sun
	cin>>xpos>>ypos;
	
	vector<double>top(n,0); 

	vector<double>height(n,0);

	vector<double>left(n,0);

	for(int i = 0;i<n;i++){ //finding the building whose top will be getting sunlight
		if(ypos>arr[i].ylefttop)//trivial condition that sun will be at height greater than that of all the building
		top[i] = (arr[i].xrighttop - arr[i].xlefttop);
	}
	
	for(int i = 0;i<n;i++){//calculating height of each building
		height[i] = arr[i].ylefttop  - arr[i].yleftbottom;
	}
	
	double maximum = 0;
	for(int i = 0;i<n;i++){ //calculating which building left will receive the sunlight
		if(height[i] >maximum && xpos<arr[i].xlefttop)
		{
			left[i] = height[i]-left[i-1];
			maximum = height[i];
		}
	//	cout<<left[i]<<" ";
	}
	
	double sum = 0;
	
	for(int i = 0;i<n;i++)//summation of the surfaces where sunlight will fall
	    sum = sum + top[i]+left[i];
	//Assuming sun is present in the left side of all buidings
	//draw line from (xpos ,ypos) and (xrightbottom , yrightbottom) 
	//see the building from right side 
	//covering all the building starting from the left side
	//intersecting the y line of the building 
	for(int i = 0;i<n;i++)
	{
	     for(int j = i+1;j<n;j++)
	     {
	             Point A = {xpos,ypos};
	             Point B = {arr[i].xrighttop,arr[i].yrighttop};
	             Point C = {arr[j].xlefttop,arr[j].ylefttop};
	             Point D = {arr[j].xleftbottom,arr[j].yleftbottom};
	             Point intersection;
	             intersection =lineLineIntersection(A,B,C,D);
				  int h = arr[j].ylefttop- intersection.y;
	             if (intersection.x == FLT_MAX && intersection.y==FLT_MAX)
	             continue;
	             if(h<0||h>height[j])
				 continue;
	             sum = sum + height[j] - h;
	             break;
	     }
	}
	cout<<sum<<endl;
}