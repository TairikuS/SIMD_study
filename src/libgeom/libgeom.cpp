// libgeom.cpp : スタティック ライブラリ用の関数を定義します。
//
#include "pch.h"
#include <intrin.h>
#include "../include/libgeom.h"

// 4つのfloat が num個の配列をsrcからdstにコピー
void copy_vector4_array(float* dst, const float* src, int num)
{
#if 1
	// ToDo: SIMD計算を使って実装して下さい

	for (int i = 0; i < num * 4; i += 4)
	{
		__m128 pd = _mm_load_ps(src + i);
		_mm_store_ps(dst+i,pd);
	}
	
#else
	float* pd = dst;
	const float* ps = src;

	for (int i = 0; i < num; i++) {
		pd[0] = ps[0];
		pd[1] = ps[1];
		pd[2] = ps[2];
		pd[3] = ps[3];

		pd += 4;
		ps += 4;
	}
#endif
}

// 4つのfloat が num個の配列 src0, src1を足してdstに出力
void add_vector4_array(float* dst, const float* src0, const float* src1, int num)
{
#if 1
	// ToDo: SIMD計算を使って実装して下さい
	for (int i = 0; i < num * 4; i += 4)
	{
		__m128 ps0 = _mm_load_ps(src0 + i);
		__m128 ps1 = _mm_load_ps(src1 + i);

		__m128 pd = _mm_add_ps(ps0, ps1);

		_mm_store_ps((dst + i), pd);
	}
#else
	float* pd = dst;
	const float* ps0 = src0;
	const float* ps1 = src1;

	for (int i = 0; i < num; i++) {
		pd[0] = ps0[0] + ps1[0];
		pd[1] = ps0[1] + ps1[1];
		pd[2] = ps0[2] + ps1[2];
		pd[3] = ps0[3] + ps1[3];

		pd += 4;
		ps0 += 4;
		ps1 += 4;
	}
#endif
}

// 4つのfloat に num個の配列 src にmatrix[4][4] の行列を掛けてdstに出力
void apply_matrix_vector4_array(float* dst, const float* src, const float* matrix, int num)
{
#if 1
	// ToDo: SIMD計算を使って実装して下さい

	for (int i = 0; i < num * 4; i += 4)
	{
		__m128 ps = _mm_load_ps(src + i);
		__m128 pd;
		float data[4];
		float sum[4] = {0};
		
		__m128 a[4];

		for (int j = 0; j < 4; j++)
		{	
			a[j] = _mm_mul_ps(_mm_load_ps(matrix + j * 4), ps);
			_mm_store_ps(data, a[j]);

			for (int k = 0; k < 4; k++)
			{
				sum[j] += data[k];
			}
		}

		pd = _mm_load_ps(sum);
		_mm_store_ps((dst + i), pd);
	}
#else
	float* pd = dst;
	const float* ps = src;

	for (int i = 0; i < num; i++) {
		pd[0] = matrix[4*0+0]*ps[0] + matrix[4*0+1]*ps[1] + matrix[4*0+2]*ps[2] + matrix[4*0+3]*ps[3];
		pd[1] = matrix[4*1+0]*ps[0] + matrix[4*1+1]*ps[1] + matrix[4*1+2]*ps[2] + matrix[4*1+3]*ps[3];
		pd[2] = matrix[4*2+0]*ps[0] + matrix[4*2+1]*ps[1] + matrix[4*2+2]*ps[2] + matrix[4*2+3]*ps[3];
		pd[3] = matrix[4*3+0]*ps[0] + matrix[4*3+1]*ps[1] + matrix[4*3+2]*ps[2] + matrix[4*3+3]*ps[3];

		pd += 4;
		ps += 4;
	}
#endif
}
