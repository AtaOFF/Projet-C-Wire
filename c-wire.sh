#!/bin/bash

FILE_DAT="$1"  # Path to the data file
OUTPUT_FILE="filtered_data.csv"   # Output CSV file (results from C program)


make > /dev/null 2>&1 || true
export MAKEFLAGS="--silent"

# Function: Display help
display_help() {
    echo "Usage: ./c-wire.sh [ARG] [OPTION]"
    echo "Arguments:"
    echo "  ARG[0] Path to the CSV file containing the data *required*"
    echo "  ARG[1] Station type (HVB, HVA, LV) *required*"
    echo "  ARG[2] Consumer type: comp (business), indiv (individual), all (all) *required*"
    echo "  ARG[3] Number of power plant *optional*"
    echo "Options:"
    echo "  -h        Display this help and ignore all other parameters *optional*"
    echo ""
    echo "Restrictions:"
    echo "  The following combinations are forbidden:"
    echo "  - hvb all, hva all, hvb indiv, hva indiv"
    echo ""
}



#Check if makefile exists
#Otherwise, an error code is returned.
if [ ! -f "makefile" ]; then
echo "Error : Makefile does not exist." >&2
exit 1
fi


#Start timer
A=$(date +%s.%N)


#Check if help command is requested in the parameters entered. If yes, display_help fonction is called.
#Otherwise, do nothing.
for arg in "$@"; do
if [ "$arg" == "-h" ]; then
display_help
exit 0
fi
done


#Implementation of the programme
#If compilation fails, return an error code
make
if [ $? -ne 0 ]; then
echo "Error : Compilation failed." >&2
exit 1
fi


#Check if the executable C exists, can be read, and be executed.
#Otherwise, an error code is returned.
if [ ! -f ./exec ]; then
echo "Error : The executable C does not exist." >&2
exit 1
fi

if [ ! -r ./exec ]; then
echo "Error : The executable C cannot be read." >&2
exit 1
fi

if [ ! -x ./exec ]; then
echo "Error : The executable C cannot be executed." >&2
exit 1
fi



#Check for required parameters. If one or more are missing, an error message is displayed,
#display_help fonction is called and an error code is returned.
if [[ -z "$1" || -z "$2" || -z "$3" ]]; then
echo "Error : Missing parameters." >&2
display_help
exit 1
fi

#Check if the first parameter is the good path to the DAT file. Otherwise, an error message is displayed,
#display_help fonction is called and an error code is returned.
if [[ ! -f "$1" || "$1" != *.dat ]]; then
echo "Error : The first parameter must be a valid path to an existing .dat file. " >&2
display_help
exit 1
fi


#Check if the second parameter is a type of station. Otherwise, an error message is displayed,
#display_help fonction is called and an error code is returned.
if [[ "$2" != "hva" && "$2" != "hvb" && "$2" != "lv" ]]; then
echo "Error : The second parameter must be a type of station." >&2
display_help
exit 1
fi


#Check if the third parameter is a type of consumer. Otherwise, an error message is displayed,
#display_help fonction is called and an error code is returned.
if [[ "$3" != "comp" && "$3" != "indiv" && "$3" != "all" ]]; then
echo "Error : The third parameter must be a type of consumer." >&2
display_help
exit 1
fi



#Check that the fourth parameter entered, which is the number of plant, if any, is valid.
#If not, an error message is displayed, display_help fonction is called and an error code is returned.
if [[ -n "$4" ]]; then
if [[ "$4" != "1" && "$4" != "2" && "$4" != "3" && "$4" != "4" && "$4" != "5" ]]; then
echo "Error : The fourth parameter must be a valid power plant." >&2
display_help
exit 1
fi
fi





#Check the 4 prohibited combinations :
#1. If the first prohibited combination (hvb all) is entered by the user, an error message is displayed,
#display_help fonction is called and an error code is returned.
if [[ "$2" == "hvb" && "$3" == "all" ]]; then
echo "Error : HV-B stations can not have all type of consumers." >&2
display_help
exit 1
fi


