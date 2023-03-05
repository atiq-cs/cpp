#pragma once


namespace dbTest {

  using namespace System;
  using namespace System::ComponentModel;
  using namespace System::Collections;
  using namespace System::Windows::Forms;
  using namespace System::Data;
  using namespace System::Data::OleDb;
  using namespace System::Drawing;

  /// <summary>
  /// Summary for Form1
  ///
  /// WARNING: If you change the name of this class, you will need to change the
  ///          'Resource File Name' property for the managed resource compiler tool
  ///          associated with all .resx files this class depends on.  Otherwise,
  ///          the designers will not be able to interact properly with localized
  ///          resources associated with this form.
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
  private: System::Windows::Forms::RichTextBox^  richTextBox1;
  protected: 
  private: System::Windows::Forms::Button^  button1;
  private: System::Windows::Forms::Label^  label1;
  private: System::Windows::Forms::Label^  label2;
  private: System::Windows::Forms::Label^  label3;
  private: System::Windows::Forms::Label^  label4;
  private: System::Windows::Forms::Label^  label5;
  private: System::Windows::Forms::Label^  label6;

  private: System::Windows::Forms::RichTextBox^  richTextBox2;
  private: System::Windows::Forms::RichTextBox^  richTextBox3;
  private: System::Windows::Forms::RichTextBox^  richTextBox4;
  private: System::Windows::Forms::RichTextBox^  richTextBox5;
  private: System::Windows::Forms::RichTextBox^  richTextBox6;

  private: System::Windows::Forms::Label^  label8;
  private: System::Windows::Forms::Label^  label9;

  private: System::Windows::Forms::RichTextBox^  richTextBox8;

