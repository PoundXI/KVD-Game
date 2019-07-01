#include "WindowPlayer.hpp"
#include "ObjectManager.hpp"
#include "TextBox.hpp"
#include "Label.hpp"
#include "Button.hpp"
#include "Game.hpp"
#include "ListBox.hpp"
#include "Conversion.hpp"
#include "Debug.hpp"
#include "FileManager.hpp"
#include "Wallpaper.hpp"
#include "PictureBox.hpp"
#include <map>

WindowPlayer::WindowPlayer() : _state(Viewing), _workWithId(0) {
}

WindowPlayer::~WindowPlayer() {
}

int WindowPlayer::Show(sf::RenderWindow& window) {
    DEBUG_PRINT("Showing WindowPlayer\n");

    const float TOP  = 60;
    const float LEFT = 180;
    Wallpaper* wallpaper = new Wallpaper(Game::GetImage("Background_All"));
    PictureBox* picture = new PictureBox(Game::GetImage("PictureBox_Player"), LEFT, TOP);

    PictureBox* picEnterName = new PictureBox(Game::GetImage("PictureBox_EnterName"), LEFT, TOP);
    TextBox* tbxName = new TextBox(LEFT + 80, TOP + 100, 250, 50);
    Button* btnOk = new Button(Game::GetImage("Button_Create"), 60, LEFT + 100, TOP + 150);

    Label* lblPage = new Label("", 30, LEFT + 20, TOP + 50);
    ListBox* listBox = new ListBox(Game::GetImage("ListBox_Body")
                                   , Game::GetImage("ListBox_First")
                                   , Game::GetImage("ListBox_Prev")
                                   , Game::GetImage("ListBox_Next")
                                   , Game::GetImage("ListBox_Last")
                                   , Game::GetImage("ListBox_Delete")
                                   , LEFT + 20, TOP + 100);

    Button* btnCreate = new Button(Game::GetImage("Button_Create"), 60, LEFT + 20, TOP + 400);

    std::vector<std::string> playerNames = FileManager::GetFileNames("profiles");
    for(int i = 0; i < playerNames.size(); i++) {
        if(playerNames[i] != "main.bin") {
            listBox->Add(playerNames[i].substr(0, playerNames[i].length() - 4));
        }
    }

    // Draw & event loop
    while(true) {
        // Get event loop
        sf::Event event;
        while(window.GetEvent(event)) {
            // Window closed
            if(event.Type == sf::Event::Closed) {
                //return -1;
            }

            // Escape key pressed
            if((event.Type == sf::Event::KeyPressed) && (event.Key.Code == sf::Key::Escape)) {
                //return -1;
            }

            char alphabet = tbxName->GetKeyPressed(event);
            if(alphabet != NULL) {
                if(alphabet == 0x8) {
                    tbxName->Remove();
                } else {
                    tbxName->Append(alphabet);
                }
            }
        }

        lblPage->SetText("Page: "
                         + Conversion::IntToString(listBox->GetCurrentPage())
                         + "/"
                         + Conversion::IntToString(listBox->GetPageCount())
                         + " ( "
                         + Conversion::IntToString(listBox->GetItemCount())
                         + " Players )"
                        );

        if(listBox->GetItemCount() == 0) {
            _state = Creating;
        } else {
            _state = Viewing;
        }

        if(btnCreate->GetState() == Button::MouseReleased) {
            _state = Creating;
        }

        if(listBox->GetSelectedIndex() != -1) {
            Game::SetPlayerName(listBox->GetSelectedText());
            DEBUG_PRINT("selected %s\n", listBox->GetSelectedText().c_str());
            return 0;
        }

        if(listBox->GetDeletedIndex() != -1) {
            DEBUG_PRINT("deleted %s\n", listBox->GetDeletedText().c_str());
            FileManager::RemoveFile("profiles/" + listBox->GetDeletedText() + ".bin");
            listBox->Remove(listBox->GetDeletedIndex());
        }

        if(btnOk->GetState() == Button::MouseReleased) {
            if(tbxName->GetText() != "") {
                if(!listBox->IsExists(tbxName->GetText())) {
                    DEBUG_PRINT("Add New Player = %s\n", tbxName->GetText().c_str());
                    listBox->Add(tbxName->GetText());

                    //Create Player Profile
                    Game::CreateIniProfile(tbxName->GetText());

                    tbxName->SetText("");
                    _state = Viewing;
                }
            }
        }

        window.Clear();

        wallpaper->Update(Game::GetWindow().GetFrameTime());
        wallpaper->Draw(window);
        if(_state == Viewing) {
            picture->Update(Game::GetWindow().GetFrameTime());
            picture->Draw(window);
            listBox->Update(Game::GetWindow().GetFrameTime());
            listBox->Draw(window);
            btnCreate->Update(Game::GetWindow().GetFrameTime());
            btnCreate->Draw(window);
            lblPage->Update(Game::GetWindow().GetFrameTime());
            lblPage->Draw(window);
        } else {
            picEnterName->Update(Game::GetWindow().GetFrameTime());
            picEnterName->Draw(window);
            tbxName->Update(Game::GetWindow().GetFrameTime());
            tbxName->Draw(window);
            btnOk->Update(Game::GetWindow().GetFrameTime());
            btnOk->Draw(window);
        }

        window.Display();
    }
}
