#ifndef TEXTEDITOR_H
#define TEXTEDITOR_H

#include <QMainWindow>
#include "calculator.h"

QT_BEGIN_NAMESPACE
namespace Ui { class TextEditor; }
QT_END_NAMESPACE

class TextEditor : public QMainWindow
{
    Q_OBJECT

public:
    TextEditor(QWidget *parent = nullptr);
    ~TextEditor();

private slots:
    void on_actionNew_triggered();
    void on_actionOpen_triggered();
    void on_actionSave_triggered();
    void on_actionSave_As_triggered();
    void on_actionCut_triggered();
    void on_actionCopy_triggered();
    void on_actionPaste_triggered();
    void on_actionRedo_triggered();
    void on_actionUndo_triggered();
    void on_actionAbout_TextEditor_triggered();
    void on_actionFont_triggered();
    void on_actionColor_triggered();
    void on_actionBold_triggered();
    void on_actionItalic_triggered();
    void on_actionUnderline_triggered();
    void on_actionZoom_In_triggered();
    void on_actionZoom_Out_triggered();
    void on_actionHighlight_Text_triggered();
    void on_actionArabic_2_triggered();

    void on_actionDots_triggered();

    void on_actionDisc_triggered();

    void on_actionSquare_triggered();

    void on_actionUppercase_triggered();

    void on_actionLowercase_triggered();

    void on_actionUpperCase_Roman_triggered();

    void on_actionLowerCase_Roman_triggered();

    void on_actionBackground_Color_triggered();

    void on_actionPrint_triggered();

    void on_actionLeft_triggered();

    void on_actionRight_triggered();

    void on_actionCenter_triggered();

    void on_actionJustify_triggered();

    void on_actionCalculator_triggered();

private:
    Ui::TextEditor *ui;
    QString file_path_;
    Calculator *calculator;
};
#endif // TEXTEDITOR_H
