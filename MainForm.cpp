
#include "MainForm.h"
#include "Manager.h" 
#include "Ball.h"
#include "Triangle.h"
#include "Rectangle.h"
#include "Star.h"
#include "Hunter.h" 
#include "Animal.h" 
#include "Tree.h" 
#include "Explosion.h" 
#include "Bullet.h" 
#include "Pictures.h" 

#include <ctime> 
#define _USE_MATH_DEFINES
#include <cmath> 

using namespace OOP5_Asorti;
using namespace System::Drawing;
using namespace System::Windows::Forms;
using namespace System::Diagnostics; 


Manager* manager = nullptr;








void MainForm::InitializeComponent(void) {
    this->components = gcnew System::ComponentModel::Container(); 

    
    
    
    
    
    
    
    
    
    


    
    this->pop_frame = (gcnew System::Windows::Forms::PictureBox());
    this->shapeGroupBox = (gcnew System::Windows::Forms::GroupBox());
    this->starBtn = (gcnew System::Windows::Forms::RadioButton());
    this->triangleBtn = (gcnew System::Windows::Forms::RadioButton());
    this->rectangleBtn = (gcnew System::Windows::Forms::RadioButton());
    this->ballBtn = (gcnew System::Windows::Forms::RadioButton());
    this->ballLabel = (gcnew System::Windows::Forms::Label());
    this->ballCountLabel = (gcnew System::Windows::Forms::Label());
    this->rectangleLabel = (gcnew System::Windows::Forms::Label());
    this->rectangleCountLabel = (gcnew System::Windows::Forms::Label());
    this->triangleLabel = (gcnew System::Windows::Forms::Label());
    this->triangleCountLabel = (gcnew System::Windows::Forms::Label());
    this->starLabel = (gcnew System::Windows::Forms::Label());
    this->starCountLabel = (gcnew System::Windows::Forms::Label());

    
    this->bulletsLabel = (gcnew System::Windows::Forms::Label());
    this->bulletsCountLabel = (gcnew System::Windows::Forms::Label());
    this->trophiesLabel = (gcnew System::Windows::Forms::Label());
    this->trophiesCountLabel = (gcnew System::Windows::Forms::Label());
    this->startButton = (gcnew System::Windows::Forms::Button());
    this->stopButton = (gcnew System::Windows::Forms::Button());


    
    (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pop_frame))->BeginInit();
    this->shapeGroupBox->SuspendLayout();
    this->SuspendLayout();

    
    this->pop_frame->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
        | System::Windows::Forms::AnchorStyles::Left)
        | System::Windows::Forms::AnchorStyles::Right);
    this->pop_frame->BackColor = System::Drawing::Color::LightCyan;
    this->pop_frame->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
    this->pop_frame->Location = System::Drawing::Point(12, 12);
    this->pop_frame->Name = L"pop_frame";
    this->pop_frame->Size = System::Drawing::Size(600, 400); 
    this->pop_frame->TabIndex = 0;
    this->pop_frame->TabStop = false;
    
    this->pop_frame->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MainForm::pop_frame_Paint);
    this->pop_frame->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &MainForm::pop_frame_MouseDown);
    this->pop_frame->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &MainForm::pop_frame_MouseUp); 
    this->pop_frame->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &MainForm::pop_frame_MouseMove); 

    
    this->shapeGroupBox->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
    this->shapeGroupBox->Controls->Add(this->starBtn);
    this->shapeGroupBox->Controls->Add(this->triangleBtn);
    this->shapeGroupBox->Controls->Add(this->rectangleBtn);
    this->shapeGroupBox->Controls->Add(this->ballBtn);
    this->shapeGroupBox->Location = System::Drawing::Point(620, 12); 
    this->shapeGroupBox->Name = L"shapeGroupBox";
    this->shapeGroupBox->Size = System::Drawing::Size(150, 130); 
    this->shapeGroupBox->TabIndex = 1;
    this->shapeGroupBox->TabStop = false;
    this->shapeGroupBox->Text = L"Shape";

    
    this->ballBtn->AutoSize = true; this->ballBtn->Location = System::Drawing::Point(15, 25); this->ballBtn->Name = L"ballBtn"; this->ballBtn->Size = System::Drawing::Size(51, 20); this->ballBtn->TabIndex = 0; this->ballBtn->TabStop = true; this->ballBtn->Text = L"Ball"; this->ballBtn->UseVisualStyleBackColor = true;
    this->rectangleBtn->AutoSize = true; this->rectangleBtn->Location = System::Drawing::Point(15, 50); this->rectangleBtn->Name = L"rectangleBtn"; this->rectangleBtn->Size = System::Drawing::Size(90, 20); this->rectangleBtn->TabIndex = 1; this->rectangleBtn->TabStop = true; this->rectangleBtn->Text = L"Rectangle"; this->rectangleBtn->UseVisualStyleBackColor = true;
    this->triangleBtn->AutoSize = true; this->triangleBtn->Location = System::Drawing::Point(15, 75); this->triangleBtn->Name = L"triangleBtn"; this->triangleBtn->Size = System::Drawing::Size(77, 20); this->triangleBtn->TabIndex = 2; this->triangleBtn->TabStop = true; this->triangleBtn->Text = L"Triangle"; this->triangleBtn->UseVisualStyleBackColor = true;
    this->starBtn->AutoSize = true; this->starBtn->Location = System::Drawing::Point(15, 100); this->starBtn->Name = L"starBtn"; this->starBtn->Size = System::Drawing::Size(54, 20); this->starBtn->TabIndex = 3; this->starBtn->TabStop = true; this->starBtn->Text = L"Star"; this->starBtn->UseVisualStyleBackColor = true;


    
    
    this->ballLabel->AutoSize = true; this->ballLabel->Location = System::Drawing::Point(620, 150); this->ballLabel->Name = L"ballLabel"; this->ballLabel->Size = System::Drawing::Size(35, 16); this->ballLabel->TabIndex = 2; this->ballLabel->Text = L"Balls:";
    this->ballCountLabel->AutoSize = true; this->ballCountLabel->Location = System::Drawing::Point(700, 150); this->ballCountLabel->Name = L"ballCountLabel"; this->ballCountLabel->Size = System::Drawing::Size(14, 16); this->ballCountLabel->TabIndex = 3; this->ballCountLabel->Text = L"0";
    this->rectangleLabel->AutoSize = true; this->rectangleLabel->Location = System::Drawing::Point(620, 170); this->rectangleLabel->Name = L"rectangleLabel"; this->rectangleLabel->Size = System::Drawing::Size(72, 16); this->rectangleLabel->TabIndex = 4; this->rectangleLabel->Text = L"Rectangles:";
    this->rectangleCountLabel->AutoSize = true; this->rectangleCountLabel->Location = System::Drawing::Point(700, 170); this->rectangleCountLabel->Name = L"rectangleCountLabel"; this->rectangleCountLabel->Size = System::Drawing::Size(14, 16); this->rectangleCountLabel->TabIndex = 5; this->rectangleCountLabel->Text = L"0";
    this->triangleLabel->AutoSize = true; this->triangleLabel->Location = System::Drawing::Point(620, 190); this->triangleLabel->Name = L"triangleLabel"; this->triangleLabel->Size = System::Drawing::Size(63, 16); this->triangleLabel->TabIndex = 6; this->triangleLabel->Text = L"Triangles:";
    this->triangleCountLabel->AutoSize = true; this->triangleCountLabel->Location = System::Drawing::Point(700, 190); this->triangleCountLabel->Name = L"triangleCountLabel"; this->triangleCountLabel->Size = System::Drawing::Size(14, 16); this->triangleCountLabel->TabIndex = 7; this->triangleCountLabel->Text = L"0";
    this->starLabel->AutoSize = true; this->starLabel->Location = System::Drawing::Point(620, 210); this->starLabel->Name = L"starLabel"; this->starLabel->Size = System::Drawing::Size(42, 16); this->starLabel->TabIndex = 8; this->starLabel->Text = L"Stars:";
    this->starCountLabel->AutoSize = true; this->starCountLabel->Location = System::Drawing::Point(700, 210); this->starCountLabel->Name = L"starCountLabel"; this->starCountLabel->Size = System::Drawing::Size(14, 16); this->starCountLabel->TabIndex = 9; this->starCountLabel->Text = L"0";


    
    this->bulletsLabel->AutoSize = true; this->bulletsLabel->Location = System::Drawing::Point(620, 240); this->bulletsLabel->Name = L"bulletsLabel"; this->bulletsLabel->Size = System::Drawing::Size(50, 16); this->bulletsLabel->TabIndex = 10; this->bulletsLabel->Text = L"Bullets:";
    this->bulletsCountLabel->AutoSize = true; this->bulletsCountLabel->Location = System::Drawing::Point(700, 240); this->bulletsCountLabel->Name = L"bulletsCountLabel"; this->bulletsCountLabel->Size = System::Drawing::Size(14, 16); this->bulletsCountLabel->TabIndex = 11; this->bulletsCountLabel->Text = L"0";
    this->trophiesLabel->AutoSize = true; this->trophiesLabel->Location = System::Drawing::Point(620, 260); this->trophiesLabel->Name = L"trophiesLabel"; this->trophiesLabel->Size = System::Drawing::Size(67, 16); this->trophiesLabel->TabIndex = 12; this->trophiesLabel->Text = L"Trophies:";
    this->trophiesCountLabel->AutoSize = true; this->trophiesCountLabel->Location = System::Drawing::Point(700, 260); this->trophiesCountLabel->Name = L"trophiesCountLabel"; this->trophiesCountLabel->Size = System::Drawing::Size(14, 16); this->trophiesCountLabel->TabIndex = 13; this->trophiesCountLabel->Text = L"0";


    
    this->startButton->Location = System::Drawing::Point(620, 300); this->startButton->Name = L"startButton"; this->startButton->Size = System::Drawing::Size(150, 30); this->startButton->TabIndex = 14; this->startButton->Text = L"Start Game"; this->startButton->UseVisualStyleBackColor = true;
    this->stopButton->Location = System::Drawing::Point(620, 340); this->stopButton->Name = L"stopButton"; this->stopButton->Size = System::Drawing::Size(150, 30); this->stopButton->TabIndex = 15; this->stopButton->Text = L"Stop Game"; this->stopButton->UseVisualStyleBackColor = true; this->stopButton->Enabled = false; 


    
    this->Controls->Add(this->stopButton);
    this->Controls->Add(this->startButton);
    this->Controls->Add(this->trophiesCountLabel);
    this->Controls->Add(this->trophiesLabel);
    this->Controls->Add(this->bulletsCountLabel);
    this->Controls->Add(this->bulletsLabel);
    this->Controls->Add(this->starCountLabel);
    this->Controls->Add(this->starLabel);
    this->Controls->Add(this->triangleCountLabel);
    this->Controls->Add(this->triangleLabel);
    this->Controls->Add(this->rectangleCountLabel);
    this->Controls->Add(this->rectangleLabel);
    this->Controls->Add(this->ballCountLabel);
    this->Controls->Add(this->ballLabel);
    this->Controls->Add(this->shapeGroupBox);
    this->Controls->Add(this->pop_frame);


    
    this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
    this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
    this->ClientSize = System::Drawing::Size(782, 423); 
    this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::Fixed3D;
    this->Name = L"MainForm";
    this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
    this->Text = L"Pop Shapes V6: Mednieks"; 
    this->KeyPreview = true; 


    
    (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pop_frame))->EndInit();
    this->shapeGroupBox->ResumeLayout(false);
    this->shapeGroupBox->PerformLayout();
    this->ResumeLayout(false);
    this->PerformLayout();

}




