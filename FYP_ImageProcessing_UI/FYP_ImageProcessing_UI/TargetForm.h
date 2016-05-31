#pragma once

namespace FYP_ImageProcessing_UI {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for TargetForm
	/// </summary>
	public ref class TargetForm : public System::Windows::Forms::Form
	{
	public:
		TargetForm(void)
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
		~TargetForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^  targetLbl;
	protected:
	private: System::Windows::Forms::TextBox^  target;
	private: System::Windows::Forms::Button^  followBtn;

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
			this->targetLbl = (gcnew System::Windows::Forms::Label());
			this->target = (gcnew System::Windows::Forms::TextBox());
			this->followBtn = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// targetLbl
			// 
			this->targetLbl->AutoSize = true;
			this->targetLbl->Location = System::Drawing::Point(64, 42);
			this->targetLbl->Name = L"targetLbl";
			this->targetLbl->Size = System::Drawing::Size(73, 13);
			this->targetLbl->TabIndex = 0;
			this->targetLbl->Text = L"Target person";
			// 
			// target
			// 
			this->target->Location = System::Drawing::Point(164, 39);
			this->target->Name = L"target";
			this->target->Size = System::Drawing::Size(39, 20);
			this->target->TabIndex = 1;
			this->target->TextChanged += gcnew System::EventHandler(this, &TargetForm::target_TextChanged);
			// 
			// followBtn
			// 
			this->followBtn->Location = System::Drawing::Point(93, 80);
			this->followBtn->Name = L"followBtn";
			this->followBtn->Size = System::Drawing::Size(75, 23);
			this->followBtn->TabIndex = 2;
			this->followBtn->Text = L"Follow";
			this->followBtn->UseVisualStyleBackColor = true;
			this->followBtn->Click += gcnew System::EventHandler(this, &TargetForm::followBtn_Click);
			// 
			// TargetForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(284, 140);
			this->Controls->Add(this->followBtn);
			this->Controls->Add(this->target);
			this->Controls->Add(this->targetLbl);
			this->Name = L"TargetForm";
			this->Load += gcnew System::EventHandler(this, &TargetForm::TargetForm_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	public: int targetIndex;

	private: System::Void target_TextChanged(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void TargetForm_Load(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void followBtn_Click(System::Object^  sender, System::EventArgs^  e) {
		targetIndex = Convert::ToInt32(this->target->Text);
		this->Close();
	}
	};
}
