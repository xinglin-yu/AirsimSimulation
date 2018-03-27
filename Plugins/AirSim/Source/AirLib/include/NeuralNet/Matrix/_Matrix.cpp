#include "_Matrix.h"  

//矩阵类方法  
//初始化  
_Matrix::_Matrix(int mm, int nn)
{
	m = mm;
	n = nn;
}

//设置m  
void _Matrix::set_m(int mm)
{
	m = mm;
}

//设置n  
void _Matrix::set_n(int nn)
{
	n = nn;
}

//初始化  
void _Matrix::init_matrix()
{
	arr = new float[m * n];
}

//释放  
void _Matrix::free_matrix()
{
	delete[]arr;
}

//读取i,j坐标的数据  
//失败返回-31415,成功返回值  
float _Matrix::read(int i, int j)
{
	if (i >= m || j >= n)
	{
		return -31415;
	}

	return *(arr + i * n + j);
}

//写入i,j坐标的数据  
//失败返回-1,成功返回1  
int _Matrix::write(int i, int j, float val)
{
	if (i >= m || j >= n)
	{
		return -1;
	}

	*(arr + i * n + j) = val;
	return 1;
}

//矩阵运算类方法  
//初始化  
_Matrix_Calc::_Matrix_Calc()
{
}

//C = A + B  
//成功返回1,失败返回-1  
int _Matrix_Calc::add(_Matrix *A, _Matrix *B, _Matrix *C)
{
	int i = 0;
	int j = 0;

	//判断是否可以运算  
	if (A->m != B->m || A->n != B->n || \
		A->m != C->m || A->n != C->n)
	{
		return -1;
	}
	//运算  
	for (i = 0; i < C->m; i++)
	{
		for (j = 0; j < C->n; j++)
		{
			C->write(i, j, A->read(i, j) + B->read(i, j));
		}
	}

	return 1;
}

//C = A - B  
//成功返回1,失败返回-1  
int _Matrix_Calc::subtract(_Matrix *A, _Matrix *B, _Matrix *C)
{
	int i = 0;
	int j = 0;

	//判断是否可以运算  
	if (A->m != B->m || A->n != B->n || \
		A->m != C->m || A->n != C->n)
	{
		return -1;
	}
	//运算  
	for (i = 0; i < C->m; i++)
	{
		for (j = 0; j < C->n; j++)
		{
			C->write(i, j, A->read(i, j) - B->read(i, j));
		}
	}

	return 1;
}

//C = A * B  
//成功返回1,失败返回-1  
int _Matrix_Calc::multiply(_Matrix *A, _Matrix *B, _Matrix *C)
{
	int i = 0;
	int j = 0;
	int k = 0;
	float temp = 0;

	//判断是否可以运算  
	if (A->m != C->m || B->n != C->n || \
		A->n != B->m)
	{
		return -1;
	}
	//运算  
	for (i = 0; i < C->m; i++)
	{
		for (j = 0; j < C->n; j++)
		{
			temp = 0;
			for (k = 0; k < A->n; k++)
			{
				temp += A->read(i, k) * B->read(k, j);
			}
			C->write(i, j, temp);
		}
	}

	return 1;
}

//行列式的值,只能计算2 * 2,3 * 3  
//失败返回-31415,成功返回值  
float _Matrix_Calc::det(_Matrix *A)
{
	float value = 0;

	//判断是否可以运算  
	if (A->m != A->n || (A->m != 2 && A->m != 3))
	{
		return -31415;
	}
	//运算  
	if (A->m == 2)
	{
		value = A->read(0, 0) * A->read(1, 1) - A->read(0, 1) * A->read(1, 0);
	}
	else
	{
		value = A->read(0, 0) * A->read(1, 1) * A->read(2, 2) + \
			A->read(0, 1) * A->read(1, 2) * A->read(2, 0) + \
			A->read(0, 2) * A->read(1, 0) * A->read(2, 1) - \
			A->read(0, 0) * A->read(1, 2) * A->read(2, 1) - \
			A->read(0, 1) * A->read(1, 0) * A->read(2, 2) - \
			A->read(0, 2) * A->read(1, 1) * A->read(2, 0);
	}

	return value;
}