MainForm::MainForm(void) {
    
    MainForm::form = this;

    
    InitializeComponent();

    
    srand(static_cast<unsigned int>(time(0)));

    
    
    if (pop_frame != nullptr) {
        ::manager = new Manager(pop_frame->Width, pop_frame->Height); 
    }
    else {
        
        ::manager = new Manager(800, 600); 
        Debug::WriteLine("Error: pop_frame was null during Manager initialization!");
    }


    
    moveTimer = gcnew Timer();
    moveTimer->Interval = 20; 
    moveTimer->Tick += gcnew EventHandler(this, &MainForm::OnMoveTimer);
    

    
    drawTimer = gcnew Timer();
    drawTimer->Interval = 20; 
    drawTimer->Tick += gcnew EventHandler(this, &MainForm::OnDrawTimer);
    

    
    this->startButton->Click += gcnew System::EventHandler(this, &MainForm::startButton_Click);
    this->stopButton->Click += gcnew System::EventHandler(this, &MainForm::stopButton_Click);
    this->KeyPreview = true;
    this->KeyDown += gcnew KeyEventHandler(this, &MainForm::MainForm_KeyDown);
    this->KeyUp += gcnew KeyEventHandler(this, &MainForm::MainForm_KeyUp);
    this->MouseWheel += gcnew MouseEventHandler(this, &MainForm::OnMouseWheel);
    

    
    this->ballBtn->Checked = true;

    
    bulletsCount = 0; 
    trophiesCount = 0;

    
    UpdateCountLabels();

    
}


