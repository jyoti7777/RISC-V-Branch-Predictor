# Branch Prediction Analysis

This repository contains a comprehensive analysis of various branch prediction methods implemented in C++ and includes a detailed report on the results of these predictions.

## Folder Structure

- **branch_predictor_204.cpp**
  - **Description:** This C++ program analyzes four branch predictors: always taken, always not-taken, one-bit, and two-bit.
  - **Functionality:** The program reads a trace from a text document (default name: `input.txt`) limited to one million lines. It then analyzes the trace and prints the Branch Target Buffer (PC of the branch instruction, target address PC, and history) along with the overall accuracy of the four predictors.
  - **Note:** The name of the trace document should be specified at line 51 of the code.

- **Branch_Prediction_Analysis_Report.pdf**
  - **Description:** This document provides an in-depth report of the analysis conducted on the branch predictors. It includes the methodology, results, and conclusions drawn from the experiments.

## Branch Prediction Methods

Branch prediction is crucial in modern computer architectures to enhance performance by speculatively executing instructions. In the context of RISC-V architecture, several branch prediction methods are commonly employed:

- **Always Taken:** Assumes all branches are always taken.
- **Always Not Taken:** Assumes branches are never taken.
- **1-Bit Predictor:** Uses a single-bit saturating counter for each branch.
- **2-Bit Predictor:** Uses a two-bit saturating counter for improved prediction accuracy.

### Analysis

#### Factorial Code Prediction Analysis:
- **Always Taken Predictor:** 65.506%
- **Always Not Taken Predictor:** 34.494%
- **1-Bit Predictor:** 87.7293%
- **2-Bit Predictor:** 89.6991%


### Inferences

- **Always Taken Predictor:** Averages about 60% accuracy, indicating that 'taken' branches generally outweigh 'not taken' branches.
- **Always Not Taken Predictor:** Averages about 40% accuracy, suggesting that 'not taken' branches are less frequent.
- **1-Bit Predictor:** Averages about 92-93% accuracy, performing well with consecutive 'taken' or 'not taken' statements but poorly with alternating patterns.
- **2-Bit Predictor:** Averages about 94-95% accuracy, handling consecutive 'taken' or 'not taken' statements well and improving performance with alternating patterns compared to the 1-bit predictor.


