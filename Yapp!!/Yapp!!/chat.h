#pragma once
#include <list>
#include <msclr/marshal_cppstd.h>
#include "SignIn.h"
#include <thread>
#include <cstdio>
#include "round.h"
#using <System.dll>


#pragma comment(lib, "ws2_32.lib")
#pragma warning(disable:4996)



std::string textmsg;

namespace Project1 {

    using namespace System;
    using namespace System::Threading;
    using namespace Threading;
    using System::Threading::Thread;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;
    using namespace System::Collections::Generic;
    using namespace System::Drawing::Drawing2D;
    using namespace System::Net::Sockets;

    //class for shit
    class Client {
    protected:
        SOCKET clientSocket;
        std::string serverAddress;
        int port;

    public:
        Client(const std::string& address, int port) : serverAddress(address), port(port), clientSocket(INVALID_SOCKET) {
            if (!Initialize()) {

                exit(1);
            }
        }

        ~Client() {
            Cleanup();
            WSACleanup();
        }

        bool Initialize() {
            WSADATA data;
            return WSAStartup(MAKEWORD(2, 2), &data) == 0;
        }

        void Cleanup() {
            if (clientSocket != INVALID_SOCKET) {
                closesocket(clientSocket);
            }

        }

        void Connect() {
            CreateSocket();
            ConnectToServer();

        }

        void StartCommunication() {
            std::thread senderThread(&Client::SendMsg, this);
            std::thread receiverThread(&Client::ReceiveMsg, this);
            senderThread.join();
            receiverThread.join();
        }

        void CreateSocket() {
            clientSocket = socket(AF_INET, SOCK_STREAM, 0);
            if (clientSocket == INVALID_SOCKET) {

                Cleanup();
                exit(1);
            }
        }

        void ConnectToServer() {
            sockaddr_in serverAddr;
            serverAddr.sin_family = AF_INET;
            serverAddr.sin_port = htons(port);


            uint32_t adad = inet_addr(serverAddress.c_str());
            serverAddr.sin_addr.S_un.S_addr = adad;
            if (connect(clientSocket, reinterpret_cast<sockaddr*>(&serverAddr), sizeof(serverAddr)) == SOCKET_ERROR) {

                Cleanup();
                exit(1);
            }

            // Assuming you have a global or member variable `uid` as std::string representing your user ID
            send(clientSocket, uid.c_str(), (int)uid.length(), 0);


        }

        void SendMsg() {


            std::string message;


            std::string msg = uid + " : " + textmsg;
            int byteSent = send(clientSocket, msg.c_str(), msg.length(), 0);




        }

        std::string ReceiveMsg() {
            char buffer[4096];
            int recvLength;

            recvLength = recv(clientSocket, buffer, sizeof(buffer), 0);
            if (recvLength <= 0) {
                return "";  // Disconnected or error
            }
            else {
                return std::string(buffer, recvLength);  // Return the message directly
            }
        }

    };

    Client client("127.0.0.1", 55555);

