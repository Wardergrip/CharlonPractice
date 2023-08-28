#pragma once

#include "Transform.h"

#include "UserInterfaceElement.h"

class Texture;

class SmartTextComponent final : public UserInterfaceElement
{
// STATICS
public:
	static bool ChangeDefaultFont(const std::string& fontPath);
private:
	static std::string c_DefaultFontPath;

// NON STATICS
public:
	SmartTextComponent(const std::string& text, int textSize = 16, const Color4f& textColor = Color4f{1,1,1,1}, const std::string& fontPath = c_DefaultFontPath);
	SmartTextComponent(const SmartTextComponent& other) = delete;
	SmartTextComponent& operator=(const SmartTextComponent& other) = delete;
	SmartTextComponent(SmartTextComponent&& other) = delete;
	SmartTextComponent& operator=(SmartTextComponent&& other) = delete;
	~SmartTextComponent();

	void Draw() const override;

	void UpdateText(const std::string& text, bool checkForChanges = true);
	void UpdateFont(const std::string& fontPath = c_DefaultFontPath, bool checkForChanges = true);
	void UpdateTextSize(int textSize, bool checkForChanges = true);
	void UpdateTextColor(const Color4f& color = Color4f{1,1,1,1}, bool checkForChanges = true);

	const Transform& GetTransform() const;
	void ChangeTransform(const Transform& transform);

	float GetWidth() const;
	float GetHeight() const;
private:
	//Transform m_Transform;

	Texture* m_pTexture;
	std::string m_CurrentText;
	std::string m_FontPath;
	int m_TextSize;
	Color4f m_TextColor;

	void RemakeTexture();
	static bool CompareColors(const Color4f& a, const Color4f& b);
};

