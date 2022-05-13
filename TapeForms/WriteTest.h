#pragma once
//#using <System.DLL>
//#using <System.Drawing.DLL>
//#using <System.Windows.Forms.DLL>

namespace TapeForms {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Timers;
	using namespace System::Threading;
	using namespace System::IO;

	public enum GUIUpdateOperation
	{
		TimerElapsedStart = 0,
		TimerElapsedStop = 1,
		LogUpdate = 2,
		ElapsedUpdate = 3,
		BytesWrittenUpdate = 4,
		SpeedUpdate = 5,
	};

	/// <summary>
	/// Summary for WriteTest
	/// </summary>
	public ref class WriteTest : public System::Windows::Forms::Form
	{
	public:
		WriteTest(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
			this->comboBoxLvl->SelectedIndex = 3;
			this->comboBoxWrtBlkSize->SelectedIndex = 1;
			this->buttonWrtCancel->Enabled = false;		
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~WriteTest()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::ComponentModel::BackgroundWorker^  backgroundWorker;
	private: System::Windows::Forms::Button^  buttonWrtStart;
	private: System::Windows::Forms::Button^  buttonWrtCancel;
	private: System::Windows::Forms::FolderBrowserDialog^  folderBrowserDialog;

	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::TextBox^  textBoxDestinationFolder;
	private: System::Windows::Forms::Button^  buttonBrowseDestFolder;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::TextBox^  textBoxMaxFileSize;
	private: System::Windows::Forms::ComboBox^  comboBoxLvl;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::TextBox^  textBoxWrtBlkSize;
	private: System::Windows::Forms::ComboBox^  comboBoxWrtBlkSize;
	private: System::Windows::Forms::RichTextBox^  richTextBoxWrtTstLog;
	private: System::Windows::Forms::StatusStrip^  statusStripPorgress;
	private: System::Windows::Forms::ToolStripStatusLabel^  toolStripStatusLabelElapsed;

	private: System::Windows::Forms::ToolStripStatusLabel^  toolStripStatusLabelBytesWritten;
	private: System::Windows::Forms::ToolStripStatusLabel^  toolStripStatusLabelSpeed;
	private: System::Timers::Timer^  timerElapsedUpdate;
	private: System::Timers::Timer^  timerOperational;
	
	private: System::TimeSpan^ elapsedTime;
	private: System::DateTime operationStarted;
	private: float processingSpeed;
	private: Int64 dataProcessed;
	
	private: DateTime lastCheckpointDateTime;
	private: Int64 lastCheckpointDataPorcessed;


	private: Int64 maxFileSize;
	private: Int64 wrtBlkSize;

	private: System::IO::FileStream^ fStream;


	private: System::ComponentModel::IContainer^  components;
	protected: 

	protected: 

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->backgroundWorker = (gcnew System::ComponentModel::BackgroundWorker());
			this->buttonWrtStart = (gcnew System::Windows::Forms::Button());
			this->buttonWrtCancel = (gcnew System::Windows::Forms::Button());
			this->folderBrowserDialog = (gcnew System::Windows::Forms::FolderBrowserDialog());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->textBoxDestinationFolder = (gcnew System::Windows::Forms::TextBox());
			this->buttonBrowseDestFolder = (gcnew System::Windows::Forms::Button());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->textBoxMaxFileSize = (gcnew System::Windows::Forms::TextBox());
			this->comboBoxLvl = (gcnew System::Windows::Forms::ComboBox());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->textBoxWrtBlkSize = (gcnew System::Windows::Forms::TextBox());
			this->comboBoxWrtBlkSize = (gcnew System::Windows::Forms::ComboBox());
			this->richTextBoxWrtTstLog = (gcnew System::Windows::Forms::RichTextBox());
			this->statusStripPorgress = (gcnew System::Windows::Forms::StatusStrip());
			this->toolStripStatusLabelElapsed = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->toolStripStatusLabelBytesWritten = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->toolStripStatusLabelSpeed = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->timerElapsedUpdate = (gcnew System::Timers::Timer());
			this->timerOperational = (gcnew System::Timers::Timer());
			this->statusStripPorgress->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->timerElapsedUpdate))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->timerOperational))->BeginInit();
			this->SuspendLayout();
			// 
			// backgroundWorker
			// 
			this->backgroundWorker->WorkerReportsProgress = true;
			this->backgroundWorker->WorkerSupportsCancellation = true;
			this->backgroundWorker->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &WriteTest::backgroundWorker_DoWork);
			this->backgroundWorker->ProgressChanged += gcnew System::ComponentModel::ProgressChangedEventHandler(this, &WriteTest::backgroundWorker_ProgressChanged);
			this->backgroundWorker->RunWorkerCompleted += gcnew System::ComponentModel::RunWorkerCompletedEventHandler(this, &WriteTest::backgroundWorker_RunWorkerCompleted);
			// 
			// buttonWrtStart
			// 
			this->buttonWrtStart->Location = System::Drawing::Point(301, 69);
			this->buttonWrtStart->Name = L"buttonWrtStart";
			this->buttonWrtStart->Size = System::Drawing::Size(75, 23);
			this->buttonWrtStart->TabIndex = 0;
			this->buttonWrtStart->Text = L"Run";
			this->buttonWrtStart->UseVisualStyleBackColor = true;
			this->buttonWrtStart->Click += gcnew System::EventHandler(this, &WriteTest::buttonWrtStart_Click);
			// 
			// buttonWrtCancel
			// 
			this->buttonWrtCancel->Location = System::Drawing::Point(413, 69);
			this->buttonWrtCancel->Name = L"buttonWrtCancel";
			this->buttonWrtCancel->Size = System::Drawing::Size(75, 23);
			this->buttonWrtCancel->TabIndex = 1;
			this->buttonWrtCancel->Text = L"Cancel";
			this->buttonWrtCancel->UseVisualStyleBackColor = true;
			this->buttonWrtCancel->Click += gcnew System::EventHandler(this, &WriteTest::buttonWrtCancel_Click);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(13, 13);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(95, 13);
			this->label1->TabIndex = 2;
			this->label1->Text = L"Destination Folder:";
			// 
			// textBoxDestinationFolder
			// 
			this->textBoxDestinationFolder->Location = System::Drawing::Point(115, 13);
			this->textBoxDestinationFolder->Name = L"textBoxDestinationFolder";
			this->textBoxDestinationFolder->Size = System::Drawing::Size(312, 20);
			this->textBoxDestinationFolder->TabIndex = 3;
			this->textBoxDestinationFolder->Text = L"D:\\";
			// 
			// buttonBrowseDestFolder
			// 
			this->buttonBrowseDestFolder->Location = System::Drawing::Point(454, 11);
			this->buttonBrowseDestFolder->Name = L"buttonBrowseDestFolder";
			this->buttonBrowseDestFolder->Size = System::Drawing::Size(75, 23);
			this->buttonBrowseDestFolder->TabIndex = 4;
			this->buttonBrowseDestFolder->Text = L"Browse";
			this->buttonBrowseDestFolder->UseVisualStyleBackColor = true;
			this->buttonBrowseDestFolder->Click += gcnew System::EventHandler(this, &WriteTest::buttonBrowseDestFolder_Click);
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(16, 57);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(72, 13);
			this->label2->TabIndex = 5;
			this->label2->Text = L"Max File Size:";
			// 
			// textBoxMaxFileSize
			// 
			this->textBoxMaxFileSize->Location = System::Drawing::Point(115, 49);
			this->textBoxMaxFileSize->Name = L"textBoxMaxFileSize";
			this->textBoxMaxFileSize->Size = System::Drawing::Size(80, 20);
			this->textBoxMaxFileSize->TabIndex = 6;
			this->textBoxMaxFileSize->Text = L"200";
			// 
			// comboBoxLvl
			// 
			this->comboBoxLvl->FormattingEnabled = true;
			this->comboBoxLvl->Items->AddRange(gcnew cli::array< System::Object^  >(5) {L"B", L"KB", L"MB", L"GB", L"TB"});
			this->comboBoxLvl->Location = System::Drawing::Point(219, 47);
			this->comboBoxLvl->Name = L"comboBoxLvl";
			this->comboBoxLvl->Size = System::Drawing::Size(60, 21);
			this->comboBoxLvl->TabIndex = 7;
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(16, 89);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(88, 13);
			this->label3->TabIndex = 8;
			this->label3->Text = L"Write Block Size:";
			// 
			// textBoxWrtBlkSize
			// 
			this->textBoxWrtBlkSize->Location = System::Drawing::Point(115, 86);
			this->textBoxWrtBlkSize->Name = L"textBoxWrtBlkSize";
			this->textBoxWrtBlkSize->Size = System::Drawing::Size(80, 20);
			this->textBoxWrtBlkSize->TabIndex = 9;
			this->textBoxWrtBlkSize->Text = L"64";
			// 
			// comboBoxWrtBlkSize
			// 
			this->comboBoxWrtBlkSize->FormattingEnabled = true;
			this->comboBoxWrtBlkSize->Items->AddRange(gcnew cli::array< System::Object^  >(5) {L"B", L"KB", L"MB", L"GB", L"TB"});
			this->comboBoxWrtBlkSize->Location = System::Drawing::Point(219, 85);
			this->comboBoxWrtBlkSize->Name = L"comboBoxWrtBlkSize";
			this->comboBoxWrtBlkSize->Size = System::Drawing::Size(60, 21);
			this->comboBoxWrtBlkSize->TabIndex = 10;
			// 
			// richTextBoxWrtTstLog
			// 
			this->richTextBoxWrtTstLog->Location = System::Drawing::Point(19, 138);
			this->richTextBoxWrtTstLog->Name = L"richTextBoxWrtTstLog";
			this->richTextBoxWrtTstLog->Size = System::Drawing::Size(500, 96);
			this->richTextBoxWrtTstLog->TabIndex = 11;
			this->richTextBoxWrtTstLog->Text = L"";
			// 
			// statusStripPorgress
			// 
			this->statusStripPorgress->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {this->toolStripStatusLabelElapsed, 
				this->toolStripStatusLabelBytesWritten, this->toolStripStatusLabelSpeed});
			this->statusStripPorgress->Location = System::Drawing::Point(0, 292);
			this->statusStripPorgress->Name = L"statusStripPorgress";
			this->statusStripPorgress->Size = System::Drawing::Size(553, 22);
			this->statusStripPorgress->TabIndex = 12;
			this->statusStripPorgress->Text = L"statusStrip1";
			// 
			// toolStripStatusLabelElapsed
			// 
			this->toolStripStatusLabelElapsed->BorderSides = static_cast<System::Windows::Forms::ToolStripStatusLabelBorderSides>((((System::Windows::Forms::ToolStripStatusLabelBorderSides::Left | System::Windows::Forms::ToolStripStatusLabelBorderSides::Top) 
				| System::Windows::Forms::ToolStripStatusLabelBorderSides::Right) 
				| System::Windows::Forms::ToolStripStatusLabelBorderSides::Bottom));
			this->toolStripStatusLabelElapsed->BorderStyle = System::Windows::Forms::Border3DStyle::Sunken;
			this->toolStripStatusLabelElapsed->Name = L"toolStripStatusLabelElapsed";
			this->toolStripStatusLabelElapsed->Size = System::Drawing::Size(179, 17);
			this->toolStripStatusLabelElapsed->Spring = true;
			// 
			// toolStripStatusLabelBytesWritten
			// 
			this->toolStripStatusLabelBytesWritten->BorderSides = static_cast<System::Windows::Forms::ToolStripStatusLabelBorderSides>((((System::Windows::Forms::ToolStripStatusLabelBorderSides::Left | System::Windows::Forms::ToolStripStatusLabelBorderSides::Top) 
				| System::Windows::Forms::ToolStripStatusLabelBorderSides::Right) 
				| System::Windows::Forms::ToolStripStatusLabelBorderSides::Bottom));
			this->toolStripStatusLabelBytesWritten->BorderStyle = System::Windows::Forms::Border3DStyle::Sunken;
			this->toolStripStatusLabelBytesWritten->Name = L"toolStripStatusLabelBytesWritten";
			this->toolStripStatusLabelBytesWritten->Size = System::Drawing::Size(179, 17);
			this->toolStripStatusLabelBytesWritten->Spring = true;
			// 
			// toolStripStatusLabelSpeed
			// 
			this->toolStripStatusLabelSpeed->BorderSides = static_cast<System::Windows::Forms::ToolStripStatusLabelBorderSides>((((System::Windows::Forms::ToolStripStatusLabelBorderSides::Left | System::Windows::Forms::ToolStripStatusLabelBorderSides::Top) 
				| System::Windows::Forms::ToolStripStatusLabelBorderSides::Right) 
				| System::Windows::Forms::ToolStripStatusLabelBorderSides::Bottom));
			this->toolStripStatusLabelSpeed->BorderStyle = System::Windows::Forms::Border3DStyle::Sunken;
			this->toolStripStatusLabelSpeed->Name = L"toolStripStatusLabelSpeed";
			this->toolStripStatusLabelSpeed->Size = System::Drawing::Size(179, 17);
			this->toolStripStatusLabelSpeed->Spring = true;
			// 
			// timerElapsedUpdate
			// 
			this->timerElapsedUpdate->Interval = 1000;
			this->timerElapsedUpdate->SynchronizingObject = this;
			this->timerElapsedUpdate->Elapsed += gcnew System::Timers::ElapsedEventHandler(this, &WriteTest::timerElapsedUpdate_Elapsed);
			// 
			// timerOperational
			// 
			this->timerOperational->Interval = 60000;
			this->timerOperational->SynchronizingObject = this;
			this->timerOperational->Elapsed += gcnew System::Timers::ElapsedEventHandler(this, &WriteTest::timerOperational_Elapsed);
			// 
			// WriteTest
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(553, 314);
			this->Controls->Add(this->statusStripPorgress);
			this->Controls->Add(this->richTextBoxWrtTstLog);
			this->Controls->Add(this->comboBoxWrtBlkSize);
			this->Controls->Add(this->textBoxWrtBlkSize);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->comboBoxLvl);
			this->Controls->Add(this->textBoxMaxFileSize);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->buttonBrowseDestFolder);
			this->Controls->Add(this->textBoxDestinationFolder);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->buttonWrtCancel);
			this->Controls->Add(this->buttonWrtStart);
			this->Name = L"WriteTest";
			this->Text = L"WriteTest";
			this->statusStripPorgress->ResumeLayout(false);
			this->statusStripPorgress->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->timerElapsedUpdate))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->timerOperational))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void timerElapsedUpdate_Elapsed(System::Object^  sender, System::Timers::ElapsedEventArgs^  e) {

				 DateTime current = DateTime::Now;
				 elapsedTime = System::TimeSpan::FromTicks(current.Ticks - operationStarted.Ticks);
				 //dataProcessed is updated from WorkingThread - we do not touch it here
				 processingSpeed = ((float)(dataProcessed) / (float)(elapsedTime->TotalSeconds));

				 // update GUI:
				 this->toolStripStatusLabelElapsed->Text = String::Format("Elapsed: {0:dd\\.hh\\:mm\\:ss}",elapsedTime);
				 this->toolStripStatusLabelBytesWritten->Text = String::Format("Bytes Written: {0:#,#}",dataProcessed);
				 this->toolStripStatusLabelSpeed->Text = String::Format("Speed: {0:#,#0.##} Bytes/Sec",processingSpeed);

			 }
