#pragma once
class ProgressBar
{
private:
	D3DXVECTOR2		m_vPos;
	D3DXVECTOR2		m_vSize;
	D3DXVECTOR2		m_vProgressSize;

	Sprite*			m_pBack;
	Sprite*			m_pFront;

public:
	ProgressBar(wstring backFile, wstring frontFile);
	~ProgressBar();

	void Init();
	void Update();
	void Render();

	void SetPos(float x, float y) { m_vPos = D3DXVECTOR2(x, y); }
	void SetSize(float x, float y) { m_vSize = D3DXVECTOR2(x, y); }
	void SetProgress(float maxGauge, float currGauage, bool horizontal);
};