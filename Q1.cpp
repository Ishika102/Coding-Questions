#include <iostream> 
using namespace std;  
  
struct Point 
{ 
    double x; 
    double y; 
}; 

int checkOrientation(Point A, Point B, Point C) //Checks the orintation of the point {collinear , clockwise , anticlockwise}
{ 
    int result = (B.y - A.y) * (C.x - B.x) - (B.x - A.x) * (C.y - B.y); 
  
    if (result == 0) 
    return 0;  // colinear 
    else if(result>0)
    return 1;  //clockwise
    else
    return 2; //anticlockwise
} 

int check(Point A, Point B, Point C)  //Check collinearity of point
{ 
    if (B.x <= max(A.x, C.x) && B.x >= min(A.x, C.x) ) 
    {
        if(B.y <= max(A.y, C.y) && B.y >= min(A.y, C.y)) 
        return 1;
        return 0;
    }
    return 0; 
} 
  
 
bool checkIntersection(Point A1, Point B1, Point A2, Point B2) 
{ 
    int first = checkOrientation(A1, B1, A2); 
    int second = checkOrientation(A1, B1, B2); 
    int third = checkOrientation(A2, B2, A1); 
    int fourth = checkOrientation(A2, B2, B1); 
  
    if (first != second && third != fourth) //Simple case
        return true; 
    if (first == 0 && check(A1, B1, A2)) // A2 lies on A1B1 
    return true; 
    if (second== 0 && check(A1, B1, B2))   //B2 lies on A1B1
    return true; 
    if (third == 0 && check(A2, B2,A1)) //A1 lies on A2B2
    return true; 
    if (fourth == 0 && check(A2, B2 ,B1)) //B1 lies on A2B2 
    return true; 
  
    return false; 
} 
   
bool findLocation(Point polygon[], int n, Point toCheck) 
{ 
    Point horizontal = {10000, toCheck.y}; //Created a point for drawing horizontal segment
    int count = 0, i = -1; 
    while(i!=0)
    { 
        if(i==-1)
        i = 0;
        int j = (i+1)%n; 
        if (checkIntersection(polygon[i], polygon[j], toCheck, horizontal)) //check the intersection of point  with edges of the polygon
        {
            if (checkOrientation(polygon[i], toCheck, polygon[j]) == false) //check collinearity of point with any of the vertex of polygon
               return check(polygon[i], toCheck, polygon[j]); 
            count++; 
        } 
        i = j; 
    }
    if(count%2==0) //no of intersections if even
    return false;
    return true;
} 
  
int main() 
{ 
    Point polygon[] = {{0, 0}, {10.5, 0}, {10.5, 10}, {0, 10}}; 
    int n = 4; 
    Point toCheck = {0,0}; 
	if (n < 3)  //Polygon is always formed by atmost three points
	{
		cout<<"False"<<endl;
		return 0;
	}
    if(findLocation(polygon, n, toCheck))
    cout << "true"<<endl;
    else
    cout << "false"<<endl;
}