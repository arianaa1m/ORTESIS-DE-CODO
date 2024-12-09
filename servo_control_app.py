import serial
import tkinter as tk

# Configurar la conexión serial con el Arduino
arduino = serial.Serial(port='COM5', baudrate=9600, timeout=1)

# Funciones para enviar comandos al Arduino
def move_anticlockwise():
    arduino.write(b'A')

def move_to_initial():
    arduino.write(b'B')

# Crear la interfaz de usuario con tkinter
root = tk.Tk()
root.title("Control de Servomotor")

# Botón para mover en sentido antihorario
btn_anticlockwise = tk.Button(root, text="Mover Antihorario", command=move_anticlockwise)
btn_anticlockwise.pack(pady=10)

# Botón para volver a la posición inicial
btn_initial = tk.Button(root, text="Volver a Inicial", command=move_to_initial)
btn_initial.pack(pady=10)

# Iniciar el bucle principal de la interfaz
root.mainloop()
