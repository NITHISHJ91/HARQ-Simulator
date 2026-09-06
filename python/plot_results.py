import matplotlib

matplotlib.use("Agg")

import pandas as pd
import matplotlib.pyplot as plt
from pathlib import Path


INPUT_FILE = Path("results/harq_results.csv")
OUTPUT_FOLDER = Path("results/figures")

OUTPUT_FOLDER.mkdir(
    parents=True,
    exist_ok=True
)

df = pd.read_csv(INPUT_FILE)

df["scheme"] = df["soft_combining"].map({
    0: "Without Chase Combining",
    1: "With Chase Combining"
})


def create_plot(
    x_column,
    y_column,
    experiment,
    title,
    x_label,
    y_label,
    filename
):

    data = df[
        df["experiment"] == experiment
    ]

    plt.figure(figsize=(8, 5))

    for scheme in data["scheme"].unique():

        scheme_data = data[
            data["scheme"] == scheme
        ]

        plt.plot(
            scheme_data[x_column],
            scheme_data[y_column],
            marker="o",
            label=scheme
        )

    plt.title(title)

    plt.xlabel(x_label)

    plt.ylabel(y_label)

    plt.grid(True, alpha=0.3)

    plt.legend()

    plt.tight_layout()

    plt.savefig(
        OUTPUT_FOLDER / filename,
        dpi=200
    )

    plt.close()


# 1. Throughput vs SNR

create_plot(
    "snr_db",
    "throughput_mbps",
    "snr_sweep",
    "Throughput vs SNR",
    "SNR (dB)",
    "Throughput (Mbps)",
    "throughput_vs_snr.png"
)


# 2. Latency vs SNR

create_plot(
    "snr_db",
    "average_latency_slots",
    "snr_sweep",
    "Latency vs SNR",
    "SNR (dB)",
    "Average Latency (slots)",
    "latency_vs_snr.png"
)


# 3. Throughput vs BLER

create_plot(
    "bler",
    "throughput_mbps",
    "bler_sweep",
    "Throughput vs BLER",
    "BLER",
    "Throughput (Mbps)",
    "throughput_vs_bler.png"
)


# 4. Latency vs BLER

create_plot(
    "bler",
    "average_latency_slots",
    "bler_sweep",
    "Latency vs BLER",
    "BLER",
    "Average Latency (slots)",
    "latency_vs_bler.png"
)


# 5. Throughput vs HARQ Processes

create_plot(
    "num_processes",
    "throughput_mbps",
    "process_sweep",
    "Throughput vs Number of HARQ Processes",
    "Number of HARQ Processes",
    "Throughput (Mbps)",
    "throughput_vs_processes.png"
)


# 6. Latency vs HARQ Processes

create_plot(
    "num_processes",
    "average_latency_slots",
    "process_sweep",
    "Latency vs Number of HARQ Processes",
    "Number of HARQ Processes",
    "Average Latency (slots)",
    "latency_vs_processes.png"
)


print("All six HARQ plots generated successfully.")