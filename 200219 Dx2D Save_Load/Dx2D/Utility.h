#pragma once
/* Utility */
inline bool PointInCircle(D3DXVECTOR2 p1, float r1, D3DXVECTOR2 point)
{
	float distX = p1.x - point.x;
	float distY = p1.y - point.y;

	float dist = sqrtf(distX * distX + distY * distY);

	if (dist > r1)
		return false;

	return true;
}

inline bool PointInRect(D3DXVECTOR2 p1, D3DXVECTOR2 s1, D3DXVECTOR2 point)
{
	float L1 = p1.x - s1.x * 0.5f;
	float R1 = L1 + s1.x; // R1 = p1.x + s1.x * 0.5f;
	float T1 = p1.y + s1.y * 0.5f;
	float B1 = T1 - s1.y;

	if (point.x < L1 || point.x > R1 ||
		point.y < B1 || point.y > T1)
		return false;

	return true;
}

inline bool CircleCollision(D3DXVECTOR2 p1, float r1, D3DXVECTOR2 p2, float r2)
{
	/*
	원 충돌 : 두 점 사이의 거리가 두 원의 반지름을 더한 값보다 작다면 두 원은 충돌 상태
	*/

	float distX = p1.x - p2.x;
	float distY = p1.y - p2.y;

	float distance = sqrtf(distX * distX + distY * distY);

	if (r1 + r2 < distance)
		return false;

	return true;
}

inline bool AABB2D(D3DXVECTOR2 p1, D3DXVECTOR2 s1, D3DXVECTOR2 p2, D3DXVECTOR2 s2)
{
	float L1 = p1.x	- s1.x * 0.5f;
	float R1 = L1	+ s1.x; // R1 = p1.x + s1.x * 0.5f;
	float T1 = p1.y	+ s1.y * 0.5f;
	float B1 = T1	- s1.y;

	float L2 = p2.x	- s2.x * 0.5f;
	float R2 = L2	+ s2.x;
	float T2 = p2.y	+ s2.y * 0.5f;
	float B2 = T2	- s2.y;

	if (R1 < L2 || L1 > R2)
		return false;

	if (B1 > T2 || T1 < B2)
		return false;

	return true;
}

inline bool AABB2D(RECT& rect1, RECT& rect2)
{
	if (rect1.right < rect2.left || rect1.left > rect2.right)
		return false;

	if (rect1.bottom > rect2.top || rect1.top < rect2.bottom)
		return false;

	return true;
}

// 기준축, A도형 중점, A도형 반지름, B도형 중점, B도형 좌표값
// A도형 : 기준축에 평행변을 가지고 있는 도형
inline bool CheckOBB2D(D3DXVECTOR2& PivotDir, D3DXVECTOR2& A_Center, float& A_Half,
	D3DXVECTOR2 B_Center, D3DXVECTOR2 v[4])
{
	// 두 센터에 대한 투영값
	float projectA_C = D3DXVec2Dot(&PivotDir, &A_Center);
	float projectB_C = D3DXVec2Dot(&PivotDir, &B_Center);

	// 두 센터의 투영값의 거리
	float length_C = fabs(projectA_C - projectB_C);

	// B도형의 각 좌표에 대한 투영 값중 가장 작은 값을 계산
	float projectB_Left = D3D11_FLOAT32_MAX;
	for (int i = 0; i < 4; i++)
	{
		float length = D3DXVec2Dot(&PivotDir, &v[i]);

		if (length < projectB_Left)
			projectB_Left = length;
	}

	// B도형의 기준벡터에 대한 반지름값
	float B_Half = fabs(projectB_Left - projectB_C);

	return length_C <= (A_Half + B_Half);
}

