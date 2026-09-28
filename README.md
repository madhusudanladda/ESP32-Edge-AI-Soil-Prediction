#  ESP32 Edge AI Soil Intelligence & Prediction System

<p align="center">
  <b>7 Sensor Parameters + 10 AI-Predicted Parameters = 17 Soil Parameters</b>
</p>

<p align="center">
  An embedded Edge AI system for real-time soil monitoring and multi-parameter soil property prediction.
</p>

---

## Overview

The **ESP32 Edge AI Soil Intelligence System** is designed to acquire real-time soil parameters from a 7-in-1 soil sensor and use an embedded machine learning model to predict additional soil properties.

The system combines directly measured sensor values with AI-predicted soil properties to provide a total of **17 soil parameters** from a single sensing and inference workflow.

The architecture is designed around:

7 Directly Measured Parameters
              +
10 AI-Predicted Parameters
              =
17 Total Soil Parameters



## System Concept

The complete system works as a combination of sensor-based measurement and Edge AI prediction.
              7-in-1 Soil Sensor
                      │
                      ▼
               RS485 / Modbus
                      │
                      ▼
                    ESP32
                      │
          ┌───────────┴───────────┐
          │                       │
          ▼                       ▼
   Direct Sensor Values       ML Processing
          │                       │
          │                       ▼
          │                 AI Prediction
          │                       │
          └───────────┬───────────┘
                      ▼
              17 Soil Parameters

The ESP32 acts as the main embedded processing unit responsible for sensor data acquisition, data processing, and execution of the machine learning inference pipeline.

## 17 Soil Parameters

The system provides a total of 17 soil parameters.

Directly Measured Parameters — 7

The 7-in-1 soil sensor provides:

#	Parameter	Source
1	Soil Moisture	                Sensor
2	Soil Temperature	            Sensor
3	pH	                          Sensor
4	Electrical Conductivity (EC)	Sensor
5	Nitrogen (N)	                Sensor
6	Phosphorus (P)	              Sensor
7	Potassium (K)	                Sensor

These values are directly acquired from the soil sensor through the RS485/Modbus communication interface.

AI-Predicted Parameters — 10

The machine learning model predicts additional soil properties:

#	Parameter	Source
8	Organic Carbon (OC)	  AI Prediction
9	Calcium (Ca)	        AI Prediction
10	Magnesium (Mg)	    AI Prediction
11	Sulphur (S)      	  AI Prediction
12	Boron (B)	          AI Prediction
13	Zinc (Zn)	          AI Prediction
14	Iron (Fe)	          AI Prediction
15	Copper (Cu)	        AI Prediction
16	Manganese (Mn)	    AI Prediction
17	Total Carbon (C)	  AI Prediction

Therefore:

7 Sensor Parameters
        +
10 AI Predictions
        =
17 Soil Parameters

## Machine Learning Approach

The system uses a Multi-Output Ridge Regression model for soil property prediction.

Although the sensor provides 7 values, the current public training dataset contains compatible laboratory measurements for pH, EC, N, P and K. Therefore, these five parameters are used as the current ML model features.

The remaining two sensor values — moisture and temperature — are still available as part of the complete sensor output and can be displayed, logged, and used by the overall system.

Current ML Input

pH  
EC  
N  
P  
K  

ML Output
OC  
Ca  
Mg  
S  
B  
Zn  
Fe  
Cu  
Mn  
C  


## Implementation

The system implementation consists of four major stages:

1. Soil Data Acquisition
          ↓
2. Data Processing
          ↓
3. Machine Learning Inference
          ↓
4. 17-Parameter Soil Output

   
1. Soil Data Acquisition

The 7-in-1 soil sensor provides real-time soil measurements through an RS485 communication interface.

The ESP32 receives the sensor data and extracts:

Moisture
Temperature
pH
EC
N
P
K

2. Data Processing

The acquired sensor values are converted into numerical features suitable for the machine learning model.

For the current trained model, the ML feature vector is:

[pH, EC, N, P, K]

The values are standardized using the same scaling parameters used during model training.


3. Machine Learning Inference

The processed values are passed through the trained multi-output regression model.

The model generates predictions for:

OC
Ca
Mg
S
B
Zn
Fe
Cu
Mn
C

4. Final Soil Output

The directly measured values and AI-predicted values are combined into a single soil information set containing:

17 Total Parameters


## Model Architecture

The machine learning pipeline follows:

Sensor / Dataset
      │
      ▼
Feature Selection
      │
      ▼
Data Standardization
      │
      ▼
Multi-Output Ridge Regression
      │
      ▼
