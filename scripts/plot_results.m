% analyze voltage from a neuron using IZ 9-param model

initOAT;
stel_nR = NeuronReader('../results/n_MEC_LII_Stellate.dat');
stel_nV = stel_nR.readValues();
t_start = 1; % start time
t_end = 2000; % end time
t_range = linspace(t_start,t_end,(t_end-t_start+1));
stel_sel = stel_nV.v(1,t_start:t_end);

plot(t_range, stel_sel,'Color','#80B3FF','LineWidth',1.5);