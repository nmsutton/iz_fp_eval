% analyze voltage from a neuron using IZ 9-param model

function []=plot_results(volt_file, output_desc)
	initOAT;
	save_plot=1;
	% retrieve spikes
	%neur_read = NeuronReader('../results/n_MEC_LII_Stellate.dat');
	neur_read = NeuronReader(volt_file);
	voltages = neur_read.readValues();
	t_start = 1; % start time
	t_end = 2000; % end time
	t_range = linspace(t_start,t_end,(t_end-t_start+1));
	selected_volt = voltages.v(1,t_start:t_end);
	% plot
	plot(t_range, selected_volt,'Color','#80B3FF','LineWidth',1.5);
	if save_plot
	    %c = clock;
	    %hr = mod(c(4),12);
	    %output_filename = sprintf("voltage_%.0f-%.0f-%.0f_%.0f-%.0f-%.0f.png",hr,c(5),c(6),c(2),c(3),c(1));
	    output_filename = sprintf("voltage_%s.png",output_desc);
	    exportgraphics(gcf,output_filename,'Resolution',300)
	end
end