10 Soil Property Predictions


## Dataset

The model was developed using a public soil dataset containing laboratory-measured soil properties from the Northern Western Ghats of India.

Dataset Source

Zenodo

DOI:

10.5281/zenodo.15519844

The dataset contains laboratory measurements for multiple soil properties including:

pH
Electrical Conductivity
Organic Carbon
Nitrogen
Phosphorus
Potassium
Calcium
Magnesium
Sulphur
Boron
Zinc
Iron
Copper
Manganese
Total Carbon


## Model Evaluation

The Edge AI model was evaluated using 5-fold cross-validation. The performance of each predicted soil parameter is measured using **R² (Coefficient of Determination)** and **MAE (Mean Absolute Error)**.

| Predicted Parameter | R² | MAE |
|---|---:|---:|
| Organic Carbon (OC) | -0.315 | 0.283 |
| Calcium (Ca) | 0.499 | 137.12 |
| Magnesium (Mg) | 0.211 | 22.10 |
| Sulphur (S) | 0.226 | 0.96 |
| Boron (B) | -0.086 | 0.020 |
| Zinc (Zn) | -0.307 | 12.74 |
| Iron (Fe) | 0.221 | 13.01 |
| Copper (Cu) | 0.231 | 0.81 |
| Manganese (Mn) | 0.204 | 36.40 |
| Total Carbon (C) | 0.138 | 0.37 |

### Overall Model Result

| Evaluation Metric | Result |
|---|---:|
| Mean R² | **0.1024** |
| Mean MAE | **22.3810** |

The model provides multi-parameter soil predictions from the available sensor-derived inputs using a multi-output Ridge Regression approach.

## Running the ML Project
1. Clone the Repository
git clone https://github.com/madhusudanladda/ESP32-Edge-AI-Soil-Prediction
2. Enter the Project Directory
cd ESP32-Edge-AI-Soil-Prediction
3. Install Dependencies
pip install -r requirements.txt
4. Run the Training and Evaluation
python train.py

The training process performs:

Dataset Loading
      ↓
Feature Selection
      ↓
Feature Scaling
      ↓
Model Training
      ↓
5-Fold Cross-Validation
      ↓
R² Evaluation
      ↓
MAE Evaluation

The evaluation script generates parameter-wise model performance results.

## ESP32 Running Process

The ESP32 side of the system follows the following operating sequence:

ESP32 Start
    │
    ▼
Initialize RS485
    │
    ▼
Read 7-in-1 Soil Sensor
    │
    ▼
Receive Sensor Values
    │
    ├── Moisture
    ├── Temperature
    ├── pH
    ├── EC
    ├── N
    ├── P
    └── K
    │
    ▼
Prepare ML Features
    │
    ▼
Apply Feature Scaling
    │
    ▼
Run ML Inference
    │
    ▼
Generate 10 Predictions
    │
    ▼
Combine Sensor + AI Values
    │
    ▼
Display / Log 17 Parameters

The embedded implementation is designed to perform the inference locally rather than requiring a continuous cloud connection for every prediction.

## System Output

#### Soil Inspection — Direct Sensor Values

| Parameter | Value | Source |
|---|---:|---|
| Soil Moisture | 42.5 % | 7-in-1 Soil Sensor |
| Soil Temperature | 28.4 °C | 7-in-1 Soil Sensor |
| pH | 6.72 | 7-in-1 Soil Sensor |
| EC | 0.84 mS/cm | 7-in-1 Soil Sensor |
| Nitrogen (N) | 118 mg/kg | 7-in-1 Soil Sensor |
| Phosphorus (P) | 24.6 mg/kg | 7-in-1 Soil Sensor |
| Potassium (K) | 186 mg/kg | 7-in-1 Soil Sensor |

#### AI-Predicted Soil Parameters

| Parameter | AI Prediction | Source |
|---|---:|---|
| Organic Carbon (OC) | 1.24 % | Edge AI Model |
| Calcium (Ca) | 842.6 mg/kg | Edge AI Model |
| Magnesium (Mg) | 126.8 mg/kg | Edge AI Model |
| Sulphur (S) | 10.42 mg/kg | Edge AI Model |
| Boron (B) | 0.38 mg/kg | Edge AI Model |
| Zinc (Zn) | 1.92 mg/kg | Edge AI Model |
| Iron (Fe) | 38.7 mg/kg | Edge AI Model |
| Copper (Cu) | 1.21 mg/kg | Edge AI Model |
| Manganese (Mn) | 112.4 mg/kg | Edge AI Model |
| Carbon (C) | 0.72 % | Edge AI Model |

