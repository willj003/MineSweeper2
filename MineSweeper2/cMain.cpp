#include "cMain.h"
wxBEGIN_EVENT_TABLE(cMain, wxFrame)
	EVT_BUTTON(10001, OnButtonClicked)
wxEND_EVENT_TABLE();

cMain::cMain() : wxFrame(nullptr, wxID_ANY, "WillsMineSweeper", wxPoint(30, 30), wxSize(800, 600))
{
	btn = new wxButton * [nFieldWidth * NFieldHeight];
	wxGridSizer* grid = new wxGridSizer(nFieldWidth, NFieldHeight, 0, 0);

	nField = new int[nFieldWidth * NFieldHeight];

	for (int x = 0; x < nFieldWidth; x++)
	{
		for (int y = 0; y < NFieldHeight; y++)
		{
			btn[y * nFieldWidth + x] = new wxButton(this, 10000 + (y * nFieldWidth + x));
			grid->Add(btn[y * nFieldWidth + x], 1, wxEXPAND | wxALL);

			btn[y * nFieldWidth + x]->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &cMain::OnButtonClicked, this);
			nField[y * nFieldWidth + x] = 0;


		}
	}
	this->SetSizer(grid);
	grid->Layout();

}

cMain::~cMain()
{
	delete[]btn;
}

void cMain::OnButtonClicked(wxCommandEvent& evt)
{
	int x = (evt.GetId() - 10000) % nFieldWidth;
	int y = (evt.GetId() - 10000) / nFieldWidth;
	if (bFirstClick)
	{
		int mines = 30;
		while (mines)
		{
			int rx = rand() % nFieldWidth;
			int ry = rand() % NFieldHeight;
			if (nField[ry * nFieldWidth + rx] == 0 && rx != x && ry != y)
			{
				nField[ry * nFieldWidth + rx] = -1;
				mines--;
			}
		}
		bFirstClick = false;
	}
	btn[y * nFieldWidth + x]->Enable(false);
	if (nField[y * nFieldWidth + x] == -1)
	{
		wxMessageBox("BOOOMM!!! - GAME OVER! :(");
		bFirstClick = true;
		for (int x = 0; x < nFieldWidth; x++)
		{
			for (int y = 0; y < NFieldHeight; y++)
			{
				nField[y * nFieldWidth + x] == 0;
				btn[y * nFieldWidth + x]->SetLabel("");
				btn[y * nFieldWidth + x]->Enable(true);
			}
		}
	}
	else
	{
		int mine_count = 0;
		for (size_t i = -1; i < 2; i++)
			for (size_t j = -1; j < 2; j++)
			{
				if (x + i >= 0 && x + i < nFieldWidth && y + j >= 0 && y + j < NFieldHeight)
				{
					if (nField[(y + j) * nFieldWidth + (x + i)] == -1)
						mine_count++;
				}
			}
		if (mine_count > 0)
		{
			btn[y * nFieldWidth + x]->SetLabel(std::to_string(mine_count));
		}
		
	}
	evt.Skip();

}
 