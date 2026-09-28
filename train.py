import pandas as pd
import numpy as np
from sklearn.model_selection import KFold
from sklearn.preprocessing import StandardScaler
from sklearn.linear_model import Ridge
from sklearn.metrics import r2_score, mean_absolute_error

FEATURES = ["pH","EC","N","P","K"]
TARGETS = ["OC","Ca","Mg","S","B","Zn","Fe","Cu","Mn","C"]

df = pd.read_csv("data/Sahyadri2024_soil_properties.csv")
X = df[FEATURES].astype(float)
Y = df[TARGETS].astype(float)

kf = KFold(n_splits=5, shuffle=True, random_state=42)
pred = np.zeros_like(Y.values)

for train_idx, test_idx in kf.split(X):
    xs = StandardScaler().fit(X.iloc[train_idx])
    ys = StandardScaler().fit(Y.iloc[train_idx])
    model = Ridge(alpha=1.0)
    model.fit(xs.transform(X.iloc[train_idx]), ys.transform(Y.iloc[train_idx]))
    pred[test_idx] = ys.inverse_transform(model.predict(xs.transform(X.iloc[test_idx])))

r2 = r2_score(Y, pred, multioutput="raw_values")
mae = mean_absolute_error(Y, pred, multioutput="raw_values")

print("5-fold cross-validation")
for name, r, e in zip(TARGETS, r2, mae):
    print(f"{name:>3}  R2={r:7.3f}  MAE={e:10.4f}")
print("Mean R2:", round(float(r2.mean()), 3))
print("Mean MAE:", round(float(mae.mean()), 4))

# For deployment, retrain on all samples and export coefficients as needed.
