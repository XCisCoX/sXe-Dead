#include "GUI.h"
void ThemeButton(LPARAM lParam)
{
	LPNMHDR item = (LPNMHDR)lParam;
	if (

		(item->idFrom == BTN_RANDOM_HWID ||
			item->idFrom == BTN_ABOUT ||
			item->idFrom == BTN_ANTI_SS ||
			item->idFrom == EXIT_APP ||
			item->idFrom == BTN_SET_HWID ||
			item->idFrom == SET_STEAM ||
			item->idFrom == BTN_RANDOM_STEAM)

		&& item->code == NM_CUSTOMDRAW)
	{
		LPNMCUSTOMDRAW item_draw = (LPNMCUSTOMDRAW)item;
		if (item_draw->uItemState & CDIS_HOT)
		{
			SetCursor(
				::LoadCursor(
					NULL,
					IDC_HAND
				)
			);
			SetDCBrushColor(item_draw->hdc,
				RGB(250, 0, 0)
			);
			SetDCPenColor(item_draw->hdc,
				RGB(250, 255, 255)
			);
			SelectObject(item_draw->hdc,
				GetStockObject(DC_BRUSH));

		}
		else if (item_draw->uItemState & CDIS_DISABLED)
		{

			SetDCBrushColor(item_draw->hdc,
				RGB(80,0, 0)
			); SetDCPenColor(item_draw->hdc,
				RGB(250, 255, 255)
			);
			SetCursor(
				::LoadCursor(
					NULL,
					IDC_ARROW
				)
			);
			SelectObject(item_draw->hdc,
				GetStockObject(DC_BRUSH));
		}
		else
		{
	
			SetCursor(
				::LoadCursor(
					NULL,
					IDC_ARROW
				)
			);
			SetDCBrushColor(item_draw->hdc,
				RGB(220,38, 38));

			SelectObject(item_draw->hdc, GetStockObject(DC_BRUSH));



		}
		SetDCPenColor(item_draw->hdc,
			RGB(250, 255, 255)
		);
		SetTextColor(item_draw->hdc,
			RGB(0, 0, 255)
		);

		SetDCPenColor(item_draw->hdc,
			RGB(255, 255, 255)
		);

		SelectObject(item_draw->hdc, GetStockObject(DC_PEN));
		
		RoundRect(item_draw->hdc, item_draw->rc.left, item_draw->rc.top,
			item_draw->rc.right, item_draw->rc.bottom, 0, 0);
	}
}
void InitGui(LPARAM lParam)
{



}