private: System::Void backgroundWorker_ProgressChanged(System::Object^  sender, System::ComponentModel::ProgressChangedEventArgs^  e) {

			int operationType = e->ProgressPercentage;

            switch (operationType)
            {
				case (int)GUIUpdateOperation::TimerElapsedStart:
					this->elapsedTime = gcnew System::TimeSpan(0);
					this->operationStarted = DateTime::Now;
					this->timerOperational->Start();
					this->timerElapsedUpdate->Start();
					break;
				case (int)GUIUpdateOperation::TimerElapsedStop:
					this->timerOperational->Stop();
					this->timerElapsedUpdate->Stop();
					break;
				/*case (int) GUIUpdateOperation::ElapsedUpdate:
					Time	//TODO:
						break;*/
				case (int)GUIUpdateOperation::BytesWrittenUpdate:
					//this->toolStripStatusLabelBytesWritten->Text = ((Int64)(e->UserState)).ToString();
					this->dataProcessed = (Int64)(e->UserState);
					break;
				/*case (int)GUIUpdateOperation::SpeedUpdate:
						//TODO:
						break;*/
				case (int)GUIUpdateOperation::LogUpdate:
						//TODO:
						break;
				default:
						//TODO:
						break;
		 }
}

private: System::Void buttonBrowseDestFolder_Click(System::Object^  sender, System::EventArgs^  e) {

			 this->folderBrowserDialog->SelectedPath = this->textBoxDestinationFolder->Text;

			 if(folderBrowserDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK)
			 {
				this->textBoxDestinationFolder->Text = this->folderBrowserDialog->SelectedPath;
			 }
		 }
