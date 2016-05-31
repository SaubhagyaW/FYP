#pragma once

namespace FYP_ImageProcessing_UI {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for Process
	/// </summary>
	public ref class Process : public System::Windows::Forms::Form
	{
	public:
		Process(void)
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
		~Process()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::PictureBox^  video;
	private: System::Windows::Forms::PictureBox^  paths;
	private: System::Windows::Forms::Button^  quitBtn;
	private: System::Windows::Forms::Button^  detectBtn;

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
			this->video = (gcnew System::Windows::Forms::PictureBox());
			this->paths = (gcnew System::Windows::Forms::PictureBox());
			this->quitBtn = (gcnew System::Windows::Forms::Button());
			this->detectBtn = (gcnew System::Windows::Forms::Button());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->video))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->paths))->BeginInit();
			this->SuspendLayout();
			// 
			// video
			// 
			this->video->Location = System::Drawing::Point(12, 74);
			this->video->Name = L"video";
			this->video->Size = System::Drawing::Size(461, 521);
			this->video->TabIndex = 0;
			this->video->TabStop = false;
			this->video->Click += gcnew System::EventHandler(this, &Process::video_Click);
			// 
			// paths
			// 
			this->paths->Location = System::Drawing::Point(489, 12);
			this->paths->Name = L"paths";
			this->paths->Size = System::Drawing::Size(648, 583);
			this->paths->TabIndex = 1;
			this->paths->TabStop = false;
			this->paths->Click += gcnew System::EventHandler(this, &Process::video_Click);
			// 
			// quitBtn
			// 
			this->quitBtn->Location = System::Drawing::Point(165, 23);
			this->quitBtn->Name = L"quitBtn";
			this->quitBtn->Size = System::Drawing::Size(75, 23);
			this->quitBtn->TabIndex = 4;
			this->quitBtn->Text = L"Quit";
			this->quitBtn->UseVisualStyleBackColor = true;
			this->quitBtn->Click += gcnew System::EventHandler(this, &Process::quitBtn_Click);
			// 
			// detectBtn
			// 
			this->detectBtn->Location = System::Drawing::Point(12, 23);
			this->detectBtn->Name = L"detectBtn";
			this->detectBtn->Size = System::Drawing::Size(121, 23);
			this->detectBtn->TabIndex = 6;
			this->detectBtn->Text = L"Start detection";
			this->detectBtn->UseVisualStyleBackColor = true;
			this->detectBtn->Click += gcnew System::EventHandler(this, &Process::detectBtn_Click);
			// 
			// Process
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1149, 607);
			this->Controls->Add(this->detectBtn);
			this->Controls->Add(this->quitBtn);
			this->Controls->Add(this->paths);
			this->Controls->Add(this->video);
			this->Name = L"Process";
			this->Text = L"Person Following System";
			this->Load += gcnew System::EventHandler(this, &Process::Process_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->video))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->paths))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion
	public: int mode;
	private: void imageProcessing();
	private: void detect();
	private: int track();

	private: System::Void Process_Load(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void video_Click(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void quitBtn_Click(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void detectBtn_Click(System::Object^  sender, System::EventArgs^  e) {
		imageProcessing();
	}
	};
}
