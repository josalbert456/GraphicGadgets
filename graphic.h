#ifndef __GRAPHIC__
#define __GRAPHIC__
#include <Box2D/Box2D.h>
#include <iostream>
#include <vector>
#include "Canvas.h"
using namespace std;

// all the algorithms will be done 
// when we converted to the mathematical axis, that is,
// up and right is positive
// after the calculation done, the y_axis will be converted back
// to the computer axis, that is down and right positive
#define CONVERT_Y_AXIS(y) 	y=-y

inline float calcDistance(b2Vec2 start, b2Vec2 end){
	// Unnecessary to convert axis
	return sqrt(pow(end.x - start.x, 2) + pow(end.y - start.y, 2));
}

inline b2Vec2 calcLineParameter(b2Vec2 start, b2Vec2 end){
	CONVERT_Y_AXIS(start.y);
	CONVERT_Y_AXIS(end.y);
	b2Vec2 result;
	result.x = (start.y - end.y) / (start.x - end.x);
	result.y = start.y - result.x * start.x;
	return result;
}

inline float calcParalellKValue(b2Vec2 originLine, b2Vec2 point){
	CONVERT_Y_AXIS(point.y);
	float y = point.y - originLine.x * point.x;
	CONVERT_Y_AXIS(y);
	return y;
}
inline b2Vec2 findCross(b2Vec2 originLine, b2Vec2 point){
	CONVERT_Y_AXIS(point.y);
	float angle = tan(atan(originLine.x) + b2_pi/2);
	float kValue = point.y - point.x * angle;
	float crossX = (originLine.y - kValue) / (angle - originLine.x);
	float crossY = crossX * originLine.x + originLine.y;
	//crossY = -crossY;
	CONVERT_Y_AXIS(crossY);
	return b2Vec2(crossX, crossY);
}

class graphic{
public:
	vector<b2Vec2>points;
	vector<int>upperPoints;
	vector<int>lowerPoints;
	vector<int>overPoints;
	void addPoint(b2Vec2 point){
		points.push_back(point);
	}
	void setPoint(int index, b2Vec2 point){
		points.at(index).x = point.x;
		points.at(index).y = point.y;
	}
	void findParalellKValues(){
		b2Vec2 startLine = calcLineParameter(points.at(0), points.at(1));
		std::cout << "L Value: " << startLine.y << std::endl;
		for(int i=2; i<points.size(); i++){
			float kValue =  calcParalellKValue(startLine, points.at(i));
			std::cout << "L Values: " << kValue << std::endl;
		}
		b2Vec2 endLine = calcLineParameter(points.at(0), points.at(points.size() - 1));
		std::cout << "L Value: " << endLine.y << std::endl;

	}
	void sortPoints(Canvas *canvas){
		b2Vec2 startLine = calcLineParameter(points.at(0), points.at(1));
		for(int i=2; i<points.size(); i++){
			b2Vec2 cross = findCross(startLine, points.at(i));
			//float distance = calcDistance(cross, points.at(i));
			//std::cout << distance << std::endl;
			canvas->drawLine(cross, points.at(i));
		}		
	}
	void draw(Canvas *canvas){
		
		for(int i=0; i<points.size()-1; i++){
			canvas->drawLine(points.at(i), points.at(i+1));
		}
		canvas->drawLine(points.at(points.size() - 1), points.at(0));
	}
};


#endif