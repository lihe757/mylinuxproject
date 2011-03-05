/*
 * main.cpp
 *
 *  Created on: 2010-3-18
 *  Edited on: 2010-10-7
 *      Author: lhx
 */
#include "Position.h"
#include "Array2D.h"
#include "LLKPathFinder.h"
#include <iostream>
#include <stack>

using std::cout;
using std::endl;
using Pos::Position;
using ary2d::Array2D;
using llk::LLKPathFinder;
/**
 * 可穿越判断函数
 * 说明:如果该数组元素等于0，则代表可穿越
 */
bool funTest(int* data) {
	if ((*data) == 0) {
		return true;
	}
	return false;

}
int main(int argc, char **argv) {
	const size_t rows = 5;
	const size_t colums = 5;
	/*5*5地图数组，0代表空，可直接通过，否则为障碍*/
	int a2[rows][colums] = {
			{ 6, 0, 0, 0, 0 },
			{ 1, 2, 3, 2, 7 },
			{ 0, 4, 0, 0, 4 },
			{ 0, 6, 0, 0, 5 },
			{ 5, 0, 0, 0, 0 }
	};
	/*生成一个二位数组对象*/
	Array2D<int> array_int = { rows, colums, &(a2[0][0]) };
	/*在二位数组对象生成LLK路径查找器*/
	LLKPathFinder<int> llkf(array_int, funTest);


	/**
	 * 双直角测试:2-2连线
	 */
	Position p1 = { 1, 1 };
	Position p2 = { 1, 3 };
	cout<<""<<llkf.find(p1,p2)<<endl;

	/**
	 * 直线测试:4-4连线
	 */
//	Position p1 = { 2, 1 };
//	Position p2 = { 2, 4 };
//	cout<<""<<llkf.find(p1,p2)<<endl;

	/**
	 * 直角测试:5-5连线
	 */
//	Position p1={3,4};
//	Position p2={4,1};
//	cout<<""<<llkf.find(p1,p2)<<endl;

	/**
	 * 连不通测试:6-6连线
	 */
//	Position p1={0,0};
//	Position p2={3,1};
//	cout<<""<<llkf.find(p1,p2)<<endl;




}
