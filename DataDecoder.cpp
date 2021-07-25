#include "DataDecoder.h"
#include <fstream>
#include <QString>
#include <algorithm>


uint16_t DataDecoder::load(const std::string& strPathToFile)
{
    uint16_t res = 0;

    std::ifstream fin(strPathToFile.data());
    if(!fin.is_open())
    {
        res = 0x01;
        return res;
    }

    double dMaxtime = 0;
    double dMinTime = std::numeric_limits<double>::max();

    double dMaxValue = 0;
    double dMinValue = std::numeric_limits<double>::max();

    size_t numOfElem = 0;

    std::string     myStr;

    if(fin)
    {
        while(getline(fin, myStr))
        {
            if((myStr.empty()) || (myStr == "\r"))
            {
                continue;
            }
            if(!isdigit(myStr[0]) && (myStr[0] != '#'))
            {
                res = 0x02;
                return res;
            }
            if(isdigit(myStr[0]))
            {
                size_t pos = myStr.find_first_of(" ");
                QString s1 = myStr.substr(0, pos).data();
                QString s2 = myStr.substr(pos + 1, myStr.length()-pos).data();
                bool bOk;
                double dTime = s1.toDouble(&bOk);
                double dValue = s2.toDouble(&bOk);
                if(bOk == false)
                {
                    res = 0x04;
                    return res;
                }

                if(dTime > dMaxtime)
                {
                    dMaxtime = dTime;
                }
                if(dValue > dMaxValue)
                {
                    dMaxValue = dValue;
                }
                if(dMinValue > dValue)
                {
                    dMinValue = dValue;
                }
                if(dMinTime > dTime)
                {
                    dMinTime = dTime;
                }
                ++numOfElem;

            }
        }
    }
    if(numOfElem == 0)
    {
        res = 0x08;
        return res;
    }

    fin.clear();
    fin.seekg(std::ios::beg);

    m_GraphData.m_vecPoints.reserve(numOfElem);

    m_GraphData.m_dMaxTime = dMaxtime;
    m_GraphData.m_dMinTime = dMinTime;

    m_GraphData.m_dMaxValue = dMaxValue;
    m_GraphData.m_dMinValue = dMinValue;

    if(fin)
    {
        while(getline(fin, myStr))
        {
            if(isdigit(myStr[0]))
            {
                size_t pos = myStr.find_first_of(" ");
                QString s1 = myStr.substr(0, pos).data();
                QString s2 = myStr.substr(pos + 1, myStr.length()-pos).data();
                m_GraphData.m_vecPoints.emplace_back(std::make_pair(s1.toDouble(), s2.toDouble()));

            }
        }
    }
return 0;
};

const GraphData& DataDecoder:: getGraphData()
{
    return m_GraphData;
};
void DataDecoder::Clear()
{
    m_GraphData.m_vecPoints.clear();
}
