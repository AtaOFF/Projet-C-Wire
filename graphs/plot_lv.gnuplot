# Configuration du fichier de données
set datafile separator ";"

# Sortie graphique
set terminal pngcairo size 1200,600 enhanced font 'Arial,14'
set output 'lv_min_max_bars.png'

# Configuration des axes
set title "Postes LV les plus et les moins chargés" font ",16"
set xlabel "Postes LV (Identifier)" font ",14"
set ylabel "Consommation (Load - Capacity)" font ",14"

# Rotation des étiquettes X pour une meilleure lisibilité
set xtics rotate by -45 font ",10"

# Configuration des couleurs
set style fill solid 1.0 border -1
set boxwidth 0.8

# Ajouter une ligne de référence pour la capacité zéro
set grid y
set arrow from -0.5,0 to 20.5,0 nohead lt 1 lc rgb "black" lw 2

# Plot en barres
plot "lv_min_max_with_diff.csv" using 0:($4>0?$4:0):xtic(1) with boxes lc rgb "red" title "Surcharge", \
     "" using 0:($4<0?$4:0) with boxes lc rgb "green" title "Marge"
