#ifndef GRAPHPAINTER_H
#define GRAPHPAINTER_H
#include <QWidget>
#include <QPainter>
#include <DataDecoder.h>

class GraphPainter: public QWidget
{
    DataDecoder* m_pDecoder = nullptr;
public:
    GraphPainter( DataDecoder* pDecoder = nullptr, QWidget* parent = nullptr);
protected:
    void paintEvent(QPaintEvent *event);  
};
#endif // GRAPHPAINTER_H
