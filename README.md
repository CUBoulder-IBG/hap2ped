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
	--output "Unphased" \
	--pathoutput /path_of_the_ped_file/ped_file.chr
	--outputtype "AGCT" \
	--mapslegendfile /path_of_the_legend_file/legend_file"$cc".legend

chromosome_number is the chromosome number from 1 to 22.

generation_number is the generation number that will be used to create ped file.

The location of the hap file is /path_of_the_hap_files/. A hap file should exist with the name /path_of_the_hap_files/hap_file.chrX.hap where X is the chromosome number. The hap file is assumed to have no header and a list of 0s or 1s separated by a space. 0s represent the reference allele while 1s is the other allele. The program hap2ped can noly deal with biallelic SNPs. The first two 0 and 1 and line n represent the two alleles of the first individual and the SNP of line n in the legend file.

The argument --output can accept the two values "Unphased" or "Phased". The two alleles will be switched with a probability of .5 if the parameter "Unphased" is provided.

The path of the output is /path_of_the_ped_file/ped_file.chr and a file /path_of_the_ped_file/ped_file.chrX.ped will be created.

One of these values can be provided to the argument --outputtype: "AGCT" or "01". A legend file is needed for the argument "AGCT".

The location of the legend file is determine with the argument --mapslegendfile following by the path. 





