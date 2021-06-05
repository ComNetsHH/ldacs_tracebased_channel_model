#include "UnitDiskRadioCustomized.h"
#include "inet/common/ProtocolTag_m.h"
#include "inet/common/packet/Packet.h"
#include "inet/common/packet/chunk/ByteCountChunk.h"
#include "inet/physicallayer/unitdisk/UnitDiskPhyHeader_m.h"
#include "inet/physicallayer/unitdisk/UnitDiskTransmitter.h"



using namespace inet;
using namespace physicallayer;

Register_Class(UnitDiskRadioCustomized);

Coord position_T;

UnitDiskRadioCustomized::UnitDiskRadioCustomized() :
    Radio()
{

}

void UnitDiskRadioCustomized::encapsulate(Packet *packet) const
{
/*
    cModule *hostT = getContainingNode(this);

    IMobility  *modT = check_and_cast<IMobility *>(hostT->getSubmodule("mobility"));

    position_T = modT->getCurrentPosition();
*/

    auto idealTransmitter = check_and_cast<const UnitDiskTransmitter *>(transmitter);
    auto phyHeader = makeShared<UnitDiskPhyHeader>();
    phyHeader->setChunkLength(idealTransmitter->getHeaderLength());
    phyHeader->setPayloadProtocol(packet->getTag<PacketProtocolTag>()->getProtocol());
    packet->insertAtFront(phyHeader);
    packet->getTag<PacketProtocolTag>()->setProtocol(&Protocol::unitDisk);
}

void UnitDiskRadioCustomized::decapsulate(Packet *packet) const
{
/*
    cModule *hostR = getContainingNode(this);

    IMobility  *modR = check_and_cast<IMobility *>(hostR->getSubmodule("mobility"));

    static std::string position_Rx;
    static std::string position_Tx;
    position_Rx = modR->getCurrentPosition().str();
    EV << " Current Position of Rx = " << position_Rx << " \n";

    position_Tx = position_T.str();
    EV << " Current Position of TX = " << position_Tx << " \n";

    int i,j,f,g,q;

    //Taking the x coordinate value and y coordinate value of Rx position from the string position_Rx
     //this loop looks for the first "," to find out the x coordinate value of Rx
    for (i=0; i<sizeof(position_Rx); i++){
        if(position_Rx[i]==','){
            f = i;// here we save the position of 1st "," into f
            break;
        }
    }
    //this loop looks for the second "," to find out the y coordinate value of Rx
    for(j = i+1; j < sizeof(position_Rx); j++){
        if(position_Rx[j]==','){
            g = j;// here we save the position of 2nd "," into g
            break;
        }
    }
    //Declaring two char variable to save the x coordinate value and y coordinate value of Rx position
    char position_Rx_x[f];
    char position_Rx_y[g-f];

    i=1;//here we start from 1 instead of 0 to avoid the "(" from the string position_Rx
    for( q=0;q<f-1;q++){
        position_Rx_x[q]=position_Rx[i];//we are assigning the x coordinate value into char array position_Rx_x
        i++;
    }

    position_Rx_x[q]='\0';// adding null at the end of the char array to indicate the end of the string
    double position_Rec_x = std::stod(position_Rx_x);//converting char array to a double data type
    EV << " position_Rec_x  = " << position_Rec_x << " \n";// printing to check if the results are correct

    i++;// incrementing i to avoid the "," in between
    for( j=0;j<g-f-1;j++){
        position_Rx_y[j]=position_Rx[i];//we are assigning the y coordinate value into char array position_Rx_y
        i++;
    }
    position_Rx_y[j]='\0';// adding null at the end of the char array to indicate the end of the string

    double position_Rec_y = std::stod(position_Rx_y);//converting char array to a double data type
    EV << " position_Rec_y  = " << position_Rec_y << " \n";// printing to check if the results are correct

    //Taking the x coordinate value and y coordinate value of Tx position from the string position_Tx
   //this loop looks for the first "," to find out the x coordinate value of Tx
    for (i=0; i<sizeof(position_Tx); i++){
        if(position_Tx[i]==','){
            f = i;// here we save the position of 1st "," into f
            break;
        }
    }

    //this loop looks for the second "," to find out the y coordinate value of Tx
    for(j = i+1; j < sizeof(position_Tx); j++){
        if(position_Tx[j]==','){
            g = j;// here we save the position of 2nd "," into g
            break;
        }
    }
    //Declaring two char variable to save the x coordinate value and y coordinate value of Tx position
    char position_Tx_x[f];
    char position_Tx_y[g-f];

    i=1; //here we start from 1 instead of 0 to avoid the "(" from the string position_Tx
    for( q=0;q<f-1;q++){
        position_Tx_x[q]=position_Tx[i]; //we are assigning the x coordinate value into char array position_Tx_x
        i++;
    }
    position_Tx_x[q]='\0'; // adding null at the end of the char array to indicate the end of the string
    double position_Trans_x = std::stod(position_Tx_x);//converting char array to a double data type
    EV << " position_Trans_x  = " << position_Trans_x << " \n";// printing to check if the results are correct

    i++;// incrementing i to avoid the "," in between
    for( j=0;j<g-f-1;j++){
        position_Tx_y[j]=position_Tx[i];//we are assigning the y coordinate value into char array position_Tx_y
        i++;
    }
    position_Tx_y[j]='\0'; // adding null at the end of the char array to indicate the end of the string

    double position_Trans_y = std::stod(position_Tx_y);//converting char array to a double data type
    EV << " position_Trans_y  = " << position_Trans_y << " \n";// printing to check if the results are correct

    //applying the formula sqrt((x_2-x_1)^2+(y_2-y_1)^2) to get the distance between Tx and Rx
    double distance = sqrt(pow((position_Rec_x-position_Trans_x),2)+ pow((position_Rec_y-position_Trans_y),2));

    EV << " distance between Tx and Rx is: " << distance << " \n";// printing to check if the results are correct

    //comparing distance with Radio Horizon rh(h1, h2)|km = 922.06 to decide for path loss
    int L_p;//path loss
    if(distance < 922060){
       //L_p =
    }

    */
    const auto& phyHeader = packet->popAtFront<UnitDiskPhyHeader>();
    packet->addTagIfAbsent<PacketProtocolTag>()->setProtocol(phyHeader->getPayloadProtocol());
}

