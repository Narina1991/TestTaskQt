#ifndef DATADECODER_H
#define DATADECODER_H
#include <vector>
#include <string>

/*The structure contains the decoded data needed to draw the graph */
struct GraphData
{
    std::vector<std::pair<double,double>> m_vecPoints;

    double m_dMaxTime = 0;
    double m_dMinTime = 0;
    double m_dMaxValue = 0;
    double m_dMinValue = 0;
};

/* The class loads the given data from the file */
class DataDecoder
{
    GraphData m_GraphData;
public:
   uint16_t load(const std::string& strPathToFile);
   const GraphData& getGraphData();
   void Clear();

};
#endif // DATADECODER_H
