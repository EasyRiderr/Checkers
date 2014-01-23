/*
 * clickablelabel.h
 * A QLabel that we can click on ==> emit a clicked signal.
 *
 * @author Yoan DUMAS
 * @version 1.0
 * @date 21/01/2014
 */


#ifndef CLICKABLELABEL_H
#define CLICKABLELABEL_H

#include <QLabel>
#include "rules.h"

class ClickableLabel : public QLabel
{

    Q_OBJECT


public:
    explicit ClickableLabel(const QString& text ="", QWidget * parent = 0 );
    ClickableLabel(position_t pos);
   ~ClickableLabel();

signals:
   void clicked(position_t pos);

protected:
   void mouseReleaseEvent(QMouseEvent * event );

private:
    position_t pos_;
};

#endif // CLICKABLELABEL_H
