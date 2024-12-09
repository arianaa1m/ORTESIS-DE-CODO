import tkinter as tk
from tkinter import ttk, messagebox
import serial
import time
import json


# Configuración inicial de comunicación serial
try:
    arduino = serial.Serial(port="COM5", baudrate=9600, timeout=1)  
except Exception as e:
    arduino = None
    print(f"No se pudo conectar con el Arduino: {e}")

# Cargar pacientes desde archivo
try:
    with open("pacientes.json", "r") as file:
        patients = json.load(file)
except FileNotFoundError:
    patients = []

selected_patient = None

class OrtesisApp:
    def __init__(self, root):
        self.root = root
        self.root.title("Ortesis Inteligente de Codo")
        self.root.geometry("800x600")
        self.root.configure(bg="#f0f8ff")

        self.servo_speed = tk.IntVar(value=100)
        self.servo_angle = tk.IntVar(value=45)

        self.show_main_menu()

    def send_to_arduino(self, command):
        """Envía un comando al Arduino."""
        if arduino:
            try:
                arduino.write(f"{command}\n".encode())
                time.sleep(0.1)
            except Exception as e:
                messagebox.showerror("Error", f"No se pudo enviar el comando: {e}")
        else:
            messagebox.showwarning("Advertencia", "Arduino no está conectado.")

    def show_main_menu(self):
        """Menú principal."""
        for widget in self.root.winfo_children():
            widget.destroy()

        tk.Label(self.root, text="Ortesis Inteligente de Codo", font=("Arial", 20, "bold"), bg="#f0f8ff", fg="#00688b").pack(pady=20)
        tk.Button(self.root, text="Gestión de Pacientes", font=("Arial", 14), bg="#008b8b", fg="white", command=self.show_patient_management).pack(pady=10)
        tk.Button(self.root, text="Modo EMG", font=("Arial", 14), bg="#008b8b", fg="white", command=self.show_emg_mode).pack(pady=10)
        tk.Button(self.root, text="Modo Manual", font=("Arial", 14), bg="#008b8b", fg="white", command=self.show_manual_mode).pack(pady=10)
        tk.Button(self.root, text="Modo Juego (Próximamente)", font=("Arial", 14), bg="gray", fg="white").pack(pady=10)

    def save_patients(self):
        """Guardar pacientes en un archivo."""
        with open("pacientes.json", "w") as file:
            json.dump(patients, file)

    def show_patient_management(self):
        """Gestión de pacientes."""
        for widget in self.root.winfo_children():
            widget.destroy()

        tk.Label(self.root, text="Gestión de Pacientes", font=("Arial", 18, "bold"), bg="#f0f8ff", fg="#00688b").pack(pady=10)

        table_frame = tk.Frame(self.root, bg="#f0f8ff")
        table_frame.pack()

        self.patient_table = ttk.Treeview(table_frame, columns=("Nombre", "Edad"), show="headings")
        self.patient_table.heading("Nombre", text="Nombre")
        self.patient_table.heading("Edad", text="Edad")
        self.patient_table.pack()

        for i, patient in enumerate(patients):
            self.patient_table.insert("", "end", iid=i, values=(patient["name"], patient["age"]))

        tk.Button(self.root, text="Agregar Paciente", font=("Arial", 12), bg="#008b8b", fg="white", command=self.add_patient).pack(pady=10)
        tk.Button(self.root, text="Volver", font=("Arial", 12), bg="#008b8b", fg="white", command=self.show_main_menu).pack(pady=10)

    def add_patient(self):
        """Agregar nuevo paciente."""
        new_window = tk.Toplevel(self.root)
        new_window.title("Agregar Paciente")

        tk.Label(new_window, text="Nombre:").pack(pady=5)
        name_entry = tk.Entry(new_window)
        name_entry.pack(pady=5)

        tk.Label(new_window, text="Edad:").pack(pady=5)
        age_entry = tk.Entry(new_window)
        age_entry.pack(pady=5)

        def save_patient():
            name = name_entry.get()
            age = age_entry.get()
            if name and age.isdigit():
                patients.append({"name": name, "age": int(age), "progress": []})
                self.save_patients()
                messagebox.showinfo("Éxito", "Paciente agregado correctamente.")
                new_window.destroy()
                self.show_patient_management()
            else:
                messagebox.showerror("Error", "Datos inválidos.")

        tk.Button(new_window, text="Guardar", command=save_patient).pack(pady=10)

    def show_emg_mode(self):
        """Modo EMG."""
        self.send_to_arduino("START_EMG")
        messagebox.showinfo("Modo EMG", "Activado")

    def show_manual_mode(self):
        """Modo Manual."""
        self.send_to_arduino("START_MANUAL")
