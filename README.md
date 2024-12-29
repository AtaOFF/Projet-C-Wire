# Projet-C-Wire
Développé par **Alicia Kellai**, **Atahan Ozsolak** et **Hiba Mesbahi**

**C-Wire** est un programme pour analyser et traiter les données d'un système de distribution d'électricité d'un réseau complexe. Il simule les consommations ou/et les capacités des sous-stations (HV-B, HV-A), des postes LV et leurs consommateurs (individuels ou entreprises).
Il combine un **script Shell** pour le filtrage des données et un **programme C** pour la construction et la manipulation d'un arbre AVL afin de calculer et visualiser des résultats. 

L'objectif esr de permettre une analyse rapide et structurée des données fournies dans un ficher **CSV**.

## **Etapes d'installation et de lancement**
1. Prérequis:
   - [Linux](https://www.linux.org/pages/download/#google_vignette) (recommandé) ou [Windows](https://www.microsoft.com/fr-fr/software-download/windows11).
   - Un compilateur C installé sur votre ordinateur (par exemple [GCC](https://fr.wikipedia.org/wiki/GNU_Compiler_Collection)).
   - Avoir [Gnuplot](https://fr.wikipedia.org/wiki/Gnuplot) sur son ordinateur.
   - Téléchargez les fichiers source du programme (les fichiers de simulations CSV sont compris dedans) sur [ce dépot **Github**](https://github.com/AtaOFF/Projet-C-Wire).
2. Lancement du projet
   - Ouvrez le terminal et accédez au répertoire contenant les fichiers source.
   - Donner les droits d'exécution au script Shell : ``` chmod +x ../c-wire.sh ```
   - Compilez le programme à l'aide de la commande suivante : ``` ./c-wire.sh <fichier_csv> <type_station> <type_consommateur>```

## Arguments possibles
1. ```<fichier.csv>```

   Chemin vers le fichier CSV contenant les données d'entrée (un fichier de simulation est fournis dans le dépot)
   
2. ```type_station```
    - ```hvb``` : Sous-station HV-B
    - ```hva``` : Sous-station HV-A
    - ```lv``` : Postes LV

3. ```type_consommateur```
   - ```comp``` : Entreprises
   - ```indiv``` : Particulier
   - ```all``` : Tous les consommateurs

