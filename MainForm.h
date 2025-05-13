#pragma once

using namespace System::ComponentModel;
using namespace System::Windows::Forms;
using namespace System::Drawing;
using namespace System::Diagnostics; // For Debug output

#include "PopObject.h"
#include "Manager.h" // Includes the global manager declaration (now with public objects)
#include "Ball.h"
#include "Triangle.h"
#include "Rectangle.h"
#include "Star.h"
#include "Hunter.h" // Need Hunter type
#include "Animal.h" // Need Animal type
#include "Tree.h" // Need Tree type
#include "Bullet.h" // Need Bullet type
#include "Explosion.h" // Need Explosion type

// Include Pictures.h here
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

    // Forward declare the MainForm class if not already included (it is here, but good practice)
    // ref class MainForm;

    public ref class MainForm : public Form {
    public:
        // Static member to hold a pointer to the form instance (Section 7.3 & 7.9.3)
        // Initialize static managed member here
    public: static MainForm^ form = nullptr;

          MainForm(void); // Constructor declaration

    protected:
        // Destructor declaration
        ~MainForm();

    private:
        // Game State Variables (Section 7.8 & 7.9.10)
        int bulletsCount;
        int trophiesCount;
        // Timer for game duration/score? (Optional)
        // System::Windows::Forms::Timer^ gameTimer;

        // Managed timer objects
        Timer^ moveTimer;
        Timer^ drawTimer;

        bool ctrlKeyPressed; // Example for pausing/speed control

        // UI Controls - Declarations only
        System::Windows::Forms::PictureBox^ pop_frame;
        System::Windows::Forms::GroupBox^ shapeGroupBox;
        System::Windows::Forms::RadioButton^ ballBtn;
        System::Windows::Forms::RadioButton^ rectangleBtn;
        System::Windows::Forms::RadioButton^ triangleBtn;
        System::Windows::Forms::RadioButton^ starBtn;

        // Labels for displaying counts
        System::Windows::Forms::Label^ ballLabel;
        System::Windows::Forms::Label^ ballCountLabel;
        System::Windows::Forms::Label^ rectangleLabel;
        System::Windows::Forms::Label^ rectangleCountLabel;
        System::Windows::Forms::Label^ triangleLabel;
        System::Windows::Forms::Label^ triangleCountLabel;
        System::Windows::Forms::Label^ starLabel;
        System::Windows::Forms::Label^ starCountLabel;

        // Labels for game-specific counts (Bullets, Trophies)
        System::Windows::Forms::Label^ bulletsLabel;
        System::Windows::Forms::Label^ bulletsCountLabel;
        System::Windows::Forms::Label^ trophiesLabel;
        System::Windows::Forms::Label^ trophiesCountLabel;

        // Start/Stop buttons
        System::Windows::Forms::Button^ startButton;
        System::Windows::Forms::Button^ stopButton;

        // Required designer variable
        System::ComponentModel::Container^ components;


        // --- Windows Form Designer generated code ---
        // Declare the InitializeComponent method (Implementation is in the .cpp file)
        void InitializeComponent(void);
        // --- END Windows Form Designer generated code ---


        // Event Handlers - Declarations only
        void OnMoveTimer(Object^ sender, EventArgs^ e);
        void OnDrawTimer(Object^ sender, EventArgs^ e);
        void pop_frame_Paint(Object^ sender, PaintEventArgs^ e);
        void pop_frame_MouseDown(Object^ sender, MouseEventArgs^ e);
        void pop_frame_MouseUp(Object^ sender, MouseEventArgs^ e);
        void MainForm_KeyDown(Object^ sender, KeyEventArgs^ e);
        void MainForm_KeyUp(Object^ sender, KeyEventArgs^ e);
        void OnMouseWheel(Object^ sender, MouseEventArgs^ e);
        void pop_frame_MouseMove(Object^ sender, MouseEventArgs^ e); // Added for aiming

        // New methods for game state management (Section 7.8 & 7.9.10) - Declarations
    public: bool takeBullet();
    public: void killAnimal();
    public: void startGame();
    public: void endGame(int reason); // 0: Hunter killed, 1: Out of bullets, -1: User stopped, 2: Win

          // Helper method to update all UI count labels
          void UpdateCountLabels();

          // Event handlers for Start/Stop buttons
          void startButton_Click(Object^ sender, EventArgs^ e);
          void stopButton_Click(Object^ sender, EventArgs^ e);
    };
}