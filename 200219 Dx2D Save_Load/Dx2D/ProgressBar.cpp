#include "stdafx.h"
#include "ProgressBar.h"


ProgressBar::ProgressBar(wstring backFile, wstring frontFile)
{
	m_pBack = new Sprite(backFile);
	m_pFront = new Sprite(frontFile);
}


ProgressBar::~ProgressBar()
{
	SAFE_DELETE(m_pBack);
	SAFE_DELETE(m_pFront);
}

void ProgressBar::Init()
{
	m_vProgressSize = m_vSize;
}

void ProgressBar::Update()
{
	m_pBack->SetConstantScale(m_vSize);
	m_pBack->SetLBPosition(m_vPos);
	m_pBack->Update();

	m_pFront->SetConstantScale(m_vProgressSize);
	m_pFront->SetLBPosition(m_vPos);
	m_pFront->Update();
}

void ProgressBar::Render()
{
	m_pBack->Render();
	m_pFront->Render();
}

void ProgressBar::SetProgress(float maxGauge, float currGauage, bool horizontal)
{
	if (horizontal)
		m_vProgressSize.x = m_pBack->GetWidth() * currGauage / maxGauge;
	else
		m_vProgressSize.y = m_pBack->GetHeight() * currGauage / maxGauge;
}