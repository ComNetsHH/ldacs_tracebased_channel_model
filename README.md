[![DOI](https://zenodo.org/badge/397504015.svg)](https://zenodo.org/badge/latestdoi/397504015)
# TraceBasedRadio
OMNeT++ Trace-Based Radio Model extends the INET's `UnitDiskRadio` to a more realistic model by obtaining the Signal-to-Noise Ratio (SNR) in the `TraceBasedReceiver` and passing the SNR to a novel `TraceBasedErrorModel`, which queries the trace file-provided lookup table to obtain the closest-matching SNR’s mapping to a Packet Error Rate (PER) and Bit Error Rate (BER). This trace file is expected to contain a triple of (SNR, PER and BER) per line as follows:
| SNR (dB) |  PER |     BER     |
|:--------:|:----:|:-----------:|
|    -5    |   1  | 0.493378795 |
|    -4    |   1  | 0.486143304 |
|    ...   |  ... |     ...     |
|    10    | 0.01 |   5.22E-08  |

## Getting Started
1. Please download [inet-4.2.5](https://github.com/inet-framework/inet/tree/v4.2.5) for OMNeT++ 5.6.2 and import it into the simulator.
2. Please clone this repo `TraceBasedRadio` and import it into OMNet++. To build it you need to do the following steps:
    1. `inet` must be set as a project reference. This is done by right-clicking on the `TraceBasedRadio` project in the Project Explorer and navigate to `Properties-> Project References -> Select inet -> Apply and Close`
    2. Ensure the build modes of this project and `inet` are identical (both `release` or both `debug`): This is done by right-clicking on each project in the Project Explorer and navigating to `Build Configuration -> Set Active -> <mode>`
    3. The `include paths` from INET must be added to this project such that you can write classes in your project which inherit `inet` classes. For that, you need to right-click on the `TraceBasedRadio` in the Project Explorer and navigate to `Properties -> OMNeT++ -> Makemake`, select the `src` folder in the list and then click "Options" in the right panel. 
    4. Go to the `Target` tab and make sure that `Shared library ...` is checked.
    5. Now go to the `Compile` tab and make sure all checkboxes are checked. 
    6. Move to the `Link` tab and make sure that the `Link with libraries exported from...` checkbox is checked. 
    7. Finally, `Apply and Close` and you should be able to `build` the `TraceBasedRadio` project without errors as a project that reference the INET project.
5. Navigate to `radio-model/simulation/omnetpp.ini` in the OMNeT++ IDE and click run. 
6. Run the following command in the terminal to extract the results into a .csv file using the OMNeT++'s scavetool:
```
cd ./radio-model/simulation/results/
scavetool export -f 'module(traceBasedRadioModel.host[1].wlan[0].radio.receiver.errorModel) AND name("Signal-to-Noise_Ratio")' -o SNR.csv General-x*.vec
scavetool export -f 'module(traceBasedRadioModel.host[0].app[0]) AND name("packetSent:count")' -o Packet_sent.csv General-x*.sca
scavetool export -f 'module(traceBasedRadioModel.host[1].app[0]) AND name("packetReceived:count")' -o Packet_received.csv General-x*.sca
```
7. The python result analysis script that generates the figure of the PER vs the SNR could be run using:
```
python result_analysis_per_vs_snr.py
```