    public ref class MyForm1 : public System::Windows::Forms::Form
    {
    public:

        Panel^ messagePanel = nullptr;

        MyForm1(void)
        {
            InitializeComponent();
            panels = gcnew List<Panel^>();
            navButtons = gcnew List<Button^>();
            addButtons = gcnew List<Button^>();
            headnames = gcnew List<Label^>();
            messages = gcnew List<Label^>();
            txtboxpic = gcnew List<PictureBox^>();
            msgpanels = gcnew List<Panel^>();
            textboxes = gcnew List<TextBox^>(); // Initialize the list of TextBoxes
            CreateNewPanel("You");  // Create the initial panel
            messagePanel = msgpanels[0];
            currentPanelIndex = 0;
            panels[currentPanelIndex]->Visible = true;
            bckImage->BringToFront();
            label2->BringToFront();
            label3->BringToFront();
            label4->BringToFront();

            // Initialize and start the timer
            movementTimer = gcnew System::Windows::Forms::Timer();
            movementTimer->Interval = 100; // Set the interval to 100ms (adjust as needed)
            movementTimer->Tick += gcnew EventHandler(this, &MyForm1::OnMovementTimerTick);
            movementTimer->Start();

            //connecting client
            client.Connect();

            Thread^ rcvThread = gcnew Thread(gcnew ThreadStart(this, &MyForm1::rcvmsg));
            rcvThread->IsBackground = true;
            rcvThread->Start();

        }

        delegate void UpdateUIDelegate(String^ msg);

        void UpdateUIWithMessage(String^ msg) {
            Label^ receivedmsg = ReceiveMessage(msg, currentY);

            if (messagePanel != nullptr) {
                messagePanel->Controls->Add(receivedmsg);
                receivedmsg->BringToFront();
                messagePanel->ScrollControlIntoView(receivedmsg);
                currentY = receivedmsg->Bottom + 10;
            }
            else {
                System::Diagnostics::Debug::WriteLine("Received msg: " + msg);

            }
        }


    private: System::Windows::Forms::PictureBox^ bckImage;
    public:

        //
        // person string name
        // 
        String^ pername;
        int txts, txts2, txtps, txtps2, msgp, msgp2, msgs, msgs2, ls, ms, currentY = 100, rightPosition;

        void rcvmsg() {
            while (true) {
                std::string rawMsg = client.ReceiveMsg();  // Now it returns the msg

                if (rawMsg.empty()) {
                    continue;  // Nothing received, keep listening
                }

                String^ msg = msclr::interop::marshal_as<String^>(rawMsg);

                System::Diagnostics::Debug::WriteLine("Received: " + msg);  // Log to Output window

                UpdateUIDelegate^ del = gcnew UpdateUIDelegate(this, &MyForm1::UpdateUIWithMessage);
                this->Invoke(del, msg);
            }
        }



        

    protected:
        ~MyForm1()
        {
            if (components)
            {
                delete components;
            }
            //client.Cleanup();
        }

    private: System::Windows::Forms::Label^ label1;
    private: System::Windows::Forms::Label^ label2;
    private: System::Windows::Forms::Label^ label3;
    private: System::Windows::Forms::Label^ label4;
    private: RoundedButton^ buttonNext;
    private: System::Windows::Forms::FlowLayoutPanel^ buttonPanel;
    private: System::Windows::Forms::Panel^ containerPanel;
    private: System::ComponentModel::Container^ components;
    private: System::Windows::Forms::Timer^ movementTimer;
    private: List<TextBox^>^ textboxes; // List to store TextBoxes
    private: List<Panel^>^ msgpanels;
    private: List<Label^>^ messages;
    private: List<Label^>^ headnames;
    private: List<Panel^>^ panels;
    private: List<Button^>^ navButtons;
    private: List<Button^>^ addButtons;
    private: List<PictureBox^>^ txtboxpic;
    private: int currentPanelIndex = -1;

#pragma region Windows Form Designer generated code
           void InitializeComponent(void)
           {

               System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(MyForm1::typeid));
               this->label1 = (gcnew System::Windows::Forms::Label());
               this->label2 = (gcnew System::Windows::Forms::Label());
               this->label3 = (gcnew System::Windows::Forms::Label());
               this->label4 = (gcnew System::Windows::Forms::Label());
               this->buttonNext = gcnew RoundedButton();;
               this->buttonPanel = (gcnew System::Windows::Forms::FlowLayoutPanel());
               this->containerPanel = (gcnew System::Windows::Forms::Panel());
               this->bckImage = (gcnew System::Windows::Forms::PictureBox());
               this->containerPanel->SuspendLayout();
               (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->bckImage))->BeginInit();
               this->SuspendLayout();
               // 
               // label1
               // 
               this->label1->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(30)), static_cast<System::Int32>(static_cast<System::Byte>(40)),
                   static_cast<System::Int32>(static_cast<System::Byte>(55)));
               this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14, System::Drawing::FontStyle::Bold));
               this->label1->ForeColor = System::Drawing::Color::MediumSlateBlue;
               this->label1->Location = System::Drawing::Point(5, 15);
               this->label1->Name = L"label1";
               this->label1->Size = System::Drawing::Size(150, 35);
               this->label1->TabIndex = 0;
               this->label1->Text = L"Chats";
               this->label1->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
               // 
               // buttonNext
               // 
               this->buttonNext->BackColor = System::Drawing::Color::MediumSlateBlue;
               this->buttonNext->BackgroundImage = System::Drawing::Image::FromFile(L"D:/New folder (2)/Yapp!!/Yapp!!/add_button.png");
               this->buttonNext->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Zoom;
               this->buttonNext->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
               this->buttonNext->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(29)), static_cast<System::Int32>(static_cast<System::Byte>(33)),
                   static_cast<System::Int32>(static_cast<System::Byte>(36)));
               this->buttonNext->Location = System::Drawing::Point(190, 15);
               this->buttonNext->Name = L"buttonNext";
               this->buttonNext->Size = System::Drawing::Size(35, 35);
               this->buttonNext->TabIndex = 0;
               this->buttonNext->UseVisualStyleBackColor = false;
               this->buttonNext->Click += gcnew System::EventHandler(this, &MyForm1::buttonNext_Click);
               this->buttonNext->MouseEnter += gcnew System::EventHandler(this, &MyForm1::buttonNext_MouseEnter);
               this->buttonNext->MouseLeave += gcnew System::EventHandler(this, &MyForm1::buttonNext_MouseLeave);
               // 
               // buttonPanel
               // 
               this->buttonPanel->AutoScroll = true;
               this->buttonPanel->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(30)), static_cast<System::Int32>(static_cast<System::Byte>(40)),
                   static_cast<System::Int32>(static_cast<System::Byte>(55)));
               this->buttonPanel->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
               this->buttonPanel->Dock = System::Windows::Forms::DockStyle::Left;
               this->buttonPanel->Location = System::Drawing::Point(0, 0);
               this->buttonPanel->Name = L"buttonPanel";
               this->buttonPanel->Size = System::Drawing::Size(246, 583);
               this->buttonPanel->TabIndex = 1;


               // 
               // containerPanel
               // 
               this->containerPanel->Controls->Add(this->label1);
               this->containerPanel->Controls->Add(this->buttonNext);
               this->containerPanel->Dock = System::Windows::Forms::DockStyle::Top;
               this->containerPanel->Location = System::Drawing::Point(264, 0);
               this->containerPanel->Name = L"containerPanel";
               this->containerPanel->Size = System::Drawing::Size(240, 65);
               this->containerPanel->TabIndex = 2;
               // 
               // bckImage
               // 
               this->bckImage->BackgroundImage = System::Drawing::Image::FromFile(L"D:/New folder (2)/Yapp!!/Yapp!!/bc_image.jpg");
               this->bckImage->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
               this->bckImage->Location = System::Drawing::Point(330, 106);
               this->bckImage->Name = L"bckImage";
               this->bckImage->Size = System::Drawing::Size(560, 321);
               this->bckImage->TabIndex = 3;
               this->bckImage->TabStop = false;
               this->bckImage->Dock = System::Windows::Forms::DockStyle::Fill;

               // 
              // label2
              // 
               this->label2->BackColor = System::Drawing::Color::FromArgb(29, 33, 36);
               this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14, System::Drawing::FontStyle::Bold));
               this->label2->ForeColor = System::Drawing::Color::White;
               this->label2->Location = System::Drawing::Point(350, 150);
               this->label2->Name = L"label2";
               this->label2->Text = L"YAPP! for window";
               this->label2->AutoSize = true;
               this->label2->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;

               // 
              // label3
              // 
               this->label3->BackColor = System::Drawing::Color::FromArgb(29, 33, 36);
               this->label3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold));
               this->label3->ForeColor = System::Drawing::Color::LightGray;
               this->label3->Location = System::Drawing::Point(300, 180);

               this->label3->Name = L"label3";
               this->label3->Text = L"Enjoying sending and receiving message using yapp!";
               this->label3->AutoSize = true;
               this->label3->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;

               // 
               // label4
               // 
               this->label4->BackColor = System::Drawing::Color::FromArgb(29, 33, 36);
               this->label4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8, System::Drawing::FontStyle::Bold));
               this->label4->ForeColor = System::Drawing::Color::Gray;
               this->label4->Location = System::Drawing::Point(350, 310);
               this->label4->Name = L"label4";
               this->label4->Text = L"🔒 end-to-end encrypted";
               this->label4->AutoSize = true;
               this->label4->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
               //
               // MyForm1
               // 
               this->AutoScaleDimensions = System::Drawing::SizeF(9, 20);
               this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
               this->BackColor = System::Drawing::Color::Black;
               this->ClientSize = System::Drawing::Size(1023, 583);
               this->BackColor = System::Drawing::Color::FromArgb(29, 33, 36);
               this->Controls->Add(this->containerPanel);
               this->Controls->Add(this->buttonPanel);
               this->Name = L"MyForm1";
               this->Text = L"MyForm1";
               this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &MyForm1::MyForm1_FormClosing);
               this->Load += gcnew System::EventHandler(this, &MyForm1::MyForm1_Load);
               this->Resize += gcnew System::EventHandler(this, &MyForm1::MyForm1_Resize);
               this->containerPanel->ResumeLayout(false);
               (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->bckImage))->EndInit();
               this->ResumeLayout(false);

               // Add label1 and buttonNext to the containerPanel
               this->buttonPanel->Controls->Add(this->containerPanel);


           }
