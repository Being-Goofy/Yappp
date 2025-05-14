#pragma once

#include <fstream>
#include<iostream>
#include<sstream>
#include <msclr/marshal_cppstd.h>

#pragma comment(lib, "ws2_32.lib")
#pragma warning(disable:4996)

std::string uid, upw;

namespace Pro {

	using namespace System;
	using namespace Threading;
	using namespace System::ComponentModel;
	using namespace System::Collections;

	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace std;


	std::ofstream outfile("D:/DB.txt", std::ios::app);
	int count_show = 1;


	/// <summary>
	/// Summary for SignIn
	/// </summary>
	public ref class SignIn : public System::Windows::Forms::Form
	{
	public:
		bool si;

		SignIn(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
			label2->Text = " ";
			si = false;
		}
	private: System::Windows::Forms::Button^ button1;
	public:
	private: System::Windows::Forms::Panel^ panel2;
	private: System::Windows::Forms::Panel^ panel1;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Button^ button2;

	private: System::Windows::Forms::PictureBox^ pictureBox1;
	private: System::Windows::Forms::Label^ label4;


	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~SignIn()
		{
			if (components)
			{
				delete components;
			}
			outfile.close();

		}
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Button^ Click;
	private: System::Windows::Forms::TextBox^ textBox1;


	private: System::Windows::Forms::TextBox^ textBox2;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::ErrorProvider^ errorProvider1;

	private: System::ComponentModel::IContainer^ components;


	protected:

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
			this->components = (gcnew System::ComponentModel::Container());
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(SignIn::typeid));
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->Click = (gcnew System::Windows::Forms::Button());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->errorProvider1 = (gcnew System::Windows::Forms::ErrorProvider(this->components));
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->panel2 = (gcnew System::Windows::Forms::Panel());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->errorProvider1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->BackColor = System::Drawing::SystemColors::ButtonHighlight;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12));
			this->label1->Location = System::Drawing::Point(98, 224);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(124, 29);
			this->label1->TabIndex = 0;
			this->label1->Text = L"Username";
			// 
			// Click
			// 
			this->Click->BackColor = System::Drawing::Color::MediumSlateBlue;
			this->Click->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->Click->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 17.8F));
			this->Click->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			this->Click->Location = System::Drawing::Point(453, 254);
			this->Click->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->Click->Name = L"Click";
			this->Click->Size = System::Drawing::Size(146, 64);
			this->Click->TabIndex = 1;
			this->Click->Text = L"Login";
			this->Click->UseVisualStyleBackColor = false;
			this->Click->Click += gcnew System::EventHandler(this, &SignIn::Click_Click);
			// 
			// textBox1
			// 
			this->textBox1->BackColor = System::Drawing::SystemColors::ButtonHighlight;
			this->textBox1->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->textBox1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16));
			this->textBox1->ForeColor = System::Drawing::SystemColors::InfoText;
			this->textBox1->Location = System::Drawing::Point(104, 270);
			this->textBox1->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(289, 37);
			this->textBox1->TabIndex = 2;
			this->textBox1->TextChanged += gcnew System::EventHandler(this, &SignIn::textBox1_TextChanged);
			this->textBox1->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &SignIn::textBox1_KeyDown);
			// 
			// textBox2
			// 
			this->textBox2->BackColor = System::Drawing::SystemColors::ButtonHighlight;
			this->textBox2->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->textBox2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16));
			this->textBox2->Location = System::Drawing::Point(104, 365);
			this->textBox2->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->textBox2->Name = L"textBox2";
			this->textBox2->Size = System::Drawing::Size(289, 37);
			this->textBox2->TabIndex = 6;
			this->textBox2->UseSystemPasswordChar = true;
			this->textBox2->TextChanged += gcnew System::EventHandler(this, &SignIn::textBox2_TextChanged);
			this->textBox2->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &SignIn::textBox2_KeyDown);
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->BackColor = System::Drawing::SystemColors::ButtonHighlight;
			this->label3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12));
			this->label3->Location = System::Drawing::Point(98, 324);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(120, 29);
			this->label3->TabIndex = 5;
			this->label3->Text = L"Password";
			this->label3->Click += gcnew System::EventHandler(this, &SignIn::label3_Click);
			// 
			// errorProvider1
			// 
			this->errorProvider1->ContainerControl = this;
			// 
			// panel1
			// 
			this->panel1->BackColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->panel1->Location = System::Drawing::Point(104, 401);
			this->panel1->Margin = System::Windows::Forms::Padding(3, 4, 3, 4);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(289, 2);
			this->panel1->TabIndex = 7;
			// 
			// panel2
			// 
			this->panel2->BackColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->panel2->Location = System::Drawing::Point(104, 306);
			this->panel2->Margin = System::Windows::Forms::Padding(3, 4, 3, 4);
			this->panel2->Name = L"panel2";
			this->panel2->Size = System::Drawing::Size(289, 2);
			this->panel2->TabIndex = 8;
			// 
			// button1
			// 
			this->button1->BackColor = System::Drawing::SystemColors::ButtonHighlight;
			this->button1->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 17.8F));
			this->button1->ForeColor = System::Drawing::Color::MediumSlateBlue;
			this->button1->Location = System::Drawing::Point(788, 611);
			this->button1->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(146, 64);
			this->button1->TabIndex = 9;
			this->button1->Text = L"Exit";
			this->button1->UseVisualStyleBackColor = false;
			this->button1->Click += gcnew System::EventHandler(this, &SignIn::button1_Click);
			// 
			// label2
			// 
			this->label2->BackColor = System::Drawing::SystemColors::ButtonHighlight;
			this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft YaHei", 8.4F, System::Drawing::FontStyle::Italic));
			this->label2->Location = System::Drawing::Point(139, 407);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(254, 29);
			this->label2->TabIndex = 10;
			this->label2->Text = L" ";
			this->label2->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			this->label2->Click += gcnew System::EventHandler(this, &SignIn::label2_Click);
			// 
			// button2
			// 
			this->button2->BackColor = System::Drawing::Color::MediumSlateBlue;
			this->button2->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14));
			this->button2->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			this->button2->Location = System::Drawing::Point(453, 349);
			this->button2->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(146, 64);
			this->button2->TabIndex = 11;
			this->button2->Text = L"Register";
			this->button2->UseVisualStyleBackColor = false;
			this->button2->Click += gcnew System::EventHandler(this, &SignIn::button2_Click);
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Cursor = System::Windows::Forms::Cursors::Hand;
			this->label4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label4->Location = System::Drawing::Point(343, 378);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(53, 20);
			this->label4->TabIndex = 12;
			this->label4->Text = L"Show";
			this->label4->Click += gcnew System::EventHandler(this, &SignIn::label4_Click);
			// 
			// pictureBox1
			// 
			this->pictureBox1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->pictureBox1->Image = System::Drawing::Image::FromFile(L"D:/New folder (2)/Yapp!!/Yapp!!/signinbg.png");
			this->pictureBox1->Location = System::Drawing::Point(0, 0);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(1012, 750);
			this->pictureBox1->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox1->TabIndex = 13;
			this->pictureBox1->TabStop = false;
			// 
			// SignIn
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(9, 20);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::SystemColors::ButtonHighlight;
			this->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->ClientSize = System::Drawing::Size(1012, 750);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->panel2);
			this->Controls->Add(this->panel1);
			this->Controls->Add(this->textBox2);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->Click);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->pictureBox1);
			this->DoubleBuffered = true;
			this->ForeColor = System::Drawing::SystemColors::ControlText;
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
			this->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->MinimumSize = System::Drawing::Size(1012, 750);
			this->Name = L"SignIn";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"ChatApp";
			this->Load += gcnew System::EventHandler(this, &SignIn::SignIn_Load);
			this->Enter += gcnew System::EventHandler(this, &SignIn::SignIn_Enter);
			this->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &SignIn::MyForm_MouseDown);
			this->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &SignIn::MyForm_MouseMove);
			this->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &SignIn::MyForm_MouseUp);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->errorProvider1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

		//private: System::Void textBox1_TextChanged(System::Object^ sender, System::EventArgs^ e) {
		//if () {
		//textBox2->Focus();
		//}
		//}

	  //bool for checking drag
		bool IsDragging;
		Point mousePos;
	private: System::Void MyForm_MouseDown(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
		//enable dragging
		IsDragging = true;
		mousePos.X = e->X;
		mousePos.Y = e->Y;

	}
	private: System::Void MyForm_MouseMove(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
		//creating movement
		if (IsDragging) {
			Point ScreenPos = PointToScreen(Point(e->X, e->Y));
			Location = Point(ScreenPos.X - mousePos.X, ScreenPos.Y - mousePos.Y);
		}
	}
	private: System::Void MyForm_MouseUp(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
		//disable dragging
		IsDragging = false;
	}
	private: System::Void SignIn_Click(System::Object^ sender, System::EventArgs^ e) {
		this->textBox1->Focus();
	}
	private: System::Void SignIn_Enter(System::Object^ sender, System::EventArgs^ e) {
		this->textBox1->Focus();
	}
	private: System::Void SignIn_Load(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void textBox2_TextChanged(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void label3_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void textBox1_TextChanged(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void textBox1_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {
		if (e->KeyValue == (int)Keys::Enter) {


			textBox2->Focus();
		}
	}
	private: System::Void textBox2_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {
		if (e->KeyValue == (int)Keys::Enter) {

			Click->PerformClick();
		}
	}
	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
		Application::Exit();
	}
	private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e) {
		std::ifstream infile("D:/DB.txt");
		if (!infile) {
			label2->Text = "Can't open file";
			return;
		}
		std::string line;
		bool Unique_User = true;  // Assume the user is unique initially

		String^ id = textBox1->Text;
		std::string inputID = msclr::interop::marshal_as<std::string>(id);

		while (getline(infile, line)) {
			std::istringstream ss(line);
			std::string uid;
			getline(ss, uid, ':');

			if (uid == inputID) {
				Unique_User = false;
				label2->Text = "Username Already Taken!!!";
				textBox1->Focus();
				break;
			}
		}
		infile.close();

		if (Unique_User) {
			if (textBox2->Text->Length >= 8) {
				String^ pw = textBox2->Text;
				std::string inputPW = msclr::interop::marshal_as<std::string>(pw);


				outfile << inputID << ":" << inputPW << std::endl;
				outfile.close();

				textBox1->Clear();
				textBox2->Clear();
				textBox1->Focus();
				label2->Text = "Registration Successful. LOGIN!!";
			}
			else {
				label2->Text = "Enter Minimum 8 Characters!";
				textBox2->Focus();
			}
		}
	}


	private: System::Void Click_Click(System::Object^ sender, System::EventArgs^ e) {
		std::ifstream infile("D:/DB.txt");
		if (!infile) {
			label2->Text = "can't open file";
			return;
		}

		String^ id = textBox1->Text;
		String^ pw = textBox2->Text;
		string line;
		bool userFound = false;
		bool passwordCorrect = false;

		while (getline(infile, line)) {
			// Debugging output
			//System::Diagnostics::Debug::WriteLine(gcnew String(line.c_str()));

			std::istringstream ss(line);


			getline(ss, uid, ':');
			getline(ss, upw);

			// Debugging output
			//System::Diagnostics::Debug::WriteLine("File ID: " + msclr::interop::marshal_as<String^>(uid) + " File PW: " + gcnew String(upw.c_str()));
			//System::Diagnostics::Debug::WriteLine("Input ID: " + id + " Input PW: " + pw);

			if (id == msclr::interop::marshal_as<String^>(uid)) {
				userFound = true;
				if (pw == msclr::interop::marshal_as<String^>(upw)) {
					passwordCorrect = true;
					break;
				}
			}
		}
		infile.close();

		if (userFound) {
			if (passwordCorrect) {
				label2->Text = "Sign In Successful";
				si = true;
				this->~SignIn();

			}
			else {
				label2->Text = "Incorrect Password";
			}
		}
		else {
			label2->Text = "User Not Found. Register!!!!";
		}
	}



	private: System::Void label2_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void button2_Click_1(System::Object^ sender, System::EventArgs^ e) {

	}
	private: System::Void label4_Click(System::Object^ sender, System::EventArgs^ e) {
		if (count_show % 2 != 0) {
			textBox2->UseSystemPasswordChar = false;
			label4->Text = "Hide";
		}
		else if (count_show % 2 == 0) {
			textBox2->UseSystemPasswordChar = true;
			label4->Text = "Show";
		}
		count_show++;
	}
	};

}
