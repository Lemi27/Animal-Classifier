# Animal-Classifier

A **K-Nearest Neighbors (KNN) classifier** implemented in **C**, designed to classify animals based on their features from the **UCI Zoo Dataset**. This project reads structured data, calculates similarity measures, and predicts animal classes using machine learning techniques.

## Features
- **Reads animal data** from an external text file (`a1Data.txt`).
- **Calculates distance metrics** (Euclidean, Hamming, Jaccard similarity).
- **Implements K-Nearest Neighbors (KNN)** to classify new animal samples.
- **Predicts animal categories** based on dataset features.
- **Computes accuracy** of the classifier on a test dataset.

## Installation
1. Clone the repository:
   ```bash
   git clone https://github.com/yourusername/KNN-Animal-Classifier.git
   cd KNN-Animal-Classifier

2. Compile the program using the provided makefile:
   ```bash
   make

3. Run the compiled program:
   ```bash
   ./miyuLemiA1 a1data.txt
