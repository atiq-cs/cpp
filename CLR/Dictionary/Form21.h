#pragma once

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;
using namespace System::Data::OleDb;

namespace dbDictQuery {

  /// <summary>
  /// Summary for Form2
  ///
  /// WARNING: If you change the name of this class, you will need to change the
  ///          'Resource File Name' property for the managed resource compiler tool
  ///          associated with all .resx files this class depends on.  Otherwise,
  ///          the designers will not be able to interact properly with localized
  ///          resources associated with this form.
  /// </summary>

  public ref class Form2 : public System::Windows::Forms::Form
  {
  public:
    Form2(void)
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
    ~Form2()
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


  private: System::Windows::Forms::Label^  label8;




  private: System::Windows::Forms::Label^  label10;
  private: System::Windows::Forms::RichTextBox^  richTextBox7;
  private: System::Windows::Forms::RichTextBox^  richTextBox9;
  private: System::Windows::Forms::TextBox^  textBox1;
  private: System::Windows::Forms::TextBox^  textBox2;
  private: System::Windows::Forms::Label^  label7;
  private: System::Windows::Forms::Label^  label11;
  private: System::Windows::Forms::RichTextBox^  richTextBox6;


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
      this->label8 = (gcnew System::Windows::Forms::Label());
      this->label10 = (gcnew System::Windows::Forms::Label());
      this->richTextBox7 = (gcnew System::Windows::Forms::RichTextBox());
      this->richTextBox9 = (gcnew System::Windows::Forms::RichTextBox());
      this->textBox1 = (gcnew System::Windows::Forms::TextBox());
      this->textBox2 = (gcnew System::Windows::Forms::TextBox());
      this->label7 = (gcnew System::Windows::Forms::Label());
      this->label11 = (gcnew System::Windows::Forms::Label());
      this->richTextBox6 = (gcnew System::Windows::Forms::RichTextBox());
      this->SuspendLayout();
      // 
      // richTextBox1
      // 
      this->richTextBox1->Font = (gcnew System::Drawing::Font(L"Bangla", 14, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
        static_cast<System::Byte>(0)));
      this->richTextBox1->Location = System::Drawing::Point(129, 27);
      this->richTextBox1->Multiline = false;
      this->richTextBox1->Name = L"richTextBox1";
      this->richTextBox1->Size = System::Drawing::Size(324, 27);
      this->richTextBox1->TabIndex = 0;
      this->richTextBox1->Text = L"";
      this->richTextBox1->TextChanged += gcnew System::EventHandler(this, &Form2::richTextBox1_TextChanged);
      // 
      // button1
      // 
      this->button1->Location = System::Drawing::Point(281, 385);
      this->button1->Name = L"button1";
      this->button1->Size = System::Drawing::Size(184, 34);
      this->button1->TabIndex = 9;
      this->button1->Text = L"Add Result to Database";
      this->button1->UseVisualStyleBackColor = true;
      this->button1->Click += gcnew System::EventHandler(this, &Form2::button1_Click);
      // 
      // label1
      // 
      this->label1->ForeColor = System::Drawing::Color::Silver;
      this->label1->Location = System::Drawing::Point(41, 29);
      this->label1->Name = L"label1";
      this->label1->Size = System::Drawing::Size(81, 24);
      this->label1->TabIndex = 2;
      this->label1->Text = L"Word";
      // 
      // label2
      // 
      this->label2->ForeColor = System::Drawing::Color::Silver;
      this->label2->Location = System::Drawing::Point(32, 310);
      this->label2->Name = L"label2";
      this->label2->Size = System::Drawing::Size(81, 24);
      this->label2->TabIndex = 3;
      this->label2->Text = L"Meaning in Eng";
      // 
      // label3
      // 
      this->label3->ForeColor = System::Drawing::Color::Silver;
      this->label3->Location = System::Drawing::Point(32, 235);
      this->label3->Name = L"label3";
      this->label3->Size = System::Drawing::Size(81, 24);
      this->label3->TabIndex = 4;
      this->label3->Text = L"Use in Bangla";
      // 
      // label4
      // 
      this->label4->ForeColor = System::Drawing::Color::Silver;
      this->label4->Location = System::Drawing::Point(35, 178);
      this->label4->Name = L"label4";
      this->label4->Size = System::Drawing::Size(87, 31);
      this->label4->TabIndex = 5;
      this->label4->Text = L"Bangla Meaning and Desc";
      // 
      // label5
      // 
      this->label5->ForeColor = System::Drawing::Color::Silver;
      this->label5->Location = System::Drawing::Point(37, 100);
      this->label5->Name = L"label5";
      this->label5->Size = System::Drawing::Size(100, 24);
      this->label5->TabIndex = 6;
      this->label5->Text = L"Parts Of Speech";
      // 
      // label6
      // 
      this->label6->ForeColor = System::Drawing::Color::Silver;
      this->label6->Location = System::Drawing::Point(39, 64);
      this->label6->Name = L"label6";
      this->label6->Size = System::Drawing::Size(81, 24);
      this->label6->TabIndex = 7;
      this->label6->Text = L"WordSerial";
      // 
      // richTextBox2
      // 
      this->richTextBox2->Font = (gcnew System::Drawing::Font(L"Bangla", 12));
      this->richTextBox2->Location = System::Drawing::Point(129, 60);
      this->richTextBox2->Multiline = false;
      this->richTextBox2->Name = L"richTextBox2";
      this->richTextBox2->Size = System::Drawing::Size(324, 27);
      this->richTextBox2->TabIndex = 1;
      this->richTextBox2->Text = L"";
      // 
      // richTextBox3
      // 
      this->richTextBox3->Font = (gcnew System::Drawing::Font(L"Bangla", 13));
      this->richTextBox3->Location = System::Drawing::Point(128, 97);
      this->richTextBox3->Name = L"richTextBox3";
      this->richTextBox3->Size = System::Drawing::Size(325, 27);
      this->richTextBox3->TabIndex = 2;
      this->richTextBox3->Text = L"";
      // 
      // richTextBox4
      // 
      this->richTextBox4->Font = (gcnew System::Drawing::Font(L"Bangla", 14, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
        static_cast<System::Byte>(0)));
      this->richTextBox4->Location = System::Drawing::Point(128, 175);
      this->richTextBox4->Name = L"richTextBox4";
      this->richTextBox4->Size = System::Drawing::Size(325, 50);
      this->richTextBox4->TabIndex = 4;
      this->richTextBox4->Text = L"";
      // 
      // richTextBox5
      // 
      this->richTextBox5->Font = (gcnew System::Drawing::Font(L"Bangla", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
        static_cast<System::Byte>(0)));
      this->richTextBox5->Location = System::Drawing::Point(127, 274);
      this->richTextBox5->Name = L"richTextBox5";
      this->richTextBox5->Size = System::Drawing::Size(327, 27);
      this->richTextBox5->TabIndex = 6;
      this->richTextBox5->Text = L"";
      // 
      // label8
      // 
      this->label8->ForeColor = System::Drawing::Color::Silver;
      this->label8->Location = System::Drawing::Point(32, 349);
      this->label8->Name = L"label8";
      this->label8->Size = System::Drawing::Size(230, 70);
      this->label8->TabIndex = 15;
      this->label8->Text = L"Query Status";
      // 
      // label10
      // 
      this->label10->ForeColor = System::Drawing::Color::Silver;
      this->label10->Location = System::Drawing::Point(553, 165);
      this->label10->Name = L"label10";
      this->label10->Size = System::Drawing::Size(185, 28);
      this->label10->TabIndex = 20;
      this->label10->Text = L"Eng Antonym";
      // 
      // richTextBox7
      // 
      this->richTextBox7->Font = (gcnew System::Drawing::Font(L"Bangla", 13, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
        static_cast<System::Byte>(0)));
      this->richTextBox7->Location = System::Drawing::Point(127, 134);
      this->richTextBox7->Multiline = false;
      this->richTextBox7->Name = L"richTextBox7";
      this->richTextBox7->Size = System::Drawing::Size(157, 27);
      this->richTextBox7->TabIndex = 3;
      this->richTextBox7->Text = L"";
      // 
      // richTextBox9
      // 
      this->richTextBox9->Font = (gcnew System::Drawing::Font(L"Bangla", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
        static_cast<System::Byte>(0)));
      this->richTextBox9->Location = System::Drawing::Point(127, 231);
      this->richTextBox9->Name = L"richTextBox9";
      this->richTextBox9->Size = System::Drawing::Size(326, 33);
      this->richTextBox9->TabIndex = 5;
      this->richTextBox9->Text = L"";
      // 
      // textBox1
      // 
      this->textBox1->Location = System::Drawing::Point(549, 189);
      this->textBox1->Name = L"textBox1";
      this->textBox1->Size = System::Drawing::Size(160, 20);
      this->textBox1->TabIndex = 8;
      // 
      // textBox2
      // 
      this->textBox2->Location = System::Drawing::Point(127, 314);
      this->textBox2->Name = L"textBox2";
      this->textBox2->Size = System::Drawing::Size(326, 20);
      this->textBox2->TabIndex = 7;
      // 
      // label7
      // 
      this->label7->ForeColor = System::Drawing::Color::Silver;
      this->label7->Location = System::Drawing::Point(36, 136);
      this->label7->Name = L"label7";
      this->label7->Size = System::Drawing::Size(77, 31);
      this->label7->TabIndex = 25;
      this->label7->Text = L"Bangla Pronun";
      // 
      // label11
      // 
      this->label11->ForeColor = System::Drawing::Color::Silver;
      this->label11->Location = System::Drawing::Point(33, 276);
      this->label11->Name = L"label11";
      this->label11->Size = System::Drawing::Size(78, 25);
      this->label11->TabIndex = 26;
      this->label11->Text = L"B Antonym";
      // 
      // richTextBox6
      // 
      this->richTextBox6->Font = (gcnew System::Drawing::Font(L"Bangla", 14, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
        static_cast<System::Byte>(0)));
      this->richTextBox6->Location = System::Drawing::Point(26, 425);
      this->richTextBox6->Name = L"richTextBox6";
      this->richTextBox6->Size = System::Drawing::Size(737, 73);
      this->richTextBox6->TabIndex = 27;
      this->richTextBox6->Text = L"";
      // 
      // Form2
      // 
      this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
      this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
      this->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(64)), static_cast<System::Int32>(static_cast<System::Byte>(64)), 
        static_cast<System::Int32>(static_cast<System::Byte>(64)));
      this->ClientSize = System::Drawing::Size(786, 502);
      this->Controls->Add(this->richTextBox6);
      this->Controls->Add(this->label11);
      this->Controls->Add(this->label7);
      this->Controls->Add(this->textBox2);
      this->Controls->Add(this->textBox1);
      this->Controls->Add(this->richTextBox9);
      this->Controls->Add(this->richTextBox7);
      this->Controls->Add(this->label10);
      this->Controls->Add(this->label8);
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
      this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
      this->Name = L"Form2";
      this->Text = L"Add Word into the Database";
      this->ResumeLayout(false);
      this->PerformLayout();

    }
