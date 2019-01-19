#ifndef _AUTO_FILL_EDIT_H_
#define _AUTO_FILL_EDIT_H_

#include <qlineedit.h>
#include <QKeyEvent>

class AutoFillEdit : public QLineEdit
{
public:
    AutoFillEdit(QWidget* parent=NULL, const char* name=NULL) : QLineEdit(parent, name) {}
    
protected:
    virtual void keyPressEvent(QKeyEvent* event)
    {
	if(event->key() == Qt::Key_Backspace && hasSelectedText())
	{
	    int startIndex = selectionStart();
	
	    if(startIndex > 0)
	    {
		setText(text().left(startIndex - 1));
	    }
	    else
	    {
		setText("");
	    }
	}
	else
	{
	    QLineEdit::keyPressEvent(event);
	}
    }
};

#endif
