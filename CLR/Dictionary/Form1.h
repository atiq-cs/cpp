#include "Form21.h"

#pragma once

namespace dbDictQuery {
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
  private:
    array<String^>^ wordlist;
  private: System::Windows::Forms::ToolStripMenuItem^  exitToolStripMenuItem;
  private: System::Windows::Forms::ContextMenuStrip^  contextMenuStrip1;
  private: System::Windows::Forms::ToolStripMenuItem^  copyToolStripMenuItem;
  private: System::Windows::Forms::ToolStripMenuItem^  selectAllToolStripMenuItem;


      int wcount;
  private: System::Windows::Forms::Label^  label1;
       String^ dbFile;


  public:
    Form1(void)
    {
      wcount = 0;
      dbFile = L"Db\\bdict.accdb";
      wordlist= gcnew array<String^> (100) {""};

      InitializeComponent();
      //
      //TODO: Add the constructor code here
      //
      // my code
      // Check if the database file exists
      if (!System::IO::File::Exists(dbFile)) {
        System::Windows::Forms::MessageBox::Show("Database file not found please reinstall", "File not found", MessageBoxButtons::OK,
          MessageBoxIcon::Exclamation);
        Application::Exit();
      }

      // updateWordList();
      // for (int i=0; i<wcount; i++)
      //   this->listBox1->Items->Add(wordlist[i]);
        
      // this->listBox1->SetSelected(0, true);
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

  private: System::Windows::Forms::RichTextBox^  richTextBox1;    // search textBox
  protected: 
  private: System::Windows::Forms::RichTextBox^  richTextBox2;    // TextBox for Bangla Meaning
  private: System::Windows::Forms::RichTextBox^  richTextBox3;    // TextBox for English Meaning
       // Debug button for removal
  private: System::Windows::Forms::MenuStrip^  menuStrip1;      // Menu
  private: System::Windows::Forms::ToolStripMenuItem^  actionsToolStripMenuItem;
  private: System::Windows::Forms::ToolStripMenuItem^  enterDataToolStripMenuItem;
  private: System::Windows::Forms::ToolStripMenuItem^  aboutThisSoftwareToolStripMenuItem;
  private: System::Windows::Forms::ListBox^  listBox1;

  private: System::ComponentModel::IContainer^  components;


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
      this->components = (gcnew System::ComponentModel::Container());
      System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(Form1::typeid));
      this->richTextBox1 = (gcnew System::Windows::Forms::RichTextBox());
      this->contextMenuStrip1 = (gcnew System::Windows::Forms::ContextMenuStrip(this->components));
      this->copyToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
      this->selectAllToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
      this->richTextBox2 = (gcnew System::Windows::Forms::RichTextBox());
      this->richTextBox3 = (gcnew System::Windows::Forms::RichTextBox());
      this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
      this->actionsToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
      this->enterDataToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
      this->aboutThisSoftwareToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
      this->exitToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
      this->listBox1 = (gcnew System::Windows::Forms::ListBox());
      this->label1 = (gcnew System::Windows::Forms::Label());
      this->contextMenuStrip1->SuspendLayout();
      this->menuStrip1->SuspendLayout();
      this->SuspendLayout();
      // 
      // richTextBox1
      // 
      this->richTextBox1->ContextMenuStrip = this->contextMenuStrip1;
      this->richTextBox1->Font = (gcnew System::Drawing::Font(L"Bangla", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
        static_cast<System::Byte>(0)));
      this->richTextBox1->Location = System::Drawing::Point(12, 37);
      this->richTextBox1->Multiline = false;
      this->richTextBox1->Name = L"richTextBox1";
      this->richTextBox1->ScrollBars = System::Windows::Forms::RichTextBoxScrollBars::None;
      this->richTextBox1->Size = System::Drawing::Size(169, 28);
      this->richTextBox1->TabIndex = 0;
      this->richTextBox1->Text = L"";
      this->richTextBox1->UseWaitCursor = true;
      this->richTextBox1->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &Form1::richTextBox1_KeyDown);
      this->richTextBox1->TextChanged += gcnew System::EventHandler(this, &Form1::richTextBox1_TextChanged);
      // 
      // contextMenuStrip1
      // 
      this->contextMenuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {this->copyToolStripMenuItem, 
        this->selectAllToolStripMenuItem});
      this->contextMenuStrip1->Name = L"contextMenuStrip1";
      this->contextMenuStrip1->Size = System::Drawing::Size(123, 48);
      // 
      // copyToolStripMenuItem
      // 
      this->copyToolStripMenuItem->Name = L"copyToolStripMenuItem";
      this->copyToolStripMenuItem->Size = System::Drawing::Size(122, 22);
      this->copyToolStripMenuItem->Text = L"Copy";
      this->copyToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::copyToolStripMenuItem_Click);
      // 
      // selectAllToolStripMenuItem
      // 
      this->selectAllToolStripMenuItem->Name = L"selectAllToolStripMenuItem";
      this->selectAllToolStripMenuItem->Size = System::Drawing::Size(122, 22);
      this->selectAllToolStripMenuItem->Text = L"Select All";
      this->selectAllToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::selectAllToolStripMenuItem_Click);
      // 
      // richTextBox2
      // 
      this->richTextBox2->ContextMenuStrip = this->contextMenuStrip1;
      this->richTextBox2->Font = (gcnew System::Drawing::Font(L"Bangla", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
        static_cast<System::Byte>(0)));
      this->richTextBox2->Location = System::Drawing::Point(215, 138);
      this->richTextBox2->Name = L"richTextBox2";
      this->richTextBox2->ReadOnly = true;
      this->richTextBox2->ScrollBars = System::Windows::Forms::RichTextBoxScrollBars::Vertical;
      this->richTextBox2->Size = System::Drawing::Size(253, 344);
      this->richTextBox2->TabIndex = 1;
      this->richTextBox2->Text = L"";
      // 
      // richTextBox3
      // 
      this->richTextBox3->ContextMenuStrip = this->contextMenuStrip1;
      this->richTextBox3->Font = (gcnew System::Drawing::Font(L"Arial", 9.5F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
        static_cast<System::Byte>(0)));
      this->richTextBox3->Location = System::Drawing::Point(497, 138);
      this->richTextBox3->Name = L"richTextBox3";
      this->richTextBox3->ReadOnly = true;
      this->richTextBox3->ScrollBars = System::Windows::Forms::RichTextBoxScrollBars::Vertical;
      this->richTextBox3->Size = System::Drawing::Size(254, 344);
      this->richTextBox3->TabIndex = 2;
      this->richTextBox3->Text = L"";
      // 
      // menuStrip1
      // 
      this->menuStrip1->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(64)), static_cast<System::Int32>(static_cast<System::Byte>(64)), 
        static_cast<System::Int32>(static_cast<System::Byte>(64)));
      this->menuStrip1->ForeColor = System::Drawing::Color::White;
      this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) {this->actionsToolStripMenuItem});
      this->menuStrip1->Location = System::Drawing::Point(0, 0);
      this->menuStrip1->Name = L"menuStrip1";
      this->menuStrip1->Size = System::Drawing::Size(780, 24);
      this->menuStrip1->TabIndex = 4;
      this->menuStrip1->Text = L"menuStrip1";
      this->menuStrip1->ItemClicked += gcnew System::Windows::Forms::ToolStripItemClickedEventHandler(this, &Form1::menuStrip1_ItemClicked);
      // 
      // actionsToolStripMenuItem
      // 
      this->actionsToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {this->enterDataToolStripMenuItem, 
        this->aboutThisSoftwareToolStripMenuItem, this->exitToolStripMenuItem});
      this->actionsToolStripMenuItem->Name = L"actionsToolStripMenuItem";
      this->actionsToolStripMenuItem->Size = System::Drawing::Size(59, 20);
      this->actionsToolStripMenuItem->Text = L"Actions";
      // 
      // enterDataToolStripMenuItem
      // 
      this->enterDataToolStripMenuItem->Name = L"enterDataToolStripMenuItem";
      this->enterDataToolStripMenuItem->Size = System::Drawing::Size(177, 22);
      this->enterDataToolStripMenuItem->Text = L"Enter Data";
      this->enterDataToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::enterDataToolStripMenuItem_Click);
      // 
      // aboutThisSoftwareToolStripMenuItem
      // 
      this->aboutThisSoftwareToolStripMenuItem->Name = L"aboutThisSoftwareToolStripMenuItem";
      this->aboutThisSoftwareToolStripMenuItem->Size = System::Drawing::Size(177, 22);
      this->aboutThisSoftwareToolStripMenuItem->Text = L"About this software";
      this->aboutThisSoftwareToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::aboutThisSoftwareToolStripMenuItem_Click);
      // 
      // exitToolStripMenuItem
      // 
      this->exitToolStripMenuItem->Name = L"exitToolStripMenuItem";
      this->exitToolStripMenuItem->Size = System::Drawing::Size(177, 22);
      this->exitToolStripMenuItem->Text = L"Exit";
      this->exitToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::exitToolStripMenuItem_Click);
      // 
      // listBox1
      // 
      this->listBox1->Font = (gcnew System::Drawing::Font(L"Bangla", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
        static_cast<System::Byte>(0)));
      this->listBox1->FormattingEnabled = true;
      this->listBox1->ItemHeight = 18;
      this->listBox1->Location = System::Drawing::Point(12, 82);
      this->listBox1->Name = L"listBox1";
      this->listBox1->Size = System::Drawing::Size(169, 400);
      this->listBox1->TabIndex = 5;
      this->listBox1->SelectedIndexChanged += gcnew System::EventHandler(this, &Form1::listBox1_SelectedIndexChanged);
      this->listBox1->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &Form1::listBox1_KeyDown);
      // 
      // label1
      // 
      this->label1->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"label1.Image")));
      this->label1->Location = System::Drawing::Point(185, 24);
      this->label1->Name = L"label1";
      this->label1->Size = System::Drawing::Size(463, 74);
      this->label1->TabIndex = 6;
      // 
      // Form1
      // 
      this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
      this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
      this->AutoValidate = System::Windows::Forms::AutoValidate::EnableAllowFocusChange;
      this->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(64)), static_cast<System::Int32>(static_cast<System::Byte>(64)), 
        static_cast<System::Int32>(static_cast<System::Byte>(64)));
      this->ClientSize = System::Drawing::Size(780, 517);
      this->Controls->Add(this->label1);
      this->Controls->Add(this->listBox1);
      this->Controls->Add(this->richTextBox3);
      this->Controls->Add(this->menuStrip1);
      this->Controls->Add(this->richTextBox2);
      this->Controls->Add(this->richTextBox1);
      this->Icon = (cli::safe_cast<System::Drawing::Icon^  >(resources->GetObject(L"$this.Icon")));
      this->MainMenuStrip = this->menuStrip1;
      this->Name = L"Form1";
      this->Text = L"বাংলা অভিধান";
      this->contextMenuStrip1->ResumeLayout(false);
      this->menuStrip1->ResumeLayout(false);
      this->menuStrip1->PerformLayout();
      this->ResumeLayout(false);
      this->PerformLayout();
    }