MainForm::~MainForm() {
    
    if (moveTimer != nullptr) {
        moveTimer->Stop();
        delete moveTimer; 
        moveTimer = nullptr;
    }
    if (drawTimer != nullptr) {
        drawTimer->Stop();
        delete drawTimer; 
        drawTimer = nullptr;
    }
    

    
    if (manager != nullptr) {
        delete manager;
        manager = nullptr;
    }

    
    if (components) {
        delete components; 
    }
}


void MainForm::UpdateCountLabels() {
    
    if (manager != nullptr) { 
        if (ballCountLabel != nullptr)  ballCountLabel->Text = manager->countBalls().ToString();
        if (rectangleCountLabel != nullptr) rectangleCountLabel->Text = manager->countRectangles().ToString();
        if (triangleCountLabel != nullptr) triangleCountLabel->Text = manager->countTriangles().ToString();
        if (starCountLabel != nullptr)  starCountLabel->Text = manager->countStars().ToString();
    }
    else {
        
        if (ballCountLabel != nullptr)  ballCountLabel->Text = "N/A";
        if (rectangleCountLabel != nullptr) rectangleCountLabel->Text = "N/A";
        if (triangleCountLabel != nullptr) triangleCountLabel->Text = "N/A";
        if (starCountLabel != nullptr)  starCountLabel->Text = "N/A";
    }


    
    if (bulletsCountLabel != nullptr) bulletsCountLabel->Text = bulletsCount.ToString();
    if (trophiesCountLabel != nullptr) trophiesCountLabel->Text = trophiesCount.ToString();

    
}



