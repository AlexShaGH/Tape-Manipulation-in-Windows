#pragma once

#include "TapeDriveWinAPI.h"
#include "TapeDriveSCSI.h"
#include "SNSDecoder.h"
#include "SenseDecoder.h"
#include "WriteTest.h"
#include "RangeRecord.h"
#include "TapeImage.h"
#include "Xor32.h"
#include "CheckDumps.h"

namespace TapeForms {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for Form1
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//

			this->comboBoxTape->SelectedIndex = 0;
			this->comboBoxReadMethod->SelectedIndex = 0;

		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  button_Load;
	protected: 
	private: System::Windows::Forms::Button^  button_Unload;
	private: System::Windows::Forms::Button^  button_Lock;
	private: System::Windows::Forms::Button^  button_Unlock;
	private: System::Windows::Forms::Button^  button_AdjustTention;
	private: System::Windows::Forms::Button^  button_EOD;
	private: System::Windows::Forms::Button^  button_Rewind;
	private: System::Windows::Forms::Button^  button_AbsBlk;
	private: System::Windows::Forms::Button^  button_Format;
	private: System::Windows::Forms::Button^  button_LogBlk;
	private: System::Windows::Forms::Button^  button_SpaceFM;
	private: System::Windows::Forms::Button^  button_SpaceBlks;
	private: System::Windows::Forms::Button^  button_SpaceSFM;
	private: System::Windows::Forms::Button^  button_GetStatus;
	private: System::Windows::Forms::Button^  button_logicalPos;
	private: System::Windows::Forms::Button^  buttonAbsPos;
	private: System::Windows::Forms::Button^  button_MediaParams;
	private: System::Windows::Forms::Button^  button_SetBlkSize;
	private: System::Windows::Forms::Button^  button_SetDriveParams;
	private: System::Windows::Forms::Button^  button_CreatePart;
	private: System::Windows::Forms::Button^  button_Erase;
	private: System::Windows::Forms::Button^  button_WriteTpM3;
	private: System::Windows::Forms::Button^  button_Write1GB;
	private: System::Windows::Forms::Button^  button_Read;
	private: System::Windows::Forms::Button^  button_SizeOf;
	private: System::Windows::Forms::Button^  button_LoadSCSI;
	private: System::Windows::Forms::Button^  btnUnloadSCSI;
	private: System::Windows::Forms::Button^  buttonFormat;
	private: System::Windows::Forms::TextBox^  textBoxFormatType;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Button^  buttonEraseSCSI;
	private: System::Windows::Forms::CheckBox^  checkBoxLongErase;
	private: System::Windows::Forms::Button^  buttonRewindSCSI;
	private: System::Windows::Forms::Button^  buttonPositionShort;
	private: System::Windows::Forms::Button^  buttonPositionLong;
	private: System::Windows::Forms::Button^  buttonPositionExtnd;
	private: System::Windows::Forms::Button^  buttonLocateEOD;
	private: System::Windows::Forms::TextBox^  textBoxPartition;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Button^  buttonLocateBOP;
	private: System::Windows::Forms::Button^  buttonLocate;
	private: System::Windows::Forms::TextBox^  textBoxBlockNumber;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::TextBox^  textBoxSpace;
	private: System::Windows::Forms::ComboBox^  comboBoxObjectType;
	private: System::Windows::Forms::Button^  buttonSpace;
	private: System::Windows::Forms::Label^  label5;
	private: System::Windows::Forms::TextBox^  textBoxFileMarks;
	private: System::Windows::Forms::Button^  buttonWriteFMSCSI;
	private: System::Windows::Forms::TextBox^  textBoxBlkSize;
	private: System::Windows::Forms::Label^  label6;
	private: System::Windows::Forms::Button^  buttonSetBlkSize;
	private: System::Windows::Forms::Button^  buttonRequestSNS;
	private: System::Windows::Forms::Button^  buttonGetBlkSize;
	private: System::Windows::Forms::ComboBox^  comboBoxTape;
	private: System::Windows::Forms::Label^  label7;
	private: System::Windows::Forms::TextBox^  textBoxReadSize;
	private: System::Windows::Forms::ComboBox^  comboBoxReadMethod;
	private: System::Windows::Forms::Button^  buttonReadSCSI;
	private: System::Windows::Forms::Button^  buttonWrt1GBSCSI;
	private: System::Windows::Forms::Button^  buttonWrtVar;
	private: System::Windows::Forms::Button^  buttonSNSDcdr;
	private: System::Windows::Forms::Button^  buttonWrtTst;
	private: System::Windows::Forms::Button^  buttonReadPt1;
	private: System::Windows::Forms::Button^  buttonXmlTst;
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::Button^  btnChkDmps;


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
			this->button_Load = (gcnew System::Windows::Forms::Button());
			this->button_Unload = (gcnew System::Windows::Forms::Button());
			this->button_Lock = (gcnew System::Windows::Forms::Button());
			this->button_Unlock = (gcnew System::Windows::Forms::Button());
			this->button_AdjustTention = (gcnew System::Windows::Forms::Button());
			this->button_EOD = (gcnew System::Windows::Forms::Button());
			this->button_Rewind = (gcnew System::Windows::Forms::Button());
			this->button_AbsBlk = (gcnew System::Windows::Forms::Button());
			this->button_Format = (gcnew System::Windows::Forms::Button());
			this->button_LogBlk = (gcnew System::Windows::Forms::Button());
			this->button_SpaceFM = (gcnew System::Windows::Forms::Button());
			this->button_SpaceBlks = (gcnew System::Windows::Forms::Button());
			this->button_SpaceSFM = (gcnew System::Windows::Forms::Button());
			this->button_GetStatus = (gcnew System::Windows::Forms::Button());
			this->button_logicalPos = (gcnew System::Windows::Forms::Button());
			this->buttonAbsPos = (gcnew System::Windows::Forms::Button());
			this->button_MediaParams = (gcnew System::Windows::Forms::Button());
			this->button_SetBlkSize = (gcnew System::Windows::Forms::Button());
			this->button_SetDriveParams = (gcnew System::Windows::Forms::Button());
			this->button_CreatePart = (gcnew System::Windows::Forms::Button());
			this->button_Erase = (gcnew System::Windows::Forms::Button());
			this->button_WriteTpM3 = (gcnew System::Windows::Forms::Button());
			this->button_Write1GB = (gcnew System::Windows::Forms::Button());
			this->button_Read = (gcnew System::Windows::Forms::Button());
			this->button_SizeOf = (gcnew System::Windows::Forms::Button());
			this->button_LoadSCSI = (gcnew System::Windows::Forms::Button());
			this->btnUnloadSCSI = (gcnew System::Windows::Forms::Button());
			this->buttonFormat = (gcnew System::Windows::Forms::Button());
			this->textBoxFormatType = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->buttonEraseSCSI = (gcnew System::Windows::Forms::Button());
			this->checkBoxLongErase = (gcnew System::Windows::Forms::CheckBox());
			this->buttonRewindSCSI = (gcnew System::Windows::Forms::Button());
			this->buttonPositionShort = (gcnew System::Windows::Forms::Button());
			this->buttonPositionLong = (gcnew System::Windows::Forms::Button());
			this->buttonPositionExtnd = (gcnew System::Windows::Forms::Button());
			this->buttonLocateEOD = (gcnew System::Windows::Forms::Button());
			this->textBoxPartition = (gcnew System::Windows::Forms::TextBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->buttonLocateBOP = (gcnew System::Windows::Forms::Button());
			this->buttonLocate = (gcnew System::Windows::Forms::Button());
			this->textBoxBlockNumber = (gcnew System::Windows::Forms::TextBox());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->textBoxSpace = (gcnew System::Windows::Forms::TextBox());
			this->comboBoxObjectType = (gcnew System::Windows::Forms::ComboBox());
			this->buttonSpace = (gcnew System::Windows::Forms::Button());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->textBoxFileMarks = (gcnew System::Windows::Forms::TextBox());
			this->buttonWriteFMSCSI = (gcnew System::Windows::Forms::Button());
			this->textBoxBlkSize = (gcnew System::Windows::Forms::TextBox());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->buttonSetBlkSize = (gcnew System::Windows::Forms::Button());
			this->buttonRequestSNS = (gcnew System::Windows::Forms::Button());
			this->buttonGetBlkSize = (gcnew System::Windows::Forms::Button());
			this->comboBoxTape = (gcnew System::Windows::Forms::ComboBox());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->textBoxReadSize = (gcnew System::Windows::Forms::TextBox());
			this->comboBoxReadMethod = (gcnew System::Windows::Forms::ComboBox());
			this->buttonReadSCSI = (gcnew System::Windows::Forms::Button());
			this->buttonWrt1GBSCSI = (gcnew System::Windows::Forms::Button());
			this->buttonWrtVar = (gcnew System::Windows::Forms::Button());
			this->buttonSNSDcdr = (gcnew System::Windows::Forms::Button());
			this->buttonWrtTst = (gcnew System::Windows::Forms::Button());
			this->buttonReadPt1 = (gcnew System::Windows::Forms::Button());
			this->buttonXmlTst = (gcnew System::Windows::Forms::Button());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->btnChkDmps = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// button_Load
			// 
			this->button_Load->Location = System::Drawing::Point(22, 49);
			this->button_Load->Name = L"button_Load";
			this->button_Load->Size = System::Drawing::Size(75, 23);
			this->button_Load->TabIndex = 0;
			this->button_Load->Text = L"Load";
			this->button_Load->UseVisualStyleBackColor = true;
			this->button_Load->Click += gcnew System::EventHandler(this, &Form1::button1_Click);
			// 
			// button_Unload
			// 
			this->button_Unload->Location = System::Drawing::Point(141, 49);
			this->button_Unload->Name = L"button_Unload";
			this->button_Unload->Size = System::Drawing::Size(75, 23);
			this->button_Unload->TabIndex = 1;
			this->button_Unload->Text = L"Unload";
			this->button_Unload->UseVisualStyleBackColor = true;
			this->button_Unload->Click += gcnew System::EventHandler(this, &Form1::button_Unload_Click);
			// 
			// button_Lock
			// 
			this->button_Lock->Location = System::Drawing::Point(22, 89);
			this->button_Lock->Name = L"button_Lock";
			this->button_Lock->Size = System::Drawing::Size(75, 23);
			this->button_Lock->TabIndex = 2;
			this->button_Lock->Text = L"Lock";
			this->button_Lock->UseVisualStyleBackColor = true;
			this->button_Lock->Click += gcnew System::EventHandler(this, &Form1::button_Lock_Click);
			// 
			// button_Unlock
			// 
			this->button_Unlock->Location = System::Drawing::Point(141, 89);
			this->button_Unlock->Name = L"button_Unlock";
			this->button_Unlock->Size = System::Drawing::Size(75, 23);
			this->button_Unlock->TabIndex = 3;
			this->button_Unlock->Text = L"Unlock";
			this->button_Unlock->UseVisualStyleBackColor = true;
			this->button_Unlock->Click += gcnew System::EventHandler(this, &Form1::button_Unlock_Click);
			// 
			// button_AdjustTention
			// 
			this->button_AdjustTention->Location = System::Drawing::Point(22, 145);
			this->button_AdjustTention->Name = L"button_AdjustTention";
			this->button_AdjustTention->Size = System::Drawing::Size(75, 23);
			this->button_AdjustTention->TabIndex = 4;
			this->button_AdjustTention->Text = L"AdjustTention";
			this->button_AdjustTention->UseVisualStyleBackColor = true;
			this->button_AdjustTention->Click += gcnew System::EventHandler(this, &Form1::button_AdjustTention_Click);
			// 
			// button_EOD
			// 
			this->button_EOD->Location = System::Drawing::Point(22, 191);
			this->button_EOD->Name = L"button_EOD";
			this->button_EOD->Size = System::Drawing::Size(75, 23);
			this->button_EOD->TabIndex = 5;
			this->button_EOD->Text = L"EOD";
			this->button_EOD->UseVisualStyleBackColor = true;
			this->button_EOD->Click += gcnew System::EventHandler(this, &Form1::button_EOD_Click);
			// 
			// button_Rewind
			// 
			this->button_Rewind->Location = System::Drawing::Point(141, 191);
			this->button_Rewind->Name = L"button_Rewind";
			this->button_Rewind->Size = System::Drawing::Size(75, 23);
			this->button_Rewind->TabIndex = 6;
			this->button_Rewind->Text = L"Rewind";
			this->button_Rewind->UseVisualStyleBackColor = true;
			this->button_Rewind->Click += gcnew System::EventHandler(this, &Form1::button_Rewind_Click);
			// 
			// button_AbsBlk
			// 
			this->button_AbsBlk->Location = System::Drawing::Point(22, 227);
			this->button_AbsBlk->Name = L"button_AbsBlk";
			this->button_AbsBlk->Size = System::Drawing::Size(75, 23);
			this->button_AbsBlk->TabIndex = 7;
			this->button_AbsBlk->Text = L"AbsBlk";
			this->button_AbsBlk->UseVisualStyleBackColor = true;
			this->button_AbsBlk->Click += gcnew System::EventHandler(this, &Form1::button_AbsBlk_Click);
			// 
			// button_Format
			// 
			this->button_Format->Location = System::Drawing::Point(141, 144);
			this->button_Format->Name = L"button_Format";
			this->button_Format->Size = System::Drawing::Size(75, 23);
			this->button_Format->TabIndex = 8;
			this->button_Format->Text = L"Format";
			this->button_Format->UseVisualStyleBackColor = true;
			this->button_Format->Click += gcnew System::EventHandler(this, &Form1::button_Format_Click);
			// 
			// button_LogBlk
			// 
			this->button_LogBlk->Location = System::Drawing::Point(141, 227);
			this->button_LogBlk->Name = L"button_LogBlk";
			this->button_LogBlk->Size = System::Drawing::Size(75, 23);
			this->button_LogBlk->TabIndex = 9;
			this->button_LogBlk->Text = L"LogBlk";
			this->button_LogBlk->UseVisualStyleBackColor = true;
			this->button_LogBlk->Click += gcnew System::EventHandler(this, &Form1::button_LogBlk_Click);
			// 
			// button_SpaceFM
			// 
			this->button_SpaceFM->Location = System::Drawing::Point(22, 272);
			this->button_SpaceFM->Name = L"button_SpaceFM";
			this->button_SpaceFM->Size = System::Drawing::Size(75, 23);
			this->button_SpaceFM->TabIndex = 10;
			this->button_SpaceFM->Text = L"SpaceFM";
			this->button_SpaceFM->UseVisualStyleBackColor = true;
			this->button_SpaceFM->Click += gcnew System::EventHandler(this, &Form1::button_SpaceFM_Click);
			// 
			// button_SpaceBlks
			// 
			this->button_SpaceBlks->Location = System::Drawing::Point(141, 272);
			this->button_SpaceBlks->Name = L"button_SpaceBlks";
			this->button_SpaceBlks->Size = System::Drawing::Size(75, 23);
			this->button_SpaceBlks->TabIndex = 11;
			this->button_SpaceBlks->Text = L"SpaceBlks";
			this->button_SpaceBlks->UseVisualStyleBackColor = true;
			this->button_SpaceBlks->Click += gcnew System::EventHandler(this, &Form1::button_SpaceBlks_Click);
			// 
			// button_SpaceSFM
			// 
			this->button_SpaceSFM->Location = System::Drawing::Point(22, 314);
			this->button_SpaceSFM->Name = L"button_SpaceSFM";
			this->button_SpaceSFM->Size = System::Drawing::Size(75, 23);
			this->button_SpaceSFM->TabIndex = 12;
			this->button_SpaceSFM->Text = L"SpaceSFM";
			this->button_SpaceSFM->UseVisualStyleBackColor = true;
			this->button_SpaceSFM->Click += gcnew System::EventHandler(this, &Form1::button_SpaceSFM_Click);
			// 
			// button_GetStatus
			// 
			this->button_GetStatus->Location = System::Drawing::Point(141, 313);
			this->button_GetStatus->Name = L"button_GetStatus";
			this->button_GetStatus->Size = System::Drawing::Size(75, 23);
			this->button_GetStatus->TabIndex = 13;
			this->button_GetStatus->Text = L"GetTapeStatus";
			this->button_GetStatus->UseVisualStyleBackColor = true;
			this->button_GetStatus->Click += gcnew System::EventHandler(this, &Form1::button_GetStatus_Click);
			// 
			// button_logicalPos
			// 
			this->button_logicalPos->Location = System::Drawing::Point(268, 49);
			this->button_logicalPos->Name = L"button_logicalPos";
			this->button_logicalPos->Size = System::Drawing::Size(75, 23);
			this->button_logicalPos->TabIndex = 14;
			this->button_logicalPos->Text = L"LogicalPos";
			this->button_logicalPos->UseVisualStyleBackColor = true;
			this->button_logicalPos->Click += gcnew System::EventHandler(this, &Form1::button_logicalPos_Click);
			// 
			// buttonAbsPos
			// 
			this->buttonAbsPos->Location = System::Drawing::Point(268, 88);
			this->buttonAbsPos->Name = L"buttonAbsPos";
			this->buttonAbsPos->Size = System::Drawing::Size(75, 23);
			this->buttonAbsPos->TabIndex = 15;
			this->buttonAbsPos->Text = L"AbsPos";
			this->buttonAbsPos->UseVisualStyleBackColor = true;
			this->buttonAbsPos->Click += gcnew System::EventHandler(this, &Form1::buttonAbsPos_Click);
			// 
			// button_MediaParams
			// 
			this->button_MediaParams->Location = System::Drawing::Point(268, 144);
			this->button_MediaParams->Name = L"button_MediaParams";
			this->button_MediaParams->Size = System::Drawing::Size(75, 23);
			this->button_MediaParams->TabIndex = 16;
			this->button_MediaParams->Text = L"MediaParams";
			this->button_MediaParams->UseVisualStyleBackColor = true;
			this->button_MediaParams->Click += gcnew System::EventHandler(this, &Form1::button_MediaParams_Click);
			// 
			// button_SetBlkSize
			// 
			this->button_SetBlkSize->Location = System::Drawing::Point(268, 190);
			this->button_SetBlkSize->Name = L"button_SetBlkSize";
			this->button_SetBlkSize->Size = System::Drawing::Size(75, 23);
			this->button_SetBlkSize->TabIndex = 17;
			this->button_SetBlkSize->Text = L"SetBlkSize";
			this->button_SetBlkSize->UseVisualStyleBackColor = true;
			this->button_SetBlkSize->Click += gcnew System::EventHandler(this, &Form1::button_SetBlkSize_Click);
			// 
			// button_SetDriveParams
			// 
			this->button_SetDriveParams->Location = System::Drawing::Point(268, 226);
			this->button_SetDriveParams->Name = L"button_SetDriveParams";
			this->button_SetDriveParams->Size = System::Drawing::Size(75, 23);
			this->button_SetDriveParams->TabIndex = 18;
			this->button_SetDriveParams->Text = L"SetDriveParams";
			this->button_SetDriveParams->UseVisualStyleBackColor = true;
			this->button_SetDriveParams->Click += gcnew System::EventHandler(this, &Form1::button_SetDriveParams_Click);
			// 
			// button_CreatePart
			// 
			this->button_CreatePart->Location = System::Drawing::Point(268, 271);
			this->button_CreatePart->Name = L"button_CreatePart";
			this->button_CreatePart->Size = System::Drawing::Size(75, 23);
			this->button_CreatePart->TabIndex = 19;
			this->button_CreatePart->Text = L"CreatePart";
			this->button_CreatePart->UseVisualStyleBackColor = true;
			this->button_CreatePart->Click += gcnew System::EventHandler(this, &Form1::button_CreatePart_Click);
			// 
			// button_Erase
			// 
			this->button_Erase->Location = System::Drawing::Point(268, 313);
			this->button_Erase->Name = L"button_Erase";
			this->button_Erase->Size = System::Drawing::Size(75, 23);
			this->button_Erase->TabIndex = 20;
			this->button_Erase->Text = L"Erase";
			this->button_Erase->UseVisualStyleBackColor = true;
			this->button_Erase->Click += gcnew System::EventHandler(this, &Form1::button_Erase_Click);
			// 
			// button_WriteTpM3
			// 
			this->button_WriteTpM3->Location = System::Drawing::Point(431, 49);
			this->button_WriteTpM3->Name = L"button_WriteTpM3";
			this->button_WriteTpM3->Size = System::Drawing::Size(75, 23);
			this->button_WriteTpM3->TabIndex = 21;
			this->button_WriteTpM3->Text = L"WriteTpM3";
			this->button_WriteTpM3->UseVisualStyleBackColor = true;
			this->button_WriteTpM3->Click += gcnew System::EventHandler(this, &Form1::button_WriteTpM3_Click);
			// 
			// button_Write1GB
			// 
			this->button_Write1GB->Location = System::Drawing::Point(431, 87);
			this->button_Write1GB->Name = L"button_Write1GB";
			this->button_Write1GB->Size = System::Drawing::Size(75, 23);
			this->button_Write1GB->TabIndex = 22;
			this->button_Write1GB->Text = L"Write1GB";
			this->button_Write1GB->UseVisualStyleBackColor = true;
			this->button_Write1GB->Click += gcnew System::EventHandler(this, &Form1::button1_Click_1);
			// 
			// button_Read
			// 
			this->button_Read->Location = System::Drawing::Point(431, 144);
			this->button_Read->Name = L"button_Read";
			this->button_Read->Size = System::Drawing::Size(75, 23);
			this->button_Read->TabIndex = 23;
			this->button_Read->Text = L"Read";
			this->button_Read->UseVisualStyleBackColor = true;
			this->button_Read->Click += gcnew System::EventHandler(this, &Form1::button_Read_Click);
			// 
			// button_SizeOf
			// 
			this->button_SizeOf->Location = System::Drawing::Point(431, 190);
			this->button_SizeOf->Name = L"button_SizeOf";
			this->button_SizeOf->Size = System::Drawing::Size(75, 23);
			this->button_SizeOf->TabIndex = 24;
			this->button_SizeOf->Text = L"SizeOff";
			this->button_SizeOf->UseVisualStyleBackColor = true;
			this->button_SizeOf->Click += gcnew System::EventHandler(this, &Form1::button_SizeOf_Click);
			// 
			// button_LoadSCSI
			// 
			this->button_LoadSCSI->Location = System::Drawing::Point(431, 226);
			this->button_LoadSCSI->Name = L"button_LoadSCSI";
			this->button_LoadSCSI->Size = System::Drawing::Size(75, 23);
			this->button_LoadSCSI->TabIndex = 25;
			this->button_LoadSCSI->Text = L"LoadSCSI";
			this->button_LoadSCSI->UseVisualStyleBackColor = true;
			this->button_LoadSCSI->Click += gcnew System::EventHandler(this, &Form1::button_LoadSCSI_Click);
			// 
			// btnUnloadSCSI
			// 
			this->btnUnloadSCSI->Location = System::Drawing::Point(431, 271);
			this->btnUnloadSCSI->Name = L"btnUnloadSCSI";
			this->btnUnloadSCSI->Size = System::Drawing::Size(75, 23);
			this->btnUnloadSCSI->TabIndex = 26;
			this->btnUnloadSCSI->Text = L"UnloadSCSI";
			this->btnUnloadSCSI->UseVisualStyleBackColor = true;
			this->btnUnloadSCSI->Click += gcnew System::EventHandler(this, &Form1::btnUnloadSCSI_Click);
			// 
			// buttonFormat
			// 
			this->buttonFormat->Location = System::Drawing::Point(605, 23);
			this->buttonFormat->Name = L"buttonFormat";
			this->buttonFormat->Size = System::Drawing::Size(75, 23);
			this->buttonFormat->TabIndex = 27;
			this->buttonFormat->Text = L"Format";
			this->buttonFormat->UseVisualStyleBackColor = true;
			this->buttonFormat->Click += gcnew System::EventHandler(this, &Form1::buttonFormat_Click);
			// 
			// textBoxFormatType
			// 
			this->textBoxFormatType->Location = System::Drawing::Point(595, 87);
			this->textBoxFormatType->Name = L"textBoxFormatType";
			this->textBoxFormatType->Size = System::Drawing::Size(100, 20);
			this->textBoxFormatType->TabIndex = 28;
			this->textBoxFormatType->Text = L"0";
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(595, 68);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(69, 13);
			this->label1->TabIndex = 29;
			this->label1->Text = L"Format Type:";
			// 
			// buttonEraseSCSI
			// 
			this->buttonEraseSCSI->Location = System::Drawing::Point(598, 144);
			this->buttonEraseSCSI->Name = L"buttonEraseSCSI";
			this->buttonEraseSCSI->Size = System::Drawing::Size(75, 23);
			this->buttonEraseSCSI->TabIndex = 30;
			this->buttonEraseSCSI->Text = L"Erase SCSI";
			this->buttonEraseSCSI->UseVisualStyleBackColor = true;
			this->buttonEraseSCSI->Click += gcnew System::EventHandler(this, &Form1::buttonEraseSCSI_Click);
			// 
			// checkBoxLongErase
			// 
			this->checkBoxLongErase->AutoSize = true;
			this->checkBoxLongErase->Location = System::Drawing::Point(598, 190);
			this->checkBoxLongErase->Name = L"checkBoxLongErase";
			this->checkBoxLongErase->Size = System::Drawing::Size(80, 17);
			this->checkBoxLongErase->TabIndex = 31;
			this->checkBoxLongErase->Text = L"Long Erase";
			this->checkBoxLongErase->UseVisualStyleBackColor = true;
			// 
			// buttonRewindSCSI
			// 
			this->buttonRewindSCSI->Location = System::Drawing::Point(598, 214);
			this->buttonRewindSCSI->Name = L"buttonRewindSCSI";
			this->buttonRewindSCSI->Size = System::Drawing::Size(75, 23);
			this->buttonRewindSCSI->TabIndex = 32;
			this->buttonRewindSCSI->Text = L"RewindSCSI";
			this->buttonRewindSCSI->UseVisualStyleBackColor = true;
			this->buttonRewindSCSI->Click += gcnew System::EventHandler(this, &Form1::buttonRewindSCSI_Click);
			// 
			// buttonPositionShort
			// 
			this->buttonPositionShort->Location = System::Drawing::Point(598, 271);
			this->buttonPositionShort->Name = L"buttonPositionShort";
			this->buttonPositionShort->Size = System::Drawing::Size(75, 23);
			this->buttonPositionShort->TabIndex = 33;
			this->buttonPositionShort->Text = L"PositionShort";
			this->buttonPositionShort->UseVisualStyleBackColor = true;
			this->buttonPositionShort->Click += gcnew System::EventHandler(this, &Form1::buttonPositionShort_Click);
			// 
			// buttonPositionLong
			// 
			this->buttonPositionLong->Location = System::Drawing::Point(598, 313);
			this->buttonPositionLong->Name = L"buttonPositionLong";
			this->buttonPositionLong->Size = System::Drawing::Size(75, 23);
			this->buttonPositionLong->TabIndex = 34;
			this->buttonPositionLong->Text = L"PositionLong";
			this->buttonPositionLong->UseVisualStyleBackColor = true;
			this->buttonPositionLong->Click += gcnew System::EventHandler(this, &Form1::buttonPositionLong_Click);
			// 
			// buttonPositionExtnd
			// 
			this->buttonPositionExtnd->Location = System::Drawing::Point(598, 358);
			this->buttonPositionExtnd->Name = L"buttonPositionExtnd";
			this->buttonPositionExtnd->Size = System::Drawing::Size(75, 23);
			this->buttonPositionExtnd->TabIndex = 35;
			this->buttonPositionExtnd->Text = L"PositionExtnd";
			this->buttonPositionExtnd->UseVisualStyleBackColor = true;
			this->buttonPositionExtnd->Click += gcnew System::EventHandler(this, &Form1::buttonPositionExtnd_Click);
			// 
			// buttonLocateEOD
			// 
			this->buttonLocateEOD->Location = System::Drawing::Point(878, 23);
			this->buttonLocateEOD->Name = L"buttonLocateEOD";
			this->buttonLocateEOD->Size = System::Drawing::Size(75, 23);
			this->buttonLocateEOD->TabIndex = 36;
			this->buttonLocateEOD->Text = L"EOD";
			this->buttonLocateEOD->UseVisualStyleBackColor = true;
			this->buttonLocateEOD->Click += gcnew System::EventHandler(this, &Form1::buttonLocateEOD_Click);
			// 
			// textBoxPartition
			// 
			this->textBoxPartition->Location = System::Drawing::Point(772, 23);
			this->textBoxPartition->Name = L"textBoxPartition";
			this->textBoxPartition->Size = System::Drawing::Size(100, 20);
			this->textBoxPartition->TabIndex = 37;
			this->textBoxPartition->Text = L"0";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(732, 23);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(31, 13);
			this->label2->TabIndex = 38;
			this->label2->Text = L"PT#:";
			// 
			// buttonLocateBOP
			// 
			this->buttonLocateBOP->Location = System::Drawing::Point(959, 23);
			this->buttonLocateBOP->Name = L"buttonLocateBOP";
			this->buttonLocateBOP->Size = System::Drawing::Size(75, 23);
			this->buttonLocateBOP->TabIndex = 39;
			this->buttonLocateBOP->Text = L"BOP";
			this->buttonLocateBOP->UseVisualStyleBackColor = true;
			this->buttonLocateBOP->Click += gcnew System::EventHandler(this, &Form1::buttonLocateBOP_Click);
			// 
			// buttonLocate
			// 
			this->buttonLocate->Location = System::Drawing::Point(878, 68);
			this->buttonLocate->Name = L"buttonLocate";
			this->buttonLocate->Size = System::Drawing::Size(75, 23);
			this->buttonLocate->TabIndex = 40;
			this->buttonLocate->Text = L"Locate";
			this->buttonLocate->UseVisualStyleBackColor = true;
			this->buttonLocate->Click += gcnew System::EventHandler(this, &Form1::buttonLocate_Click);
			// 
			// textBoxBlockNumber
			// 
			this->textBoxBlockNumber->Location = System::Drawing::Point(772, 68);
			this->textBoxBlockNumber->Name = L"textBoxBlockNumber";
			this->textBoxBlockNumber->Size = System::Drawing::Size(100, 20);
			this->textBoxBlockNumber->TabIndex = 41;
			this->textBoxBlockNumber->Text = L"100";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(735, 77);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(26, 13);
			this->label3->TabIndex = 42;
			this->label3->Text = L"Bl#:";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(738, 129);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(38, 13);
			this->label4->TabIndex = 43;
			this->label4->Text = L"Space";
			// 
			// textBoxSpace
			// 
			this->textBoxSpace->Location = System::Drawing::Point(783, 129);
			this->textBoxSpace->Name = L"textBoxSpace";
			this->textBoxSpace->Size = System::Drawing::Size(100, 20);
			this->textBoxSpace->TabIndex = 44;
			this->textBoxSpace->Text = L"10";
			// 
			// comboBoxObjectType
			// 
			this->comboBoxObjectType->FormattingEnabled = true;
			this->comboBoxObjectType->Items->AddRange(gcnew cli::array< System::Object^  >(2) {L"Blocks", L"FileMarks"});
			this->comboBoxObjectType->Location = System::Drawing::Point(911, 127);
			this->comboBoxObjectType->Name = L"comboBoxObjectType";
			this->comboBoxObjectType->Size = System::Drawing::Size(121, 21);
			this->comboBoxObjectType->TabIndex = 45;
			// 
			// buttonSpace
			// 
			this->buttonSpace->Location = System::Drawing::Point(1072, 125);
			this->buttonSpace->Name = L"buttonSpace";
			this->buttonSpace->Size = System::Drawing::Size(75, 23);
			this->buttonSpace->TabIndex = 46;
			this->buttonSpace->Text = L"Run";
			this->buttonSpace->UseVisualStyleBackColor = true;
			this->buttonSpace->Click += gcnew System::EventHandler(this, &Form1::buttonSpace_Click);
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(738, 190);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(74, 13);
			this->label5->TabIndex = 47;
			this->label5->Text = L"FileMarks Cnt:";
			// 
			// textBoxFileMarks
			// 
			this->textBoxFileMarks->Location = System::Drawing::Point(837, 192);
			this->textBoxFileMarks->Name = L"textBoxFileMarks";
			this->textBoxFileMarks->Size = System::Drawing::Size(100, 20);
			this->textBoxFileMarks->TabIndex = 48;
			this->textBoxFileMarks->Text = L"1";
			// 
			// buttonWriteFMSCSI
			// 
			this->buttonWriteFMSCSI->Location = System::Drawing::Point(987, 189);
			this->buttonWriteFMSCSI->Name = L"buttonWriteFMSCSI";
			this->buttonWriteFMSCSI->Size = System::Drawing::Size(75, 23);
			this->buttonWriteFMSCSI->TabIndex = 49;
			this->buttonWriteFMSCSI->Text = L"WriteFMSCSI";
			this->buttonWriteFMSCSI->UseVisualStyleBackColor = true;
			this->buttonWriteFMSCSI->Click += gcnew System::EventHandler(this, &Form1::buttonWriteFMSCSI_Click);
			// 
			// textBoxBlkSize
			// 
			this->textBoxBlkSize->Location = System::Drawing::Point(804, 245);
			this->textBoxBlkSize->Name = L"textBoxBlkSize";
			this->textBoxBlkSize->Size = System::Drawing::Size(100, 20);
			this->textBoxBlkSize->TabIndex = 50;
			this->textBoxBlkSize->Text = L"65536";
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Location = System::Drawing::Point(738, 248);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(60, 13);
			this->label6->TabIndex = 51;
			this->label6->Text = L"Block Size:";
			// 
			// buttonSetBlkSize
			// 
			this->buttonSetBlkSize->Location = System::Drawing::Point(925, 243);
			this->buttonSetBlkSize->Name = L"buttonSetBlkSize";
			this->buttonSetBlkSize->Size = System::Drawing::Size(75, 23);
			this->buttonSetBlkSize->TabIndex = 52;
			this->buttonSetBlkSize->Text = L"Set";
			this->buttonSetBlkSize->UseVisualStyleBackColor = true;
			this->buttonSetBlkSize->Click += gcnew System::EventHandler(this, &Form1::buttonSetBlkSize_Click);
			// 
			// buttonRequestSNS
			// 
			this->buttonRequestSNS->Location = System::Drawing::Point(738, 292);
			this->buttonRequestSNS->Name = L"buttonRequestSNS";
			this->buttonRequestSNS->Size = System::Drawing::Size(75, 23);
			this->buttonRequestSNS->TabIndex = 53;
			this->buttonRequestSNS->Text = L"RequestSNS";
			this->buttonRequestSNS->UseVisualStyleBackColor = true;
			this->buttonRequestSNS->Click += gcnew System::EventHandler(this, &Form1::buttonRequestSNS_Click);
			// 
			// buttonGetBlkSize
			// 
			this->buttonGetBlkSize->Location = System::Drawing::Point(862, 292);
			this->buttonGetBlkSize->Name = L"buttonGetBlkSize";
			this->buttonGetBlkSize->Size = System::Drawing::Size(75, 23);
			this->buttonGetBlkSize->TabIndex = 54;
			this->buttonGetBlkSize->Text = L"GetBlkSize";
			this->buttonGetBlkSize->UseVisualStyleBackColor = true;
			this->buttonGetBlkSize->Click += gcnew System::EventHandler(this, &Form1::buttonGetBlkSize_Click);
			// 
			// comboBoxTape
			// 
			this->comboBoxTape->AutoCompleteMode = System::Windows::Forms::AutoCompleteMode::Suggest;
			this->comboBoxTape->AutoCompleteSource = System::Windows::Forms::AutoCompleteSource::ListItems;
			this->comboBoxTape->FormattingEnabled = true;
			this->comboBoxTape->Items->AddRange(gcnew cli::array< System::Object^  >(5) {L"\\\\.\\TAPE0", L"\\\\.\\TAPE1", L"\\\\.\\TAPE2", 
				L"\\\\.\\TAPE3", L"\\\\.\\TAPE4"});
			this->comboBoxTape->Location = System::Drawing::Point(22, 12);
			this->comboBoxTape->Name = L"comboBoxTape";
			this->comboBoxTape->Size = System::Drawing::Size(121, 21);
			this->comboBoxTape->TabIndex = 55;
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Location = System::Drawing::Point(738, 345);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(36, 13);
			this->label7->TabIndex = 56;
			this->label7->Text = L"Read:";
			// 
			// textBoxReadSize
			// 
			this->textBoxReadSize->Location = System::Drawing::Point(783, 338);
			this->textBoxReadSize->Name = L"textBoxReadSize";
			this->textBoxReadSize->Size = System::Drawing::Size(100, 20);
			this->textBoxReadSize->TabIndex = 57;
			this->textBoxReadSize->Text = L"0";
			// 
			// comboBoxReadMethod
			// 
			this->comboBoxReadMethod->FormattingEnabled = true;
			this->comboBoxReadMethod->Items->AddRange(gcnew cli::array< System::Object^  >(2) {L"Bytes", L"Blocks"});
			this->comboBoxReadMethod->Location = System::Drawing::Point(889, 337);
			this->comboBoxReadMethod->Name = L"comboBoxReadMethod";
			this->comboBoxReadMethod->Size = System::Drawing::Size(74, 21);
			this->comboBoxReadMethod->TabIndex = 58;
			// 
			// buttonReadSCSI
			// 
			this->buttonReadSCSI->Location = System::Drawing::Point(970, 337);
			this->buttonReadSCSI->Name = L"buttonReadSCSI";
			this->buttonReadSCSI->Size = System::Drawing::Size(75, 23);
			this->buttonReadSCSI->TabIndex = 59;
			this->buttonReadSCSI->Text = L"Read";
			this->buttonReadSCSI->UseVisualStyleBackColor = true;
			this->buttonReadSCSI->Click += gcnew System::EventHandler(this, &Form1::buttonReadSCSI_Click);
			// 
			// buttonWrt1GBSCSI
			// 
			this->buttonWrt1GBSCSI->Location = System::Drawing::Point(741, 379);
			this->buttonWrt1GBSCSI->Name = L"buttonWrt1GBSCSI";
			this->buttonWrt1GBSCSI->Size = System::Drawing::Size(75, 23);
			this->buttonWrt1GBSCSI->TabIndex = 60;
			this->buttonWrt1GBSCSI->Text = L"Write1GBSCSI";
			this->buttonWrt1GBSCSI->UseVisualStyleBackColor = true;
			this->buttonWrt1GBSCSI->Click += gcnew System::EventHandler(this, &Form1::buttonWrt1GBSCSI_Click);
			// 
			// buttonWrtVar
			// 
			this->buttonWrtVar->Location = System::Drawing::Point(862, 379);
			this->buttonWrtVar->Name = L"buttonWrtVar";
			this->buttonWrtVar->Size = System::Drawing::Size(101, 23);
			this->buttonWrtVar->TabIndex = 61;
			this->buttonWrtVar->Text = L"WriteVar16KBlk";
			this->buttonWrtVar->UseVisualStyleBackColor = true;
			this->buttonWrtVar->Click += gcnew System::EventHandler(this, &Form1::buttonWrtVar_Click);
			// 
			// buttonSNSDcdr
			// 
			this->buttonSNSDcdr->Location = System::Drawing::Point(161, 13);
			this->buttonSNSDcdr->Name = L"buttonSNSDcdr";
			this->buttonSNSDcdr->Size = System::Drawing::Size(84, 23);
			this->buttonSNSDcdr->TabIndex = 62;
			this->buttonSNSDcdr->Text = L"SNS Decoder";
			this->buttonSNSDcdr->UseVisualStyleBackColor = true;
			this->buttonSNSDcdr->Click += gcnew System::EventHandler(this, &Form1::buttonSNSDcdr_Click);
			// 
			// buttonWrtTst
			// 
			this->buttonWrtTst->Location = System::Drawing::Point(251, 13);
			this->buttonWrtTst->Name = L"buttonWrtTst";
			this->buttonWrtTst->Size = System::Drawing::Size(75, 23);
			this->buttonWrtTst->TabIndex = 63;
			this->buttonWrtTst->Text = L"WriteTest";
			this->buttonWrtTst->UseVisualStyleBackColor = true;
			this->buttonWrtTst->Click += gcnew System::EventHandler(this, &Form1::buttonWrtTst_Click);
			// 
			// buttonReadPt1
			// 
			this->buttonReadPt1->Location = System::Drawing::Point(1034, 245);
			this->buttonReadPt1->Name = L"buttonReadPt1";
			this->buttonReadPt1->Size = System::Drawing::Size(144, 23);
			this->buttonReadPt1->TabIndex = 64;
			this->buttonReadPt1->Text = L"Read PT 1";
			this->buttonReadPt1->UseVisualStyleBackColor = true;
			this->buttonReadPt1->Click += gcnew System::EventHandler(this, &Form1::buttonReadPt1_Click);
			// 
			// buttonXmlTst
			// 
			this->buttonXmlTst->Location = System::Drawing::Point(22, 358);
			this->buttonXmlTst->Name = L"buttonXmlTst";
			this->buttonXmlTst->Size = System::Drawing::Size(75, 23);
			this->buttonXmlTst->TabIndex = 65;
			this->buttonXmlTst->Text = L"XmlTest";
			this->buttonXmlTst->UseVisualStyleBackColor = true;
			this->buttonXmlTst->Click += gcnew System::EventHandler(this, &Form1::buttonXmlTst_Click);
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(333, 12);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(92, 23);
			this->button1->TabIndex = 66;
			this->button1->Text = L"XOR";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &Form1::button1_Click_2);
			// 
			// btnChkDmps
			// 
			this->btnChkDmps->Location = System::Drawing::Point(440, 13);
			this->btnChkDmps->Name = L"btnChkDmps";
			this->btnChkDmps->Size = System::Drawing::Size(145, 23);
			this->btnChkDmps->TabIndex = 67;
			this->btnChkDmps->Text = L"Check Dumps CDS-71582";
			this->btnChkDmps->UseVisualStyleBackColor = true;
			this->btnChkDmps->Click += gcnew System::EventHandler(this, &Form1::btnChkDmps_Click);
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1190, 419);
			this->Controls->Add(this->btnChkDmps);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->buttonXmlTst);
			this->Controls->Add(this->buttonReadPt1);
			this->Controls->Add(this->buttonWrtTst);
			this->Controls->Add(this->buttonSNSDcdr);
			this->Controls->Add(this->buttonWrtVar);
			this->Controls->Add(this->buttonWrt1GBSCSI);
			this->Controls->Add(this->buttonReadSCSI);
			this->Controls->Add(this->comboBoxReadMethod);
			this->Controls->Add(this->textBoxReadSize);
			this->Controls->Add(this->label7);
			this->Controls->Add(this->comboBoxTape);
			this->Controls->Add(this->buttonGetBlkSize);
			this->Controls->Add(this->buttonRequestSNS);
			this->Controls->Add(this->buttonSetBlkSize);
			this->Controls->Add(this->label6);
			this->Controls->Add(this->textBoxBlkSize);
			this->Controls->Add(this->buttonWriteFMSCSI);
			this->Controls->Add(this->textBoxFileMarks);
			this->Controls->Add(this->label5);
			this->Controls->Add(this->buttonSpace);
			this->Controls->Add(this->comboBoxObjectType);
			this->Controls->Add(this->textBoxSpace);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->textBoxBlockNumber);
			this->Controls->Add(this->buttonLocate);
			this->Controls->Add(this->buttonLocateBOP);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->textBoxPartition);
			this->Controls->Add(this->buttonLocateEOD);
			this->Controls->Add(this->buttonPositionExtnd);
			this->Controls->Add(this->buttonPositionLong);
			this->Controls->Add(this->buttonPositionShort);
			this->Controls->Add(this->buttonRewindSCSI);
			this->Controls->Add(this->checkBoxLongErase);
			this->Controls->Add(this->buttonEraseSCSI);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->textBoxFormatType);
			this->Controls->Add(this->buttonFormat);
			this->Controls->Add(this->btnUnloadSCSI);
			this->Controls->Add(this->button_LoadSCSI);
			this->Controls->Add(this->button_SizeOf);
			this->Controls->Add(this->button_Read);
			this->Controls->Add(this->button_Write1GB);
			this->Controls->Add(this->button_WriteTpM3);
			this->Controls->Add(this->button_Erase);
			this->Controls->Add(this->button_CreatePart);
			this->Controls->Add(this->button_SetDriveParams);
			this->Controls->Add(this->button_SetBlkSize);
			this->Controls->Add(this->button_MediaParams);
			this->Controls->Add(this->buttonAbsPos);
			this->Controls->Add(this->button_logicalPos);
			this->Controls->Add(this->button_GetStatus);
			this->Controls->Add(this->button_SpaceSFM);
			this->Controls->Add(this->button_SpaceBlks);
			this->Controls->Add(this->button_SpaceFM);
			this->Controls->Add(this->button_LogBlk);
			this->Controls->Add(this->button_Format);
			this->Controls->Add(this->button_AbsBlk);
			this->Controls->Add(this->button_Rewind);
			this->Controls->Add(this->button_EOD);
			this->Controls->Add(this->button_AdjustTention);
			this->Controls->Add(this->button_Unlock);
			this->Controls->Add(this->button_Lock);
			this->Controls->Add(this->button_Unload);
			this->Controls->Add(this->button_Load);
			this->Name = L"Form1";
			this->Text = L"Form1";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {

				 this->button_Load->Enabled = false;
				 ITapeDrive^ tapeDrive = gcnew TapeDriveWinAPI();
				 //String^ tapeName = "\\\\.\\TAPE0";
				String^ tapeName = this->comboBoxTape->SelectedItem->ToString();
				 UInt32 returnCode = -1;
				 bool res1 = tapeDrive->Open(tapeName, returnCode);
				 if (!res1)
				 {
					 String^ msg = returnCode.ToString() + ": " +(gcnew Win32Exception(returnCode))->Message;
					 MessageBox::Show(msg);
				 }

				 res1 = tapeDrive->Load(false, returnCode);
				 if (!res1)
				 {
					 String^ msg = returnCode.ToString() + ": " +(gcnew Win32Exception(returnCode))->Message;
					 MessageBox::Show(msg);
				 }

				 bool res2 = tapeDrive->Close(returnCode);
				 if (!res2)
				 {
					 String^ msg = returnCode.ToString() + ": " +(gcnew Win32Exception(returnCode))->Message;
					 MessageBox::Show(msg);
				 }

				 this->button_Load->Enabled = true;
			 }
	private: System::Void button_Unload_Click(System::Object^  sender, System::EventArgs^  e) {

				 this->button_Unload->Enabled = false;

				 ITapeDrive^ tapeDrive = gcnew TapeDriveWinAPI();
				 //String^ tapeName = "\\\\.\\TAPE0";
				 String^ tapeName = this->comboBoxTape->SelectedItem->ToString();
				 UInt32 returnCode = -1;
				 bool res1 = tapeDrive->Open(tapeName, returnCode);
				 if (!res1)
				 {
					 String^ msg = returnCode.ToString() + ": " +(gcnew Win32Exception(returnCode))->Message;
					 MessageBox::Show(msg);
				 }

				 res1 = tapeDrive->Unload(false, returnCode);
				 if (!res1)
				 {
					 String^ msg = returnCode.ToString() + ": " +(gcnew Win32Exception(returnCode))->Message;
					 MessageBox::Show(msg);
				 }

				 bool res2 = tapeDrive->Close(returnCode);
				 if (!res2)
				 {
					 String^ msg = returnCode.ToString() + ": " +(gcnew Win32Exception(returnCode))->Message;
					 MessageBox::Show(msg);
				 }

				 this->button_Unload->Enabled = true;
			 }