private: System::Void buttonWrtStart_Click(System::Object^  sender, System::EventArgs^  e) {
			 //disable gui
			 this->comboBoxLvl->Enabled = false;
			 this->comboBoxWrtBlkSize->Enabled = false;

			 this->buttonBrowseDestFolder->Enabled = false;
			 this->buttonWrtStart->Enabled = false;

			 //this->richTextBoxWrtTstLog->Enabled = false;
			 
			 this->textBoxDestinationFolder->Enabled = false;
			 this->textBoxMaxFileSize->Enabled = false;
			 this->textBoxWrtBlkSize->Enabled = false;

			 //enable cancel button
			 this->buttonWrtCancel->Enabled = true;

			 // retrieve and initialize all the required data
			 dataProcessed = 0;
			 elapsedTime = gcnew TimeSpan(0);
			 operationStarted = DateTime::Now;
			 processingSpeed = 0;
			 dataProcessed = 0;

			lastCheckpointDateTime = operationStarted;
			lastCheckpointDataPorcessed = dataProcessed;

			 // retrieve writing parameters
			 Int64 sizeBase = Int64::Parse(this->textBoxMaxFileSize->Text);
			 Int64 magnitude = Math::Pow(1024,comboBoxLvl->SelectedIndex);
			 maxFileSize = sizeBase * magnitude;

			 this->richTextBoxWrtTstLog->AppendText("Write Speed Test Started!\n");
			 this->richTextBoxWrtTstLog->AppendText(String::Format("File Size: {0} {1}\n",sizeBase,comboBoxLvl->Text));


			 sizeBase = Int64::Parse(this->textBoxWrtBlkSize->Text);
			 magnitude = Math::Pow(1024,comboBoxWrtBlkSize->SelectedIndex);
			 wrtBlkSize = sizeBase * magnitude;

			 this->richTextBoxWrtTstLog->AppendText(String::Format("Block Size: {0} {1}\n",sizeBase,comboBoxWrtBlkSize->Text));

			 String^ fileName = this->textBoxDestinationFolder->Text + "\\temp.bin";

			 Int32 bufferSize = 8;

			 
			 //fStream = gcnew FileStream(fileName, System::IO::FileMode::Create, System::IO::FileAccess::ReadWrite, System::IO::FileShare::Read, bufferSize, System::IO::FileOptions::WriteThrough );
			 fStream = gcnew FileStream(fileName, System::IO::FileMode::Create, System::IO::FileAccess::ReadWrite, System::IO::FileShare::Read, bufferSize, System::IO::FileOptions::None );
			 //fStream = gcnew FileStream(fileName, System::IO::FileMode::Create, System::IO::FileAccess::ReadWrite, System::IO::FileShare::Read, bufferSize, System::IO::FileOptions::SequentialScan );

			 fStream->SetLength(maxFileSize);


			 backgroundWorker->RunWorkerAsync();
 			 
		 }