bool MainForm::takeBullet() {
    
    if (bulletsCount > 0) {
        bulletsCount--;
        UpdateCountLabels();
        return true;
    }
    else {
        
        endGame(1); 
        return false;
    }
}

void MainForm::killAnimal() {
    
    trophiesCount++;
    
    
    
    

    bulletsCount += 3; 
    Debug::WriteLine("Animal killed! Trophies: " + trophiesCount + ", Bullets replenished.");


    
    if (manager != nullptr && pop_frame != nullptr) {
        
        
        manager->add(new Animal(pop_frame->Width, pop_frame->Height, rand() % pop_frame->Width, rand() % pop_frame->Height));
    }

    UpdateCountLabels();

    
    
    
    
}

void MainForm::startGame() {
    if (manager == nullptr || pop_frame == nullptr) {
        Debug::WriteLine("Cannot start game: manager or pop_frame is null.");
        return;
    }
    Debug::WriteLine("Starting game...");

    
    bulletsCount = 50; 
    trophiesCount = 0;
    

    
    manager->destroyAll();
    
    
    
    
    
    Hunter* playerHunter = new Hunter(pop_frame->Width, pop_frame->Height, pop_frame->Width / 2, pop_frame->Height / 2);
    manager->add(playerHunter);
    

    
    for (int i = 0; i < 5; ++i) { 
        manager->add(new Animal(pop_frame->Width, pop_frame->Height, rand() % pop_frame->Width, rand() % pop_frame->Height));
        manager->add(new Tree(pop_frame->Width, pop_frame->Height, rand() % pop_frame->Width, rand() % pop_frame->Height));
    }
    
    for (int i = 0; i < 5; ++i) { 
        manager->add(new Ball(pop_frame->Width, pop_frame->Height, rand() % pop_frame->Width, rand() % pop_frame->Height));
        manager->add(new Triangle(pop_frame->Width, pop_frame->Height, rand() % pop_frame->Width, rand() % pop_frame->Height));
        manager->add(new ::Rectangle(pop_frame->Width, pop_frame->Height, rand() % pop_frame->Width, rand() % pop_frame->Height));
        manager->add(new Star(pop_frame->Width, pop_frame->Height, rand() % pop_frame->Width, rand() % pop_frame->Height));
    }


    UpdateCountLabels(); 

    
    moveTimer->Start();
    drawTimer->Start();
    

    
    if (startButton != nullptr) startButton->Enabled = false;
    if (stopButton != nullptr) stopButton->Enabled = true;

    Debug::WriteLine("Game Started! Initial Bullets: " + bulletsCount);
}