private: System::Void button_Lock_Click(System::Object^  sender, System::EventArgs^  e) {

			 this->button_Lock->Enabled = false;
			 TapeDriveWinAPI^ tapeDrive = gcnew TapeDriveWinAPI();
			 //String^ tapeName = "\\\\.\\TAPE0";
			 String^ tapeName = this->comboBoxTape->SelectedItem->ToString();
			 UInt32 returnCode = -1;
			 bool res1 = tapeDrive->Open(tapeName, returnCode);
			 if (!res1)
			 {
				 String^ msg = returnCode.ToString() + ": " +(gcnew Win32Exception(returnCode))->Message;
				 MessageBox::Show(msg);
			 }

			 res1 = tapeDrive->Lock(false, returnCode);
			 if (!res1)
			 {
				 String^ msg = returnCode.ToString() + ": " +(gcnew Win32Exception(returnCode))->Message;
				 MessageBox::Show(msg);
			 }

			 bool res2 = tapeDrive->Close(returnCode);
			 if (!res2)
			 {
				 String^ msg = returnCode.ToString() + ": " +(gcnew Win32Exception(returnCode))->Message;
				 MessageBox::Show(msg);
			 }
			 this->button_Lock->Enabled = true;
		 }
private: System::Void button_Unlock_Click(System::Object^  sender, System::EventArgs^  e) {

			 this->button_Unlock->Enabled = false;
			 TapeDriveWinAPI^ tapeDrive = gcnew TapeDriveWinAPI();
			 //String^ tapeName = "\\\\.\\TAPE0";
			 String^ tapeName = this->comboBoxTape->SelectedItem->ToString();
			 UInt32 returnCode = -1;
			 bool res1 = tapeDrive->Open(tapeName, returnCode);
			 if (!res1)
			 {
				 String^ msg = returnCode.ToString() + ": " +(gcnew Win32Exception(returnCode))->Message;
				 MessageBox::Show(msg);
			 }

			 res1 = tapeDrive->Unlock(false, returnCode);
			 if (!res1)
			 {
				 String^ msg = returnCode.ToString() + ": " +(gcnew Win32Exception(returnCode))->Message;
				 MessageBox::Show(msg);
			 }

			 bool res2 = tapeDrive->Close(returnCode);
			 if (!res2)
			 {
				 String^ msg = returnCode.ToString() + ": " +(gcnew Win32Exception(returnCode))->Message;
				 MessageBox::Show(msg);
			 }
			 this->button_Unlock->Enabled = true;
		 }
