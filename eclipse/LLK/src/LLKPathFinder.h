/*
 * LLKPathFinder.h
 *
 *  Created on: 2010-3-26
 *  Edited on: 2010-10-7
 *      Author: lhx
 */

#ifndef LLKPATHFINDER_H_
#define LLKPATHFINDER_H_
#include "Position.h"
#include "Array2D.h"
#include <stack>
#include <iostream>
using namespace std;
using std::stack;
using ary2d::Array2D;
using Pos::Position;
namespace llk {

template<class T>
class LLKPathFinder {
	//��Խ�����жϺ���ָ��
	typedef bool (*CROSSABLE_CONDTION_FUNC)(T* data);
public:
	LLKPathFinder(const Array2D<T> &_array, CROSSABLE_CONDTION_FUNC func);
	virtual ~LLKPathFinder();

	bool find(Position p1, Position p2);
private:
	stack<Position> pathNodes;
	bool canConnect;
	const Array2D<T> *array;
	CROSSABLE_CONDTION_FUNC m_CrossableFunction;
	//���·��ջ
	void clearStack(stack<Position> &stak) {
		while (!stak.empty()) {
			stak.pop();
		}
	}
	//��ӡ·��ջ
	void printStack(stack<Position> &stak) {
		while (!stak.empty()) {
			cout << "Pos( " << stak.top().r << " , " << stak.top().c << " )"
					<< endl;
			stak.pop();
		}
	}
protected:
	/**
	 * ͬһֱ�߼��
	 */
	bool _sameLineCheck(const Position &p1, const Position &p2,
			const Array2D<T> &array);
	/**
	 * ���սǼ��
	 */
	bool _oneCornerCheck(const Position &p1, const Position &p2, const Array2D<
			T> &array);
	/**
	 * ˫�սǼ��
	 */
	bool _towCornerCheck(const Position &p1, const Position &p2, const Array2D<
			T> array);

};

}

template<class T> llk::LLKPathFinder<T>::LLKPathFinder(
		const Array2D<T> & _array, CROSSABLE_CONDTION_FUNC func) {
	array = &_array;
	m_CrossableFunction = func;
}

template<class T> llk::LLKPathFinder<T>::~LLKPathFinder() {
	delete array;
	array = 0;
}

template<class T> bool llk::LLKPathFinder<T>::find(Position p1, Position p2) {
	cout << "Finding road!" << endl;
	clearStack(pathNodes);//���
	pathNodes.push(p1);
	while (true) {
		canConnect = _sameLineCheck(p1, p2, *array);//��ͬһ������
		if (canConnect)
			break;
		canConnect = _oneCornerCheck(p1, p2, *array);//��һ���ս�
		if (canConnect)
			break;
		canConnect = _towCornerCheck(p1, p2, *array);//�������ս�
		break;

	}
	if (canConnect) {
		cout << "Path was found!" << endl;
		pathNodes.push(p2);
		printStack(pathNodes);
	} else {
		cout << "Path was not found!" << endl;
	}

	return canConnect;
}

template<class T> bool llk::LLKPathFinder<T>::_sameLineCheck(
		const Position & p1, const Position & p2, const Array2D<T> & array) {
	int absDist = 0;//���Ծ���
	int signl = Pos::Positive;//�����ţ�����ָ������
	int spaceCount = 0;
	if (Pos::isSameRow(p1, p2)) {//ͬ��
		//���о�
		absDist = Pos::columDistance(p1, p2);
		if (absDist == 0)
			return true;
		signl = absDist > 0 ? Pos::Negative : signl;
		absDist = absDist > 0 ? absDist : (absDist * (-1));
		for (int i = 1; i < absDist; i++) {
			//�ж�
			if (m_CrossableFunction(ary2d::getData(p1.r, p1.c + (i * signl),
					array))) {
				spaceCount += 1;
			}
		}
		absDist--;
		return (absDist == spaceCount);
	} else if (Pos::isSameColum(p1, p2)) {//ͬ��
		//���о�
		absDist = Pos::rowDistance(p1, p2);
		if (absDist == 0)
			return true;
		signl = absDist > 0 ? Pos::Negative : signl;
		absDist = absDist > 0 ? absDist : (absDist * (-1));
		for (int i = 1; i < absDist; i++) {

			//�ж�
			if (m_CrossableFunction(ary2d::getData(p1.r + (i * signl), p1.c,
					array))) {
				spaceCount += 1;
			}

		}
		absDist--;
		return (absDist == spaceCount);
	}
	return false;
}

template<class T> bool llk::LLKPathFinder<T>::_oneCornerCheck(
		const Position & p1, const Position & p2, const Array2D<T> & array) {
	Position firstCheckPos = { p1.r, p2.c };
	Position secondCheckPos = { p2.r, p1.c };
	bool isCrossable = false;
	if (m_CrossableFunction(ary2d::getData(firstCheckPos.r, firstCheckPos.c,
			array))) {

		//��һ�սǼ��
		isCrossable = _sameLineCheck(p1, firstCheckPos, array)
				&& _sameLineCheck(firstCheckPos, p2, array);
		if (isCrossable) {
			pathNodes.push(firstCheckPos);
		}
		return isCrossable;

	}
	if (m_CrossableFunction(ary2d::getData(secondCheckPos.r, secondCheckPos.c,
			array))) {
		//�ڶ����սǼ��
		isCrossable = _sameLineCheck(p1, secondCheckPos, array)
				&& _sameLineCheck(secondCheckPos, p2, array);
		if (isCrossable) {
			pathNodes.push(secondCheckPos);
		}
		return isCrossable;
	}

	return false;
}

template<class T> bool llk::LLKPathFinder<T>::_towCornerCheck(
		const Position & p1, const Position & p2, const Array2D<T> array) {//����
	Position checkPos = { p1.r, p1.c };
	for (int direction = 1; direction <= 4; direction++) {
		checkPos.r = p1.r;
		checkPos.c = p1.c;
		switch (direction) {
		case Pos::EAST: {
			checkPos.c++;
			while ((checkPos.c < array.maxcolum) && m_CrossableFunction(
					ary2d::getData(checkPos.r, checkPos.c, array))) {
				pathNodes.push(checkPos);
				if (_oneCornerCheck(checkPos, p2, array)) {
					return true;
				} else {
					pathNodes.pop();
				}
				checkPos.c++;
			}
		}
			break;
		case Pos::WEST: {
			checkPos.c--;
			while ((checkPos.c >= 0) && m_CrossableFunction(ary2d::getData(
					checkPos.r, checkPos.c, array))) {
				pathNodes.push(checkPos);
				if (_oneCornerCheck(checkPos, p2, array)) {
					return true;
				} else {
					pathNodes.pop();
				}
				checkPos.c--;
			}
		}
			break;
		case Pos::NORTH: {
			checkPos.r--;
			while ((checkPos.r >= 0) && m_CrossableFunction(ary2d::getData(
					checkPos.r, checkPos.c, array))) {
				pathNodes.push(checkPos);
				if (_oneCornerCheck(checkPos, p2, array)) {
					return true;
				} else {
					pathNodes.pop();
				}
				checkPos.r--;
			}
		}
			break;
		case Pos::SOUTH: {
			checkPos.r++;
			while ((checkPos.r < array.maxrow) && m_CrossableFunction(
					ary2d::getData(checkPos.r, checkPos.c, array))) {
				pathNodes.push(checkPos);
				if (_oneCornerCheck(checkPos, p2, array)) {
					return true;
				} else {
					pathNodes.pop();
				}
				checkPos.r++;
			}
		}

		}
	}
	return false;
}

#endif
