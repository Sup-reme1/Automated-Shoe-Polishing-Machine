# Automated Shoe Polishing Machine

An autonomous, multi-axis mechatronic system designed to provide consistent and efficient footwear maintenance. This project replaces labor-intensive manual polishing with a synchronized hardware-software solution controlled by an **Arduino** microcontroller.

---

## 🚀 Features
* **Multi-Axis Motion Control:** Utilizes three **NEMA 17 stepper motors** for precise linear translation and 360-degree shoe rotation.
* **Dual-Action Brushing:** Features a high-torque **28BYJ-48 motor** dedicated to brush rotation, supporting both horizontal and vertical cleaning orientations.
* **Automated Fluid Delivery:** Integrated **mini DC pump** and spray nozzle system for uniform polish distribution.
* **Sensor-Driven Logic:** Sequential operational algorithm that verifies shoe presence, liquid levels, and safety door status before initiation.
* **Stable Power Architecture:** Optimized for a **12V DC** power supply to handle simultaneous inductive loads from motors and pumps.

---

## 🛠️ Hardware Components
* **Microcontroller:** Arduino (Uno/Mega)
* **Actuators:**
    * 3x NEMA 17 Stepper Motors (Translation & Rotation)
    * 1x 28BYJ-48 Stepper Motor (Brush Drive)
    * 1x 12V Mini DC Submersible Pump
* **Drivers:** A4988 / ULN2003 Driver Modules
* **Sensors:** IR Proximity Sensors, Magnetic Reed Switches, Non-contact Liquid Level Sensors
* **Power:** 12V DC Adapter (or 4S LiFePO4 Battery Pack with BMS)

---

## 🔧 Installation & Setup
1.  **Mechanical Assembly:** Construct the frame ensuring the **Rod Supports** and **Threaded Rod** are aligned for smooth translation.
2.  **Wiring:** Connect the stepper motors to their respective drivers and the DC pump to a relay or MOSFET module. Ensure a common ground for the 12V and 5V rails.
3.  **Firmware:**
    * Open `SETUP` in the Arduino IDE.
    * Install necessary libraries.
    * Upload the code to your Arduino board.

---

## 🤝 Acknowledgments
* **Supervisor:** Prof. A. I. O. Yussuff (Lagos State University)
* **Technical Collaborator:** Hassan Abdulgafar, Tairu Abdulgafar, Okpare Joshua, Abayomi Jude and Electronic and Computer Engineer and Technologist.
* **Mechanical Support:** LASU Mechanical Workshop Engineers and Technologist.

---

## 📜 License
This project is developed as part of an Electronic and Computer Engineering Final Year Project at Lagos State University. Distributed under the MIT License.

**Developer:** Ajibowu Abdulbasit 
