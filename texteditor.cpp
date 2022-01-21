#include "texteditor.h"
#include "ui_texteditor.h"
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include <QFont>
#include <QColor>
#include <QColorDialog>
#include <QFontDialog>
#include <QTextCursor>
#include <QTextList>
#include <QPrinter>
#include <QPrintDialog>
#include "calculator.h"

static bool bold = false;
static bool underline = false;
static bool italic = false;

TextEditor::TextEditor(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::TextEditor)
{
    ui->setupUi(this);
    this->setCentralWidget(ui->textEdit);

}

TextEditor::~TextEditor()
{
    delete ui;
}

//New blank file
void TextEditor::on_actionNew_triggered()
{
    file_path_ = "";
    ui->textEdit->setText("");
}

//Open file
void TextEditor::on_actionOpen_triggered()
{
    QString file_name = QFileDialog::getOpenFileName(this, "Open this File");
    QFile file(file_name); //constructor
    file_path_ = file_name;
    if(!file.open(QFile::ReadOnly | QFile::Text)){
        QMessageBox::warning(this, "Alert", "File Not Open!");
        return;
    }
    QTextStream in(&file);
    QString text = in.readAll();
    ui->textEdit->setText(text);
    file.close();
}

//Save changes
void TextEditor::on_actionSave_triggered()
{
    QFile file(file_path_); //constructor
    if(!file.open(QFile::WriteOnly | QFile::Text)){
        QMessageBox::warning(this, "Alert", "File not open! Check if it is created and saved before");
        return;
    }
    QTextStream out(&file);
    QString text = ui->textEdit->toHtml();
    out << text;
    file.flush();
    file.close();
    QMessageBox::information(this, "Success", "Changes Saved Successfully");

}

//Save the file with a name
void TextEditor::on_actionSave_As_triggered()
{
    QString file_name = QFileDialog::getSaveFileName(this, "Save this File");
    QFile file(file_name); //constructor
    file_path_ = file_name;
    if(!file.open(QFile::WriteOnly | QFile::Text)){
        QMessageBox::warning(this, "Alert", "File Not Open!");
        return;
    }
    QTextStream out(&file);
    QString text = ui->textEdit->toHtml();
    out << text;
    file.flush();
    file.close();
    QMessageBox::information(this, "Success", "File Saved Successfully");
}

//Cut text
void TextEditor::on_actionCut_triggered()
{
    ui->textEdit->cut();
}

//Copy text
void TextEditor::on_actionCopy_triggered()
{
    ui->textEdit->copy();
}

//Paste text
void TextEditor::on_actionPaste_triggered()
{
    ui->textEdit->paste();
}

//Redo
void TextEditor::on_actionRedo_triggered()
{
    ui->textEdit->redo();
}

//Undo
void TextEditor::on_actionUndo_triggered()
{
    ui->textEdit->undo();
}

//Get Application About
void TextEditor::on_actionAbout_TextEditor_triggered()
{
    QString txtAbout;
    txtAbout = "<b>About</b>: Hi! Welcome to Noteculator.\n";
    txtAbout += "Noteculator is a text editor that helps you to edit and format text documents, save them etc. with a calculator that would be benefitable for budget planning, academic purposes, and any other basic mathematical operations while you document. \n";
    txtAbout += "<b>Created By</b>: H. Tharushi Kavinya De Silva";

    QMessageBox::about(this, "About Noteculator", txtAbout);

}

//Change font style
void TextEditor::on_actionFont_triggered()
{
    bool ok;
    QFont fontStyle = QFontDialog::getFont(&ok, QFont("Helvetica [Cronyx]", 10), this);
    if (ok) {
        ui->textEdit->setFont(fontStyle);
        // the user clicked OK and font is set to the font the user selected
    } else
        return;

}

//Change font color
void TextEditor::on_actionColor_triggered()
{
    QColor fontColor = QColorDialog::getColor(Qt::white, this, "Select a Color");
    if(fontColor.isValid()){
        ui->textEdit->setTextColor(fontColor);
    }
}

//Format text bold
void TextEditor::on_actionBold_triggered()
{
    if(!bold){
        ui->textEdit->setFontWeight(QFont::Bold);
        bold=true;
    }
    else{
        ui->textEdit->setFontWeight(QFont::Normal);
        bold=false;
    }

}

//Format text to Italic
void TextEditor::on_actionItalic_triggered()
{
    if(!italic){
        ui->textEdit->setFontItalic(true);
        italic=true;
    }
    else{
        ui->textEdit->setFontItalic(false);
        italic=false;
    }

}