private: System::Void button_AdjustTention_Click(System::Object^  sender, System::EventArgs^  e) {

			 this->button_AdjustTention->Enabled = false;
			 TapeDriveWinAPI^ tapeDrive = gcnew TapeDriveWinAPI();
			 //String^ tapeName = "\\\\.\\TAPE0";
			 String^ tapeName = this->comboBoxTape->SelectedItem->ToString();
			 UInt32 returnCode = -1;
			 bool res1 = tapeDrive->Open(tapeName, returnCode);
			 if (!res1)
			 {
				 String^ msg = returnCode.ToString() + ": " +(gcnew Win32Exception(returnCode))->Message;
				 MessageBox::Show(msg);
			 }

			 res1 = tapeDrive->AdjustTension(false, returnCode);
			 if (!res1)
			 {
				 String^ msg = returnCode.ToString() + ": " +(gcnew Win32Exception(returnCode))->Message;
				 MessageBox::Show(msg);
			 }

			 bool res2 = tapeDrive->Close(returnCode);
			 if (!res2)
			 {
				 String^ msg = returnCode.ToString() + ": " +(gcnew Win32Exception(returnCode))->Message;
				 MessageBox::Show(msg);
			 }
			 this->button_AdjustTention->Enabled = true;
		 }
private: System::Void button_EOD_Click(System::Object^  sender, System::EventArgs^  e) {

			 this->button_EOD->Enabled = false;
			 TapeDriveWinAPI^ tapeDrive = gcnew TapeDriveWinAPI();

			 this->comboBoxTape->AutoCompleteMode = System::Windows::Forms::AutoCompleteMode::Suggest;
			 

			 //String^ tapeName = "\\\\.\\TAPE0";
			String^ tapeName = this->comboBoxTape->SelectedItem->ToString();
			 UInt32 returnCode = -1;
			 bool res1 = tapeDrive->Open(tapeName, returnCode);
			 if (!res1)
			 {
				 String^ msg = returnCode.ToString() + ": " +(gcnew Win32Exception(returnCode))->Message;
				 MessageBox::Show(msg);
			 }

			 res1 = tapeDrive->SeekToEOD(1,false, returnCode);
			 if (!res1)
			 {
				 String^ msg = returnCode.ToString() + ": " +(gcnew Win32Exception(returnCode))->Message;
				 MessageBox::Show(msg);
			 }

			 bool res2 = tapeDrive->Close(returnCode);
			 if (!res2)
			 {
				 String^ msg = returnCode.ToString() + ": " +(gcnew Win32Exception(returnCode))->Message;
				 MessageBox::Show(msg);
			 }
			 this->button_EOD->Enabled = true;
		 }
