import numpy as np


def calculateDustsE(xs, ys, zs, r_D_e, l, q, Q):
    eps_0 = 8.85418781762039e-12  # vacuum dielectric permitivity
    k = 1.0 / (eps_0 * 4.0 * np.pi)

    h = zs[0] - zs[1]

    R12 = np.linalg.norm(xs - ys)

    # r = np.sqrt(R12**2 + h**2)
    # R = np.sqrt(R12**2 + (h - l)**2)

    # f12p = k * Q * Q * 

    f12p = (
        k
        * q
        * Q
        / np.sqrt((h - l) ** 2 + R12**2)
        * np.exp(-np.sqrt((h - l) ** 2 + R12**2) / r_D_e)
        * (1.0 / np.sqrt((h - l) ** 2 + R12**2) + 1.0 / r_D_e)
    )
    f12m = (
        k
        * Q
        * Q
        / np.sqrt(h**2 + R12**2)
        * np.exp(-np.sqrt(h**2 + R12**2) / r_D_e)
        * (1.0 / np.sqrt(h**2 + R12**2) + 1.0 / r_D_e)
    )

    f1 = (
        f12m
        * np.array([xs[0] - xs[1], ys[0] - ys[1], zs[0] - zs[1]])
        # / np.sqrt(h**2 + R12**2)
    )
    f2 = -f12m * np.array([xs[0] - xs[1], ys[0] - ys[1], zs[0] - zs[1]]) / np.sqrt(
        h**2 + R12**2
    ) - f12p * np.array([xs[0] - xs[1], ys[0] - ys[1], zs[0] - zs[1] + l]) / np.sqrt(
        (h - l) ** 2 + R12**2
    )

    return f1, f2
