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

    If the combination of station and consumption is invalid (hvb-individual, hvb-all, hva-individual and hva-all), the script shows "Error : impossible request"

Options :
    -h, --help Show this help
EOF
}

# Timer global
script_start_time=$(date +%s)  # Capture the start time in seconds

# Manage help option
if [[ "$1" == "-h" || "$1" == "--help" ]]; then
    help
    exit 0
fi

if [ $# -ne 3 ]; then # If the number of arguments is incorrect
    echo "Usage : $0 <path> <station> <consumption>"
    help # Return "help" function
    exit 1
fi

path=$1 # First argument
station=$2 # Second argument
consumption=$3 # Third argument

if [ ! -f "$path" ]; then # If the path is incorrect
    echo "Error : $path is incorrect"
    help # Return "help" function
    exit 2
fi

if [[ "$station" != "hvb" && "$station" != "hva" && "$station" != "lv" ]]; then # If the type of station is incorrect
    echo "Error : $station the station's type is incorrect"
    help # Return "help" function
    exit 3
fi

if [[ "$consumption" != "company" && "$consumption" != "individual" && "$consumption" != "all" ]]; then # If the type of consumption is incorrect
    echo "Error : $consumption the consumption's type is incorrect"
    help # Return "help" function
    exit 4
fi

exec="codeC/MNH_CWire"
if [[ ! -f "$exec" ]]; then # If the executable doesn't exist
    echo "Error : $exec doesn't exist. Compiling..."
    cd codeC
    make clean
    make all
    cd ..

    if [[ ! -f "$exec" ]]; then
        echo "Error : $exec hasn't been compiled."
        exit 5
    fi
fi

tmp="tmp"
if [[ ! -d "$tmp" ]]; then # Checks or initializes the temporary directory tmp to store intermediate files
    echo "Error : $tmp doesn't exist. Creation of the directory"
    mkdir tmp
else
    rm -rf $tmp/*
fi

case "$station-$consumption" in
    "hvb-company") # Data extraction for hvb and company in a temporary file
        awk -F";" '($2 != "-" && $5 != "-") || ($2 != "-" && $7 != "-") {print $2 ";" $7 ";" $8}' input/c-wire_v25.dat > tmp/hvbCtmp.csv
        sed -i 's/-/0/g' tmp/hvbCtmp.csv
        tmp_file="tmp/hvbCtmp.csv"
        final_file="tests/hvb_comp.csv"
        ;; #hvb company

    "hva-company") # Data extraction for hva and company in a temporary file
        awk -F";" '($3 != "-" && $5 != "-") || ($3 != "-" && $7 != "-") {print $3 ";" $7 ";" $8}' input/c-wire_v25.dat > tmp/hvaCtmp.csv
        sed -i 's/-/0/g' tmp/hvaCtmp.csv
        tmp_file="tmp/hvaCtmp.csv"
        final_file="tests/hva_comp.csv"
        ;; #hva company

    "lv-company") # Data extraction for lv and company in a temporary file
        awk -F";" '($4 != "-" && $5 != "-") || ($4 != "-" && $7 != "-") {print $4 ";" $7 ";" $8}' input/c-wire_v25.dat > tmp/lvCtmp.csv
        sed -i 's/-/0/g' tmp/lvCtmp.csv
        tmp_file="tmp/lvCtmp.csv"
        final_file="tests/lv_comp.csv"
        ;; #lv company

    "lv-individual") # Data extraction for lv and individual in a temporary file
        awk -F";" '($4 != "-" && $6 != "-") || ($4 != "-" && $7 != "-") {print $4 ";" $7 ";" $8}' input/c-wire_v25.dat > tmp/lvItmp.csv
        sed -i 's/-/0/g' tmp/lvItmp.csv
        tmp_file="tmp/lvItmp.csv"
        final_file="tests/lv_indiv.csv"
        ;; #lv indiv

    "lv-all") # Data extraction for lv and all in a temporary file + 10 minimal and 10 maximal values of lv all in a temporary file
        awk -F";" '($4 != "-" && $5 != "-") || ($4 != "-" && $6 != "-") || ($4 != "-" && $7 != "-") {print $4 ";" $7 ";" $8}' "$path" > "$tmp/lvAtmp.csv"
        sed -i 's/-/0/g' "$tmp/lvAtmp.csv"

        tmp_file="$tmp/lvAtmp.csv"
        final_file="tests/lv_all_minmax.csv"

        if [[ -s "$tmp_file" ]]; then
            echo "Nom;Capacite;Consommation;Difference" > "$final_file"
            awk -F";" 'NR > 1 && $2 ~ /^[0-9]+$/ && $3 ~ /^[0-9]+$/ {
                capacite = $2;
                consommation = $3;
                difference = capacite - consommation;
                print $0 ";" difference;
            }' "$tmp_file" | sort -t';' -k4,4n | {
                head -n 10 >> "$final_file"
                tail -n 10 >> "$final_file"
            }
        else
            echo "Error: No valid data in lv-all"
            exit 7
        fi
        ;;

    *)
        echo "Error : impossible request"
        help 
        exit 6
esac

# Creation or reset of the final file
if [[ ! -f "$final_file" ]]; then
    chmod +w "$final_file"
    touch $final_file

else 
    chmod +w "$final_file" # Give the final file a writing authorization
fi

./codeC/MNH_CWire "$tmp_file" "$final_file" > /dev/null # Running the main executable with temporary files as argument
sort -t ';' -k 2,2 "$final_file" > /dev/null

# End global timer
script_end_time=$(date +%s)  # Capture the end time in seconds
total_elapsed_time=$((script_end_time - script_start_time))  # Total time in seconds
echo "Total script execution time: $total_elapsed_time seconds"

echo "                                                                        ,---.    ,---.,---.   .--..---.  .---.  
                                                                        |    \  /    ||    \  |  ||   |  |_ _|  
                                                                        |  ,  \/  ,  ||  ,  \ |  ||   |  ( ' )  
                                                                        |  |\_   /|  ||  |\_ \|  ||   '-(_{;}_) 
                                                                        |  _( )_/ |  ||  _( )_\  ||      (_,_)  
                                                                        | (_ o _) |  || (_ o _)  || _ _--.   |  
                                                                        |  (_,_)  |  ||  (_,_)\  ||( ' ) |   |  
                                                                        |  |      |  ||  |    |  |(_{;}_)|   |  
                                                                        '--'      '--''--'    '--''(_,_) '---'  
"

echo "             ▗▄▖▗▄▄▄▖    ▗▖  ▗▖▗▄▖ ▗▖ ▗▖▗▄▄▖      ▗▄▄▖▗▄▄▄▖▗▄▄▖ ▗▖  ▗▖▗▄▄▄▖ ▗▄▄▖▗▄▄▄▖    ▗▄▄▄▖ ▗▄▖ ▗▄▄▖      ▗▄▖ ▗▖  ▗▖▗▖  ▗▖    ▗▄▄▄▖▗▄▄▖ ▗▄▄▄▖ ▗▄▖▗▄▄▄▖▗▖  ▗▖▗▄▄▄▖▗▖  ▗▖▗▄▄▄▖
            ▐▌ ▐▌ █       ▝▚▞▘▐▌ ▐▌▐▌ ▐▌▐▌ ▐▌    ▐▌   ▐▌   ▐▌ ▐▌▐▌  ▐▌  █  ▐▌   ▐▌       ▐▌   ▐▌ ▐▌▐▌ ▐▌    ▐▌ ▐▌▐▛▚▖▐▌ ▝▚▞▘       █  ▐▌ ▐▌▐▌   ▐▌ ▐▌ █  ▐▛▚▞▜▌▐▌   ▐▛▚▖▐▌  █  
            ▐▛▀▜▌ █        ▐▌ ▐▌ ▐▌▐▌ ▐▌▐▛▀▚▖     ▝▀▚▖▐▛▀▀▘▐▛▀▚▖▐▌  ▐▌  █  ▐▌   ▐▛▀▀▘    ▐▛▀▀▘▐▌ ▐▌▐▛▀▚▖    ▐▛▀▜▌▐▌ ▝▜▌  ▐▌        █  ▐▛▀▚▖▐▛▀▀▘▐▛▀▜▌ █  ▐▌  ▐▌▐▛▀▀▘▐▌ ▝▜▌  █  
            ▐▌ ▐▌ █        ▐▌ ▝▚▄▞▘▝▚▄▞▘▐▌ ▐▌    ▗▄▄▞▘▐▙▄▄▖▐▌ ▐▌ ▝▚▞▘ ▗▄█▄▖▝▚▄▄▖▐▙▄▄▖    ▐▌   ▝▚▄▞▘▐▌ ▐▌    ▐▌ ▐▌▐▌  ▐▌  ▐▌        █  ▐▌ ▐▌▐▙▄▄▖▐▌ ▐▌ █  ▐▌  ▐▌▐▙▄▄▖▐▌  ▐▌  █  
"

echo "                                                                                                                       ____ 
                                                                                                                      |   / 
                                                                  (    (    (            (                            |  /  
                                                             (    ))\  ))\   )\ )   (    ))\   (    (    (    (       | /   
                                                             )\  /((_)/((_) (()/(   )\  /((_)  )\   )\   )\   )\ )    |/    
                                                            ((_)(_)) (_))    )(_)) ((_)(_))(  ((_) ((_) ((_) _(_/(   (      
                                                            (_-</ -_)/ -_)  | || |/ _ \| || | (_-</ _ \/ _ \| ' \))  )\     
                                                            /__/\___|\___|   \_, |\___/ \_,_| /__/\___/\___/|_||_|  ((_)    
                                                                             |__/                                           

"