private: System::Void button_Rewind_Click(System::Object^  sender, System::EventArgs^  e) {

			 this->button_Rewind->Enabled = false;
			 TapeDriveWinAPI^ tapeDrive = gcnew TapeDriveWinAPI();
			 //String^ tapeName = "\\\\.\\TAPE0";
			 String^ tapeName = this->comboBoxTape->SelectedItem->ToString();
			 UInt32 returnCode = -1;
			 bool res1 = tapeDrive->Open(tapeName, returnCode);
			 if (!res1)
			 {
				 String^ msg = returnCode.ToString() + ": " +(gcnew Win32Exception(returnCode))->Message;
				 MessageBox::Show(msg);
			 }

			 res1 = tapeDrive->Rewind(false, returnCode);
			 if (!res1)
			 {
				 String^ msg = returnCode.ToString() + ": " +(gcnew Win32Exception(returnCode))->Message;
				 MessageBox::Show(msg);
			 }

			 bool res2 = tapeDrive->Close(returnCode);
			 if (!res2)
			 {
				 String^ msg = returnCode.ToString() + ": " +(gcnew Win32Exception(returnCode))->Message;
				 MessageBox::Show(msg);
			 }
			 this->button_Rewind->Enabled = true;
		 }
private: System::Void button_AbsBlk_Click(System::Object^  sender, System::EventArgs^  e) {

			 this->button_AbsBlk->Enabled = false;
			 TapeDriveWinAPI^ tapeDrive = gcnew TapeDriveWinAPI();
			 //String^ tapeName = "\\\\.\\TAPE0";
			 String^ tapeName = this->comboBoxTape->SelectedItem->ToString();
			 UInt32 returnCode = -1;
			 bool res1 = tapeDrive->Open(tapeName, returnCode);
			 if (!res1)
			 {
				 String^ msg = returnCode.ToString() + ": " +(gcnew Win32Exception(returnCode))->Message;
				 MessageBox::Show(msg);
			 }

			 res1 = tapeDrive->SeekToAbsoluteBlock(1, false, returnCode);
			 if (!res1)
			 {
				 String^ msg = returnCode.ToString() + ": " +(gcnew Win32Exception(returnCode))->Message;
				 MessageBox::Show(msg);
			 }

			 bool res2 = tapeDrive->Close(returnCode);
			 if (!res2)
			 {
				 String^ msg = returnCode.ToString() + ": " +(gcnew Win32Exception(returnCode))->Message;
				 MessageBox::Show(msg);
			 }
			 this->button_AbsBlk->Enabled = true;
		 }
private: System::Void button_Format_Click(System::Object^  sender, System::EventArgs^  e) {
			 this->button_Format->Enabled = false;
			 TapeDriveWinAPI^ tapeDrive = gcnew TapeDriveWinAPI();
			 //String^ tapeName = "\\\\.\\TAPE0";
			 String^ tapeName = this->comboBoxTape->SelectedItem->ToString();
			 UInt32 returnCode = -1;
			 bool res1 = tapeDrive->Open(tapeName, returnCode);
			 if (!res1)
			 {
				 String^ msg = returnCode.ToString() + ": " +(gcnew Win32Exception(returnCode))->Message;
				 MessageBox::Show(msg);
			 }

			 res1 = tapeDrive->FormatTape(false, returnCode);
			 if (!res1)
			 {
				 String^ msg = returnCode.ToString() + ": " +(gcnew Win32Exception(returnCode))->Message;
				 MessageBox::Show(msg);
			 }

			 bool res2 = tapeDrive->Close(returnCode);
			 if (!res2)
			 {
				 String^ msg = returnCode.ToString() + ": " +(gcnew Win32Exception(returnCode))->Message;
				 MessageBox::Show(msg);
			 }
			 this->button_Format->Enabled = true;
		 }
private: System::Void button_LogBlk_Click(System::Object^  sender, System::EventArgs^  e) {
			 this->button_LogBlk->Enabled = false;
			 TapeDriveWinAPI^ tapeDrive = gcnew TapeDriveWinAPI();
			 //String^ tapeName = "\\\\.\\TAPE0";
			 String^ tapeName = this->comboBoxTape->SelectedItem->ToString();
			 UInt32 returnCode = -1;
			 bool res1 = tapeDrive->Open(tapeName, returnCode);
			 if (!res1)
			 {
				 String^ msg = returnCode.ToString() + ": " +(gcnew Win32Exception(returnCode))->Message;
				 MessageBox::Show(msg);
			 }

			 res1 = tapeDrive->SeekToLogicalBlock(1, 20, false, returnCode);
			 if (!res1)
			 {
				 String^ msg = returnCode.ToString() + ": " +(gcnew Win32Exception(returnCode))->Message;
				 MessageBox::Show(msg);
			 }

			 bool res2 = tapeDrive->Close(returnCode);
			 if (!res2)
			 {
				 String^ msg = returnCode.ToString() + ": " +(gcnew Win32Exception(returnCode))->Message;
				 MessageBox::Show(msg);
			 }
			 this->button_LogBlk->Enabled = true;
		 }
private: System::Void button_SpaceFM_Click(System::Object^  sender, System::EventArgs^  e) {
			 this->button_SpaceFM->Enabled = false;
			 TapeDriveWinAPI^ tapeDrive = gcnew TapeDriveWinAPI();
			 //String^ tapeName = "\\\\.\\TAPE0";
			 String^ tapeName = this->comboBoxTape->SelectedItem->ToString();
			 UInt32 returnCode = -1;
			 bool res1 = tapeDrive->Open(tapeName, returnCode);
			 if (!res1)
			 {
				 String^ msg = returnCode.ToString() + ": " +(gcnew Win32Exception(returnCode))->Message;
				 MessageBox::Show(msg);
			 }

			 Int64 count = Int64::Parse(this->textBoxSpace->Text);

			 res1 = tapeDrive->SpaceFileMarks(count, false, returnCode);
			 if (!res1)
			 {
				 String^ msg = returnCode.ToString() + ": " +(gcnew Win32Exception(returnCode))->Message;
				 MessageBox::Show(msg);
			 }

			 bool res2 = tapeDrive->Close(returnCode);
			 if (!res2)
			 {
				 String^ msg = returnCode.ToString() + ": " +(gcnew Win32Exception(returnCode))->Message;
				 MessageBox::Show(msg);
			 }
			 this->button_SpaceFM->Enabled = true;
		 }
private: System::Void button_SpaceBlks_Click(System::Object^  sender, System::EventArgs^  e) {

			 this->button_SpaceBlks->Enabled = false;
			 TapeDriveWinAPI^ tapeDrive = gcnew TapeDriveWinAPI();
			 //String^ tapeName = "\\\\.\\TAPE0";
			 String^ tapeName = this->comboBoxTape->SelectedItem->ToString();
			 UInt32 returnCode = -1;
			 bool res1 = tapeDrive->Open(tapeName, returnCode);
			 if (!res1)
			 {
				 String^ msg = returnCode.ToString() + ": " +(gcnew Win32Exception(returnCode))->Message;
				 MessageBox::Show(msg);
			 }

			 res1 = tapeDrive->SpaceBlocks(-500, false, returnCode);
			 if (!res1)
			 {
				 String^ msg = returnCode.ToString() + ": " +(gcnew Win32Exception(returnCode))->Message;
				 MessageBox::Show(msg);
			 }

			 bool res2 = tapeDrive->Close(returnCode);
			 if (!res2)
			 {
				 String^ msg = returnCode.ToString() + ": " +(gcnew Win32Exception(returnCode))->Message;
				 MessageBox::Show(msg);
			 }
			 this->button_SpaceBlks->Enabled = true;
		 }
private: System::Void button_SpaceSFM_Click(System::Object^  sender, System::EventArgs^  e) {
			 this->button_SpaceSFM->Enabled = false;
			 TapeDriveWinAPI^ tapeDrive = gcnew TapeDriveWinAPI();
			 //String^ tapeName = "\\\\.\\TAPE0";
			 String^ tapeName = this->comboBoxTape->SelectedItem->ToString();
			 UInt32 returnCode = -1;
			 bool res1 = tapeDrive->Open(tapeName, returnCode);
			 if (!res1)
			 {
				 String^ msg = returnCode.ToString() + ": " +(gcnew Win32Exception(returnCode))->Message;
				 MessageBox::Show(msg);
			 }

			 res1 = tapeDrive->SpaceSetMarks(2, false, returnCode);
			 if (!res1)
			 {
				 String^ msg = returnCode.ToString() + ": " +(gcnew Win32Exception(returnCode))->Message;
				 MessageBox::Show(msg);
			 }

			 bool res2 = tapeDrive->Close(returnCode);
			 if (!res2)
			 {
				 String^ msg = returnCode.ToString() + ": " +(gcnew Win32Exception(returnCode))->Message;
				 MessageBox::Show(msg);
			 }
			 this->button_SpaceSFM->Enabled = true;
		 }
private: System::Void button_GetStatus_Click(System::Object^  sender, System::EventArgs^  e) {
			 this->button_GetStatus->Enabled = false;

			 TapeDriveWinAPI^ tapeDrive = gcnew TapeDriveWinAPI();
			 //String^ tapeName = "\\\\.\\TAPE0";
			 String^ tapeName = this->comboBoxTape->SelectedItem->ToString();
			 UInt32 returnCode = -1;
			 bool res1 = tapeDrive->Open(tapeName, returnCode);
			 if (!res1)
			 {
				 String^ msg = returnCode.ToString() + ": " +(gcnew Win32Exception(returnCode))->Message;
				 MessageBox::Show(msg);
			 }

			 res1 = tapeDrive->GetTapeStatusOK(returnCode);
			 if (!res1)
			 {
				 String^ msg = "Error: " + returnCode.ToString() + ": " +(gcnew Win32Exception(returnCode))->Message;
				 MessageBox::Show(msg);
			 }
			 else{
				 String^ msg = "OK: " + returnCode.ToString() + ": " +(gcnew Win32Exception(returnCode))->Message;
				 MessageBox::Show(msg);
			 }

			 bool res2 = tapeDrive->Close(returnCode);
			 if (!res2)
			 {
				 String^ msg = returnCode.ToString() + ": " +(gcnew Win32Exception(returnCode))->Message;
				 MessageBox::Show(msg);
			 }
			 this->button_GetStatus->Enabled = true;
		 }
private: System::Void button_logicalPos_Click(System::Object^  sender, System::EventArgs^  e) {

			 this->button_logicalPos->Enabled = false;

			 TapeDriveWinAPI^ tapeDrive = gcnew TapeDriveWinAPI();
			 //String^ tapeName = "\\\\.\\TAPE0";
			 String^ tapeName = this->comboBoxTape->SelectedItem->ToString();
			 UInt32 returnCode = -1;
			 bool res1 = tapeDrive->Open(tapeName, returnCode);
			 if (!res1)
			 {
				 String^ msg = returnCode.ToString() + ": " +(gcnew Win32Exception(returnCode))->Message;
				 MessageBox::Show(msg);
			 }

			 UInt32  partition = 66;
			 Int64 blkAddr = -1;
			 res1 = tapeDrive->GetTapePositionLogical(partition, blkAddr, returnCode);
			 if (!res1)
			 {
				 String^ msg = "Error: " + returnCode.ToString() + ": " +(gcnew Win32Exception(returnCode))->Message + " Partition: " + partition.ToString() + " Address: " + blkAddr.ToString();
				 MessageBox::Show(msg);
			 }
			 else{
				 String^ msg = "OK: " + returnCode.ToString() + ": " +(gcnew Win32Exception(returnCode))->Message + " Partition: " + partition.ToString() + " Address: " + blkAddr.ToString();
				 MessageBox::Show(msg);
			 }

			 bool res2 = tapeDrive->Close(returnCode);
			 if (!res2)
			 {
				 String^ msg = returnCode.ToString() + ": " +(gcnew Win32Exception(returnCode))->Message;
				 MessageBox::Show(msg);
			 }
			 this->button_logicalPos->Enabled = true;


		 }
