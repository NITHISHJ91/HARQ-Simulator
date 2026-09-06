import pandas as pd
from pathlib import Path


INPUT_FILE = Path("results/harq_results.csv")

df = pd.read_csv(INPUT_FILE)


print("=" * 60)
print("HARQ SIMULATION ANALYSIS")
print("=" * 60)

print()

print("Total simulation records:", len(df))

print()

print("Experiments:")
print(df["experiment"].value_counts())

print()

print("Soft combining comparison:")
print(
    df.groupby("soft_combining")[
        "throughput_mbps"
    ].mean()
)

print()

print("Average latency:")
print(
    df.groupby("soft_combining")[
        "average_latency_slots"
    ].mean()
)

print()

print("Average success rate:")
print(
    df.groupby("soft_combining")[
        "success_rate"
    ].mean()
)

print()

print("Average retransmission rate:")
print(
    df.groupby("soft_combining")[
        "retransmission_rate"
    ].mean()
)

print()

print("=" * 60)
print("Analysis completed.")
print("=" * 60)