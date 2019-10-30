# hap2ped

Turn HAP files into ped phased that can be phased or unphased using 0 and 1 or AGCT 

# Download

To download “hap2ped”, you can push the green button “Clone or Download” and then “Download ZIP”.

Or, you can type the following commands in the terminal:

    git clone https://github.com/emmanuelsapin/hap2ped
    cd hap2ped


# Binary files

The compiled files for Linux are availible in the main direcory: Haptoped_Linux

#Compile

To compile Haptoped, run the following command:

volve, run the following commands:

    make


# Documentation

The progam hap2ped turn hap files into ped files. The following command runs hap2ped:


   hap2ped \
	--chr chromosome_number \
	--gen generation_number \
	--pathped /path_of_the_hap_files/hap_file.chr \
	--output "Phased"_or_"Unphased" \
	--pathoutput /path_of_the_ped_file/ped_file.chr
	--outputtype "AGCT"_or_"01" \
	--mapslegendfile /path_of_the_legend_file/legend_file"$cc".legend

chromosome_number is the chromosome number from 1 to 22
