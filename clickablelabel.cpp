/*
 * clickablelabel.cpp
 * A QLabel that we can click on ==> emit a clicked signal.
 *
 * @author Yoan DUMAS
 * @version 1.0
 * @date 21/01/2014
 */


#include "clickablelabel.h"


ClickableLabel::ClickableLabel(position_t pos){
    pos_ = pos;
}


ClickableLabel::ClickableLabel(const QString& text, QWidget * parent) :
    QLabel(parent)
{
    this->setText(text);
    pos_ = (position_t) {-1, -1};
}

ClickableLabel::~ClickableLabel()
{
}

void ClickableLabel::mouseReleaseEvent (QMouseEvent * event)
{
    emit clicked(pos_);
}