#2. If the second prohibited combination (hvb indiv) is entered by the user, an error message is displayed,
#display_help fonction is called and an error code is returned.
if [[ "$2" == "hvb" && "$3" == "indiv" ]]; then
echo "Error : HV-B stations can not have individuals as consumers." >&2
display_help
exit 1
fi


#3. If the third prohibited combination (hva indiv) is entered by the user, an error message is displayed,
#display_help fonction is called and an error code is returned.
if [[ "$2" == "hva"  && "$3" == "indiv" ]]; then
echo "Error : HV-A stations can not have individuals as consumers." >&2
display_help
exit 1
fi


#4. If the fourth prohibited combination (hva all) is entered by the user, an error message is displayed,
#display_help fonction is called and an error code is returned.
if [[ "$2" == "hva" &&  "$3" == "all" ]]; then
echo "Error : HV-A stations can not have all type of consumers." >&2
display_help
exit 1
fi





#Filter data based on user input and call the C program with the filtered data (5 possible combinations) :
#1. Companies linked to an HVB station (hvb comp) :
#Selection of the collones concerned in the CSV file.
#Extraction of these in the executable by replacing the "-"" with "0" to facilitate data manipulation.
if [[ "$2" == "hvb" ]] && [[ "$3" == "comp" ]]; then
  if [[ -n "$4" ]]; then
  awk -F';'  -v power_plant="$4" '$1 == power_plant && $2 != "-" && $3 == "-" && $4 == "-" && $5 != "-" && $8 != "-" || $1 == power_plant && $2 != "-" && $3 == "-" && $4 == "-" == $7 != "-"' "$1" | cut -d';' -f2,7,8 | tr '-' '0' | ./exec | while read line;
  do echo $line
  done > hvb_comp_$4.csv
  sort -t ';' -k2,2n hvb_comp_$4.csv -o hvb_comp_$4.csv
  else
  awk -F';'  '$2 != "-" && $3 == "-" && $4 == "-" && $5 != "-" && $8 != "-" || $2 != "-" && $3 == "-" && $4 == "-" && $7 != "-"' "$1" | cut -d';' -f2,7,8 | tr '-' '0' | ./exec | while read line;
  do
  echo $line
  done > hvb_comp.csv
  sort -t ';' -k2,2n hvb_comp.csv -o hvb_comp.csv
fi
fi


#2. Companies linked to an HVA station (hva comp) :
#Selection of the collones concerned in the CSV file.
#Extraction of these in the executable by replacing the "-"" with "0" to facilitate data manipulation.
#Redirection results to an output file with the appropriate name.
if [[ "$2" == "hva" ]] && [[ "$3" == "comp" ]]; then
  if [[ -n "$4" ]]; then
  awk -F';'  -v power_plant="$4" '$1 == power_plant && $2 == "-" && $3 != "-" && $4 == "-" && $5 != "-" && $8 != "-" || $1 == power_plant && $2 != "-" && $3 != "-" && $4 == "-" && $7 != "-"' "$1" | cut -d';' -f3,7,8 | tr '-' '0' | ./exec | while read line;
  do
  echo $line
  done > hva_comp_$4.csv
  sort -t ';' -k2,2n hva_comp_$4.csv -o hva_comp_$4.csv
  else
  awk -F';'  '$2 == "-" && $3 != "-" && $4 == "-" && $5 != "-" && $8 != "-" || $2 != "-" && $3 != "-" && $4 == "-" && $7 != "-"' "$1" | cut -d';' -f3,7,8 | tr '-' '0' | ./exec | while read line;
  do
  echo $line
  done > hva_comp.csv
  sort -t ';' -k2,2n hva_comp.csv -o hva_comp.csv
fi
fi

