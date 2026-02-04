# 🌌 Realistic 3D Black Hole Simulation

A real-time **3D black hole physics simulation** created using **C++, OpenGL, GLUT, and GLM**. This project visualizes gravitational attraction, star particle motion, warped spacetime, and a glowing rotating accretion disk for a cinematic black hole effect.

---

## 🚀 Features

* 🌑 Central 3D black hole (event horizon)
* 💫 Rotating glowing accretion disk
* ✨ Star particles attracted into the black hole
* 🌀 Gravity-based particle physics
* 🌠 Warped spacetime grid visualization
* 🎥 Smooth rotating 3D camera
* ⚡ Real-time rendering using OpenGL

---

## 🛠 Tech Stack

* **Language:** C++
* **Graphics:** OpenGL + GLUT
* **Math:** GLM
* **Build System:** CMake

---

## 📁 Project Structure

```text
Blackhole3D/
│
├── src/
│   └── main.cpp
│
├── CMakeLists.txt
│
├── build/
│
└── README.md
```

---

## ⚙️ Build & Run Instructions

### 1. Install Dependencies (One Time Only)

```bash
vcpkg install freeglut glm
```

---

### 2. Configure Project

```bash
mkdir build
cd build
cmake -G "Visual Studio 17 2022" -A x64 -DCMAKE_TOOLCHAIN_FILE=C:/vcpkg/scripts/buildsystems/vcpkg.cmake ..
```

---

### 3. Build

```bash
cmake --build . --config Release
```

---

### 4. Run

```bash
.\Release\BlackHole3D.exe
```

---

## 🎮 Simulation Behavior

* Stars orbit and spiral inward due to gravity.
* Particles accelerate near the black hole and disappear after crossing the event horizon.
* Accretion disk rotates dynamically around the black hole.
* Camera smoothly orbits around the system.

---

## 🧠 Physics Used

* Newtonian gravity
* Velocity damping for stable motion
* Tangential orbital velocity initialization
* Continuous real-time physics updates

---

## 🔮 Future Improvements

* Free camera movement (WASD + mouse)
* Gravitational lensing effects
* Bloom & HDR glow
* Relativistic physics simulation
* Cinematic rendering

