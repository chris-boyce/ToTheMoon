// Semester 2 Christopher Boyce : TTM Project


#include "WidgetBase.h"


#if WITH_EDITOR
const FText UWidgetBase::GetPaletteCategory()
{
	return NSLOCTEXT("UMG", "CustomPalleteCategory", "ToTheMoon");
}
#endif