private: System::Void buttonWrtCancel_Click(System::Object^  sender, System::EventArgs^  e) {

			 if (MessageBox::Show("Cancel currently running operation?", "Cancellation request", MessageBoxButtons::YesNo, MessageBoxIcon::Stop) == System::Windows::Forms::DialogResult::Yes)
			 {
				backgroundWorker->CancelAsync();
			 }

		 }
private: System::Void backgroundWorker_RunWorkerCompleted(System::Object^  sender, System::ComponentModel::RunWorkerCompletedEventArgs^  e) {

				this->timerOperational->Stop();
				this->timerElapsedUpdate->Stop();

				
				fStream->SetLength(fStream->Position);
				fStream->Close();
				 // First, handle the case where an exception was thrown.
				 if ( e->Error != nullptr )
				 {
//					 MessageBox::Show( e->Error->Message );
					 this->richTextBoxWrtTstLog->AppendText("Operation Completed with Error\n");
				 }
				 else
					 if ( e->Cancelled )
					 {
						 // Next, handle the case where the user canceled 
						 // the operation.
						 // Note that due to a race condition in 
						 // the DoWork event handler, the Cancelled
						 // flag may not have been set, even though
						 // CancelAsync was called.
						 this->richTextBoxWrtTstLog->AppendText("Operation has been Cancelled\n");

					 }
					 else
					 {
						 // Finally, handle the case where the operation 
						 // succeeded.
						 this->richTextBoxWrtTstLog->AppendText("Operation Completed Successfully\n");

					 }

					 //Enable GUI
					 this->comboBoxLvl->Enabled = true;
					 this->comboBoxWrtBlkSize->Enabled = true;

					 this->buttonBrowseDestFolder->Enabled = true;
					 this->buttonWrtStart->Enabled = true;

					 //this->richTextBoxWrtTstLog->Enabled = true;

					 this->textBoxDestinationFolder->Enabled = true;
					 this->textBoxMaxFileSize->Enabled = true;
					 this->textBoxWrtBlkSize->Enabled = true;

					 //Disable cancel button
					 this->buttonWrtCancel->Enabled = false;
				 }
