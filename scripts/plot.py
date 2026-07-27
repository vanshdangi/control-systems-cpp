import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

# ==========================================================
# Configuration
# ==========================================================
CSV_FILE = "output/pid_dc_motor_position.csv"
OUTPUT_FILE = "images/pid_dc_motor_position.png"

TITLE = "PID DC Motor Position"

TARGET = 1.5708

X_LIMITS = (0, 10)
Y_LIMITS = (-2.5, 3.8)

# ==========================================================
# Style
# ==========================================================
plt.style.use("dark_background")

plt.rcParams.update({
    "figure.facecolor": "#111111",
    "axes.facecolor": "#111111",
    "savefig.facecolor": "#111111",

    "font.family": "DejaVu Sans",

    "font.size": 11,
    "axes.titlesize": 18,
    "axes.labelsize": 13,
    "legend.fontsize": 11,

    "axes.edgecolor": "#AAAAAA",
    "axes.linewidth": 1.2,

    "xtick.color": "#DDDDDD",
    "ytick.color": "#DDDDDD",

    "grid.color": "#444444",
    "grid.linestyle": "--",
    "grid.linewidth": 0.8,
    "grid.alpha": 0.45,
})

# ==========================================================
# Load CSV
# ==========================================================
df = pd.read_csv(CSV_FILE)

# ==========================================================
# Plot
# ==========================================================
fig, ax = plt.subplots(figsize=(10, 5))

# Position
ax.plot(
    df["Time"],
    df["Position"],
    color="#8DD3C7",
    linewidth=3,
    label="Position",
)

# Velocity
ax.plot(
    df["Time"],
    df["Velocity"],
    color="#FFF7A8",
    linewidth=2.8,
    label="Velocity",
)

# Target
ax.axhline(
    TARGET,
    color="white",
    linestyle=":",
    linewidth=1.2,
    alpha=0.55,
    label=f"Target ($\pi/2$)",
)

ax.set_yticks([
    -np.pi/2,
    0,
    np.pi/2,
    np.pi
])

ax.set_yticklabels([
    r"$-\pi/2$",
    "0",
    r"$\pi/2$",
    r"$\pi$"
])

# ==========================================================
# Axes
# ==========================================================
ax.set_xlim(*X_LIMITS)
ax.set_ylim(*Y_LIMITS)

ax.set_title(TITLE, pad=18)
ax.set_xlabel("Time (s)")

ax.grid(True)

# Legend
legend = ax.legend(
    loc="upper right",
    frameon=True,
)

legend.get_frame().set_facecolor("#1B1B1B")
legend.get_frame().set_edgecolor("#666666")
legend.get_frame().set_alpha(0.9)

# Remove top/right spines
ax.spines["top"].set_visible(False)
ax.spines["right"].set_visible(False)

plt.tight_layout()

plt.savefig(
    OUTPUT_FILE,
    dpi=300,
    bbox_inches="tight",
)

plt.show()