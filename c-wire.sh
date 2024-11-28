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