private: System::Void buttonAbsPos_Click(System::Object^  sender, System::EventArgs^  e) {

			 this->buttonAbsPos->Enabled = false;

			 TapeDriveWinAPI^ tapeDrive = gcnew TapeDriveWinAPI();
			 //String^ tapeName = "\\\\.\\TAPE0";
			 String^ tapeName = this->comboBoxTape->SelectedItem->ToString();
			 UInt32 returnCode = -1;
			 bool res1 = tapeDrive->Open(tapeName, returnCode);
			 if (!res1)
			 {
				 String^ msg = returnCode.ToString() + ": " +(gcnew Win32Exception(returnCode))->Message;
				 MessageBox::Show(msg);
			 }

			 UInt32  partition = 66;
			 Int64 blkAddr = -1;
			 res1 = tapeDrive->GetTapePositionAbsolute(partition, blkAddr, returnCode);
			 if (!res1)
			 {
				 String^ msg = "Error: " + returnCode.ToString() + ": " +(gcnew Win32Exception(returnCode))->Message + " Partition: " + partition.ToString() + " Address: " + blkAddr.ToString();
				 MessageBox::Show(msg);
			 }
			 else{
				 String^ msg = "OK: " + returnCode.ToString() + ": " +(gcnew Win32Exception(returnCode))->Message + " Partition: " + partition.ToString() + " Address: " + blkAddr.ToString();
				 MessageBox::Show(msg);
			 }

			 bool res2 = tapeDrive->Close(returnCode);
			 if (!res2)
			 {
				 String^ msg = returnCode.ToString() + ": " +(gcnew Win32Exception(returnCode))->Message;
				 MessageBox::Show(msg);
			 }
			 this->buttonAbsPos->Enabled = true;
		 }
private: System::Void button_MediaParams_Click(System::Object^  sender, System::EventArgs^  e) {

			 this->button_MediaParams->Enabled = false;

			 TapeDriveWinAPI^ tapeDrive = gcnew TapeDriveWinAPI();
			 //String^ tapeName = "\\\\.\\TAPE0";
			 String^ tapeName = this->comboBoxTape->SelectedItem->ToString();
			 UInt32 returnCode = -1;
			 bool res1 = tapeDrive->Open(tapeName, returnCode);
			 if (!res1)
			 {
				 String^ msg = returnCode.ToString() + ": " +(gcnew Win32Exception(returnCode))->Message;
				 MessageBox::Show(msg);
			 }

//			 NumberFormatInfo nfi = new CultureInfo( "en-US", false ).NumberFormat;


			 TAPE_GET_MEDIA_PARAMETERS  mediaInfo;
			 res1 = tapeDrive->GetMediaParameters(&mediaInfo, returnCode);
			 if (!res1)
			 {
				 String^ msg = "Error: " + returnCode.ToString() + ": " +(gcnew Win32Exception(returnCode))->Message;
				 MessageBox::Show(msg);
			 }
			 else{
				 String^ msg = "OK: " + returnCode.ToString() + ": " +(gcnew Win32Exception(returnCode))->Message;
				 msg = msg + String::Format(" Partitions: {0} , Block Size: {1} , Write Protect: {2}, Capacity: {3:#,#}, Remaining: {4:#,#}", mediaInfo.PartitionCount, mediaInfo.BlockSize,(Boolean)(mediaInfo.WriteProtected), mediaInfo.Capacity.QuadPart, mediaInfo.Remaining.QuadPart);
				 MessageBox::Show(msg);
			 }

			 TAPE_GET_DRIVE_PARAMETERS  driveInfo;
			 res1 = tapeDrive->GetDriveParameters(&driveInfo, returnCode);
			 if (!res1)
			 {
				 String^ msg = "Error: " + returnCode.ToString() + ": " +(gcnew Win32Exception(returnCode))->Message;
				 MessageBox::Show(msg);
			 }
			 else{
				 String^ msg = "OK: " + returnCode.ToString() + ": " +(gcnew Win32Exception(returnCode))->Message;
				 msg = msg + 
					 String::Format(" ECC: {0}, Compression: {1} , DataPadding: {2}, ReportSetmarks: {3}, DefaultBlockSize: {4:#,#}, MaximumBlockSize: {5:#,#}, MinimumBlockSize: {6:#,#}, MaximumPartitionCount: {7}, FeaturesLow: {8:X}, FeaturesHigh: {9:X}, EOTWarningZoneSize: {10}",
					(Boolean)(driveInfo.ECC), (Boolean)(driveInfo.Compression), (Boolean)(driveInfo.DataPadding), (Boolean)(driveInfo.ReportSetmarks), driveInfo.DefaultBlockSize, driveInfo.MaximumBlockSize,
					 driveInfo.MinimumBlockSize,driveInfo.MaximumPartitionCount,driveInfo.FeaturesLow, driveInfo.FeaturesHigh, driveInfo.EOTWarningZoneSize);
				 MessageBox::Show(msg);
			 }

			 bool res2 = tapeDrive->Close(returnCode);
			 if (!res2)
			 {
				 String^ msg = returnCode.ToString() + ": " +(gcnew Win32Exception(returnCode))->Message;
				 MessageBox::Show(msg);
			 }
			 this->button_MediaParams->Enabled = true;

		 }
private: System::Void button_SetBlkSize_Click(System::Object^  sender, System::EventArgs^  e) {

			 this->button_SetBlkSize->Enabled = false;

			 TapeDriveWinAPI^ tapeDrive = gcnew TapeDriveWinAPI();
			 //String^ tapeName = "\\\\.\\TAPE0";
			 String^ tapeName = this->comboBoxTape->SelectedItem->ToString();
			 UInt32 returnCode = -1;
			 bool res1 = tapeDrive->Open(tapeName, returnCode);
			 if (!res1)
			 {
				 String^ msg = returnCode.ToString() + ": " +(gcnew Win32Exception(returnCode))->Message;
				 MessageBox::Show(msg);
			 }


			 res1 = tapeDrive->SetMediaBlockSize(65536, returnCode);
			 if (!res1)
			 {
				 String^ msg = "Error: " + returnCode.ToString() + ": " +(gcnew Win32Exception(returnCode))->Message;
				 MessageBox::Show(msg);
			 }
			 else{
				 String^ msg = "OK: " + returnCode.ToString() + ": " +(gcnew Win32Exception(returnCode))->Message;
				 MessageBox::Show(msg);
			 }

			 bool res2 = tapeDrive->Close(returnCode);
			 if (!res2)
			 {
				 String^ msg = returnCode.ToString() + ": " +(gcnew Win32Exception(returnCode))->Message;
				 MessageBox::Show(msg);
			 }
			 this->button_SetBlkSize->Enabled = true;
		 }
private: System::Void button_SetDriveParams_Click(System::Object^  sender, System::EventArgs^  e) {

			 this->button_SetDriveParams->Enabled = false;

			 TapeDriveWinAPI^ tapeDrive = gcnew TapeDriveWinAPI();
			 //String^ tapeName = "\\\\.\\TAPE0";
			 String^ tapeName = this->comboBoxTape->SelectedItem->ToString();
			 UInt32 returnCode = -1;
			 bool res1 = tapeDrive->Open(tapeName, returnCode);
			 if (!res1)
			 {
				 String^ msg = returnCode.ToString() + ": " +(gcnew Win32Exception(returnCode))->Message;
				 MessageBox::Show(msg);
			 }


			 TAPE_SET_DRIVE_PARAMETERS driveParams;

			 driveParams.Compression = false;
			 driveParams.DataPadding = false;
			 driveParams.ECC = false;
			 driveParams.ReportSetmarks = true;
			 driveParams.EOTWarningZoneSize = 0;

			 res1 = tapeDrive->SetTapeDriveParams(driveParams,returnCode);
			 if (!res1)
			 {
				 String^ msg = "Error: " + returnCode.ToString() + ": " +(gcnew Win32Exception(returnCode))->Message;
				 MessageBox::Show(msg);
			 }
			 else{
				 String^ msg = "OK: " + returnCode.ToString() + ": " +(gcnew Win32Exception(returnCode))->Message;
				 MessageBox::Show(msg);
			 }

			 bool res2 = tapeDrive->Close(returnCode);
			 if (!res2)
			 {
				 String^ msg = returnCode.ToString() + ": " +(gcnew Win32Exception(returnCode))->Message;
				 MessageBox::Show(msg);
			 }
			 this->button_SetDriveParams->Enabled = true;
		 }
private: System::Void button_CreatePart_Click(System::Object^  sender, System::EventArgs^  e) {

			 this->button_CreatePart->Enabled = false;

			 TapeDriveWinAPI^ tapeDrive = gcnew TapeDriveWinAPI();
			 //String^ tapeName = "\\\\.\\TAPE0";
			 String^ tapeName = this->comboBoxTape->SelectedItem->ToString();
			 UInt32 returnCode = -1;
			 bool res1 = tapeDrive->Open(tapeName, returnCode);
			 if (!res1)
			 {
				 String^ msg = returnCode.ToString() + ": " +(gcnew Win32Exception(returnCode))->Message;
				 MessageBox::Show(msg);
			 }


			 res1 = tapeDrive->PartitionTape(TAPE_SELECT_PARTITIONS,1,5000,returnCode);
			 if (!res1)
			 {
				 String^ msg = "Error: " + returnCode.ToString() + ": " +(gcnew Win32Exception(returnCode))->Message;
				 MessageBox::Show(msg);
			 }
			 else{
				 String^ msg = "OK: " + returnCode.ToString() + ": " +(gcnew Win32Exception(returnCode))->Message;
				 MessageBox::Show(msg);
			 }

			 bool res2 = tapeDrive->Close(returnCode);
			 if (!res2)
			 {
				 String^ msg = returnCode.ToString() + ": " +(gcnew Win32Exception(returnCode))->Message;
				 MessageBox::Show(msg);
			 }
			 this->button_CreatePart->Enabled = true;
		 }
private: System::Void button_Erase_Click(System::Object^  sender, System::EventArgs^  e) {

			 this->button_Erase->Enabled = false;

			 TapeDriveWinAPI^ tapeDrive = gcnew TapeDriveWinAPI();
			 //String^ tapeName = "\\\\.\\TAPE0";
			 String^ tapeName = this->comboBoxTape->SelectedItem->ToString();
			 UInt32 returnCode = -1;
			 bool res1 = tapeDrive->Open(tapeName, returnCode);
			 if (!res1)
			 {
				 String^ msg = returnCode.ToString() + ": " +(gcnew Win32Exception(returnCode))->Message;
				 MessageBox::Show(msg);
			 }


			 res1 = tapeDrive->EraseTapeDo(TAPE_ERASE_SHORT,false,returnCode);
			 if (!res1)
			 {
				 String^ msg = "Error: " + returnCode.ToString() + ": " +(gcnew Win32Exception(returnCode))->Message;
				 MessageBox::Show(msg);
			 }
			 else{
				 String^ msg = "OK: " + returnCode.ToString() + ": " +(gcnew Win32Exception(returnCode))->Message;
				 MessageBox::Show(msg);
			 }

			 bool res2 = tapeDrive->Close(returnCode);
			 if (!res2)
			 {
				 String^ msg = returnCode.ToString() + ": " +(gcnew Win32Exception(returnCode))->Message;
				 MessageBox::Show(msg);
			 }
			 this->button_Erase->Enabled = true;
		 }
private: System::Void button_WriteTpM3_Click(System::Object^  sender, System::EventArgs^  e) {

			 this->button_WriteTpM3->Enabled = false;

			 TapeDriveWinAPI^ tapeDrive = gcnew TapeDriveWinAPI();
			 //String^ tapeName = "\\\\.\\TAPE0";
			 String^ tapeName = this->comboBoxTape->SelectedItem->ToString();
			 UInt32 returnCode = -1;
			 bool res1 = tapeDrive->Open(tapeName, returnCode);
			 if (!res1)
			 {
				 String^ msg = returnCode.ToString() + ": " +(gcnew Win32Exception(returnCode))->Message;
				 MessageBox::Show(msg);
			 }


			 res1 = tapeDrive->WriteTapemarkDo(TAPE_FILEMARKS,3,false,returnCode);
			 if (!res1)
			 {
				 String^ msg = "Error: " + returnCode.ToString() + ": " +(gcnew Win32Exception(returnCode))->Message;
				 MessageBox::Show(msg);
			 }
			 else{
				 String^ msg = "OK: " + returnCode.ToString() + ": " +(gcnew Win32Exception(returnCode))->Message;
				 MessageBox::Show(msg);
			 }

			 bool res2 = tapeDrive->Close(returnCode);
			 if (!res2)
			 {
				 String^ msg = returnCode.ToString() + ": " +(gcnew Win32Exception(returnCode))->Message;
				 MessageBox::Show(msg);
			 }
			 this->button_WriteTpM3->Enabled = true;
		 }
private: System::Void button1_Click_1(System::Object^  sender, System::EventArgs^  e) {

			 this->button_Write1GB->Enabled = false;

			 TapeDriveWinAPI^ tapeDrive = gcnew TapeDriveWinAPI();
			 //String^ tapeName = "\\\\.\\TAPE0";
			 String^ tapeName = this->comboBoxTape->SelectedItem->ToString();
			 UInt32 returnCode = -1;
			 bool res1 = tapeDrive->Open(tapeName, returnCode);
			 if (!res1)
			 {
				 String^ msg = returnCode.ToString() + ": " +(gcnew Win32Exception(returnCode))->Message;
				 MessageBox::Show(msg);
			 }


			 array<byte>^ buffer = gcnew array<byte>(65536);

			 pin_ptr<byte> pBuffer = &buffer[0];
			 memset(pBuffer,8,65536);
			 pBuffer = nullptr;
			 for (int j =0; j<65536; j++)
			 {
				 buffer[j]= rand();
			 }

			 UInt32 written = 0;

			 for(int i =0; i< 65536; i++)
			 {

				 res1 = tapeDrive->WriteTape(buffer,65536, written, returnCode);		 
				if (!res1)
				{
					String^ msg = "Error: " + returnCode.ToString() + ": " +(gcnew Win32Exception(returnCode))->Message;
					MessageBox::Show(msg);
				}

			}


			 bool res2 = tapeDrive->Close(returnCode);
			 if (!res2)
			 {
				 String^ msg = returnCode.ToString() + ": " +(gcnew Win32Exception(returnCode))->Message;
				 MessageBox::Show(msg);
			 }
			 this->button_Write1GB->Enabled = true;
		 }
private: System::Void button_Read_Click(System::Object^  sender, System::EventArgs^  e) {

			 this->button_Read->Enabled = false;

			 TapeDriveWinAPI^ tapeDrive = gcnew TapeDriveWinAPI();
			 //String^ tapeName = "\\\\.\\TAPE0";
			 String^ tapeName = this->comboBoxTape->SelectedItem->ToString();
			 UInt32 returnCode = -1;
			 bool res1 = tapeDrive->Open(tapeName, returnCode);
			 if (!res1)
			 {
				 String^ msg = returnCode.ToString() + ": " +(gcnew Win32Exception(returnCode))->Message;
				 MessageBox::Show(msg);
			 }


			 array<byte>^ buffer = gcnew array<byte>(65536);

			 pin_ptr<byte> pBuffer = &buffer[0];
			 memset(pBuffer,8,65536);
			 pBuffer = nullptr;

			 UInt32 read = 0;

			 for(int i =0; i< 73559; i++)
			 {
				 res1 = tapeDrive->ReadTape(buffer,80, read, returnCode);		 
				if (!res1)
				{
					String^ msg = "Error: " + returnCode.ToString() + ": " +(gcnew Win32Exception(returnCode))->Message;
					MessageBox::Show(msg);
				}

			}


			 bool res2 = tapeDrive->Close(returnCode);
			 if (!res2)
			 {
				 String^ msg = returnCode.ToString() + ": " +(gcnew Win32Exception(returnCode))->Message;
				 MessageBox::Show(msg);
			 }
			 this->button_Read->Enabled = true;
		 }
