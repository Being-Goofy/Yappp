#pragma once


using namespace System;
using namespace Threading;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;
using namespace System::Collections::Generic;
using namespace System::Drawing::Drawing2D;

public ref class RoundedLabel : public Label
{
public: float r = 15;
protected:
    virtual void OnPaint(PaintEventArgs^ e) override
    {
        // Define the button's rectangle
        System::Drawing::RectangleF rect = System::Drawing::RectangleF(-0.5, -0.5, static_cast<float>(this->Width), static_cast<float>(this->Height));
        float radius = r; // Adjust the radius to get rounded corners

        // Create a path with rounded corners
        System::Drawing::Drawing2D::GraphicsPath^ path = gcnew System::Drawing::Drawing2D::GraphicsPath();
        path->AddArc(rect.X, rect.Y, radius, radius, 180, 90);
        path->AddArc(rect.Right - radius, rect.Y, radius, radius, 270, 90);
        path->AddArc(rect.Right - radius, rect.Bottom - radius, radius, radius, 0, 90);
        path->AddArc(rect.X, rect.Bottom - radius, radius, radius, 90, 90);
        path->CloseAllFigures();

        // Set the button's region to the rounded rectangle
        this->Region = gcnew System::Drawing::Region(path);

        // Draw the background
        e->Graphics->SmoothingMode = System::Drawing::Drawing2D::SmoothingMode::AntiAlias;
        e->Graphics->FillPath(gcnew SolidBrush(this->BackColor), path);

        // Draw the image if there is one
        if (this->BackgroundImage != nullptr)
        {
            e->Graphics->DrawImage(this->BackgroundImage, System::Drawing::Rectangle::Round(rect));
        }

        // Draw the border
        System::Drawing::Pen^ pen = gcnew System::Drawing::Pen(System::Drawing::Color::FromArgb(0, 0, 0, 0), 2); // Transparent border
        e->Graphics->DrawPath(pen, path);

        // Draw the text
        TextRenderer::DrawText(e->Graphics, this->Text, this->Font, System::Drawing::Rectangle::Round(rect), this->ForeColor, TextFormatFlags::HorizontalCenter | TextFormatFlags::VerticalCenter);
    }

private:
    System::Drawing::Color originalBackColor;
    System::Drawing::Color hoverBackColor = System::Drawing::Color::FromArgb(49, 50, 70);

    void OnMouseEnter(System::Object^ sender, System::EventArgs^ e)
    {
        originalBackColor = this->BackColor;
        this->BackColor = hoverBackColor;
        this->Invalidate(); // Force the button to redraw itself
    }

    void OnMouseLeave(System::Object^ sender, System::EventArgs^ e)
    {
        if (!this->Focused) {
            this->BackColor = originalBackColor;
        }
        this->Invalidate(); // Force the button to redraw itself
    }
};



public ref class RoundedButton : public Button
{
public: float r = 10;
protected:
    virtual void OnPaint(PaintEventArgs^ e) override
    {
        // Define the button's rectangle
        System::Drawing::RectangleF rect = System::Drawing::RectangleF(-0.5, -0.5, static_cast<float>(this->Width), static_cast<float>(this->Height));
        float radius = r; // Adjust the radius to get rounded corners

        // Create a path with rounded corners
        System::Drawing::Drawing2D::GraphicsPath^ path = gcnew System::Drawing::Drawing2D::GraphicsPath();
        path->AddArc(rect.X, rect.Y, radius, radius, 180, 90);
        path->AddArc(rect.Right - radius, rect.Y, radius, radius, 270, 90);
        path->AddArc(rect.Right - radius, rect.Bottom - radius, radius, radius, 0, 90);
        path->AddArc(rect.X, rect.Bottom - radius, radius, radius, 90, 90);
        path->CloseAllFigures();

        // Set the button's region to the rounded rectangle
        this->Region = gcnew System::Drawing::Region(path);

        // Draw the background
        e->Graphics->SmoothingMode = System::Drawing::Drawing2D::SmoothingMode::AntiAlias;
        e->Graphics->FillPath(gcnew SolidBrush(this->BackColor), path);

        // Draw the image if there is one
        if (this->BackgroundImage != nullptr)
        {
            e->Graphics->DrawImage(this->BackgroundImage, System::Drawing::Rectangle::Round(rect));
        }

        // Draw the border
        System::Drawing::Pen^ pen = gcnew System::Drawing::Pen(System::Drawing::Color::FromArgb(0, 0, 0, 0), 2); // Transparent border
        e->Graphics->DrawPath(pen, path);

        // Draw the text
        TextRenderer::DrawText(e->Graphics, this->Text, this->Font, System::Drawing::Rectangle::Round(rect), this->ForeColor, TextFormatFlags::HorizontalCenter | TextFormatFlags::VerticalCenter);
    }

private:
    System::Drawing::Color originalBackColor;
    System::Drawing::Color hoverBackColor = System::Drawing::Color::FromArgb(49, 50, 70);

    void OnMouseEnter(System::Object^ sender, System::EventArgs^ e)
    {
        originalBackColor = this->BackColor;
        this->BackColor = hoverBackColor;
        this->Invalidate(); // Force the button to redraw itself
    }

    void OnMouseLeave(System::Object^ sender, System::EventArgs^ e)
    {
        if (!this->Focused) {
            this->BackColor = originalBackColor;
        }
        this->Invalidate(); // Force the button to redraw itself
    }
};