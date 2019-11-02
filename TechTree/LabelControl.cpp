/* INCLUDES */

// Class header
#include "LabelControl.h"

/* FUNCTIONS */

LabelControl* LabelControl::Constructor()
{
	// Call original function
	return ((LabelControl *(__thiscall *)(LabelControl *))0x00544280)(this);
}

int LabelControl::sub_545D50(int unknown)
{
	// Call original function
	return ((int(__thiscall *)(LabelControl *, int))0x00545D50)(this, unknown);
}

int LabelControl::sub_545D70(int unknown)
{
	// Call original function
	return ((int(__thiscall *)(LabelControl *, int))0x00545D70)(this, unknown);
}

int LabelControl::SetStyleText2Colors(int styleTextColor1_BGR, int styleTextColor2_BGR)
{
	// Call original function
	return ((int(__thiscall *)(LabelControl *, int, int))0x00545DB0)(this, styleTextColor1_BGR, styleTextColor2_BGR);
}

void LabelControl::ForceDraw()
{
	// Call original function
	((void(__thiscall *)(LabelControl *))0x005464A0)(this);
}

void LabelControl::InterpreteTextFormatCodesAndComputeWordWrap(char *unformattedText, int id, int isResearch)
{
	// Call virtual function
	static_cast<LabelControlVTable *>(_VTable)->InterpreteTextFormatCodesAndComputeWordWrap(this, unformattedText, id, isResearch);
}

int LabelControl::sub_545DF0(int unknown1, char unknown2)
{
	// Call original function
	return ((int(__thiscall *)(LabelControl *, int, char))0x00545DF0)(this, unknown1, unknown2);
}

void LabelControl::SetBackgroundSlp(char *slpFileName, int slpResId)
{
	// Call original function
	((void(__thiscall *)(LabelControl *, char *, int))0x00545E10)(this, slpFileName, slpResId);
}

int LabelControl::sub_5444B0(DirectDrawArea *parentControlBackBuffer, Control *parentControl, int posX, int posY, int width, int height, HFONT *fonts, int maximumCharWidth, int maximumCharHeight, char *slpFileName, int unknown1, char unknown2, int unknown3, char unknown4, short maxLineLength, char *text)
{
	// Call original function
	return ((int(__thiscall *)(LabelControl *, DirectDrawArea *, Control *, int, int, int, int, HFONT *, int, int, char *, int, char, int, char, short, char *))0x005444B0)(this, parentControlBackBuffer, parentControl, posX, posY, width, height, fonts, maximumCharWidth, maximumCharHeight, slpFileName, unknown1, unknown2, unknown3, unknown4, maxLineLength, text);
}

void LabelControl::SetTextAlignment(int horizontalAlignment, int verticalAlignment)
{
	// Call original function
	((void(__thiscall *)(LabelControl *, int, int))0x00545D10)(this, horizontalAlignment, verticalAlignment);
}

int LabelControl::GetLineCount()
{
	// Return line count
	return _lineCount;
}