inline bool OBB2D(D3DXMATRIX& matA, D3DXMATRIX& matB)
{
	// 처음 설계 기본 좌표 값은 0기준 사이즈 1짜리이다.
	D3DXVECTOR2 vA[4], vB[4];
	vA[0] = D3DXVECTOR2(-0.5f,-0.5f);
	vA[1] = D3DXVECTOR2(-0.5f, 0.5f);
	vA[2] = D3DXVECTOR2( 0.5f, 0.5f);
	vA[3] = D3DXVECTOR2( 0.5f,-0.5f);

	// 월드(SRT)매트릭스를 사용하여 현재 화면에서의 좌표값을 계산
	for (int i = 0; i < 4; i++)
	{
		D3DXVec2TransformCoord(&vB[i], &vA[i], &matB);
		D3DXVec2TransformCoord(&vA[i], &vA[i], &matA);
	}

	// 두 사각형의 중점 계산
	D3DXVECTOR2 vA_Center((vA[0] + vA[2]) * 0.5f);
	D3DXVECTOR2 vB_Center((vB[0] + vB[2]) * 0.5f);

	// 기준축 벡터 계산1
	D3DXVECTOR2 vA_01 = vA[1] - vA[0];
	D3DXVECTOR2 vA_03 = vA[3] - vA[0];
	D3DXVECTOR2 vB_01 = vB[1] - vB[0];
	D3DXVECTOR2 vB_03 = vB[3] - vB[0];

	// 사각형 한변의 절반 크기 (기준축 평행변)
	float fA_01_Half = D3DXVec2Length(&vA_01) * 0.5f;
	float fA_03_Half = D3DXVec2Length(&vA_03) * 0.5f;
	float fB_01_Half = D3DXVec2Length(&vB_01) * 0.5f;
	float fB_03_Half = D3DXVec2Length(&vB_03) * 0.5f;

	// 기준축 벡터 계산2
	D3DXVec2Normalize(&vA_01, &vA_01);
	D3DXVec2Normalize(&vA_03, &vA_03);
	D3DXVec2Normalize(&vB_01, &vB_01);
	D3DXVec2Normalize(&vB_03, &vB_03);

	// 각 기준축 별로 충돌 검사하는 방식이 같기 때문에 함수화하여 사용
	if (!CheckOBB2D(vA_01, vA_Center, fA_01_Half, vB_Center, vB))
		return false;

	if (!CheckOBB2D(vA_03, vA_Center, fA_03_Half, vB_Center, vB))
		return false;

	if (!CheckOBB2D(vB_01, vB_Center, fB_01_Half, vA_Center, vA))
		return false;

	if (!CheckOBB2D(vB_03, vB_Center, fB_03_Half, vA_Center, vA))
		return false;

	return true;
}

inline float GetAngle(D3DXVECTOR2 p1, D3DXVECTOR2 p2) // p1 -> p2
{
	/*
	p1 에서 p2 방향의 각도 값 = theta
	cos(theta) = (x2 - x1) / 대각선 길이
	theta = cos^-1( (x2 - x1) / 대각선 길이 )
	theta = acos( (x2 - x1) / 대각선 길이 )
	*/

	float distX = p2.x - p1.x;
	float distY = p2.y - p1.y;

	float distance = sqrtf(distX * distX + distY * distY);

	float result = acosf(distX / distance);

	if (p2.y < p1.y)
		result = D3DX_PI * 2 - result;

	// 서클 클래스가 사용하는 앵글값은 Degree 값이고
	// cos, sin 함수들이 사용하는 값은 Radian 값이다.
	return D3DXToDegree(result);
}

template <typename T>
inline T LinearInterpolation(T from, T to, float cp) // cp = 0 ~ 1
{
	// return from * (1.0 - cp) + to * cp;
	return from + (to - from) * cp;
}

template <typename T>
inline T BezierCurve(T from, T via, T to, float cp) // Quadratic Bezier
{
	T t1 = LinearInterpolation(from, via, cp);
	T t2 = LinearInterpolation(via, to, cp);

	return LinearInterpolation(t1, t2, cp);
}