#pragma endregion

    private: System::Void MyForm1_Load(System::Object^ sender, System::EventArgs^ e) {
    }

    private: System::Void CenterLabel() {
        // Calculate the center position

        //width
        int x = (this->Width / 2) - 30;
        int y = (this->Width / 2) - 120;
        int z = (this->Width / 2) - 15;
        //height
        int xh = (this->Height / 2) - 60;
        int yh = (this->Height / 2) - 30;
        int zh = this->Height - 100;
        // Set the new location
        if (this->Width > 640) {
            label2->Location = System::Drawing::Point(x, xh);
            label3->Location = System::Drawing::Point(y, yh);
            label4->Location = System::Drawing::Point(z, zh);
        }
    }

    private: Label^ newLabel;


    private:
        System::Void OnMovementTimerTick(System::Object^ sender, System::EventArgs^ e) {
            // Assuming you have a label named newLabel
            if (newLabel != nullptr) {
                int newX = newLabel->Location.X + 5; // Move 5 pixels to the right
                if (newX > this->Width) { // Reset to left if it goes off-screen
                    newX = 0;
                }
                newLabel->Location = System::Drawing::Point(newX, newLabel->Location.Y);
            }
        }


    private:
        System::Void MyForm1_Resize(System::Object^ sender, System::EventArgs^ e) {
            try {
                txtps = this->Height - 83;
                txtps2 = this->Width - 245;
                txts = this->Height - 75;
                txts2 = this->Width - 300;
                msgp = this->Height - 85;
                msgp2 = this->Width - 200;
                msgs = this->Height - 77;
                msgs2 = this->Width - 80;
                ls = this->Width - 230;
                ms = this->Width - 675;

                CenterLabel();
                // Update the position of each TextBox
                for each (TextBox ^ textBox in textboxes)
                {
                    textBox->Location = System::Drawing::Point(250, txts);
                    textBox->Width = txts2;
                }
                // Update the position of each TextBox
                for each (Label ^ hedn in headnames)
                {
                    hedn->Width = ls;
                }

                // Update the position of message panel
                for each (Panel ^ mpanel in msgpanels)
                {
                    mpanel->Size = System::Drawing::Size(msgp2, msgp);
                }

                // Update the position of each addbutton
                for each (Button ^ addbutton in addButtons)
                {
                    addbutton->Location = System::Drawing::Point(msgs2, msgs);
                }

                // Update the position of each addbutton
                for each (PictureBox ^ txtpic in txtboxpic)
                {
                    txtpic->Location = System::Drawing::Point(200, txtps);
                    txtpic->Width = txtps2;
                }
                for each (Label ^ lb in messages) {
                    lb->Location = System::Drawing::Point(rightPosition - lb->Width + msgp2 - 500, lb->Top);
                }

            }
            catch (Exception^ ex) {}
        }


    private: System::Void MyForm1_FormClosing(System::Object^ sender, System::Windows::Forms::FormClosingEventArgs^ e) {
        if (MessageBox::Show("Do you want to exit?", "Exit", MessageBoxButtons::YesNo, MessageBoxIcon::Question) == System::Windows::Forms::DialogResult::Yes)
            e->Cancel = false;
        else
            e->Cancel = true;
    }

           void CreateNewPanel(String^ pername)
           {
               Panel^ newPanel = gcnew Panel();
               newPanel->Dock = System::Windows::Forms::DockStyle::Fill;
               newPanel->BackColor = System::Drawing::Color::FromArgb(29, 33, 36);
               newPanel->Size = System::Drawing::Size(300, 1);
               //newPanel->Location = System::Drawing::Point(200, 1);

               RoundedLabel^ label = gcnew RoundedLabel();
               label->Text = pername;
               label->Location = Point(195, 10);
               label->Font = gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12);
               label->AutoSize = false;
               label->Size = System::Drawing::Size(ls, 40);
               label->BackColor = System::Drawing::Color::FromArgb(30, 40, 55);
               label->ForeColor = Color::White;
               label->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;

               headnames->Add(label);


               PictureBox^ txtboxImage = gcnew PictureBox();
               txtboxImage->BackgroundImage = System::Drawing::Image::FromFile(L"D:/New folder (2)/Yapp!!/Yapp!!/textbox_img.png");
               txtboxImage->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
               txtboxImage->Location = System::Drawing::Point(200, txtps);
               txtboxImage->Name = L"txtboxImage";
               txtboxImage->Size = System::Drawing::Size(txtps2, 35);
               txtboxImage->TabIndex = 3;
               txtboxImage->TabStop = false;

               txtboxpic->Add(txtboxImage);


               TextBox^ textBox = gcnew TextBox();
               textBox->Font = gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11);
               textBox->Location = Point(220, txts);
               textBox->AutoSize = false;
               textBox->Size = System::Drawing::Size(txts2, 18);
               textBox->BackColor = System::Drawing::Color::FromArgb(49, 50, 70);
               textBox->ForeColor = System::Drawing::Color::White;
               textBox->Multiline = true;
               textBox->BorderStyle = System::Windows::Forms::BorderStyle::None;
               textBox->TextAlign = System::Windows::Forms::HorizontalAlignment::Left;

               textboxes->Add(textBox);


               Panel^ messagePanel = gcnew Panel();
               messagePanel->Location = Point(177, 50);
               messagePanel->Size = System::Drawing::Size(msgp2, msgp - 70);
               messagePanel->BackColor = System::Drawing::Color::FromArgb(29, 33, 36);
               messagePanel->ForeColor = System::Drawing::Color::FromArgb(103, 134, 252);
               messagePanel->AutoScroll = true; // Enable scrolling

               msgpanels->Add(messagePanel);


               RoundedButton^ addButton = gcnew RoundedButton();
               addButton->r = 10;
               addButton->Font = gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12);
               addButton->Location = Point(msgs2, msgs);
               addButton->Size = System::Drawing::Size(25, 23);
               addButton->BackColor = System::Drawing::Color::MediumSlateBlue;
               addButton->BackgroundImage = System::Drawing::Image::FromFile(L"D:/New folder (2)/Yapp!!/Yapp!!/send_img.png");
               addButton->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
               addButton->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
               addButton->Click += gcnew System::EventHandler(this, &MyForm1::addButton_Click);
               addButton->MouseEnter += gcnew System::EventHandler(this, &MyForm1::addButton_MouseEnter);
               addButton->MouseLeave += gcnew System::EventHandler(this, &MyForm1::addButton_MouseLeave);

               addButtons->Add(addButton);

               newPanel->Controls->Add(addButton);
               newPanel->Controls->Add(textBox);
               newPanel->Controls->Add(txtboxImage);
               newPanel->Controls->Add(label);
               newPanel->Controls->Add(messagePanel);
               newPanel->Controls->Add(this->label2);
               newPanel->Controls->Add(this->label3);
               newPanel->Controls->Add(this->label4);
               newPanel->Controls->Add(this->bckImage);

               panels->Add(newPanel);
               this->Controls->Add(newPanel);
               newPanel->Visible = false;

               CreateNavButton(panels->Count - 1, pername);
               this->buttonNext->BringToFront();

           }

           void MyForm1::buttonPanel_Scroll(System::Object^ sender, ScrollEventArgs^ e)
           {
               if (e->ScrollOrientation == ScrollOrientation::HorizontalScroll)
               {
                   buttonPanel->HorizontalScroll->Value = 0; // Reset horizontal scroll position to 0
               }
           }


           void CreateNavButton(int panelIndex, String^ pername)
           {
               bckImage->SendToBack();
               label2->SendToBack();
               label3->SendToBack();
               label4->SendToBack();
               RoundedButton^ navButton = gcnew RoundedButton();
               navButton->Font = gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15);
               navButton->Text = pername;
               navButton->Tag = panelIndex;

               navButton->Click += gcnew System::EventHandler(this, &MyForm1::navButton_Click);
               navButton->Size = System::Drawing::Size(150, 69);
               navButton->BackColor = System::Drawing::Color::FromArgb(49, 50, 70);
               navButton->ForeColor = System::Drawing::Color::White;
               navButton->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
               navButton->MouseEnter += gcnew System::EventHandler(this, &MyForm1::navButton_MouseEnter);
               navButton->MouseLeave += gcnew System::EventHandler(this, &MyForm1::navButton_MouseLeave);

               navButtons->Add(navButton);

               // Calculate the vertical offset
               int yOffset = 10; // Initial vertical offset
               for each (Button ^ btn in navButtons)
               {
                   yOffset += btn->Height + 10; // Add spacing between nav buttons
               }

               navButton->Location = Point(10, yOffset); // Set the horizontal and vertical position

               if (yOffset > buttonPanel->Height - 60)
                   this->buttonPanel->Size = System::Drawing::Size(181, 583);


               buttonPanel->Controls->Add(navButton);

           }



           void ResetNavButtonsColor()
           {
               for each (Button ^ btn in navButtons)
               {
                   btn->BackColor = System::Drawing::Color::FromArgb(49, 50, 70);
               }
           }

           System::Void buttonNext_Click(System::Object^ sender, System::EventArgs^ e)
           {
               if (currentPanelIndex >= 0 && currentPanelIndex < panels->Count)
               {
                   panels[currentPanelIndex]->Visible = false;
               }

               currentPanelIndex++;
               if (currentPanelIndex == panels->Count)
               {
                   CreateNewPanel(pername);
               }

               panels[currentPanelIndex]->Visible = true;
               ResetNavButtonsColor();
               navButtons[currentPanelIndex]->BackColor = System::Drawing::Color::MediumSlateBlue;
           }

           System::Drawing::Color navcolor;

           //event when mouse enter or leave the contact button
           System::Void navButton_MouseEnter(System::Object^ sender, System::EventArgs^ e) {
               Button^ clickedButton = safe_cast<Button^>(sender);
               int panelIndex = safe_cast<int>(clickedButton->Tag);
               navcolor = clickedButton->BackColor;
               if (clickedButton->BackColor != System::Drawing::Color::MediumSlateBlue)
                   clickedButton->BackColor = System::Drawing::Color::FromArgb(29, 33, 36);

           }
           System::Void navButton_MouseLeave(System::Object^ sender, System::EventArgs^ e) {
               Button^ clickedButton = safe_cast<Button^>(sender);
               int panelIndex = safe_cast<int>(clickedButton->Tag);
               if (clickedButton->BackColor != System::Drawing::Color::MediumSlateBlue)
                   clickedButton->BackColor = navcolor;

           }


           //event when mouse enter or leave the send button
           System::Void buttonNext_MouseEnter(System::Object^ sender, System::EventArgs^ e) {
               Button^ clickedButton = safe_cast<Button^>(sender);
               clickedButton->BackColor = System::Drawing::Color::SlateBlue;
           }
           System::Void buttonNext_MouseLeave(System::Object^ sender, System::EventArgs^ e) {
               Button^ clickedButton = safe_cast<Button^>(sender);
               clickedButton->BackColor = System::Drawing::Color::MediumSlateBlue;
           }


           //event when mouse enter or leave the add button
           System::Void addButton_MouseEnter(System::Object^ sender, System::EventArgs^ e) {
               Button^ clickedButton = safe_cast<Button^>(sender);
               clickedButton->BackColor = System::Drawing::Color::SlateBlue;
           }
           System::Void addButton_MouseLeave(System::Object^ sender, System::EventArgs^ e) {
               Button^ clickedButton = safe_cast<Button^>(sender);
               clickedButton->BackColor = System::Drawing::Color::MediumSlateBlue;
           }


           System::Void navButton_Click(System::Object^ sender, System::EventArgs^ e)
           {
               bckImage->SendToBack();
               label2->SendToBack();
               label3->SendToBack();
               label4->SendToBack();
               Button^ clickedButton = safe_cast<Button^>(sender);
               int panelIndex = safe_cast<int>(clickedButton->Tag);

               if (currentPanelIndex >= 0 && currentPanelIndex < panels->Count)
               {
                   panels[currentPanelIndex]->Visible = false;
               }

               currentPanelIndex = panelIndex;
               panels[currentPanelIndex]->Visible = true;

               ResetNavButtonsColor();
               clickedButton->BackColor = System::Drawing::Color::MediumSlateBlue;
           }
           Label^ ReceiveMessage(String^ replyText, int yPosition)
           {
               RoundedLabel^ reply = gcnew RoundedLabel();
               reply->r = 6;
               reply->Text = replyText;
               reply->Font = gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10);
               reply->ForeColor = System::Drawing::Color::White;
               reply->BackColor = System::Drawing::Color::FromArgb(30, 40, 55);
               reply->AutoSize = true;
               reply->TextAlign = System::Drawing::ContentAlignment::MiddleLeft; // Text alignment
               reply->Padding = System::Windows::Forms::Padding(5); // Add padding to the label for spacing

               // Set the label size based on its content
               System::Drawing::Size textSize = TextRenderer::MeasureText(reply->Text, reply->Font);
               reply->Size = System::Drawing::Size(textSize.Width + reply->Padding.Right + reply->Padding.Left, textSize.Height + reply->Padding.Top + reply->Padding.Bottom);

               // Set the location to be below the newLabel, on the left
               reply->Location = Point(20, yPosition);

               return reply;
           }



           System::Void addButton_Click(System::Object^ sender, System::EventArgs^ e)
           {
               bckImage->SendToBack();
               label2->SendToBack();
               label3->SendToBack();
               label4->SendToBack();
               Button^ clickedButton = safe_cast<Button^>(sender);
               Panel^ parentPanel = safe_cast<Panel^>(clickedButton->Parent);
               TextBox^ textBox = nullptr;

               // Find the TextBox and messagePanel in the parent panel
               for each (Control ^ ctrl in parentPanel->Controls)
               {
                   if (dynamic_cast<TextBox^>(ctrl) != nullptr)
                   {
                       textBox = safe_cast<TextBox^>(ctrl);
                   }
                   if (dynamic_cast<Panel^>(ctrl) != nullptr && ctrl->Location == Point(177, 50))
                   {
                       messagePanel = safe_cast<Panel^>(ctrl);
                   }
               }

               messagePanel->AutoScroll = true; // Enable auto-scrolling

               if (textBox != nullptr && messagePanel != nullptr && !String::IsNullOrWhiteSpace(textBox->Text))
               {
                   RoundedLabel^ newLabel = gcnew RoundedLabel();
                   newLabel->r = 6;
                   newLabel->Text = textBox->Text;
                   newLabel->Font = gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10);
                   newLabel->ForeColor = System::Drawing::Color::White;
                   newLabel->BackColor = System::Drawing::Color::MediumSlateBlue;
                   newLabel->AutoSize = true;
                   newLabel->TextAlign = System::Drawing::ContentAlignment::MiddleLeft; // Text alignment
                   newLabel->Padding = System::Windows::Forms::Padding(5); // Add padding to the label for spacing

                   textmsg = msclr::interop::marshal_as<std::string>(textBox->Text);

                   client.SendMsg();


                   // Calculate the position to ensure the right side is fixed
                   rightPosition = messagePanel->Width - ms; // Fixed right position
                   newLabel->AutoSize = true;
                   newLabel->AutoSize = false; // Set AutoSize to false after calculation

                   // Set the label size based on its content
                   System::Drawing::Size textSize = TextRenderer::MeasureText(newLabel->Text, newLabel->Font);
                   newLabel->Size = System::Drawing::Size(textSize.Width + newLabel->Padding.Right + newLabel->Padding.Left, textSize.Height + newLabel->Padding.Top + newLabel->Padding.Bottom);

                   // Calculate the position for the new label and reply label
                   currentY = 10; // Starting Y position for the first label



                   // Find the Y position for the new label based on existing labels
                   for each (Control ^ ctrl in messagePanel->Controls)
                   {
                       if (ctrl->Bottom > currentY)
                       {
                           currentY = ctrl->Bottom + 5; // Add some spacing between messages
                       }
                   }


                   newLabel->Location = System::Drawing::Point(rightPosition - newLabel->Width + messagePanel->Width - 500, currentY);

                   messages->Add(newLabel);


                   // Add the newLabel to the messagePanel
                   messagePanel->Controls->Add(newLabel);



                   newLabel->BringToFront(); // Make sure the new label is on top

                   // Scroll to the bottom to show the newly added label
                   messagePanel->ScrollControlIntoView(newLabel);

                   // Update the currentY position for the reply label
                   currentY = newLabel->Bottom + 10;
                   static int a = 0;
                   if (a == 1) {
                       // Create and add the reply label below the newLabel, on the left
                       Label^ reply = ReceiveMessage("kamehameha", currentY + 5);

                       // Add the reply label to the messagePanel
                       messagePanel->Controls->Add(reply);
                       reply->BringToFront(); // Make sure the reply label is on top

                       // Scroll to the bottom to show the newly added reply label
                       messagePanel->ScrollControlIntoView(reply);

                   }
                   messagePanel->ScrollControlIntoView(newLabel);
                   // Clear the textBox after adding the new message
                   textBox->Clear();
                   a++;

               }
           }
    };
}