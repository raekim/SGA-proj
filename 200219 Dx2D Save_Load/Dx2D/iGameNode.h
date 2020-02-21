#pragma once

interface iGameNode
{
public:
	virtual void Init() PURE;
	virtual void Update() PURE;
	virtual void Render() PURE;
};