  private: System::Windows::Forms::Label^  label10;

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
      this->richTextBox1 = (gcnew System::Windows::Forms::RichTextBox());
      this->button1 = (gcnew System::Windows::Forms::Button());
      this->label1 = (gcnew System::Windows::Forms::Label());
      this->label2 = (gcnew System::Windows::Forms::Label());
      this->label3 = (gcnew System::Windows::Forms::Label());
      this->label4 = (gcnew System::Windows::Forms::Label());
      this->label5 = (gcnew System::Windows::Forms::Label());
      this->label6 = (gcnew System::Windows::Forms::Label());
      this->richTextBox2 = (gcnew System::Windows::Forms::RichTextBox());
      this->richTextBox3 = (gcnew System::Windows::Forms::RichTextBox());
      this->richTextBox4 = (gcnew System::Windows::Forms::RichTextBox());
      this->richTextBox5 = (gcnew System::Windows::Forms::RichTextBox());
      this->richTextBox6 = (gcnew System::Windows::Forms::RichTextBox());
      this->label8 = (gcnew System::Windows::Forms::Label());
      this->label9 = (gcnew System::Windows::Forms::Label());
      this->richTextBox8 = (gcnew System::Windows::Forms::RichTextBox());
      this->label10 = (gcnew System::Windows::Forms::Label());
      this->SuspendLayout();
      // 
      // richTextBox1
      // 
      this->richTextBox1->Font = (gcnew System::Drawing::Font(L"Bangla", 14, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
        static_cast<System::Byte>(0)));
      this->richTextBox1->Location = System::Drawing::Point(189, 40);
      this->richTextBox1->Name = L"richTextBox1";
      this->richTextBox1->Size = System::Drawing::Size(327, 27);
      this->richTextBox1->TabIndex = 0;
      this->richTextBox1->Text = L"";
      this->richTextBox1->TextChanged += gcnew System::EventHandler(this, &Form1::richTextBox1_TextChanged);
      // 
      // button1
      // 
      this->button1->Location = System::Drawing::Point(281, 366);
      this->button1->Name = L"button1";
      this->button1->Size = System::Drawing::Size(184, 34);
      this->button1->TabIndex = 7;
      this->button1->Text = L"Add Result to Database";
      this->button1->UseVisualStyleBackColor = true;
      this->button1->Click += gcnew System::EventHandler(this, &Form1::button1_Click);
      // 
      // label1
      // 
      this->label1->Location = System::Drawing::Point(82, 43);
      this->label1->Name = L"label1";
      this->label1->Size = System::Drawing::Size(81, 24);
      this->label1->TabIndex = 2;
      this->label1->Text = L"Word";
      this->label1->Click += gcnew System::EventHandler(this, &Form1::label1_Click);
      // 
      // label2
      // 
      this->label2->Location = System::Drawing::Point(82, 253);
      this->label2->Name = L"label2";
      this->label2->Size = System::Drawing::Size(81, 24);
      this->label2->TabIndex = 3;
      this->label2->Text = L"Meaning in Eng";
      this->label2->Click += gcnew System::EventHandler(this, &Form1::label2_Click);
      // 
      // label3
      // 
      this->label3->Location = System::Drawing::Point(82, 214);
      this->label3->Name = L"label3";
      this->label3->Size = System::Drawing::Size(81, 24);
      this->label3->TabIndex = 4;
      this->label3->Text = L"Use in Bangla";
      this->label3->Click += gcnew System::EventHandler(this, &Form1::label3_Click);
      // 
      // label4
      // 
      this->label4->Location = System::Drawing::Point(82, 169);
      this->label4->Name = L"label4";
      this->label4->Size = System::Drawing::Size(81, 24);
      this->label4->TabIndex = 5;
      this->label4->Text = L"Meaning";
      // 
      // label5
      // 
      this->label5->Location = System::Drawing::Point(82, 132);
      this->label5->Name = L"label5";
      this->label5->Size = System::Drawing::Size(100, 24);
      this->label5->TabIndex = 6;
      this->label5->Text = L"Parts Of Speech";
      // 
      // label6
      // 
      this->label6->Location = System::Drawing::Point(82, 93);
      this->label6->Name = L"label6";
      this->label6->Size = System::Drawing::Size(81, 24);
      this->label6->TabIndex = 7;
      this->label6->Text = L"WordSerial";
      // 
      // richTextBox2
      // 
      this->richTextBox2->Font = (gcnew System::Drawing::Font(L"Bangla", 14, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
        static_cast<System::Byte>(0)));
      this->richTextBox2->Location = System::Drawing::Point(189, 85);
      this->richTextBox2->Name = L"richTextBox2";
      this->richTextBox2->Size = System::Drawing::Size(327, 27);
      this->richTextBox2->TabIndex = 1;
      this->richTextBox2->Text = L"";
      this->richTextBox2->TextChanged += gcnew System::EventHandler(this, &Form1::richTextBox2_TextChanged);
      // 
      // richTextBox3
      // 
      this->richTextBox3->Font = (gcnew System::Drawing::Font(L"Bangla", 14, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
        static_cast<System::Byte>(0)));
      this->richTextBox3->Location = System::Drawing::Point(189, 129);
      this->richTextBox3->Name = L"richTextBox3";
      this->richTextBox3->Size = System::Drawing::Size(327, 27);
      this->richTextBox3->TabIndex = 2;
      this->richTextBox3->Text = L"";
      this->richTextBox3->TextChanged += gcnew System::EventHandler(this, &Form1::richTextBox3_TextChanged);
      // 
      // richTextBox4
      // 
      this->richTextBox4->Font = (gcnew System::Drawing::Font(L"Bangla", 14, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
        static_cast<System::Byte>(0)));
      this->richTextBox4->Location = System::Drawing::Point(189, 169);
      this->richTextBox4->Name = L"richTextBox4";
      this->richTextBox4->Size = System::Drawing::Size(327, 27);
      this->richTextBox4->TabIndex = 3;
      this->richTextBox4->Text = L"";
      this->richTextBox4->TextChanged += gcnew System::EventHandler(this, &Form1::richTextBox4_TextChanged);
      // 
      // richTextBox5
      // 
      this->richTextBox5->Font = (gcnew System::Drawing::Font(L"Bangla", 14, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
        static_cast<System::Byte>(0)));
      this->richTextBox5->Location = System::Drawing::Point(189, 214);
      this->richTextBox5->Name = L"richTextBox5";
      this->richTextBox5->Size = System::Drawing::Size(327, 27);
      this->richTextBox5->TabIndex = 4;
      this->richTextBox5->Text = L"";
      this->richTextBox5->TextChanged += gcnew System::EventHandler(this, &Form1::richTextBox5_TextChanged);
      // 
      // richTextBox6
      // 
      this->richTextBox6->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.5F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
        static_cast<System::Byte>(0)));
      this->richTextBox6->Location = System::Drawing::Point(189, 247);
      this->richTextBox6->Name = L"richTextBox6";
      this->richTextBox6->Size = System::Drawing::Size(327, 27);
      this->richTextBox6->TabIndex = 5;
      this->richTextBox6->Text = L"";
      this->richTextBox6->TextChanged += gcnew System::EventHandler(this, &Form1::richTextBox6_TextChanged);
      // 
      // label8
      // 
      this->label8->Location = System::Drawing::Point(226, 326);
      this->label8->Name = L"label8";
      this->label8->Size = System::Drawing::Size(326, 31);
      this->label8->TabIndex = 15;
      this->label8->Text = L"Query Status";
      // 
      // label9
      // 
      this->label9->Location = System::Drawing::Point(32, 429);
      this->label9->Name = L"label9";
      this->label9->Size = System::Drawing::Size(725, 64);
      this->label9->TabIndex = 16;
      this->label9->Text = L"SQL Query";
      // 
      // richTextBox8
      // 
      this->richTextBox8->Font = (gcnew System::Drawing::Font(L"Bangla", 14, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
        static_cast<System::Byte>(0)));
      this->richTextBox8->Location = System::Drawing::Point(556, 206);
      this->richTextBox8->Name = L"richTextBox8";
      this->richTextBox8->Size = System::Drawing::Size(201, 58);
      this->richTextBox8->TabIndex = 18;
      this->richTextBox8->Text = L"";
      this->richTextBox8->TextChanged += gcnew System::EventHandler(this, &Form1::richTextBox8_TextChanged);
      // 
      // label10
      // 
      this->label10->Location = System::Drawing::Point(553, 165);
      this->label10->Name = L"label10";
      this->label10->Size = System::Drawing::Size(185, 28);
      this->label10->TabIndex = 20;
      this->label10->Text = L"Anotonym";
      // 
      // Form1
      // 
      this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
      this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
      this->ClientSize = System::Drawing::Size(786, 502);
      this->Controls->Add(this->label10);
      this->Controls->Add(this->richTextBox8);
      this->Controls->Add(this->label9);
      this->Controls->Add(this->label8);
      this->Controls->Add(this->richTextBox6);
      this->Controls->Add(this->richTextBox5);
      this->Controls->Add(this->richTextBox4);
      this->Controls->Add(this->richTextBox3);
      this->Controls->Add(this->richTextBox2);
      this->Controls->Add(this->label6);
      this->Controls->Add(this->label5);
      this->Controls->Add(this->label4);
      this->Controls->Add(this->label3);
      this->Controls->Add(this->label2);
      this->Controls->Add(this->label1);
      this->Controls->Add(this->button1);
      this->Controls->Add(this->richTextBox1);
      this->Name = L"Form1";
      this->Text = L"Form1";
      this->Load += gcnew System::EventHandler(this, &Form1::Form1_Load);
      this->ResumeLayout(false);
    }

