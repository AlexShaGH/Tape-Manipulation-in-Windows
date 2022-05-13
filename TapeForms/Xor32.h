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
	/// Summary for Xor32
	/// </summary>
	public ref class Xor32 : public System::Windows::Forms::Form
	{
	public:
		Xor32(void)
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
		~Xor32()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::OpenFileDialog^  openFileDialog1;
	protected: 
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::TextBox^  textBox1;
	private: System::Windows::Forms::RichTextBox^  richTextBox1;
	private: System::Windows::Forms::Button^  buttonXor16;
	private: System::Windows::Forms::Button^  buttonXor32;

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
			this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->richTextBox1 = (gcnew System::Windows::Forms::RichTextBox());
			this->buttonXor16 = (gcnew System::Windows::Forms::Button());
			this->buttonXor32 = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// openFileDialog1
			// 
			this->openFileDialog1->FileName = L"openFileDialog1";
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(395, 28);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(75, 23);
			this->button1->TabIndex = 0;
			this->button1->Text = L"File";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &Xor32::button1_Click);
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(40, 30);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(334, 20);
			this->textBox1->TabIndex = 1;
			// 
			// richTextBox1
			// 
			this->richTextBox1->Location = System::Drawing::Point(40, 79);
			this->richTextBox1->Name = L"richTextBox1";
			this->richTextBox1->Size = System::Drawing::Size(334, 171);
			this->richTextBox1->TabIndex = 2;
			this->richTextBox1->Text = L"";
			// 
			// buttonXor16
			// 
			this->buttonXor16->Location = System::Drawing::Point(395, 79);
			this->buttonXor16->Name = L"buttonXor16";
			this->buttonXor16->Size = System::Drawing::Size(75, 23);
			this->buttonXor16->TabIndex = 3;
			this->buttonXor16->Text = L"XOR16";
			this->buttonXor16->UseVisualStyleBackColor = true;
			this->buttonXor16->Click += gcnew System::EventHandler(this, &Xor32::buttonXor16_Click);
			// 
			// buttonXor32
			// 
			this->buttonXor32->Location = System::Drawing::Point(395, 123);
			this->buttonXor32->Name = L"buttonXor32";
			this->buttonXor32->Size = System::Drawing::Size(75, 23);
			this->buttonXor32->TabIndex = 4;
			this->buttonXor32->Text = L"XOR32";
			this->buttonXor32->UseVisualStyleBackColor = true;
			this->buttonXor32->Click += gcnew System::EventHandler(this, &Xor32::buttonXor32_Click);
			// 
			// Xor32
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(494, 262);
			this->Controls->Add(this->buttonXor32);
			this->Controls->Add(this->buttonXor16);
			this->Controls->Add(this->richTextBox1);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->button1);
			this->Name = L"Xor32";
			this->Text = L"Xor32";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {

				

				 if(openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK)
				 {
					 textBox1->Text = openFileDialog1->FileName;
				 }
				 else return;
/*
				 richTextBox1->AppendText("Open " + openFileDialog1->FileName + "\n");

				 FileStream^ fStream = gcnew FileStream(openFileDialog1->FileName, System::IO::FileMode::Open, System::IO::FileAccess::Read, System::IO::FileShare::Read);
				 
				 Int64 fileSize = fStream->Length;

				 richTextBox1->AppendText("File Size: " + fileSize.ToString() + "\n");

				 Boolean isAligned = false;

				 if (fileSize % 4 == 0)
				 {
					 isAligned = true;
				 }

				 richTextBox1->AppendText("Aligned by 4: " + isAligned.ToString() + "\n");

				 if (!isAligned)
				 {
					  richTextBox1->AppendText("Unable to calculate XOR" + "\n");
					  return;
				 }

				 UInt32 rdDWord = 0;
				 UInt32 xorData = 0;

				 fStream->Position =0;

				 BinaryReader^ rd = gcnew BinaryReader(fStream);

				 for (Int64 i=0; i < fileSize/4; i++)
				 {
					 rdDWord = rd->ReadUInt32();
					 xorData = xorData ^ rdDWord;
				 }

				 richTextBox1->AppendText("XOR " + xorData.ToString("X")+ "\n");*/




				 
			 }
	private: System::Void buttonXor16_Click(System::Object^  sender, System::EventArgs^  e) {

				 richTextBox1->AppendText("Open " + openFileDialog1->FileName + "\n");

				 FileStream^ fStream = gcnew FileStream(openFileDialog1->FileName, System::IO::FileMode::Open, System::IO::FileAccess::Read, System::IO::FileShare::Read);

				 Int64 fileSize = fStream->Length;

				 richTextBox1->AppendText("File Size: " + fileSize.ToString() + "\n");

				 Boolean isAligned = false;

				 if (fileSize % 2 == 0)
				 {
					 isAligned = true;
				 }

				 richTextBox1->AppendText("Aligned by 2: " + isAligned.ToString() + "\n");

				 if (!isAligned)
				 {
					 richTextBox1->AppendText("Unable to calculate XOR" + "\n");
					 return;
				 }

				 UInt16 rdWord = 0;
				 UInt16 xorData = 0;

				 fStream->Position =0;

				 BinaryReader^ rd = gcnew BinaryReader(fStream);

				 for (Int64 i=0; i < fileSize/2; i++)
				 {
					 rdWord = rd->ReadUInt16();
					 xorData = xorData ^ rdWord;
				 }

				 richTextBox1->AppendText("XOR " + xorData.ToString("X")+ "\n");
			 }
private: System::Void buttonXor32_Click(System::Object^  sender, System::EventArgs^  e) {


			 richTextBox1->AppendText("Open " + openFileDialog1->FileName + "\n");

			 FileStream^ fStream = gcnew FileStream(openFileDialog1->FileName, System::IO::FileMode::Open, System::IO::FileAccess::Read, System::IO::FileShare::Read);

			 Int64 fileSize = fStream->Length;

			 richTextBox1->AppendText("File Size: " + fileSize.ToString() + "\n");

			 Boolean isAligned = false;

			 if (fileSize % 4 == 0)
			 {
				 isAligned = true;
			 }

			 richTextBox1->AppendText("Aligned by 4: " + isAligned.ToString() + "\n");

			 if (!isAligned)
			 {
				 richTextBox1->AppendText("Unable to calculate XOR" + "\n");
				 return;
			 }

			 UInt32 rdDWord = 0;
			 UInt32 xorData = 0;

			 fStream->Position =0;

			 BinaryReader^ rd = gcnew BinaryReader(fStream);

			 for (Int64 i=0; i < fileSize/4; i++)
			 {
				 rdDWord = rd->ReadUInt32();
				 xorData = xorData ^ rdDWord;
			 }

			 richTextBox1->AppendText("XOR " + xorData.ToString("X")+ "\n");
		 }
};
}
