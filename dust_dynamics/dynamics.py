import numpy as np
import time

# from calculateCharge import Charge
# from calculatePlasmaE import Plasma
from calculateDustsE import calculateDustsE
from fit import fit
import warnings
import sys

warnings.filterwarnings("ignore")

directory = sys.argv[1]


k_B = 1.380649e-23  # Boltzmann constant (J/K)
m_i = 6.6335209e-26  # Ar+ ions' mass (kg)

# Regular Loop ~ 1-2 Pa
P = 0.25 * 18.131842  # Pressure (Pascal)
r_D_e = 0.0016622715189364113

g = 9.8  # free fall acceleration (m/s^2)
rho = 1500  # mass density of dust particle
n_dust = 50_000  # number of dust particles time steps
T_p = 300  # Kinetic temperature of dust particles motion

# эти 1.1 1.2 2.0 от Ez trap
E_x_trap = -1.0 * 1035598  # x-trap (kg/s^2)
E_y_trap = -1.0 * 1035598  # y-trap (kg/s^2)
d_t_p = 5e-5  # integration step for dust particles dynamics, s
N_p = 2  # number of dust particles
r_p = 4.445e-6  # Dust particle radius
Q = -3e-15

# Regular Loop >= 0.1 ... 0.5
# its neccsary dist >= l
q = -0.3 * Q
l = 0.3 * r_D_e

m_p = 4.0 / 3.0 * np.pi * r_p**3 * rho
n_output = 200
output_filename = directory + "trajectory.xyz"
file = open(output_filename, "w")
file.close()
data_filename = directory + "data.txt"
data_file = open(data_filename, "w")
data_file.close()
x, y, z = np.zeros((n_dust, N_p)), np.zeros((n_dust, N_p)), np.zeros((n_dust, N_p))
v_x, v_y, v_z = (
    np.zeros((n_dust, N_p)),
    np.zeros((n_dust, N_p)),
    np.zeros((n_dust, N_p)),
)
f_x, f_y, f_z = (
    np.zeros((n_dust, N_p)),
    np.zeros((n_dust, N_p)),
    np.zeros((n_dust, N_p)),
)

# plasma = Plasma()

# charge = Charge(directory)

# q = np.zeros((n_dust, N_p))

t = np.zeros(n_dust)

# 0.6 | 0.7 | 0.8
z[0] = np.array([0.7 * r_D_e, 0.0])

# Regular loop R ~ .2 r_D_e
# может задать нижней частице нач скорость вбок
# Q2 немного меньше чем Q1 (Q2 -- нижняя)

# q[0] = charge.calculateLinearCharge(x[0]/r_D_e,y[0]/r_D_e,z[0]/r_D_e)
# E_x_plasma, E_y_plasma, E_z_plasma = plasma.calculatePlasmaE(x[0]/r_D_e,y[0]/r_D_e,z[0]/r_D_e, q[0])
interaction1, interaction2 = calculateDustsE(x[0], y[0], z[0], r_D_e, l, q, Q)

E_trap_to_approximate = (
    m_p * g / Q * np.ones(N_p) - np.array([interaction1[2], interaction2[2]]) / Q
)

E_0, alpha = fit(z[0], E_trap_to_approximate)

print(E_0, alpha, sep="\n")

print(E_0 + alpha * z[0] - E_trap_to_approximate)

for iteration in range(1, n_dust):
    start = time.time()
    v_T = np.sqrt(k_B * T_p / m_i)
    gamma_p = 8.0 / 3.0 * np.sqrt(2.0 * np.pi) * r_p**2 * P / v_T / m_p 
    s_p = np.sqrt(2 * k_B * T_p * m_p * gamma_p / d_t_p)
    f_therm_p_x = np.random.normal(0, s_p, N_p) - m_p * gamma_p * v_x[iteration - 1]
    f_therm_p_y = np.random.normal(0, s_p, N_p) - m_p * gamma_p * v_y[iteration - 1]
    f_therm_p_z = np.random.normal(0, s_p, N_p) - m_p * gamma_p * v_z[iteration - 1]

    x_time = x[iteration - 1]
    y_time = y[iteration - 1]
    z_time = z[iteration - 1]
    q_time = Q
    # q_time = charge.calculateLinearCharge(x_time/r_D_e,y_time/r_D_e,z_time/r_D_e)
    # E_x_plasma, E_y_plasma, E_z_plasma = plasma.calculatePlasmaE(
    #     x_time / r_D_e, y_time / r_D_e, z_time / r_D_e, q_time
    # )
    # E_x_dusts, E_y_dusts, E_z_dusts = calculateDustsE(
    # x_time / r_D_e, y_time / r_D_e, z_time / r_D_e, q_time
    # )

    interaction1, interaction2 = calculateDustsE(x_time, y_time, z_time, r_D_e, l, q, Q)

    E_z_trap = E_0 + alpha * z_time

    a_x = (
        -E_x_trap * q_time * x_time / m_p
        + np.array([interaction1[0], interaction2[0]]) / m_p
        + f_therm_p_x / m_p
    )
    a_y = (
        -E_y_trap * q_time * y_time / m_p
        + np.array([interaction1[1], interaction2[1]]) / m_p
        + f_therm_p_y / m_p
    )
    a_z = (
        -g
        + E_z_trap * q_time  / m_p
        + np.array([interaction1[2], interaction2[2]]) / m_p
        + f_therm_p_z / m_p
    )

    x[iteration] = x[iteration - 1] + v_x[iteration - 1] * d_t_p + 0.5 * a_x * d_t_p**2
    y[iteration] = y[iteration - 1] + v_y[iteration - 1] * d_t_p + 0.5 * a_y * d_t_p**2
    z[iteration] = z[iteration - 1] + v_z[iteration - 1] * d_t_p + 0.5 * a_z * d_t_p**2

    v_x[iteration] = v_x[iteration - 1] + a_x * d_t_p
    v_y[iteration] = v_y[iteration - 1] + a_y * d_t_p
    v_z[iteration] = v_z[iteration - 1] + a_z * d_t_p

    # q[iteration] = q_time

    t[iteration] = t[iteration - 1] + d_t_p
    end = time.time()

    if iteration % n_output == 0:
        file = open(output_filename, "a")
        file.write("{}\n".format(N_p))
        file.write("{}\n".format(iteration))
        for j in range(N_p):
            file.write(
                "{}\t{}\t{}\t{}\n".format(
                    "Ar", x[iteration][j], y[iteration][j], z[iteration][j]
                )
            )
        file.close()

        output_string = "{}".format(t[iteration])
        for j in range(N_p):
            output_string += "\t{}\t{}\t{}\t{}\t{}\t{}\t{}\t{}".format(
                x[iteration][j],
                y[iteration][j],
                z[iteration][j],
                v_x[iteration][j],
                v_y[iteration][j],
                v_z[iteration][j],
                a_x[j] * m_p - f_therm_p_x[j],
                a_z[j] * m_p - f_therm_p_z[j],
            )
        output_string += "\n"
        data_file = open(data_filename, "a")
        data_file.write(output_string)
        data_file.close()
        print("iter {} out of {}".format(iteration, n_dust))
