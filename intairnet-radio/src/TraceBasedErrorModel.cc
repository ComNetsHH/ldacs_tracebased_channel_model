#include "inet/physicallayer/base/packetlevel/FlatTransmissionBase.h"
#include <iostream>
#include <fstream>
#include <string>
#include "TraceBasedErrorModel.h"

using namespace std;
using namespace inet::physicallayer;
using namespace inet;

Define_Module(TraceBasedErrorModel);

TraceBasedErrorModel::TraceBasedErrorModel() :
    packetErrorRate(NaN),
    bitErrorRate(NaN),
    symbolErrorRate(NaN),
    SNR(NaN)
{
}

int line_number=0;
double SNR_to_PER_array[100][3];

void TraceBasedErrorModel::initialize(int stage)
{
    if (stage == INITSTAGE_LOCAL) {
        packetErrorRate = par("packetErrorRate");
        bitErrorRate = par("bitErrorRate");
        symbolErrorRate = par("symbolErrorRate");
        SNR = par("SNR");

        //reading the .txt file to read SNR to PER
             int f,g,i,j,q,n;
             int z;

             // Creating a text string, which is used to output the text file
             string myText;

             // Read from the text file
             ifstream MyReadFile("per_snr.txt");

             // Use a while loop together with the getline() function to read the file line by line
             while (getline (MyReadFile, myText)) {

                 // finding the position of the first ","
                 for( i = 0; i < myText.length(); i++){
                     if(myText[i]==','){
                         f = i;
                         break;
                     }
                 }

                 // finding the position of the second ","
                 for( j = i+1; j < myText.length(); j++){
                     if(myText[j]==','){
                         g = j;
                     }
                 }

                 char temp[f];
                 char temp2[g-f];

                 //assigning the SNR part of the text file into array SNR_to_PER_array
                 for( q=0;q<f;q++){
                     temp[q]=myText[q];
                 }
                 temp[q]='\0';
                 // convert string to double
                 SNR_to_PER_array[line_number][0]= std::stod(temp);
                 q++;

                 //asinging the SNR part of the text file into array SNR_to_PER_array
                 for( i=0;i<g-f-1;i++){
                     temp2[i]=myText[q];
                     q++;
                 }
                 temp2[i]='\0';
                 SNR_to_PER_array[line_number][1]= std::stod(temp2);
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
               << "packetErrorRate = " << packetErrorRate
               << "bitErrorRate = " << bitErrorRate
               << "symbolErrorRate = " << symbolErrorRate
               << "SNR = " << SNR;
    return stream;
}

double TraceBasedErrorModel::snrToPacketErrorRateMapping(double SNR)
{
    Enter_Method_Silent();

    //Rounding to nearest neighbor
    SNR = round(SNR);

    //recording each SNR for analysis
    recordScalar("#Signal-to-Noise_Ratio",SNR);

    //Taking care of the edges(SNR)
    if(SNR > 10)
        SNR = 10;     //since 10 is the largest SNR value in .csv
    else if(SNR <-4)
        SNR = -4;    //since -4 is the smallest possible SNR value within distance < Radio horizon

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

double TraceBasedErrorModel::computePacketErrorRate(const ISnir *test_snir, IRadioSignal::SignalPart part) const
{
    Enter_Method_Silent();
    return packetErrorRate;
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