#3. Companies linkes to a LV station (lv comp) :
#Selection of the collones concerned in the CSV file.
#Extraction of these in the executable by replacing the "-"" with "0" to facilitate data manipulation.
#Redirection results to an output file with the appropriate name.
if [[ "$2" == "lv" ]] && [[ "$3" == "comp" ]]; then
  if [[ -n "$4" ]]; then
  awk -F';'  -v power_plant="$4" '$1 == power_plant && $2 == "-" && $3 == "-" && $4 != "-" && $5 != "-" && $8 != "-" || $1 == power_plant && $2 == "-" && $3 != "-" && $4 != "-" && $7 != "-"' "$1" | cut -d';' -f4,7,8 | tr '-' '0' | ./exec | while read line;
  do
  echo $line
  done > lv_comp_$4.csv
  sort -t ';' -k2,2n lv_comp_$4.csv -o lv_comp_$4.csv
  else
  awk -F';'  '$2 == "-" && $3 == "-" && $4 != "-" && $5 != "-" && $8 != "-" || $2 == "-" && $3 != "-" && $4 != "-" && $7 != "-"' "$1" | cut -d';' -f4,7,8 | tr '-' '0' | ./exec | while read line;
  do
  echo $line
  done > lv_comp.csv
  sort -t ';' -k2,2n lv_comp.csv -o lv_comp.csv
fi
fi

#4. Individuals linked to a LV station (lv indiv) :
#Selection of the collones concerned in the CSV file.
#Extraction of these in the executable by replacing the "-"" with "0" to facilitate data manipulation.
#Redirection results to an output file with the appropriate name.
if [[ "$2" == "lv" ]] && [[ "$3" == "indiv" ]]; then
  if [[ -n "$4" ]]; then
  awk -F';' -v power_plant="$4" '$1 == power_plant && $2 == "-" && $3 == "-" && $4 != "-" && $6 != "-" && $8 != "-" || $1 == power_plant && $2 == "-" && $3 != "-" && $4 != "-" && $7 != "-"' "$1" | cut -d';' -f4,7,8 | tr '-' '0' | ./exec | while read line;
  do
  echo $line
  done > lv_indiv_$4.csv
  sort -t ';' -k2,2n lv_indiv_$4.csv -o lv_indiv_$4.csv
  else
  awk -F';' '$2 == "-" && $3 == "-" && $4 != "-" && $6 != "-" && $8 != "-" || $2 == "-" && $3 != "-" && $4 != "-" && $7 != "-"' "$1" | cut -d';' -f4,7,8 | tr '-' '0' | ./exec | while read line;
  do
  echo $line
  done > lv_indiv.csv
  sort -t ';' -k2,2n lv_indiv.csv -o lv_indiv.csv
  fi
fi

#5. Individuals and companies linked to a LV station (lv all) :
#Selection of the collones concerned in the CSV file.
#Extraction of these in the executable by replacing the "-"" with "0" to facilitate data manipulation.
#Redirection results to an output file with the appropriate name.
#In this case (lv all), create an additional file with the 10 lv stations that use most energy,
#and the 10 that use least energy.
if [[ "$2" == "lv" ]] && [[ "$3" == "all" ]]; then
  if [[ -n "$4" ]]; then
  awk -F';' -v power_plant="$4" '$1 == power_plant && $2 == "-" && $3 == "-" && $4 != "-" && $8 != "-" || $1 == power_plant && $2 == "-" && $3 == "-" && $4 != "-" && $7 != "-"' "$1" | cut -d';' -f4,7,8 | tr '-' '0' | ./exec| while read line;
  do
  echo $line
  done > lv_all_$4.csv
  sort -t ';' -k2,2n lv_all_$4.csv -o lv_all_$4.csv
  head -n 10 lv_all_$4.csv > lv_min_max_$4.csv
  tail -n 10 lv_all_$4.csv >> lv_min_max_$4.csv
  else
  awk -F';' '$2 == "-" && $3 == "-" && $4 != "-" && $8 != "-" || $2 == "-" && $3 != "-" && $4 != "-" && $7 != "-"' "$1" | cut -d';' -f4,7,8 | tr '-' '0' | ./exec | while read line;
  do
  echo $line
  done > lv_all.csv
  sort -t ';' -k2,2n lv_all.csv -o lv_all.csv
  head -n 10 lv_all.csv > lv_min_max.csv
  tail -n 10 lv_all.csv >> lv_min_max.csv
fi
fi




#Display elapsed time
B=$(date +%s.%N)
diff=$(echo "$B - $A" | bc)
echo "Elapsed time : $diff seconds"
