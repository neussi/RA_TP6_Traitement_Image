# Traitement d'Image From Scratch

## Description
Développement d'une structure d'image performante et d'algorithmes de traitement de bas niveau pour la détection de marqueurs.

Ce projet fait partie du cursus de Réalité Augmentée From Scratch (Semestre 1). L'implémentation est réalisée entièrement en C++17 sans bibliothèque tierce (Zero STL), en suivant les directives de développement moteur Jenga/Nkentseu.

## Fonctionnalités implémentées
- Gestion du buffer RGBA contigu.
- Entrées/Sorties au format PPM P6.
- Image Intégrale (Summed Area Table) pour des requêtes en O(1).
- Seuillage adaptatif (Adaptive Thresholding) optimisé.

## Installation et Compilation
Le projet utilise le système de build **Jenga**.

1. Assurez-vous d'avoir Jenga installé sur votre système.
2. Clonez le dépôt :
   ```bash
   git clone git@github.com:neussi/RA_TP6_Traitement_Image.git
   cd RA_TP6_Traitement_Image
   ```
3. Compilez le projet :
   ```bash
   jenga build
   ```
4. Exécutez le programme :
   ```bash
   jenga run TP6
   ```

## Résultats
Le programme génère des sorties dans la console et, le cas échéant, des fichiers images (.ppm) illustrant les concepts mathématiques et graphiques abordés.

## Auteur
**NEUSSI NJIETCHEU PATRICE EUGNE**
Matricule : 24P820