private: System::Void button_SizeOf_Click(System::Object^  sender, System::EventArgs^  e) {

			 this->button_SizeOf->Enabled = false;

			 READ_POSITION rp;

			 memset(&rp,0,sizeof(READ_POSITION));

			 rp.ReadPosition.BOP = 1;
			 rp.ReadPosition.LOCU = 1;
			 
			 rp.ReadPosition.EOP = 1;

			 rp.ReadPosition.BPEW = 1;

			 rp.ReadPosition.BYCU = 1;
			 rp.ReadPosition.LOLU = 1;
			 rp.ReadPosition.PERR = 1;

			 rp.ReadPosition.PartitionNumber = 3;

			 rp.RawData[3] = 0x1c;

			 Int64 addLength = rp.ReadPosition.AdditionalLength();

			 rp.ReadPosition.NumOfLogicalObjInObjBuff(0x050607);
			 Int64 numOfL = rp.ReadPosition.NumOfLogicalObjInObjBuff();

			 rp.ReadPosition.FirstLogicalObjLocation(0x08090a0b0c0d0e0f);
			 Int64 logicalFLOIO = rp.ReadPosition.FirstLogicalObjLocation();

			 rp.ReadPosition.LastLogicalObjLocation(0x1011121314151617);
			 Int64 logicalLLOIO = rp.ReadPosition.LastLogicalObjLocation();

			 rp.ReadPosition.NumOfBytesInObjBuff(0x18191a1b1c1d1e1f);
			 Int64 numberOfBytes = rp.ReadPosition.NumOfBytesInObjBuff();

			 Int64 size = sizeof(rp);
			 String^ msg = " Size of: " + size;
			 MessageBox::Show(msg);

			 this->button_SizeOf->Enabled = true;
		 }
private: System::Void button_LoadSCSI_Click(System::Object^  sender, System::EventArgs^  e) {

			 this->button_LoadSCSI->Enabled = false;
			 TapeDriveSCSI^ tapeDrive = gcnew TapeDriveSCSI();
			 //String^ tapeName = "\\\\.\\TAPE0";
			 String^ tapeName = this->comboBoxTape->SelectedItem->ToString();
			 UInt32 returnCode = -1;
			 bool res1 = tapeDrive->Open(tapeName, returnCode);
			 if (!res1)
			 {
				 String^ msg = returnCode.ToString() + ": " +(gcnew Win32Exception(returnCode))->Message;
				 MessageBox::Show(msg);
			 }

			 ERROR_SNS_INFO^ snsInfo;
			 res1 = tapeDrive->Load(false, returnCode, snsInfo);
			 if (!res1)
			 {
				 String^ msg = returnCode.ToString() + ": " +(gcnew Win32Exception(returnCode))->Message + "\n" 
					 + String::Format("SNS Key: {0:X}, ASC: {1:X}, ASCQ: {2:X}, FRU: {3:X} ",snsInfo->SNSKey, snsInfo->ASC, snsInfo->ASCQ, snsInfo->FRU);
				 MessageBox::Show(msg);
			 }

			 bool res2 = tapeDrive->Close(returnCode);
			 if (!res2)
			 {
				 String^ msg = returnCode.ToString() + ": " +(gcnew Win32Exception(returnCode))->Message;
				 MessageBox::Show(msg);
			 }

			 this->button_LoadSCSI->Enabled = true;
		 }
private: System::Void btnUnloadSCSI_Click(System::Object^  sender, System::EventArgs^  e) {

			 this->btnUnloadSCSI->Enabled = false;
			 TapeDriveSCSI^ tapeDrive = gcnew TapeDriveSCSI();
			 //String^ tapeName = "\\\\.\\TAPE0";
			 String^ tapeName = this->comboBoxTape->SelectedItem->ToString();
			 UInt32 returnCode = -1;
			 bool res1 = tapeDrive->Open(tapeName, returnCode);
			 if (!res1)
			 {
				 String^ msg = returnCode.ToString() + ": " +(gcnew Win32Exception(returnCode))->Message;
				 MessageBox::Show(msg);
			 }

			ERROR_SNS_INFO^ snsInfo;

			 res1 = tapeDrive->Unload(false, returnCode, snsInfo);
			 if (!res1)
			 {
				 String^ msg = returnCode.ToString() + ": " +(gcnew Win32Exception(returnCode))->Message + "\n" 
					 + String::Format("SNS Key: {0:X}, ASC: {1:X}, ASCQ: {2:X}, FRU: {3:X} ",snsInfo->SNSKey, snsInfo->ASC, snsInfo->ASCQ, snsInfo->FRU);
				 MessageBox::Show(msg);
			 }

			 bool res2 = tapeDrive->Close(returnCode);
			 if (!res2)
			 {
				 String^ msg = returnCode.ToString() + ": " +(gcnew Win32Exception(returnCode))->Message;
				 MessageBox::Show(msg);
			 }

			 this->btnUnloadSCSI->Enabled = true;
		 }
private: System::Void buttonFormat_Click(System::Object^  sender, System::EventArgs^  e) {

				this->buttonFormat->Enabled = false;

				TapeDriveSCSI^ tapeDrive = gcnew TapeDriveSCSI();
				//String^ tapeName = "\\\\.\\TAPE0";
				String^ tapeName = this->comboBoxTape->SelectedItem->ToString();
				UInt32 returnCode = -1;
				bool res1 = tapeDrive->Open(tapeName, returnCode);
				if (!res1)
				{
					String^ msg = returnCode.ToString() + ": " +(gcnew Win32Exception(returnCode))->Message;
					MessageBox::Show(msg);
				}

				ERROR_SNS_INFO^ snsInfo;
				
				Byte fmtType = 	Byte::Parse(textBoxFormatType->Text);

				res1 = tapeDrive->FormatTape(fmtType, false, false, returnCode, snsInfo);

				if (!res1)
				{
					String^ msg = returnCode.ToString() + ": " +(gcnew Win32Exception(returnCode))->Message + "\n" 
						+ String::Format("SNS Key: {0:X}, ASC: {1:X}, ASCQ: {2:X}, FRU: {3:X} ",snsInfo->SNSKey, snsInfo->ASC, snsInfo->ASCQ, snsInfo->FRU);
					MessageBox::Show(msg);
				}

				bool res2 = tapeDrive->Close(returnCode);
				if (!res2)
				{
					String^ msg = returnCode.ToString() + ": " +(gcnew Win32Exception(returnCode))->Message;
					MessageBox::Show(msg);
				}

			 	this->buttonFormat->Enabled = true;
		 }
private: System::Void buttonEraseSCSI_Click(System::Object^  sender, System::EventArgs^  e) {


			 this->buttonEraseSCSI->Enabled = false;

			 TapeDriveSCSI^ tapeDrive = gcnew TapeDriveSCSI();
			 //String^ tapeName = "\\\\.\\TAPE0";
			 String^ tapeName = this->comboBoxTape->SelectedItem->ToString();
			 UInt32 returnCode = -1;
			 bool res1 = tapeDrive->Open(tapeName, returnCode);
			 if (!res1)
			 {
				 String^ msg = returnCode.ToString() + ": " +(gcnew Win32Exception(returnCode))->Message;
				 MessageBox::Show(msg);
			 }

			 ERROR_SNS_INFO^ snsInfo;

			 bool isLongErase = checkBoxLongErase->Checked;

			 res1 = tapeDrive->EraseTape(isLongErase,false, returnCode, snsInfo);

			 if (!res1)
			 {
				 String^ msg = returnCode.ToString() + ": " +(gcnew Win32Exception(returnCode))->Message + "\n" 
					 + String::Format("SNS Key: {0:X}, ASC: {1:X}, ASCQ: {2:X}, FRU: {3:X} ",snsInfo->SNSKey, snsInfo->ASC, snsInfo->ASCQ, snsInfo->FRU);
				 MessageBox::Show(msg);
			 }

			 bool res2 = tapeDrive->Close(returnCode);
			 if (!res2)
			 {
				 String^ msg = returnCode.ToString() + ": " +(gcnew Win32Exception(returnCode))->Message;
				 MessageBox::Show(msg);
			 }

			 this->buttonEraseSCSI->Enabled = true;

		 }
private: System::Void buttonRewindSCSI_Click(System::Object^  sender, System::EventArgs^  e) {

			 this->buttonRewindSCSI->Enabled = false;

			 TapeDriveSCSI^ tapeDrive = gcnew TapeDriveSCSI();
			 //String^ tapeName = "\\\\.\\TAPE0";
			 String^ tapeName = this->comboBoxTape->SelectedItem->ToString();
			 UInt32 returnCode = -1;
			 bool res1 = tapeDrive->Open(tapeName, returnCode);
			 if (!res1)
			 {
				 String^ msg = returnCode.ToString() + ": " +(gcnew Win32Exception(returnCode))->Message;
				 MessageBox::Show(msg);
			 }

			 ERROR_SNS_INFO^ snsInfo;

			 res1 = tapeDrive->Rewind(false, returnCode, snsInfo);

			 if (!res1)
			 {
				 String^ msg = returnCode.ToString() + ": " +(gcnew Win32Exception(returnCode))->Message + "\n" 
					 + String::Format("SNS Key: {0:X}, ASC: {1:X}, ASCQ: {2:X}, FRU: {3:X} ",snsInfo->SNSKey, snsInfo->ASC, snsInfo->ASCQ, snsInfo->FRU);
				 MessageBox::Show(msg);
			 }

			 bool res2 = tapeDrive->Close(returnCode);
			 if (!res2)
			 {
				 String^ msg = returnCode.ToString() + ": " +(gcnew Win32Exception(returnCode))->Message;
				 MessageBox::Show(msg);
			 }

			 this->buttonRewindSCSI->Enabled = true;
		 }
private: System::Void buttonPositionShort_Click(System::Object^  sender, System::EventArgs^  e) {

			 this->buttonPositionShort->Enabled = false;

			 TapeDriveSCSI^ tapeDrive = gcnew TapeDriveSCSI();
			 //String^ tapeName = "\\\\.\\TAPE0";
			 String^ tapeName = this->comboBoxTape->SelectedItem->ToString();
			 UInt32 returnCode = -1;
			 bool res1 = tapeDrive->Open(tapeName, returnCode);
			 if (!res1)
			 {
				 String^ msg = returnCode.ToString() + ": " +(gcnew Win32Exception(returnCode))->Message;
				 MessageBox::Show(msg);
			 }

			 ERROR_SNS_INFO^ snsInfo;
			 READ_POSITION_SHORT positionInfo;
			 memset(&positionInfo,0,sizeof(positionInfo));

			 res1 = tapeDrive->ReadPositionShort(positionInfo,returnCode,snsInfo);

			 if (!res1)
			 {
				 String^ msg = returnCode.ToString() + ": " +(gcnew Win32Exception(returnCode))->Message + "\n" 
					 + String::Format("SNS Key: {0:X}, ASC: {1:X}, ASCQ: {2:X}, FRU: {3:X} ",snsInfo->SNSKey, snsInfo->ASC, snsInfo->ASCQ, snsInfo->FRU);
				 MessageBox::Show(msg);
			 }
			 else{
				 String^ msg = String::Format("BOP: {0}, EOP: {1}, LOCU: {2}, BYCU: {3}, LOLU: {4}, PERR: {5}, BPEW: {6}, ",positionInfo.BOP, positionInfo.EOP, positionInfo.LOCU, positionInfo.BYCU, positionInfo.LOLU, positionInfo.PERR, positionInfo.BPEW) +
					 String::Format("Partition Number: {0}, First Logical Obj Location: {1}, Last Logical Obj Location: {2}, ",positionInfo.PartitionNumber,positionInfo.FirstLogicalObjLocation(),positionInfo.LastLogicalObjLocation()) +
					 String::Format("Number Of Logical Objects in Obj Buffer: {0}, Number Of Bytes in Obj Buffer: {1}",positionInfo.NumOfLogicalObjInObjBuffer(), positionInfo.NumOfBytesInObjBuff());
				 MessageBox::Show(msg);


			 }

			 bool res2 = tapeDrive->Close(returnCode);
			 if (!res2)
			 {
				 String^ msg = returnCode.ToString() + ": " +(gcnew Win32Exception(returnCode))->Message;
				 MessageBox::Show(msg);
			 }

			 this->buttonPositionShort->Enabled = true;
		 }
private: System::Void buttonPositionLong_Click(System::Object^  sender, System::EventArgs^  e) {


			 this->buttonPositionLong->Enabled = false;

			 TapeDriveSCSI^ tapeDrive = gcnew TapeDriveSCSI();
			 //String^ tapeName = "\\\\.\\TAPE0";
			 String^ tapeName = this->comboBoxTape->SelectedItem->ToString();
			 UInt32 returnCode = -1;
			 bool res1 = tapeDrive->Open(tapeName, returnCode);
			 if (!res1)
			 {
				 String^ msg = returnCode.ToString() + ": " +(gcnew Win32Exception(returnCode))->Message;
				 MessageBox::Show(msg);
			 }

			 ERROR_SNS_INFO^ snsInfo;
			 READ_POSITION_LONG positionInfo;
			 memset(&positionInfo,0,sizeof(positionInfo));

			 res1 = tapeDrive->ReadPositionLong(positionInfo,returnCode,snsInfo);

			 if (!res1)
			 {
				 String^ msg = returnCode.ToString() + ": " +(gcnew Win32Exception(returnCode))->Message + "\n" 
					 + String::Format("SNS Key: {0:X}, ASC: {1:X}, ASCQ: {2:X}, FRU: {3:X} ",snsInfo->SNSKey, snsInfo->ASC, snsInfo->ASCQ, snsInfo->FRU);
				 MessageBox::Show(msg);
			 }
			 else{
				 String^ msg = String::Format("BOP: {0}, EOP: {1}, MPU: {2}, LONU: {3}, ",positionInfo.BOP, positionInfo.EOP, positionInfo.MPU, positionInfo.LONU) +
					 String::Format("Partition Number: {0}, Logical Obj Number: {1}, Logical File Number: {2} ",positionInfo.PartitionNumber(),positionInfo.LogicalObjNumber(), positionInfo.LogicalFileIdnf());

				 MessageBox::Show(msg);


			 }

			 bool res2 = tapeDrive->Close(returnCode);
			 if (!res2)
			 {
				 String^ msg = returnCode.ToString() + ": " +(gcnew Win32Exception(returnCode))->Message;
				 MessageBox::Show(msg);
			 }

			 this->buttonPositionLong->Enabled = true;

		 }
private: System::Void buttonPositionExtnd_Click(System::Object^  sender, System::EventArgs^  e) {

			 this->buttonPositionExtnd->Enabled = false;

			 TapeDriveSCSI^ tapeDrive = gcnew TapeDriveSCSI();
			 //String^ tapeName = "\\\\.\\TAPE0";
			 String^ tapeName = this->comboBoxTape->SelectedItem->ToString();
			 UInt32 returnCode = -1;
			 bool res1 = tapeDrive->Open(tapeName, returnCode);
			 if (!res1)
			 {
				 String^ msg = returnCode.ToString() + ": " +(gcnew Win32Exception(returnCode))->Message;
				 MessageBox::Show(msg);
			 }

			 ERROR_SNS_INFO^ snsInfo;
			 READ_POSITION_EXTND positionInfo;
			 memset(&positionInfo,0,sizeof(positionInfo));

			 res1 = tapeDrive->ReadPositionExtended(positionInfo,returnCode,snsInfo);

			 if (!res1)
			 {
				 String^ msg = returnCode.ToString() + ": " +(gcnew Win32Exception(returnCode))->Message + "\n" 
					 + String::Format("SNS Key: {0:X}, ASC: {1:X}, ASCQ: {2:X}, FRU: {3:X} ",snsInfo->SNSKey, snsInfo->ASC, snsInfo->ASCQ, snsInfo->FRU);
				 MessageBox::Show(msg);
			 }
			 else{
				 String^ msg = String::Format("BOP: {0}, EOP: {1}, LOCU: {2}, BYCU: {3}, LOLU: {4}, PERR: {5}, BPEW: {6}, ",positionInfo.BOP, positionInfo.EOP, positionInfo.LOCU, positionInfo.BYCU, positionInfo.LOLU, positionInfo.PERR, positionInfo.BPEW) +
					 String::Format("Partition Number: {0}, First Logical Obj Location: {1}, Last Logical Obj Location: {2}, ",positionInfo.PartitionNumber,positionInfo.FirstLogicalObjLocation(),positionInfo.LastLogicalObjLocation()) +
					 String::Format("Number Of Logical Objects in Obj Buffer: {0}, Number Of Bytes in Obj Buffer: {1}",positionInfo.NumOfLogicalObjInObjBuff(), positionInfo.NumOfBytesInObjBuff());
				 MessageBox::Show(msg);

			 }

			 bool res2 = tapeDrive->Close(returnCode);
			 if (!res2)
			 {
				 String^ msg = returnCode.ToString() + ": " +(gcnew Win32Exception(returnCode))->Message;
				 MessageBox::Show(msg);
			 }

			 this->buttonPositionExtnd->Enabled = true;
		 }
