/*
 * Point.h
 *
 *  Created on: 2010-3-18
 *      Author: lhx
 */

#ifndef POINT_H_
#define POINT_H_
namespace Pos {
static const int Positive=1;//��
static const int Negative=-1;//��
static const int NORTH=4;//��
static const int SOUTH=2;//��
static const int EAST=1;//��
static const int WEST=3;//��
/**
 * ��¼�������е�λ��
 */
struct Position {
	int r;
	int c;
};

/**
 * ͬ���ж�
 */
inline bool isSameRow(const Position &p1, const Position &p2) {
	return p1.r == p2.r ? true : false;
}
/**
 * ͬ���ж�
 */
inline bool isSameColum(const Position &p1, const Position &p2) {
	return p1.c == p2.c ? true : false;
}
/**
 * ���о����ֵ
 */
inline int rowDistance(const Position &p1, const Position &p2) {
	return p1.r - p2.r;

}
/**
 * ���о����ֵ
 */
inline int columDistance(const Position &p1, const Position &p2) {
	return  p1.c - p2.c;

}

}
#endif /* POINT_H_ */
