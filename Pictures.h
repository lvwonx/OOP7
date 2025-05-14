#pragma once

using namespace System;
using namespace System::Drawing;
using namespace System::Resources;
using namespace System::Reflection; 

ref class Pictures {
private:
    
    static Bitmap^ LoadBitmap(String^ bitmapNameInResources) {
        
        
        
        
        
        
        
        
        String^ resourceManagerPath = "MainForm.resx"; 

        Assembly^ asmExec = Assembly::GetExecutingAssembly();

        try {
            ResourceManager^ resman = gcnew ResourceManager(resourceManagerPath, asmExec);
            return (Bitmap^)resman->GetObject(bitmapNameInResources);
        }
        catch (Exception^ ex) {
            
            System::Diagnostics::Debug::WriteLine("Failed to load bitmap: " + bitmapNameInResources);
            System::Diagnostics::Debug::WriteLine("Error: " + ex->Message);
            System::Diagnostics::Debug::WriteLine("Make sure '" + resourceManagerPath + "' is correct and '" + bitmapNameInResources + "' exists in the resource file.");
            
            
            
            
            
            
            return nullptr; 
        }
    }

public:
    
    
    
    
    

    static Bitmap^ HunterBitmap = LoadBitmap("HunterImageFromResources");   
    static Bitmap^ AnimalBitmap = LoadBitmap("AnimalImageFromResources");   
    static Bitmap^ TreeBitmap = LoadBitmap("TreeImageFromResources");     
    static Bitmap^ BulletBitmap = LoadBitmap("BulletImageFromResources");   

    
    
};