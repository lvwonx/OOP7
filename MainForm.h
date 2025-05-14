#pragma once

using namespace System::ComponentModel;
using namespace System::Windows::Forms;
using namespace System::Drawing;
using namespace System::Diagnostics; 

#include "PopObject.h"
#include "Manager.h" 
#include "Ball.h"
#include "Triangle.h"
#include "Rectangle.h"
#include "Star.h"
#include "Hunter.h" 
#include "Animal.h" 
#include "Tree.h" 
#include "Bullet.h" 
#include "Explosion.h" 


#include "Pictures.h"


namespace OOP5_Asorti {
    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Windows::Forms;

    using System::Drawing::Point;
    using System::Drawing::Size;
    using System::Drawing::Color;
    using System::Drawing::Graphics;
    using System::Drawing::Drawing2D::SmoothingMode;

    
    

    public ref class MainForm : public Form {
    public:
        
        
    public: static MainForm^ form = nullptr;

          MainForm(void); 

    protected:
        
        ~MainForm();

    private:
        
        int bulletsCount;
        int trophiesCount;
        
        

        
        Timer^ moveTimer;
        Timer^ drawTimer;

        bool ctrlKeyPressed; 

        
        System::Windows::Forms::PictureBox^ pop_frame;
        System::Windows::Forms::GroupBox^ shapeGroupBox;
        System::Windows::Forms::RadioButton^ ballBtn;
        System::Windows::Forms::RadioButton^ rectangleBtn;
        System::Windows::Forms::RadioButton^ triangleBtn;
        System::Windows::Forms::RadioButton^ starBtn;

        
        System::Windows::Forms::Label^ ballLabel;
        System::Windows::Forms::Label^ ballCountLabel;
        System::Windows::Forms::Label^ rectangleLabel;
        System::Windows::Forms::Label^ rectangleCountLabel;
        System::Windows::Forms::Label^ triangleLabel;
        System::Windows::Forms::Label^ triangleCountLabel;
        System::Windows::Forms::Label^ starLabel;
        System::Windows::Forms::Label^ starCountLabel;

        
        System::Windows::Forms::Label^ bulletsLabel;
        System::Windows::Forms::Label^ bulletsCountLabel;
        System::Windows::Forms::Label^ trophiesLabel;
        System::Windows::Forms::Label^ trophiesCountLabel;

        
        System::Windows::Forms::Button^ startButton;
        System::Windows::Forms::Button^ stopButton;

        
        System::ComponentModel::Container^ components;


        
        
        void InitializeComponent(void);
        


        
        void OnMoveTimer(Object^ sender, EventArgs^ e);
        void OnDrawTimer(Object^ sender, EventArgs^ e);
        void pop_frame_Paint(Object^ sender, PaintEventArgs^ e);
        void pop_frame_MouseDown(Object^ sender, MouseEventArgs^ e);
        void pop_frame_MouseUp(Object^ sender, MouseEventArgs^ e);
        void MainForm_KeyDown(Object^ sender, KeyEventArgs^ e);
        void MainForm_KeyUp(Object^ sender, KeyEventArgs^ e);
        void OnMouseWheel(Object^ sender, MouseEventArgs^ e);
        void pop_frame_MouseMove(Object^ sender, MouseEventArgs^ e); 

        
    public: bool takeBullet();
    public: void killAnimal();
    public: void startGame();
    public: void endGame(int reason); 

          
          void UpdateCountLabels();

          
          void startButton_Click(Object^ sender, EventArgs^ e);
          void stopButton_Click(Object^ sender, EventArgs^ e);
    };
}