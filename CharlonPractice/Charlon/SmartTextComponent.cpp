#include "pch.h"
#include "SmartTextComponent.h"

#include "Texture.h"

#include <iostream>

std::string SmartTextComponent::c_DefaultFontPath{"consola.ttf"};

bool SmartTextComponent::ChangeDefaultFont(const std::string& fontPath)
{
	if (fontPath == c_DefaultFontPath)
	{
		return false;
	}
	c_DefaultFontPath = fontPath;
	return true;
}

SmartTextComponent::SmartTextComponent(const std::string& text, int textSize, const Color4f & textColor, const std::string& fontPath)
	:UserInterfaceElement(Rectf{})
	,m_CurrentText{text}
	,m_FontPath{fontPath}
	,m_TextSize{textSize}
	,m_TextColor{textColor}
{
	m_pTexture = new Texture{m_CurrentText,m_FontPath,m_TextSize,m_TextColor};
}

SmartTextComponent::~SmartTextComponent()
{
	delete m_pTexture;
	m_pTexture = nullptr;
}

void SmartTextComponent::Draw() const
{
	m_Transform.Push();
	{
		m_Transform.Apply();
		m_pTexture->Draw();
	}
	m_Transform.Pop();
}

void SmartTextComponent::UpdateText(const std::string& text, bool checkForChanges)
{
	if (checkForChanges)
	{
		if (text == m_CurrentText)
		{
			return;
		}
	}
	m_CurrentText = text;
	RemakeTexture();
}

void SmartTextComponent::UpdateFont(const std::string& fontPath, bool checkForChanges)
{
	if (checkForChanges)
	{
		if (fontPath == m_FontPath)
		{
			return;
		}
	}
	
	m_FontPath = fontPath;
	RemakeTexture();
}

void SmartTextComponent::UpdateTextSize(int textSize, bool checkForChanges)
{
	if (checkForChanges)
	{
		if (textSize == m_TextSize)
		{
			return;
		}
	}
	m_TextSize = textSize;
	RemakeTexture();
}

void SmartTextComponent::UpdateTextColor(const Color4f& color, bool checkForChanges)
{
	if (checkForChanges)
	{
		if (CompareColors(m_TextColor, color))
		{
			return;
		}
	}
	m_TextColor = color;
	RemakeTexture();
}

const Transform& SmartTextComponent::GetTransform() const
{
	return m_Transform;
}

void SmartTextComponent::ChangeTransform(const Transform& transform)
{
	m_Transform = transform;
}

float SmartTextComponent::GetWidth() const
{
	if (m_pTexture == nullptr)
	{
		return 0.0f;
	}
	return m_pTexture->GetWidth();
}

float SmartTextComponent::GetHeight() const
{
	if (m_pTexture == nullptr)
	{
		return 0.0f;
	}
	return m_pTexture->GetHeight();
}

void SmartTextComponent::RemakeTexture()
{
	delete m_pTexture;
	m_pTexture = new Texture{ m_CurrentText,m_FontPath,m_TextSize,m_TextColor };
}

bool SmartTextComponent::CompareColors(const Color4f& a, const Color4f& b)
{
	if ((a.r-b.r) <= FLT_EPSILON)
	{
		if ((a.g - b.g) <= FLT_EPSILON)
		{
			if ((a.b - b.b) <= FLT_EPSILON)
			{
				if ((a.a - b.a) <= FLT_EPSILON)
				{
					return true;
				}
			}
		}
	}
	return false;
}