private: System::Void buttonLocateEOD_Click(System::Object^  sender, System::EventArgs^  e) {

			 				UInt32 partNumber = UInt32::Parse(textBoxPartition->Text);

							this->buttonLocateEOD->Enabled = false;

							TapeDriveSCSI^ tapeDrive = gcnew TapeDriveSCSI();
							//String^ tapeName = "\\\\.\\TAPE0";
							String^ tapeName = this->comboBoxTape->SelectedItem->ToString();
							UInt32 returnCode = -1;
							bool res1 = tapeDrive->Open(tapeName, returnCode);
							if (!res1)
							{
								String^ msg = returnCode.ToString() + ": " +(gcnew Win32Exception(returnCode))->Message;
								MessageBox::Show(msg);
							}

							ERROR_SNS_INFO^ snsInfo;

							//res1 = tapeDrive->SeekToEOD(returnCode, snsInfo);
							res1 = tapeDrive->SeekToEOD(false, partNumber, returnCode, snsInfo);
//							res1 = tapeDrive->SeekToEODCurrentPartition(false,returnCode,snsInfo);

							if (!res1)
							{
								String^ msg = returnCode.ToString() + ": " +(gcnew Win32Exception(returnCode))->Message + "\n" 
									+ String::Format("SNS Key: {0:X}, ASC: {1:X}, ASCQ: {2:X}, FRU: {3:X} ",snsInfo->SNSKey, snsInfo->ASC, snsInfo->ASCQ, snsInfo->FRU);
								MessageBox::Show(msg);
							}

							bool res2 = tapeDrive->Close(returnCode);
							if (!res2)
							{
								String^ msg = returnCode.ToString() + ": " +(gcnew Win32Exception(returnCode))->Message;
								MessageBox::Show(msg);
							}

							this->buttonLocateEOD->Enabled = true;
		 }
private: System::Void buttonLocateBOP_Click(System::Object^  sender, System::EventArgs^  e) {

			 UInt32 partNumber = UInt32::Parse(textBoxPartition->Text);

			 this->buttonLocateBOP->Enabled = false;

			 TapeDriveSCSI^ tapeDrive = gcnew TapeDriveSCSI();
			 //String^ tapeName = "\\\\.\\TAPE0";
			 String^ tapeName = this->comboBoxTape->SelectedItem->ToString();
			 UInt32 returnCode = -1;
			 bool res1 = tapeDrive->Open(tapeName, returnCode);
			 if (!res1)
			 {
				 String^ msg = returnCode.ToString() + ": " +(gcnew Win32Exception(returnCode))->Message;
				 MessageBox::Show(msg);
			 }

			 ERROR_SNS_INFO^ snsInfo;


			 //res1 = tapeDrive->SeekToBOP(partNumber, false, returnCode, snsInfo);
			 //res1 = tapeDrive->SeekToBOPCurrentPartition(false,returnCode,snsInfo);
			 res1 = tapeDrive->SeekToBOP(false, partNumber, returnCode, snsInfo);

			 if (!res1)
			 {
				 String^ msg = returnCode.ToString() + ": " +(gcnew Win32Exception(returnCode))->Message + "\n" 
					 + String::Format("SNS Key: {0:X}, ASC: {1:X}, ASCQ: {2:X}, FRU: {3:X} ",snsInfo->SNSKey, snsInfo->ASC, snsInfo->ASCQ, snsInfo->FRU);
				 MessageBox::Show(msg);
			 }

			 bool res2 = tapeDrive->Close(returnCode);
			 if (!res2)
			 {
				 String^ msg = returnCode.ToString() + ": " +(gcnew Win32Exception(returnCode))->Message;
				 MessageBox::Show(msg);
			 }

			 this->buttonLocateBOP->Enabled = true;
		 }
private: System::Void buttonLocate_Click(System::Object^  sender, System::EventArgs^  e) {
			 
			 UInt64 blockNumber = UInt64::Parse(textBoxBlockNumber->Text);

			 this->buttonLocate->Enabled = false;

			 TapeDriveSCSI^ tapeDrive = gcnew TapeDriveSCSI();
			 //String^ tapeName = "\\\\.\\TAPE0";
			 String^ tapeName = this->comboBoxTape->SelectedItem->ToString();
			 UInt32 returnCode = -1;
			 bool res1 = tapeDrive->Open(tapeName, returnCode);
			 if (!res1)
			 {
				 String^ msg = returnCode.ToString() + ": " +(gcnew Win32Exception(returnCode))->Message;
				 MessageBox::Show(msg);
			 }

			 ERROR_SNS_INFO^ snsInfo;

			 res1 = tapeDrive->LocateCDB16(true,false,1,LogicalObject,blockNumber,returnCode,snsInfo);

			 if (!res1)
			 {
				 String^ msg = returnCode.ToString() + ": " +(gcnew Win32Exception(returnCode))->Message + "\n" 
					 + String::Format("SNS Key: {0:X}, ASC: {1:X}, ASCQ: {2:X}, FRU: {3:X} ",snsInfo->SNSKey, snsInfo->ASC, snsInfo->ASCQ, snsInfo->FRU);
				 MessageBox::Show(msg);
			 }

			 bool res2 = tapeDrive->Close(returnCode);
			 if (!res2)
			 {
				 String^ msg = returnCode.ToString() + ": " +(gcnew Win32Exception(returnCode))->Message;
				 MessageBox::Show(msg);
			 }

			 this->buttonLocate->Enabled = true;
		 }
private: System::Void buttonSpace_Click(System::Object^  sender, System::EventArgs^  e) {

			 this->buttonSpace->Enabled = false;

			
			 Int64 count = Int64::Parse(this->textBoxSpace->Text);

			 TapeDriveSCSI^ tapeDrive = gcnew TapeDriveSCSI();
			 //String^ tapeName = "\\\\.\\TAPE0";
			 String^ tapeName = this->comboBoxTape->SelectedItem->ToString();
			 UInt32 returnCode = -1;
			 bool res1 = tapeDrive->Open(tapeName, returnCode);
			 if (!res1)
			 {
				 String^ msg = returnCode.ToString() + ": " +(gcnew Win32Exception(returnCode))->Message;
				 MessageBox::Show(msg);
			 }

			 ERROR_SNS_INFO^ snsInfo;
			 
			 if(this->comboBoxObjectType->Text == "Blocks")
			 {
				 res1 = tapeDrive->SpaceCDB16(Blocks,count,returnCode,snsInfo);
			 }
			 else
			 {
				 res1 = tapeDrive->SpaceCDB16(FileMarks,count,returnCode,snsInfo);
			 }

			 if (!res1)
			 {
				 String^ msg = returnCode.ToString() + ": " +(gcnew Win32Exception(returnCode))->Message + "\n" 
					 + String::Format("SNS Key: {0:X}, ASC: {1:X}, ASCQ: {2:X}, FRU: {3:X} ",snsInfo->SNSKey, snsInfo->ASC, snsInfo->ASCQ, snsInfo->FRU);
				 MessageBox::Show(msg);
			 }

			 bool res2 = tapeDrive->Close(returnCode);
			 if (!res2)
			 {
				 String^ msg = returnCode.ToString() + ": " +(gcnew Win32Exception(returnCode))->Message;
				 MessageBox::Show(msg);
			 }

			 this->buttonSpace->Enabled = true;
		 }
private: System::Void buttonWriteFMSCSI_Click(System::Object^  sender, System::EventArgs^  e) {

			 this->buttonWriteFMSCSI->Enabled = false;

			 Int32 count = Int32::Parse(this->textBoxFileMarks->Text);

			 TapeDriveSCSI^ tapeDrive = gcnew TapeDriveSCSI();
			 //String^ tapeName = "\\\\.\\TAPE0";
			 String^ tapeName = this->comboBoxTape->SelectedItem->ToString();
			 UInt32 returnCode = -1;
			 bool res1 = tapeDrive->Open(tapeName, returnCode);
			 if (!res1)
			 {
				 String^ msg = returnCode.ToString() + ": " +(gcnew Win32Exception(returnCode))->Message;
				 MessageBox::Show(msg);
			 }

			 ERROR_SNS_INFO^ snsInfo;

			 res1 = tapeDrive->WriteFileMarks(count,false,returnCode,snsInfo);

			 if (!res1)
			 {
				 String^ msg = returnCode.ToString() + ": " +(gcnew Win32Exception(returnCode))->Message + "\n" 
					 + String::Format("SNS Key: {0:X}, ASC: {1:X}, ASCQ: {2:X}, FRU: {3:X} ",snsInfo->SNSKey, snsInfo->ASC, snsInfo->ASCQ, snsInfo->FRU);
				 MessageBox::Show(msg);
			 }

			 bool res2 = tapeDrive->Close(returnCode);
			 if (!res2)
			 {
				 String^ msg = returnCode.ToString() + ": " +(gcnew Win32Exception(returnCode))->Message;
				 MessageBox::Show(msg);
			 }

			 this->buttonWriteFMSCSI->Enabled = true;

		 }
private: System::Void buttonSetBlkSize_Click(System::Object^  sender, System::EventArgs^  e) {

			 this->buttonSetBlkSize->Enabled = false;

			 UInt32 blkSize = UInt32::Parse(this->textBoxBlkSize->Text);

			 TapeDriveSCSI^ tapeDrive = gcnew TapeDriveSCSI();
			 //String^ tapeName = "\\\\.\\TAPE0";
			 String^ tapeName = this->comboBoxTape->SelectedItem->ToString();
			 UInt32 returnCode = -1;
			 bool res1 = tapeDrive->Open(tapeName, returnCode);
			 if (!res1)
			 {
				 String^ msg = returnCode.ToString() + ": " +(gcnew Win32Exception(returnCode))->Message;
				 MessageBox::Show(msg);
			 }

			 ERROR_SNS_INFO^ snsInfo;

			 //res1 = tapeDrive->SetBlockSizeCDB10(blkSize,returnCode,snsInfo);
			 res1 = tapeDrive->SetBlockSizeCDB6(blkSize,returnCode,snsInfo);

			 if (!res1)
			 {
				 String^ msg = returnCode.ToString() + ": " +(gcnew Win32Exception(returnCode))->Message + "\n" 
					 + String::Format("SNS Key: {0:X}, ASC: {1:X}, ASCQ: {2:X}, FRU: {3:X} ",snsInfo->SNSKey, snsInfo->ASC, snsInfo->ASCQ, snsInfo->FRU);
				 MessageBox::Show(msg);
			 }

			 bool res2 = tapeDrive->Close(returnCode);
			 if (!res2)
			 {
				 String^ msg = returnCode.ToString() + ": " +(gcnew Win32Exception(returnCode))->Message;
				 MessageBox::Show(msg);
			 }

			 this->buttonSetBlkSize->Enabled = true;
		 }
private: System::Void buttonRequestSNS_Click(System::Object^  sender, System::EventArgs^  e) {

			 this->buttonRequestSNS->Enabled = false;

			 UInt32 blkSize = UInt32::Parse(this->textBoxBlkSize->Text);

			 TapeDriveSCSI^ tapeDrive = gcnew TapeDriveSCSI();
			 //String^ tapeName = "\\\\.\\TAPE0";
			 String^ tapeName = this->comboBoxTape->SelectedItem->ToString();
			 UInt32 returnCode = -1;
			 bool res1 = tapeDrive->Open(tapeName, returnCode);
			 if (!res1)
			 {
				 String^ msg = returnCode.ToString() + ": " +(gcnew Win32Exception(returnCode))->Message;
				 MessageBox::Show(msg);
			 }

			 ERROR_SNS_INFO^ snsInfoActual;
			 
			 ERROR_SNS_INFO^ snsInfoHelper;

			 SENSE_DATA snsData;
			 UInt32 senseSize = sizeof(snsData);
			 memset(&snsData,0,senseSize);

			 res1 = tapeDrive->RequestSense(&snsData,0,senseSize,returnCode,snsInfoHelper);

			 if (!res1)
			 {
				 String^ msg = returnCode.ToString() + ": " +(gcnew Win32Exception(returnCode))->Message + "\n" 
					 + String::Format("SNS Key: {0:X}, ASC: {1:X}, ASCQ: {2:X}, FRU: {3:X} ",snsInfoHelper->SNSKey, snsInfoHelper->ASC, snsInfoHelper->ASCQ, snsInfoHelper->FRU);
				 MessageBox::Show(msg);
			 }
			 else
			 {
				 snsInfoActual = tapeDrive->GetSNSInfoFromFixedData(&snsData);
				 String^ msg = String::Format("SNS Key: {0:X}, ASC: {1:X}, ASCQ: {2:X}, FRU: {3:X} ",snsInfoActual->SNSKey, snsInfoActual->ASC, snsInfoActual->ASCQ, snsInfoActual->FRU);
				 MessageBox::Show(msg);

			 }

			 bool res2 = tapeDrive->Close(returnCode);
			 if (!res2)
			 {
				 String^ msg = returnCode.ToString() + ": " +(gcnew Win32Exception(returnCode))->Message;
				 MessageBox::Show(msg);
			 }

			 this->buttonRequestSNS->Enabled = true;

		 }
private: System::Void buttonGetBlkSize_Click(System::Object^  sender, System::EventArgs^  e) {

			 this->buttonGetBlkSize->Enabled = false;

			 UInt32 blkSize = 0;

			 TapeDriveSCSI^ tapeDrive = gcnew TapeDriveSCSI();
			 //String^ tapeName = "\\\\.\\TAPE0";
			 String^ tapeName = this->comboBoxTape->SelectedItem->ToString();
			 UInt32 returnCode = -1;
			 bool res1 = tapeDrive->Open(tapeName, returnCode);
			 if (!res1)
			 {
				 String^ msg = returnCode.ToString() + ": " +(gcnew Win32Exception(returnCode))->Message;
				 MessageBox::Show(msg);
			 }

			 ERROR_SNS_INFO^ snsInfo;

			 res1 = tapeDrive->GetMediaBlockSize(blkSize,returnCode,snsInfo);

			 if (!res1)
			 {
				 String^ msg = returnCode.ToString() + ": " +(gcnew Win32Exception(returnCode))->Message + "\n" 
					 + String::Format("SNS Key: {0:X}, ASC: {1:X}, ASCQ: {2:X}, FRU: {3:X} ",snsInfo->SNSKey, snsInfo->ASC, snsInfo->ASCQ, snsInfo->FRU);
				 MessageBox::Show(msg);
			 }
			 else
			 {
				 String^ msg = String::Format("Block Size: {0}",blkSize);
				 MessageBox::Show(msg);

			 }

			 bool res2 = tapeDrive->Close(returnCode);
			 if (!res2)
			 {
				 String^ msg = returnCode.ToString() + ": " +(gcnew Win32Exception(returnCode))->Message;
				 MessageBox::Show(msg);
			 }

			 this->buttonGetBlkSize->Enabled = true;
		 }
