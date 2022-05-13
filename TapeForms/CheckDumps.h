#pragma once

namespace TapeForms {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::IO;

	/// <summary>
	/// Summary for CheckDumps
	/// </summary>
	public ref class CheckDumps : public System::Windows::Forms::Form
	{
	public:
		CheckDumps(void)
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
		~CheckDumps()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::FolderBrowserDialog^  folderBrowserDialog1;
	protected: 
	private: System::Windows::Forms::RichTextBox^  richTextBoxLog;
	private: System::Windows::Forms::TextBox^  textBoxFolder;
	private: System::Windows::Forms::Button^  btnFolder;
	private: System::Windows::Forms::Button^  btnRun;
	private: System::Windows::Forms::Button^  btnRename;

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
			this->folderBrowserDialog1 = (gcnew System::Windows::Forms::FolderBrowserDialog());
			this->richTextBoxLog = (gcnew System::Windows::Forms::RichTextBox());
			this->textBoxFolder = (gcnew System::Windows::Forms::TextBox());
			this->btnFolder = (gcnew System::Windows::Forms::Button());
			this->btnRun = (gcnew System::Windows::Forms::Button());
			this->btnRename = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// richTextBoxLog
			// 
			this->richTextBoxLog->Location = System::Drawing::Point(12, 61);
			this->richTextBoxLog->Name = L"richTextBoxLog";
			this->richTextBoxLog->Size = System::Drawing::Size(456, 189);
			this->richTextBoxLog->TabIndex = 0;
			this->richTextBoxLog->Text = L"";
			// 
			// textBoxFolder
			// 
			this->textBoxFolder->Location = System::Drawing::Point(13, 13);
			this->textBoxFolder->Name = L"textBoxFolder";
			this->textBoxFolder->Size = System::Drawing::Size(255, 20);
			this->textBoxFolder->TabIndex = 1;
			this->textBoxFolder->Text = L"D:\\";
			// 
			// btnFolder
			// 
			this->btnFolder->Location = System::Drawing::Point(295, 13);
			this->btnFolder->Name = L"btnFolder";
			this->btnFolder->Size = System::Drawing::Size(75, 23);
			this->btnFolder->TabIndex = 2;
			this->btnFolder->Text = L"Folder";
			this->btnFolder->UseVisualStyleBackColor = true;
			this->btnFolder->Click += gcnew System::EventHandler(this, &CheckDumps::btnFolder_Click);
			// 
			// btnRun
			// 
			this->btnRun->Location = System::Drawing::Point(393, 12);
			this->btnRun->Name = L"btnRun";
			this->btnRun->Size = System::Drawing::Size(75, 23);
			this->btnRun->TabIndex = 3;
			this->btnRun->Text = L"Check";
			this->btnRun->UseVisualStyleBackColor = true;
			this->btnRun->Click += gcnew System::EventHandler(this, &CheckDumps::btnRun_Click);
			// 
			// btnRename
			// 
			this->btnRename->Location = System::Drawing::Point(484, 12);
			this->btnRename->Name = L"btnRename";
			this->btnRename->Size = System::Drawing::Size(75, 23);
			this->btnRename->TabIndex = 4;
			this->btnRename->Text = L"Rename";
			this->btnRename->UseVisualStyleBackColor = true;
			this->btnRename->Click += gcnew System::EventHandler(this, &CheckDumps::btnRename_Click);
			// 
			// CheckDumps
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(583, 262);
			this->Controls->Add(this->btnRename);
			this->Controls->Add(this->btnRun);
			this->Controls->Add(this->btnFolder);
			this->Controls->Add(this->textBoxFolder);
			this->Controls->Add(this->richTextBoxLog);
			this->Name = L"CheckDumps";
			this->Text = L"CheckDumps";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void btnFolder_Click(System::Object^  sender, System::EventArgs^  e) {
				 this->folderBrowserDialog1->SelectedPath = this->textBoxFolder->Text;
				 

				 if(folderBrowserDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK)
				 {
					 this->textBoxFolder->Text = this->folderBrowserDialog1->SelectedPath;
				 }
			 }
	private: System::Void btnRun_Click(System::Object^  sender, System::EventArgs^  e) {

				 Windows::Forms::Cursor^ tempCursor = this->Cursor;
				 this->Cursor = Cursors::WaitCursor;

				 String^ logEntry = "Processing files in folder " + folderBrowserDialog1->SelectedPath + "\n";
				 this->richTextBoxLog->AppendText(logEntry);

				 logEntry = "FileName,Block#,Size,Name???\n";
				 this->richTextBoxLog->AppendText(logEntry);

				 DirectoryInfo^ dir = gcnew DirectoryInfo(folderBrowserDialog1->SelectedPath);

				 //FileStream^ logFile = gcnew FileStream()

				 StreamWriter^ logFile = gcnew StreamWriter(dir->Name + "-list.csv");
				 logFile->Write(logEntry);
 
				 
				 for each (FileInfo^ fl in dir->GetFiles("*.dat"))
				 {
					 StreamReader^ sr = fl->OpenText();
					 if (fl->Length > 0 && sr->ReadLine()->Contains("ARCHIVE-TPFSYS"))
					 {
	 					 logEntry = fl->Name + 
							 "," + 
							 (sr->ReadLine())->Remove(0,2) + 
							 "," + 
							 sr->ReadLine() +
							 "," + 
							 sr->ReadLine() +
							 "\n";


						 this->richTextBoxLog->AppendText(logEntry);
						 logFile->Write(logEntry);
					 }

					 sr->Close();


				 }

				 logFile->Close();
				 this->richTextBoxLog->AppendText("Done\n");
				 this->Cursor = tempCursor;
				 tempCursor = nullptr;


			 }
private: System::Void btnRename_Click(System::Object^  sender, System::EventArgs^  e) {

			 Windows::Forms::Cursor^ tempCursor = this->Cursor;
			 this->Cursor = Cursors::WaitCursor;

			 String^ logEntry = "Renaming files in folder " + folderBrowserDialog1->SelectedPath + "\n";
			 this->richTextBoxLog->AppendText(logEntry);

			 logEntry = "Original File Name, New File Name\n";
			 this->richTextBoxLog->AppendText(logEntry);

			 DirectoryInfo^ dir = gcnew DirectoryInfo(folderBrowserDialog1->SelectedPath);

			 StreamWriter^ logFile = gcnew StreamWriter(dir->Name + "-rename.csv");
			 logFile->Write(logEntry);

			 String^ newName = String::Empty;
			 String^ oldName = String::Empty;
			 String^ digitsNamePart = String::Empty;
			 Int32 fileNumber = 0;

			 for each (FileInfo^ fl in dir->GetFiles("*.dat"))
			 {
				 // form new name
				 oldName = fl->Name;

				 digitsNamePart = oldName->Remove(0,4);
				 digitsNamePart = digitsNamePart->Remove(6);

				 fileNumber = Int32::Parse(digitsNamePart,System::Globalization::NumberStyles::HexNumber);

				 digitsNamePart = fileNumber.ToString("000000");
				 newName = digitsNamePart + ".bin";

				 logEntry = oldName + ", " + newName + "\n";

				 
					fl->MoveTo(dir->FullName + "\\" + newName);
				 

					 this->richTextBoxLog->AppendText(logEntry);
					 logFile->Write(logEntry);

					 this->Update();

			 }

			 logFile->Close();
			 this->richTextBoxLog->AppendText("Done\n");
			 this->Cursor = tempCursor;
			 tempCursor = nullptr;
		 }
};
}
