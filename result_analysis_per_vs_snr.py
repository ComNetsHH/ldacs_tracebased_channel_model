import numpy as np
import matplotlib.pyplot as plt
from matplotlib.ticker import (MultipleLocator, FormatStrFormatter,
                               AutoMinorLocator)
from scipy import stats as st
import pandas as pd

def parse_if_number(s):
    try: return float(s)
    except: return True if s=="true" else False if s=="false" else s if s else None

def parse_ndarray(s):
    return np.fromstring(s, sep=' ') if s else None

def confidence_interval_t(data, confidence=0.95):
    data_array = 1.0 * np.array(data)
    degree_of_freedom = len(data_array) - 1
    sample_mean, sample_standard_error = np.mean(data_array), st.sem(data_array)
    t = st.t.ppf((1 + confidence) / 2., degree_of_freedom)
    margin_of_error = sample_standard_error * t
    Confidence_Interval = 1.0 * np.array([sample_mean - margin_of_error, sample_mean + margin_of_error])
    return sample_mean, Confidence_Interval, margin_of_error

SNR_filename = 'SNR.csv'
Packet_sent_filename = 'Packet_sent.csv'
Packet_received_filename = 'Packet_received.csv'
no_simulation_runs = 10
variable_values = [180000, 220000, 275000, 370000, 420000, 530000, 670000, 840000, 1100000, 1400000]
variable_name = 'xValues'

result_SNR = pd.read_csv(SNR_filename, converters={
        'attrvalue': parse_if_number,
        'binedges': parse_ndarray,
        'binvalues': parse_ndarray,
        'vectime': parse_ndarray,
        'vecvalue': parse_ndarray})
iter_vars = result_SNR.loc[result_SNR.type=='itervar', ['run', 'attrname', 'attrvalue']]
iter_vars_pivot = iter_vars.pivot(index='run', columns='attrname', values='attrvalue')
result_merged = result_SNR.merge(iter_vars_pivot, left_on='run', right_index=True, how='outer')
no_elements_variable_values = len(variable_values)
result_array = np.empty(shape=[no_elements_variable_values])
vectors = result_merged[result_SNR.type == 'vector']
selected_vectors = []
for value in variable_values:
        vec = vectors[(vectors.name == 'Signal-to-Noise_Ratio') & (getattr(result_merged, variable_name) == value)]
        selected_vectors.append(vec)
result_array_SNR = []
for vectors in selected_vectors:
    snr_element = []
    for row in vectors.itertuples():
        snr_row = np.mean(row.vecvalue)
        snr_element.append(snr_row)
    snr_element = np.mean(np.array(snr_element))
    result_array_SNR.append(snr_element)
result_array_SNR_avg = np.array(result_array_SNR)

variable_values = ['180000', '220000', '275000', '370000', '420000', '530000', '670000', '840000', '1100000', '1400000']
result_Packet_sent = pd.read_csv(Packet_sent_filename)
iter_vars = result_Packet_sent.loc[result_Packet_sent.type == 'itervar', ['run', 'attrname', 'attrvalue']]
iter_vars_pivot = iter_vars.pivot(index='run', columns='attrname', values='attrvalue')
result_merged_Packet_sent = result_Packet_sent.merge(iter_vars_pivot, left_on='run', right_index=True, how='outer')
no_elements_variable_values = len(variable_values)
result_array_Packet_sent = np.empty(shape=[no_elements_variable_values, no_simulation_runs])
for index, value in enumerate(variable_values):
    output_row = result_merged_Packet_sent[(getattr(result_merged_Packet_sent, variable_name) == value)
                                               & (result_merged_Packet_sent.type == 'scalar')
                                               & (result_merged_Packet_sent.module == 'traceBasedRadioModel.host[0].app[0]')
                                               & (result_merged_Packet_sent.name == 'packetSent:count')]
    result_array_Packet_sent[index] = output_row['value'].to_numpy()

