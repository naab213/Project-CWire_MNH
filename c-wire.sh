#!/bin/bash

help() {
	cat << EOF
Usage : $0 <path> <station> <consumption>
Description :
This script.

For its good fonctionment, this script verify the validity of the 3 arguments :
	1. First argument : valid path to a file
	2. Second argument : valid type of station
	3. Third argument : valid type of consumption

Required arguments :
	<path> : valid absolute path to a file
	<station> : allowed values ("hvb", "hva", "lv")
	<consumption> : allowed values ("company", "individual", "all")

Options :
	-h, --help Show this help
EOF
}


timer() {
	start=$date( +%s)
	"$@"
	end=$date( +%s)
	time=$($end - $start)
	echo "The treatment $* took $time second(s)"
}

if [ $# -ne 3 ]; then
	echo "Usage : $0 <path> <station> <consumption>"
	help
	exit 1
fi
path=$1
station=$2
consumption=$3
if [ -f "$path" ]; then
	echo "Error : $path the path is incorrect"
	help
	exit 2
fi
if [[ "$station" != "hvb" || "$station" != "hva" || "$station" != "lv" ]]; then
	echo "Error : $station the station's type is incorrect"
	help
	exit 3
fi
if [[ "$consumption" != "company" || "$consumption" != "indiviual" || "$consumption" != "all" ]];
	echo "Error : $consumption the consumption's type is incorrect"
	help
	exit 4
fi

exec="codeC/MNH_CWire"
if [[ ! -f "$exec" ]]; then
	echo "Error : $exec doesn't exist. Compiling..."
	make -f Makefile.mak

	if [[ ! -f "$exec" ]]; then
		echo "Error : $exec hasn't been compiled."
		exit 5
	fi
fi

tmp="tmp"
if [[ ! -d "$tmp " ]]; then
	echo "Error : $tmp doesn't exist. Creation of the directory"
	mkdir tmp
else
	rm -rf $tmp
fi

timer(cut -d; -f2,5 c-wire_v25.dat > hvbCtmp.csv) //hvb company
timer(cut -d; -f3,5 c-wire_v25.dat > hvaCtmp.csv) //hva company
timer(cut -d; -f4,5 c-wire_v25.dat > lvCtmp.csv) //lv company
timer(cut -d; -f4,6 c-wire_v25.dat > lvItmp.csv) //lv indiv
timer(cut -d; -f4,5,6 c-wire_v25.dat > lvAtmp.csv) //lv all