//求转置矩阵,B = AT  
//成功返回1,失败返回-1  
int _Matrix_Calc::transpos(_Matrix *A, _Matrix *B)
{
	int i = 0;
	int j = 0;

	//判断是否可以运算  
	if (A->m != B->n || A->n != B->m)
	{
		return -1;
	}
	//运算  
	for (i = 0; i < B->m; i++)
	{
		for (j = 0; j < B->n; j++)
		{
			B->write(i, j, A->read(j, i));
		}
	}

	return 1;
}

//打印2维矩阵  
void printff_matrix(_Matrix *A)
{
	int i = 0;
	int j = 0;
	int m = 0;
	int n = 0;

	m = A->m;
	n = A->n;
	for (i = 0; i < m; i++)
	{
		for (j = 0; j < n; j++)
		{
			printf("%f ", A->read(i, j));
		}
		printf("\n");
	}
}

//求逆矩阵,B = A^(-1)  
//成功返回1,失败返回-1  
int _Matrix_Calc::inverse(_Matrix *A, _Matrix *B)
{
	int i = 0;
	int j = 0;
	int k = 0;
	_Matrix m(A->m, 2 * A->m);
	float temp = 0;
	float b = 0;

	//判断是否可以运算  
	if (A->m != A->n || B->m != B->n || A->m != B->m)
	{
		return -1;
	}

	/*
	//如果是2维或者3维求行列式判断是否可逆
	if (A->m == 2 || A->m == 3)
	{
	if (det(A) == 0)
	{
	return -1;
	}
	}
	*/

	//增广矩阵m = A | B初始化  
	m.init_matrix();
	for (i = 0; i < m.m; i++)
	{
		for (j = 0; j < m.n; j++)
		{
			if (j <= A->n - 1)
			{
				m.write(i, j, A->read(i, j));
			}
			else
			{
				if (i == j - A->n)
				{
					m.write(i, j, 1);
				}
				else
				{
					m.write(i, j, 0);
				}
			}
		}
	}

	//高斯消元  
	//变换下三角  
	for (k = 0; k < m.m - 1; k++)
	{
		//如果坐标为k,k的数为0,则行变换  
		if (m.read(k, k) == 0)
		{
			for (i = k + 1; i < m.m; i++)
			{
				if (m.read(i, k) != 0)
				{
					break;
				}
			}
			if (i >= m.m)
			{
				return -1;
			}
			else
			{
				//交换行  
				for (j = 0; j < m.n; j++)
				{
					temp = m.read(k, j);
					m.write(k, j, m.read(k + 1, j));
					m.write(k + 1, j, temp);
				}
			}
		}

		//消元  
		for (i = k + 1; i < m.m; i++)
		{
			//获得倍数  
			b = m.read(i, k) / m.read(k, k);
			//行变换  
			for (j = 0; j < m.n; j++)
			{
				temp = m.read(i, j) - b * m.read(k, j);
				m.write(i, j, temp);
			}
		}
	}
	//变换上三角  
	for (k = m.m - 1; k > 0; k--)
	{
		//如果坐标为k,k的数为0,则行变换  
		if (m.read(k, k) == 0)
		{
			for (i = k + 1; i < m.m; i++)
			{
				if (m.read(i, k) != 0)
				{
					break;
				}
			}
			if (i >= m.m)
			{
				return -1;
			}
			else
			{
				//交换行  
				for (j = 0; j < m.n; j++)
				{
					temp = m.read(k, j);
					m.write(k, j, m.read(k + 1, j));
					m.write(k + 1, j, temp);
				}
			}
		}

		//消元  
		for (i = k - 1; i >= 0; i--)
		{
			//获得倍数  
			b = m.read(i, k) / m.read(k, k);
			//行变换  
			for (j = 0; j < m.n; j++)
			{
				temp = m.read(i, j) - b * m.read(k, j);
				m.write(i, j, temp);
			}
		}
	}
	//将左边方阵化为单位矩阵  
	for (i = 0; i < m.m; i++)
	{
		if (m.read(i, i) != 1)
		{
			//获得倍数  
			b = 1 / m.read(i, i);
			//行变换  
			for (j = 0; j < m.n; j++)
			{
				temp = m.read(i, j) * b;
				m.write(i, j, temp);
			}
		}
	}
	//求得逆矩阵  
	for (i = 0; i < B->m; i++)
	{
		for (j = 0; j < B->m; j++)
		{
			B->write(i, j, m.read(i, j + m.m));
		}
	}
	//释放增广矩阵  
	m.free_matrix();

	return 1;
}