result_Packet_received = pd.read_csv(Packet_received_filename)
iter_vars = result_Packet_received.loc[result_Packet_received.type == 'itervar', ['run', 'attrname', 'attrvalue']]
iter_vars_pivot = iter_vars.pivot(index='run', columns='attrname', values='attrvalue')
result_merged_Packet_received = result_Packet_received.merge(iter_vars_pivot, left_on='run', right_index=True, how='outer')
no_elements_variable_values = len(variable_values)
result_array_Packet_received = np.empty(shape=[no_elements_variable_values, no_simulation_runs])
for index, value in enumerate(variable_values):
    output_row = result_merged_Packet_received[(getattr(result_merged_Packet_received, variable_name) == value)
                                               & (result_merged_Packet_received.type == 'scalar')
                                               & (result_merged_Packet_received.module == 'traceBasedRadioModel.host[1].app[0]')
                                               & (result_merged_Packet_received.name == 'packetReceived:count')]
    result_array_Packet_received[index] = output_row['value'].to_numpy()

dropped_packet_array = np.subtract(result_array_Packet_sent, result_array_Packet_received)
PER_simulated = np.divide(dropped_packet_array, result_array_Packet_sent)

PER_theoretical = np.array([0.01, 0.01, 0.01, 0.1, 0.5, 0.7, 0.95, 1, 1, 1])

sample_mean, Confidence_Interval_array, margin_of_error = confidence_interval_t(PER_simulated[0], confidence=0.95)
sample_mean_per_simulated_array = 1.0 * np.array(sample_mean)
margin_of_error_per_array = 1.0 * np.array(margin_of_error)
for row in range(1, result_array_SNR_avg.size):
    sample_mean, confidence_Interval, margin_of_error = confidence_interval_t(PER_simulated[row], confidence=0.95)
    sample_mean_per_simulated_array = np.append(sample_mean_per_simulated_array, sample_mean)
    margin_of_error_per_array = np.append(margin_of_error_per_array, margin_of_error)

##########################################################
# SNR vs PER
##########################################################

ylabel = 'PER'
xlabel = 'SNR (dB)'
rotation_xticks = ''
yaxis_minor_ticks_separation = 0.0
title = ''




fig, ax = plt.subplots()

ax.scatter(result_array_SNR_avg, PER_theoretical, marker='s', color='black',s=25,label='Theoretical')

ax.plot(result_array_SNR_avg, PER_theoretical, color='black', linestyle='dashed')


x_data = result_array_SNR_avg
y_data = sample_mean_per_simulated_array
margin_of_error = margin_of_error_per_array

x_pos = np.arange(len(x_data))
# ax.scatter(SNR_with_margin_rounded, sample_mean_per_simulated_array, color='blue',marker='+', s=30)
ax.errorbar(result_array_SNR_avg, sample_mean_per_simulated_array,yerr=margin_of_error_per_array,
            fmt='+',ecolor='black',color='black',elinewidth=1,markersize=9,capsize=4,capthick=1,label='Simulation')


ax.set_yscale('log')

ax.legend()

ax.set_xlabel(xlabel, fontname='Helvetica', fontsize=10)  # , fontweight='bold'

ax.tick_params(which='both', width=1)
ax.tick_params(which='major', length=3, color='black', labelsize=8)
ax.tick_params(which='minor', length=2, color='black')

ax.grid(True, ls=(0, (1, 8)), c='black', linewidth=0.5)  # , linewidth=0.5
ax.xaxis.grid(ls=(0, (1, 5)))
ax.grid(which='minor', ls=(0, (1, 10)), c='black', alpha=0.7, linewidth=0.5)

ax.xaxis.set_major_locator(MultipleLocator(2))

ax.margins(x=0)

plt.tight_layout()
plt.savefig('snr-vs-per-curve.pdf', format='pdf', dpi=1200)
plt.show()