void MainForm::endGame(int reason) {
    Debug::WriteLine("Ending game. Reason: " + reason);

    
    if (moveTimer != nullptr) moveTimer->Stop();
    if (drawTimer != nullptr) drawTimer->Stop();
    

    
    if (startButton != nullptr) startButton->Enabled = true;
    if (stopButton != nullptr) stopButton->Enabled = false;

    
    String^ message;
    String^ caption = "Game Over";
    switch (reason) {
    case 0: 
        message = "Game Over! Hunter was killed.\n\nTrophies collected: " + trophiesCount.ToString();
        break;
    case 1: 
        message = "Game Over! Out of bullets.\n\nTrophies collected: " + trophiesCount.ToString();
        break;
    case -1: 
        message = "Game Stopped by User.\n\nTrophies collected: " + trophiesCount.ToString();
        caption = "Game Stopped";
        break;
    case 2: 
        message = "Congratulations! You won!\n\nTrophies collected: " + trophiesCount.ToString();
        caption = "Game Won!";
        break;
    default: 
        message = "Game Over!\n\nTrophies collected: " + trophiesCount.ToString();
        break;
    }

    
    MessageBox::Show(message, caption, MessageBoxButtons::OK);

    
    
    
    
}



void MainForm::OnMoveTimer(Object^ sender, EventArgs^ e) {
    
    if (this->IsDisposed || this->Disposing) return;

    
    if (!ctrlKeyPressed && manager != nullptr && moveTimer->Enabled) { 
        manager->move();

        
        UpdateCountLabels();

        
        
        bool hunterExists = false;
        if (manager != nullptr) {
            
            for (int i = 0; i < Manager::MaxObjects; ++i) { 
                if (manager->objects[i] != nullptr && dynamic_cast<Hunter*>(manager->objects[i]) != nullptr) {
                    hunterExists = true;
                    break;
                }
            }
        }

        if (!hunterExists && moveTimer->Enabled) { 
            endGame(0); 
        }
    }
}


void MainForm::OnDrawTimer(Object^ sender, EventArgs^ e) {
    if (this->IsDisposed || this->Disposing) return;
    if (pop_frame != nullptr) pop_frame->Invalidate(); 
}

void MainForm::pop_frame_Paint(Object^ sender, PaintEventArgs^ e) {
    
    if (this->IsDisposed || this->Disposing || e == nullptr || e->Graphics == nullptr) return;

    Graphics^ g = e->Graphics;
    g->SmoothingMode = SmoothingMode::AntiAlias; 
    if (manager != nullptr) {
        manager->drawFrame(g); 
    }
}



void MainForm::pop_frame_MouseDown(Object^ sender, MouseEventArgs^ e) {
    if (this->IsDisposed || this->Disposing) return;

    
    
    
    

    if (e->Button == System::Windows::Forms::MouseButtons::Left) {
        
        if (manager == nullptr || !moveTimer->Enabled) { 
            PopObject* newObject = nullptr;
            int clickX = e->X;
            int clickY = e->Y;
            int width = (pop_frame != nullptr) ? pop_frame->Width : 0;
            int height = (pop_frame != nullptr) ? pop_frame->Height : 0;

            if (width == 0 || height == 0) return;

            
            if (ballBtn->Checked) { if (manager->countBalls() < 20) newObject = new Ball(width, height, clickX, clickY); }
            else if (rectangleBtn->Checked) { if (manager->countRectangles() < 20) newObject = new ::Rectangle(width, height, clickX, clickY); }
            else if (triangleBtn->Checked) { if (manager->countTriangles() < 20) newObject = new Triangle(width, height, clickX, clickY); }
            else if (starBtn->Checked) { if (manager->countStars() < 20) newObject = new Star(width, height, clickX, clickY); }
            
            


            if (newObject != nullptr && manager != nullptr) {
                
                float speed = (static_cast<float>(rand()) / RAND_MAX * 5.0f + 1.0f); 
                float angle = static_cast<float>(rand()) / RAND_MAX * 2.0f * static_cast<float>(M_PI);
                newObject->setSpeed(speed * cos(angle), speed * sin(angle));

                manager->add(newObject);
                
            }
            else if (newObject != nullptr) {
                delete newObject; 
            }
        }
    }
    else if (e->Button == System::Windows::Forms::MouseButtons::Right) {
        
        
        if (manager != nullptr && !moveTimer->Enabled) {
            PopObject* target = manager->search(e->X, e->Y);
            if (target) {
                
                if (dynamic_cast<Hunter*>(target) == nullptr) { 
                    manager->remove(target);
                    
                }
            }
        }
    }
}

void MainForm::pop_frame_MouseUp(Object^ sender, MouseEventArgs^ e) {
    if (this->IsDisposed || this->Disposing) return;
    
}

