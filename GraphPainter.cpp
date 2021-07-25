#include "GraphPainter.h"

GraphPainter::GraphPainter(DataDecoder* pDecoder, QWidget* parent):QWidget(parent)
{
    m_pDecoder = pDecoder;
}

/* To draw the graph, calculate the coordinate in pixels for each point */
void GraphPainter::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    if(m_pDecoder != nullptr)
    {
        const auto& crGraphData = m_pDecoder->getGraphData();
        if(!crGraphData.m_vecPoints.empty())
        {
            auto iteratorBeg = crGraphData.m_vecPoints.begin();
            auto iteratorEnd = crGraphData.m_vecPoints.end();

            auto iteratorPrev = m_pDecoder->getGraphData().m_vecPoints.begin();
            ++iteratorBeg;

            while(iteratorBeg != iteratorEnd)
            {

                int x1 = width()*(iteratorPrev->first - crGraphData.m_dMinTime)/(crGraphData.m_dMaxTime-crGraphData.m_dMinTime);
                int x2 = width()*(iteratorBeg->first- crGraphData.m_dMinTime)/(crGraphData.m_dMaxTime-crGraphData.m_dMinTime);


                int y1 = height() - height()*(iteratorPrev->second-crGraphData.m_dMinValue)/(crGraphData.m_dMaxValue-crGraphData.m_dMinValue);
                int y2 = height() - height()*(iteratorBeg->second-crGraphData.m_dMinValue)/(crGraphData.m_dMaxValue-crGraphData.m_dMinValue);

                if(!((x1 == x2) && (y1 == y2)))
                {
                    painter.drawLine(QPoint(x1, y1), QPoint(x2, y2));
                    iteratorPrev =iteratorBeg;
                }

                ++iteratorBeg;

            }
        }

    }
    QWidget::paintEvent(event);

}