private: System::Void backgroundWorker_DoWork(System::Object^  sender, System::ComponentModel::DoWorkEventArgs^  e) {

			 Int64 dataProcessedLocal = 0;
			 array<Byte>^ buffer = gcnew array<Byte>(this->wrtBlkSize);
			 Int32 writeSize = this->wrtBlkSize;

			 Random^ rnd = gcnew Random();

			 rnd->NextBytes(buffer);

			 backgroundWorker->ReportProgress(GUIUpdateOperation::TimerElapsedStart,nullptr);

			 while ( dataProcessedLocal < this->maxFileSize )
			 {
				 if(backgroundWorker->CancellationPending)
				 {
					 e->Cancel = true;
					 break;
				 }

				 if( (dataProcessedLocal + writeSize) > this->maxFileSize)
				 {
					 writeSize = maxFileSize - dataProcessedLocal;
				 }

				 fStream->Write(buffer,0, writeSize);

				 dataProcessedLocal += writeSize;

				 backgroundWorker->ReportProgress(GUIUpdateOperation::BytesWrittenUpdate,dataProcessedLocal);
				
			 }
		 }
private: System::Void timerOperational_Elapsed(System::Object^  sender, System::Timers::ElapsedEventArgs^  e) {

			 //dataProcessed is updated from WorkingThread - we do not touch it here
			 // make a snapshot of state:
			 DateTime currentTime = DateTime::Now;
			 Int64 currentDataProcessed = dataProcessed;

			 // duration:
			 TimeSpan^ duration = currentTime.Subtract(lastCheckpointDateTime);

			 // data difference:
			 float dataDifference = (float)(currentDataProcessed - lastCheckpointDataPorcessed);

			 // now we can calculate last speed:
			 float currentProcessingSpeed = dataDifference / (float)(duration->TotalSeconds);

			 // update GUI:

			 String^ msg = String::Format("Checkpoint: Data Written: {0:#,#}; Current Speed {1:#,#0.##} Bytes/Sec\n",currentDataProcessed,currentProcessingSpeed);
			 this->richTextBoxWrtTstLog->AppendText(msg);
			  this->richTextBoxWrtTstLog->ScrollToCaret();

			 lastCheckpointDataPorcessed = currentDataProcessed;
			 lastCheckpointDateTime = currentTime;

		 }
};
}