#pragma endregion
  private: System::Void richTextBox1_TextChanged(System::Object^  sender, System::EventArgs^  e) {
         label8->Text = "";
       }
  private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
        String^ myConnectionString = gcnew String(L"Provider=Microsoft.ACE.OLEDB.12.0;Data Source=H:\\Sourcecodes\\Win32\\CLR\\Db\\bdict.accdb;Persist Security Info=False;");
        OleDbConnection^ myConnection = gcnew OleDbConnection(myConnectionString);
        String^ myInsertQuery = String::Concat("INSERT INTO b2e (WordAlias, WordSerial, \
          PartsOfSpeech, Meaning, UseInSentence, EngMeaning, Antonym) Values\
          ('", richTextBox1->Text, "', '", richTextBox2->Text, "', '", richTextBox3->Text,\
          "', '", richTextBox4->Text, "', '", richTextBox5->Text, "', '", richTextBox6->Text,\
           "', '", richTextBox8->Text,"')");
        label9->Text = String::Concat("Actual query: ", myInsertQuery);
        OleDbCommand^ myCommand = gcnew OleDbCommand(myInsertQuery);
        myCommand->Connection = myConnection;
        myConnection->Open();
        myCommand->ExecuteNonQuery();
        myCommand->Connection->Close();
        label8->Text = L"Data inserted into database successfully.";
       }
  private: System::Void label1_Click(System::Object^  sender, System::EventArgs^  e) {
       }
  private: System::Void richTextBox2_TextChanged(System::Object^  sender, System::EventArgs^  e) {
       }
  private: System::Void richTextBox3_TextChanged(System::Object^  sender, System::EventArgs^  e) {
       }
  private: System::Void richTextBox4_TextChanged(System::Object^  sender, System::EventArgs^  e) {
         label8->Text = "";
       }
  private: System::Void label3_Click(System::Object^  sender, System::EventArgs^  e) {
       }
  private: System::Void richTextBox5_TextChanged(System::Object^  sender, System::EventArgs^  e) {
       }
  private: System::Void richTextBox7_TextChanged(System::Object^  sender, System::EventArgs^  e) {
       }
  private: System::Void richTextBox6_TextChanged(System::Object^  sender, System::EventArgs^  e) {
       }
private: System::Void label2_Click(System::Object^  sender, System::EventArgs^  e) {
     }
private: System::Void Form1_Load(System::Object^  sender, System::EventArgs^  e) {
     }
private: System::Void label7_Click(System::Object^  sender, System::EventArgs^  e) {
     }
private: System::Void label7_Click_1(System::Object^  sender, System::EventArgs^  e) {
     }
private: System::Void richTextBox7_TextChanged_1(System::Object^  sender, System::EventArgs^  e) {
     }
private: System::Void richTextBox8_TextChanged(System::Object^  sender, System::EventArgs^  e) {
     }
};
}

