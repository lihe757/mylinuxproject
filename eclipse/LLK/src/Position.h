/*
 * Point.h
 *
 *  Created on: 2010-3-18
 *      Author: lhx
 */

#ifndef POINT_H_
#define POINT_H_
namespace Pos {
static const int Positive=1;//正
static const int Negative=-1;//负
static const int NORTH=4;//北
static const int SOUTH=2;//南
static const int EAST=1;//东
static const int WEST=3;//西
/**
 * 记录在数组中的位置
 */
struct Position {
	int r;
	int c;
};

/**
 * 同行判断
 */
inline bool isSameRow(const Position &p1, const Position &p2) {
	return p1.r == p2.r ? true : false;
}
/**
 * 同列判断
 */
inline bool isSameColum(const Position &p1, const Position &p2) {
	return p1.c == p2.c ? true : false;
}
/**
 * 求行距相对值
 */
inline int rowDistance(const Position &p1, const Position &p2) {
	return p1.r - p2.r;

}
/**
 * 求列距相对值
 */
inline int columDistance(const Position &p1, const Position &p2) {
	return  p1.c - p2.c;

}

}
#endif /* POINT_H_ */