void MainForm::pop_frame_MouseMove(Object^ sender, MouseEventArgs^ e) {
    if (this->IsDisposed || this->Disposing) return;

    
    
    if (manager != nullptr && moveTimer->Enabled) { 
        PopObject* hunterObj = nullptr;
        
        for (int i = 0; i < Manager::MaxObjects; ++i) { 
            if (manager->objects[i] != nullptr && dynamic_cast<Hunter*>(manager->objects[i]) != nullptr) {
                hunterObj = manager->objects[i];
                break; 
            }
        }

        if (hunterObj != nullptr) {
            Hunter* playerHunter = dynamic_cast<Hunter*>(hunterObj);
            if (playerHunter != nullptr) {
                
                playerHunter->setAimPosition(static_cast<float>(e->X), static_cast<float>(e->Y));
            }
        }
    }
}



void MainForm::MainForm_KeyDown(Object^ sender, KeyEventArgs^ e) {
    if (this->IsDisposed || this->Disposing) return;

    
    bool isGameRunning = (manager != nullptr && moveTimer->Enabled);

    if (isGameRunning) {
        
        PopObject* hunterObj = nullptr;
        
        for (int i = 0; i < Manager::MaxObjects; ++i) { 
            if (manager->objects[i] != nullptr && dynamic_cast<Hunter*>(manager->objects[i]) != nullptr) {
                hunterObj = manager->objects[i];
                break;
            }
        }

        if (hunterObj != nullptr) {
            
            if (e->KeyCode == Keys::Up) hunterObj->doCommand(CMD_START_UP);
            else if (e->KeyCode == Keys::Down) hunterObj->doCommand(CMD_START_DOWN);
            else if (e->KeyCode == Keys::Left) hunterObj->doCommand(CMD_START_LEFT);
            else if (e->KeyCode == Keys::Right) hunterObj->doCommand(CMD_START_RIGHT);
            else if (e->KeyCode == Keys::Space) {
                
                hunterObj->doCommand(CMD_SHOOT);
                
            }
        }
    }

    
    if (e->KeyCode == Keys::ControlKey) {
        ctrlKeyPressed = true;
        
        
    }
    
    else if (e->KeyCode == Keys::D) {
        if (manager != nullptr) {
            manager->destroyAll();
            UpdateCountLabels(); 
        }
    }
}

void MainForm::MainForm_KeyUp(Object^ sender, KeyEventArgs^ e) {
    if (this->IsDisposed || this->Disposing) return;

    
    bool isGameRunning = (manager != nullptr && moveTimer->Enabled);

    if (isGameRunning) {
        
        PopObject* hunterObj = nullptr;
        
        for (int i = 0; i < Manager::MaxObjects; ++i) { 
            if (manager->objects[i] != nullptr && dynamic_cast<Hunter*>(manager->objects[i]) != nullptr) {
                hunterObj = manager->objects[i];
                break;
            }
        }

        if (hunterObj != nullptr) {
            
            if (e->KeyCode == Keys::Up) hunterObj->doCommand(CMD_STOP_UP);
            else if (e->KeyCode == Keys::Down) hunterObj->doCommand(CMD_STOP_DOWN);
            else if (e->KeyCode == Keys::Left) hunterObj->doCommand(CMD_STOP_LEFT);
            else if (e->KeyCode == Keys::Right) hunterObj->doCommand(CMD_STOP_RIGHT);
        }
    }

    
    if (e->KeyCode == Keys::ControlKey) {
        ctrlKeyPressed = false;
        
        
    }
}

void MainForm::OnMouseWheel(Object^ sender, MouseEventArgs^ e) {
    if (this->IsDisposed || this->Disposing) return;

    
    if (manager != nullptr) {
        float factor = (e->Delta > 0) ? 1.1f : 0.9f; 
        manager->scaleSpeed(factor);
    }
}


void MainForm::startButton_Click(Object^ sender, EventArgs^ e) {
    
    if (manager != nullptr && !moveTimer->Enabled) { 
        startGame();
    }
}

void MainForm::stopButton_Click(Object^ sender, EventArgs^ e) {
    
    if (manager != nullptr && moveTimer->Enabled) { 
        endGame(-1); 
    }
}



#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")





[System::STAThreadAttribute] 
int main() {
    
    Application::EnableVisualStyles();
    
    Application::SetCompatibleTextRenderingDefault(false);

    
    MainForm^ form = gcnew MainForm();

    
    Application::Run(form);

    
    

    return 0;
}