//Format text to underlined
void TextEditor::on_actionUnderline_triggered()
{
    if(!underline){
        ui->textEdit->setFontUnderline(true);
        underline=true;
    }
    else{
        ui->textEdit->setFontUnderline(false);
        underline=false;
    }
}

//Zoom in
void TextEditor::on_actionZoom_In_triggered()
{
    ui->textEdit->zoomIn();
}

//Zoom out
void TextEditor::on_actionZoom_Out_triggered()
{
    ui->textEdit->zoomOut();
}

//Highlight Text
void TextEditor::on_actionHighlight_Text_triggered()
{
    QColor highlightColor = QColorDialog::getColor(Qt::white, this, "Choose a Color");
    if(highlightColor.isValid()){
        ui->textEdit->setTextBackgroundColor(highlightColor);
    }

}

//Arabic Numeric Bulleting
void TextEditor::on_actionArabic_2_triggered()
{
    QTextCursor txtCursor = ui->textEdit->textCursor(); //get cursor
    QTextListFormat::Style txtListStyle = QTextListFormat::ListDecimal; //formatting using ListDecimal

    txtCursor.beginEditBlock();
    QTextBlockFormat txtBlockFormat = txtCursor.blockFormat();
    QTextListFormat txtListFormat;

    //check current list
    if(txtCursor.currentList())
    {
        txtListFormat= txtCursor.currentList()->format();
         } else
    {
        txtListFormat.setIndent(txtBlockFormat.indent()+1);
        txtBlockFormat.setIndent(0);
        txtCursor.setBlockFormat(txtBlockFormat);
    }
    txtListFormat.setStyle(txtListStyle);
    txtCursor.createList(txtListFormat);
    txtCursor.endEditBlock();
}

//Dot Bullets
void TextEditor::on_actionDots_triggered()
{
    QTextCursor txtCursor = ui->textEdit->textCursor(); //get cursor
    QTextListFormat::Style txtListStyle = QTextListFormat::ListDisc; //formatting using ListCircles

    txtCursor.beginEditBlock();
    QTextBlockFormat txtBlockFormat = txtCursor.blockFormat();
    QTextListFormat txtListFormat;

    //check current list
    if(txtCursor.currentList())
    {
        txtListFormat= txtCursor.currentList()->format();
         } else
    {
        txtListFormat.setIndent(txtBlockFormat.indent()+1);
        txtBlockFormat.setIndent(0);
        txtCursor.setBlockFormat(txtBlockFormat);
    }
    txtListFormat.setStyle(txtListStyle);
    txtCursor.createList(txtListFormat);
    txtCursor.endEditBlock();

}

//Disc Bullets
void TextEditor::on_actionDisc_triggered()
{
    QTextCursor txtCursor = ui->textEdit->textCursor(); //get cursor
    QTextListFormat::Style txtListStyle = QTextListFormat::ListCircle; //formatting using ListDisc

    txtCursor.beginEditBlock();
    QTextBlockFormat txtBlockFormat = txtCursor.blockFormat();
    QTextListFormat txtListFormat;

    //check current list
    if(txtCursor.currentList())
    {
        txtListFormat= txtCursor.currentList()->format();
         } else
    {
        txtListFormat.setIndent(txtBlockFormat.indent()+1);
        txtBlockFormat.setIndent(0);
        txtCursor.setBlockFormat(txtBlockFormat);
    }
    txtListFormat.setStyle(txtListStyle);
    txtCursor.createList(txtListFormat);
    txtCursor.endEditBlock();
}

//Square Bullets
void TextEditor::on_actionSquare_triggered()
{
    QTextCursor txtCursor = ui->textEdit->textCursor(); //get cursor
    QTextListFormat::Style txtListStyle = QTextListFormat::ListSquare; //formatting using ListSquare

    txtCursor.beginEditBlock();
    QTextBlockFormat txtBlockFormat = txtCursor.blockFormat();
    QTextListFormat txtListFormat;

    //check current list
    if(txtCursor.currentList())
    {
        txtListFormat= txtCursor.currentList()->format();
         } else
    {
        txtListFormat.setIndent(txtBlockFormat.indent()+1);
        txtBlockFormat.setIndent(0);
        txtCursor.setBlockFormat(txtBlockFormat);
    }
    txtListFormat.setStyle(txtListStyle);
    txtCursor.createList(txtListFormat);
    txtCursor.endEditBlock();

}