#pragma endregion
  private: System::Void richTextBox1_TextChanged(System::Object^  sender, System::EventArgs^  e) {
         label8->Text = "";
       }
  private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
         String^ dbFile = L"Db\\bdict.accdb";
         if (!System::IO::File::Exists(dbFile)) {
          
         }

        String^ myConnectionString = gcnew String(L"Provider=Microsoft.ACE.OLEDB.12.0;Data Source="+dbFile+L";Persist Security Info=False;");
        OleDbConnection^ myConnection = gcnew OleDbConnection(myConnectionString);
        
        String^ myInsertQuery = String::Concat("INSERT INTO b2e (WordAlias, WordSerial, \
          PartsOfSpeech, BPron, Meaning, UseInSentence, BAntonym, EngMeaning, EngAntonym) Values\
          ('", richTextBox1->Text, "', '", richTextBox2->Text, "', '", richTextBox3->Text,\
          "', '", richTextBox7->Text, "', '", richTextBox4->Text, "', '", richTextBox9->Text,\
          "', '", richTextBox5->Text, "', '", textBox2->Text, "', '", textBox1->Text,"')");

        richTextBox6->Text = String::Concat("Actual query: ", myInsertQuery);
        OleDbCommand^ myCommand = gcnew OleDbCommand(myInsertQuery);
        myCommand->Connection = myConnection;
        myConnection->Open();
        myCommand->ExecuteNonQuery();

        myCommand->Connection->Close();
        label8->Text = L"Data inserted into database successfully. Enter another word now.";
       }
};
}
