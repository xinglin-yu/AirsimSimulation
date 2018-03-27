#pragma once

#ifndef _MATRIX_H  
#define _MATRIX_H  

//头文件  
#include <stdio.h>  
#include <stdlib.h>  

//矩阵数据结构  
//二维矩阵  
class _Matrix
{
private:
public:
	int m;
	int n;
	float *arr;

	//初始化  
	_Matrix(int mm = 0, int nn = 0);
	//设置m  
	void set_m(int mm);
	//设置n  
	void set_n(int nn);
	//初始化  
	void init_matrix();
	//释放  
	void free_matrix();
	//读取i,j坐标的数据  
	//失败返回-31415,成功返回值  
	float read(int i, int j);
	//写入i,j坐标的数据  
	//失败返回-1,成功返回1  
	int write(int i, int j, float val);
};

//二维运算类  
class _Matrix_Calc
{
private:
public:
	_Matrix_Calc();
	//C = A + B  
	//成功返回1,失败返回-1  
	int add(_Matrix *A, _Matrix *B, _Matrix *C);
	//C = A - B  
	//成功返回1,失败返回-1  
	int subtract(_Matrix *A, _Matrix *B, _Matrix *C);
	//C = A * B  
	//成功返回1,失败返回-1  
	int multiply(_Matrix *A, _Matrix *B, _Matrix *C);
	//行列式的值,只能计算2 * 2,3 * 3  
	//失败返回-31415,成功返回值  
	float _Matrix_Calc::det(_Matrix *A);
	//求转置矩阵,B = AT  
	//成功返回1,失败返回-1  
	int transpos(_Matrix *A, _Matrix *B);
	//求逆矩阵,B = A^(-1)  
	//成功返回1,失败返回-1  
	int inverse(_Matrix *A, _Matrix *B);
};

#endif  