#pragma endregion
      private: System::Void richTextBox1_TextChanged(System::Object^  sender, System::EventArgs^  e) {
             /*if (label1->Text == "")
              label1->Text = L"Text changed.";
             else
               label1->Text = "";*/
             int matchIndex = findMatch(richTextBox1->Text);
             // label1->Text = L"Got index: "+matchIndex;
             // label1->Text = label1->Text + L"\nYou have entered: "+richTextBox1->Text;
             if (matchIndex >= 0)
              listBox1->SelectedIndex = matchIndex;
             
           }
      private: System::Void enterDataToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
              Form2^ newMDIChild = gcnew Form2();
              // Set the Parent Form of the Child window.
              //newMDIChild->MdiParent = this;
              // Display the new form.
              newMDIChild->ShowDialog();
           }
      private: System::Void menuStrip1_ItemClicked(System::Object^  sender, System::Windows::Forms::ToolStripItemClickedEventArgs^  e) {
           }


      private: System::Void listBox1_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
             // disable wait cursor
             richTextBox1->UseWaitCursor = false;

             array<String^>^ sep = gcnew array<String^> (1) {" ["};
             String^ Item = listBox1->SelectedItem->ToString();
             array<String^>^ res = Item->Split(sep, System::StringSplitOptions::None);
             String^ Word = res[0];
             String^ serial = res[1]->Remove(res[1]->Length-2);
             //richTextBox3->Text = "You have selected item "+ System::Convert::ToString(listBox1->SelectedIndex) + "  its value is: "+ Word + " serial: " + serial;
             updateMeaning(Word, serial);
           }
      private: System::Void aboutThisSoftwareToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
            showMyDialog();
           }

      private: Void showMyDialog() {

          //  Application::Run(gcnew Form2());
           }

          // private: String^ serialize(String^ str) {
          //   String^ bDigit;  // Bangladigit
          //   array<wchar_t>^stchar = str->ToCharArray();
          //   for (int i=0; i<str->Length; i++) {
          //     richTextBox3->Text = String::Concat(richTextBox3->Text, stchar[i], ":", System::Convert::ToString((int)stchar[i]), "\n");
          //     //stchar[i] = (int)stchar[i] + '১';
          //     stchar[i] = 0x09E6+stchar[i]-48;
          //     richTextBox3->Text = String::Concat(richTextBox3->Text, stchar[i], ":", System::Convert::ToString((int)stchar[i]), "\n");
          //   }
          //   bDigit = gcnew String(stchar);
          //   return String::Concat(" [", bDigit, "] ");
          // }

        private: String^ serialize(String^ str) {
            String^ bDigit;  // Bangladigit
            array<wchar_t>^stchar = str->ToCharArray();
            for (int i=0; i<str->Length; i++) {
              //richTextBox3->Text = String::Concat(richTextBox3->Text, stchar[i], ":", System::Convert::ToString((int)stchar[i]), "\n");
              //stchar[i] = (int)stchar[i] + '১';
              stchar[i] = 0x09E6+stchar[i]-48;
              //richTextBox3->Text = String::Concat(richTextBox3->Text, stchar[i], ":", System::Convert::ToString((int)stchar[i]), "\n");
            }
            bDigit = gcnew String(stchar);
            return String::Concat(" [", bDigit, "] ");
          }
        private: String^ deserialize(String^ str) {
            String^ engDigit;  // Bangladigit
            array<wchar_t>^stchar = str->ToCharArray();
            for (int i=0; i<str->Length; i++) {
              //richTextBox3->Text = String::Concat(richTextBox3->Text, stchar[i], ":", System::Convert::ToString((int)stchar[i]), "\n");
              //stchar[i] = (int)stchar[i] + '১';
              stchar[i] = stchar[i] - 0x09E6 + 48;
              //richTextBox3->Text = String::Concat(richTextBox3->Text, stchar[i], ":", System::Convert::ToString((int)stchar[i]), "\n");
            }
            engDigit = gcnew String(stchar);
            return engDigit;
          }

        private:
        Void updateWordList() {
          // If the connection string is null, use a default.
          String^ myConnectionString = gcnew String(L"Provider=Microsoft.ACE.OLEDB.12.0;Data Source="+dbFile+";Persist Security Info=False;");
          
          // if(myConnectionString->Equals(S"")) 
          // {
          //    myConnectionString = S"Provider=SQLOLEDB;Data Source=localhost;Initial Catalog=Northwind;"  
          //    S"Integrated Security=SSPI;";
          // }

          OleDbConnection^ myConnection = gcnew OleDbConnection(myConnectionString);
          String^ myInsertQuery = L"select WordAlias, WordSerial from b2e order by WordAlias ASC";
          OleDbCommand^ myCommand = gcnew OleDbCommand(myInsertQuery);
          myCommand->Connection = myConnection;
          myConnection->Open();
          OleDbDataReader^ myReader = myCommand->ExecuteReader();
           while (myReader->Read()) {
            try {
              if (!myReader->IsDBNull(1)) {
                wordlist[wcount++] = myReader->GetString(0)+ serialize(System::Convert::ToString(myReader->GetInt32(1)));
              }
            }
            catch (Exception^ e) {
              richTextBox2->Text = e->ToString();
            }
          }

          // always call Close when done reading.
          myReader->Close();
          // Close the connection when done with it.
          myConnection->Close();
         }

  private: System::Void exitToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
         Application::Exit();
       }

  private: Void updateMeaning(String^ Word, String^ Serial) {
          // If the connection string is null, use a default.
          String^ myConnectionString = gcnew String(L"Provider=Microsoft.ACE.OLEDB.12.0;Data Source="+dbFile+";Persist Security Info=False;");
            //String^ myConnectionString = gcnew String(L"Provider=Microsoft.ACE.OLEDB.12.0;Data Source=Db\\bdict.accdb;Persist Security Info=False;");
          OleDbConnection^ myConnection = gcnew OleDbConnection(myConnectionString);
          //String^ myInsertQuery = L"select * from b2e where WordAlias='"+Word+"' and WordSerial="+Serial;
          // Convert Serial from unicode to english
          Serial = deserialize(Serial);
          //label1->Text="got text: "+Serial;

          String^ myInsertQuery = L"Select * from b2e where WordAlias='"+Word+"' and WordSerial="+Serial;
          String^ desc;
          OleDbCommand^ myCommand = gcnew OleDbCommand(myInsertQuery);
          myCommand->Connection = myConnection;
          myConnection->Open();
          OleDbDataReader^ myReader = myCommand->ExecuteReader();

          while (myReader->Read())
          {
            try {
              // Clear description
              desc = "";
              // Column 1, WordAlias
              if (!myReader->IsDBNull(1)) {
                // Column 6, Pronunciation
                if (!myReader->IsDBNull(6)) {
                  desc = "[ " + myReader->GetString(6) + L" ] ";
                }
                // Column 3, PartsOfSpeech
                if (!myReader->IsDBNull(3)) {
                  desc = desc + myReader->GetString(3)+L". ";
                }
                // Column 4, Meaning
                if (!myReader->IsDBNull(4)) {
                  desc = desc + myReader->GetString(4)+L"\n\n";
                }
                // Column 5, Use of the word in Bangla
                if (!myReader->IsDBNull(5)) {
                  desc = desc +L"প্রয়োগ: "+ myReader->GetString(5)+"";
                }
                richTextBox2->Text = desc;
                // Clear description
                desc = "";
                // Column 9, Pronunciation in English
                if (!myReader->IsDBNull(9)) {
                  desc = L"[ "+ myReader->GetString(9)+L" ] ";
                }
                // Column 8, Meaning in English
                if (!myReader->IsDBNull(8)) {
                  desc = desc+ myReader->GetString(8);
                }
                // Display in RichTextBox
                richTextBox3->Text = desc;
                //richTextBox2->Text = myReader->GetString(1) + " " + System::Convert::ToString(myReader->GetInt32(2));
              }
            }
            catch (Exception^ e) {
              //label1->Text = "IndexChange=> " + e->ToString();
            }
          }

          // always call Close when done reading.
          myReader->Close();
          // Close the connection when done with it.
          myConnection->Close();        
       }

  private: System::Void copyToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
         richTextBox2->Copy();
       }
  private: System::Void selectAllToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
         richTextBox2->SelectAll();
       }
  private: int findMatch(String^ substr) {
         for (int i=0; i<wcount; i++)
           if (wordlist[i]->StartsWith(substr))
             return i;
         return -1;
       }
  private: System::Void richTextBox1_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^ e) {
         if (e->KeyCode == Keys::Up) {
           listBox1->Focus();
           //label1->Text = L"Upkey is pressed.";
           if (listBox1->SelectedIndex > 0)
             listBox1->SelectedIndex--;
         }
         else if (e->KeyCode == Keys::Down) {
           listBox1->Focus();
           //label1->Text = L"Downkey is pressed.";
           if (listBox1->SelectedIndex < wcount -1)
             listBox1->SelectedIndex++;
         }

       }

   private: System::Void listBox1_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {
          if (e->KeyCode == Keys::Back) {
            if (richTextBox1->Text->Length > 0) {
              richTextBox1->Text = richTextBox1->Text->Remove(richTextBox1->Text->Length - 1);
              richTextBox1->SelectionStart = richTextBox1->Text->Length;
            }
            //label1->Text = label1->Text + L" Text: "+richTextBox1->Text;
            richTextBox1->Focus();
          }
          else if (e->KeyCode != Keys::Up && e->KeyCode != Keys::Down)
            richTextBox1->Focus();
        }
  };
}
