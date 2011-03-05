/*
 * Array2D.h
 *
 *  Created on: 2010-3-24
 *      Author: lhx
 */

#ifndef ARRAY2D_H_
#define ARRAY2D_H_

namespace ary2d {
/**
 * 一个简单的二位数组类
 */
template<typename T>
struct Array2D {
	int maxrow;
	int maxcolum;
	T* data;
};

template<typename T>
/**
 * 根据行列参数获得数组中的元素
 */
inline T* getData(const int r, const int c, const Array2D<T> &array2d) {
	if ((r >= 0 && array2d.maxrow > r) && (c >= 0 && array2d.maxcolum > c)) {
		return array2d.data + (r * array2d.maxcolum) + c;
	}
	return 0;

}

}

#endif /* ARRAY2D_H_ */
