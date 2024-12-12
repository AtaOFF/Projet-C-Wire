FILE_DAT="data_cwire.dat"
FILE_TEMP="filtered_data.dat" # temp file with filtered data
FILE_C="./code" # path to the compiled C executable
OUTPUT_FILE="result.txt" # file to show C program results (can be modified in the future to a graphic file)

#!/bin/bash

# Function: Display help
display_help() {
    echo "Usage: $0 <path_to_CSV_file> <station_type> <consumer_type> [central_id] [-h]"
    echo ""
    echo "Parameter descriptions:"
    echo "  <path_to_CSV_file>   Path to the CSV file containing the data (required)."
    echo "  <station_type>       Type of station to process: hvb, hva, lv (required)."
    echo "  <consumer_type>      Type of consumer: comp (business), indiv (individual), all (all) (required)."
    echo "  [central_id]         ID of a specific station (optional)."
    echo "  -h                   Display this help and ignore all other parameters (optional)."
    echo ""
    echo "Restrictions:"
    echo "  The following combinations are forbidden:"
    echo "  - hvb all, hva all, hvb indiv, hva indiv"
    echo ""
}

if [[ "$1" == "-h" ]]; then
  display_help
  exit 0
fi

# Check files
if [ ! -f "$FILE_DAT" ]; then
    echo "Error : File $FILE_DAT does not exist or is not accessible"
    exit 1
fi

if [ ! -r "$FILE_C" ]; then
    echo "Error : File $FILE_C does not have read permissions"
    exit 1
fi

if [ ! -x "$FILE_C" ]; then
    echo "Error : File $FILE_C is not executable"
    exit 1
fi

//timer 
A=$(date +%s.%N)

./code

if [[ "$1" == "hvb" ]] && [[ "$2" == "comp" ]]; then
  awk -F';' '$2 != "-" && $4 == "-" && $7 == "-" || $2 != "-" && $3 == "-" && $4 == "-" && $5 == "-" && $6 == "-"' "cwire.dat" | cut -d';' -f2,5,7,8 | tr '-' '0' | ./projet
fi

if [[ "$1" == "hvb" ]] && [[ "$2" == "indiv" ]]; then
  echo "Erreur : les stations HV-B ne peuvent pas avoir de particuliers comme consommateurs."
  display_help
fi

if [[ "$1" == "hvb" ]] && [[ "$2" == "all" ]]; then
  echo "Erreur : les stations HV-B ne peuvent pas avoir tous les types de consommateurs."
  display_help
fi

if [[ "$1" == "hva" ]] && [[ "$2" == "comp" ]]; then
  awk -F';' '$2 != "-" && $4 == "-" && $7 == "-" || $2 != "-" && $3 == "-" && $4 == "-" && $5 == "-" && $6 == "-"' "cwire.dat" | cut -d';' -f2,5,7,8 | tr '-' '0' | ./projet
fi

if [[ "$1" == "hva" ]] && [[ "$2" == "indiv" ]]; then
  echo "Erreur : les stations HV-A ne peuvent pas avoir de particuliers comme consommateurs."
  display_help

if [[ "$1" == "hva" ]] && [[ "$2" == "all" ]]; then
  echo "Erreur : les stations HV-A ne peuvent pas avoir tous les types de consommateurs."
  display_help
fi

if [[ "$1" == "lv" ]] && [[ "$2" == "comp" ]]; then
  awk -F';' '$2 != "-" && $4 == "-" && $7 == "-" || $2 != "-" && $3 == "-" && $4 == "-" && $5 == "-" && $6 == "-"' "cwire.dat" | cut -d';' -f2,5,7,8 | tr '-' '0' | ./projet
fi

if [[ "$1" == "lv" ]] && [[ "$2" == "indiv" ]]; then
  awk -F';' '$2 != "-" && $4 == "-" && $7 == "-" || $2 != "-" && $3 == "-" && $4 == "-" && $5 == "-" && $6 == "-"' "cwire.dat" | cut -d';' -f2,5,7,8 | tr '-' '0' | ./projet
fi

if [[ "$1" == "lv" ]] && [[ "$2" == "all" ]]; then
  awk -F';' '$2 != "-" && $4 == "-" && $7 == "-" || $2 != "-" && $3 == "-" && $4 == "-" && $5 == "-" && $6 == "-"' "cwire.dat" | cut -d';' -f2,5,7,8 | tr '-' '0' | ./projet
fi


# Vérification des options
if [[ -z "$1" || -z "$2" || -z "$3" ]]; then
  echo "Erreur : il manque des paramètres."
  display_help
  exit 1
fi

B=$(date +%s.%N)
diff=$(echo "$B - $A" | bc)
echo "Temps écoulé : $diff secondes"