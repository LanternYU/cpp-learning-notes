#include<iostream>
#include<cmath>
#include "coordin.h"
using namespace std;
polar rect_to_polar(rect xypos){
	polar answer;
	answer.distance=
		sqrt(xypos.x*xypos.x+xypos.y*xypos.y);
	answer.angle = atan2(xypos.x,xypos.y);
	return answer;
}

void show_pplar(polar dapos){
	const double rad_to_deg=57.29577951;
	cout<< "distance = "<<dapos.distance;
	cout<< "angle = "<<dapos.angle*rad_to_deg;
}	cour <<"degree\n";
