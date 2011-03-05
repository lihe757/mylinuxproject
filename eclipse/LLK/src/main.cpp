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
 * �ɴ�Խ�жϺ���
 * ˵��:���������Ԫ�ص���0�������ɴ�Խ
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
	/*5*5��ͼ���飬0����գ���ֱ��ͨ��������Ϊ�ϰ�*/
	int a2[rows][colums] = {
			{ 6, 0, 0, 0, 0 },
			{ 1, 2, 3, 2, 7 },
			{ 0, 4, 0, 0, 4 },
			{ 0, 6, 0, 0, 5 },
			{ 5, 0, 0, 0, 0 }
	};
	/*����һ����λ�������*/
	Array2D<int> array_int = { rows, colums, &(a2[0][0]) };
	/*�ڶ�λ�����������LLK·��������*/
	LLKPathFinder<int> llkf(array_int, funTest);


	/**
	 * ˫ֱ�ǲ���:2-2����
	 */
	Position p1 = { 1, 1 };
	Position p2 = { 1, 3 };
	cout<<""<<llkf.find(p1,p2)<<endl;

	/**
	 * ֱ�߲���:4-4����
	 */
//	Position p1 = { 2, 1 };
//	Position p2 = { 2, 4 };
//	cout<<""<<llkf.find(p1,p2)<<endl;

	/**
	 * ֱ�ǲ���:5-5����
	 */
//	Position p1={3,4};
//	Position p2={4,1};
//	cout<<""<<llkf.find(p1,p2)<<endl;

	/**
	 * ����ͨ����:6-6����
	 */
//	Position p1={0,0};
//	Position p2={3,1};
//	cout<<""<<llkf.find(p1,p2)<<endl;




}
