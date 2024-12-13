
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


#Start timer 
A=$(date +%s.%N)


#Check if help command is requested. If yes, display_help is called. Otherwise, do nothing.
for arg in "$@"; do
if [ "$arg" == "-h" ]; then
display_help
break
fi
done


#Check if the first argument is the path to the CSV file.
if [[ -z "$1" || ! -f "$1" || "$1" != *.csv ]]; then
echo "Error : The first parameter is invalid."
display_help
fi









#verify arguments
if [ $# -lt 3]; then
echo "Error : There could not be less than 3 parameters."
display_help
fi


# verify files
if [ ! -f "$FILE_DAT" ]; then
    echo "Error : File $FILE_DAT does not exist or is not accessible."
    exit 1
fi

if [ ! -r "$FILE_C" ]; then
    echo "Error : File $FILE_C does not have read permissions."
    exit 1
fi

if [ ! -x "$FILE_C" ]; then
    echo "Error : File $FILE_C is not executable."
    exit 1
fi


if [[ "$1" == "hvb" ]] && [[ "$2" == "comp" ]]; then
  awk -F';' '$2 != "-" && $4 == "-" && $7 == "-" || $2 != "-" && $3 == "-" && $4 == "-" && $5 == "-" && $6 == "-"' "cwire.dat" | cut -d';' -f2,5,7,8 | tr '-' '0' | ./projet
fi

if [[ "$1" == "hvb" ]] && [[ "$2" == "indiv" ]]; then
  echo "Error : HV-B stations can not have individuals as consumers."
  display_help
fi

if [[ "$1" == "hvb" ]] && [[ "$2" == "all" ]]; then
  echo "Error : HV-B stations can not have all type of consumers."
  display_help
fi

if [[ "$1" == "hva" ]] && [[ "$2" == "comp" ]]; then
  awk -F';' '$2 != "-" && $4 == "-" && $7 == "-" || $2 != "-" && $3 == "-" && $4 == "-" && $5 == "-" && $6 == "-"' "cwire.dat" | cut -d';' -f2,5,7,8 | tr '-' '0' | ./projet
fi

if [[ "$1" == "hva" ]] && [[ "$2" == "indiv" ]]; then
  echo "Error : HV-A stations can not have individuals as consumers."
  display_help

if [[ "$1" == "hva" ]] && [[ "$2" == "all" ]]; then
  echo "Error : HV-A stations can not have all type of consumers."
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


# verify options
if [[ -z "$1" || -z "$2" || -z "$3" ]]; then
  echo "Error : Missing parameters."
  display_help
  exit 1
fi

B=$(date +%s.%N)
diff=$(echo "$B - $A" | bc)
echo "Elapsed time : $diff seconds"

./codeC