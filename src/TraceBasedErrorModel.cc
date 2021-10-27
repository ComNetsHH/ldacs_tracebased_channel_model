#include "inet/physicallayer/base/packetlevel/FlatTransmissionBase.h"
#include <iostream>
#include <fstream>
#include <string>
#include "TraceBasedErrorModel.h"
#include <algorithm>
#include <vector>

using namespace std;
using namespace inet::physicallayer;
using namespace inet;

Define_Module(TraceBasedErrorModel);

TraceBasedErrorModel::TraceBasedErrorModel() :
        TraceFileName()
{
}

int line_number;
vector<vector<double>> SNR_to_PER_array;

void TraceBasedErrorModel::initialize(int stage)
{
    SNR_Vector.setName("Signal-to-Noise_Ratio");

    if (stage == INITSTAGE_LOCAL) {

        //reading the .txt file to read SNR to PER
             int position_of_first_comma,position_of_second_comma,searching_position_output_textfile,position_at_output_textfile,assigning_position_PER,assigning_position_SNR;

             // Creating a text string, which is used to output the text file
             string output_textfile;

             string file_name = par("TraceFileName");

             // Read from the text file
             ifstream MyReadFile(file_name);
             line_number=0;
             // Using a while loop together with the getline() function to read the file line by line
             while (getline (MyReadFile, output_textfile)) {

                 // finding the position of the first ","
                 for( searching_position_output_textfile = 0; searching_position_output_textfile < output_textfile.length(); searching_position_output_textfile++){
                     if(output_textfile[searching_position_output_textfile]==','){
                         position_of_first_comma = searching_position_output_textfile;
                         break;
                     }
                 }

                 // finding the position of the second ","
                 for( searching_position_output_textfile = searching_position_output_textfile+1; searching_position_output_textfile < output_textfile.length(); searching_position_output_textfile++){
                     if(output_textfile[searching_position_output_textfile]==','){
                         position_of_second_comma = searching_position_output_textfile;
                     }
                 }

                 char SNR_Part[position_of_first_comma];
                 char PER_Part[position_of_second_comma-position_of_first_comma];

                 //assigning the SNR part of the text file into array SNR_to_PER_array
                 position_at_output_textfile=0;
                 for(assigning_position_SNR = 0;assigning_position_SNR<position_of_first_comma;assigning_position_SNR++){
                     SNR_Part[assigning_position_SNR]=output_textfile[position_at_output_textfile];
                     position_at_output_textfile++;
                 }
                 SNR_Part[assigning_position_SNR]='\0';
                 vector<double> temp;
                 // convert string to double
                 temp.push_back(std::stod(SNR_Part));
                 position_at_output_textfile++;

                 //assigning the PER part of the text file into array SNR_to_PER_array
                 for( assigning_position_PER=0;assigning_position_PER<position_of_second_comma-position_of_first_comma-1;assigning_position_PER++){
                     PER_Part[assigning_position_PER]=output_textfile[position_at_output_textfile];
                     position_at_output_textfile++;
                 }
                 PER_Part[assigning_position_PER]='\0';
                 temp.push_back(std::stod(PER_Part));
                 SNR_to_PER_array.push_back(temp);
                 temp.clear();
                 line_number++;

             }
             // Closing the file
             MyReadFile.close();
    }

}

std::ostream& TraceBasedErrorModel::printToStream(std::ostream& stream, int level) const
{
    if (level <= PRINT_LEVEL_TRACE)
        stream << "TraceBasedErrorModel"
               << "TraceFileName = " << TraceFileName;
    return stream;
}


/*This additional find_max_value method takes an array as input and looks for the maximum number
 * in that given array.
 */
double TraceBasedErrorModel::find_max_value(vector<vector<double>> array){
    double max= array[0][0];
    for (int j = 1; j < line_number; j++)
            {
                if (array[j][0] > max)
                   max = array[j][0];
            }
    return max;
}
/*This additional find_min_value method takes an array as input and looks for the minimum number
 * in that given array.
 */
double TraceBasedErrorModel::find_min_value(vector<vector<double>> array){
    double min= array[0][0];
    for (int j = 1; j < line_number; j++)
            {
                if (array[j][0] < min)
                   min = array[j][0];
            }
    return min;
}

double TraceBasedErrorModel::snrToPacketErrorRateMapping(double SNR)
{
    Enter_Method_Silent();

    //Rounding to nearest neighbor
    SNR = round(SNR);

    //recording SNR for analysis
    SNR_Vector.record(SNR);

    //Taking care of the edges(SNR)
    double min_SNR,max_SNR;
    max_SNR=find_max_value(SNR_to_PER_array);
    min_SNR=find_min_value(SNR_to_PER_array);

    if(SNR > max_SNR)
        SNR = max_SNR;     //rounding to the highest SNR value when SNR is greater than the possible highest value
    else if(SNR <min_SNR)
        SNR = min_SNR;     //rounding to the lowest SNR value when SNR is smaller than the possible lowest value

    //finding the corresponding PER of the current SNR
    double PER;
    for(int k=0; k<line_number;k++){
        if(SNR_to_PER_array[k][0]== SNR){
            PER = SNR_to_PER_array[k][1];
            break;
        }
    }

    return PER;
}

double TraceBasedErrorModel::snrToBitErrorRateMapping(double SNR)
{
// TODO: map to corresponding bit error rate  for the given SNR
//       use the trace file to find the Bit error rate
//       Not yet implemented;
}
double TraceBasedErrorModel::computePacketErrorRate(const ISnir *test_snir, IRadioSignal::SignalPart part) const
{
    Enter_Method_Silent();
    return 0;
}

double TraceBasedErrorModel::computeBitErrorRate(const ISnir *snir, IRadioSignal::SignalPart part) const
{
    Enter_Method_Silent();
    return 0;
}

double TraceBasedErrorModel::computeSymbolErrorRate(const ISnir *snir, IRadioSignal::SignalPart part) const
{
    Enter_Method_Silent();
    return 0;
}