private: System::Void buttonReadSCSI_Click(System::Object^  sender, System::EventArgs^  e) {

			 this->buttonReadSCSI->Enabled = false;


			 UInt32 transferLength = UInt32::Parse(this->textBoxReadSize->Text);

			 TapeDriveSCSI^ tapeDrive = gcnew TapeDriveSCSI();
			 //String^ tapeName = "\\\\.\\TAPE0";
			 String^ tapeName = this->comboBoxTape->SelectedItem->ToString();
			 UInt32 returnCode = -1;
			 bool res1 = tapeDrive->Open(tapeName, returnCode);
			 if (!res1)
			 {
				 String^ msg = returnCode.ToString() + ": " +(gcnew Win32Exception(returnCode))->Message;
				 MessageBox::Show(msg);
			 }

			 ERROR_SNS_INFO^ snsInfo;

			 array<byte>^ buffer;
			 UInt32 bytesTransferred;
			 UInt32 blockSize = 8192;

			 switch(this->comboBoxReadMethod->SelectedIndex)
			 {
			 case 0:
				 //.... bytes
				 buffer = gcnew array<byte>(transferLength);
				 res1 = tapeDrive->ReadVarBlock(buffer,bytesTransferred,returnCode,snsInfo);
				 break;
			 case 1:
				 //.... blocks
				 buffer = gcnew array<byte>(transferLength*blockSize);
				 res1 = tapeDrive->ReadFixedBlocks(buffer,blockSize,transferLength,bytesTransferred,returnCode,snsInfo);
				 break;
			 }

			 if (!res1)
			 {
				 String^ msg = returnCode.ToString() + ": " +(gcnew Win32Exception(returnCode))->Message + "\n" 
					 + String::Format("SNS Key: {0:X}, ASC: {1:X}, ASCQ: {2:X}, FRU: {3:X} ",snsInfo->SNSKey, snsInfo->ASC, snsInfo->ASCQ, snsInfo->FRU);
				 MessageBox::Show(msg);
			 }
			 else
			 {
				 String^ msg = String::Format("Bytes Read: {0}",bytesTransferred);
				 MessageBox::Show(msg);

			 }

			 bool res2 = tapeDrive->Close(returnCode);
			 if (!res2)
			 {
				 String^ msg = returnCode.ToString() + ": " +(gcnew Win32Exception(returnCode))->Message;
				 MessageBox::Show(msg);
			 }

			 this->buttonReadSCSI->Enabled = true;
		 }
private: System::Void buttonWrt1GBSCSI_Click(System::Object^  sender, System::EventArgs^  e) {

			 this->buttonWrt1GBSCSI->Enabled = false;

			 TapeDriveSCSI^ tapeDrive = gcnew TapeDriveSCSI();
			 //String^ tapeName = "\\\\.\\TAPE0";
			 String^ tapeName = this->comboBoxTape->SelectedItem->ToString();
			 UInt32 returnCode = -1;
			 bool res1 = tapeDrive->Open(tapeName, returnCode);
			 if (!res1)
			 {
				 String^ msg = returnCode.ToString() + ": " +(gcnew Win32Exception(returnCode))->Message;
				 MessageBox::Show(msg);
			 }

			 ERROR_SNS_INFO^ snsInfo;

			 array<byte>^ buffer = gcnew array<byte>(65536);

			 pin_ptr<byte> pBuffer = &buffer[0];
			 memset(pBuffer,8,65536);
			 pBuffer = nullptr;
			 for (int j =0; j<65536; j++)
			 {
				 buffer[j]= rand();
			 }

		 	 res1 = tapeDrive->SetBlockSizeCDB6(65536,returnCode,snsInfo);
			 if (!res1)
			 {
				 String^ msg = returnCode.ToString() + ": " +(gcnew Win32Exception(returnCode))->Message + "\n" 
					 + String::Format("SNS Key: {0:X}, ASC: {1:X}, ASCQ: {2:X}, FRU: {3:X} ",snsInfo->SNSKey, snsInfo->ASC, snsInfo->ASCQ, snsInfo->FRU);
				 MessageBox::Show(msg);
			 }


			 UInt32 bytesTransferred = 0;

			 for(int i =0; i< 16384; i++)
			 {

				 res1 = tapeDrive->WriteFixedBlocks(buffer,65536,1,bytesTransferred, returnCode, snsInfo);
				 if (!res1)
				 {
					 String^ msg = returnCode.ToString() + ": " +(gcnew Win32Exception(returnCode))->Message + "\n" 
						 + String::Format("SNS Key: {0:X}, ASC: {1:X}, ASCQ: {2:X}, FRU: {3:X} ",snsInfo->SNSKey, snsInfo->ASC, snsInfo->ASCQ, snsInfo->FRU);
					 MessageBox::Show(msg);
				 }

			 }


			 bool res2 = tapeDrive->Close(returnCode);
			 if (!res2)
			 {
				 String^ msg = returnCode.ToString() + ": " +(gcnew Win32Exception(returnCode))->Message;
				 MessageBox::Show(msg);
			 }
			 this->buttonWrt1GBSCSI->Enabled = true;
		 }
private: System::Void buttonWrtVar_Click(System::Object^  sender, System::EventArgs^  e) {

			 this->buttonWrtVar->Enabled = false;

			 TapeDriveSCSI^ tapeDrive = gcnew TapeDriveSCSI();

			 String^ tapeName = this->comboBoxTape->SelectedItem->ToString();
			 UInt32 returnCode = -1;
			 bool res1 = tapeDrive->Open(tapeName, returnCode);
			 if (!res1)
			 {
				 String^ msg = returnCode.ToString() + ": " +(gcnew Win32Exception(returnCode))->Message;
				 MessageBox::Show(msg);
			 }

			 ERROR_SNS_INFO^ snsInfo;

			 array<byte>^ buffer;// = gcnew array<byte>(65536);

			 //pin_ptr<byte> pBuffer = &buffer[0];
			 //memset(pBuffer,8,65536);
			 //pBuffer = nullptr;
			 /*for (int j =0; j<65536; j++)
			 {
				 buffer[j]= rand();
			 }*/

			 UInt32 blockSize = 0;
			 res1 = tapeDrive->SetBlockSizeCDB6(blockSize,returnCode,snsInfo);
			 if (!res1)
			 {
				 String^ msg = returnCode.ToString() + ": " +(gcnew Win32Exception(returnCode))->Message + "\n" 
					 + String::Format("SNS Key: {0:X}, ASC: {1:X}, ASCQ: {2:X}, FRU: {3:X} ",snsInfo->SNSKey, snsInfo->ASC, snsInfo->ASCQ, snsInfo->FRU);
				 MessageBox::Show(msg);
			 }


			 UInt32 bytesTransferred = 0;

			 Random^ rnd = gcnew Random();


			 for(int i =0; i< 16384; i++)
			 {
				 // Generate buffer
				 blockSize = rnd->Next(1,65536);
				 buffer = gcnew array<byte>(blockSize);
				 rnd->NextBytes(buffer);

				 // write buffer
				 res1 = tapeDrive->WriteVarBlock(buffer,bytesTransferred,returnCode,snsInfo);
				 if (!res1)
				 {
					 String^ msg = returnCode.ToString() + ": " +(gcnew Win32Exception(returnCode))->Message + "\n" 
						 + String::Format("SNS Key: {0:X}, ASC: {1:X}, ASCQ: {2:X}, FRU: {3:X} ",snsInfo->SNSKey, snsInfo->ASC, snsInfo->ASCQ, snsInfo->FRU);
					 MessageBox::Show(msg);
				 }

			 }


			 bool res2 = tapeDrive->Close(returnCode);
			 if (!res2)
			 {
				 String^ msg = returnCode.ToString() + ": " +(gcnew Win32Exception(returnCode))->Message;
				 MessageBox::Show(msg);
			 }

			 this->buttonWrtVar->Enabled = true;


		 }
private: System::Void buttonSNSDcdr_Click(System::Object^  sender, System::EventArgs^  e) {
			 SNSDecoder^ decoder = gcnew SNSDecoder();
			 decoder->ShowDialog();
		 }
private: System::Void buttonWrtTst_Click(System::Object^  sender, System::EventArgs^  e) {
			 WriteTest^ dlg = gcnew WriteTest();
			 dlg->ShowDialog();
		 }
private: System::Void buttonReadPt1_Click(System::Object^  sender, System::EventArgs^  e) {

			 UInt64 blockNumber = 0;
			 UInt64 partNumber = 1;

			 this->buttonReadPt1->Enabled = false;

			 TapeDriveSCSI^ tapeDrive = gcnew TapeDriveSCSI();
			 //String^ tapeName = "\\\\.\\TAPE0";
			 String^ tapeName = this->comboBoxTape->SelectedItem->ToString();
			 UInt32 returnCode = -1;
			 bool res1 = tapeDrive->Open(tapeName, returnCode);
			 if (!res1)
			 {
				 String^ msg = returnCode.ToString() + ": " +(gcnew Win32Exception(returnCode))->Message;
				 MessageBox::Show(msg);
			 }

			 ERROR_SNS_INFO^ snsInfo;

			 //res1 = tapeDrive->LocateCDB16(true,true,partNumber,LogicalObject,blockNumber,returnCode,snsInfo);
			 res1 = tapeDrive->SeekToBOP(false, partNumber, returnCode, snsInfo);

			 if (!res1)
			 {
				 String^ msg = returnCode.ToString() + ": " +(gcnew Win32Exception(returnCode))->Message + "\n" 
					 + String::Format("SNS Key: {0:X}, ASC: {1:X}, ASCQ: {2:X}, FRU: {3:X} ",snsInfo->SNSKey, snsInfo->ASC, snsInfo->ASCQ, snsInfo->FRU);
				 MessageBox::Show(msg);
			 }
			 else{


					 // TODO: Read-write Cycle

					 array<byte>^ buffer;
					 UInt32 bytesTransferred;
					 UInt64 transferLength = 1048576;
					 Int64 currentBlkNumber = -1;
					 UInt32 previousBlkSize = 0;

					//.... bytes
					buffer = gcnew array<byte>(transferLength);

					snsInfo->SNSKey = 0;
					snsInfo->ASC = 0;
					snsInfo->ASCQ= 0;
					snsInfo->FRU = 0;
					bool continueProcessing = true;

					UInt32 fileCounter = 0;
					String^ fileName = "e:\\file" + String::Format("{0:00000000}",fileCounter) + ".bin";
					bool fileOpen = false;

					FileStream^ outputFile;

					StreamWriter^ logFile = gcnew StreamWriter("e:\\log.txt");


					while(continueProcessing){

									currentBlkNumber++;
									res1 = tapeDrive->ReadVarBlock(buffer,bytesTransferred,returnCode,snsInfo);
									


/*									if (!res1)
									{
										String^ msg = returnCode.ToString() + ": " +(gcnew Win32Exception(returnCode))->Message + "\n" 
											+ String::Format("SNS Key: {0:X}, ASC: {1:X}, ASCQ: {2:X}, FRU: {3:X} ",snsInfo->SNSKey, snsInfo->ASC, snsInfo->ASCQ, snsInfo->FRU);
											MessageBox::Show(msg);
											//  TODO: CleanUp

											if(fileOpen)
											{// existing file

												outputFile->Close();
												fileOpen = false;

											}
											logFile->Write(msg);
											previousBlkSize = 0;
											continueProcessing = false;
											continue;
									}*/


									if(snsInfo->SNSKey == 0 && snsInfo->ASC == 0 && snsInfo->ASCQ == 0 /*NORMAL READ*/)
									{
										// TODO
										if(fileOpen)
										{// existing file

											outputFile->Write(buffer,0,bytesTransferred);

										}
										else
										{// new file
											fileName = "e:\\file" + String::Format("{0:00000000}",fileCounter) + ".bin";
											outputFile = gcnew FileStream(fileName, System::IO::FileMode::Create, System::IO::FileAccess::ReadWrite, System::IO::FileShare::Read, 8, System::IO::FileOptions::None );
											fileOpen = true;

											String^ msg = String::Format("New TapeFile: {0} at Block #: {1}",fileName,currentBlkNumber);
											logFile->WriteLine(msg);

											outputFile->Write(buffer,0,bytesTransferred);


										}

										if(previousBlkSize != bytesTransferred)
										{
											String^ msg = String::Format("OfsPBA: {0} BSize: {1}",currentBlkNumber,bytesTransferred);
											logFile->WriteLine(msg);
											previousBlkSize = bytesTransferred;
										}

										continue;
									}
									else if(snsInfo->SNSKey == 0 && snsInfo->ASC == 0 && snsInfo->ASCQ == 1 /*FILE MARK*/)
									{
										// update log, close current file, make preparations for new file, continue looping
										if(fileOpen)
										{// existing file

											outputFile->Close();
											fileOpen = false;
											fileCounter++;

										}
										previousBlkSize = 0;
										String^ msg = String::Format("Filemark at Blk #: {0}",currentBlkNumber);
										logFile->WriteLine(msg);
										continue;
									}
									else if(snsInfo->SNSKey == 8 && snsInfo->ASC == 0 && snsInfo->ASCQ == 5/*EOD*/)
									{
										// TODO - update log, close and save everything then exit
										if(fileOpen)
										{// existing file

											outputFile->Close();
											fileOpen = false;
											//fileCounter++;

										}
										previousBlkSize = 0;



										String^ msg = String::Format("Reached EOD at Blk #: {0}",currentBlkNumber);
										logFile->WriteLine(msg);
										continueProcessing = false;
										continue;
									}
									else // something wrong and unexpected
									{
										if(fileOpen)
										{// existing file

											outputFile->Close();
											fileOpen = false;
											
										}

										previousBlkSize = 0;
										String^ msg = "Return code " + returnCode.ToString() + ": " +(gcnew Win32Exception(returnCode))->Message + "\n" 
										+ String::Format("SNS Key: {0:X}, ASC: {1:X}, ASCQ: {2:X}, FRU: {3:X} ",snsInfo->SNSKey, snsInfo->ASC, snsInfo->ASCQ, snsInfo->FRU);
										MessageBox::Show(msg);
										String^ msg2 = String::Format(" Blk #: {0}", currentBlkNumber);
										logFile->WriteLine("something wrong and unexpected\n" + msg + msg2);
										continueProcessing = false;
										continue;
									}

					
					}
					logFile->Close();

			 }


			 bool res2 = tapeDrive->Close(returnCode);
			 if (!res2)
			 {
				 String^ msg = returnCode.ToString() + ": " +(gcnew Win32Exception(returnCode))->Message;
				 MessageBox::Show(msg);
			 }

			 this->buttonReadPt1->Enabled = true;

		 }
private: System::Void buttonXmlTst_Click(System::Object^  sender, System::EventArgs^  e) {

			 using namespace System::Xml::Serialization;

			 TapeImage^ image = gcnew TapeImage();

//			 image->_cm->_content = gcnew File()
/*
			 List<RangeRecord^>^ lst = gcnew List<RangeRecord^>;

			 for(Int32 i = 0; i<12; i++)
			 {
				 RangeRecord^ rangeRecord = gcnew RangeRecord();
				 rangeRecord->StartBlockNumber = i;
				 rangeRecord->BlockSize = i;
				 rangeRecord->SizeInBlocks = 4294967296 + i;

				 lst->Add(rangeRecord);

			 }


			 XmlSerializer^ ser = gcnew XmlSerializer(lst->GetType());

			 TextWriter^ writer = gcnew StreamWriter("serialization.xml");



			 ser->Serialize( writer, lst );
			 writer->Close();

			 
			 List<RangeRecord^>^ lstnew = gcnew List<RangeRecord^>;
			 TextReader^ reader = gcnew StreamReader("serialization.xml");
			 lstnew = dynamic_cast<List<RangeRecord^>^>(ser->Deserialize( reader ));*/



		 }
private: System::Void button1_Click_2(System::Object^  sender, System::EventArgs^  e) {
			 Xor32^ dlg = gcnew Xor32();
			 dlg->ShowDialog();
		 }
private: System::Void btnChkDmps_Click(System::Object^  sender, System::EventArgs^  e) {
			 CheckDumps^ dlg = gcnew CheckDumps();
			 dlg->ShowDialog();
		 }
};
}

