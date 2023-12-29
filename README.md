# Traveling Salesman Problem Solver for Turkish Cities

This project aims to solve the Traveling Salesman Problem using heuristic algorithms, finding the shortest route among Turkish cities based on distance matrices.

## Features

- Reads distance values between Turkish cities from an Excel file.
- Implements various heuristic algorithms (Nearest Neighbor, Farthest Insertion, Cheapest Insertion, Clark and Wright) to find the Hamiltonian tour efficiently.
- Ensures the generated tour adheres to specified constraints: each city is visited only once, starting and ending in Ankara.

## Installation

1. Clone the repository.
2. Ensure you have [Python](https://www.python.org/) installed.
3. Install necessary packages using `pip install -r requirements.txt`.

## Usage

1. Place the 'Mesafe.xls' file with city distance values in the project directory.
2. Run the main script: `python main.py`.
3. Follow the instructions to select an algorithm and see the tour results.

## Algorithms Implemented

- Nearest Neighbor Algorithm
- Farthest Insertion Algorithm
- Cheapest Insertion Algorithm
- Clark and Wright (Savings) Algorithm

