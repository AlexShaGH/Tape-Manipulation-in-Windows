#pragma once

#include "SenseDecoder.h"

using namespace System::Globalization;


namespace TapeForms {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for SNSDecoder
	/// </summary>
	public ref class SNSDecoder : public System::Windows::Forms::Form
	{
	public:
		SNSDecoder(void)
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
		~SNSDecoder()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  buttonSNSDecode;
	private: System::Windows::Forms::Button^  buttonSNSCancel;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::TextBox^  textBoxSNSKey;
	private: System::Windows::Forms::TextBox^  textBoxASC;
	private: System::Windows::Forms::TextBox^  textBoxASCQ;
	private: System::Windows::Forms::TextBox^  textBoxFRU;



	protected: 

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
			this->buttonSNSDecode = (gcnew System::Windows::Forms::Button());
			this->buttonSNSCancel = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->textBoxSNSKey = (gcnew System::Windows::Forms::TextBox());
			this->textBoxASC = (gcnew System::Windows::Forms::TextBox());
			this->textBoxASCQ = (gcnew System::Windows::Forms::TextBox());
			this->textBoxFRU = (gcnew System::Windows::Forms::TextBox());
			this->SuspendLayout();
			// 
			// buttonSNSDecode
			// 
			this->buttonSNSDecode->Location = System::Drawing::Point(183, 12);
			this->buttonSNSDecode->Name = L"buttonSNSDecode";
			this->buttonSNSDecode->Size = System::Drawing::Size(75, 23);
			this->buttonSNSDecode->TabIndex = 0;
			this->buttonSNSDecode->Text = L"Decode";
			this->buttonSNSDecode->UseVisualStyleBackColor = true;
			this->buttonSNSDecode->Click += gcnew System::EventHandler(this, &SNSDecoder::buttonSNSDecode_Click);
			// 
			// buttonSNSCancel
			// 
			this->buttonSNSCancel->DialogResult = System::Windows::Forms::DialogResult::Cancel;
			this->buttonSNSCancel->Location = System::Drawing::Point(183, 54);
			this->buttonSNSCancel->Name = L"buttonSNSCancel";
			this->buttonSNSCancel->Size = System::Drawing::Size(75, 23);
			this->buttonSNSCancel->TabIndex = 1;
			this->buttonSNSCancel->Text = L"Cancel";
			this->buttonSNSCancel->UseVisualStyleBackColor = true;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(10, 15);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(53, 13);
			this->label1->TabIndex = 2;
			this->label1->Text = L"SNS Key:";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(10, 45);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(31, 13);
			this->label2->TabIndex = 3;
			this->label2->Text = L"ASC:";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(10, 75);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(39, 13);
			this->label3->TabIndex = 4;
			this->label3->Text = L"ASCQ:";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(10, 105);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(32, 13);
			this->label4->TabIndex = 5;
			this->label4->Text = L"FRU:";
			// 
			// textBoxSNSKey
			// 
			this->textBoxSNSKey->Location = System::Drawing::Point(70, 15);
			this->textBoxSNSKey->Name = L"textBoxSNSKey";
			this->textBoxSNSKey->Size = System::Drawing::Size(30, 20);
			this->textBoxSNSKey->TabIndex = 6;
			this->textBoxSNSKey->Text = L"00";
			// 
			// textBoxASC
			// 
			this->textBoxASC->Location = System::Drawing::Point(70, 45);
			this->textBoxASC->Name = L"textBoxASC";
			this->textBoxASC->Size = System::Drawing::Size(30, 20);
			this->textBoxASC->TabIndex = 7;
			this->textBoxASC->Text = L"00";
			// 
			// textBoxASCQ
			// 
			this->textBoxASCQ->Location = System::Drawing::Point(70, 75);
			this->textBoxASCQ->Name = L"textBoxASCQ";
			this->textBoxASCQ->Size = System::Drawing::Size(30, 20);
			this->textBoxASCQ->TabIndex = 8;
			this->textBoxASCQ->Text = L"00";
			// 
			// textBoxFRU
			// 
			this->textBoxFRU->Location = System::Drawing::Point(70, 105);
			this->textBoxFRU->Name = L"textBoxFRU";
			this->textBoxFRU->Size = System::Drawing::Size(30, 20);
			this->textBoxFRU->TabIndex = 9;
			this->textBoxFRU->Text = L"00";
			// 
			// SNSDecoder
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->CancelButton = this->buttonSNSCancel;
			this->ClientSize = System::Drawing::Size(284, 262);
			this->Controls->Add(this->textBoxFRU);
			this->Controls->Add(this->textBoxASCQ);
			this->Controls->Add(this->textBoxASC);
			this->Controls->Add(this->textBoxSNSKey);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->buttonSNSCancel);
			this->Controls->Add(this->buttonSNSDecode);
			this->Name = L"SNSDecoder";
			this->Text = L"SNSDecoder";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void buttonSNSDecode_Click(System::Object^  sender, System::EventArgs^  e) {

				 ERROR_SNS_INFO^ snsInfo = gcnew ERROR_SNS_INFO();
				 snsInfo->SNSKey = Byte::Parse(this->textBoxSNSKey->Text, NumberStyles::HexNumber);
				 snsInfo->ASC = Byte::Parse(this->textBoxASC->Text, NumberStyles::HexNumber);
				 snsInfo->ASCQ = Byte::Parse(this->textBoxASCQ->Text, NumberStyles::HexNumber);
				 snsInfo->FRU = Byte::Parse(this->textBoxFRU->Text, NumberStyles::HexNumber);

				 String^ decodedMsg = SenseDecoder::DecodeSense(snsInfo);

				 MessageBox::Show(decodedMsg);
			 }
};
}