//Uppercase Alphabetic Bullets
void TextEditor::on_actionUppercase_triggered()
{
    QTextCursor txtCursor = ui->textEdit->textCursor(); //get cursor
    QTextListFormat::Style txtListStyle = QTextListFormat::ListUpperAlpha; //formatting using ListUpperAlpha

    txtCursor.beginEditBlock();
    QTextBlockFormat txtBlockFormat = txtCursor.blockFormat();
    QTextListFormat txtListFormat;

    //check current list
    if(txtCursor.currentList())
    {
        txtListFormat= txtCursor.currentList()->format();
         } else
    {
        txtListFormat.setIndent(txtBlockFormat.indent()+1);
        txtBlockFormat.setIndent(0);
        txtCursor.setBlockFormat(txtBlockFormat);
    }
    txtListFormat.setStyle(txtListStyle);
    txtCursor.createList(txtListFormat);
    txtCursor.endEditBlock();
}

//Lowercase Alphabetic Bullets
void TextEditor::on_actionLowercase_triggered()
{
    QTextCursor txtCursor = ui->textEdit->textCursor(); //get cursor
    QTextListFormat::Style txtListStyle = QTextListFormat::ListLowerAlpha; //formatting using ListLowerAlpha

    txtCursor.beginEditBlock();
    QTextBlockFormat txtBlockFormat = txtCursor.blockFormat();
    QTextListFormat txtListFormat;

    //check current list
    if(txtCursor.currentList())
    {
        txtListFormat= txtCursor.currentList()->format();
         } else
    {
        txtListFormat.setIndent(txtBlockFormat.indent()+1);
        txtBlockFormat.setIndent(0);
        txtCursor.setBlockFormat(txtBlockFormat);
    }
    txtListFormat.setStyle(txtListStyle);
    txtCursor.createList(txtListFormat);
    txtCursor.endEditBlock();
}

//Roman Numerals Upper Case
void TextEditor::on_actionUpperCase_Roman_triggered()
{
    QTextCursor txtCursor = ui->textEdit->textCursor(); //get cursor
    QTextListFormat::Style txtListStyle = QTextListFormat::ListUpperRoman; //formatting using ListUpperRoman

    txtCursor.beginEditBlock();
    QTextBlockFormat txtBlockFormat = txtCursor.blockFormat();
    QTextListFormat txtListFormat;

    //check current list
    if(txtCursor.currentList())
    {
        txtListFormat= txtCursor.currentList()->format();
         } else
    {
        txtListFormat.setIndent(txtBlockFormat.indent()+1);
        txtBlockFormat.setIndent(0);
        txtCursor.setBlockFormat(txtBlockFormat);
    }
    txtListFormat.setStyle(txtListStyle);
    txtCursor.createList(txtListFormat);
    txtCursor.endEditBlock();
}

//Roman Numerals Lower Case
void TextEditor::on_actionLowerCase_Roman_triggered()
{
    QTextCursor txtCursor = ui->textEdit->textCursor(); //get cursor
    QTextListFormat::Style txtListStyle = QTextListFormat::ListLowerRoman; //formatting using ListLowerRoman

    txtCursor.beginEditBlock();
    QTextBlockFormat txtBlockFormat = txtCursor.blockFormat();
    QTextListFormat txtListFormat;

    //check current list
    if(txtCursor.currentList())
    {
        txtListFormat= txtCursor.currentList()->format();
         } else
    {
        txtListFormat.setIndent(txtBlockFormat.indent()+1);
        txtBlockFormat.setIndent(0);
        txtCursor.setBlockFormat(txtBlockFormat);
    }
    txtListFormat.setStyle(txtListStyle);
    txtCursor.createList(txtListFormat);
    txtCursor.endEditBlock();
}

//TextEditor Background to Black
void TextEditor::on_actionBackground_Color_triggered()
{
    QColor bgColor = QColorDialog::getColor(Qt::white, this,"Choose black as editing pane background color");
     if(bgColor.isValid()) {
         ui->textEdit->setPalette(QPalette(bgColor));
       }
}

//Print
void TextEditor::on_actionPrint_triggered()
{
      QPrinter printer;
      printer.setPrinterName("Print File");
      QPrintDialog dialog(&printer,this);
      if(dialog.exec() == QDialog::Rejected) {
          QMessageBox::warning(this, "Alert", "Couldn't access the printer");
          return;
      }
      ui->textEdit->print(&printer);
}

//Alignments

void TextEditor::on_actionLeft_triggered()
{
    ui->textEdit->setAlignment(Qt::AlignLeft);
}


void TextEditor::on_actionRight_triggered()
{
    ui->textEdit->setAlignment(Qt::AlignRight);
}


void TextEditor::on_actionCenter_triggered()
{
    ui->textEdit->setAlignment(Qt::AlignCenter);
}


void TextEditor::on_actionJustify_triggered()
{
    ui->textEdit->setAlignment(Qt::AlignJustify);
}

//Get Calculator
void TextEditor::on_actionCalculator_triggered()
{
    calculator = new Calculator(this);
    calculator->show();


}

