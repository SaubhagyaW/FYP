#pragma once

#include "Process.h"

namespace FYP_ImageProcessing_UI {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for Home
	/// </summary>
	public ref class Home : public System::Windows::Forms::Form
	{
	public:
		Home(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Home()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^  navigationMode;
	protected:

	private: System::Windows::Forms::RadioButton^  option1;
	private: System::Windows::Forms::RadioButton^  option2;
	private: System::Windows::Forms::Button^  continueBtn;

	protected:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->navigationMode = (gcnew System::Windows::Forms::Label());
			this->option1 = (gcnew System::Windows::Forms::RadioButton());
			this->option2 = (gcnew System::Windows::Forms::RadioButton());
			this->continueBtn = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// navigationMode
			// 
			this->navigationMode->AutoSize = true;
			this->navigationMode->Location = System::Drawing::Point(43, 50);
			this->navigationMode->Name = L"navigationMode";
			this->navigationMode->Size = System::Drawing::Size(87, 13);
			this->navigationMode->TabIndex = 0;
			this->navigationMode->Text = L"Navigation mode";
			this->navigationMode->Click += gcnew System::EventHandler(this, &Home::navigationMode_Click);
			// 
			// option1
			// 
			this->option1->AutoSize = true;
			this->option1->Location = System::Drawing::Point(76, 76);
			this->option1->Name = L"option1";
			this->option1->Size = System::Drawing::Size(189, 17);
			this->option1->TabIndex = 1;
			this->option1->TabStop = true;
			this->option1->Text = L"Side-by-side accompaniment mode";
			this->option1->UseVisualStyleBackColor = true;
			this->option1->CheckedChanged += gcnew System::EventHandler(this, &Home::option1_CheckedChanged);
			// 
			// option2
			// 
			this->option2->AutoSize = true;
			this->option2->Location = System::Drawing::Point(76, 99);
			this->option2->Name = L"option2";
			this->option2->Size = System::Drawing::Size(156, 17);
			this->option2->TabIndex = 2;
			this->option2->TabStop = true;
			this->option2->Text = L"Following from behind mode";
			this->option2->UseVisualStyleBackColor = true;
			this->option2->CheckedChanged += gcnew System::EventHandler(this, &Home::option2_CheckedChanged);
			// 
			// continueBtn
			// 
			this->continueBtn->Location = System::Drawing::Point(104, 161);
			this->continueBtn->Name = L"continueBtn";
			this->continueBtn->Size = System::Drawing::Size(75, 23);
			this->continueBtn->TabIndex = 3;
			this->continueBtn->Text = L"Continue";
			this->continueBtn->UseVisualStyleBackColor = true;
			this->continueBtn->Click += gcnew System::EventHandler(this, &Home::continueBtn_Click);
			// 
			// Home
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(310, 261);
			this->Controls->Add(this->continueBtn);
			this->Controls->Add(this->option2);
			this->Controls->Add(this->option1);
			this->Controls->Add(this->navigationMode);
			this->Name = L"Home";
			this->Text = L"Person Following system";
			this->Load += gcnew System::EventHandler(this, &Home::Home_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: int mode;

	private: System::Void Home_Load(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void option1_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
		mode = 1;
	}
	private: System::Void option2_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
		mode = 2;
	}
	private: System::Void navigationMode_Click(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void continueBtn_Click(System::Object^  sender, System::EventArgs^  e) {
		FYP_ImageProcessing_UI::Process processForm;
		processForm.mode = mode;
		processForm.ShowDialog();
	}
	};
}
