#pragma once

using namespace System;
using namespace System::Drawing;
using namespace System::Resources;
using namespace System::Reflection; // Required for Assembly

ref class Pictures {
private:
    // Helper method to load a bitmap from resources
    static Bitmap^ LoadBitmap(String^ bitmapNameInResources) {
        // =======================================================================================
        // !!! IMPORTANT: YOU MUST CUSTOMIZE THIS PATH !!!
        // Replace "YourProjectName.PicturesResxFileName" with your actual project's root namespace
        // and the name of your .resx file.
        // Example: If your project namespace is "MyGame" and your resource file is "GameArt.resx",
        // this might be "MyGame.GameArt".
        // The PDF used "Project.Pictures". Check your project's properties for the root namespace.
        // =======================================================================================
        String^ resourceManagerPath = "MainForm.resx"; // <--- CUSTOMIZE THIS

        Assembly^ asmExec = Assembly::GetExecutingAssembly();

        try {
            ResourceManager^ resman = gcnew ResourceManager(resourceManagerPath, asmExec);
            return (Bitmap^)resman->GetObject(bitmapNameInResources);
        }
        catch (Exception^ ex) {
            // Output error to debug console if resource loading fails
            System::Diagnostics::Debug::WriteLine("Failed to load bitmap: " + bitmapNameInResources);
            System::Diagnostics::Debug::WriteLine("Error: " + ex->Message);
            System::Diagnostics::Debug::WriteLine("Make sure '" + resourceManagerPath + "' is correct and '" + bitmapNameInResources + "' exists in the resource file.");
            // You might want to list available resources to help debug:
            // array<String^>^ names = asmExec->GetManifestResourceNames();
            // System::Diagnostics::Debug::WriteLine("Available manifest resources:");
            // for each (String^ name in names) {
            //     System::Diagnostics::Debug::WriteLine(" - " + name);
            // }
            return nullptr; // Return null if loading failed
        }
    }

public:
    // =======================================================================================
    // !!! IMPORTANT: UNCOMMENT AND CUSTOMIZE THESE LINES FOR EACH IMAGE YOU USE !!!
    // Replace "HunterImageFromResources" with the actual name of your hunter image 
    // AS IT APPEARS IN YOUR .resx FILE (usually without the file extension).
    // =======================================================================================

    static Bitmap^ HunterBitmap = LoadBitmap("HunterImageFromResources");   // <--- UNCOMMENTED & CUSTOMIZE "HunterImageFromResources"
    static Bitmap^ AnimalBitmap = LoadBitmap("AnimalImageFromResources");   // <--- UNCOMMENTED & CUSTOMIZE "AnimalImageFromResources"
    static Bitmap^ TreeBitmap = LoadBitmap("TreeImageFromResources");     // <--- UNCOMMENTED & CUSTOMIZE "TreeImageFromResources"
    static Bitmap^ BulletBitmap = LoadBitmap("BulletImageFromResources");   // <--- UNCOMMENTED & CUSTOMIZE "BulletImageFromResources"

    // Add more static Bitmap members for other images as needed:
    // static Bitmap^ ExplosionSpriteSheet = LoadBitmap("ExplosionEffects"); 
};