# HARQ Simulator

A simulation-based study of Hybrid Automatic Repeat reQuest (HARQ) using C++ and Python.

The project models retransmissions over a fading wireless channel and studies how Chase Combining affects throughput and latency.

## Project Description

HARQ is used in wireless communication systems to improve reliability when packets are received with errors.

In this project, an N-process stop-and-wait HARQ system is simulated. When a packet fails, it can be retransmitted up to a configurable number of times.

Two cases are compared:

- HARQ without soft combining
- HARQ with Chase Combining

The simulation is used to study the effect of SNR, BLER and the number of parallel HARQ processes on system performance.

## Objectives

The main objectives are:

1. Implement an N-process HARQ simulator in C++.
2. Model a fading wireless channel with configurable BLER.
3. Implement retransmission of failed packets.
4. Implement Chase Combining for soft combining.
5. Measure throughput and latency.
6. Study performance for different SNR values.
7. Study performance for different BLER values.
8. Study the effect of the number of HARQ processes.
9. Generate performance plots using Python.

## Technologies Used

- C++17
- Python 3
- Pandas
- Matplotlib
- Git
- GitHub Actions

## Project Structure

```text
HARQ-Simulator/
│
├── cpp/
│   ├── main.cpp
│   ├── channel.h
│   ├── channel.cpp
│   ├── harq_process.h
│   ├── harq_process.cpp
│   ├── simulator.h
│   └── simulator.cpp
│
├── python/
│   ├── plot_results.py
│   ├── analyze_results.py
│   └── requirements.txt
│
├── results/
│   ├── harq_results.csv
│   └── figures/
│
├── report/
│   └── HARQ_Simulation_Report.pdf
│
├── .github/
│   └── workflows/
│       └── harq_simulation.yml
│
├── README.md
├── .gitignore
└── LICENSE